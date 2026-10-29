/*
 * kyopro-atlas：知識マップ（planning/interfaces.md §7、design.md §8.4・§9.1、design-review T2）
 *
 * docs/guide/knowledge-map.md の <div id="kp-map"></div> に、graph.json のページの前提関係を描く。
 * Cytoscape.js と dagre（同梱）は地図のあるページでだけ読み込む。
 *
 * - 既定は分野ごとの表示（?field=<分野>）。その分野のページに加え、ほかの分野の直接の前提と次のページを破線の枠で出す
 * - ?focus=<id>：そのページの祖先（前提をすべて）と子孫（次に読む）だけを描く。子孫が多いときは深さを絞って始める
 *   （?depth=<1〜3>、0 はすべて）。related は配置に使わず、配置の後で選んだページのすぐ下（か上）の空いた所に「関連」の
 *   囲みとして足す。全体が収まらないときは、選んだページと関連の囲みが入るように寄せる（#59）
 * - ?view=all：分野を頂点にした全体の図。辺の太さは分野をまたぐ前提の本数。分野を押すとその分野の表示になる
 * - 枠の色はレベル（AtCoder の色）。理解したページ（ページのレベルの「理解した」）を塗り、前提をすべて理解した
 *   未読のページ（次の候補）を光らせる。「+青」は上位の帯の節を持つページ
 * - 点の説明は地図の中に重ねて出す（#59。点が地図の下半分なら上に、上半分なら下に）。点を押す（タップ・クリック）か
 *   長押しすると説明を固定し、×・Esc・地図の空いた所を押すと閉じる。マウスを乗せると説明を仮に出す（固定した説明は
 *   替えない）。そのページへは、説明の「ページを開く」か、点のダブルクリック（ダブルタップ）で移る
 * - 「ページ」欄：題名・短い題名・別名（それぞれのかっこの中と外も）・id を、filter.js の照合の規則（window.KPMatch：
 *   NFKC・大文字と小文字・空白・カタカナとひらがなの違いを問わない）で比べ、完全一致 → 前方一致 → 部分一致の順に選ぶ。
 *   同じ段では、当たった名前が短い → frequency（A・B・C）→ レベルの低い → ナビゲーションの順。どれにも当たらなければ
 *   言い換え（gcd ⇔ 最大公約数 など）でも探す。ほかの候補は上の行にボタンで出す
 * - 色は Material の CSS 変数から取り、ライトとダークの切り替えに追従する
 */
(function () {
  "use strict";

  var SRC = document.currentScript ? document.currentScript.src : location.href;
  var ASSETS = new URL("../", SRC); // …/assets/
  var ROOT = new URL("../../", SRC); // サイトのルート（graph.json の url はここからの相対）
  var LIBS = ["vendor/cytoscape-3.34.3/cytoscape.min.js", "vendor/cytoscape-dagre-4.0.1/cytoscape-dagre.min.js"];
  var LEVELS = ["基礎", "水", "青", "黄", "発展"];
  var LV_CLASS = { 基礎: "kiso", 水: "mizu", 青: "ao", 黄: "ki", 発展: "hatten" };
  var DEFAULT_FIELD = "basics";
  var MAX_DESCENDANTS = 80; // 焦点の表示で子孫がこれより多いときは、深さを絞って始める
  var FONT_SIZE = 13;
  var FIELD_FONT_SIZE = 15; // 全体の図の分野の点
  var LINE_HEIGHT = 1.25;
  var PAD_X = 10;
  var PAD_Y = 6;
  var MAX_LABEL_W = 168;
  var READABLE_ZOOM = 0.8; // 全体を収めると文字がこれより小さくなるときは、この倍率で一部を見せる（指でずらして読む）
  var MIN_FOCUS_ZOOM = 0.45; // 焦点の表示で、選んだページと関連の囲みを入れるために下げてよい倍率の下限
  var REL_GAP = 10; // 関連の囲みの中の点の間
  var REL_PAD = 10; // 関連の囲みの枠と点の間（スタイルの padding と同じ）
  var REL_LABEL = 22; // 関連の囲みの上の「関連」の文字の分
  var REL_MARGIN = 36; // 関連の囲みとほかの点の間
  var FREQ_RANK = { A: 0, B: 1, C: 2 };
  var LAYOUT = { name: "dagre", rankDir: "LR", nodeSep: 14, rankSep: 56, edgeSep: 8, fit: false, animate: false };
  var LAYOUT_FIELDS = { name: "dagre", rankDir: "TB", nodeSep: 30, rankSep: 60, fit: false, animate: false };

  var current = null; // このページの地図

  // ---------------------------------------------------------------- 読み込み

  var scripts = Object.create(null);

  function loadScript(rel) {
    var src = new URL(rel, ASSETS).href;
    if (!scripts[src]) {
      scripts[src] = new Promise(function (resolve, reject) {
        var s = document.createElement("script");
        s.src = src;
        s.onload = function () { resolve(); };
        s.onerror = function () {
          delete scripts[src];
          reject(new Error("読み込めない：" + rel));
        };
        document.head.appendChild(s);
      });
    }
    return scripts[src];
  }

  function loadLibs() {
    return (window.cytoscape ? Promise.resolve() : loadScript(LIBS[0]))
      .then(function () { return window.cytoscapeDagre ? null : loadScript(LIBS[1]); })
      .then(function () {
        var has = false;
        try { has = !!window.cytoscape("layout", "dagre"); } catch (e) { has = false; }
        if (!has) window.cytoscape.use(window.cytoscapeDagre); // window.cytoscape があれば dagre は読み込み時に自分で登録する
      });
  }

  function loadGraph() {
    if (window.KPProgress && window.KPProgress.loadGraph) return window.KPProgress.loadGraph();
    return fetch(new URL("data/graph.json", ASSETS)).then(function (r) {
      if (!r.ok) throw new Error("graph.json を読めない（" + r.status + "）");
      return r.json();
    });
  }

  // ---------------------------------------------------------------- データ

  function indexGraph(g) {
    var pages = g.pages || [];
    var byId = new Map();
    pages.forEach(function (p) { byId.set(p.id, p); });
    var children = new Map();
    pages.forEach(function (p) {
      (p.prerequisites || []).forEach(function (q) {
        if (!byId.has(q)) return;
        if (!children.has(q)) children.set(q, []);
        children.get(q).push(p.id);
      });
    });
    var fields = (g.fields || []).slice().sort(function (a, b) { return a.order - b.order; });
    var fieldTitle = new Map(fields.map(function (f) { return [f.id, f.title]; }));
    var hasPages = new Set(pages.map(function (p) { return p.field; }));
    return { pages: pages, byId: byId, children: children, fields: fields, fieldTitle: fieldTitle, hasPages: hasPages };
  }

  // ---------------------------------------------------------------- 名前で探す（#59）

  // 照合の規則は filter.js の window.KPMatch（#60 の絞り込みと同じ）。読めなかったときだけ、最低限の規則で代える
  function matcher() {
    if (window.KPMatch) return window.KPMatch;
    return {
      norm: function (s) { return String(s == null ? "" : s).normalize("NFKC").toLowerCase().replace(/[\s\-_・]+/g, ""); },
      synonyms: function () { return []; },
    };
  }

  var PAREN = /[（(]([^（）()]*)[）)]/g;

  // ページの名前（正規化したもの）：題名・短い題名・別名と、それぞれのかっこの中と外（「BIT（Fenwick Tree）」なら
  // 「BIT」と「Fenwick Tree」も）、id
  function pageNames(p, norm) {
    var out = [];
    [p.title, p.nav_title].concat(p.aliases || []).forEach(function (t) {
      if (!t) return;
      out.push(t);
      var inner = [];
      var outer = t.replace(PAREN, function (_m, x) { inner.push(x); return ""; });
      if (inner.length) out = out.concat([outer], inner);
    });
    out.push(p.id);
    var seen = new Set();
    return out.map(norm).filter(function (n) {
      if (!n || seen.has(n)) return false;
      seen.add(n);
      return true;
    });
  }

  function compareKeys(a, b) {
    for (var i = 0; i < a.length; i++) if (a[i] !== b[i]) return a[i] - b[i];
    return 0;
  }

  // 語に合うページを、よく合う順に並べる。完全一致（0）→ 前方一致（1）→ 部分一致（2）の段で比べ、同じ段では
  // 当たった名前が短い → frequency → レベルの低い → ナビゲーションの順（graph.json の pages の順）。
  // 語そのものに合うページがなければ、言い換え（gcd ⇔ 最大公約数 など）でも探す。言い換えには元の語を渡す
  // （送り仮名を落とすかを、カタカナをひらがなにする前の形で決めるため）
  function findPages(G, query) {
    var M = matcher();
    if (!G.names) G.names = new Map(G.pages.map(function (p) { return [p.id, pageNames(p, M.norm)]; }));
    var q = M.norm(query);
    if (!q) return [];
    var tries = [[q], M.synonyms(query).map(function (s) { return s.n; })];
    for (var t = 0; t < tries.length; t++) {
      var vs = tries[t];
      var found = [];
      G.pages.forEach(function (p, i) {
        var best = null;
        G.names.get(p.id).forEach(function (n) {
          vs.forEach(function (v) {
            var at = n.indexOf(v);
            if (at < 0) return;
            var key = [n === v ? 0 : at === 0 ? 1 : 2, n.length, p.frequency in FREQ_RANK ? FREQ_RANK[p.frequency] : 3,
              LEVELS.indexOf(p.level) >= 0 ? LEVELS.indexOf(p.level) : LEVELS.length, i];
            if (!best || compareKeys(key, best) < 0) best = key;
          });
        });
        if (best) found.push({ p: p, key: best });
      });
      if (found.length) {
        return found.sort(function (a, b) { return compareKeys(a.key, b.key); }).map(function (x) { return x.p; });
      }
    }
    return [];
  }

  function progressState() {
    try { return window.KPProgress ? window.KPProgress.load() : null; } catch (e) { return null; }
  }

  function isUnderstood(st, p) {
    return !!(st && p.level && st.understood[p.id] && st.understood[p.id][p.level] === true);
  }

  // 次の候補：レベルを持つ未読のページで、レベルを持つ前提をすべて理解した
  function isCandidate(st, p, G) {
    if (!p.level || isUnderstood(st, p)) return false;
    return (p.prerequisites || []).every(function (q) {
      var qp = G.byId.get(q);
      return !qp || !qp.level || isUnderstood(st, qp);
    });
  }

  function upperLevels(p) {
    var r = LEVELS.indexOf(p.level);
    if (r < 0) return [];
    var s = new Set();
    (p.sections || []).forEach(function (sec) { if (LEVELS.indexOf(sec.level) > r) s.add(sec.level); });
    return LEVELS.filter(function (l) { return s.has(l); });
  }

  // 祖先（前提をたどったすべて）と、深さつきの子孫
  function relatives(G, id, depth) {
    var anc = new Set();
    var stack = [id];
    while (stack.length) {
      var x = stack.pop();
      (G.byId.get(x).prerequisites || []).forEach(function (q) {
        if (G.byId.has(q) && q !== id && !anc.has(q)) {
          anc.add(q);
          stack.push(q);
        }
      });
    }
    var desc = new Map();
    var frontier = [id];
    var d = 0;
    while (frontier.length && (!depth || d < depth)) {
      d++;
      var next = [];
      frontier.forEach(function (x) {
        (G.children.get(x) || []).forEach(function (c) {
          if (c !== id && !desc.has(c)) {
            desc.set(c, d);
            next.push(c);
          }
        });
      });
      frontier = next;
    }
    return { anc: anc, desc: desc };
  }

  // 子孫が多すぎないように始めの深さを決める（0 はすべて）
  function autoDepth(G, id) {
    var all = relatives(G, id, 0).desc;
    if (all.size <= MAX_DESCENDANTS) return 0;
    var best = 1;
    for (var d = 2; d <= 3; d++) {
      var c = 0;
      all.forEach(function (v) { if (v <= d) c++; });
      if (c <= MAX_DESCENDANTS) best = d;
    }
    return best;
  }

  // ---------------------------------------------------------------- 文字の大きさと色

  var ctx2d = null;
  var sizeCache = new Map();

  function textWidth(text, font) {
    if (!ctx2d) ctx2d = document.createElement("canvas").getContext("2d");
    ctx2d.font = font;
    return ctx2d.measureText(text).width;
  }

  // 日本語は単語の区切りがないので、英数字の並びは1語、それ以外は1文字ずつで折り返す
  function wrapLine(text, font, maxW) {
    var tokens = text.match(/[A-Za-z0-9_.+#'-]+|\s+|[^\sA-Za-z0-9_.+#'-]/g) || [text];
    var lines = [];
    var cur = "";
    tokens.forEach(function (tok) {
      if (!cur && /^\s+$/.test(tok)) return;
      if (cur && textWidth(cur + tok, font) > maxW) {
        lines.push(cur.replace(/\s+$/, ""));
        cur = /^\s+$/.test(tok) ? "" : tok;
      } else {
        cur += tok;
      }
      while (cur.length > 1 && textWidth(cur, font) > maxW) {
        var k = cur.length - 1;
        while (k > 1 && textWidth(cur.slice(0, k), font) > maxW) k--;
        lines.push(cur.slice(0, k));
        cur = cur.slice(k);
      }
    });
    if (cur.replace(/\s+$/, "")) lines.push(cur.replace(/\s+$/, ""));
    return lines.length ? lines : [text];
  }

  // 折り返したラベルと、それが収まる点の幅・高さ
  function labelBox(text, family, size) {
    var font = size + "px " + family;
    var key = font + "\u0000" + text;
    var hit = sizeCache.get(key);
    if (hit) return hit;
    var maxW = MAX_LABEL_W * size / FONT_SIZE;
    var lines = [];
    text.split("\n").forEach(function (t) { lines = lines.concat(wrapLine(t, font, maxW)); });
    var w = 0;
    lines.forEach(function (l) { w = Math.max(w, textWidth(l, font)); });
    var box = {
      label: lines.join("\n"),
      w: Math.ceil(w) + 2 * PAD_X,
      h: Math.ceil(lines.length * size * LINE_HEIGHT) + 2 * PAD_Y,
    };
    sizeCache.set(key, box);
    return box;
  }

  function parseColor(s) {
    var m = /rgba?\(([^)]+)\)/.exec(s || "");
    if (!m) return [0, 0, 0, 1];
    var p = m[1].split(/[\s,/]+/).filter(Boolean).map(Number);
    return [p[0], p[1], p[2], p.length > 3 ? p[3] : 1];
  }

  // CSS の色（変数を含む）を、背景に重ねた不透明な rgb() にする。Cytoscape.js は 8 桁の16進数と透明度を扱えない
  function cssColor(root, expr) {
    var probe = document.createElement("span");
    probe.style.display = "none";
    probe.style.color = expr;
    root.appendChild(probe);
    var c = getComputedStyle(probe).color;
    probe.remove();
    return parseColor(c);
  }

  function over(c, bg) {
    var a = c[3];
    return "rgb(" + [0, 1, 2].map(function (i) { return Math.round(c[i] * a + bg[i] * (1 - a)); }).join(",") + ")";
  }

  function palette(root) {
    var bg = cssColor(root, "var(--md-default-bg-color)");
    bg[3] = 1;
    function v(name) { return over(cssColor(root, "var(" + name + ")"), bg); }
    var P = {
      bg: over(bg, bg),
      fg: v("--md-default-fg-color"),
      fgLight: v("--md-default-fg-color--light"),
      fgLighter: v("--md-default-fg-color--lighter"),
      accent: v("--md-accent-fg-color"),
      primary: v("--md-primary-fg-color"),
      lv: {},
      lvFg: {},
      font: getComputedStyle(root).fontFamily || "sans-serif",
    };
    LEVELS.forEach(function (l) {
      P.lv[l] = v("--kp-lv-" + LV_CLASS[l]);
      P.lvFg[l] = v("--kp-lv-" + LV_CLASS[l] + "-fg");
    });
    return P;
  }

  function buildStyle(P) {
    var s = [
      {
        selector: "node",
        style: {
          shape: "round-rectangle",
          width: "data(w)",
          height: "data(h)",
          label: "data(label)",
          "text-wrap": "wrap",
          "text-max-width": "2000px",
          "text-valign": "center",
          "text-halign": "center",
          "font-size": FONT_SIZE,
          "line-height": LINE_HEIGHT,
          "font-family": P.font,
          color: P.fg,
          "background-color": P.bg,
          "border-width": 2,
          "border-color": P.fgLighter,
        },
      },
      { selector: "node.ext", style: { "border-style": "dashed", color: P.fgLight } },
      { selector: "node.rel", style: { "border-style": "dotted", color: P.fgLight } },
      {
        selector: "node.relbox",
        style: {
          shape: "round-rectangle",
          label: "data(label)",
          "text-valign": "top",
          "text-halign": "center",
          "text-margin-x": "data(lx)", // 「関連」の文字は囲みの左の端に寄せる（中央は選んだページからの破線が通る）
          "font-size": 11,
          color: P.fgLight,
          "background-color": P.fgLighter,
          "background-opacity": 0.06,
          "border-width": 1,
          "border-style": "dashed",
          "border-color": P.fgLighter,
          padding: 10,
        },
      },
      {
        selector: "node.field",
        style: { "border-color": P.primary, "border-width": 2, "font-size": FIELD_FONT_SIZE },
      },
      { selector: "node.next", style: { "border-color": P.primary, "border-style": "dashed", color: P.fgLight } },
      { selector: "node.src", style: { "overlay-color": P.accent, "overlay-opacity": 0.25, "overlay-padding": 4 } },
      {
        selector: "node.cand",
        style: {
          "border-width": 3,
          "underlay-color": P.accent,
          "underlay-padding": 5,
          "underlay-opacity": 0.45,
          "underlay-shape": "round-rectangle",
        },
      },
      { selector: "node.focus", style: { "border-width": 4, "font-weight": "bold" } },
      { selector: "node.hover", style: { "overlay-color": P.fg, "overlay-opacity": 0.08, "overlay-padding": 3 } },
      {
        selector: "edge",
        style: {
          width: 1.5,
          "curve-style": "bezier",
          "line-color": P.fgLighter,
          "target-arrow-color": P.fgLighter,
          "target-arrow-shape": "triangle",
          "arrow-scale": 0.9,
        },
      },
      { selector: "edge.agg", style: { width: "data(wpx)" } },
      { selector: "edge.weak", style: { opacity: 0.5 } },
      { selector: "edge.rel", style: { "line-style": "dashed", "target-arrow-shape": "none", width: 1.2, opacity: 0.8 } },
      { selector: "edge.hl", style: { width: 3, "line-color": P.accent, "target-arrow-color": P.accent, "z-index": 10 } },
    ];
    LEVELS.forEach(function (l) {
      var c = LV_CLASS[l];
      s.push({ selector: "node.lv-" + c, style: { "border-color": P.lv[l] } });
      s.push({ selector: "node.lv-" + c + ".done", style: { "background-color": P.lv[l], color: P.lvFg[l] } });
    });
    return s;
  }

  // ---------------------------------------------------------------- 画面の部品

  function html(tag, cls, text) {
    var e = document.createElement(tag);
    if (cls) e.className = cls;
    if (text != null) e.textContent = text;
    return e;
  }

  function button(text) {
    var b = html("button", null, text);
    b.type = "button";
    return b;
  }

  function buildUI(root) {
    root.textContent = "";
    var toolbar = html("div", "kp-map__toolbar");
    var seg = html("div", "kp-map__seg");
    seg.setAttribute("role", "group");
    seg.setAttribute("aria-label", "表示のしかた");
    var bField = button("分野ごと");
    var bAll = button("全体（分野）");
    seg.append(bField, bAll);
    var fieldLabel = html("label", null, "分野");
    var fieldSel = document.createElement("select");
    fieldLabel.appendChild(fieldSel);
    var findLabel = html("label", null, "ページ");
    var find = document.createElement("input");
    find.type = "search";
    find.placeholder = "名前・略称で探して中心に";
    find.setAttribute("autocomplete", "off");
    find.setAttribute("enterkeyhint", "search");
    find.setAttribute("list", "kp-map-pages");
    find.setAttribute("aria-label", "ページを名前で探して、その前後を表示する");
    findLabel.appendChild(find);
    var list = document.createElement("datalist");
    list.id = "kp-map-pages";
    var depthLabel = html("label", null, "次に読むの深さ");
    var depthSel = document.createElement("select");
    [["1", "1"], ["2", "2"], ["3", "3"], ["0", "すべて"]].forEach(function (o) { depthSel.add(new Option(o[1], o[0])); });
    depthLabel.appendChild(depthSel);
    depthLabel.hidden = true;
    var bFit = button("全体を収める");
    toolbar.append(seg, fieldLabel, findLabel, list, depthLabel, bFit);

    var status = html("p", "kp-map__status");
    status.setAttribute("aria-live", "polite");
    // 地図と、その上に重ねる点の説明（#59）。説明は地図の中に出すので、狭い画面でも点を押した場所から離れない
    var stage = html("div", "kp-map__stage");
    var canvas = html("div", "kp-map__canvas");
    canvas.setAttribute("role", "img");
    canvas.setAttribute("aria-label", "ページの前提関係の図。同じ内容はレベル別の一覧と各ページの「前提」「次に読む」にもある");
    var info = html("div", "kp-map__info");
    info.hidden = true;
    info.setAttribute("role", "region");
    info.setAttribute("aria-label", "点の説明");
    info.setAttribute("aria-live", "polite");
    var infoClose = button("×");
    infoClose.className = "kp-map__close";
    infoClose.setAttribute("aria-label", "説明を閉じる");
    infoClose.title = "説明を閉じる（Esc）";
    var infoBody = html("div", "kp-map__info-body");
    info.append(infoClose, infoBody);
    stage.append(canvas, info);

    var legend = html("ul", "kp-map__legend");
    function item(sw, text) {
      var li = html("li");
      if (sw) {
        var s = html("span", "kp-sw " + sw);
        s.setAttribute("aria-hidden", "true");
        li.appendChild(s);
      }
      li.appendChild(document.createTextNode(text));
      legend.appendChild(li);
    }
    LEVELS.forEach(function (l) { item("kp-lv-" + LV_CLASS[l], l); });
    item("kp-sw--fill kp-lv-mizu", "塗り：理解した");
    item("kp-sw--glow", "光る枠：次の候補（前提をすべて理解した）");
    item("kp-sw--ext", "破線の枠：ほかの分野のページ");
    item(null, "「+青」など：上位の帯の節がある");
    item("kp-sw--rel", "点線：関連（焦点の表示だけ。配置には使わない）");

    root.append(toolbar, status, stage, legend);
    return {
      bField: bField, bAll: bAll, fieldLabel: fieldLabel, fieldSel: fieldSel, find: find, list: list,
      depthLabel: depthLabel, depthSel: depthSel, bFit: bFit, status: status, canvas: canvas, info: info,
      infoClose: infoClose, infoBody: infoBody,
    };
  }

  // ---------------------------------------------------------------- 地図

  function createMap(root, ui, G) {
    var P = palette(root);
    var cy = window.cytoscape({
      container: ui.canvas,
      elements: [],
      style: buildStyle(P),
      minZoom: 0.08,
      maxZoom: 2.5,
      boxSelectionEnabled: false,
      autoungrabify: true, // 点は動かせない（指で触ると地図全体が動く）
      autounselectify: true,
    });
    var state = { view: "field", field: null, focus: null, depth: 0 };
    var notice = "";
    var holdUntil = 0;
    var api = { root: root, cy: cy, state: state, timings: {} };

    function pageNode(p, extra) {
      var ups = upperLevels(p);
      var box = labelBox((p.nav_title || p.title) + (ups.length ? " +" + ups.join("") : ""), P.font, FONT_SIZE);
      var cls = ["page", p.level ? "lv-" + LV_CLASS[p.level] : "lv-none"].concat(extra || []);
      return { group: "nodes", data: { id: p.id, label: box.label, w: box.w, h: box.h }, classes: cls.join(" ") };
    }

    function edge(s, t, cls) {
      return { group: "edges", data: { id: s + "->" + t + (cls ? ":" + cls : ""), source: s, target: t }, classes: cls || "" };
    }

    // 分野のページ＋ほかの分野の直接の前提（1ページずつ）＋この分野の先にある分野（分野ごとに1つの「→」の点にまとめる）。
    // 「→」の点は配置に使わず、配置の後で右に並べる。辺は引かず、マウスを乗せる・長押しすると元のページを光らせる
    function fieldElements(field) {
      var core = new Set();
      G.pages.forEach(function (p) { if (p.field === field) core.add(p.id); });
      var ext = new Set();
      var next = new Map(); // 分野 → その分野の、core を直接の前提にするページ
      core.forEach(function (id) {
        (G.byId.get(id).prerequisites || []).forEach(function (q) { if (G.byId.has(q) && !core.has(q)) ext.add(q); });
        (G.children.get(id) || []).forEach(function (c) {
          if (core.has(c)) return;
          var f = G.byId.get(c).field;
          if (!next.has(f)) next.set(f, new Set());
          next.get(f).add(c);
        });
      });
      var els = [];
      core.forEach(function (id) { els.push(pageNode(G.byId.get(id))); });
      ext.forEach(function (id) { els.push(pageNode(G.byId.get(id), ["ext"])); });
      next.forEach(function (pages, f) {
        var box = labelBox("→ " + (G.fieldTitle.get(f) || f) + "\n" + pages.size + " ページ", P.font, FONT_SIZE);
        var sources = [];
        core.forEach(function (id) {
          if ((G.children.get(id) || []).some(function (c) { return pages.has(c); })) sources.push(id);
        });
        els.push({
          group: "nodes",
          data: { id: "next:" + f, field: f, label: box.label, w: box.w, h: box.h, pages: Array.from(pages), sources: sources },
          classes: "next",
        });
      });
      core.forEach(function (id) {
        (G.byId.get(id).prerequisites || []).forEach(function (q) { if (core.has(q) || ext.has(q)) els.push(edge(q, id)); });
      });
      return { elements: els, core: core.size, ext: ext.size, next: next.size };
    }

    function focusElements(id, depth) {
      var R = relatives(G, id, depth);
      var ids = new Set([id]);
      R.anc.forEach(function (x) { ids.add(x); });
      R.desc.forEach(function (_d, x) { ids.add(x); });
      var els = [];
      ids.forEach(function (x) { els.push(pageNode(G.byId.get(x), x === id ? ["focus"] : [])); });
      ids.forEach(function (x) {
        (G.byId.get(x).prerequisites || []).forEach(function (q) { if (ids.has(q)) els.push(edge(q, x)); });
      });
      return { elements: els, anc: R.anc.size, desc: R.desc.size, total: relatives(G, id, 0).desc.size };
    }

    function overviewElements() {
      var st = progressState();
      var count = new Map(G.fields.map(function (f) { return [f.id, { total: 0, leveled: 0, done: 0 }]; }));
      G.pages.forEach(function (p) {
        var c = count.get(p.field);
        if (!c) return;
        c.total++;
        if (p.level) {
          c.leveled++;
          if (isUnderstood(st, p)) c.done++;
        }
      });
      var els = G.fields.filter(function (f) { return G.hasPages.has(f.id); }).map(function (f) {
        var c = count.get(f.id);
        var box = labelBox(f.title + "\n" + (c.leveled ? "理解 " + c.done + " / " + c.leveled : c.total + " ページ"), P.font, FIELD_FONT_SIZE);
        return { group: "nodes", data: { id: "field:" + f.id, field: f.id, label: box.label, w: box.w, h: box.h }, classes: "field" };
      });
      var agg = new Map();
      G.pages.forEach(function (p) {
        (p.prerequisites || []).forEach(function (q) {
          var qp = G.byId.get(q);
          if (!qp || qp.field === p.field) return;
          var k = qp.field + ">" + p.field;
          agg.set(k, (agg.get(k) || 0) + 1);
        });
      });
      var max = 1;
      agg.forEach(function (n) { max = Math.max(max, n); });
      agg.forEach(function (n, k) {
        var ab = k.split(">");
        els.push({
          group: "edges",
          data: { id: "agg:" + k, source: "field:" + ab[0], target: "field:" + ab[1], n: n, wpx: 1 + 5 * Math.sqrt(n / max) },
          classes: n === 1 ? "agg weak" : "agg",
        });
      });
      return { elements: els };
    }

    // 関連の囲みの中の並び：点を列ごとに上から詰める。列の数は 1〜3 のうち、囲みが地図に最も大きく入るもの
    // （狭い画面では縦長、広い画面では横に並ぶ）。返すのは囲みの幅・高さと、囲みの左上からの各点の中心
    function relGrid(nodes) {
      var best = null;
      for (var cols = 1; cols <= Math.min(3, nodes.length); cols++) {
        var rows = Math.ceil(nodes.length / cols);
        var colW = [];
        var colH = [];
        var pos = nodes.map(function (nd, k) {
          var c = Math.floor(k / rows);
          var y = colH[c] || 0;
          colW[c] = Math.max(colW[c] || 0, nd.data.w);
          colH[c] = y + nd.data.h + REL_GAP;
          return { c: c, y: y + nd.data.h / 2 };
        });
        var xs = [];
        var x = REL_PAD;
        colW.forEach(function (w, c) { xs[c] = x + w / 2; x += w + REL_GAP * 2; });
        var w = x - REL_GAP * 2 + REL_PAD;
        var h = REL_LABEL + 2 * REL_PAD + Math.max.apply(null, colH) - REL_GAP;
        var z = Math.min((cy.width() - 48) / w, (cy.height() - 48) / h);
        if (!best || z > best.z + 1e-9) {
          best = { z: z, w: w, h: h, at: pos.map(function (q) { return { x: xs[q.c], y: REL_LABEL + REL_PAD + q.y }; }) };
        }
      }
      return best;
    }

    // related は配置の後で足す（配置には使わない。T2）。図にまだない関連のページは「関連」の囲みに入れ、選んだページの
    // すぐ下（か上）の空いた所に置く。焦点の表示では、選んだページの段（列）にはほかの点がない（祖先は左、子孫は右の段）
    // ので、多くは選んだページの真下に入る。ほかの点と重なれば、重なった点の外までずらし、上下で近い方を選ぶ
    function addRelated(id) {
      var p = G.byId.get(id);
      var rel = (p.related || []).filter(function (r, k, arr) { return r !== id && G.byId.has(r) && arr.indexOf(r) === k; });
      if (!rel.length) return;
      var f = cy.getElementById(id);
      var fb = f.boundingBox();
      var missing = rel.filter(function (r) { return cy.getElementById(r).empty(); });
      var nodes = missing.map(function (r) { return pageNode(G.byId.get(r), ["rel"]); });
      var adds = [];
      if (nodes.length) {
        var grid = relGrid(nodes);
        var cx = (fb.x1 + fb.x2) / 2;
        var x1 = cx - grid.w / 2;
        var x2 = cx + grid.w / 2;
        var others = cy.nodes().not(f).map(function (n) { return n.boundingBox(); });
        var half = REL_MARGIN / 2;
        var clash = function (top) {
          return others.filter(function (b) {
            return b.x2 > x1 - half && b.x1 < x2 + half && b.y2 > top - half && b.y1 < top + grid.h + half;
          });
        };
        var below = fb.y2 + REL_MARGIN;
        var above = fb.y1 - REL_MARGIN - grid.h;
        for (var k = 0, c; k < 500 && (c = clash(below)).length; k++) {
          below = Math.max.apply(null, c.map(function (b) { return b.y2; })) + REL_MARGIN;
        }
        for (k = 0; k < 500 && (c = clash(above)).length; k++) {
          above = Math.min.apply(null, c.map(function (b) { return b.y1; })) - REL_MARGIN - grid.h;
        }
        var top = below - fb.y2 <= fb.y1 - (above + grid.h) ? below : above;
        adds.push({ group: "nodes", data: { id: "__related", label: "関連", w: 1, h: 1, lx: REL_PAD + 12 - grid.w / 2 }, classes: "relbox" });
        nodes.forEach(function (nd, i) {
          nd.data.parent = "__related";
          nd.position = { x: x1 + grid.at[i].x, y: top + grid.at[i].y };
          adds.push(nd);
        });
      }
      rel.forEach(function (r) { adds.push(edge(id, r, "rel")); });
      cy.add(adds);
    }

    // 「→」の点を、元のページの高さの平均の順に、図の右に1列に並べる
    function placeNext() {
      var nexts = cy.nodes(".next");
      if (nexts.empty()) return;
      var bb = cy.elements().not(nexts).boundingBox();
      var items = nexts.map(function (n) {
        var ys = n.data("sources").map(function (id) { return cy.getElementById(id).position("y"); });
        return { n: n, y: ys.reduce(function (a, b) { return a + b; }, 0) / Math.max(1, ys.length) };
      }).sort(function (a, b) { return a.y - b.y; });
      var total = items.reduce(function (t, it) { return t + it.n.data("h") + 12; }, -12);
      var y = (bb.y1 + bb.y2) / 2 - total / 2;
      var x = bb.x2 + 70;
      items.forEach(function (it) {
        it.n.position({ x: x + it.n.data("w") / 2, y: y + it.n.data("h") / 2 });
        y += it.n.data("h") + 12;
      });
    }

    function colorize() {
      var st = progressState();
      var c = { done: 0, cand: 0 };
      cy.batch(function () {
        cy.nodes(".page").forEach(function (n) {
          var p = G.byId.get(n.id());
          var done = isUnderstood(st, p);
          var cand = isCandidate(st, p, G);
          n.toggleClass("done", done);
          n.toggleClass("cand", cand);
          if (!n.hasClass("ext") && !n.hasClass("rel")) {
            if (done) c.done++;
            if (cand) c.cand++;
          }
        });
      });
      return c;
    }

    function fit() {
      var eles = cy.elements();
      if (eles.empty()) return;
      cy.resize(); // 入れ物の大きさが変わっていても合わせる
      cy.fit(eles, 24);
      if (state.view === "all" || cy.zoom() >= READABLE_ZOOM) return; // 全体の図は点が少ないので必ず全部を収める
      cy.zoom(READABLE_ZOOM);
      var bb = eles.boundingBox();
      var h = cy.height();
      if (state.view === "focus") {
        // 選んだページと関連の囲みが両方入るように寄せる。読める倍率で入らなければ、MIN_FOCUS_ZOOM まで倍率を下げる
        var target = cy.getElementById(state.focus).union(cy.getElementById("__related"));
        var tb = target.boundingBox();
        var zf = Math.min(READABLE_ZOOM, (cy.width() - 48) / tb.w, (h - 48) / tb.h);
        cy.zoom(Math.max(MIN_FOCUS_ZOOM, zf));
        cy.center(target);
      } else {
        // 左（前提の側）から読めるように、左端をそろえ、縦は収まれば中央、収まらなければ上をそろえる
        var z = cy.zoom();
        var py = bb.h * z <= h - 48 ? (h - bb.h * z) / 2 - bb.y1 * z : 24 - bb.y1 * z;
        cy.pan({ x: 24 - bb.x1 * z, y: py });
      }
    }

    function setStatus(parts, withClear) {
      ui.status.textContent = (notice ? notice + " " : "") + parts;
      if (withClear) {
        var b = button("解除");
        b.addEventListener("click", function () { setState({ view: "field", field: G.byId.get(state.focus).field }); });
        ui.status.appendChild(b);
      }
    }

    var lastBuilt = null;

    function showStatus(built, c) {
      if (state.view === "all") {
        setStatus("分野どうしの前提を、辺の太さ（前提の本数）で表す。分野を押すとその分野の表示になる。");
      } else if (state.view === "focus") {
        var p = G.byId.get(state.focus);
        var shown = built.desc < built.total ? "（全 " + built.total + " ページのうち、深さ " + state.depth + " まで）" : "";
        setStatus((p.nav_title || p.title) + "：前提 " + built.anc + " ページ・次に読む " + built.desc + " ページ" + shown +
          "。理解した " + c.done + "・次の候補 " + c.cand + "。", true);
      } else {
        setStatus((G.fieldTitle.get(state.field) || state.field) + "：" + built.core + " ページ（理解した " + c.done +
          "・次の候補 " + c.cand + "）。破線の枠はほかの分野にある前提、「→」はこの分野の先にある分野（押すとその分野へ）。");
      }
    }

    function render() {
      var t0 = performance.now();
      var built;
      if (state.view === "all") built = overviewElements();
      else if (state.view === "focus") built = focusElements(state.focus, state.depth);
      else built = fieldElements(state.field);
      var t1 = performance.now();
      cy.batch(function () {
        cy.elements().remove();
        cy.add(built.elements);
      });
      var t2 = performance.now();
      cy.elements().not(".next").layout(state.view === "all" ? LAYOUT_FIELDS : LAYOUT).run();
      placeNext();
      var t3 = performance.now();
      if (state.view === "focus") addRelated(state.focus);
      var c = colorize();
      fit();
      var t4 = performance.now();

      lastBuilt = built;
      showStatus(built, c);
      notice = "";
      syncToolbar();
      writeQuery();
      api.timings = {
        build: t1 - t0, add: t2 - t1, layout: t3 - t2, after: t4 - t3, total: t4 - t0,
        nodes: cy.nodes().length, edges: cy.edges().length,
      };
      requestAnimationFrame(function () {
        api.timings.firstFrame = performance.now() - t0; // 描き始めてから最初の画面まで
        api.timings.shownAt = performance.now(); // ページを開いてから地図が出るまで（instant navigation では最初のページから）
      });
    }

    function setState(patch) {
      Object.keys(patch).forEach(function (k) { state[k] = patch[k]; });
      if (state.view === "focus" && patch.focus && !("depth" in patch)) state.depth = autoDepth(G, state.focus);
      closeInfo();
      render();
    }

    function syncToolbar() {
      ui.bField.setAttribute("aria-pressed", String(state.view !== "all"));
      ui.bAll.setAttribute("aria-pressed", String(state.view === "all"));
      ui.fieldLabel.hidden = state.view !== "field";
      ui.fieldSel.value = state.field || "";
      ui.depthLabel.hidden = state.view !== "focus";
      ui.depthSel.value = String(state.depth || 0);
    }

    function writeQuery() {
      var q = new URLSearchParams();
      if (state.view === "focus") {
        q.set("focus", state.focus);
        if (state.depth) q.set("depth", String(state.depth));
      } else if (state.view === "all") {
        q.set("view", "all");
      } else if (state.field) {
        q.set("field", state.field);
      }
      var qs = q.toString();
      try {
        history.replaceState(history.state, "", location.pathname + (qs ? "?" + qs : "") + location.hash);
      } catch (e) { /* 書き換えられなくても表示は続ける */ }
    }

    function pageUrl(p) { return new URL(p.url, ROOT).href; }

    // instant navigation に任せるため、location を直接変えずにリンクを押す
    function navigate(url) {
      var a = document.createElement("a");
      a.href = url;
      a.hidden = true;
      document.body.appendChild(a);
      a.click();
      a.remove();
    }

    // ---- 点の説明（地図の中に重ねる。#59）
    // 固定（pinned）した説明は、×・Esc・地図の空いた所を押すまで残り、マウスを乗せたほかの点の説明に替わらない。
    // マウスを乗せただけの説明は仮のもので、点と説明の両方から離れると少し待って消える
    var pinned = false;
    var overInfo = false;
    var hideTimer = 0;

    function openInfo(fill, n, pin) {
      clearTimeout(hideTimer);
      ui.infoBody.textContent = "";
      fill(ui.infoBody);
      if (!pin) ui.infoBody.appendChild(html("p", "kp-map__hint", "点を押すと、この説明を固定する"));
      pinned = !!pin;
      ui.info.classList.toggle("kp-map__info--pinned", pinned);
      // 点が地図の下半分にあれば説明を上に、上半分にあれば下に重ねて、点を隠さない
      ui.info.classList.toggle("kp-map__info--top", !!n && n.renderedPosition("y") > cy.height() / 2);
      ui.info.hidden = false;
      if (pinned) reveal(ui.info);
    }

    function closeInfo() {
      clearTimeout(hideTimer);
      pinned = false;
      overInfo = false;
      ui.info.hidden = true;
      cy.nodes(".src").removeClass("src");
    }

    function hideSoon() {
      if (pinned) return;
      clearTimeout(hideTimer);
      hideTimer = setTimeout(function () { if (!pinned && !overInfo) closeInfo(); }, 400);
    }

    // 説明が画面の外（固定のヘッダーの下を含む）にあれば、見える所までページを送る（地図が画面から一部はみ出ているとき）
    function reveal(el) {
      var r = el.getBoundingClientRect();
      var header = document.querySelector(".md-header");
      var top = (header ? Math.max(0, header.getBoundingClientRect().bottom) : 0) + 8;
      var bottom = window.innerHeight - 8;
      var dy = r.bottom > bottom ? r.bottom - bottom : 0;
      if (r.top - dy < top) dy = r.top - top;
      if (dy) window.scrollBy({ top: dy, behavior: "smooth" });
    }

    function fillPage(box, p) {
      var head = html("p", "kp-map__info-head");
      var link = html("a", null, p.title);
      link.href = pageUrl(p);
      var strong = html("strong");
      strong.appendChild(link);
      head.appendChild(strong);
      if (p.level) head.append(" ", html("span", "kp-mini kp-lv-" + LV_CLASS[p.level], p.level));
      head.append(" " + (G.fieldTitle.get(p.field) || p.field));
      if (p.stage === "stub") head.append("（準備中）");
      box.appendChild(head);
      if (p.summary) box.appendChild(html("p", null, p.summary));
      var acts = html("p", "kp-map__acts");
      var open = html("a", "kp-map__open", "ページを開く");
      open.href = pageUrl(p);
      acts.appendChild(open);
      if (!(state.view === "focus" && state.focus === p.id)) {
        var center = button("この点を中心に表示");
        center.addEventListener("click", function () { setState({ view: "focus", focus: p.id }); });
        acts.appendChild(center);
      }
      box.appendChild(acts);
    }

    function showPage(n, pin) {
      var p = G.byId.get(n.id());
      openInfo(function (box) { fillPage(box, p); }, n, pin);
    }

    function hover(n, on) {
      n.toggleClass("hover", on);
      n.connectedEdges().not(".rel").toggleClass("hl", on);
    }

    // 点を押す（クリック・タップ）・長押しで説明を固定する。ダブルクリック（ダブルタップ）でそのページへ移る
    cy.on("tap", "node.page", function (e) {
      if (Date.now() < holdUntil) return; // 長押しの直後の tap は、長押しで出した説明をそのままにする
      showPage(e.target, true);
    });
    cy.on("dbltap", "node.page", function (e) { navigate(pageUrl(G.byId.get(e.target.id()))); });
    cy.on("taphold", "node.page", function (e) {
      holdUntil = Date.now() + 1000;
      showPage(e.target, true);
    });
    cy.on("tap", "node.field, node.next", function (e) {
      if (Date.now() < holdUntil) return;
      setState({ view: "field", field: e.target.data("field") });
    });
    cy.on("tap", function (e) { if (e.target === cy && pinned) closeInfo(); }); // 地図の空いた所を押すと閉じる

    function showNext(n, on, pin) {
      n.toggleClass("hover", on);
      if (pinned && !pin) return; // 固定した説明は替えない
      cy.nodes(".src").removeClass("src");
      if (!on) { hideSoon(); return; }
      cy.collection(n.data("sources").map(function (id) { return cy.getElementById(id); }).filter(function (x) { return x.nonempty(); }))
        .addClass("src");
      var titles = n.data("pages").map(function (id) { return G.byId.get(id).title; });
      var text = "→ " + (G.fieldTitle.get(n.data("field")) || n.data("field")) + "：" + titles.slice(0, 8).join("・") +
        (titles.length > 8 ? " ほか " + (titles.length - 8) + " ページ" : "") + "。光っているページが前提になる（押すとその分野の表示）";
      openInfo(function (box) { box.appendChild(html("p", null, text)); }, n, pin);
    }
    cy.on("mouseover", "node.next", function (e) { showNext(e.target, true, false); });
    cy.on("mouseout", "node.next", function (e) { showNext(e.target, false, false); });
    cy.on("taphold", "node.next", function (e) {
      holdUntil = Date.now() + 1000;
      showNext(e.target, true, true);
    });
    cy.on("mouseover", "node.page", function (e) {
      hover(e.target, true);
      if (!pinned) showPage(e.target, false);
    });
    cy.on("mouseover", "node.field", function (e) { hover(e.target, true); });
    cy.on("mouseout", "node.page, node.field", function (e) {
      hover(e.target, false);
      hideSoon();
    });
    cy.on("mouseover", "edge.agg", function (e) {
      if (pinned) return;
      var d = e.target.data();
      var text = (G.fieldTitle.get(d.source.slice(6)) || "") + " → " + (G.fieldTitle.get(d.target.slice(6)) || "") +
        "：分野をまたぐ前提 " + d.n + " 本";
      openInfo(function (box) { box.appendChild(html("p", null, text)); }, null, false);
    });
    cy.on("mouseout", "edge.agg", hideSoon);
    cy.on("pan zoom", function () { if (!pinned && !ui.info.hidden) closeInfo(); }); // 仮の説明は地図を動かすと消す

    // 点の上から地図の外へ一気に出ると、Cytoscape.js は点の mouseout を出さないので、地図から出たときにも仮の説明を消す
    ui.canvas.addEventListener("mouseleave", function () {
      cy.nodes(".hover").removeClass("hover");
      cy.edges(".hl").removeClass("hl");
      if (!pinned) cy.nodes(".src").removeClass("src");
      hideSoon();
    });
    ui.info.addEventListener("mouseenter", function () { overInfo = true; clearTimeout(hideTimer); });
    ui.info.addEventListener("mouseleave", function () { overInfo = false; hideSoon(); });
    ui.infoClose.addEventListener("click", closeInfo);
    function onKey(e) {
      if (e.key === "Escape" && !ui.info.hidden && root.isConnected) closeInfo();
    }
    document.addEventListener("keydown", onKey);

    // ツールバー：「ページ」欄の候補は題名と別名（別名は「→ 題名」を添える）。同じ文字の候補は最初の 1 つだけ
    G.fields.forEach(function (f) { if (G.hasPages.has(f.id)) ui.fieldSel.add(new Option(f.title, f.id)); });
    var listed = new Set();
    function addOption(value, label) {
      if (!value || listed.has(value)) return;
      listed.add(value);
      var o = document.createElement("option");
      o.value = value;
      if (label) o.label = label;
      ui.list.appendChild(o);
    }
    G.fields.forEach(function (f) {
      G.pages.filter(function (p) { return p.field === f.id; })
        .sort(function (a, b) { return a.order - b.order; })
        .forEach(function (p) { addOption(p.title, null); });
    });
    G.fields.forEach(function (f) {
      G.pages.filter(function (p) { return p.field === f.id; })
        .sort(function (a, b) { return a.order - b.order; })
        .forEach(function (p) { (p.aliases || []).forEach(function (a) { addOption(a, "→ " + p.title); }); });
    });
    ui.bField.addEventListener("click", function () {
      var f = state.field || (state.focus && G.byId.get(state.focus).field) || defaultField();
      setState({ view: "field", field: f });
    });
    ui.bAll.addEventListener("click", function () { setState({ view: "all" }); });
    ui.fieldSel.addEventListener("change", function () { setState({ view: "field", field: ui.fieldSel.value }); });
    ui.depthSel.addEventListener("change", function () { setState({ depth: Number(ui.depthSel.value) }); });
    // 「ページ」欄：いちばん合うページを中心にし、ほかの候補（5 件まで）を上の行にボタンで出す
    function showAlternatives(v, list) {
      if (!list.length) return;
      var span = html("span", "kp-map__alts");
      span.appendChild(document.createTextNode("「" + v + "」のほかの候補："));
      list.forEach(function (p) {
        var b = button(p.nav_title || p.title);
        b.addEventListener("click", function () { setState({ view: "focus", focus: p.id, field: p.field }); });
        span.appendChild(b);
      });
      ui.status.appendChild(span);
    }
    ui.find.addEventListener("change", function () {
      var v = ui.find.value.trim();
      var found = findPages(G, v);
      if (found.length) {
        ui.find.value = "";
        ui.find.blur(); // スマホではキーボードを閉じて地図を見せる
        setState({ view: "focus", focus: found[0].id, field: found[0].field });
        showAlternatives(v, found.slice(1, 6));
      } else if (v) {
        ui.status.textContent = "「" + v + "」に合うページがない。略称・英語名・名前の一部でも探せる。";
      }
    });
    ui.bFit.addEventListener("click", function () { cy.fit(cy.elements(), 24); });

    function defaultField() {
      if (G.hasPages.has(DEFAULT_FIELD)) return DEFAULT_FIELD;
      var f = G.fields.filter(function (x) { return G.hasPages.has(x.id); })[0];
      return f ? f.id : null;
    }

    function start(q) {
      if (q.focus && G.byId.has(q.focus)) {
        state.view = "focus";
        state.focus = q.focus;
        state.field = G.byId.get(q.focus).field;
        var d = q.depth == null ? NaN : Number(q.depth);
        state.depth = d >= 0 && d <= 3 && Math.floor(d) === d ? d : autoDepth(G, q.focus);
      } else if (q.view === "all") {
        state.view = "all";
        state.field = defaultField();
      } else {
        state.view = "field";
        state.field = q.field && G.hasPages.has(q.field) ? q.field : defaultField();
      }
      if (q.focus && !G.byId.has(q.focus)) notice = "ページ「" + q.focus + "」が見つからないので、分野ごとの表示にした。";
      render();
    }

    // 「理解した」の変更（このタブ・別のタブ）を反映する。配置はそのままにして色と数だけ直す（全体の図は数が点の中にあるので描き直す）
    function onProgress() {
      if (!root.isConnected || !lastBuilt) return;
      if (state.view === "all") render();
      else showStatus(lastBuilt, colorize());
    }
    document.addEventListener("kp:progress", onProgress);

    // ライトとダークの切り替えに追従する
    var observer = new MutationObserver(function () {
      P = palette(root);
      cy.style(buildStyle(P));
    });
    observer.observe(document.body, { attributes: true, attributeFilter: ["data-md-color-scheme", "data-md-color-primary", "data-md-color-accent"] });

    api.start = start;
    api.setState = setState;
    api.findPages = function (q) { return findPages(G, q).map(function (p) { return p.id; }); };
    api.destroy = function () {
      document.removeEventListener("kp:progress", onProgress);
      document.removeEventListener("keydown", onKey);
      clearTimeout(hideTimer);
      observer.disconnect();
      cy.destroy();
    };
    return api;
  }

  function parseQuery() {
    var q = new URLSearchParams(location.search);
    return { focus: q.get("focus"), field: q.get("field"), view: q.get("view"), depth: q.get("depth") };
  }

  function mount(root) {
    if (root.dataset.kpMounted) return;
    root.dataset.kpMounted = "1";
    var t0 = performance.now();
    var ui = buildUI(root);
    ui.status.textContent = "地図を読み込んでいる…";
    Promise.all([loadLibs(), loadGraph()])
      .then(function (res) {
        if (!root.isConnected) return;
        var t1 = performance.now();
        var G = indexGraph(res[1]);
        var map = createMap(root, ui, G);
        current = map;
        root.kpMap = map;
        map.start(parseQuery());
        map.timings.load = t1 - t0;
        map.timings.mount = performance.now() - t0;
      })
      .catch(function (e) {
        root.dataset.kpMounted = "";
        ui.status.textContent = "地図を表示できなかった（" + e.message + "）。同じ内容はレベル別の一覧で見られる。";
        console.error("kyopro-atlas: 知識マップを表示できなかった", e);
      });
  }

  function onDocument(doc) {
    if (current && !current.root.isConnected) {
      current.destroy();
      current = null;
    }
    var root = (doc.body || document.body).querySelector("#kp-map");
    if (root) mount(root);
  }

  if (window.document$) {
    window.document$.subscribe(onDocument);
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function () { onDocument(document); });
  } else {
    onDocument(document);
  }
})();

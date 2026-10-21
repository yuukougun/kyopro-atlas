/*
 * kyopro-atlas：知識マップ（planning/interfaces.md §7、design.md §8.4・§9.1、design-review T2）
 *
 * docs/guide/knowledge-map.md の <div id="kp-map"></div> に、graph.json のページの前提関係を描く。
 * Cytoscape.js と dagre（同梱）は地図のあるページでだけ読み込む。
 *
 * - 既定は分野ごとの表示（?field=<分野>）。その分野のページに加え、ほかの分野の直接の前提と次のページを破線の枠で出す
 * - ?focus=<id>：そのページの祖先（前提をすべて）と子孫（次に読む）だけを描く。子孫が多いときは深さを絞って始める
 *   （?depth=<1〜3>、0 はすべて）。related は配置に使わず、配置の後で右に薄く足す
 * - ?view=all：分野を頂点にした全体の図。辺の太さは分野をまたぐ前提の本数。分野を押すとその分野の表示になる
 * - 枠の色はレベル（AtCoder の色）。理解したページ（ページのレベルの「理解した」）を塗り、前提をすべて理解した
 *   未読のページ（次の候補）を光らせる。「+青」は上位の帯の節を持つページ
 * - 点を押す（タップする）とそのページへ移る。マウスを乗せる・長押しすると説明を出す
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
    find.placeholder = "名前で探して中心に";
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
    var canvas = html("div", "kp-map__canvas");
    canvas.setAttribute("role", "img");
    canvas.setAttribute("aria-label", "ページの前提関係の図。同じ内容はレベル別の一覧と各ページの「前提」「次に読む」にもある");
    var info = html("div", "kp-map__info");
    info.hidden = true;
    info.setAttribute("aria-live", "polite");

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

    root.append(toolbar, status, canvas, info, legend);
    return {
      bField: bField, bAll: bAll, fieldLabel: fieldLabel, fieldSel: fieldSel, find: find, list: list,
      depthLabel: depthLabel, depthSel: depthSel, bFit: bFit, status: status, canvas: canvas, info: info,
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

    // related は配置の後で、図の右に「関連」の囲みとして足す（配置には使わない。T2）
    function addRelated(id) {
      var p = G.byId.get(id);
      var rel = (p.related || []).filter(function (r, k, arr) { return r !== id && G.byId.has(r) && arr.indexOf(r) === k; });
      if (!rel.length) return;
      var bb = cy.elements().boundingBox();
      var fy = cy.getElementById(id).position("y");
      var missing = rel.filter(function (r) { return cy.getElementById(r).empty(); });
      var nodes = missing.map(function (r) { return pageNode(G.byId.get(r), ["rel"]); });
      var total = nodes.reduce(function (s, nd) { return s + nd.data.h + 10; }, -10);
      var y = fy - total / 2;
      var x = bb.x2 + 90;
      var adds = [];
      if (nodes.length) adds.push({ group: "nodes", data: { id: "__related", label: "関連", w: 1, h: 1 }, classes: "relbox" });
      nodes.forEach(function (nd) {
        nd.data.parent = "__related";
        nd.position = { x: x + nd.data.w / 2, y: y + nd.data.h / 2 };
        y += nd.data.h + 10;
        adds.push(nd);
      });
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
        cy.center(cy.getElementById(state.focus));
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
      ui.info.hidden = true;
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

    function showInfo(p) {
      var box = ui.info;
      box.textContent = "";
      var head = html("p");
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
      var acts = html("p");
      var open = html("a", null, "ページを開く");
      open.href = pageUrl(p);
      acts.appendChild(open);
      if (!(state.view === "focus" && state.focus === p.id)) {
        var center = button("この点を中心に表示");
        center.addEventListener("click", function () { setState({ view: "focus", focus: p.id }); });
        acts.appendChild(center);
      }
      box.appendChild(acts);
      box.hidden = false;
    }

    function hover(n, on) {
      n.toggleClass("hover", on);
      n.connectedEdges().not(".rel").toggleClass("hl", on);
    }

    cy.on("tap", "node.page", function (e) {
      if (Date.now() < holdUntil) return; // 長押しの直後の tap は無視する
      navigate(pageUrl(G.byId.get(e.target.id())));
    });
    cy.on("tap", "node.field, node.next", function (e) {
      if (Date.now() < holdUntil) return;
      setState({ view: "field", field: e.target.data("field") });
    });
    function showNext(n, on) {
      n.toggleClass("hover", on);
      cy.collection(n.data("sources").map(function (id) { return cy.getElementById(id); }).filter(function (x) { return x.nonempty(); }))
        .toggleClass("src", on);
      if (!on) return;
      var titles = n.data("pages").map(function (id) { return G.byId.get(id).title; });
      ui.info.textContent = "→ " + (G.fieldTitle.get(n.data("field")) || n.data("field")) + "：" + titles.slice(0, 8).join("・") +
        (titles.length > 8 ? " ほか " + (titles.length - 8) + " ページ" : "") + "。光っているページが前提になる（押すとその分野の表示）";
      ui.info.hidden = false;
    }
    cy.on("mouseover", "node.next", function (e) { showNext(e.target, true); });
    cy.on("mouseout", "node.next", function (e) { showNext(e.target, false); });
    cy.on("taphold", "node.next", function (e) {
      holdUntil = Date.now() + 1000;
      cy.nodes(".src").removeClass("src");
      showNext(e.target, true);
    });
    cy.on("taphold", "node.page", function (e) {
      holdUntil = Date.now() + 1000;
      showInfo(G.byId.get(e.target.id()));
    });
    cy.on("mouseover", "node.page", function (e) {
      hover(e.target, true);
      showInfo(G.byId.get(e.target.id()));
    });
    cy.on("mouseover", "node.field", function (e) { hover(e.target, true); });
    cy.on("mouseout", "node", function (e) { hover(e.target, false); });
    cy.on("mouseover", "edge.agg", function (e) {
      var d = e.target.data();
      ui.info.textContent = (G.fieldTitle.get(d.source.slice(6)) || "") + " → " + (G.fieldTitle.get(d.target.slice(6)) || "") +
        "：分野をまたぐ前提 " + d.n + " 本";
      ui.info.hidden = false;
    });

    // ツールバー
    G.fields.forEach(function (f) { if (G.hasPages.has(f.id)) ui.fieldSel.add(new Option(f.title, f.id)); });
    var byTitle = new Map();
    G.fields.forEach(function (f) {
      G.pages.filter(function (p) { return p.field === f.id; })
        .sort(function (a, b) { return a.order - b.order; })
        .forEach(function (p) {
          byTitle.set(p.title, p.id);
          var o = document.createElement("option");
          o.value = p.title;
          ui.list.appendChild(o);
        });
    });
    ui.bField.addEventListener("click", function () {
      var f = state.field || (state.focus && G.byId.get(state.focus).field) || defaultField();
      setState({ view: "field", field: f });
    });
    ui.bAll.addEventListener("click", function () { setState({ view: "all" }); });
    ui.fieldSel.addEventListener("change", function () { setState({ view: "field", field: ui.fieldSel.value }); });
    ui.depthSel.addEventListener("change", function () { setState({ depth: Number(ui.depthSel.value) }); });
    ui.find.addEventListener("change", function () {
      var v = ui.find.value.trim();
      var id = byTitle.get(v) || (G.byId.has(v) ? v : null);
      if (!id) {
        G.pages.some(function (p) {
          if ((p.nav_title && p.nav_title === v) || p.title.indexOf(v) >= 0) { id = p.id; return true; }
          return false;
        });
      }
      if (id) {
        ui.find.value = "";
        ui.find.blur(); // スマホではキーボードを閉じて地図を見せる
        setState({ view: "focus", focus: id, field: G.byId.get(id).field });
      } else if (v) {
        ui.status.textContent = "「" + v + "」に合うページがない。";
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
    api.destroy = function () {
      document.removeEventListener("kp:progress", onProgress);
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

/*
 * 動く図：Aho-Corasick 法で、Trie の節点を BFS 順に取り出して失敗リンクと遷移表を作り（前半）、
 * テキストを 1 文字ずつ流して状態の移動と出現を示す（後半）（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="aho-corasick" data-config='{"patterns": ["he", "she", "his", "hers"], "text": "ushers"}'></div>
 * config：
 *   patterns … パターンの配列（1〜6 個）。各要素は英小文字 1〜5 文字で、同じ文字列は 2 回書かない。
 *              幅 360 で読めるよう、Trie の節点は根を含めて 16 個まで、葉は 4 個まで、パターンに現れる文字は 6 種類まで
 *   text     … 流すテキスト（英小文字 1〜8 文字）。パターンに現れない文字を含んでよい
 *
 * snippets/aho-corasick/count.cpp の build と同じ手順をたどる。根をキューに入れ、取り出した節点 v について
 * 終端の印を link(v) から受け継ぎ、パターンに現れる文字 c を順に見る。v に子 u（文字 c）があれば nxt[v][c] = u とし、
 * link(u) = nxt[link(v)][c]（v が根なら根）。子がなければ nxt[v][c] = nxt[link(v)][c]（v が根なら根）。
 * パターンに現れない文字は、どの節点からも根へ移る。
 * 前半は初期状態と取り出し 1 回ごとに 1 ステップ。後半は読み始め・1 文字ごと・読み終わりに 1 ステップずつ。
 * 後半では、着いた状態から失敗リンクを根までたどり（連鎖）、連鎖の上にある終端の節点を、そこで終わる出現とする。
 *
 * 図：上に Trie（静的な図 failure-links.svg と同じく、終端は二重丸、失敗リンクは破線の矢印。根を指すリンクは
 * 矢印を根まで引かず、節点の横の短い破線の矢印と「根」で示す）。下に、前半はキューと「link(v) の行と v の行」、
 * 後半はテキストと各文字を読んだ後の状態・見つけた出現の括弧・パターンごとの回数を置く。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/aho-corasick.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("aho-corasick", def);
})(function () {
  "use strict";

  var MAX_PATTERNS = 6;
  var MAX_LEN = 5;
  var MAX_TEXT = 8;
  var MAX_NODES = 16;
  var MAX_LEAVES = 4;
  var MAX_SIGMA = 6;
  var LOWER = /^[a-z]+$/;

  // ---------- 入力と Trie ----------

  function buildTrie(patterns) {
    var nodes = [{ s: "", parent: -1, c: "", depth: 0, kids: {}, pat: -1 }];
    var seen = {};
    patterns.forEach(function (p, j) {
      var v = 0;
      for (var i = 0; i < p.length; i++) {
        var ch = p[i];
        seen[ch] = true;
        var u = nodes[v].kids[ch];
        if (u == null) {
          u = nodes.length;
          nodes.push({ s: p.slice(0, i + 1), parent: v, c: ch, depth: i + 1, kids: {}, pat: -1 });
          nodes[v].kids[ch] = u;
        }
        v = u;
      }
      nodes[v].pat = j;
    });
    return { nodes: nodes, sigma: Object.keys(seen).sort() };
  }

  function validate(config) {
    if (!config || typeof config !== "object" || Array.isArray(config)) throw new Error("data-config がない");
    var ps = config.patterns;
    if (!Array.isArray(ps) || ps.length < 1 || ps.length > MAX_PATTERNS) {
      throw new Error("patterns は 1〜" + MAX_PATTERNS + " 個の文字列の配列にする");
    }
    var patterns = [];
    for (var i = 0; i < ps.length; i++) {
      var p = ps[i];
      if (typeof p !== "string" || p.length < 1 || p.length > MAX_LEN || !LOWER.test(p)) {
        throw new Error("patterns の各要素は英小文字 1〜" + MAX_LEN + " 文字の文字列にする");
      }
      if (patterns.indexOf(p) >= 0) throw new Error("patterns に同じ文字列が 2 回ある：" + p);
      patterns.push(p);
    }
    var text = config.text;
    if (typeof text !== "string" || text.length < 1 || text.length > MAX_TEXT) {
      throw new Error("text は 1〜" + MAX_TEXT + " 文字の文字列にする");
    }
    if (!LOWER.test(text)) throw new Error("text の文字は英小文字にする");
    var t = buildTrie(patterns);
    if (t.nodes.length > MAX_NODES) {
      throw new Error("Trie の節点が根を含めて " + t.nodes.length + " 個ある。" + MAX_NODES + " 個までにする");
    }
    var leaves = t.nodes.filter(function (x) { return Object.keys(x.kids).length === 0; }).length;
    if (leaves > MAX_LEAVES) {
      throw new Error("Trie の葉が " + leaves + " 個ある。幅 360 で読めるよう " + MAX_LEAVES + " 個までにする");
    }
    if (t.sigma.length > MAX_SIGMA) {
      throw new Error("パターンに現れる文字が " + t.sigma.length + " 種類ある。" + MAX_SIGMA + " 種類までにする");
    }
    return { patterns: patterns, text: text, nodes: t.nodes, sigma: t.sigma };
  }

  // count.cpp の build と同じ順に、BFS で行と失敗リンクを決める。pops は取り出し 1 回ごとの記録
  function automaton(c) {
    var nodes = c.nodes, sigma = c.sigma, n = nodes.length;
    var link = [], row = [], mark = [];
    for (var i = 0; i < n; i++) {
      link.push(null);
      row.push(null);
      mark.push(nodes[i].pat >= 0);
    }
    link[0] = 0; // 根の失敗リンクは根とする
    var queue = [0], order = [], pops = [];
    while (queue.length) {
      var v = queue.shift();
      order.push(v);
      var from = v === 0 ? null : link[v];
      var inherited = from !== null && mark[from];
      if (inherited) mark[v] = true; // 印を失敗リンク先から受け継ぐ
      var r = {}, kids = [];
      for (var k = 0; k < sigma.length; k++) {
        var ch = sigma[k];
        var u = nodes[v].kids[ch];
        var w = v === 0 ? 0 : row[from][ch]; // link(v) の行は v より先に埋まっている
        if (u == null) {
          r[ch] = w; // 子がなければ、失敗した先の遷移を写す
        } else {
          r[ch] = u;
          link[u] = w; // 子の失敗リンクは、親の失敗リンク先から ch で進んだ先
          kids.push({ c: ch, u: u, w: w });
          queue.push(u);
        }
      }
      row[v] = r;
      pops.push({ v: v, from: from, kids: kids, inherited: inherited, queue: queue.slice(), link: link.slice(), mark: mark.slice() });
    }
    return { link: link, row: row, mark: mark, order: order, pops: pops };
  }

  function step(A, v, ch) {
    var t = A.row[v][ch];
    return t == null ? 0 : t; // パターンに現れない文字は根へ
  }

  // 節点の名前の後に助詞を続けるとき、英字なら空白を入れる（根なら入れない）
  function bare(name) {
    return /[a-z]$/.test(name) ? name + " " : name;
  }

  function listJa(a) {
    if (a.length === 2) return a[0] + " と " + a[1];
    return a.join("・");
  }

  // ---------- 状態の列 ----------
  // 各状態：
  //   phase … init（Trie だけ）／pop（節点を 1 つ取り出した）／scan（読み始め）／read（1 文字読んだ）／done（読み終えた）
  //   節点は文字列で表す（根は ""）。
  //   前半：popped（取り出した節点）、from（link(popped)。根なら null）、kids（子 {c, u, link}）、
  //         row・fromRow（popped と link(popped) の行。文字 → 節点）、inherited（終端の印を受け継いだか）、
  //         queue（処理の後のキュー。先頭 → 末尾）、done（取り出し済みの節点。BFS 順）、
  //         link（節点 → 失敗リンク。未定は null）、mark（節点 → 終端の印。受け継いだ分を含む）
  //   後半：pos（読んだ文字数）、char（読んだ文字）、prev・cur（読む前と後の状態）、
  //         via（child：子へ進んだ／root：根のまま／jump：子がなく遷移表の値へ移った）、
  //         chain（cur から根までの失敗リンクの連鎖。cur を含み根で終わる）、
  //         found（このステップで見つけた出現 {pattern, start, end}。end は読んだ文字数で、テキストの [start, end)）、
  //         all（ここまでに見つけた出現）、counts（パターンごとの出現回数。patterns の順）、trail（各文字を読んだ後の状態）
  //   caption
  function states(config) {
    var c = validate(config);
    var nodes = c.nodes, sigma = c.sigma, P = c.patterns, text = c.text;
    var A = automaton(c);
    var n = nodes.length;

    function key(v) { return nodes[v].s; }
    function nm(v) { return v === 0 ? "根" : nodes[v].s; }
    function linkMap(arr) {
      var m = {};
      for (var v = 0; v < n; v++) m[key(v)] = arr[v] === null ? null : key(arr[v]);
      return m;
    }
    function markMap(arr) {
      var m = {};
      for (var v = 0; v < n; v++) m[key(v)] = arr[v];
      return m;
    }
    function rowMap(v) {
      if (v === null) return null;
      var m = {};
      sigma.forEach(function (ch) { m[ch] = key(A.row[v][ch]); });
      return m;
    }
    function occ(list) {
      return list.map(function (o) { return { pattern: o.pattern, start: o.start, end: o.end }; });
    }
    var zeros = P.map(function () { return 0; });
    function snap(extra) {
      var s = {
        phase: null, popped: null, from: null, kids: [], row: null, fromRow: null, inherited: false,
        queue: [], done: [], link: null, mark: null,
        pos: 0, char: null, prev: null, cur: null, via: null, chain: [], found: [], all: [], counts: zeros.slice(), trail: [],
        caption: "",
      };
      Object.keys(extra).forEach(function (k) { s[k] = extra[k]; });
      return s;
    }

    var out = [];
    var init = [];
    var initMark = [];
    for (var v0 = 0; v0 < n; v0++) {
      init.push(v0 === 0 ? 0 : null);
      initMark.push(nodes[v0].pat >= 0);
    }
    out.push(snap({
      phase: "init", queue: [""], link: linkMap(init), mark: markMap(initMark),
      caption: "パターン " + P.join(", ") + " を Trie に入れた（二重丸が終端）。失敗リンクはまだ決まっていない。" +
        "根をキューに入れ、BFS 順に節点を 1 つずつ取り出して、その行と子の失敗リンクを決めていく。",
    }));

    var done = [];
    A.pops.forEach(function (p) {
      var v = p.v;
      done.push(key(v));
      var cap;
      if (v === 0) {
        cap = "根を取り出す。根の行は、子のある文字（" + p.kids.map(function (k) { return k.c; }).join(", ") +
          "）ではその子、ほかの文字では根にする。根の子 " + p.kids.map(function (k) { return nm(k.u); }).join(", ") +
          " の失敗リンクは根にする（真の接尾辞は空だけである）。";
      } else {
        var L = nm(p.from), V = nm(v);
        cap = V + " を取り出す。";
        if (p.kids.length === 0) {
          cap += "子はないので、" + V + " の行は link(" + V + ") = " + L + " の行をそのまま写す。";
        } else {
          cap += V + " の行は link(" + V + ") = " + L + " の行を写し、子のある欄（" +
            p.kids.map(function (k) { return k.c; }).join(", ") + "）だけ自分の子にする。" +
            p.kids.map(function (k) {
              return "子 " + nm(k.u) + " の失敗リンクは nxt[link(" + V + ") = " + L + "][" + k.c + "] = " + nm(k.w);
            }).join("、") + " である。";
        }
        if (p.inherited) {
          cap += "link(" + V + ") = " + L + " が終端の印を持つので、" + V + " もその印を受け継ぐ" +
            (nodes[v].pat >= 0 ? "。" : "（" + V + " 自身はパターンの終端ではない）。");
        }
      }
      out.push(snap({
        phase: "pop", popped: key(v), from: p.from === null ? null : key(p.from),
        kids: p.kids.map(function (k) { return { c: k.c, u: key(k.u), link: key(k.w) }; }),
        row: rowMap(v), fromRow: rowMap(p.from), inherited: p.inherited,
        queue: p.queue.map(key), done: done.slice(), link: linkMap(p.link), mark: markMap(p.mark),
        caption: cap,
      }));
    });

    var allDone = A.order.map(key);
    var finalLink = linkMap(A.link);
    var finalMark = markMap(A.mark);
    function later(extra) {
      extra.done = allDone.slice();
      extra.link = finalLink;
      extra.mark = finalMark;
      return snap(extra);
    }

    out.push(later({
      phase: "scan", cur: "", chain: [""],
      caption: "すべての節点を取り出し、失敗リンクと遷移表ができた。ここからテキスト " + text +
        " を 1 文字ずつ読む。状態は根から始める。",
    }));

    var cur = 0, counts = zeros.slice(), all = [], trail = [];
    for (var i = 0; i < text.length; i++) {
      var ch = text[i];
      var prev = cur;
      var child = nodes[prev].kids[ch];
      cur = step(A, prev, ch);
      var via = child != null ? "child" : prev === 0 ? "root" : "jump";
      trail.push(key(cur));
      var chain = [];
      for (var x = cur; ; x = A.link[x]) {
        chain.push(x);
        if (x === 0) break;
      }
      var found = [];
      chain.forEach(function (y) {
        if (nodes[y].pat >= 0) found.push({ pattern: nodes[y].pat, start: i + 1 - nodes[y].depth, end: i + 1 });
      });
      found.forEach(function (f) { counts[f.pattern]++; });
      all = all.concat(found);

      var cap = (i + 1) + " 文字目の " + ch + " を読む。";
      if (via === "child") {
        cap += bare(nm(prev)) + "に子 " + ch + " があるので、" + bare(nm(cur)) + "へ進む。";
      } else if (via === "root") {
        cap += "根に子 " + ch + " はないので、根のままである。";
      } else {
        cap += bare(nm(prev)) + "に子 " + ch + " はない。遷移表では nxt[" + nm(prev) + "][" + ch + "] = " + nm(cur) +
          "（link(" + nm(prev) + ") = " + nm(A.link[prev]) + " の行から写した値）なので、" +
          (cur === prev ? bare(nm(cur)) + "のままである。" : bare(nm(cur)) + "へ移る。");
      }
      if (cur === 0) {
        cap += "状態が根なので、ここで終わるパターンはない。";
      } else {
        cap += "失敗リンクをたどると " + chain.map(nm).join("・") + " で、";
        if (found.length) {
          var names = found.map(function (f) { return P[f.pattern]; });
          cap += "ここで終わる出現は " + listJa(names) + (names.length > 1 ? " の " + names.length + " つである。" : " である。");
        } else {
          cap += "終端の節点はないので、ここで終わるパターンはない。";
        }
      }
      out.push(later({
        phase: "read", pos: i + 1, char: ch, prev: key(prev), cur: key(cur), via: via, chain: chain.map(key),
        found: occ(found), all: occ(all), counts: counts.slice(), trail: trail.slice(), caption: cap,
      }));
    }

    var capEnd = "テキストを読み終えた。";
    if (all.length === 0) {
      capEnd += "パターンの出現はなかった。";
    } else {
      var groups = [];
      all.forEach(function (o) {
        var g = groups.length ? groups[groups.length - 1] : null;
        if (g && g.end === o.end) g.names.push(P[o.pattern]);
        else groups.push({ end: o.end, names: [P[o.pattern]] });
      });
      var parts = groups.map(function (g) { return g.names.join("・") + "（" + g.end + " 文字目で終わる）"; });
      capEnd += "出現は " + (parts.length === 2 ? parts.join("と ") : parts.join("、")) + "の " + all.length + " つである。";
    }
    capEnd += "連鎖を毎回たどると遅くなることがあるので、回数をまとめて数える方法を出現回数の集計の節で述べる。";
    out.push(later({
      phase: "done", pos: text.length, cur: key(cur), all: occ(all), counts: counts.slice(), trail: trail.slice(),
      caption: capEnd,
    }));
    return out;
  }

  // ---------- 配置 ----------
  var W = 400;
  var R = 16; // 節点の半径
  var RING = 4; // 終端の外側の輪（半径 R + RING）
  var DY = 46; // 深さ 1 つ分の高さ
  var ROOT_Y = 30;
  var SIDE = 64; // 両端の葉の外側に空ける幅（回り込む矢印と「根」の札の分）
  var CLEAR = 9; // 線と節点の間に空けたい距離
  var GAP = 2; // 矢じりの先と節点の円の間
  var ALONG = [0, -0.3, 0.3, -0.6, 0.6];
  var BOW = [0, 0.1, -0.1, 0.2, -0.2, 0.3, -0.3, 0.45, -0.45, 0.6, -0.6, 0.8, -0.8, 1, -1];
  var TAG_DIRS = [0, 180, -40, -140, 40, 140, -90, 90]; // 「根」の札を置く向き（度。0 が右、正が下）

  function dist(p, q) {
    var dx = p[0] - q[0], dy = p[1] - q[1];
    return Math.sqrt(dx * dx + dy * dy);
  }
  function unit(p, q) { // p から q への単位ベクトル
    var d = dist(p, q) || 1;
    return [(q[0] - p[0]) / d, (q[1] - p[1]) / d];
  }
  function orient(a, b, c) { return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]); }
  function crosses(a, b, c, d) {
    return orient(a, b, c) * orient(a, b, d) < 0 && orient(c, d, a) * orient(c, d, b) < 0;
  }
  function segDist(p, a, b) { // 点 p と線分 ab の距離
    var vx = b[0] - a[0], vy = b[1] - a[1];
    var l2 = vx * vx + vy * vy;
    var t = l2 ? Math.max(0, Math.min(1, ((p[0] - a[0]) * vx + (p[1] - a[1]) * vy) / l2)) : 0;
    return dist(p, [a[0] + t * vx, a[1] + t * vy]);
  }
  function quad(p0, c, p2, t) {
    var u = 1 - t;
    return [u * u * p0[0] + 2 * u * t * c[0] + t * t * p2[0], u * u * p0[1] + 2 * u * t * c[1] + t * t * p2[1]];
  }
  function polyCross(pts, a, b) {
    var k = 0;
    for (var i = 1; i < pts.length; i++) if (crosses(pts[i - 1], pts[i], a, b)) k++;
    return k;
  }

  // 文字の幅の見積もり（英数字は約 0.56 字、日本語は 1 字）
  function textWidth(s, size) {
    var w = 0;
    for (var i = 0; i < s.length; i++) {
      var ch = s[i];
      if (s.charCodeAt(i) >= 0x2000) w += 1;
      else if (/[ilj.,:;|()\[\]' ]/.test(ch)) w += 0.3;
      else if (/[mw]/.test(ch)) w += 0.85;
      else w += 0.56;
    }
    return w * size;
  }

  // 節点 a（半径 ra）から節点 b（半径 rb）への 2 次のベジェ曲線。cp は制御点
  function curve(a, ra, cp, b, rb) {
    var u0 = unit(a, cp), u2 = unit(b, cp);
    var p0 = [a[0] + u0[0] * ra, a[1] + u0[1] * ra];
    var p2 = [b[0] + u2[0] * rb, b[1] + u2[1] * rb];
    var pts = [];
    for (var i = 0; i <= 32; i++) pts.push(quad(p0, cp, p2, i / 32));
    return { p0: p0, c: cp, p2: p2, pts: pts };
  }

  function curveLength(pts) {
    var s = 0;
    for (var i = 1; i < pts.length; i++) s += dist(pts[i - 1], pts[i]);
    return s;
  }

  // 曲線の悪さ：節点や辺の文字に近い・枠の外に出る・辺やほかの線と交わる・曲がり・長さ
  function badness(cv, from, to, G, lines) {
    var pen = 0, pts = cv.pts;
    pts.forEach(function (p) {
      if (p[0] < G.minX || p[0] > G.maxX || p[1] < G.minY || p[1] > G.maxY) pen += 300;
    });
    for (var k = 0; k < G.pos.length; k++) {
      if (k === from || k === to) continue;
      var m = Infinity;
      for (var i = 0; i < pts.length; i++) m = Math.min(m, dist(pts[i], G.pos[k]));
      var clr = m - G.rad[k];
      if (clr < CLEAR) pen += (CLEAR - clr) * 60;
    }
    // 端の節点そのものに戻り込まない
    for (var j = 4; j < pts.length - 4; j++) {
      if (dist(pts[j], G.pos[from]) < G.rad[from] + 2 || dist(pts[j], G.pos[to]) < G.rad[to] + 2) pen += 200;
    }
    G.labels.forEach(function (lb) {
      var m2 = Infinity;
      for (var i = 0; i < pts.length; i++) m2 = Math.min(m2, dist(pts[i], lb.c));
      if (m2 < 11) pen += (11 - m2) * 20;
    });
    G.edges.forEach(function (e) {
      pen += 25 * polyCross(pts, e.a, e.b);
      // 辺に沿って重なる（1 本の道の Trie で、すぐ上の節点へのリンクなど）
      for (var i = 4; i < pts.length - 4; i++) if (segDist(pts[i], e.a, e.b) < 6) pen += 12;
    });
    lines.forEach(function (o) {
      for (var i = 1; i < o.pts.length; i++) pen += 15 * polyCross(pts, o.pts[i - 1], o.pts[i]);
      for (var a = 3; a < pts.length - 3; a++) {
        for (var b = 0; b < o.pts.length; b++) if (dist(pts[a], o.pts[b]) < 6) { pen += 20; break; }
      }
    });
    (G.tags || []).forEach(function (t) {
      t.foot.forEach(function (q) {
        for (var i = 0; i < pts.length; i++) if (dist(pts[i], q) < 7) { pen += 40; break; }
      });
    });
    // 隣り合う深さの節点どうしのリンクは、短すぎると矢印に見えないので少しふくらませる
    var len = curveLength(pts);
    if (len < 36) pen += (36 - len) * 4;
    return pen + 0.03 * len;
  }

  // from から to への曲線を、制御点の候補の中から選ぶ
  function route(from, to, G, lines) {
    var a = G.pos[from], b = G.pos[to];
    var L = dist(a, b) || 1;
    var d = unit(a, b), nrm = [-d[1], d[0]];
    var mid = [(a[0] + b[0]) / 2, (a[1] + b[1]) / 2];
    var best = null;
    ALONG.forEach(function (ka) {
      BOW.forEach(function (kb) {
        var cp = [mid[0] + (ka * d[0] + kb * nrm[0]) * L, mid[1] + (ka * d[1] + kb * nrm[1]) * L];
        var cv = curve(a, G.rad[from], cp, b, G.rad[to] + GAP);
        var pen = badness(cv, from, to, G, lines) + Math.abs(kb) * 40 + Math.abs(ka) * 15;
        if (!best || pen < best.pen - 1e-9) best = { pen: pen, cv: cv };
      });
    });
    return best.cv;
  }

  // 根を指す失敗リンクの札（短い破線の矢印と「根」）の位置
  function tagShape(G, v, deg) {
    var th = deg * Math.PI / 180;
    var u = [Math.cos(th), Math.sin(th)];
    var c = G.pos[v];
    var r0 = G.rad[v] + 1;
    var s = [c[0] + u[0] * r0, c[1] + u[1] * r0];
    var e = [c[0] + u[0] * (r0 + 15), c[1] + u[1] * (r0 + 15)];
    var t = [e[0] + u[0] * 9, e[1] + u[1] * 9];
    var foot = [s, [(s[0] + e[0]) / 2, (s[1] + e[1]) / 2], e, t,
      [t[0] - 6, t[1] - 7], [t[0] + 6, t[1] - 7], [t[0] - 6, t[1] + 7], [t[0] + 6, t[1] + 7]];
    return { v: v, u: u, s: s, e: e, t: t, foot: foot };
  }

  function placeTag(G, v, lines, placed) {
    var best = null;
    TAG_DIRS.forEach(function (deg, k) {
      var sh = tagShape(G, v, deg);
      var pen = k * 2;
      sh.foot.forEach(function (q, qi) {
        if (q[0] < 4 || q[0] > W - 4 || q[1] < G.minY - 6 || q[1] > G.maxY) pen += 500;
        for (var w = 0; w < G.pos.length; w++) {
          if (w === v && qi === 0) continue;
          var clr = dist(q, G.pos[w]) - G.rad[w];
          if (w === v) clr += 6;
          if (clr < 5) pen += (5 - clr) * 40;
        }
        G.edges.forEach(function (ed) {
          var dd = segDist(q, ed.a, ed.b);
          if (dd < 6) pen += (6 - dd) * 30;
        });
        G.labels.forEach(function (lb) {
          var dd = dist(q, lb.c);
          if (dd < 11) pen += (11 - dd) * 30;
        });
        lines.forEach(function (o) {
          for (var i = 0; i < o.pts.length; i++) if (dist(q, o.pts[i]) < 7) { pen += 60; break; }
        });
        placed.forEach(function (o) {
          o.foot.forEach(function (r) { if (dist(q, r) < 12) pen += 60; });
        });
      });
      if (!best || pen < best.pen) best = { pen: pen, shape: sh };
    });
    return best.shape;
  }

  // 出現の括弧を重ならない段に分ける（始まりの順に、空いている一番下の段へ）
  function occurrenceLevels(c, A) {
    var occs = [];
    var cur = 0;
    for (var i = 0; i < c.text.length; i++) {
      cur = step(A, cur, c.text[i]);
      for (var x = cur; x !== 0; x = A.link[x]) {
        if (c.nodes[x].pat >= 0) occs.push({ pattern: c.nodes[x].pat, start: i + 1 - c.nodes[x].depth, end: i + 1 });
      }
    }
    occs.sort(function (p, q) { return p.start - q.start || q.end - p.end; });
    var ends = [], level = {};
    occs.forEach(function (o) {
      var k = 0;
      while (k < ends.length && ends[k] > o.start) k++;
      ends[k] = o.end;
      level[o.pattern + ":" + o.start] = k;
    });
    return { levels: Math.max(1, ends.length), level: level };
  }

  function layout(config) {
    var c = validate(config);
    var A = automaton(c);
    var nodes = c.nodes, n = nodes.length;
    var kidsOf = nodes.map(function (x) {
      return c.sigma.filter(function (ch) { return x.kids[ch] != null; }).map(function (ch) { return x.kids[ch]; });
    });
    // 葉を左から順に並べ、親は最初と最後の子の中央に置く（子は文字の順）
    var col = new Array(n), leaves = 0;
    (function place(v) {
      var ks = kidsOf[v];
      if (!ks.length) {
        col[v] = leaves++;
        return;
      }
      ks.forEach(place);
      col[v] = (col[ks[0]] + col[ks[ks.length - 1]]) / 2;
    })(0);
    var maxDepth = 0;
    nodes.forEach(function (x) { maxDepth = Math.max(maxDepth, x.depth); });
    var pitch = leaves > 1 ? Math.min(120, (W - 2 * SIDE) / (leaves - 1)) : 0;
    var x0 = (W - (leaves - 1) * pitch) / 2;
    var pos = nodes.map(function (x, v) { return [x0 + col[v] * pitch, ROOT_Y + x.depth * DY]; });
    var rad = nodes.map(function (x) { return x.pat >= 0 ? R + RING : R; });
    var G = {
      c: c, A: A, pos: pos, rad: rad, edges: [], labels: [],
      minX: 6, maxX: W - 6, minY: ROOT_Y - R - 14, maxY: ROOT_Y + maxDepth * DY + R + RING + 14,
    };
    for (var v = 1; v < n; v++) {
      var p = nodes[v].parent;
      var uu = unit(pos[p], pos[v]);
      var a = [pos[p][0] + uu[0] * rad[p], pos[p][1] + uu[1] * rad[p]];
      var b = [pos[v][0] - uu[0] * rad[v], pos[v][1] - uu[1] * rad[v]];
      G.edges.push({ p: p, v: v, a: a, b: b });
      var mx = (pos[p][0] + pos[v][0]) / 2, my = (pos[p][1] + pos[v][1]) / 2;
      var dx = pos[v][0] - pos[p][0];
      var lb;
      if (dx < -1) lb = { x: mx - 8, y: my - 4, anchor: "end" };
      else if (dx > 1) lb = { x: mx + 8, y: my - 4, anchor: "start" };
      else lb = { x: mx - 8, y: my, anchor: "end" };
      lb.c = [lb.anchor === "end" ? lb.x - 4 : lb.x + 4, lb.y];
      lb.text = nodes[v].c;
      lb.v = v;
      G.labels.push(lb);
    }
    // 失敗リンク（根以外を指すもの）を、決まる順（BFS 順）に引く
    G.links = {};
    var lines = [];
    A.order.forEach(function (v) {
      if (v === 0 || A.link[v] === 0) return;
      var cv = route(v, A.link[v], G, lines);
      G.links[v] = cv;
      lines.push(cv);
    });
    G.lines = lines;
    // 根を指す失敗リンクの札
    G.tags = [];
    G.tagOf = {};
    A.order.forEach(function (v) {
      if (v === 0 || A.link[v] !== 0) return;
      var t = placeTag(G, v, lines, G.tags);
      G.tags.push(t);
      G.tagOf[v] = t;
    });
    G.jumps = {}; // 後半の、子へ進むのでない移動の曲線（必要になったときに作る）

    // 下の段
    var panelTop = G.maxY + 6;
    // 前半の表
    var S = c.sigma.length;
    var lbl = textWidth("文字", 13);
    A.pops.forEach(function (pp) {
      if (pp.v === 0) return;
      lbl = Math.max(lbl, textWidth("link(" + nodes[pp.v].s + ") = " + (pp.from === 0 ? "根" : nodes[pp.from].s), 13),
        textWidth(nodes[pp.v].s, 14));
    });
    lbl += 12;
    var cw = Math.min(46, (W - 16 - lbl) / S);
    var tableX = (W - (lbl + S * cw)) / 2;
    G.table = { x: tableX, lbl: lbl, cw: cw, head: panelTop + 30, row1: panelTop + 40, row2: panelTop + 70, ch: 26 };
    var heightA = 98;
    // 後半のテキストの段
    var occL = occurrenceLevels(c, A);
    var textTop = panelTop + 6 + occL.levels * 8 + 4;
    var tlbl = textWidth("テキスト", 13) + 10;
    var tcw = Math.min(42, (W - 16 - tlbl) / c.text.length);
    var tx = (W - (tlbl + c.text.length * tcw)) / 2;
    // パターンごとの回数の行（収まらなければ 2 行に分ける）
    var items = c.patterns.map(function (p) { return p + " 0"; });
    var head = "出現回数：";
    var lineW = textWidth(head, 13) + items.reduce(function (s, it) { return s + textWidth(it, 13) + textWidth("・", 13); }, 0);
    var countLines = lineW > W - 16 ? 2 : 1;
    G.text = {
      x: tx + tlbl, lbl: tlbl, cw: tcw, top: textTop, h: 26, state: textTop + 26 + 13, count: textTop + 26 + 34,
      levels: occL.levels, level: occL.level, countLines: countLines,
    };
    var heightB = textTop - panelTop + 26 + 34 + 9 + 18 * (countLines - 1);
    G.panelTop = panelTop;
    G.legendTop = panelTop + Math.max(heightA, heightB) + 8;
    G.height = Math.ceil(G.legendTop + 38);
    return G;
  }

  var cache = typeof WeakMap === "function" ? new WeakMap() : null;
  function layoutFor(config) {
    var G = cache && cache.get(config);
    if (!G) {
      G = layout(config);
      if (cache) cache.set(config, G);
    }
    return G;
  }

  function viewBox(config) {
    return "0 0 " + W + " " + layoutFor(config).height;
  }

  // ---------- 描画 ----------
  var LINK = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:1.6;stroke-dasharray:5 4";
  var LINK_ON = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3.2;stroke-dasharray:7 4";
  var MOVE = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3.5";
  var HALO = "paint-order:stroke;stroke:var(--md-default-bg-color);stroke-width:3px";
  var LABEL_HALO = "paint-order:stroke;stroke:var(--md-default-bg-color);stroke-width:4px;stroke-linejoin:round";

  function arrowHead(svg, h, tip, dir, size, cls) {
    var px = -dir[1], py = dir[0];
    var bx = tip[0] - dir[0] * size, by = tip[1] - dir[1] * size;
    svg.appendChild(h("path", {
      d: "M" + tip[0].toFixed(1) + " " + tip[1].toFixed(1) +
        "L" + (bx + px * size * 0.5).toFixed(1) + " " + (by + py * size * 0.5).toFixed(1) +
        "L" + (bx - px * size * 0.5).toFixed(1) + " " + (by - py * size * 0.5).toFixed(1) + "z",
      class: cls,
    }));
  }

  // 曲線を矢じりの手前で止めて描き、矢じりを付ける
  function drawCurve(svg, h, cv, style, on, attrs) {
    var size = on ? 11 : 9;
    var dir = unit(cv.c, cv.p2);
    var back = Math.max(0.5, 1 - (size * 0.6) / (2 * (dist(cv.c, cv.p2) || 1)));
    var c1 = [cv.p0[0] + (cv.c[0] - cv.p0[0]) * back, cv.p0[1] + (cv.c[1] - cv.p0[1]) * back];
    var end = quad(cv.p0, cv.c, cv.p2, back);
    var a = { d: "M" + cv.p0[0].toFixed(1) + " " + cv.p0[1].toFixed(1) + "Q" + c1[0].toFixed(1) + " " + c1[1].toFixed(1) +
      " " + end[0].toFixed(1) + " " + end[1].toFixed(1), style: style };
    Object.keys(attrs || {}).forEach(function (k) { a[k] = attrs[k]; });
    svg.appendChild(h("path", a));
    arrowHead(svg, h, cv.p2, dir, size, "kp-v-mark is-b");
  }

  function drawTag(svg, h, t, on, name) {
    var size = on ? 9 : 7;
    var end = [t.e[0] - t.u[0] * size * 0.6, t.e[1] - t.u[1] * size * 0.6];
    svg.appendChild(h("path", {
      d: "M" + t.s[0].toFixed(1) + " " + t.s[1].toFixed(1) + "L" + end[0].toFixed(1) + " " + end[1].toFixed(1),
      style: on ? "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3;stroke-dasharray:4 3" :
        "fill:none;stroke:var(--md-accent-fg-color);stroke-width:1.6;stroke-dasharray:4 3",
      "data-root-tag": name,
    }));
    arrowHead(svg, h, t.e, t.u, size, "kp-v-mark is-b");
    svg.appendChild(h("text", {
      x: t.t[0].toFixed(1), y: t.t[1].toFixed(1), class: on ? "kp-v-ptr is-b" : "kp-v-text is-sub",
      style: "font-size:13px;" + HALO,
    }, "根"));
  }

  function nodeFont(s) {
    return s.length <= 3 ? 14 : s.length === 4 ? 13 : 12;
  }

  function drawNode(svg, h, G, v, o) {
    var p = G.pos[v];
    var nd = G.c.nodes[v];
    if (o.source) {
      svg.appendChild(h("circle", {
        cx: p[0], cy: p[1], r: R + RING + 5, class: "kp-v-cell is-focus", style: "fill:none", "stroke-dasharray": "4 3",
        "data-source": nd.s,
      }));
    }
    if (nd.pat >= 0) {
      svg.appendChild(h("circle", {
        cx: p[0], cy: p[1], r: R + RING, class: o.found ? "kp-v-cell is-focus" : "kp-v-cell", style: "fill:none",
        "data-terminal": nd.s,
      }));
    }
    svg.appendChild(h("circle", { cx: p[0], cy: p[1], r: R, style: "fill:var(--md-default-bg-color);stroke:none" }));
    svg.appendChild(h("circle", {
      cx: p[0], cy: p[1], r: R, class: "kp-v-cell" + (o.cls ? " " + o.cls : ""), style: o.thick ? "stroke-width:2.8" : null,
      "data-node": nd.s,
    }));
    svg.appendChild(h("text", {
      x: p[0], y: p[1], class: "kp-v-text" + (o.tcls ? " " + o.tcls : ""),
      style: "font-size:" + (v === 0 ? 14 : nodeFont(nd.s)) + "px" + (o.bold ? ";font-weight:700" : ""),
    }, v === 0 ? "根" : nd.s));
  }

  function render(svg, s, config, h) {
    var G = layoutFor(config);
    var c = G.c, nodes = c.nodes, n = nodes.length;
    var idx = {};
    nodes.forEach(function (x, v) { idx[x.s] = v; });
    function nm(key) { return key === "" ? "根" : key; }
    var front = s.phase === "init" || s.phase === "pop";
    var newKid = {};
    s.kids.forEach(function (k) { newKid[idx[k.u]] = true; });
    var inChain = {};
    var hot = s.phase === "read";
    if (hot) s.chain.forEach(function (k) { inChain[idx[k]] = true; });
    var foundAt = {};
    if (hot) s.found.forEach(function (f) { foundAt[idx[c.patterns[f.pattern]]] = true; });

    // Trie の辺。後半で子へ進んだ辺は太線（辺の文字は、輪に隠れないよう節点の後に描く）
    G.edges.forEach(function (e) {
      var on = hot && s.via === "child" && idx[s.prev] === e.p && idx[s.cur] === e.v;
      svg.appendChild(h("line", {
        x1: e.a[0].toFixed(1), y1: e.a[1].toFixed(1), x2: e.b[0].toFixed(1), y2: e.b[1].toFixed(1),
        class: on ? "kp-v-cell is-focus" : "kp-v-cell", "data-edge": nodes[e.v].s,
      }));
    });

    // 失敗リンク（決まったものだけ）。前半はこのステップで決まったもの、後半はたどる連鎖を太くする
    for (var v = 1; v < n; v++) {
      var lk = s.link[nodes[v].s];
      if (lk == null) continue;
      var on = front ? !!newKid[v] : hot && inChain[v];
      if (idx[lk] === 0) drawTag(svg, h, G.tagOf[v], on, nodes[v].s);
      else drawCurve(svg, h, G.links[v], on ? LINK_ON : LINK, on, { "data-link": nodes[v].s });
    }

    // 後半：子へ進むのでない移動は、実線の矢印で示す
    if (hot && s.via === "jump" && s.prev !== s.cur) {
      var keyJ = s.prev + ">" + s.cur;
      if (!G.jumps[keyJ]) G.jumps[keyJ] = route(idx[s.prev], idx[s.cur], G, G.lines);
      drawCurve(svg, h, G.jumps[keyJ], MOVE, true, { "data-move": keyJ });
    }

    // 節点
    var doneSet = {};
    s.done.forEach(function (k) { doneSet[idx[k]] = true; });
    for (v = 0; v < n; v++) {
      var o = { cls: "", tcls: "", bold: false, thick: false, source: false, found: false };
      if (front) {
        var decided = s.link[nodes[v].s] != null;
        if (s.popped != null && idx[s.popped] === v) {
          o.cls = "is-answer";
          o.tcls = "is-on-answer";
        } else if (doneSet[v]) {
          o.cls = "is-yes";
          o.thick = true;
        } else if (!decided) {
          o.cls = "is-sentinel";
          o.tcls = "is-dim";
        } else if (newKid[v]) {
          o.bold = true; // このステップで失敗リンクが決まった子（リンクの矢印も太い）
        }
        if (s.from != null && idx[s.from] === v) o.source = true;
      } else if (s.phase === "scan" || hot) {
        if (idx[s.cur] === v) {
          o.cls = "is-answer";
          o.tcls = "is-on-answer";
        } else if (inChain[v]) {
          o.cls = "is-yes";
          o.thick = true;
          o.bold = true;
        }
        o.found = !!foundAt[v];
      }
      drawNode(svg, h, G, v, o);
    }

    // 辺の文字。縦に並んだ節点の間は狭く、写す元の輪（半径 R + RING + 5）や出現の太い輪がかかるので、
    // 節点の後に縁取り付きで描いて上に出す
    G.labels.forEach(function (lb) {
      svg.appendChild(h("text", {
        x: lb.x.toFixed(1), y: lb.y.toFixed(1), class: "kp-v-text is-sub",
        style: "font-size:13px;font-style:italic;text-anchor:" + lb.anchor + ";" + LABEL_HALO,
        "data-edge-label": nodes[lb.v].s,
      }, lb.text));
    });

    if (front) renderTable(svg, s, G, h, idx, nm);
    else renderText(svg, s, G, h);
    renderLegend(svg, s, G, h, front);
  }

  function cellRect(svg, h, x, y, w, ht, cls, dashed, data) {
    var a = { x: x.toFixed(1), y: y.toFixed(1), width: (w - 4).toFixed(1), height: ht, rx: 5, class: cls };
    if (dashed) a["stroke-dasharray"] = "4 3";
    if (data) a["data-cell"] = data;
    svg.appendChild(h("rect", a));
  }

  // 前半の下の段：キューと、link(v) の行・v の行
  function renderTable(svg, s, G, h, idx, nm) {
    var top = G.panelTop;
    var T = G.table;
    var sigma = G.c.sigma;
    svg.appendChild(h("text", {
      x: 8, y: top + 9, class: "kp-v-text", style: "text-anchor:start;font-size:13px",
    }, "キュー（先頭 → 末尾）：" + (s.queue.length ? s.queue.map(nm).join(", ") : "空")));
    if (s.phase !== "pop") {
      svg.appendChild(h("text", {
        x: W / 2, y: T.row1 + 26, class: "kp-v-text is-sub", style: "font-size:13px",
      }, "取り出した節点の行と、その失敗リンク先の行をここに示す"));
      return;
    }
    var kidCol = {};
    s.kids.forEach(function (k) { kidCol[k.c] = true; });
    function cx(j) { return T.x + T.lbl + j * T.cw + 2; }
    function label(y, text, bold) {
      svg.appendChild(h("text", {
        x: (T.x + T.lbl - 8).toFixed(1), y: y, class: "kp-v-text" + (bold ? "" : " is-sub"),
        style: "text-anchor:end;font-size:13px" + (bold ? ";font-weight:700" : ""),
      }, text));
    }
    label(T.head, "文字", false);
    sigma.forEach(function (ch, j) {
      svg.appendChild(h("text", {
        x: (cx(j) + (T.cw - 4) / 2).toFixed(1), y: T.head, class: "kp-v-text is-sub", style: "font-size:13px;font-style:italic",
      }, ch));
    });
    // 上の行：link(v) の行（根を取り出したときは写す元がない）
    if (s.from == null) {
      label(T.row1 + T.ch / 2, "写す元なし", false);
      sigma.forEach(function (ch, j) {
        svg.appendChild(h("rect", {
          x: cx(j).toFixed(1), y: T.row1, width: (T.cw - 4).toFixed(1), height: T.ch, rx: 5, class: "kp-v-cell is-sentinel",
          "data-cell": "from:" + ch,
        }));
      });
    } else {
      label(T.row1 + T.ch / 2, "link(" + nm(s.popped) + ") = " + nm(s.from), false);
      sigma.forEach(function (ch, j) {
        var focus = !!kidCol[ch];
        cellRect(svg, h, cx(j), T.row1, T.cw, T.ch, focus ? "kp-v-cell is-focus" : "kp-v-cell", false, "from:" + ch);
        svg.appendChild(h("text", {
          x: (cx(j) + (T.cw - 4) / 2).toFixed(1), y: T.row1 + T.ch / 2, class: "kp-v-text",
          style: "font-size:13px" + (focus ? ";font-weight:700" : ""),
        }, nm(s.fromRow[ch])));
      });
    }
    // 下の行：v の行。子のある欄は自分の子（塗り・太字）、ほかは写した値（破線）
    label(T.row2 + T.ch / 2, nm(s.popped), true);
    sigma.forEach(function (ch, j) {
      var own = !!kidCol[ch];
      var copied = !own && s.from != null;
      cellRect(svg, h, cx(j), T.row2, T.cw, T.ch, own ? "kp-v-cell is-yes" : copied ? "kp-v-cell is-no" : "kp-v-cell", copied, "row:" + ch);
      svg.appendChild(h("text", {
        x: (cx(j) + (T.cw - 4) / 2).toFixed(1), y: T.row2 + T.ch / 2, class: "kp-v-text",
        style: "font-size:13px" + (own ? ";font-weight:700" : ""),
      }, nm(s.row[ch])));
    });
  }

  // 後半の下の段：テキスト・各文字を読んだ後の状態・出現の括弧・回数
  function renderText(svg, s, G, h) {
    var T = G.text;
    var c = G.c;
    var text = c.text;
    function cx(i) { return T.x + i * T.cw + 2; }
    function label(y, str) {
      svg.appendChild(h("text", {
        x: (T.x - 8).toFixed(1), y: y, class: "kp-v-text is-sub", style: "text-anchor:end;font-size:13px",
      }, str));
    }
    var curPos = s.phase === "read" ? s.pos - 1 : -1;
    // 出現の括弧（テキストの上）。このステップで見つけたものは太く
    var nowKey = {};
    s.found.forEach(function (f) { nowKey[f.pattern + ":" + f.start] = true; });
    s.all.forEach(function (f) {
      var k = f.pattern + ":" + f.start;
      var lv = T.level[k] || 0;
      var y = T.top - 5 - lv * 8;
      var x1 = cx(f.start) + 2, x2 = cx(f.end - 1) + T.cw - 8;
      var now = !!nowKey[k] || s.phase === "done";
      svg.appendChild(h("path", {
        d: "M" + x1.toFixed(1) + " " + (y + 4) + "V" + y + "H" + x2.toFixed(1) + "V" + (y + 4),
        style: "fill:none;stroke:" + (now ? "var(--md-accent-fg-color);stroke-width:2.5" : "var(--md-default-fg-color--light);stroke-width:1.5"),
        "data-occ": c.patterns[f.pattern] + "@" + f.start,
      }));
    });
    label(T.top + T.h / 2, "テキスト");
    for (var i = 0; i < text.length; i++) {
      var read = i < s.pos;
      var cls = i === curPos ? "kp-v-cell is-focus" : read ? "kp-v-cell" : "kp-v-cell is-no";
      cellRect(svg, h, cx(i), T.top, T.cw, T.h, cls, false, "text:" + i);
      svg.appendChild(h("text", {
        x: (cx(i) + (T.cw - 4) / 2).toFixed(1), y: T.top + T.h / 2, class: "kp-v-text" + (read ? "" : " is-dim"),
        style: "font-size:15px" + (i === curPos ? ";font-weight:700" : ""),
      }, text[i]));
    }
    label(T.state, "状態");
    s.trail.forEach(function (k, i2) {
      var isCur = i2 === curPos;
      svg.appendChild(h("text", {
        x: (cx(i2) + (T.cw - 4) / 2).toFixed(1), y: T.state, class: isCur ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: "font-size:13px", "data-trail": i2,
      }, k === "" ? "根" : k));
    });
    // パターンごとの回数。このステップで増えたものは太字
    var inc = {};
    s.found.forEach(function (f) { inc[f.pattern] = true; });
    var x = 8, y = T.count;
    var head = "出現回数：";
    svg.appendChild(h("text", { x: x, y: y, class: "kp-v-text is-sub", style: "text-anchor:start;font-size:13px" }, head));
    x += textWidth(head, 13);
    var startX = x;
    c.patterns.forEach(function (p, j) {
      var item = p + " " + s.counts[j] + (j < c.patterns.length - 1 ? "・" : "");
      var w = textWidth(item, 13);
      if (x + w > W - 8 && x > startX) {
        x = startX;
        y += 18;
      }
      svg.appendChild(h("text", {
        x: x.toFixed(1), y: y, class: inc[j] ? "kp-v-ptr is-b" : "kp-v-text", style: "text-anchor:start;font-size:13px",
        "data-count": p,
      }, item));
      x += w;
    });
  }

  function renderLegend(svg, s, G, h, front) {
    var y1 = G.legendTop + 8, y2 = G.legendTop + 28;
    var x = 8;
    function text(xx, yy, str) {
      svg.appendChild(h("text", { x: xx, y: yy, class: "kp-v-text is-sub", style: "text-anchor:start;font-size:12.5px" }, str));
      return Math.round(xx + textWidth(str, 12.5) + 14);
    }
    // 1 行目：終端・失敗リンク・根を指す失敗リンク
    svg.appendChild(h("circle", { cx: x + 8, cy: y1, r: 8, class: "kp-v-cell", style: "fill:none" }));
    svg.appendChild(h("circle", { cx: x + 8, cy: y1, r: 5, class: "kp-v-cell" }));
    x = text(x + 20, y1, "パターンの終端");
    svg.appendChild(h("path", { d: "M" + x + " " + y1 + "H" + (x + 20), style: LINK }));
    arrowHead(svg, h, [x + 27, y1], [1, 0], 8, "kp-v-mark is-b");
    x = text(x + 31, y1, "失敗リンク");
    svg.appendChild(h("path", { d: "M" + x + " " + y1 + "H" + (x + 12), style: "fill:none;stroke:var(--md-accent-fg-color);stroke-width:1.6;stroke-dasharray:4 3" }));
    arrowHead(svg, h, [x + 17, y1], [1, 0], 7, "kp-v-mark is-b");
    svg.appendChild(h("text", { x: x + 26, y: y1, class: "kp-v-text is-sub", style: "font-size:13px" }, "根"));
    text(x + 36, y1, "根を指す失敗リンク");
    // 2 行目：節点の塗り（前半と後半で意味が違う）
    x = 8;
    function dot(cls) {
      svg.appendChild(h("circle", { cx: x + 8, cy: y2, r: 7, class: "kp-v-cell " + cls, style: cls === "is-yes" ? "stroke-width:2.8" : null }));
    }
    if (front) {
      dot("is-sentinel");
      x = text(x + 20, y2, "リンク未定");
      dot("is-yes");
      x = text(x + 20, y2, "取り出し済み");
      dot("is-answer");
      x = text(x + 20, y2, "取り出した節点");
      svg.appendChild(h("circle", { cx: x + 8, cy: y2, r: 7, class: "kp-v-cell is-focus", style: "fill:none", "stroke-dasharray": "3 2" }));
      text(x + 20, y2, "写す元");
    } else {
      dot("is-answer");
      x = text(x + 20, y2, "いまの状態");
      dot("is-yes");
      x = text(x + 20, y2, "たどる連鎖");
      svg.appendChild(h("path", { d: "M" + x + " " + y2 + "H" + (x + 18), style: MOVE }));
      x = text(x + 24, y2, "今回の移動");
      svg.appendChild(h("path", {
        d: "M" + x + " " + (y2 + 4) + "V" + (y2 - 3) + "H" + (x + 18) + "V" + (y2 + 4),
        style: "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.5",
      }));
      text(x + 24, y2, "出現");
    }
  }

  return {
    title: "Aho-Corasick 法：BFS 順に失敗リンクと遷移表を作り、テキストを流して出現を見つける",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

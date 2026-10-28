/*
 * 動く図：最大流で、残余グラフの増加路に流すたびに順辺の容量が減って逆辺の容量が増え、
 * 逆辺を通ると先に流した分を押し戻せる様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="max-flow-residual"
 *        data-config='{"n": 4, "labels": ["s", "a", "b", "t"], "edges": [[0, 1, 1], [0, 2, 1], [1, 3, 1], [2, 3, 1]], "s": 0, "t": 3}'></div>
 * config：
 *   n      … 頂点の数（2〜8）。頂点は 0〜n−1
 *   edges  … 有向の辺 [u, v, c] の配列（0〜12 本）。c は容量で 1〜99 の整数。自己ループと、同じ 2 頂点を結ぶ 2 本目の辺
 *            （逆向きも。順辺と逆辺の組が重なるため）は不可
 *   s, t   … 始点と終点（省略時 0 と n−1。s ≠ t）
 *   paths  … 流す増加路を、頂点の列 [s, …, t] で順に並べた配列（省略可。20 本まで）。各道は同じ頂点を 2 度通らず、
 *            その時点の残余グラフで容量が正の辺だけを通ること。渡した道を流し終えても増加路が残れば、続きは DFS で探す
 *   labels … 頂点の名前（省略可。n 個の 1〜3 文字の文字列）
 *   pos    … 頂点の位置 [x, y] の配列（省略可。単位は任意で、枠に合わせて拡大・縮小する）。
 *            省略時は s を左端、t を右端に置き、ほかの頂点を番号の順に上の弧（左から）、続けて下の弧（左から）に並べる
 *
 * 残余グラフ：元の辺 u → v（容量 c、流量 f）ごとに、順辺 u → v（容量 c − f、実線）と逆辺 v → u（容量 f、破線）を、
 * それぞれ進む向きの左側にずらして並べる。容量が 0 の辺は薄く描く。
 * DFS：s から、各頂点で元の辺の番号の順に（ACL の mf_graph が辺を持つ順と同じく、順辺も逆辺も足した順に）見て、
 * 容量が正で未訪問の頂点へ進み、最初に t に着いた道を増加路にする。
 * ステップ：最初に元のグラフ。増加路 1 本ごとに「道を選び、最小の容量 d を示す」「d を流す」の 2 つ。
 * 最後に、残余グラフで s から届く頂点を塗り、そこから外へ出る元の辺（最小カット）に印を付ける。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/max-flow-residual.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("max-flow-residual", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_M = 12;
  var MAX_C = 99;
  var MAX_PATHS = 20;
  var MAX_AUG = 99; // 増加路の本数の上限（状態は 1 + 2 × 99 + 1 = 200 まで）

  // ---------- 描画の寸法（validate が頂点の間隔を確かめるのにも使う） ----------
  var W = 440;
  var R = 17;
  var OFF = 5; // 順辺と逆辺を、元の辺の中心線から左右にずらす幅
  var INSET = Math.sqrt(R * R - OFF * OFF) + 3; // 頂点の中心から、ずらした線の端（矢じりの先）まで
  var AH = 9; // 矢じりの長さ
  var MX = 60; // 頂点の中心と左右の端の間（端の列の縦の辺でも、外側の「99→98」が枠に収まる幅）
  var GH_MAX = 150; // 頂点の中心が並ぶ高さの上限
  var RX = 2.2; // 既定の配置の横の半径（縦の半径 1 に対して）
  var TOP = 30; // 枠の上端から頂点の中心の最上段まで
  var BELOW = 36; // 頂点の中心の最下段から下の行まで
  var MIN_DIST = 60; // 頂点の中心どうしの間隔の下限（辺と数を描く場所）
  var GAP = 4; // 線から数の文字まで
  var FS = 14; // 辺の数の文字の大きさ
  var LABEL_W = 70; // 下の行の左の見出しの幅
  var ROW_H = 24;
  var ROWS = 4; // 増加路・流す量・流量・カット（カットは最後だけ）
  var LEGEND_GAP = 14;
  var LEGEND_H = 48;
  var HALO = "paint-order: stroke; stroke: var(--md-default-bg-color); stroke-width: 4px";

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 2 || n > MAX_N) throw new Error("n は 2〜" + MAX_N + " の整数にする");
    var s = config.s == null ? 0 : config.s;
    if (!isInt(s) || s < 0 || s >= n) throw new Error("s は 0〜" + (n - 1) + " の整数にする");
    var t = config.t == null ? n - 1 : config.t;
    if (!isInt(t) || t < 0 || t >= n) throw new Error("t は 0〜" + (n - 1) + " の整数にする");
    if (s === t) throw new Error("s と t は別の頂点にする");
    var es = config.edges == null ? [] : config.edges;
    if (!Array.isArray(es) || es.length > MAX_M) throw new Error("edges は 0〜" + MAX_M + " 本の辺 [u, v, c] の配列にする");
    var edges = [];
    var seen = Object.create(null);
    for (var i = 0; i < es.length; i++) {
      var e = es[i];
      if (!Array.isArray(e) || e.length !== 3) throw new Error("edges の各辺は [u, v, c] の形にする");
      var u = e[0], v = e[1], cap = e[2];
      if (!isInt(u) || !isInt(v) || u < 0 || v < 0 || u >= n || v >= n) {
        throw new Error("辺の端は 0〜" + (n - 1) + " の整数にする");
      }
      if (u === v) throw new Error("自己ループ（" + u + " から " + u + " への辺）は描けない");
      if (!isInt(cap) || cap < 1 || cap > MAX_C) throw new Error("辺の容量は 1〜" + MAX_C + " の整数にする");
      var key = Math.min(u, v) + "-" + Math.max(u, v);
      if (seen[key]) {
        throw new Error("同じ 2 頂点を結ぶ辺は 1 本にする（" + u + " と " + v + "。逆向きの辺も、順辺と逆辺が重なるので不可）");
      }
      seen[key] = true;
      edges.push([u, v, cap]);
    }
    var labels = [];
    if (config.labels != null) {
      if (!Array.isArray(config.labels) || config.labels.length !== n) throw new Error("labels は n 個の文字列にする");
      for (var j = 0; j < n; j++) {
        var lb = config.labels[j];
        if (typeof lb !== "string" || lb.length < 1 || lb.length > 3) throw new Error("labels の各要素は 1〜3 文字にする");
        if (labels.indexOf(lb) >= 0) throw new Error("labels に同じ名前がある：" + lb);
        labels.push(lb);
      }
    } else {
      for (var k = 0; k < n; k++) labels.push(String(k));
    }
    var pos = null;
    if (config.pos != null) {
      if (!Array.isArray(config.pos) || config.pos.length !== n) throw new Error("pos は n 個の [x, y] の配列にする");
      pos = [];
      for (var q = 0; q < n; q++) {
        var p = config.pos[q];
        if (!Array.isArray(p) || p.length !== 2 || typeof p[0] !== "number" || typeof p[1] !== "number" ||
            !isFinite(p[0]) || !isFinite(p[1])) {
          throw new Error("pos の各要素は数の組 [x, y] にする");
        }
        for (var r = 0; r < q; r++) {
          if (pos[r][0] === p[0] && pos[r][1] === p[1]) throw new Error("pos に同じ位置の頂点がある");
        }
        pos.push([p[0], p[1]]);
      }
    }
    var ps = config.paths == null ? [] : config.paths;
    if (!Array.isArray(ps) || ps.length > MAX_PATHS) {
      throw new Error("paths は 0〜" + MAX_PATHS + " 本の道（頂点の列）の配列にする");
    }
    var paths = [];
    for (var a = 0; a < ps.length; a++) {
      var path = ps[a];
      var head = "paths の " + (a + 1) + " 本目：";
      if (!Array.isArray(path) || path.length < 2) throw new Error(head + "頂点の列 [s, …, t] にする");
      var used = Object.create(null);
      for (var b = 0; b < path.length; b++) {
        if (!isInt(path[b]) || path[b] < 0 || path[b] >= n) throw new Error(head + "頂点は 0〜" + (n - 1) + " の整数にする");
        if (used[path[b]]) throw new Error(head + "同じ頂点を 2 度通る");
        used[path[b]] = true;
      }
      if (path[0] !== s || path[path.length - 1] !== t) {
        throw new Error(head + labels[s] + " から始めて " + labels[t] + " で終える");
      }
      paths.push(path.slice());
    }
    var c = {
      named: config.labels != null, n: n, s: s, t: t, edges: edges, labels: labels, pos: pos, paths: paths,
    };
    var pts = layout(c).pts;
    for (var x = 0; x < n; x++) {
      for (var y = 0; y < x; y++) {
        var dx = pts[x][0] - pts[y][0], dy = pts[x][1] - pts[y][1];
        if (Math.sqrt(dx * dx + dy * dy) < MIN_DIST) {
          throw new Error("頂点 " + labels[y] + " と " + labels[x] + " が近すぎて、辺と容量を描けない。pos を広げる");
        }
      }
    }
    return c;
  }

  // 頂点の組 x → y を通る残余グラフの辺。元の辺 x → y なら順辺（容量 c − f）、元の辺 y → x なら逆辺（容量 f）
  function arcBetween(c, flow, x, y) {
    for (var k = 0; k < c.edges.length; k++) {
      var e = c.edges[k];
      if (e[0] === x && e[1] === y) return { edge: k, rev: false, from: x, to: y, cap: e[2] - flow[k] };
      if (e[0] === y && e[1] === x) return { edge: k, rev: true, from: x, to: y, cap: flow[k] };
    }
    return null;
  }

  // paths で渡された道を、今の残余グラフの辺の列にする
  function givenArcs(c, flow, path, idx) {
    var L = c.labels;
    var head = "paths の " + (idx + 1) + " 本目：";
    var arcs = [];
    for (var i = 0; i + 1 < path.length; i++) {
      var a = arcBetween(c, flow, path[i], path[i + 1]);
      if (!a) throw new Error(head + L[path[i]] + " と " + L[path[i + 1]] + " を結ぶ辺がない");
      if (a.cap <= 0) {
        throw new Error(head + L[path[i]] + " → " + L[path[i + 1]] + " の残りの容量が 0 なので、増加路にならない");
      }
      arcs.push(a);
    }
    return arcs;
  }

  // 辺の番号の順に見る DFS で増加路を探す。なければ null
  function findPath(c, flow) {
    var seen = [];
    for (var i = 0; i < c.n; i++) seen.push(false);
    var arcs = [];
    function dfs(v) {
      if (v === c.t) return true;
      seen[v] = true;
      for (var k = 0; k < c.edges.length; k++) {
        var e = c.edges[k];
        var a = e[0] === v ? { edge: k, rev: false, from: v, to: e[1], cap: e[2] - flow[k] }
          : e[1] === v ? { edge: k, rev: true, from: v, to: e[0], cap: flow[k] } : null;
        if (!a || a.cap <= 0 || seen[a.to]) continue;
        arcs.push(a);
        if (dfs(a.to)) return true;
        arcs.pop();
      }
      return false;
    }
    return dfs(c.s) ? arcs : null;
  }

  // 残余グラフで、容量が正の辺だけをたどって s から届く頂点
  function reachable(c, flow) {
    var reach = [];
    for (var i = 0; i < c.n; i++) reach.push(false);
    reach[c.s] = true;
    var stack = [c.s];
    while (stack.length > 0) {
      var v = stack.pop();
      for (var k = 0; k < c.edges.length; k++) {
        var e = c.edges[k];
        var to = e[0] === v && e[2] - flow[k] > 0 ? e[1] : e[1] === v && flow[k] > 0 ? e[0] : -1;
        if (to >= 0 && !reach[to]) {
          reach[to] = true;
          stack.push(to);
        }
      }
    }
    return reach;
  }

  // 各ステップの状態：
  //   phase（init / path / push / end）、flow（元の辺ごとの流量。そのステップの後）、total（流量）、
  //   path（増加路の頂点の列）・arcs（増加路の辺 {edge, rev（逆辺か）, from, to, cap（流す前の残りの容量）}）・d（流す量）・
  //   auto（DFS で見つけた道か）… path と push のステップだけ。before（流す前の flow）… push のステップだけ、
  //   reach（s から届く頂点）・cut（届く側から外へ出る元の辺の番号）・back（外から届く側へ入る元の辺の番号）… end だけ、
  //   last（最後の状態か）、caption
  function states(config) {
    var c = validate(config);
    var L = c.labels;
    var m = c.edges.length;
    var flow = [];
    for (var i = 0; i < m; i++) flow.push(0);
    var total = 0;
    var out = [];
    function arcText(a) {
      return L[a.from] + " → " + L[a.to];
    }
    function pairText(a) {
      return L[a.to] + " → " + L[a.from];
    }
    function edgeText(k) {
      return L[c.edges[k][0]] + " → " + L[c.edges[k][1]];
    }
    function copyArcs(arcs) {
      return arcs.map(function (a) { return { edge: a.edge, rev: a.rev, from: a.from, to: a.to, cap: a.cap }; });
    }
    function snap(extra) {
      var st = {
        phase: "", flow: flow.slice(), total: total,
        path: null, arcs: null, d: null, auto: false, before: null,
        reach: null, cut: null, back: null, last: false, caption: "",
      };
      Object.keys(extra).forEach(function (key) { st[key] = extra[key]; });
      return st;
    }

    out.push(snap({
      phase: "init",
      caption: "始点 " + L[c.s] + " から終点 " + L[c.t] + " へ流す。" + (m === 0 ? "辺はない。"
        : "各辺に添えた数は残りの容量で、はじめは容量そのものである。" +
          "逆辺（破線）は流した分を押し戻すための辺で、まだ容量 0 なので薄く描く。"),
    }));

    var given = 0, aug = 0;
    for (;;) {
      var arcs, auto;
      if (given < c.paths.length) {
        arcs = givenArcs(c, flow, c.paths[given], given);
        given++;
        auto = false;
      } else {
        arcs = findPath(c, flow);
        auto = true;
        if (!arcs) break;
      }
      if (++aug > MAX_AUG) throw new Error("増加路が " + MAX_AUG + " 本を超えた。容量を小さくする");
      var d = Infinity;
      arcs.forEach(function (a) { d = Math.min(d, a.cap); });
      var verts = [c.s].concat(arcs.map(function (a) { return a.to; }));
      var pathText = verts.map(function (v) { return L[v]; }).join(" → ");
      var revs = arcs.filter(function (a) { return a.rev; });

      var cap = auto ? "残余グラフを辺の並びの順に DFS でたどり、増加路 " + pathText + " を見つける。"
        : "増加路 " + pathText + " を選ぶ。";
      revs.forEach(function (a) {
        cap += arcText(a) + " は逆辺で、" + pairText(a) + " に流している " + a.cap + " まで押し戻せる。";
      });
      cap += "道の上の残りの容量は " + arcs.map(function (a) { return a.cap; }).join("、") + " で、" +
        (arcs.length > 1 ? "最小の " : "") + "d = " + d + " だけ流せる。";
      out.push(snap({ phase: "path", path: verts, arcs: copyArcs(arcs), d: d, auto: auto, caption: cap }));

      var before = flow.slice();
      arcs.forEach(function (a) { flow[a.edge] += a.rev ? -d : d; });
      var prevTotal = total;
      total += d;
      var passed = arcs.map(arcText).join("・"), paired = arcs.map(pairText).join("・");
      cap = "d = " + d + " を流す。" + (revs.length === 0
        ? "通った順辺 " + passed + " の容量が " + d + " 減り、その逆辺 " + paired + " の容量が " + d + " 増える。"
        : "通った辺 " + passed + " の容量が " + d + " 減り、逆向きの辺 " + paired + " の容量が " + d + " 増える。");
      revs.forEach(function (a) {
        cap += arcText(a) + " は逆辺なので、元の辺 " + pairText(a) + " の流量が " + before[a.edge] + " から " +
          flow[a.edge] + " に減る（押し戻す）。";
      });
      cap += "流量は " + prevTotal + " + " + d + " = " + total + " になる。";
      out.push(snap({
        phase: "push", path: verts, arcs: copyArcs(arcs), d: d, auto: auto, before: before, caption: cap,
      }));
    }

    var reach = reachable(c, flow);
    var cut = [], back = [];
    c.edges.forEach(function (e, k) {
      if (reach[e[0]] && !reach[e[1]]) cut.push(k);
      if (!reach[e[0]] && reach[e[1]]) back.push(k);
    });
    var inS = [];
    for (var v = 0; v < c.n; v++) if (reach[v]) inS.push(L[v]);
    var caps = cut.map(function (k) { return c.edges[k][2]; });
    var sum = caps.reduce(function (x, y) { return x + y; }, 0);
    var cap2 = L[c.s] + " から " + L[c.t] + " への増加路は" + (aug === 0 ? "、はじめからない。" : "もうない。") +
      "残余グラフで容量が正の辺だけをたどって " + L[c.s] + " から届く頂点（塗った頂点）は " +
      (inS.length === 1 ? L[c.s] + " だけで" : inS.join("・") + " で") + "、" + L[c.t] + " には届かない。";
    if (cut.length === 0) {
      cap2 += "塗った頂点から外へ出る元の辺はなく、その容量の和は 0 である。";
    } else if (cut.length === 1) {
      cap2 += "塗った頂点から外へ出る元の辺 " + edgeText(cut[0]) + " は容量いっぱいに流れていて、その容量 " + sum +
        " が今の流量に等しい。";
    } else {
      cap2 += "塗った頂点から外へ出る元の辺 " + cut.map(edgeText).join("・") + " はどれも容量いっぱいに流れていて、" +
        "容量の和 " + caps.join(" + ") + " = " + sum + " が今の流量に等しい。";
    }
    if (back.length > 0) cap2 += "外から塗った頂点へ入る元の辺 " + back.map(edgeText).join("・") + " の流量は 0 である。";
    cap2 += "これが最小カットで、流量 " + total + " が最大である。";
    out.push(snap({ phase: "end", reach: reach, cut: cut, back: back, last: true, caption: cap2 }));
    return out;
  }

  // ---------- 描画 ----------
  function layout(c) {
    var raw = c.pos;
    if (!raw) {
      raw = [];
      for (var i = 0; i < c.n; i++) raw.push(null);
      raw[c.s] = [-RX, 0];
      raw[c.t] = [RX, 0];
      var others = [];
      for (var v = 0; v < c.n; v++) if (v !== c.s && v !== c.t) others.push(v);
      var top = Math.ceil(others.length / 2), bot = others.length - top;
      others.forEach(function (u, k) {
        var th = k < top ? Math.PI - (Math.PI * (k + 1)) / (top + 1) : Math.PI + (Math.PI * (k - top + 1)) / (bot + 1);
        raw[u] = [RX * Math.cos(th), -Math.sin(th)];
      });
    }
    var x0 = Infinity, x1 = -Infinity, y0 = Infinity, y1 = -Infinity;
    raw.forEach(function (p) {
      x0 = Math.min(x0, p[0]); x1 = Math.max(x1, p[0]);
      y0 = Math.min(y0, p[1]); y1 = Math.max(y1, p[1]);
    });
    var bw = x1 - x0, bh = y1 - y0;
    var sx = bw > 0 ? (W - 2 * MX) / bw : Infinity;
    var sy = bh > 0 ? GH_MAX / bh : Infinity;
    var sc = Math.min(sx, sy);
    if (sc === Infinity) sc = 1;
    var gh = bh * sc;
    var ox = (W - bw * sc) / 2;
    return {
      gh: gh,
      pts: raw.map(function (p) { return [ox + (p[0] - x0) * sc, TOP + (p[1] - y0) * sc]; }),
    };
  }

  function dims(c) {
    var g = layout(c);
    var rowTop = TOP + g.gh + BELOW;
    var legendTop = rowTop + ROWS * ROW_H + LEGEND_GAP;
    return { g: g, rowTop: rowTop, legendTop: legendTop, height: legendTop + LEGEND_H };
  }

  function viewBox(config) {
    var c = validate(config);
    return "0 0 " + W + " " + Math.ceil(dims(c).height);
  }

  // 文字の幅の見積もり（数字・英字・記号は 0.6 字、空白は 0.3 字、矢印・かな・漢字は 1 字）
  function textW(str, size) {
    var w = 0;
    for (var i = 0; i < str.length; i++) {
      var ch = str.charAt(i);
      w += /[0-9A-Za-z.,()=+\-]/.test(ch) ? 0.6 : ch === " " ? 0.3 : 1;
    }
    return w * size;
  }

  // 頂点 pa から pb へ向かう辺を、進む向きの左側に OFF だけずらした線
  function arcGeom(pa, pb) {
    var dx = pb[0] - pa[0], dy = pb[1] - pa[1];
    var len = Math.sqrt(dx * dx + dy * dy);
    var ux = dx / len, uy = dy / len;
    var nx = uy, ny = -ux; // 進む向きの左（画面の y は下向き）
    return {
      len: len, ux: ux, uy: uy, nx: nx, ny: ny,
      x1: pa[0] + ux * INSET + nx * OFF, y1: pa[1] + uy * INSET + ny * OFF,
      tx: pb[0] - ux * INSET + nx * OFF, ty: pb[1] - uy * INSET + ny * OFF, // 矢じりの先
      mx: (pa[0] + pb[0]) / 2 + nx * OFF, my: (pa[1] + pb[1]) / 2 + ny * OFF,
    };
  }

  function render(svg, s, config, h) {
    var c = validate(config);
    var L = c.labels;
    var g = layout(c);
    var pts = g.pts;
    var rowTop = TOP + g.gh + BELOW;
    var onPath = Object.create(null);
    var pushed = Object.create(null);
    if (s.arcs) {
      s.arcs.forEach(function (a) {
        if (s.phase === "path") onPath[a.edge + (a.rev ? "r" : "f")] = true;
        if (s.phase === "push") pushed[a.edge] = true;
      });
    }

    // 残余グラフの辺：元の辺ごとに順辺（f）と逆辺（r）
    var items = [];
    c.edges.forEach(function (e, k) {
      [false, true].forEach(function (rev) {
        var key = k + (rev ? "r" : "f");
        var rest = rev ? s.flow[k] : e[2] - s.flow[k];
        var text = String(rest);
        if (pushed[k]) text = (rev ? s.before[k] : e[2] - s.before[k]) + "→" + rest;
        items.push({
          key: key, k: k, rev: rev, from: rev ? e[1] : e[0], to: rev ? e[0] : e[1], rest: rest, text: text,
          focus: !!onPath[key], pushed: !!pushed[k], widest: e[2] + "→" + e[2],
          g: rev ? arcGeom(pts[e[1]], pts[e[0]]) : arcGeom(pts[e[0]], pts[e[1]]),
        });
      });
    });
    // 薄い辺 → ふつうの辺 → 増加路の順に描き、強調する線を上に重ねる
    function rank(it) {
      return it.focus ? 2 : it.rest > 0 ? 1 : 0;
    }
    var order = items.slice().sort(function (a, b) {
      return rank(a) - rank(b) || a.k - b.k || (a.rev ? 1 : 0) - (b.rev ? 1 : 0);
    });

    // 線と矢じり：順辺は実線、逆辺は破線。容量 0 は薄く、増加路は太く
    order.forEach(function (it) {
      var gm = it.g;
      var zero = it.rest === 0 && !it.focus;
      svg.appendChild(h("line", {
        x1: gm.x1, y1: gm.y1, x2: gm.tx - gm.ux * (AH - 1), y2: gm.ty - gm.uy * (AH - 1),
        class: it.focus ? "kp-v-cell is-focus" : zero ? "kp-v-cell is-no" : "kp-v-cell",
        "stroke-dasharray": it.rev ? (it.focus ? "7 4" : "5 4") : null,
        style: it.focus ? null : zero ? "stroke-width: 1.2" : "stroke-width: 2",
        "data-arc": it.key,
      }));
      var aw = it.focus ? 5.5 : 4.5;
      var bx = gm.tx - gm.ux * AH, by = gm.ty - gm.uy * AH;
      svg.appendChild(h("path", {
        d: "M" + gm.tx + " " + gm.ty + "L" + (bx + gm.nx * aw) + " " + (by + gm.ny * aw) +
          "L" + (bx - gm.nx * aw) + " " + (by - gm.ny * aw) + "z",
        class: it.focus ? "kp-v-mark is-focus" : "kp-v-mark",
        style: zero ? "fill: var(--md-default-fg-color--lighter)" : null,
        "data-head": it.key,
      }));
    });

    // 最小カット：届く側から外へ出る元の辺に、届く側の寄りで横切る印
    if (s.phase === "end") {
      s.cut.forEach(function (k) {
        var e = c.edges[k];
        var gm = arcGeom(pts[e[0]], pts[e[1]]);
        var at = Math.max(INSET + 8, Math.min(0.3 * gm.len, gm.len / 2 - 12));
        var px = pts[e[0]][0] + gm.ux * at, py = pts[e[0]][1] + gm.uy * at;
        svg.appendChild(h("line", {
          x1: px + gm.nx * 13, y1: py + gm.ny * 13, x2: px - gm.nx * 13, y2: py - gm.ny * 13,
          class: "kp-v-cell is-focus", style: "stroke-linecap: round", "data-cut": k,
        }));
      });
    }

    // 頂点：最後のステップで、s から届く頂点を塗る
    for (var v = 0; v < c.n; v++) {
      var on = !!(s.reach && s.reach[v]);
      svg.appendChild(h("circle", {
        cx: pts[v][0], cy: pts[v][1], r: R, class: on ? "kp-v-cell is-answer" : "kp-v-cell", "data-vertex": v,
      }));
      svg.appendChild(h("text", { x: pts[v][0], y: pts[v][1], class: on ? "kp-v-text is-on-answer" : "kp-v-text" }, L[v]));
    }

    // 辺の数：線の外側に置く。左右に寄る辺は文字の端を線にそろえ、ステップで文字の幅が変わっても動かないようにする
    items.forEach(function (it) {
      var gm = it.g;
      var anchor = gm.nx > 0.35 ? "start" : gm.nx < -0.35 ? "end" : "middle";
      var dist = GAP + (Math.abs(gm.ny) * FS) / 2 + (anchor === "middle" ? (Math.abs(gm.nx) * textW(it.widest, FS)) / 2 : 0);
      var x = gm.mx + gm.nx * dist, y = gm.my + gm.ny * dist;
      var tw = textW(it.text, FS);
      if (anchor === "start") x = Math.min(x, W - 2 - tw);
      else if (anchor === "end") x = Math.max(x, 2 + tw);
      else x = Math.max(2 + tw / 2, Math.min(W - 2 - tw / 2, x));
      svg.appendChild(h("text", {
        x: x, y: y,
        class: it.focus || it.pushed ? "kp-v-ptr is-focus" : it.rest > 0 ? "kp-v-text" : "kp-v-text is-dim",
        style: (anchor !== "middle" ? "text-anchor: " + anchor + "; " : "") + "font-size: " + FS + "px; " + HALO,
        "data-cap": it.key,
      }, it.text));
    });

    // 下の行：増加路・流す量・流量（最後はカットも）
    function row(i, name, head, text, focus) {
      var y = rowTop + i * ROW_H + ROW_H / 2;
      svg.appendChild(h("text", {
        x: 6, y: y, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px",
      }, head));
      svg.appendChild(h("text", {
        x: LABEL_W, y: y, class: focus ? "kp-v-ptr is-focus" : "kp-v-text",
        style: "text-anchor: start; font-size: 14px", "data-row": name,
      }, text));
    }
    var pathText = s.path ? s.path.map(function (u) { return L[u]; }).join(" → ") : "";
    if (s.phase === "init") {
      row(0, "path", "増加路", "—", false);
      row(1, "d", "流す量", "—", false);
      row(2, "total", "流量", "0", false);
    } else if (s.phase === "path") {
      row(0, "path", "増加路", pathText, true);
      row(1, "d", "流す量", s.arcs.length > 1
        ? "d = min(" + s.arcs.map(function (a) { return a.cap; }).join(", ") + ") = " + s.d : "d = " + s.d, true);
      row(2, "total", "流量", String(s.total), false);
    } else if (s.phase === "push") {
      row(0, "path", "増加路", pathText, false);
      row(1, "d", "流す量", "d = " + s.d, false);
      row(2, "total", "流量", s.total - s.d + " + " + s.d + " = " + s.total, true);
    } else {
      row(0, "path", "増加路", "なし（" + L[c.t] + " に届かない）", true);
      row(1, "d", "流す量", "—", false);
      row(2, "total", "流量", s.total + "（最大）", true);
      var cutCaps = s.cut.map(function (k) { return c.edges[k][2]; });
      var cutSum = cutCaps.reduce(function (x, y) { return x + y; }, 0);
      var cutText = s.cut.length === 0 ? "出る辺なし（容量の和 0）"
        : s.cut.map(function (k) { return L[c.edges[k][0]] + " → " + L[c.edges[k][1]]; }).join("・") +
          "（容量の和 " + cutSum + "）";
      if (LABEL_W + textW(cutText, 14) > W - 4) cutText = s.cut.length + " 本の辺（容量の和 " + cutSum + "）";
      row(3, "cut", "カット", cutText, true);
    }

    // 凡例
    var ly = dims(c).legendTop;
    var lx = 6;
    function legendText(y, text) {
      svg.appendChild(h("text", {
        x: lx, y: y, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px",
      }, text));
      lx += textW(text, 13) + 16;
    }
    function legendLine(y, attrs, text) {
      var a = { x1: lx, y1: y, x2: lx + 22, y2: y };
      Object.keys(attrs).forEach(function (key) { a[key] = attrs[key]; });
      svg.appendChild(h("line", a));
      lx += 27;
      legendText(y, text);
    }
    var l1 = ly + 10, l2 = ly + 34;
    legendLine(l1, { class: "kp-v-cell", style: "stroke-width: 2" }, "順辺（残りの容量）");
    legendLine(l1, { class: "kp-v-cell", style: "stroke-width: 2", "stroke-dasharray": "5 4" }, "逆辺（押し戻せる量）");
    legendLine(l1, { class: "kp-v-cell is-no", style: "stroke-width: 1.2" }, "容量 0");
    lx = 6;
    legendLine(l2, { class: "kp-v-cell is-focus" }, "増加路");
    svg.appendChild(h("circle", { cx: lx + 8, cy: l2, r: 8, class: "kp-v-cell is-answer" }));
    lx += 21;
    legendText(l2, (c.named ? L[c.s] + " " : "始点") + "から届く頂点");
    svg.appendChild(h("line", { x1: lx, y1: l2, x2: lx + 22, y2: l2, class: "kp-v-cell", style: "stroke-width: 2" }));
    svg.appendChild(h("line", {
      x1: lx + 11, y1: l2 - 9, x2: lx + 11, y2: l2 + 9, class: "kp-v-cell is-focus", style: "stroke-linecap: round",
    }));
    lx += 27;
    legendText(l2, "カットの辺");
  }

  return {
    title: "最大流で、増加路に流すたびに残余グラフの順辺と逆辺の容量が変わる様子",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

/*
 * 動く図：幅優先探索（BFS）で、キューの中身と距離の層が育つ様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="bfs-layers"
 *        data-config='{"labels": ["s", "a", "b"], "edges": [[0, 1], [1, 2]], "source": 0}'></div>
 * config：
 *   labels … 頂点の名前（1〜8 個の 1〜3 文字の文字列）。頂点の数 n はこの長さ
 *   n      … labels を省くときの頂点の数（1〜8）。名前は 0〜n−1 になる（caption では「頂点 0」と書く）。両方あるときは一致させる
 *            距離の数と紛れないよう、本文では labels を書くのがよい
 *   edges  … 無向の辺 [u, v] の配列（0〜14 本）。自己ループと、同じ 2 頂点を結ぶ 2 本目の辺は不可
 *   source … 始点（省略時 0）
 *
 * 本文のコード片と同じ書き方で動かす：dist を −1 で初期化し、始点に 0 を書いて push する。
 * 先頭の u を取り出し、u の隣を辺の並びの順に見て、dist が −1 のものだけに dist[u] + 1 と親 u を書いて末尾に push する
 * （印は push のときに付ける）。1 回の取り出しを 1 ステップにし、最初に初期状態、最後にまとめの状態を置く。
 *
 * 頂点は最後に決まる距離ごとの列（層）に並べ、列の中は見つけた順に上から置く。始点から届かない頂点は右端の列に置く。
 * 無向グラフでは辺は同じ層か隣の層の間にしかないので、隣の列への辺はほかの頂点の上を通らない。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/bfs-layers.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("bfs-layers", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_M = 14;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n;
    var labels = [];
    if (config.labels != null) {
      if (!Array.isArray(config.labels) || config.labels.length < 1 || config.labels.length > MAX_N) {
        throw new Error("labels は 1〜" + MAX_N + " 個の文字列の配列にする");
      }
      n = config.labels.length;
      for (var j = 0; j < n; j++) {
        var lb = config.labels[j];
        if (typeof lb !== "string" || lb.length < 1 || lb.length > 3) throw new Error("labels の各要素は 1〜3 文字にする");
        if (labels.indexOf(lb) >= 0) throw new Error("labels に同じ名前がある：" + lb);
        labels.push(lb);
      }
      if (config.n != null && config.n !== n) throw new Error("n と labels の個数が違う");
    } else {
      n = config.n;
      if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする（または labels を書く）");
      for (var k = 0; k < n; k++) labels.push(String(k));
    }
    var source = config.source == null ? 0 : config.source;
    if (!isInt(source) || source < 0 || source >= n) throw new Error("source は 0〜" + (n - 1) + " の整数にする");
    var es = config.edges == null ? [] : config.edges;
    if (!Array.isArray(es) || es.length > MAX_M) throw new Error("edges は 0〜" + MAX_M + " 本の辺 [u, v] の配列にする");
    var edges = [];
    var seen = Object.create(null);
    for (var i = 0; i < es.length; i++) {
      var e = es[i];
      if (!Array.isArray(e) || e.length !== 2) throw new Error("edges の各辺は [u, v] の形にする");
      var u = e[0], v = e[1];
      if (!isInt(u) || !isInt(v) || u < 0 || v < 0 || u >= n || v >= n) {
        throw new Error("辺の端は 0〜" + (n - 1) + " の整数にする");
      }
      if (u === v) throw new Error("自己ループ（" + labels[u] + " から " + labels[u] + " への辺）は描けない");
      var key = Math.min(u, v) + "-" + Math.max(u, v);
      if (seen[key]) throw new Error("同じ 2 頂点を結ぶ辺は 1 本にする（" + labels[u] + " と " + labels[v] + "）");
      seen[key] = true;
      edges.push([u, v]);
    }
    // caption で使う名前：labels を省いたときは距離の数と紛れないよう「頂点 k」と書く
    var capNames = config.labels != null ? labels : labels.map(function (x) { return "頂点 " + x; });
    return { n: n, labels: labels, capNames: capNames, source: source, edges: edges };
  }

  // 頂点 v の隣 [to, 辺の番号] を辺の並びの順に
  function adjacency(c) {
    var adj = [];
    for (var i = 0; i < c.n; i++) adj.push([]);
    c.edges.forEach(function (e, k) {
      adj[e[0]].push([e[1], k]);
      adj[e[1]].push([e[0], k]);
    });
    return adj;
  }

  // 名前の列を「・」でつなぐ
  function names(L, vs) {
    return vs.map(function (v) { return L[v]; }).join("・");
  }

  // キューの中の距離の種類を言う
  function queueText(dist, queue) {
    if (queue.length === 0) return "キューは空になった。";
    var ds = queue.map(function (v) { return dist[v]; });
    var kinds = [];
    ds.forEach(function (d) { if (kinds.indexOf(d) < 0) kinds.push(d); });
    return "キューの中の距離は前から " + ds.join(", ") + " で、" +
      (kinds.length === 1 ? kinds[0] + " の 1 種類である。" : kinds[0] + " と " + kinds[1] + " の 2 種類である。");
  }

  // 各ステップの状態：
  //   phase（init / pop / done）、dist（−1 は未発見）、par（親。なければ −1）、parEdge（親への辺の番号。なければ −1）、
  //   queue（処理の後のキュー。先頭から）、popped（取り出した頂点。なければ null）、done（取り出し済みか）、
  //   pushed（このステップで見つけて push した頂点）、scanned（このステップで見た辺 {to, edge, found}）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var L = c.capNames;
    var adj = adjacency(c);
    var dist = [], par = [], parEdge = [], done = [];
    for (var i = 0; i < n; i++) {
      dist.push(-1);
      par.push(-1);
      parEdge.push(-1);
      done.push(false);
    }
    dist[c.source] = 0;
    var queue = [c.source];
    var out = [];
    function snap(extra) {
      var s = {
        dist: dist.slice(), par: par.slice(), parEdge: parEdge.slice(), queue: queue.slice(), done: done.slice(),
        popped: null, pushed: [], scanned: [],
      };
      Object.keys(extra).forEach(function (k) { s[k] = extra[k]; });
      return s;
    }

    out.push(snap({
      phase: "init",
      caption: "dist をすべて −1（まだ見つけていない）にし、始点 " + L[c.source] + " に dist = 0 と書いてキューに入れる。",
    }));

    while (queue.length > 0) {
      var u = queue.shift();
      done[u] = true;
      var d = dist[u];
      var pushed = [], skipped = [], scanned = [];
      adj[u].forEach(function (a) {
        var to = a[0];
        if (dist[to] === -1) {
          dist[to] = d + 1;
          par[to] = u;
          parEdge[to] = a[1];
          queue.push(to);
          pushed.push(to);
          scanned.push({ to: to, edge: a[1], found: true });
        } else {
          skipped.push(to);
          scanned.push({ to: to, edge: a[1], found: false });
        }
      });
      var cap = "先頭の " + L[u] + "（距離 " + d + "）を取り出す。";
      if (adj[u].length === 0) cap += L[u] + " に隣の頂点はない。";
      if (skipped.length > 0) cap += "隣の " + names(L, skipped) + " はもう距離が書いてあるので飛ばす。";
      if (pushed.length > 0) {
        cap += (skipped.length > 0 ? "" : "隣の ") + names(L, pushed) + " は −1 なので、見つけたこの場で距離 " + (d + 1) +
          " と親 " + L[u] + " を書き、末尾に入れる。";
      }
      cap += queueText(dist, queue);
      out.push(snap({ phase: "pop", popped: u, pushed: pushed, scanned: scanned, caption: cap }));
    }

    var res = [];
    var unreached = [];
    for (var t = 0; t < n; t++) {
      res.push(L[t] + ": " + (dist[t] === -1 ? "−1" : dist[t]));
      if (dist[t] === -1) unreached.push(t);
    }
    out.push(snap({
      phase: "done",
      caption: "キューが空になったので終わる。距離は " + res.join("、") + " である。" +
        (unreached.length ? names(L, unreached) + " には始点から届かず、−1 のままである。" : "") +
        "太い辺（親への辺）をたどると、始点から各頂点への最短路の木になる。",
    }));
    return out;
  }

  // ---------- 描画 ----------
  var W = 440;
  var R = 16;
  var MX = 56; // 左右の端の列の中心と枠の端の間
  var COL_MAX = 132; // 列の間隔の上限
  var BAND_W = 64;
  var BAND_TOP = 22;
  var CY0 = BAND_TOP + 42; // 一番上の頂点の中心
  var SP = 64; // 列の中の頂点の間隔
  var CELL_W = 40, CELL_H = 30, CELL_GAP = 6;
  var LEGEND_H = 76;

  // 頂点の置き場：最後に決まる距離ごとの列。列の中は見つけた順
  function layout(c) {
    var sts = states(c);
    var last = sts[sts.length - 1];
    var dist = last.dist;
    var order = [];
    sts.forEach(function (s) { if (s.phase === "pop") order.push(s.popped); });
    for (var v = 0; v < c.n; v++) if (dist[v] === -1) order.push(v);
    var maxD = 0;
    dist.forEach(function (d) { maxD = Math.max(maxD, d); });
    var hasUnreached = dist.indexOf(-1) >= 0;
    var cols = maxD + 1 + (hasUnreached ? 1 : 0);
    var members = [];
    for (var k = 0; k < cols; k++) members.push([]);
    order.forEach(function (v) { members[dist[v] === -1 ? cols - 1 : dist[v]].push(v); });
    var maxK = 1;
    members.forEach(function (m) { maxK = Math.max(maxK, m.length); });
    var gap = cols > 1 ? Math.min(COL_MAX, (W - 2 * MX) / (cols - 1)) : 0;
    var x0 = (W - gap * (cols - 1)) / 2;
    var pts = [], col = [], row = [];
    members.forEach(function (m, k) {
      m.forEach(function (v, j) {
        pts[v] = [x0 + gap * k, CY0 + (j + (maxK - m.length) / 2) * SP];
        col[v] = k;
        row[v] = j;
      });
    });
    var bandBottom = CY0 + (maxK - 1) * SP + R + 28;
    return {
      pts: pts, col: col, row: row, cols: cols, maxD: maxD, hasUnreached: hasUnreached,
      colX: function (k) { return x0 + gap * k; }, members: members, bandBottom: bandBottom,
    };
  }

  function dims(c) {
    var g = layout(c);
    var popTop = g.bandBottom + 14;
    var qTop = popTop + CELL_H + 14;
    var legendTop = qTop + 18 + CELL_H + 22;
    return { g: g, popTop: popTop, qTop: qTop, legendTop: legendTop, height: legendTop + LEGEND_H };
  }

  function viewBox(config) {
    return "0 0 " + W + " " + Math.ceil(dims(validate(config)).height);
  }

  var OFF_V = R + 12, OFF_H = R + 10; // 距離の文字の、頂点の中心からの離れ（上下・左右）

  // 距離の文字を置く向き：頂点につながる辺の向きから最も離れた向き（上・下を優先し、だめなら右・左。枠の端では横に置かない）。
  // banUp のときは上に置かない（同じ列ですぐ上の頂点が文字を下に置いていて、間に 2 つ並ぶと重なるため）
  function labelDir(v, c, pts, banUp) {
    var angs = [];
    c.edges.forEach(function (e) {
      var o = e[0] === v ? e[1] : e[1] === v ? e[0] : -1;
      if (o >= 0) angs.push(Math.atan2(pts[o][1] - pts[v][1], pts[o][0] - pts[v][0]));
    });
    var cands = [[0, -1], [0, 1], [1, 0], [-1, 0]];
    var pen = [0, 0.05, 1.2, 1.25];
    var best = cands[0], bestScore = -Infinity;
    cands.forEach(function (d, k) {
      // 横に置くと「−1→3」が枠からはみ出す所は使わない
      var tx = pts[v][0] + d[0] * (OFF_H + 40);
      if (tx < 0 || tx > W) return;
      if (banUp && d[1] < 0) return;
      // 横に置くとき、その向きの近くに別の頂点（とその上下の文字）があれば使わない
      if (d[0] !== 0) {
        for (var o = 0; o < c.n; o++) {
          if (o === v) continue;
          var ox = (pts[o][0] - pts[v][0]) * d[0], oy = Math.abs(pts[o][1] - pts[v][1]);
          if (ox > 0 && ox < OFF_H + 40 + R && oy < OFF_V + 18) return;
        }
      }
      var a = Math.atan2(d[1], d[0]);
      var m = Math.PI;
      angs.forEach(function (b) {
        var x = Math.abs(a - b) % (2 * Math.PI);
        m = Math.min(m, Math.min(x, 2 * Math.PI - x));
      });
      var score = m - pen[k];
      if (score > bestScore + 1e-9) { bestScore = score; best = d; }
    });
    return best;
  }

  // 全頂点の距離の文字の向きを、各列の上から順に決める
  function labelDirs(c, g) {
    var dirs = [];
    g.members.forEach(function (m) {
      var prevDown = false;
      m.forEach(function (v) {
        dirs[v] = labelDir(v, c, g.pts, prevDown);
        prevDown = dirs[v][1] > 0;
      });
    });
    return dirs;
  }

  // 太い線の中に重ねる細い破線（背景色）
  function focusOverlay(attrs, k) {
    var o = {
      style: "fill: none; stroke: var(--md-default-bg-color); stroke-width: 1.5",
      "stroke-dasharray": "4 3", "data-focus-tree": k < 0 ? null : k,
    };
    ["d", "x1", "y1", "x2", "y2"].forEach(function (key) { if (attrs[key] != null) o[key] = attrs[key]; });
    return o;
  }

  var HALO = "paint-order: stroke; stroke: var(--md-default-bg-color); stroke-width: 4px";

  function render(svg, s, config, h) {
    var c = validate(config);
    var L = c.labels;
    var D = dims(c);
    var g = D.g;
    var pts = g.pts;

    // 層の帯：いまキューにある距離の帯は塗り、見つけた頂点のある帯は実線、まだの帯は破線
    var inQueue = Object.create(null);
    s.queue.forEach(function (v) { inQueue[s.dist[v]] = true; });
    var found = Object.create(null);
    s.dist.forEach(function (d) { if (d >= 0) found[d] = true; });
    for (var k = 0; k < g.cols; k++) {
      var unreachCol = g.hasUnreached && k === g.cols - 1;
      var cls = unreachCol || !found[k] ? "kp-v-cell is-sentinel" : inQueue[k] ? "kp-v-cell is-yes" : "kp-v-cell";
      var bx = g.colX(k) - BAND_W / 2;
      svg.appendChild(h("rect", {
        x: bx, y: BAND_TOP, width: BAND_W, height: g.bandBottom - BAND_TOP, rx: 8, class: cls,
        style: "stroke-width: 1", "data-band": unreachCol ? "unreached" : k,
      }));
      var head = unreachCol ? "届かない" : "距離 " + k;
      svg.appendChild(h("text", {
        x: g.colX(k), y: 10, class: !unreachCol && inQueue[k] ? "kp-v-ptr is-b" : "kp-v-text is-sub",
      }, head));
    }

    // 辺：親への辺は太い実線、このステップで見た辺は強調、ほかは細い破線
    var scannedEdge = Object.create(null);
    s.scanned.forEach(function (x) { scannedEdge[x.edge] = x; });
    var treeEdge = Object.create(null);
    s.parEdge.forEach(function (k) { if (k >= 0) treeEdge[k] = true; });
    c.edges.forEach(function (e, k) {
      var a = pts[e[0]], b = pts[e[1]];
      var sc = scannedEdge[k];
      var tree = !!treeEdge[k];
      var cls = sc ? "kp-v-cell is-focus" : tree ? "kp-v-cell is-answer" : "kp-v-cell";
      var attrs = {
        class: cls, style: "fill: none" + (tree ? "; stroke-width: 4.5" : ""),
        "stroke-dasharray": tree ? null : "5 4", "data-edge": k,
      };
      var dx = b[0] - a[0], dy = b[1] - a[1];
      var len = Math.sqrt(dx * dx + dy * dy);
      var ux = dx / len, uy = dy / len;
      if (g.col[e[0]] === g.col[e[1]] && Math.abs(g.row[e[0]] - g.row[e[1]]) > 1) {
        // 同じ列で間に頂点がある：右へふくらむ弧
        var bulge = 34 * (Math.abs(g.row[e[0]] - g.row[e[1]]) - 0.5);
        // 2 次ベジエの一番右は制御点までの半分なので、枠の右端（線の太さの分を残す）を超えないよう頭打ちにする
        bulge = Math.min(bulge, 2 * (W - 6 - a[0]));
        var mx = (a[0] + b[0]) / 2 + bulge, my = (a[1] + b[1]) / 2;
        attrs.d = "M" + a[0] + " " + a[1] + "Q" + mx + " " + my + " " + b[0] + " " + b[1];
        svg.appendChild(h("path", attrs));
      } else {
        attrs.x1 = a[0] + ux * R; attrs.y1 = a[1] + uy * R;
        attrs.x2 = b[0] - ux * R; attrs.y2 = b[1] - uy * R;
        svg.appendChild(h("line", attrs));
      }
      // 今見た辺が親への辺でもあるときは、色だけでなく、太い線の中に細い破線を重ねて前からの親への辺と区別する
      if (sc && tree) svg.appendChild(h(attrs.d != null ? "path" : "line", focusOverlay(attrs, k)));
    });

    // 頂点：未発見は破線、キューの中は白、取り出し済みは塗り。取り出した頂点は外側に輪
    var dirs = labelDirs(c, g);
    var pushedNow = Object.create(null);
    s.pushed.forEach(function (v) { pushedNow[v] = true; });
    for (var v = 0; v < c.n; v++) {
      var p = pts[v];
      if (s.popped === v) {
        svg.appendChild(h("circle", { cx: p[0], cy: p[1], r: R + 5, class: "kp-v-cell is-focus", style: "fill: none", "data-ring": v }));
      }
      var unseen = s.dist[v] === -1;
      svg.appendChild(h("circle", {
        cx: p[0], cy: p[1], r: R, "data-vertex": v,
        class: s.done[v] ? "kp-v-cell is-answer" : unseen ? "kp-v-cell is-sentinel" : "kp-v-cell",
      }));
      svg.appendChild(h("text", {
        x: p[0], y: p[1], class: s.done[v] ? "kp-v-text is-on-answer" : unseen ? "kp-v-text is-dim" : "kp-v-text",
      }, L[v]));
      // 距離（辺から離れた向き）。このステップで書いたものは「−1→d」
      var dir = dirs[v];
      var off = dir[1] !== 0 ? OFF_V : OFF_H;
      svg.appendChild(h("text", {
        x: p[0] + dir[0] * off, y: p[1] + dir[1] * off, class: pushedNow[v] ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: HALO + (pushedNow[v] ? "" : "; font-size: 13px") +
          (dir[0] > 0 ? "; text-anchor: start" : dir[0] < 0 ? "; text-anchor: end" : ""),
        "data-dist": v,
      }, pushedNow[v] ? "−1→" + s.dist[v] : unseen ? "−1" : String(s.dist[v])));
    }

    // 取り出した頂点
    function cell(x, y, label, cls, tcls) {
      svg.appendChild(h("rect", { x: x, y: y, width: CELL_W, height: CELL_H, rx: 5, class: cls }));
      svg.appendChild(h("text", { x: x + CELL_W / 2, y: y + CELL_H / 2, class: tcls }, label));
    }
    function headText(x, y, text, cls) {
      svg.appendChild(h("text", { x: x, y: y, class: cls || "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, text));
    }
    var LX = 8;
    var py = D.popTop;
    headText(LX, py + CELL_H / 2, "取り出した頂点");
    var PX = 112;
    if (s.popped !== null) {
      cell(PX, py, L[s.popped], "kp-v-cell is-answer is-focus", "kp-v-text is-on-answer");
      headText(PX + CELL_W + 10, py + CELL_H / 2,
        "距離 " + s.dist[s.popped] + (s.pushed.length ? "・見つけた：" + names(L, s.pushed) : "・新しく見つけた頂点はない"),
        "kp-v-ptr is-focus");
    } else {
      headText(PX, py + CELL_H / 2, s.phase === "init" ? "—（初期状態）" : "—（終わり）");
    }

    // キュー（先頭が左）。下の数は距離。距離が変わる所に縦線
    var qy = D.qTop;
    headText(LX, qy + 6, "キュー（左が先頭、下の数は距離）");
    var cy = qy + 18;
    if (s.queue.length === 0) {
      headText(LX, cy + CELL_H / 2, "空");
    }
    s.queue.forEach(function (q, j) {
      var x = LX + j * (CELL_W + CELL_GAP);
      var isNew = !!pushedNow[q];
      cell(x, cy, L[q], isNew ? "kp-v-cell is-focus" : "kp-v-cell", "kp-v-text");
      svg.appendChild(h("text", { x: x + CELL_W / 2, y: cy + CELL_H + 10, class: "kp-v-text is-sub" }, s.dist[q]));
      if (j > 0 && s.dist[s.queue[j - 1]] !== s.dist[q]) {
        var bx2 = x - CELL_GAP / 2;
        svg.appendChild(h("rect", { x: bx2 - 1, y: cy - 4, width: 2, height: CELL_H + 18, class: "kp-v-mark is-b", "data-split": j }));
      }
    });

    // 凡例
    var ly = D.legendTop;
    function legendLine(x, cls, style, dash, text) {
      svg.appendChild(h("line", { x1: x, y1: ly + 8, x2: x + 24, y2: ly + 8, class: cls, style: style, "stroke-dasharray": dash }));
      svg.appendChild(h("text", { x: x + 30, y: ly + 8, class: "kp-v-text is-sub", style: "text-anchor: start" }, text));
    }
    legendLine(8, "kp-v-cell is-answer", "stroke-width: 4.5", null, "親への辺（par）");
    legendLine(150, "kp-v-cell", null, "5 4", "ほかの辺");
    // 今見た辺：細い破線（もう距離が書いてあった隣）と、細い破線を重ねた太い線（親への辺でもある）
    ly += 24;
    svg.appendChild(h("line", { x1: 8, y1: ly + 8, x2: 32, y2: ly + 8, class: "kp-v-cell is-focus", "stroke-dasharray": "5 4" }));
    var tl = { x1: 40, y1: ly + 8, x2: 64, y2: ly + 8 };
    svg.appendChild(h("line", { x1: 40, y1: ly + 8, x2: 64, y2: ly + 8, class: "kp-v-cell is-focus", style: "stroke-width: 4.5" }));
    svg.appendChild(h("line", focusOverlay(tl, -1)));
    svg.appendChild(h("text", { x: 70, y: ly + 8, class: "kp-v-text is-sub", style: "text-anchor: start" }, "今見た辺（太いものは親への辺でもある）"));
    var l2 = ly + 32;
    function legendDot(x, cls, text) {
      svg.appendChild(h("circle", { cx: x + 9, cy: l2, r: 8, class: cls }));
      svg.appendChild(h("text", { x: x + 24, y: l2, class: "kp-v-text is-sub", style: "text-anchor: start" }, text));
    }
    legendDot(8, "kp-v-cell is-answer", "取り出し済み");
    legendDot(150, "kp-v-cell", "キューの中");
    legendDot(270, "kp-v-cell is-sentinel", "未発見（−1）");
  }

  return {
    title: "幅優先探索で、キューから頂点を取り出し、隣を見つけて距離の層を広げていく",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

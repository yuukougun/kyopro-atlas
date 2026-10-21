/*
 * 動く図：01-BFS で、deque の先頭から組を取り出し、重み 0 の辺で縮んだ頂点を先頭へ、重み 1 の辺で縮んだ頂点を末尾へ入れる様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="zero-one-bfs"
 *        data-config='{"n": 3, "source": 0, "edges": [[0, 1, 1], [0, 2, 0]]}'></div>
 * config：
 *   n        … 頂点の数（1〜8）。頂点は 0〜n−1
 *   edges    … 辺 [u, v, w] の配列（0〜12 本）。w は 0 か 1。自己ループと、同じ 2 頂点を結ぶ 2 本目の辺は不可
 *   directed … 省略か true なら有向（u → v）。false なら無向
 *   source   … 始点（省略時 0）
 *   labels   … 頂点の名前（省略可。n 個の 1〜3 文字の文字列）
 *   pos      … 頂点の位置 [x, y] の配列（省略可。単位は任意で、枠に合わせて拡大・縮小する）。省略時は円の上に並べる
 *
 * 本文の処理の流れと同じ書き方で動かす：deque の先頭の組 (d, u) を取り出し、d > dist[u] なら古い組として読み飛ばす。
 * そうでなければ u から出る辺を辺の並びの順に見て、d + w < dist[v] なら dist[v] を更新し、
 * w = 0 なら (d, v) を先頭へ、w = 1 なら (d + 1, v) を末尾へ入れる。
 * 1 回の取り出しを 1 ステップにし、最初に初期状態を置く。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/zero-one-bfs.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("zero-one-bfs", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_M = 12;
  var MAX_STEPS = 200;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var directed = config.directed == null ? true : config.directed;
    if (typeof directed !== "boolean") throw new Error("directed は true か false にする");
    var source = config.source == null ? 0 : config.source;
    if (!isInt(source) || source < 0 || source >= n) throw new Error("source は 0〜" + (n - 1) + " の整数にする");
    var es = config.edges == null ? [] : config.edges;
    if (!Array.isArray(es) || es.length > MAX_M) throw new Error("edges は 0〜" + MAX_M + " 本の辺 [u, v, w] の配列にする");
    var edges = [];
    var seen = Object.create(null);
    for (var i = 0; i < es.length; i++) {
      var e = es[i];
      if (!Array.isArray(e) || e.length !== 3) throw new Error("edges の各辺は [u, v, w] の形にする");
      var u = e[0], v = e[1], w = e[2];
      if (!isInt(u) || !isInt(v) || u < 0 || v < 0 || u >= n || v >= n) {
        throw new Error("辺の端は 0〜" + (n - 1) + " の整数にする");
      }
      if (u === v) throw new Error("自己ループ（" + u + " から " + u + " への辺）は描けない");
      if (w !== 0 && w !== 1) throw new Error("01-BFS の辺の重みは 0 か 1 にする");
      var key = Math.min(u, v) + "-" + Math.max(u, v);
      if (seen[key]) throw new Error("同じ 2 頂点を結ぶ辺は 1 本にする（" + u + " と " + v + "）");
      seen[key] = true;
      edges.push([u, v, w]);
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
    return { named: config.labels != null, n: n, directed: directed, source: source, edges: edges, labels: labels, pos: pos };
  }

  // 頂点 v から出る辺 [to, w, 辺の番号] を辺の並びの順に
  function adjacency(c) {
    var adj = [];
    for (var i = 0; i < c.n; i++) adj.push([]);
    c.edges.forEach(function (e, k) {
      adj[e[0]].push([e[1], e[2], k]);
      if (!c.directed) adj[e[1]].push([e[0], e[2], k]);
    });
    return adj;
  }

  function distText(v) {
    return v === null ? "∞" : String(v);
  }

  // 各ステップの状態：
  //   phase（init / pop / stale）、dist（null は ∞）、done（取り出して距離が確定したか）、
  //   deque（処理の後の deque。(距離, 頂点) を先頭 → 末尾）、newFront / newBack（このステップで先頭・末尾に入れた組の数。
  //   先頭に入れた組は deque の先頭の newFront 個、末尾に入れた組は末尾の newBack 個になる）、
  //   popped（取り出した組。初期状態は null）、stale（古い組として読み飛ばしたか）、
  //   updated（このステップの更新 {to, edge, from, old, next, w, front}）、kept（見たが縮まなかった辺 {to, edge, w, cand, cur}）、
  //   last（最後の状態か）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var L = c.labels;
    var adj = adjacency(c);
    var dist = [], done = [];
    for (var i = 0; i < n; i++) {
      dist.push(null);
      done.push(false);
    }
    dist[c.source] = 0;
    var dq = [[0, c.source]];
    var out = [];
    function pair(p) {
      return "(" + p[0] + ", " + L[p[1]] + ")";
    }
    function snap(extra) {
      var s = {
        dist: dist.slice(), done: done.slice(),
        deque: dq.map(function (p) { return p.slice(); }),
        newFront: 0, newBack: 0,
        popped: null, stale: false, updated: [], kept: [], last: false,
      };
      Object.keys(extra).forEach(function (k) { s[k] = extra[k]; });
      return s;
    }

    out.push(snap({
      phase: "init",
      caption: "始点 " + L[c.source] + " の dist を 0、ほかを ∞ にし、deque に " + pair([0, c.source]) + " を入れる。",
    }));

    while (dq.length > 0) {
      if (out.length > MAX_STEPS) throw new Error("ステップが " + MAX_STEPS + " を超えた。グラフを小さくする");
      var top = dq.shift();
      var d = top[0], u = top[1];
      var cap = "先頭の " + pair(top) + " を取り出す。";
      var s;
      if (d > dist[u]) {
        cap += "dist[" + L[u] + "] = " + dist[u] + " < " + d + " なので古い組であり、読み飛ばす。";
        s = snap({ phase: "stale", popped: top.slice(), stale: true, caption: cap });
      } else {
        done[u] = true;
        cap += L[u] + " の距離 " + d + " が確定する。";
        var ups = [], kept = [];
        var nf = 0, nb = 0;
        adj[u].forEach(function (a) {
          var to = a[0], w = a[1];
          var nd = d + w;
          var arrow = L[u] + " → " + L[to] + "（重み " + w + "）";
          if (dist[to] === null || nd < dist[to]) {
            var old = dist[to];
            var staleNote = "";
            if (old !== null) {
              // 縮む前の距離で入っている組は古い組になる
              for (var t = 0; t < dq.length; t++) {
                if (dq[t][1] === to && dq[t][0] === old) { staleNote = pair([old, to]) + " は古い組になる。"; break; }
              }
            }
            ups.push({ to: to, edge: a[2], from: u, old: old, next: nd, w: w, front: w === 0 });
            dist[to] = nd;
            if (w === 0) {
              dq.unshift([nd, to]);
              nf++;
            } else {
              dq.push([nd, to]);
              nb++;
            }
            cap += arrow + "で dist[" + L[to] + "] を " + distText(old) + " → " + nd + " に" +
              (old === null ? "し" : "縮め") + "、" + pair([nd, to]) + " を" + (w === 0 ? "先頭" : "末尾") + "へ入れる。" + staleNote;
          } else {
            kept.push({ to: to, edge: a[2], w: w, cand: nd, cur: dist[to] });
            cap += arrow + "では " + d + " + " + w + " = " + nd + " で、dist[" + L[to] + "] = " + dist[to] + " より小さくならない。";
          }
        });
        if (adj[u].length === 0) cap += L[u] + " から出る辺はない。";
        s = snap({ phase: "pop", popped: top.slice(), updated: ups, kept: kept, newFront: nf, newBack: nb, caption: cap });
      }
      out.push(s);
    }

    var lastS = out[out.length - 1];
    lastS.last = true;
    var unreached = [];
    var res = [];
    for (var v = 0; v < n; v++) {
      if (dist[v] === null) unreached.push(L[v]);
      res.push(c.named ? L[v] + ": " + distText(dist[v]) : distText(dist[v]));
    }
    lastS.caption += "deque が空になったので終わる。最短距離は" +
      (c.named ? " " + res.join("、") : n === 1 ? "頂点 0 が " + res[0] : "頂点 0〜" + (n - 1) + " の順に " + res.join("、")) + " である。" +
      (unreached.length ? unreached.join("・") + " には始点から届かず、∞ のままである。" : "");
    return out;
  }

  // ---------- 描画 ----------
  var W = 440;
  var R = 17;
  var MX = 46; // 頂点の中心と左右の端の間
  var GH_MAX = 150; // 頂点の中心が並ぶ高さの上限
  var TOP = 42; // 枠の上端から頂点の中心の最上段まで（距離の文字の分）
  var BELOW = 46;
  var OFF_V = R + 14, OFF_H = R + 12; // 頂点の中心から距離の文字まで（上下・左右）
  var DIST_W = 36; // 距離の文字（「∞→7」まで、太字 14px）の幅の見積もり
  var LABEL_W = 104; // 行の左の見出しの幅
  var CELL_W = 60, CELL_H = 28, CELL_GAP = 2;
  var PER_ROW = 5;
  var ROW_H = CELL_H + 8;
  var DQ_ROW_H = CELL_H + 22; // deque の行は、枠の下に「先頭へ」「末尾へ」を書く分だけ高い
  var LEGEND_H = 46;

  function layout(c) {
    var raw = c.pos;
    if (!raw) {
      raw = [];
      for (var i = 0; i < c.n; i++) {
        var th = Math.PI - (2 * Math.PI * i) / c.n; // 0 を左に置き、時計回り
        raw.push([Math.cos(th), -Math.sin(th)]);
      }
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

  // render は毎回呼ばれるので、凡例の位置に使う状態の列は同じ config について 1 回だけ作る
  var cacheKey = null, cacheVal = null;
  function cachedStates(config) {
    if (cacheKey !== config) { cacheVal = states(config); cacheKey = config; }
    return cacheVal;
  }

  function maxDeque(sts) {
    var m = 1;
    sts.forEach(function (s) { m = Math.max(m, s.deque.length); });
    return m;
  }

  function dims(c, sts) {
    var g = layout(c);
    var rowTop = TOP + g.gh + BELOW;
    var rows = Math.ceil(maxDeque(sts) / PER_ROW);
    var legendTop = rowTop + ROW_H + DQ_ROW_H * rows + 4;
    return { g: g, rowTop: rowTop, legendTop: legendTop, height: legendTop + LEGEND_H };
  }

  function viewBox(config, sts) {
    var c = validate(config);
    return "0 0 " + W + " " + Math.ceil(dims(c, sts || states(config)).height);
  }

  // 距離の文字を置く向き：頂点につながる辺の向きから最も離れた向き（上・下・右・左の順に優先）。
  // 左右は、文字が枠（0〜W）に収まるときだけ候補にする
  function labelDir(v, c, pts) {
    var angs = [];
    c.edges.forEach(function (e) {
      var o = e[0] === v ? e[1] : e[1] === v ? e[0] : -1;
      if (o < 0) return;
      angs.push(Math.atan2(pts[o][1] - pts[v][1], pts[o][0] - pts[v][0]));
    });
    var cands = [[0, -1], [0, 1], [1, 0], [-1, 0]];
    var best = null, bestScore = -1;
    cands.forEach(function (d, k) {
      if (d[0] !== 0) {
        var edge = pts[v][0] + d[0] * (OFF_H + DIST_W);
        if (edge < 0 || edge > W) return;
      }
      var a = Math.atan2(d[1], d[0]);
      var m = Math.PI;
      angs.forEach(function (b) {
        var x = Math.abs(a - b) % (2 * Math.PI);
        m = Math.min(m, Math.min(x, 2 * Math.PI - x));
      });
      var score = m - k * 0.05; // ほぼ同じなら上・下を選ぶ
      if (score > bestScore + 1e-9) { bestScore = score; best = d; }
    });
    return best;
  }

  var HALO = "paint-order: stroke; stroke: var(--md-default-bg-color); stroke-width: 4px";

  function render(svg, s, config, h) {
    var c = validate(config);
    var L = c.labels;
    var g = layout(c);
    var pts = g.pts;
    var rowTop = TOP + g.gh + BELOW;
    var updatedEdge = Object.create(null);
    var updatedTo = Object.create(null);
    s.updated.forEach(function (u) { updatedEdge[u.edge] = true; updatedTo[u.to] = u; });

    // 辺：重み 0 は実線、重み 1 は破線。このステップで距離を縮めた辺は太く強調する
    c.edges.forEach(function (e, k) {
      var a = pts[e[0]], b = pts[e[1]];
      var dx = b[0] - a[0], dy = b[1] - a[1];
      var len = Math.sqrt(dx * dx + dy * dy);
      var ux = dx / len, uy = dy / len;
      var endGap = c.directed ? R + 3 : R;
      var x1 = a[0] + ux * R, y1 = a[1] + uy * R;
      var x2 = b[0] - ux * endGap, y2 = b[1] - uy * endGap;
      var up = !!updatedEdge[k];
      if (c.directed) { x2 -= ux * 8; y2 -= uy * 8; }
      svg.appendChild(h("line", {
        x1: x1, y1: y1, x2: x2, y2: y2, class: up ? "kp-v-cell is-focus" : "kp-v-cell",
        "stroke-dasharray": e[2] === 1 ? "6 4" : null,
        "data-edge": k,
      }));
      if (c.directed) {
        // 矢じり（行き先の円の手前）
        var tx = b[0] - ux * endGap, ty = b[1] - uy * endGap;
        var bx = tx - ux * 11, by = ty - uy * 11;
        var px = -uy * 5.5, py = ux * 5.5;
        svg.appendChild(h("path", {
          d: "M" + tx + " " + ty + "L" + (bx + px) + " " + (by + py) + "L" + (bx - px) + " " + (by - py) + "z",
          class: up ? "kp-v-mark is-focus" : "kp-v-mark",
        }));
      }
      // 重み：辺の中点から、上（縦の辺なら右）へずらす
      var nx = -uy, ny = ux;
      if (ny > 0 || (Math.abs(ny) < 1e-9 && nx < 0)) { nx = -nx; ny = -ny; }
      if (Math.abs(ux) < 0.2) { nx = 1; ny = 0; }
      var mx = (a[0] + b[0]) / 2 + nx * 11, my = (a[1] + b[1]) / 2 + ny * 11;
      svg.appendChild(h("text", {
        x: mx, y: my, class: up ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: "font-size: 14px; " + HALO,
      }, String(e[2])));
    });

    // 頂点：確定済みは塗り、未確定は白。取り出した頂点は外側に輪（読み飛ばしなら破線の輪）
    for (var v = 0; v < c.n; v++) {
      var p = pts[v];
      if (s.popped && s.popped[1] === v) {
        svg.appendChild(h("circle", {
          cx: p[0], cy: p[1], r: R + 5, class: "kp-v-cell is-focus", style: "fill: none",
          "stroke-dasharray": s.stale ? "4 3" : null, "data-ring": v,
        }));
      }
      svg.appendChild(h("circle", {
        cx: p[0], cy: p[1], r: R, class: s.done[v] ? "kp-v-cell is-answer" : "kp-v-cell", "data-vertex": v,
      }));
      svg.appendChild(h("text", {
        x: p[0], y: p[1], class: s.done[v] ? "kp-v-text is-on-answer" : "kp-v-text",
      }, L[v]));
      // 暫定距離
      var dir = labelDir(v, c, pts);
      var u = updatedTo[v];
      var txt = u ? distText(u.old) + "→" + u.next : distText(s.dist[v]);
      var off = dir[1] !== 0 ? OFF_V : OFF_H;
      svg.appendChild(h("text", {
        x: p[0] + dir[0] * off, y: p[1] + dir[1] * off,
        class: u ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: (dir[0] > 0 ? "text-anchor: start; " : dir[0] < 0 ? "text-anchor: end; " : "") + "font-size: 14px; " + HALO,
        "data-dist": v,
      }, txt));
    }

    function cell(x, y, label, opts) {
      svg.appendChild(h("rect", {
        x: x, y: y, width: CELL_W, height: CELL_H, rx: 5,
        class: opts.focus ? "kp-v-cell is-focus" : opts.stale ? "kp-v-cell is-no" : "kp-v-cell",
        "stroke-dasharray": opts.stale ? "4 3" : null,
      }));
      svg.appendChild(h("text", {
        x: x + CELL_W / 2, y: y + CELL_H / 2, class: opts.stale ? "kp-v-text is-dim" : "kp-v-text",
        style: "font-size: 14px",
      }, label));
      if (opts.stale) {
        // 取り消し線（古い組）
        svg.appendChild(h("rect", { x: x + 6, y: y + CELL_H / 2 - 0.75, width: CELL_W - 12, height: 1.5, class: "kp-v-mark", "data-strike": 1 }));
      }
    }
    function pairText(q) { return "(" + q[0] + ", " + L[q[1]] + ")"; }
    function head(y, text) {
      svg.appendChild(h("text", { x: 6, y: y + CELL_H / 2, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, text));
    }
    function note(x, y, text) {
      svg.appendChild(h("text", { x: x, y: y + CELL_H / 2, class: "kp-v-text is-sub", style: "text-anchor: start" }, text));
    }

    // 取り出した組
    var y = rowTop;
    head(y, "取り出した組");
    if (s.popped) {
      cell(LABEL_W, y, pairText(s.popped), { focus: !s.stale, stale: s.stale });
      svg.appendChild(h("text", {
        x: LABEL_W + CELL_W + 8, y: y + CELL_H / 2, class: s.stale ? "kp-v-text is-sub" : "kp-v-ptr is-focus",
        style: "text-anchor: start",
      }, s.stale ? "古い組なので読み飛ばす" : L[s.popped[1]] + " の距離が確定"));
    } else {
      note(LABEL_W, y, "—（初期状態）");
    }

    // deque（先頭 → 末尾）。このステップで入れた組は太枠にし、枠の下に「先頭へ」「末尾へ」と書く
    y += ROW_H;
    head(y, "deque");
    svg.appendChild(h("text", { x: 6, y: y + CELL_H / 2 + 15, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 11px" }, "先頭 → 末尾"));
    if (s.deque.length === 0) note(LABEL_W, y, "空");
    var len = s.deque.length;
    s.deque.forEach(function (q, k) {
      var cx = LABEL_W + (k % PER_ROW) * (CELL_W + CELL_GAP);
      var cy = y + Math.floor(k / PER_ROW) * DQ_ROW_H;
      var stale = s.dist[q[1]] !== null && q[0] > s.dist[q[1]];
      var side = k < s.newFront ? "先頭へ" : k >= len - s.newBack ? "末尾へ" : null;
      cell(cx, cy, pairText(q), { stale: stale, focus: !!side && !stale });
      if (side) {
        svg.appendChild(h("text", {
          x: cx + CELL_W / 2, y: cy + CELL_H + 9, class: "kp-v-ptr is-focus", style: "font-size: 12px", "data-push": k,
        }, side));
      }
    });

    // 凡例
    var ly = dims(c, cachedStates(config)).legendTop;
    function legendLine(x, cls, dash, text) {
      svg.appendChild(h("line", { x1: x, y1: ly + 8, x2: x + 22, y2: ly + 8, class: cls, "stroke-dasharray": dash }));
      svg.appendChild(h("text", { x: x + 27, y: ly + 8, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, text));
    }
    legendLine(6, "kp-v-cell", null, "重み 0");
    legendLine(96, "kp-v-cell", "6 4", "重み 1");
    legendLine(186, "kp-v-cell is-focus", null, "今回縮めた辺（太線）");
    var l2 = ly + 30;
    svg.appendChild(h("circle", { cx: 14, cy: l2, r: 8, class: "kp-v-cell is-answer" }));
    svg.appendChild(h("text", { x: 27, y: l2, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, "確定済み"));
    svg.appendChild(h("circle", { cx: 124, cy: l2, r: 8, class: "kp-v-cell" }));
    svg.appendChild(h("text", { x: 137, y: l2, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, "未確定"));
    svg.appendChild(h("rect", { x: 266, y: l2 - 8, width: 22, height: 16, rx: 3, class: "kp-v-cell is-no", "stroke-dasharray": "4 3" }));
    svg.appendChild(h("rect", { x: 270, y: l2 - 0.75, width: 14, height: 1.5, class: "kp-v-mark" }));
    svg.appendChild(h("text", { x: 293, y: l2, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, "古い組"));
  }

  return {
    title: "01-BFS で、重み 0 の辺で縮んだ頂点を deque の先頭へ、重み 1 の辺で縮んだ頂点を末尾へ入れていく",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

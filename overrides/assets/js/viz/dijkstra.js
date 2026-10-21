/*
 * 動く図：ヒープ版のダイクストラ法で、取り出した組・確定済みの頂点・ヒープの中身が変わる様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="dijkstra"
 *        data-config='{"n": 5, "directed": false, "source": 0, "edges": [[0, 1, 4], [0, 2, 1]]}'></div>
 * config：
 *   n        … 頂点の数（1〜8）。頂点は 0〜n−1
 *   edges    … 辺 [u, v, w] の配列（0〜12 本）。w は絶対値 99 以下の整数。自己ループと、同じ 2 頂点を結ぶ 2 本目の辺は不可
 *   directed … true なら有向（u → v）。省略か false なら無向（無向では負の辺は不可。u-v-u が負閉路になるため）
 *   source   … 始点（省略時 0）
 *   labels   … 頂点の名前（省略可。n 個の 1〜3 文字の文字列）
 *   pos      … 頂点の位置 [x, y] の配列（省略可。単位は任意で、枠に合わせて拡大・縮小する）。省略時は円の上に並べる
 *
 * 本文のコード片と同じ書き方で動かす：最小の (d, v) を取り出し、d > dist[v] なら古い組として読み飛ばす。
 * そうでなければ v を確定し、出る辺で d + w < dist[to] なら dist[to] を更新して (dist[to], to) を入れる。
 * 確定済みの頂点への更新も止めない（負の辺があると、確定済みの距離が後から縮む場面を見せるため）。
 * 始点から届く負閉路があると終わらないので、Error にする。
 * 1 回の取り出しを 1 ステップにし、最初に初期状態を置く。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/dijkstra.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("dijkstra", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_M = 12;
  var MAX_W = 99;
  var MAX_STEPS = 200;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var directed = config.directed == null ? false : config.directed;
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
      if (!isInt(w) || Math.abs(w) > MAX_W) throw new Error("辺の重みは絶対値 " + MAX_W + " 以下の整数にする");
      if (!directed && w < 0) throw new Error("無向グラフに負の辺があると、その辺を往復する道が負閉路になる");
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
    var c = { named: config.labels != null, n: n, directed: directed, source: source, edges: edges, labels: labels, pos: pos };
    if (directed && hasNegativeCycle(c)) {
      throw new Error("始点から届く負閉路があると、入れ直す書き方は終わらない");
    }
    return c;
  }

  // 始点から届く負閉路があるか（ベルマンフォード法）
  function hasNegativeCycle(c) {
    var dist = [];
    for (var i = 0; i < c.n; i++) dist.push(null);
    dist[c.source] = 0;
    for (var it = 0; it < c.n; it++) {
      var changed = false;
      c.edges.forEach(function (e) {
        if (dist[e[0]] !== null && (dist[e[1]] === null || dist[e[0]] + e[2] < dist[e[1]])) {
          dist[e[1]] = dist[e[0]] + e[2];
          changed = true;
        }
      });
      if (!changed) return false;
    }
    return true;
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

  function num(v) {
    return v < 0 ? "−" + -v : String(v);
  }
  function distText(v) {
    return v === null ? "∞" : num(v);
  }
  function sumText(d, w) {
    return num(d) + (w < 0 ? " − " + -w : " + " + w);
  }
  function less(a, b) {
    return a[0] !== b[0] ? a[0] < b[0] : a[1] < b[1];
  }
  function sorted(heap) {
    return heap.slice().sort(function (a, b) { return less(a, b) ? -1 : less(b, a) ? 1 : 0; });
  }

  // 各ステップの状態：
  //   phase（init / pop / stale）、dist（null は ∞）、done（確定済みか）、prev（今の暫定距離を与えた辺の番号。なければ null）、
  //   heap（処理の後のヒープ。(距離, 頂点) を小さい順）、popped（取り出した組。初期状態は null）、stale（古い組として読み飛ばしたか）、
  //   again（確定済みの頂点をもう一度取り出したか）、updated（このステップの更新 {to, edge, from, to値の旧 old, 新 next, wasDone}）、
  //   last（最後の状態か）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var L = c.labels;
    var adj = adjacency(c);
    var dist = [], done = [], prev = [];
    for (var i = 0; i < n; i++) {
      dist.push(null);
      done.push(false);
      prev.push(null);
    }
    dist[c.source] = 0;
    var heap = [[0, c.source]];
    var out = [];
    function pair(p) {
      return "(" + num(p[0]) + ", " + L[p[1]] + ")";
    }
    function snap(extra) {
      var s = {
        dist: dist.slice(), done: done.slice(), prev: prev.slice(),
        heap: sorted(heap).map(function (p) { return p.slice(); }),
        popped: null, stale: false, again: false, updated: [], last: false,
      };
      Object.keys(extra).forEach(function (k) { s[k] = extra[k]; });
      return s;
    }

    out.push(snap({
      phase: "init",
      caption: "始点 " + L[c.source] + " の暫定距離を 0、ほかを ∞ にし、ヒープに " + pair([0, c.source]) + " を入れる。",
    }));

    while (heap.length > 0) {
      if (out.length > MAX_STEPS) throw new Error("ステップが " + MAX_STEPS + " を超えた。グラフを小さくする");
      var best = 0;
      for (var b = 1; b < heap.length; b++) if (less(heap[b], heap[best])) best = b;
      var top = heap.splice(best, 1)[0];
      var d = top[0], v = top[1];
      var cap = pair(top) + " を取り出す。";
      var s;
      if (d > dist[v]) {
        cap += "dist[" + L[v] + "] = " + num(dist[v]) + " < " + num(d) + " なので古い組であり、読み飛ばす。";
        s = snap({ phase: "stale", popped: top.slice(), stale: true, caption: cap });
      } else {
        var again = done[v];
        done[v] = true;
        var ups = [];
        var checked = 0;
        adj[v].forEach(function (a) {
          var to = a[0], w = a[1];
          checked++;
          var nd = d + w;
          if (dist[to] === null || nd < dist[to]) {
            ups.push({ to: to, edge: a[2], from: v, old: dist[to], next: nd, w: w, wasDone: done[to] });
            dist[to] = nd;
            prev[to] = a[2];
            heap.push([nd, to]);
          }
        });
        if (again) {
          cap += "dist[" + L[v] + "] = " + num(d) + " なので古い組ではなく、確定済みの " + L[v] +
            " をもう一度取り出して、出る辺を見直す。";
        } else {
          cap += L[v] + " を確定する。";
        }
        var normal = ups.filter(function (u) { return !u.wasDone; });
        var bad = ups.filter(function (u) { return u.wasDone; });
        if (normal.length > 0) {
          cap += normal.map(function (u) {
            return L[u.to] + " を " + distText(u.old) + " → " + num(u.next) + "（" + sumText(d, u.w) + "）";
          }).join("、") + "に更新し、" + normal.map(function (u) { return pair([u.next, u.to]); }).join("・") + " を入れる。";
          if (checked > ups.length) cap += "ほかの辺では短くならない。";
        }
        bad.forEach(function (u) {
          cap += L[v] + " → " + L[u.to] + " で " + sumText(d, u.w) + " = " + num(u.next) + " < " + num(u.old) +
            " となり、確定済みの " + L[u.to] + " の距離が " + num(u.old) + " から " + num(u.next) + " に縮む。" +
            "入れ直す書き方なので " + pair([u.next, u.to]) + " を入れ、あとで " + L[u.to] +
            " をもう一度取り出して出る辺も見直す。done[v] で捨てる書き方では " + pair([u.next, u.to]) +
            " を取り出しても読み飛ばすので、" + L[u.to] + " から出る辺が見直されず、その先の距離が誤りうる。";
        });
        if (ups.length === 0) cap += checked === 0 ? L[v] + " から出る辺はなく、更新はない。" : "更新はない。";
        if (again) cap += "同じ頂点を何度も取り出しうるので、計算量の保証はなくなる。";
        s = snap({ phase: "pop", popped: top.slice(), again: again, updated: ups, caption: cap });
      }
      out.push(s);
    }

    var lastS = out[out.length - 1];
    lastS.last = true;
    var unreached = [];
    var res = [];
    for (var t = 0; t < n; t++) {
      if (dist[t] === null) unreached.push(L[t]);
      res.push(c.named ? L[t] + ": " + distText(dist[t]) : distText(dist[t]));
    }
    lastS.caption += "ヒープが空になったので終わる。最短距離は" +
      (c.named ? " " + res.join("、") : "頂点 0〜" + (n - 1) + " の順に " + res.join("、")) + " である。" +
      (unreached.length ? unreached.join("・") + " には始点から届かず、∞ のままである。" : "") +
      (lastS.prev.some(function (e) { return e !== null; }) ? "細い実線の辺が最短路の木である。" : "");
    return out;
  }

  // ---------- 描画 ----------
  var W = 440;
  var R = 17;
  var MX = 46; // 頂点の中心と左右の端の間
  var GH_MAX = 150; // 頂点の中心が並ぶ高さの上限
  var TOP = 38; // 枠の上端から頂点の中心の最上段まで（距離の文字の分）
  var BELOW = 46;
  var LABEL_W = 104; // ヒープの行の左の見出しの幅
  var CELL_W = 60, CELL_H = 28, CELL_GAP = 2;
  var PER_ROW = 5;
  var ROW_H = CELL_H + 8;
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

  function maxHeap(sts) {
    var m = 1;
    sts.forEach(function (s) { m = Math.max(m, s.heap.length); });
    return m;
  }

  function dims(c, sts) {
    var g = layout(c);
    var heapTop = TOP + g.gh + BELOW;
    var rows = Math.ceil(maxHeap(sts) / PER_ROW);
    var legendTop = heapTop + ROW_H * (1 + rows) + 4;
    return { g: g, heapTop: heapTop, legendTop: legendTop, height: legendTop + LEGEND_H };
  }

  function viewBox(config, sts) {
    var c = validate(config);
    return "0 0 " + W + " " + Math.ceil(dims(c, sts || states(config)).height);
  }

  // 距離の文字を置く向き：頂点につながる辺の向きから最も離れた向き（上・下・右・左の順に優先）
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

  function render(svg, s, config, h) {
    var c = validate(config);
    var L = c.labels;
    var g = layout(c);
    var pts = g.pts;
    var heapTop = TOP + g.gh + BELOW;
    var updatedEdge = Object.create(null);
    var updatedTo = Object.create(null);
    s.updated.forEach(function (u) { updatedEdge[u.edge] = true; updatedTo[u.to] = u; });
    var treeEdge = Object.create(null);
    s.prev.forEach(function (k) { if (k !== null) treeEdge[k] = true; });

    // 辺：このステップで更新に使った辺は太い実線、今の暫定距離を与えている辺は細い実線、ほかは細い破線
    c.edges.forEach(function (e, k) {
      var a = pts[e[0]], b = pts[e[1]];
      var dx = b[0] - a[0], dy = b[1] - a[1];
      var len = Math.sqrt(dx * dx + dy * dy);
      var ux = dx / len, uy = dy / len;
      var endGap = c.directed ? R + 3 : R;
      var x1 = a[0] + ux * R, y1 = a[1] + uy * R;
      var x2 = b[0] - ux * endGap, y2 = b[1] - uy * endGap;
      var up = !!updatedEdge[k];
      var cls = up ? "kp-v-cell is-focus" : "kp-v-cell";
      if (c.directed) { x2 -= ux * 8; y2 -= uy * 8; }
      svg.appendChild(h("line", {
        x1: x1, y1: y1, x2: x2, y2: y2, class: cls,
        "stroke-dasharray": up || treeEdge[k] ? null : "5 4",
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
        style: "font-size: 14px; paint-order: stroke; stroke: var(--md-default-bg-color); stroke-width: 4px",
      }, num(e[2])));
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
      var txt = u ? distText(u.old) + "→" + num(u.next) + (u.wasDone ? "！" : "") : distText(s.dist[v]);
      var off = dir[1] !== 0 ? R + 14 : R + 12;
      svg.appendChild(h("text", {
        x: p[0] + dir[0] * off, y: p[1] + dir[1] * off,
        class: u ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: (dir[0] > 0 ? "text-anchor: start; " : dir[0] < 0 ? "text-anchor: end; " : "") +
          "font-size: 14px; paint-order: stroke; stroke: var(--md-default-bg-color); stroke-width: 4px",
        "data-dist": v,
      }, txt));
    }

    // 取り出した組
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
    function pairText(q) { return "(" + num(q[0]) + ", " + L[q[1]] + ")"; }
    function head(y, text) {
      svg.appendChild(h("text", { x: 6, y: y + CELL_H / 2, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, text));
    }
    var y = heapTop;
    head(y, "取り出した組");
    if (s.popped) {
      cell(LABEL_W, y, pairText(s.popped), { focus: !s.stale, stale: s.stale });
      svg.appendChild(h("text", {
        x: LABEL_W + CELL_W + 8, y: y + CELL_H / 2, class: s.stale ? "kp-v-text is-sub" : "kp-v-ptr is-focus",
        style: "text-anchor: start",
      }, s.stale ? "古い組なので読み飛ばす" : s.again ? L[s.popped[1]] + " をもう一度処理" : L[s.popped[1]] + " を確定"));
    } else {
      svg.appendChild(h("text", { x: LABEL_W, y: y + CELL_H / 2, class: "kp-v-text is-sub", style: "text-anchor: start" }, "—（初期状態）"));
    }
    y += ROW_H;
    head(y, "ヒープ");
    if (s.heap.length === 0) {
      svg.appendChild(h("text", { x: LABEL_W, y: y + CELL_H / 2, class: "kp-v-text is-sub", style: "text-anchor: start" }, "空"));
    }
    s.heap.forEach(function (q, k) {
      var cx = LABEL_W + (k % PER_ROW) * (CELL_W + CELL_GAP);
      var cy = y + Math.floor(k / PER_ROW) * ROW_H;
      var stale = s.dist[q[1]] !== null && q[0] > s.dist[q[1]];
      cell(cx, cy, pairText(q), { stale: stale });
    });

    // 凡例
    var ly = dims(c, cachedStates(config)).legendTop;
    function legendLine(x, cls, dash, text) {
      svg.appendChild(h("line", { x1: x, y1: ly + 8, x2: x + 22, y2: ly + 8, class: cls, "stroke-dasharray": dash }));
      svg.appendChild(h("text", { x: x + 27, y: ly + 8, class: "kp-v-text is-sub", style: "text-anchor: start; font-size: 13px" }, text));
    }
    legendLine(6, "kp-v-cell is-focus", null, "今回更新");
    legendLine(116, "kp-v-cell", null, "距離を与えた辺");
    legendLine(266, "kp-v-cell", "5 4", "ほかの辺");
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
    title: "ダイクストラ法で、ヒープから組を取り出して頂点を確定していく",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

/*
 * 動く図：ワーシャルフロイド法で、中継点 k を増やしながら距離の表 d[i][j] を更新していく様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="warshall-floyd"
 *        data-config='{"n": 4, "directed": true, "edges": [[0, 1, 5], [0, 3, 1]], "pos": [[0, 0], [1, 0], [1, 1], [0, 1]]}'></div>
 * config：
 *   n        … 頂点の数（1〜6）。頂点は 0〜n−1
 *   edges    … 辺 [u, v, w] の配列（0〜15 本）。w は絶対値 99 以下の整数。自己ループと、同じ向きの 2 本目の辺は不可
 *              （有向で u → v と v → u の両方があるときは、2 本を曲げて描く）
 *   directed … true なら有向（u → v）。省略か false なら無向（両向きに書く。無向では負の辺は不可）
 *   order    … "kij"（省略時。正しい順）か "ijk"（k を一番内側に置いた誤った順。確認問題の様子を見せる）
 *   labels   … 頂点の名前（省略可。n 個の 1〜3 文字の文字列）。表の見出しは常に 0〜n−1 の番号
 *   pos      … 頂点の位置 [x, y] の配列（省略可。単位は任意で、枠に合わせて拡大・縮小する）。省略時は円の上に並べる
 *
 * 負閉路があると表の値が意味を持たないので Error にする。
 *
 * "kij" のステップ：最初に辺だけの表、各 k の段の始まり（k 行目・k 列目が中継点）、
 *   段の中で i ≠ j かつ i, j ≠ k のマス (i, j) を行の順に 1 つずつ（d[i][k] + d[k][j] と比べる）。
 *   k 行目・k 列目・対角はその段で変わらない（負閉路がなければ d[k][k] = 0）ので飛ばす。
 * "ijk" のステップ：最初に辺だけの表、i ≠ j のマス (i, j) を行の順に 1 つずつ（k を内側で回した結果をまとめて 1 ステップ）。
 *   最後に正しい表と違うマスを示す。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/warshall-floyd.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("warshall-floyd", def);
})(function () {
  "use strict";

  var MAX_N = 6;
  var MAX_M = 15;
  var MAX_W = 99;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var directed = config.directed == null ? false : config.directed;
    if (typeof directed !== "boolean") throw new Error("directed は true か false にする");
    var order = config.order == null ? "kij" : config.order;
    if (order !== "kij" && order !== "ijk") throw new Error("order は \"kij\" か \"ijk\" にする");
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
      var key = directed ? u + ">" + v : Math.min(u, v) + "-" + Math.max(u, v);
      if (seen[key]) throw new Error("同じ向きの辺は 1 本にする（" + u + " と " + v + "）");
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
    var c = { n: n, directed: directed, order: order, edges: edges, labels: labels, pos: pos };
    var fin = floyd(c);
    for (var t = 0; t < n; t++) {
      if (fin[t][t] < 0) throw new Error("負閉路がある（頂点 " + t + " を通る）と、表の値が最短距離にならない");
    }
    return c;
  }

  // 辺だけの表（null は ∞）
  function initial(c) {
    var d = [];
    for (var i = 0; i < c.n; i++) {
      var row = [];
      for (var j = 0; j < c.n; j++) row.push(i === j ? 0 : null);
      d.push(row);
    }
    c.edges.forEach(function (e) {
      d[e[0]][e[1]] = e[2];
      if (!c.directed) d[e[1]][e[0]] = e[2];
    });
    return d;
  }

  function add(a, b) {
    return a === null || b === null ? null : a + b;
  }
  function less(a, b) {
    return a !== null && (b === null || a < b);
  }

  // 正しい順のワーシャルフロイド法（負閉路の判定と、"ijk" の最後の比べ合わせに使う）
  function floyd(c) {
    var d = initial(c);
    for (var k = 0; k < c.n; k++) {
      for (var i = 0; i < c.n; i++) {
        for (var j = 0; j < c.n; j++) {
          var s = add(d[i][k], d[k][j]);
          if (less(s, d[i][j])) d[i][j] = s;
        }
      }
    }
    return d;
  }

  function num(v) {
    return v === null ? "∞" : v < 0 ? "−" + -v : String(v);
  }
  function sumText(a, b) {
    if (b !== null && b < 0) return num(a) + " − " + -b;
    return num(a) + " + " + num(b);
  }
  function cellName(i, j) {
    return "d[" + i + "][" + j + "]";
  }
  function copy(d) {
    return d.map(function (row) { return row.slice(); });
  }

  // 各ステップの状態：
  //   phase（init / k / cell / ij）、order、d（そのステップの後の表。null は ∞）、
  //   k・i・j（そのステップの中継点と比べるマス。なければ null）、
  //   cell：a = d[i][k]、b = d[k][j]、old（比べる前の d[i][j]）、cand（a + b。どちらかが ∞ なら null）、updated（更新したか）
  //   ij：cands（k ごとの {k, a, b, sum}。k ≠ i, j）、old、next、updated
  //   changed（この段で、または "ijk" ではこれまでに更新したマス [i, j] の列）、wrong（"ijk" の最後で正しい表と違うマス）、
  //   formula（図の下の 1 行）、last、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var d = initial(c);
    var out = [];
    function snap(extra) {
      var s = {
        phase: null, order: c.order, d: copy(d), k: null, i: null, j: null,
        changed: [], wrong: [], formula: "", last: false, caption: "",
      };
      Object.keys(extra).forEach(function (key) { s[key] = extra[key]; });
      return s;
    }

    out.push(snap({
      phase: "init",
      formula: "辺だけの表（対角は 0、辺がなければ ∞）",
      caption: "辺だけの表から始める。d[i][i] = 0、辺 u → v があれば d[u][v] はその長さ、なければ ∞ である。" +
        "これは途中に頂点を 1 つも通さない経路の最短の長さである。",
    }));

    if (c.order === "kij") {
      for (var k = 0; k < n; k++) {
        var changed = [];
        var cap = "k = " + k + "：頂点 " + k + " も経由してよいことにする。" + k + " 行目と " + k + " 列目（中継点）は、d[" + k + "][" + k +
          "] = 0 なのでこの段では変わらない。";
        if (n >= 3) cap += "対角も 0 のまま変わらないので飛ばし、ほかのマス d[i][j] を d[i][" + k + "] + d[" + k + "][j] と比べていく。";
        else cap += "ほかに比べるマスはない。";
        out.push(snap({ phase: "k", k: k, formula: "中継点 k = " + k + "：" + k + " 行目と " + k + " 列目は変わらない", caption: cap }));
        for (var i = 0; i < n; i++) {
          for (var j = 0; j < n; j++) {
            if (i === j || i === k || j === k) continue;
            var a = d[i][k], b = d[k][j], old = d[i][j];
            var cand = add(a, b);
            var up = less(cand, old);
            if (up) {
              d[i][j] = cand;
              changed.push([i, j]);
            }
            var res = up ? cand : old;
            var formula = cellName(i, j) + " = min(" + num(old) + ", " + sumText(a, b) + ") = " + num(res) + (up ? "（更新）" : "");
            var cc = "k = " + k + "：" + cellName(i, j) + " を " + cellName(i, k) + " + " + cellName(k, j) + " と比べる。";
            if (cand === null) {
              cc += (a === null ? cellName(i, k) : cellName(k, j)) + " が ∞ なので、頂点 " + k + " を経由しても届かない。" +
                cellName(i, j) + " は " + num(old) + " のまま。";
            } else if (up) {
              cc += sumText(a, b) + " = " + num(cand) + " が今の " + num(old) + " より小さいので、" + num(cand) + " に更新する。" +
                "頂点 " + k + " を経由する、より短い経路が見つかった。";
            } else {
              cc += sumText(a, b) + " = " + num(cand) + " は今の " + num(old) + (cand === old ? " と同じなので、" : " より大きいので、") +
                num(old) + " のまま。";
            }
            out.push(snap({
              phase: "cell", k: k, i: i, j: j, a: a, b: b, old: old, cand: cand, updated: up,
              changed: changed.map(function (p) { return p.slice(); }), formula: formula, caption: cc,
            }));
          }
        }
        var lastOfStage = out[out.length - 1];
        if (lastOfStage.phase === "cell") {
          lastOfStage.caption += changed.length === 0 ? "k = " + k + " の段で変わったマスはない。" :
            "k = " + k + " の段で変わったのは " + changed.map(function (p) { return cellName(p[0], p[1]); }).join("・") +
            (changed.length === 1 ? " だけである。" : " である。");
        }
      }
      var lastS = out[out.length - 1];
      lastS.last = true;
      lastS.caption += "これで頂点 0〜" + (n - 1) + " のすべてを経由してよくなったので、表は全点対の最短距離である。";
    } else {
      var all = [];
      for (var i2 = 0; i2 < n; i2++) {
        for (var j2 = 0; j2 < n; j2++) {
          if (i2 === j2) continue;
          var old2 = d[i2][j2];
          var cands = [];
          var cur = old2;
          for (var k2 = 0; k2 < n; k2++) {
            if (k2 === i2 || k2 === j2) continue;
            var a2 = d[i2][k2], b2 = d[k2][j2], s2 = add(a2, b2);
            cands.push({ k: k2, a: a2, b: b2, sum: s2 });
            if (less(s2, cur)) cur = s2;
          }
          var up2 = cur !== old2;
          d[i2][j2] = cur;
          if (up2) all.push([i2, j2]);
          var f2 = cellName(i2, j2) + " = min(" + [num(old2)].concat(cands.map(function (x) { return sumText(x.a, x.b); })).join(", ") +
            ") = " + num(cur) + (up2 ? "（更新）" : "");
          var c2 = "i, j, k の順：" + cellName(i2, j2) + " を、k を内側で回して今の表の " + cellName(i2, "k") + " + " + cellName("k", j2) +
            " と比べる。";
          if (out.length === 1 && n >= 3) {
            c2 += "k = " + i2 + "（= i）と k = " + j2 + "（= j）の候補は " + cellName(i2, i2) + " + " + cellName(i2, j2) + " のように今の " +
              cellName(i2, j2) + " そのものなので除く。";
          }
          if (cands.length === 0) {
            c2 += "比べる k がないので " + num(old2) + " のまま。";
          } else {
            c2 += "候補は " + cands.map(function (x) { return "k = " + x.k + " で " + sumText(x.a, x.b); }).join("、") + "。";
            c2 += up2 ? num(old2) + " から " + num(cur) + " に更新する。" : num(old2) + " のまま。";
          }
          c2 += "(" + i2 + ", " + j2 + ") はこの後もう計算しない。";
          out.push(snap({
            phase: "ij", i: i2, j: j2, old: old2, next: cur, cands: cands, updated: up2,
            changed: all.map(function (p) { return p.slice(); }), formula: f2, caption: c2,
          }));
        }
      }
      var correct = floyd(c);
      var wrong = [];
      for (var x = 0; x < n; x++) {
        for (var y = 0; y < n; y++) if (d[x][y] !== correct[x][y]) wrong.push([x, y, correct[x][y]]);
      }
      var lastI = out[out.length - 1];
      lastI.last = true;
      lastI.wrong = wrong;
      if (wrong.length === 0) {
        lastI.caption += "このグラフでは、たまたま正しい表と一致した。";
      } else {
        lastI.caption += "正しい表と比べると、" + wrong.map(function (w) {
          return cellName(w[0], w[1]) + " が " + num(d[w[0]][w[1]]) + "（正しくは " + num(w[2]) + "）";
        }).join("、") + "で、2 つ以上の頂点を経由する経路を見落としている。";
      }
    }
    return out;
  }

  // ---------- 描画 ----------
  var W = 440;
  var R = 15;
  var GX0 = 30, GX1 = 160; // 頂点の中心が並ぶ横の範囲
  var GH_MAX = 120; // 頂点の中心が並ぶ高さの上限
  var TX = 186; // 表の行見出しの左端
  var RH = 34; // 行見出しの幅
  var TY = 44; // 表の 1 行目の上端
  var CS_MAX = 48;
  var LEGEND_H = 50;
  var HALO = "paint-order: stroke; stroke: var(--md-default-bg-color); stroke-width: 4px";

  function cellSize(n) {
    return Math.min(CS_MAX, Math.floor((W - 4 - TX - RH) / n));
  }

  function layout(c) {
    var raw = c.pos;
    if (!raw) {
      raw = [];
      for (var i = 0; i < c.n; i++) {
        var th = Math.PI / 2 + Math.PI / c.n - (2 * Math.PI * i) / c.n;
        raw.push([Math.cos(th), -Math.sin(th)]);
      }
    }
    var x0 = Infinity, x1 = -Infinity, y0 = Infinity, y1 = -Infinity;
    raw.forEach(function (p) {
      x0 = Math.min(x0, p[0]); x1 = Math.max(x1, p[0]);
      y0 = Math.min(y0, p[1]); y1 = Math.max(y1, p[1]);
    });
    var bw = x1 - x0, bh = y1 - y0;
    var sx = bw > 0 ? (GX1 - GX0) / bw : Infinity;
    var sy = bh > 0 ? GH_MAX / bh : Infinity;
    var sc = Math.min(sx, sy);
    if (sc === Infinity) sc = 1;
    var gh = bh * sc;
    var ox = (GX0 + GX1 - bw * sc) / 2;
    var tableMid = TY + (cellSize(c.n) * c.n) / 2;
    var oy = Math.max(TY - 4, tableMid - gh / 2);
    return {
      bottom: oy + gh + R + 22,
      pts: raw.map(function (p) { return [ox + (p[0] - x0) * sc, oy + (p[1] - y0) * sc]; }),
    };
  }

  function dims(c) {
    var g = layout(c);
    var tableBottom = TY + cellSize(c.n) * c.n;
    var fy = Math.max(tableBottom, g.bottom) + 20;
    return { g: g, fy: fy, legendTop: fy + 22, height: fy + 22 + LEGEND_H };
  }

  function viewBox(config) {
    var c = validate(config);
    return "0 0 " + W + " " + Math.ceil(dims(c).height);
  }

  // 頂点の印（i・j）を置く向き：つながる辺の向きから最も離れた向き
  function labelDir(v, c, pts) {
    var angs = [];
    c.edges.forEach(function (e) {
      var o = e[0] === v ? e[1] : e[1] === v ? e[0] : -1;
      if (o < 0) return;
      angs.push(Math.atan2(pts[o][1] - pts[v][1], pts[o][0] - pts[v][0]));
    });
    var cands = [[0, -1], [0, 1], [-1, 0], [1, 0], [-0.7071, -0.7071], [0.7071, -0.7071], [-0.7071, 0.7071], [0.7071, 0.7071]];
    var best = null, bestScore = -1;
    cands.forEach(function (d, k) {
      var a = Math.atan2(d[1], d[0]);
      var m = Math.PI;
      angs.forEach(function (b) {
        var x = Math.abs(a - b) % (2 * Math.PI);
        m = Math.min(m, Math.min(x, 2 * Math.PI - x));
      });
      var score = m - k * 0.02;
      if (score > bestScore + 1e-9) { bestScore = score; best = d; }
    });
    return best;
  }

  function render(svg, s, config, h) {
    var c = validate(config);
    var n = c.n;
    var L = c.labels;
    var dm = dims(c);
    var pts = dm.g.pts;
    var CS = cellSize(n);

    // ---- グラフ ----
    var pair = Object.create(null);
    if (c.directed) c.edges.forEach(function (e) { pair[e[0] + ">" + e[1]] = true; });
    c.edges.forEach(function (e, idx) {
      var a = pts[e[0]], b = pts[e[1]];
      var dx = b[0] - a[0], dy = b[1] - a[1];
      var len = Math.sqrt(dx * dx + dy * dy);
      var ux = dx / len, uy = dy / len;
      var nx = -uy, ny = ux; // 進む向きの左
      var bend = c.directed && pair[e[1] + ">" + e[0]] ? 16 : 0;
      var mx = (a[0] + b[0]) / 2 + nx * bend * 2, my = (a[1] + b[1]) / 2 + ny * bend * 2; // 2 次ベジエの制御点
      // 端：中心から制御点の向きに R だけ進めた点
      function toward(p, q, dist) {
        var vx = q[0] - p[0], vy = q[1] - p[1];
        var l = Math.sqrt(vx * vx + vy * vy);
        return [p[0] + (vx / l) * dist, p[1] + (vy / l) * dist, vx / l, vy / l];
      }
      var ctrl = [mx, my];
      var s0 = toward(a, ctrl, R);
      var tip = toward(b, ctrl, R + 2);
      var endDir = [-tip[2], -tip[3]]; // 行き先へ入る向き
      var e1 = c.directed ? [tip[0] - endDir[0] * 9, tip[1] - endDir[1] * 9] : toward(b, ctrl, R);
      svg.appendChild(h("path", {
        d: "M" + s0[0] + " " + s0[1] + "Q" + mx + " " + my + " " + e1[0] + " " + e1[1],
        class: "kp-v-cell", style: "fill: none", "data-edge": idx,
      }));
      if (c.directed) {
        var bx = tip[0] - endDir[0] * 10, by = tip[1] - endDir[1] * 10;
        var px = -endDir[1] * 5, py = endDir[0] * 5;
        svg.appendChild(h("path", {
          d: "M" + tip[0] + " " + tip[1] + "L" + (bx + px) + " " + (by + py) + "L" + (bx - px) + " " + (by - py) + "z",
          class: "kp-v-mark",
        }));
      }
      // 重み：曲線の頂点（中点）から外側へ
      var cx = (a[0] + b[0]) / 2 + nx * bend, cy = (a[1] + b[1]) / 2 + ny * bend;
      var ox = nx, oy = ny;
      if (!bend) {
        if (oy > 0 || (Math.abs(oy) < 1e-9 && ox < 0)) { ox = -ox; oy = -oy; }
        if (Math.abs(ux) < 0.2) { ox = 1; oy = 0; }
      }
      svg.appendChild(h("text", {
        x: cx + ox * (bend ? 13 : 10), y: cy + oy * (bend ? 13 : 10), class: "kp-v-text is-sub",
        style: "font-size: 13px; " + HALO,
      }, num(e[2])));
    });
    for (var v = 0; v < n; v++) {
      var p = pts[v];
      var isK = s.k === v;
      var isEnd = s.i === v || s.j === v;
      if (isEnd) {
        svg.appendChild(h("circle", { cx: p[0], cy: p[1], r: R + 4, class: "kp-v-cell is-focus", style: "fill: none", "data-ring": v }));
      }
      svg.appendChild(h("circle", { cx: p[0], cy: p[1], r: R, class: isK ? "kp-v-cell is-answer" : "kp-v-cell", "data-vertex": v }));
      svg.appendChild(h("text", { x: p[0], y: p[1], class: isK ? "kp-v-text is-on-answer" : "kp-v-text", style: "font-size: 15px" }, L[v]));
      var marks = [];
      if (s.i === v) marks.push("i");
      if (s.j === v) marks.push("j");
      if (isK) marks.push("k");
      if (marks.length) {
        var dir = labelDir(v, c, pts);
        var off = isEnd ? R + 15 : R + 11;
        svg.appendChild(h("text", {
          x: p[0] + dir[0] * off, y: p[1] + dir[1] * off, class: "kp-v-ptr is-focus",
          style: "font-size: 14px; font-style: italic; " + HALO, "data-mark": v,
        }, marks.join(",")));
      }
    }

    // ---- 表 ----
    var x0 = TX + RH;
    svg.appendChild(h("text", { x: TX + RH / 2, y: TY - 14, class: "kp-v-text is-sub", style: "font-size: 12px" }, "i＼j"));
    for (var t = 0; t < n; t++) {
      var hk = s.phase !== "init" && s.k === t;
      svg.appendChild(h("text", {
        x: x0 + t * CS + CS / 2, y: TY - 14, class: hk ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: "font-size: 13px", "data-colhead": t,
      }, hk ? "k=" + t : String(t)));
      svg.appendChild(h("text", {
        x: TX + RH / 2, y: TY + t * CS + CS / 2, class: hk ? "kp-v-ptr is-focus" : "kp-v-text is-sub",
        style: "font-size: 13px", "data-rowhead": t,
      }, hk ? "k=" + t : String(t)));
    }
    var changedSet = Object.create(null);
    s.changed.forEach(function (q) { changedSet[q[0] + "," + q[1]] = true; });
    var wrongSet = Object.create(null);
    s.wrong.forEach(function (q) { wrongSet[q[0] + "," + q[1]] = q[2]; });
    var operand = Object.create(null);
    if (s.phase === "cell") {
      operand[s.i + "," + s.k] = true;
      operand[s.k + "," + s.j] = true;
    } else if (s.phase === "ij") {
      s.cands.forEach(function (q) { operand[s.i + "," + q.k] = true; operand[q.k + "," + s.j] = true; });
    }
    for (var i = 0; i < n; i++) {
      for (var j = 0; j < n; j++) {
        var x = x0 + j * CS, y = TY + i * CS;
        var key = i + "," + j;
        var inK = s.k !== null && (i === s.k || j === s.k);
        var focus = s.i === i && s.j === j;
        var isWrong = key in wrongSet;
        var cls = "kp-v-cell" + (isWrong ? " is-no" : inK ? " is-yes" : "");
        svg.appendChild(h("rect", { x: x, y: y, width: CS, height: CS, class: cls, "data-cell": key }));
        var txt = num(s.d[i][j]);
        var tcls = "kp-v-text";
        if (focus && s.updated) {
          txt = num(s.old) + "→" + num(s.d[i][j]);
          tcls = "kp-v-ptr is-focus";
        }
        var fs = txt.length > 5 ? 11 : txt.length > 3 ? 13 : 15;
        svg.appendChild(h("text", {
          x: isWrong ? x + Math.round(CS * 0.62) : x + CS / 2, y: isWrong ? y + Math.round(CS * 0.38) : y + CS / 2, class: tcls, style: "font-size: " + fs + "px", "data-value": key,
        }, txt));
        if (changedSet[key] && !(focus && s.updated)) {
          // この段（"ijk" ではこれまで）に更新したマス：右上の三角
          svg.appendChild(h("path", {
            d: "M" + (x + CS - 11) + " " + (y + 1.5) + "L" + (x + CS - 1.5) + " " + (y + 1.5) + "L" + (x + CS - 1.5) + " " + (y + 11) + "z",
            class: "kp-v-mark is-focus", "data-changed": key,
          }));
        }
        if (isWrong) {
          // 正しくないマス：二重の枠、値の左に ×、下に正しい値
          svg.appendChild(h("rect", {
            x: x + 2, y: y + 2, width: CS - 4, height: CS - 4, class: "kp-v-cell is-focus",
            style: "fill: none; stroke-width: 2", "data-wrong-frame": key,
          }));
          if (CS >= 44) {
            svg.appendChild(h("rect", {
              x: x + 6, y: y + 6, width: CS - 12, height: CS - 12, class: "kp-v-cell is-focus",
              style: "fill: none; stroke-width: 1.5",
            }));
          }
          svg.appendChild(h("text", {
            x: x + Math.round(CS * 0.3), y: y + Math.round(CS * 0.38), class: "kp-v-ptr is-focus", style: "font-size: 14px", "data-wrong": key,
          }, "×"));
          svg.appendChild(h("text", {
            x: x + CS / 2, y: y + Math.round(CS * 0.72), class: "kp-v-ptr is-focus", style: "font-size: " + (CS >= 44 ? 12 : 10) + "px", "data-truth": key,
          }, "正 " + num(wrongSet[key])));
        }
      }
    }
    // 足す 2 マス（破線の枠）と、比べるマス（太い枠）は、マスの上に重ねて描く
    Object.keys(operand).forEach(function (key) {
      var ij = key.split(",").map(Number);
      svg.appendChild(h("rect", {
        x: x0 + ij[1] * CS + 3, y: TY + ij[0] * CS + 3, width: CS - 6, height: CS - 6, rx: 3,
        class: "kp-v-cell is-focus", style: "fill: none; stroke-width: 2", "stroke-dasharray": "4 3", "data-operand": key,
      }));
    });
    if (s.i !== null) {
      svg.appendChild(h("rect", {
        x: x0 + s.j * CS, y: TY + s.i * CS, width: CS, height: CS, class: "kp-v-cell is-focus", style: "fill: none",
        "data-focus": s.i + "," + s.j,
      }));
    }

    // ---- 式の 1 行 ----
    svg.appendChild(h("text", {
      x: 6, y: dm.fy, class: s.updated ? "kp-v-ptr is-focus" : "kp-v-text", style: "text-anchor: start; font-size: 14px",
      "data-formula": 1,
    }, s.formula));

    // ---- 凡例 ----
    var ly = dm.legendTop;
    var lt = "text-anchor: start; font-size: 12px";
    function sw(x, y, cls, dash, fill) {
      svg.appendChild(h("rect", {
        x: x, y: y - 8, width: 20, height: 16, rx: 2, class: cls, "stroke-dasharray": dash,
        style: fill ? null : "fill: none; stroke-width: 2",
      }));
    }
    function label(x, y, text) {
      svg.appendChild(h("text", { x: x, y: y, class: "kp-v-text is-sub", style: lt }, text));
    }
    if (c.order === "kij") {
      sw(6, ly, "kp-v-cell is-yes", null, true); label(31, ly, "中継点 k の行と列");
      sw(156, ly, "kp-v-cell is-focus", null, false); label(181, ly, "比べるマス (i, j)");
      sw(300, ly, "kp-v-cell is-focus", "4 3", false); label(325, ly, "足す 2 マス");
    } else {
      sw(6, ly, "kp-v-cell is-focus", null, false); label(31, ly, "比べるマス (i, j)");
      sw(156, ly, "kp-v-cell is-focus", "4 3", false); label(181, ly, "足す候補のマス");
      sw(300, ly, "kp-v-cell is-no", null, true);
      svg.appendChild(h("rect", { x: 300, y: ly - 8, width: 20, height: 16, rx: 2, class: "kp-v-cell is-focus", style: "fill: none; stroke-width: 2" }));
      svg.appendChild(h("rect", { x: 303, y: ly - 5, width: 14, height: 10, class: "kp-v-cell is-focus", style: "fill: none; stroke-width: 1.5" }));
      label(325, ly, "× 正しい値と違う");
    }
    var l2 = ly + 26;
    svg.appendChild(h("text", { x: 16, y: l2, class: "kp-v-ptr is-focus", style: "font-size: 12px" }, "5→3"));
    label(34, l2, "今回の更新");
    svg.appendChild(h("path", { d: "M152 " + (l2 - 7) + "L164 " + (l2 - 7) + "L164 " + (l2 + 5) + "z", class: "kp-v-mark is-focus" }));
    label(172, l2, c.order === "kij" ? "この段で更新した" : "更新済み");
    if (c.order === "kij") {
      svg.appendChild(h("circle", { cx: 310, cy: l2, r: 8, class: "kp-v-cell is-answer" }));
      label(325, l2, "頂点 k");
    } else {
      svg.appendChild(h("circle", { cx: 310, cy: l2, r: 8, class: "kp-v-cell is-focus", style: "fill: none" }));
      label(325, l2, "頂点 i, j");
    }
  }

  return {
    title: "ワーシャルフロイド法で、中継点 k を増やしながら距離の表を更新していく",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

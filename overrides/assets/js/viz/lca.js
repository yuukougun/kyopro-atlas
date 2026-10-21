/*
 * 動く図：ダブリングで LCA を求める（深さをそろえてから、k を大きいほうから試して同時に跳ぶ）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="lca" data-config='{"n": 12, "parents": [-1, 0, 0, 1, 1, 2, 3, 4, 6, 7, 5, 8], "query": [11, 9]}'></div>
 * config：
 *   n       … 頂点数（1〜16）。頂点は 0-indexed で、根は 0
 *             葉（子のない頂点）は 6 個まで。横幅は葉の数で決まり、7 個以上では幅 360 で文字が読めなくなるので Error にする
 *   parents … 長さ n の整数の配列。parents[0] = −1（根）、それ以外は親の番号（0 以上 n 未満）。親をたどるとどの頂点も根に着く
 *   query   … LCA を求める 2 頂点 [u, v]
 *
 * 表の段数 L は本文のコードと同じく「2^L ≥ n となる最小の L（ただし 1 以上）」、up[k][v] は v の 2^k 個上の祖先（根の親は根）。
 * ① dep[u] ≥ dep[v] とし、d = dep[u] − dep[v] の 1 の桁 k ごとに u = up[k][u]（コードと同じく k の小さいほうから）。
 *    u = v になったら v が答え。
 * ② k = L−1, …, 0 の順に up[k][u] と up[k][v] を比べ、違えば両方を跳ばす。最後に up[0][u] が答え。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/lca.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("lca", def);
})(function () {
  "use strict";

  var MAX_N = 16;
  var MAX_LEAVES = 6; // 葉 6 個で viewBox の幅 472（幅 360 で約 0.7 倍）

  function isInt(x) { return typeof x === "number" && Number.isInteger(x); }

  function validate(config) {
    if (!config || typeof config !== "object" || Array.isArray(config)) throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var p = config.parents;
    if (!Array.isArray(p) || p.length !== n) throw new Error("parents は長さ n（" + n + "）の配列にする");
    if (p[0] !== -1) throw new Error("parents[0] は −1 にする（根は 0）");
    for (var i = 1; i < n; i++) {
      if (!isInt(p[i]) || p[i] < 0 || p[i] >= n) throw new Error("parents[" + i + "] は 0 以上 n 未満の整数にする");
      if (p[i] === i) throw new Error("parents[" + i + "] が自分自身を指している");
    }
    // 深さ：親をたどって根に着くかを確かめながら求める
    var dep = new Array(n).fill(-1);
    dep[0] = 0;
    for (var v = 1; v < n; v++) {
      var chain = [];
      var x = v;
      while (dep[x] < 0) {
        if (chain.indexOf(x) >= 0) throw new Error("parents に閉路がある（頂点 " + x + "）。木にする");
        chain.push(x);
        x = p[x];
      }
      for (var j = chain.length - 1; j >= 0; j--) dep[chain[j]] = dep[p[chain[j]]] + 1;
    }
    var hasChild = new Array(n).fill(false);
    for (i = 1; i < n; i++) hasChild[p[i]] = true;
    var leaves = hasChild.filter(function (b) { return !b; }).length;
    if (leaves > MAX_LEAVES) {
      throw new Error("葉（子のない頂点）が " + leaves + " 個ある。幅 360 で読めるよう " + MAX_LEAVES + " 個までにする");
    }
    var q = config.query;
    if (!Array.isArray(q) || q.length !== 2 || !isInt(q[0]) || !isInt(q[1]) ||
        q[0] < 0 || q[0] >= n || q[1] < 0 || q[1] >= n) {
      throw new Error("query は 0 以上 n 未満の 2 頂点 [u, v] にする");
    }
    return { n: n, parents: p.slice(), dep: dep, query: [q[0], q[1]] };
  }

  function tableOf(c) {
    var n = c.n;
    var L = 1;
    while ((1 << L) < n) L++;
    var up = [];
    up.push(c.parents.map(function (x) { return x < 0 ? 0 : x; }));
    for (var k = 0; k + 1 < L; k++) {
      up.push(up[k].map(function (x) { return up[k][x]; }));
    }
    return { L: L, up: up };
  }

  function bin(d, L) {
    var s = d.toString(2);
    while (s.length < L) s = "0" + s;
    return s;
  }

  // 状態：phase（start・align・aligned・compare・jump・done）、u・v（いまの位置）、cmp（比べている 2 頂点）、
  //   arrows（この状態で跳んだ [元, 先, 側]）、table（"align" か "jump"）、rows（k ごとの表の値）、focus（注目の段）、
  //   answer（答え。done のときだけ）、caption
  function states(config) {
    var c = validate(config);
    var T = tableOf(c);
    var L = T.L, up = T.up, dep = c.dep;
    var u = c.query[0], v = c.query[1];
    var out = [];
    var alignRows = [];
    var jumpRows = [];
    for (var k = 0; k < L; k++) {
      alignRows.push({ bit: 0, a: null, res: null });
      jumpRows.push({ a: null, b: null, res: null });
    }
    function copyRows(rows) { return rows.map(function (r) { return Object.assign({}, r); }); }
    function push(s) {
      s.u = u;
      s.v = v;
      s.L = L;
      s.rows = copyRows(s.table === "align" ? alignRows : jumpRows);
      if (!s.cmp) s.cmp = [];
      if (!s.arrows) s.arrows = [];
      if (s.focus == null) s.focus = null;
      if (s.answer == null) s.answer = null;
      out.push(s);
    }

    var q0 = u, q1 = v;
    var first = "lca(" + q0 + ", " + q1 + ") を求める。表は L = " + L + " 段（k = 0〜" + (L - 1) + "）で、up[k][x] は x の 2^k 個上の祖先（根の親は根 0）。";
    if (dep[u] < dep[v]) {
      var t = u; u = v; v = t;
      first += "dep[" + q0 + "] = " + dep[q0] + " < dep[" + q1 + "] = " + dep[q1] + " なので入れ替え、深いほうを u = " + u + "、v = " + v + " とする。";
    } else {
      first += "dep[" + u + "] = " + dep[u] + " ≥ dep[" + v + "] = " + dep[v] + " なので u = " + u + "、v = " + v + " とする。";
    }
    var d = dep[u] - dep[v];
    var u0 = u;
    for (k = 0; k < L; k++) alignRows[k].bit = (d >> k) & 1;
    push({ phase: "start", table: "align", caption: first });

    // ① 深さをそろえる
    if (d === 0) {
      for (k = 0; k < L; k++) alignRows[k].res = "そのまま";
      push({
        phase: "aligned", table: "align",
        caption: "① 深さの差 d = 0 なので、上げる必要はない。",
      });
    } else {
      for (k = 0; k < L; k++) {
        if (!((d >> k) & 1)) {
          alignRows[k].res = "そのまま";
          continue;
        }
        var nu = up[k][u];
        alignRows[k].a = nu;
        alignRows[k].res = "上げる";
        var from = u;
        u = nu;
        push({
          phase: "align", table: "align", focus: k, arrows: [[from, nu, "u"]],
          caption: "① 深さの差 d = " + d + "（2 進数で " + bin(d, L) + "）の k = " + k + " の桁が 1 なので、u を 2^" + k +
            " = " + (1 << k) + " 個上げて up[" + k + "][" + from + "] = " + nu + " にする。",
        });
      }
      for (k = 0; k < L; k++) if (!alignRows[k].res) alignRows[k].res = "そのまま";
      push({
        phase: "aligned", table: "align",
        caption: "深さがそろった（どちらも " + dep[u] + "）。" +
          (u === v ? "u と v が一致したので、② には進まない。" : "u = " + u + " と v = " + v + " は違うので、② に進む。"),
      });
    }

    if (u === v) {
      push({
        phase: "done", table: "align", answer: u,
        caption: q0 === q1
          ? "u = v = " + u + " で同じ頂点なので、答えは " + u + " である。"
          : "u = v = " + u + " になった。v = " + v + " は u = " + u0 + " の祖先だったので、答えは " + u + " である。",
      });
      return out;
    }

    // ② k を大きいほうから試し、2^k 個上が違うときだけ両方を跳ばす
    for (k = L - 1; k >= 0; k--) {
      var a = up[k][u], b = up[k][v];
      var step = 1 << k;
      jumpRows[k].a = a;
      jumpRows[k].b = b;
      var clamp = step > dep[u] ? "（根より上は根 0 で止まる）" : "";
      var head = "② k = " + k + "：u = " + u + " の " + step + " 個上と v = " + v + " の " + step + " 個上";
      if (a === b) {
        jumpRows[k].res = "跳ばない";
        push({
          phase: "compare", table: "jump", focus: k, cmp: [a, b], same: true,
          caption: head + "はどちらも " + a + clamp + "。同じなので跳ばない（跳ぶと LCA を通り過ぎるかもしれない）。",
        });
      } else {
        jumpRows[k].res = "跳ぶ";
        push({
          phase: "compare", table: "jump", focus: k, cmp: [a, b], same: false,
          caption: head + "は " + a + " と " + b + " で違う。まだ LCA より下にいるので、両方を " + step + " 個上げる。",
        });
        var fu = u, fv = v;
        u = a;
        v = b;
        push({
          phase: "jump", table: "jump", focus: k, arrows: [[fu, a, "u"], [fv, b, "v"]],
          caption: "② k = " + k + "：跳んで u = " + u + "、v = " + v + " になった（どちらも深さ " + dep[u] + "）。",
        });
      }
    }
    var ans = up[0][u];
    push({
      phase: "done", table: "jump", answer: ans,
      caption: "すべての k を試した。u = " + u + "、v = " + v + " は LCA のすぐ下の子にいるので、答えは up[0][" + u + "] = " +
        ans + " である。",
    });
    return out;
  }

  // 描画の寸法
  var PITCH = 64; // 葉の間隔
  var DY = 54; // 深さ 1 の間隔
  var R = 16; // 頂点の半径
  var LABEL_W = 52; // 左の「深さ d」
  var SIDE = 34; // 木の左右の余白（u・v の名札の分）
  var COLS = [40, 56, 84, 84, 84]; // 表の列の幅
  var ROW = 30;
  var MIN_W = 380;
  var LINE = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.4";
  var LINE_ON = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3";
  var RING_CMP = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.5;stroke-dasharray:5 3";
  var RING_ANS = "fill:none;stroke:var(--md-primary-fg-color);stroke-width:2.5";
  var HALO = "paint-order:stroke;stroke:var(--md-default-bg-color);stroke-width:4px;stroke-linejoin:round";

  // 木の配置：子を番号の順に並べ、葉を左から 1 列ずつ、内側の頂点は最初と最後の子の真ん中
  function layout(c) {
    var n = c.n;
    var ch = [];
    for (var i = 0; i < n; i++) ch.push([]);
    for (i = 1; i < n; i++) ch[c.parents[i]].push(i);
    var col = new Array(n).fill(0);
    var leaves = 0;
    // 反復の帰りがけ順（パス状の木でも再帰を深くしない）
    var stack = [[0, 0]];
    while (stack.length) {
      var top = stack[stack.length - 1];
      var x = top[0];
      if (top[1] < ch[x].length) {
        stack.push([ch[x][top[1]++], 0]);
        continue;
      }
      stack.pop();
      if (ch[x].length === 0) col[x] = leaves++;
      else col[x] = (col[ch[x][0]] + col[ch[x][ch[x].length - 1]]) / 2;
    }
    var maxDep = Math.max.apply(null, c.dep);
    return { col: col, leaves: leaves, maxDep: maxDep };
  }

  function dims(config) {
    var c = validate(config);
    var T = tableOf(c);
    var lay = layout(c);
    var treeW = LABEL_W + 2 * SIDE + (lay.leaves - 1) * PITCH + 2 * R;
    var tableW = COLS.reduce(function (s, w) { return s + w; }, 0);
    var width = Math.max(MIN_W, treeW, tableW + 24);
    var treeTop = 50;
    var tableHead = treeTop + lay.maxDep * DY + R + 34; // 表の見出しの行
    var tableTop = tableHead + 16; // 列名の行の上端
    var height = tableTop + ROW * (T.L + 1) + 10;
    return {
      c: c, T: T, lay: lay, width: width, height: height, treeTop: treeTop,
      treeX: LABEL_W + (width - treeW) / 2 + SIDE + R, tableHead: tableHead, tableTop: tableTop,
      tableX: (width - tableW) / 2, tableW: tableW,
    };
  }

  function viewBox(config) {
    var D = dims(config);
    return "0 0 " + D.width + " " + D.height;
  }

  var cache = typeof WeakMap === "function" ? new WeakMap() : null;
  function dimsFor(config) {
    var d = cache && cache.get(config);
    if (!d) {
      d = dims(config);
      if (cache) cache.set(config, d);
    }
    return d;
  }

  function render(svg, s, config, h) {
    var D = dimsFor(config);
    var c = D.c, lay = D.lay, n = c.n;
    function nx(x) { return D.treeX + lay.col[x] * PITCH; }
    function ny(x) { return D.treeTop + c.dep[x] * DY; }

    function head(x, y, dx, dy, cls) {
      var len = Math.sqrt(dx * dx + dy * dy) || 1;
      var ux = dx / len, uy = dy / len, AL = 10, AW = 5;
      var bx = x - ux * AL, by = y - uy * AL;
      svg.appendChild(h("path", {
        d: "M" + x + " " + y + "L" + (bx - uy * AW) + " " + (by + ux * AW) + "L" + (bx + uy * AW) + " " + (by - ux * AW) + "Z",
        class: cls,
      }));
    }

    // 見出し
    var q = c.query;
    var title = "lca(" + q[0] + ", " + q[1] + ")：" +
      (s.phase === "done" ? "答え " + s.answer : s.table === "align" ? "① 深さをそろえる" : "② 同時に跳ぶ");
    svg.appendChild(h("text", { x: D.width / 2, y: 14, class: "kp-v-ptr is-a", style: "font-size:15px" }, title));

    // 深さの目盛り
    for (var d = 0; d <= lay.maxDep; d++) {
      svg.appendChild(h("text", {
        x: 6, y: D.treeTop + d * DY, class: "kp-v-text is-sub", style: "text-anchor:start;font-size:13px",
      }, "深さ " + d));
    }

    // 辺
    for (var x = 1; x < n; x++) {
      var p = c.parents[x];
      svg.appendChild(h("line", { x1: nx(p), y1: ny(p), x2: nx(x), y2: ny(x), style: LINE }));
    }

    // 跳んだ矢印：u 側と v 側を外へふくらませる
    var mid = (nx(s.u) + nx(s.v)) / 2;
    s.arrows.forEach(function (a) {
      var fx = nx(a[0]), fy = ny(a[0]), tx = nx(a[1]), ty = ny(a[1]);
      var side = a[2] === "u" ? -1 : 1;
      if (s.arrows.length === 2) side = nx(a[1]) < mid || (nx(a[1]) === mid && a[2] === "u") ? -1 : 1;
      var span = Math.abs(fy - ty);
      var bend = side * Math.max(28, span * 0.45);
      var sx = fx + side * R * 0.8, sy = fy - R * 0.6;
      var ex = tx + side * R * 0.8, ey = ty + R * 0.6;
      var cx = (sx + ex) / 2 + bend, cy = (sy + ey) / 2;
      // 先の向き：制御点から終点へ
      var hx = ex - cx, hy = ey - cy, hl = Math.sqrt(hx * hx + hy * hy) || 1;
      var bx = ex - hx / hl * 8, by = ey - hy / hl * 8;
      svg.appendChild(h("path", { d: "M" + sx + " " + sy + "Q" + cx + " " + cy + " " + bx + " " + by, style: LINE_ON }));
      head(ex, ey, hx, hy, "kp-v-mark is-b");
    });

    // 比べている 2 頂点（破線の輪）。同じ頂点のときは半径を変えて二重にし、2 つを比べていることが見えるようにする
    s.cmp.forEach(function (x, i) {
      var twice = i === 1 && s.cmp[0] === x;
      svg.appendChild(h("circle", { cx: nx(x), cy: ny(x), r: twice ? R + 11 : R + 6, style: RING_CMP }));
    });

    // 頂点
    for (x = 0; x < n; x++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      var cur = x === s.u || x === s.v;
      var ans = s.answer === x;
      if (cur && !ans) cls.push("is-focus");
      if (ans) { cls.push("is-answer"); tcls.push("is-on-answer"); }
      if (ans) svg.appendChild(h("circle", { cx: nx(x), cy: ny(x), r: R + 5, style: RING_ANS }));
      svg.appendChild(h("circle", { cx: nx(x), cy: ny(x), r: R, class: cls.join(" ") }));
      svg.appendChild(h("text", {
        x: nx(x), y: ny(x), class: tcls.join(" "), style: cur || ans ? "font-weight:700" : null,
      }, x));
    }

    // 名札：u は左、v は右、答えは上
    function tag(x, text, dx, anchor, cls) {
      svg.appendChild(h("text", {
        x: nx(x) + dx, y: ny(x), class: cls, style: "font-size:15px;text-anchor:" + anchor + ";" + HALO,
      }, text));
    }
    tag(s.u, "u", -(R + 9), "end", "kp-v-ptr is-b");
    tag(s.v, "v", R + 9, "start", "kp-v-ptr is-b");
    // 「LCA」は親への辺と反対の側の斜め上に置き、辺に重ねない（親が真上か根なら右上）
    if (s.answer != null) {
      var an = s.answer, ap = c.parents[an];
      var left = ap >= 0 && nx(ap) > nx(an);
      svg.appendChild(h("text", {
        x: nx(an) + (left ? -(R + 2) : R + 2), y: ny(an) - R - 6, class: "kp-v-ptr is-focus",
        style: "font-size:14px;text-anchor:" + (left ? "end" : "start") + ";" + HALO,
      }, "LCA"));
    }

    // 表
    var align = s.table === "align";
    var L = D.T.L;
    var dd = Math.abs(c.dep[q[0]] - c.dep[q[1]]);
    var bits = dd.toString(2);
    while (bits.length < L) bits = "0" + bits;
    svg.appendChild(h("text", {
      x: D.width / 2, y: D.tableHead, class: "kp-v-ptr is-a", style: "font-size:14px",
    }, align ? "① 深さの差 d = " + dd + "（2 進数で " + bits + "）の 1 の桁で u を上げる" : "② k を大きいほうから試す（違えば跳ぶ）"));
    var names = align ? ["k", "2^k", "d の桁", "up[k][u]", "結果"] : ["k", "2^k", "up[k][u]", "up[k][v]", "結果"];
    var colX = [];
    var acc = D.tableX;
    COLS.forEach(function (w) { colX.push(acc + w / 2); acc += w; });
    var y0 = D.tableTop;
    names.forEach(function (t, i) {
      svg.appendChild(h("text", { x: colX[i], y: y0 + ROW / 2, class: "kp-v-text is-sub", style: "font-size:13px" }, t));
    });
    for (var r = 0; r < L; r++) {
      var k = L - 1 - r;
      var row = s.rows[k];
      var ry = y0 + ROW * (r + 1);
      var focus = s.focus === k;
      svg.appendChild(h("rect", {
        x: D.tableX, y: ry + 2, width: D.tableW, height: ROW - 4, rx: 5,
        class: "kp-v-cell" + (focus ? " is-focus" : ""),
      }));
      var vals = align
        ? [k, 1 << k, row.bit, row.a == null ? "" : row.a, row.res || ""]
        : [k, 1 << k, row.a == null ? "" : row.a, row.b == null ? "" : row.b, row.res || ""];
      vals.forEach(function (t, i) {
        var st = "font-size:14px";
        var cl = "kp-v-text";
        if (focus) st += ";font-weight:700";
        if (i === 4 && (t === "跳ばない" || t === "そのまま")) cl += " is-dim";
        if (i === 4 && (t === "跳ぶ" || t === "上げる")) st += ";font-weight:700";
        svg.appendChild(h("text", { x: colX[i], y: ry + ROW / 2, class: cl, style: st }, t));
      });
    }
  }

  return {
    title: "ダブリングで LCA を求める：深さをそろえてから同時に跳ぶ",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

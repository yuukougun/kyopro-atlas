/*
 * 動く図：商の列挙（⌊N/i⌋ が同じ値になる i の区間 [l, r] を 1 つずつ取り、Σ ⌊N/i⌋ を区間ごとに足す）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="floor-quotient-enum" data-config='{"n": 20}'></div>
 * config：
 *   n … 正の整数 N（1〜30）。i = 1〜N の ⌊N/i⌋ を棒の階段に描く
 *
 * ステップ：(1) 階段全体と √N の縦線を示す → (2) l = 1 から、q = ⌊N/l⌋、r = ⌊N/q⌋ を求めて区間 [l, r] を強調し、
 * 和に (r − l + 1) × q を足して l ← r + 1 とする（区間ごとに 1 状態）→ (3) l > N で終わり、区間の数と和を示す。
 * √N より左（l ≤ √N）の区間は幅 1、右（l > √N）の区間は商が √N 未満になることを caption に書く。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/floor-quotient-enum.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("floor-quotient-enum", def);
})(function () {
  "use strict";

  var MAX_N = 30; // 棒が 360px の幅でも見分けられる本数にとどめる

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    return { n: n };
  }

  // s = ⌊√N⌋（整数だけで求める）
  function isqrt(n) {
    var s = Math.floor(Math.sqrt(n));
    while (s * s > n) s--;
    while ((s + 1) * (s + 1) <= n) s++;
    return s;
  }

  // √N の表示：平方数なら「√16 = 4」、そうでなければ小数第 2 位まで「√20 ≈ 4.47」
  function sqrtText(n, s) {
    return s * s === n ? "√" + n + " = " + s : "√" + n + " ≈ " + Math.sqrt(n).toFixed(2);
  }

  // 商が同じ区間の列：{l, r, q}
  function blocksOf(n) {
    var out = [];
    for (var l = 1; l <= n; ) {
      var q = Math.floor(n / l);
      var r = Math.floor(n / q);
      out.push({ l: l, r: r, q: q });
      l = r + 1;
    }
    return out;
  }

  // 各ステップの状態：phase（start・block・done）、cur（いま足した区間の番号。start は −1、done は区間の数）、
  // sum（cur までの区間を足した和）、l・q・r（block のとき）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var s = isqrt(n);
    var rt = sqrtText(n, s);
    var blocks = blocksOf(n);
    var out = [];
    var sum = 0;

    out.push({
      phase: "start", n: n, s: s, blocks: blocks, cur: -1, sum: 0,
      caption: "N = " + n + " の ⌊N/i⌋ を i = 1〜" + n + " の棒で並べた。" +
        (s < n
          ? rt + " の縦線より左（i ≤ √N）は値が 1 個ずつ変わり、右（i > √N）の値はどれも √N 未満である。"
          : "棒は " + rt + " の縦線より左（i ≤ √N）の 1 本だけである。") +
        "l = 1 から、商が同じ区間をまとめて足していく。",
    });
    for (var k = 0; k < blocks.length; k++) {
      var b = blocks[k];
      var w = b.r - b.l + 1;
      var add = w * b.q;
      sum += add;
      var side = b.l <= s
        ? "l ≤ √N の側なので、幅 1 の区間である。"
        : "l > √N の側なので、商 q = " + b.q + " は √N より小さい。";
      out.push({
        phase: "block", n: n, s: s, blocks: blocks, cur: k, sum: sum, l: b.l, q: b.q, r: b.r,
        caption: "l = " + b.l + "、q = ⌊" + n + "/" + b.l + "⌋ = " + b.q + "、r = ⌊" + n + "/" + b.q + "⌋ = " + b.r + "。" +
          "和に (" + b.r + " − " + b.l + " + 1) × " + b.q + " = " + add + " を足して " + sum + " になる。" + side +
          "次の左端は l = r + 1 = " + (b.r + 1) + "。",
      });
    }
    var left = blocks.filter(function (b) { return b.l <= s; }).length;
    out.push({
      phase: "done", n: n, s: s, blocks: blocks, cur: blocks.length, sum: sum,
      caption: "l = " + (n + 1) + " > N なので終わる。区間は " + blocks.length + " 個（√N より左に " + left + " 個、右に " +
        (blocks.length - left) + " 個）で、Σ ⌊" + n + "/i⌋ = " + sum + " である。",
    });
    return out;
  }

  // 描画の寸法
  var LEFT = 22; // 縦軸の左の余白
  var RIGHT = 12;
  var TOP = 60; // 高さ N の棒の上端（上の 2 行の文字と、棒の上の値の間をあける）
  var CHART_H = 190; // 高さ N の棒の高さ
  var AXIS = TOP + CHART_H; // 横軸
  var HEIGHT = AXIS + 66;
  var MIN_W = 300; // viewBox の最小の幅（N が小さいときに上の文字が切れないように）

  function barW(n) {
    return Math.max(10, Math.min(36, Math.floor(340 / n)));
  }

  function viewBox(config) {
    var n = config.n;
    return "0 0 " + Math.max(MIN_W, LEFT + n * barW(n) + RIGHT) + " " + HEIGHT;
  }

  function render(svg, st, config, h) {
    var n = st.n;
    var W = barW(n);
    var unit = CHART_H / n;
    var small = W < 16; // 棒が細いときは文字を小さくし、添字を間引く
    function xl(i) { return LEFT + (i - 1) * W; } // 棒 i の左端
    function yt(v) { return AXIS - v * unit; }

    var cur = st.cur;
    var focus = st.phase === "block" ? st.blocks[cur] : null;

    // 棒：足し終えた区間は塗り、まだの区間は点線の枠
    st.blocks.forEach(function (b, k) {
      var done = k <= cur;
      for (var i = b.l; i <= b.r; i++) {
        var attrs = { x: xl(i), y: yt(b.q), width: W, height: b.q * unit, class: "kp-v-cell" + (done ? " is-yes" : "") };
        if (!done) attrs["stroke-dasharray"] = "3 2";
        attrs.style = "stroke-width: 1";
        svg.appendChild(h("rect", attrs));
      }
    });
    // 段（同じ商の区間）を太枠で囲む。いまの区間はさらに太く
    st.blocks.forEach(function (b, k) {
      var on = focus && k === cur;
      svg.appendChild(h("rect", {
        x: xl(b.l), y: yt(b.q), width: (b.r - b.l + 1) * W, height: b.q * unit,
        class: "kp-v-cell" + (on ? " is-focus" : ""), style: on ? "fill: none" : "fill: none; stroke-width: 2",
      }));
      svg.appendChild(h("text", {
        x: xl(b.l) + (b.r - b.l + 1) * W / 2, y: yt(b.q) - (small ? 7 : 9),
        class: on ? "kp-v-ptr is-focus" : "kp-v-text" + (small ? " is-sub" : ""), style: on && !small ? "font-size: 16px" : null,
      }, b.q));
    });

    // 横軸と添字 i
    svg.appendChild(h("line", { x1: LEFT - 4, y1: AXIS, x2: xl(n + 1) + 4, y2: AXIS, class: "kp-v-cell", style: "stroke-width: 1.5" }));
    svg.appendChild(h("text", { x: LEFT - 12, y: AXIS + 12, class: "kp-v-text is-sub" }, "i"));
    // 棒が細いときは 1・5 の倍数・N と、いまの区間の l・r だけ書く（l・r の隣の数は重なるので省く）
    function isEnd(i) { return !!focus && (i === focus.l || i === focus.r); }
    for (var i = 1; i <= n; i++) {
      var show = !small || isEnd(i) ||
        ((i === 1 || i === n || i % 5 === 0) && !isEnd(i - 1) && !isEnd(i + 1));
      if (show) svg.appendChild(h("text", { x: xl(i) + W / 2, y: AXIS + 12, class: "kp-v-text is-sub" }, i));
    }

    // √N の縦線（棒 s と s + 1 の間）と、左右の区別
    var sx = xl(st.s + 1);
    svg.appendChild(h("line", {
      x1: sx, y1: 18, x2: sx, y2: AXIS + 4, class: "kp-v-cell", style: "stroke-width: 1.5", "stroke-dasharray": "5 3",
    }));
    svg.appendChild(h("text", { x: sx, y: 9, class: "kp-v-ptr is-a" }, st.s * st.s === n ? "√N = " + st.s : "√N ≈ " + Math.sqrt(n).toFixed(2)));
    svg.appendChild(h("text", { x: sx - 5, y: 27, class: "kp-v-ptr is-a", style: "text-anchor: end" }, "1 個ずつ"));
    if (st.s < n) svg.appendChild(h("text", { x: sx + 5, y: 27, class: "kp-v-ptr is-a", style: "text-anchor: start" }, "商 < √N"));

    // いまの区間の l と r を三角の印で示す
    if (focus) {
      var py = AXIS + 22;
      var lx = xl(focus.l) + W / 2;
      var rx = xl(focus.r) + W / 2;
      if (focus.l === focus.r) {
        svg.appendChild(h("path", { d: "M" + (lx - 6) + " " + (py + 8) + "h12l-6 -8z", class: "kp-v-mark is-focus" }));
        svg.appendChild(h("text", { x: lx, y: py + 18, class: "kp-v-ptr is-focus" }, "l = r"));
      } else {
        svg.appendChild(h("line", { x1: lx, y1: py + 4, x2: rx, y2: py + 4, class: "kp-v-cell is-focus", style: "stroke-width: 2" }));
        [["l", lx], ["r", rx]].forEach(function (p) {
          svg.appendChild(h("path", { d: "M" + (p[1] - 6) + " " + (py + 8) + "h12l-6 -8z", class: "kp-v-mark is-focus" }));
          svg.appendChild(h("text", { x: p[1], y: py + 18, class: "kp-v-ptr is-focus" }, p[0]));
        });
      }
    }

    // 下の行：区間の数と和
    var count = st.phase === "start" ? 0 : st.phase === "done" ? st.blocks.length : cur + 1;
    var msg = st.phase === "done"
      ? "区間 " + count + " 個、和 = " + st.sum + "（終わり）"
      : "足した区間 " + count + " 個、和 = " + st.sum;
    svg.appendChild(h("text", { x: LEFT, y: HEIGHT - 8, class: "kp-v-ptr is-b", style: "text-anchor: start" }, msg));
  }

  return {
    title: "商の列挙で、⌊N/i⌋ が同じ値の区間をまとめて足す",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

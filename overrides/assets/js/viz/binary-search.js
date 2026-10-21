/*
 * 動く図の見本：二分探索で境界を探す（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="binary-search" data-config='{"array": [1, 3, 3, 5, 8, 13, 21, 34], "target": 8}'></div>
 * config：
 *   array  … 広義単調増加の数の配列（1〜16 個）
 *   target … 探す値 x
 *   mode   … "lower"（既定。a[i] ≥ x を満たす最初の i）か "upper"（a[i] > x を満たす最初の i）
 *
 * 条件「a[i] ≥ x」は i について単調（ある所から先はずっと満たす）なので、満たさない側の端 ng と満たす側の端 ok を
 * 番兵（ng = −1、ok = N）から始めて、間を半分ずつ縮める。常に「a[ng] は満たさず、a[ok] は満たす」が成り立ち、
 * ok − ng = 1 になったときの ok が答えになる。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/binary-search.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("binary-search", def);
})(function () {
  "use strict";

  var MAX_N = 16;

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var a = config.array;
    if (!Array.isArray(a) || a.length < 1 || a.length > MAX_N) {
      throw new Error("array は 1〜" + MAX_N + " 個の数の配列にする");
    }
    for (var i = 0; i < a.length; i++) {
      if (typeof a[i] !== "number" || !isFinite(a[i])) throw new Error("array の要素は数にする");
      if (i > 0 && a[i - 1] > a[i]) throw new Error("array が単調（広義単調増加）でない");
    }
    if (typeof config.target !== "number" || !isFinite(config.target)) throw new Error("target は数にする");
    var mode = config.mode == null ? "lower" : config.mode;
    if (mode !== "lower" && mode !== "upper") throw new Error('mode は "lower" か "upper" にする');
    return { array: a.slice(), target: config.target, mode: mode };
  }

  // 各ステップの状態：ng・ok（いまの両端）、mid（調べている位置。なければ null）、phase、caption
  function states(config) {
    var c = validate(config);
    var a = c.array;
    var x = c.target;
    var upper = c.mode === "upper";
    var cond = upper ? "a[i] > " + x : "a[i] ≥ " + x;
    var test = upper ? function (v) { return v > x; } : function (v) { return v >= x; };
    var n = a.length;
    var ng = -1;
    var ok = n;
    var out = [];

    out.push({
      phase: "start", ng: ng, ok: ok, mid: null,
      caption: "条件 " + cond + " を満たす最初の i を探す。満たさない側の端 ng = −1 と、満たす側の端 ok = " + n +
        "（どちらも配列の外の番兵）から始める。",
    });
    while (ok - ng > 1) {
      var mid = Math.floor((ng + ok) / 2);
      var yes = test(a[mid]);
      out.push({
        phase: "probe", ng: ng, ok: ok, mid: mid, yes: yes,
        caption: "mid = ⌊(" + ng + " + " + ok + ") / 2⌋ = " + mid + "。a[" + mid + "] = " + a[mid] + " は条件 " + cond +
          (yes ? " を満たす。" : " を満たさない。"),
      });
      if (yes) ok = mid;
      else ng = mid;
      out.push({
        phase: "move", ng: ng, ok: ok, mid: null, moved: yes ? "ok" : "ng",
        caption: (yes ? "ok" : "ng") + " を " + mid + " に動かす。答えは ng < i ≤ ok、つまり " + (ng + 1) + " 以上 " + ok +
          " 以下にある。",
      });
    }
    out.push({
      phase: "done", ng: ng, ok: ok, mid: null,
      caption: "ok − ng = 1 になったので終わる。" +
        (ok < n ? "答えは i = " + ok + "（a[" + ok + "] = " + a[ok] + "）。" : "条件を満たす i はなく、答えは N = " + n + "。"),
    });
    return out;
  }

  // 描画の寸法：列 k（−1〜N）を x = (k + 1) × W に置く
  var W = 52;
  var CELL = 44;
  var TOP = 26; // 枠の上端
  var HEIGHT = 120;

  function viewBox(config) {
    return "0 0 " + (config.array.length + 2) * W + " " + HEIGHT;
  }

  function render(svg, s, config, h) {
    var a = config.array;
    var n = a.length;
    function cx(k) { return (k + 1) * W + W / 2; }

    for (var k = -1; k <= n; k++) {
      var x0 = cx(k) - CELL / 2;
      if (k === -1 || k === n) {
        svg.appendChild(h("rect", { x: x0, y: TOP, width: CELL, height: CELL, rx: 6, class: "kp-v-cell is-sentinel" }));
      } else {
        var cls = ["kp-v-cell"];
        var tcls = ["kp-v-text"];
        if (k <= s.ng) { cls.push("is-no"); tcls.push("is-dim"); }
        else if (k >= s.ok) cls.push("is-yes");
        if (k === s.mid) cls.push("is-focus");
        if (s.phase === "done" && k === s.ok) { cls.push("is-answer"); tcls.push("is-on-answer"); }
        svg.appendChild(h("rect", { x: x0, y: TOP, width: CELL, height: CELL, rx: 6, class: cls.join(" ") }));
        svg.appendChild(h("text", { x: cx(k), y: TOP + CELL / 2, class: tcls.join(" ") }, a[k]));
      }
      svg.appendChild(h("text", { x: cx(k), y: TOP + CELL + 13, class: "kp-v-text is-sub" }, k === -1 ? "−1" : k));
    }

    // mid は枠の上に、ng と ok は番号の下に、三角の印と名前で示す
    if (s.mid != null) {
      var m = cx(s.mid);
      svg.appendChild(h("text", { x: m, y: 7, class: "kp-v-ptr is-focus" }, "mid"));
      svg.appendChild(h("path", { d: "M" + (m - 6) + " 15h12l-6 8z", class: "kp-v-mark is-focus" }));
    }
    var py = TOP + CELL + 22;
    [["ng", s.ng, "is-a"], ["ok", s.ok, "is-b"]].forEach(function (p) {
      var px = cx(p[1]);
      svg.appendChild(h("path", { d: "M" + (px - 6) + " " + (py + 8) + "h12l-6 -8z", class: "kp-v-mark " + p[2] }));
      svg.appendChild(h("text", { x: px, y: py + 18, class: "kp-v-ptr " + p[2] }, p[0]));
    });
  }

  return {
    title: "二分探索で、単調な条件を満たす最初の位置を探す",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

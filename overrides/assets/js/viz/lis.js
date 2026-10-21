/*
 * 動く図：最長増加部分列（LIS）の二分探索版で、長さごとの末尾の最小値 L が 1 か所ずつ変わる様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="lis" data-config='{"array": [3, 1, 4, 1, 5, 9, 2, 6], "strict": true}'></div>
 * config：
 *   array  … −99 以上 99 以下の整数の配列（1〜8 個。N = 8 で viewBox の幅 404、スマホの幅 360 でも 0.76 倍ほどで字が読める）
 *   strict … true（既定。狭義の増加。位置は lower_bound＝x 以上の最初の位置）か
 *            false（広義の増加。位置は upper_bound＝x より大きい最初の位置）
 *
 * L[k] ＝「ここまでに見た要素で作れる長さ k + 1 の増加部分列の、末尾として取りうる最小値」。L は昇順に並ぶ。
 * 左から a[i] = x を見るたびに、二分探索で位置 k を求め、k < |L| なら L[k] を x に置き換え、k = |L| なら末尾に追加する。
 * k + 1 は a[i] で終わる増加部分列の最長 dp[i] で、素朴な O(N^2) の DP（a[j] < a[i] となる左の dp[j] の最大 + 1）と一致する。
 * 図の中段には素朴な DP の dp[i] を並べ、置換・追加のたびに同じ値が出ることを対比する。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/lis.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("lis", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_V = 99;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var a = config.array;
    if (!Array.isArray(a) || a.length < 1 || a.length > MAX_N) {
      throw new Error("array は 1〜" + MAX_N + " 個の整数の配列にする");
    }
    for (var i = 0; i < a.length; i++) {
      if (!isInt(a[i]) || a[i] < -MAX_V || a[i] > MAX_V) {
        throw new Error("array の要素は −" + MAX_V + " 以上 " + MAX_V + " 以下の整数にする");
      }
    }
    var strict = config.strict == null ? true : config.strict;
    if (typeof strict !== "boolean") throw new Error("strict は true か false にする");
    return { array: a.slice(), strict: strict };
  }

  function fmt(v) {
    return v < 0 ? "−" + -v : String(v);
  }

  function listText(L) {
    return L.length ? "(" + L.map(fmt).join(", ") + ")" : "空";
  }

  // 素朴な O(N^2) の DP：dp[i] ＝ a[i] で終わる増加部分列の長さの最大
  function naive(a, strict) {
    var dp = [];
    for (var i = 0; i < a.length; i++) {
      var best = 0;
      for (var j = 0; j < i; j++) {
        if ((strict ? a[j] < a[i] : a[j] <= a[i]) && dp[j] > best) best = dp[j];
      }
      dp.push(best + 1);
    }
    return dp;
  }

  // 各ステップの状態：i（いま入れる要素の添字。start は −1、done は N）、L（その時点の L）、k（位置。なければ null）、
  // old（置き換える前の L[k]。追加なら null）、dp（決まった dp[i]。未定は null）、phase、caption
  //   phase：start・find（位置 k を二分探索で求める。L は入れる前）・update（置換か追加をした後）・done
  function states(config) {
    var c = validate(config);
    var a = c.array;
    var n = a.length;
    var strict = c.strict;
    var ref = naive(a, strict);
    var L = [];
    var dp = [];
    for (var t = 0; t < n; t++) dp.push(null);
    var out = [];

    function push(phase, i, k, old, caption) {
      out.push({ phase: phase, i: i, L: L.slice(), k: k, old: old, dp: dp.slice(), caption: caption });
    }

    var bound = strict ? "lower_bound" : "upper_bound";
    var rule = strict ? "x 以上の最初の位置" : "x より大きい最初の位置";
    push("start", -1, null, null,
      (strict ? "狭義" : "広義") + "の増加部分列の最長を求める。L[k] は長さ k + 1 の増加部分列の末尾の最小値で、空から始める。" +
      "左から a[i] = x を見て、L の中で " + rule + " k を " + bound + " で求める。");

    for (var i = 0; i < n; i++) {
      var x = a[i];
      // 二分探索：L[lo] は条件（狭義なら L[k] ≥ x、広義なら L[k] > x）を満たさず、L[hi] は満たす（番兵 −1 と |L|）
      var lo = -1;
      var hi = L.length;
      while (hi - lo > 1) {
        var mid = (lo + hi) >> 1;
        if (strict ? L[mid] >= x : L[mid] > x) hi = mid;
        else lo = mid;
      }
      var k = hi;
      var append = k === L.length;
      var head = "a[" + i + "] = " + fmt(x) + " を入れる。";
      var findText;
      if (L.length === 0) findText = head + "L は空なので、位置は末尾の k = 0 になる。";
      else {
        findText = head + "L = " + listText(L) + " の中で " + fmt(x) + (strict ? " 以上の" : " より大きい") + "最初の位置は" +
          (append ? "ない（どの値も " + fmt(x) + (strict ? " 未満" : " 以下") + "）ので、末尾の k = " + k + " になる。"
            : " k = " + k + "（L[" + k + "] = " + fmt(L[k]) + "）である。");
      }
      push("find", i, k, null, findText);
      var old = append ? null : L[k];
      if (append) L.push(x);
      else L[k] = x;
      dp[i] = k + 1;
      var what = append
        ? fmt(x) + " を末尾に追加する。長さ " + (k + 1) + " の列ができる"
        : "L[" + k + "] = " + fmt(old) + " を " + fmt(x) + " に置き換える" + (old === x ? "（値は変わらない）" : "");
      var cmp = strict ? " < " : " ≤ ";
      var naiveText = ref[i] === 1
        ? "素朴な DP でも、a[j]" + cmp + fmt(x) + " となる左の j がないので dp[" + i + "] = 1 である。"
        : "素朴な DP でも、a[j]" + cmp + fmt(x) + " となる左の dp[j] の最大 " + (ref[i] - 1) + " に 1 を足して dp[" + i + "] = " +
          ref[i] + " になる。";
      push("update", i, k, old,
        what + "。L = " + listText(L) + "。a[" + i + "] で終わる最長は k + 1 = " + (k + 1) + " で、" + naiveText);
    }

    var maxDp = 0;
    for (var j = 0; j < n; j++) if (dp[j] > maxDp) maxDp = dp[j];
    push("done", n, null, null,
      "すべて入れた。LIS の長さは L の要素数の " + L.length + " で、dp の最大 " + maxDp + " と一致する。" +
      (L.length >= 2 ? "L = " + listText(L) + " は長さごとの末尾の最小値で、元の列の部分列とは限らない。" : ""));
    return out;
  }

  // 描画の寸法：列 k を x = LEFT + k × W に置く
  var W = 44;
  var CELL = 38;
  var LEFT = 40;
  var RIGHT = 12;
  var A_TOP = 30; // a の行の上端
  var D_TOP = 100; // dp の行の上端
  var L_TOP = 178; // L の行の上端
  var HEIGHT = L_TOP + CELL + 64;

  function viewBox(config) {
    return "0 0 " + (LEFT + config.array.length * W + RIGHT) + " " + HEIGHT;
  }

  function render(svg, s, config, h) {
    var a = config.array;
    var n = a.length;
    var strict = config.strict == null ? true : config.strict;
    var pad = (W - CELL) / 2;
    function bx(k) { return LEFT + k * W + pad; }
    function cx(k) { return LEFT + k * W + W / 2; }
    function label(y, t) {
      svg.appendChild(h("text", { x: LEFT / 2, y: y, class: "kp-v-text is-sub", "font-style": "italic" }, t));
    }

    // 上段：列 a。いま入れる要素を太い枠と上の三角で示し、まだ見ていない要素は薄くする
    for (var i = 0; i < n; i++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      if (i > s.i) { cls.push("is-no"); tcls.push("is-dim"); }
      if (i === s.i) cls.push("is-focus");
      svg.appendChild(h("rect", { x: bx(i), y: A_TOP, width: CELL, height: CELL, rx: 6, class: cls.join(" ") }));
      svg.appendChild(h("text", { x: cx(i), y: A_TOP + CELL / 2, class: tcls.join(" ") }, fmt(a[i])));
      svg.appendChild(h("text", { x: cx(i), y: A_TOP + CELL + 14, class: "kp-v-text is-sub" }, i));
    }
    label(A_TOP + CELL / 2, "a");
    label(A_TOP + CELL + 14, "i");
    if (s.i >= 0 && s.i < n) {
      var ix = cx(s.i);
      svg.appendChild(h("text", { x: ix, y: 7, class: "kp-v-ptr is-focus" }, "x"));
      svg.appendChild(h("path", { d: "M" + (ix - 6) + " 15h12l-6 8z", class: "kp-v-mark is-focus" }));
    }

    // 中段：a[i] で終わる最長 dp[i]（k + 1 と素朴な DP で同じ値）。update では a[j] と比べて dp[i] に効く左の j を塗る
    var cmpOk = function (u, v) { return strict ? u < v : u <= v; };
    for (var j = 0; j < n; j++) {
      var v = s.dp[j];
      var dcls = ["kp-v-cell"];
      var feeds = s.phase === "update" && j < s.i && cmpOk(a[j], a[s.i]);
      if (v == null) dcls.push("is-sentinel");
      else if (j === s.i && s.phase === "update") dcls.push("is-answer");
      else if (feeds) dcls.push("is-yes");
      svg.appendChild(h("rect", { x: bx(j), y: D_TOP, width: CELL, height: CELL, rx: 6, class: dcls.join(" ") }));
      if (v != null) {
        var on = j === s.i && s.phase === "update";
        svg.appendChild(h("text", { x: cx(j), y: D_TOP + CELL / 2, class: "kp-v-text" + (on ? " is-on-answer" : "") }, v));
      }
      // 素朴な DP で比べる相手（a[j] が小さい左の要素）には、塗りに加えて下に小さな丸を付ける（色だけに頼らない）
      if (feeds) svg.appendChild(h("circle", { cx: cx(j), cy: D_TOP + CELL + 8, r: 3, class: "kp-v-mark is-b" }));
    }
    label(D_TOP + CELL / 2, "dp");

    // 下段：L。いまの位置 k を下の三角で、追加なら破線の空き枠で示す。置換なら前の値を上に書く
    var len = s.L.length;
    for (var k = 0; k < len; k++) {
      var lcls = ["kp-v-cell"];
      var ltcls = ["kp-v-text"];
      if (k === s.k && s.phase === "update") { lcls.push("is-answer"); ltcls.push("is-on-answer"); }
      else if (k === s.k) lcls.push("is-focus");
      svg.appendChild(h("rect", { x: bx(k), y: L_TOP, width: CELL, height: CELL, rx: 6, class: lcls.join(" ") }));
      svg.appendChild(h("text", { x: cx(k), y: L_TOP + CELL / 2, class: ltcls.join(" ") }, fmt(s.L[k])));
    }
    if (s.phase === "find" && s.k === len) {
      svg.appendChild(h("rect", { x: bx(len), y: L_TOP, width: CELL, height: CELL, rx: 6, class: "kp-v-cell is-sentinel" }));
      svg.appendChild(h("text", { x: cx(len), y: L_TOP + CELL / 2, class: "kp-v-text is-sub" }, "追加"));
    }
    if (s.phase === "update" && s.old != null) {
      svg.appendChild(h("text", { x: cx(s.k), y: L_TOP - 12, class: "kp-v-ptr is-a" }, fmt(s.old) + "→" + fmt(s.L[s.k])));
    }
    if (s.phase === "update" && s.old == null) {
      svg.appendChild(h("text", { x: cx(s.k), y: L_TOP - 12, class: "kp-v-ptr is-a" }, "追加"));
    }
    var shown = Math.max(len + (s.phase === "find" && s.k === len ? 1 : 0), 1);
    for (var q = 0; q < shown; q++) {
      svg.appendChild(h("text", { x: cx(q), y: L_TOP + CELL + 14, class: "kp-v-text is-sub" }, q));
    }
    if (len === 0 && s.k == null) {
      svg.appendChild(h("rect", { x: bx(0), y: L_TOP, width: CELL, height: CELL, rx: 6, class: "kp-v-cell is-sentinel" }));
    }
    label(L_TOP + CELL / 2, "L");
    label(L_TOP + CELL + 14, "k");
    if (s.k != null) {
      var kx = cx(s.k);
      var ky = L_TOP + CELL + 22;
      svg.appendChild(h("path", { d: "M" + (kx - 6) + " " + (ky + 8) + "h12l-6 -8z", class: "kp-v-mark is-focus" }));
      svg.appendChild(h("text", { x: kx, y: ky + 17, class: "kp-v-ptr is-focus", "font-style": "italic" }, "k"));
    }
    // いちばん下に L の長さと探し方
    var width = LEFT + n * W + RIGHT;
    svg.appendChild(h("text", { x: width / 2, y: L_TOP + CELL + 54, class: "kp-v-text is-sub" },
      "|L| = " + len + "　" + (strict ? "狭義・lower_bound" : "広義・upper_bound")));
  }

  return {
    title: "最長増加部分列で、長さごとの末尾の最小値 L を二分探索で更新する",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

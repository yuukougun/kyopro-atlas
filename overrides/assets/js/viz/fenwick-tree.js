/*
 * 動く図：BIT（Fenwick Tree）で、sum(i) が箱を下へ、add(i, x) が箱を上へたどる様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="fenwick-tree"
 *        data-config='{"a": [3, 1, 4, 1, 5, 9, 2, 6], "ops": [{"type": "sum", "i": 7}, {"type": "add", "i": 3, "x": 2}]}'></div>
 * config（添字は本文の「保つ性質」の節と同じ 1-indexed）：
 *   a   … 初期の列 a_1, …, a_N（1〜12 個の整数。絶対値 99 以下）。N = a の長さ
 *   ops … 操作の配列（1〜4 個）。{"type": "sum", "i"}（a_1 + … + a_i を求める。0 ≤ i ≤ N）か
 *          {"type": "add", "i", "x"}（a_i に x を足す。1 ≤ i ≤ N、x は 0 でない整数で絶対値 99 以下）
 *   t と sum の途中の値は絶対値 999 以下、幅 1 の枠に描く a の値は add の後も −99〜999 になる列と操作にする（枠に収めるため）
 *
 * 箱 t[i] は区間 (i − lowbit(i), i] の和を持つ。長さ 2^k の箱を段 k に並べ、長い段を上に描く（本文の boxes.svg と同じ向き）。
 * ステップ：(1) 初期の t を示す → (2) 操作ごとに、始めの状態、ループ 1 回ごとの状態（今の i を 2 進数で示し、
 * 足す・直す箱を強調し、次の i への式を書く）、止まった状態を順に並べる。
 * 色だけに頼らないよう、今の箱は太い枠、この操作で通った箱は点線の枠、今の i は列の下の三角の印で示す。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/fenwick-tree.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("fenwick-tree", def);
})(function () {
  "use strict";

  var MAX_N = 12;
  var MAX_OPS = 4;
  var MAX_ABS_A = 99;
  var MAX_ABS_T = 999; // 箱の枠に収まる桁数（途中の t と a、sum の答えもこの範囲にする）
  // 幅 1 列の枠（a の行と、奇数の i の t[i] = a_i）には 3 文字までしか収まらないので、a の値は −99〜999 にする
  var MIN_NARROW = -99;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function lowbit(i) {
    return i & -i;
  }

  // 1-indexed の t を、t[i] = a_{i−lowbit(i)+1} + … + a_i の定義どおりに作る（t[0] は使わない）
  function buildT(a) {
    var n = a.length - 1;
    var t = new Array(n + 1).fill(0);
    for (var i = 1; i <= n; i++) {
      for (var j = i - lowbit(i) + 1; j <= i; j++) t[i] += a[j];
    }
    return t;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var a0 = config.a;
    if (!Array.isArray(a0) || a0.length < 1 || a0.length > MAX_N) {
      throw new Error("a は 1〜" + MAX_N + " 個の整数の配列にする");
    }
    for (var k = 0; k < a0.length; k++) {
      if (!isInt(a0[k]) || Math.abs(a0[k]) > MAX_ABS_A) {
        throw new Error("a の要素は絶対値 " + MAX_ABS_A + " 以下の整数にする");
      }
    }
    var n = a0.length;
    var ops = config.ops;
    if (!Array.isArray(ops) || ops.length < 1 || ops.length > MAX_OPS) {
      throw new Error("ops は 1〜" + MAX_OPS + " 個の操作の配列にする");
    }
    var out = [];
    for (var j = 0; j < ops.length; j++) {
      var o = ops[j];
      if (!o || (o.type !== "sum" && o.type !== "add")) throw new Error('ops の type は "sum" か "add" にする');
      if (o.type === "sum") {
        if (!isInt(o.i) || o.i < 0 || o.i > n) throw new Error("sum の i は 0 ≤ i ≤ " + n + " の整数にする（1-indexed）");
        out.push({ type: "sum", i: o.i });
      } else {
        if (!isInt(o.i) || o.i < 1 || o.i > n) {
          throw new Error("add の i は 1 ≤ i ≤ " + n + " の整数にする（1-indexed。i = 0 の add は止まらない）");
        }
        if (!isInt(o.x) || o.x === 0 || Math.abs(o.x) > MAX_ABS_A) {
          throw new Error("add の x は 0 でない整数（絶対値 " + MAX_ABS_A + " 以下）にする");
        }
        out.push({ type: "add", i: o.i, x: o.x });
      }
    }
    // 途中の t と a、sum の答えが枠からはみ出さないか、操作を順に行って確かめる
    var a = [0].concat(a0);
    var t = buildT(a);
    var tooBig = t.some(function (v) { return Math.abs(v) > MAX_ABS_T; });
    var narrowBad = false;
    for (var q = 0; q < out.length && !tooBig && !narrowBad; q++) {
      if (out[q].type === "add") {
        a[out[q].i] += out[q].x;
        if (a[out[q].i] < MIN_NARROW || a[out[q].i] > MAX_ABS_T) narrowBad = true;
        for (var p = out[q].i; p <= n; p += lowbit(p)) {
          t[p] += out[q].x;
          if (Math.abs(t[p]) > MAX_ABS_T) tooBig = true;
        }
      } else {
        for (var r = out[q].i, s = 0; r > 0; r -= lowbit(r)) {
          s += t[r];
          if (Math.abs(s) > MAX_ABS_T) tooBig = true;
        }
      }
    }
    if (narrowBad) {
      throw new Error("幅 1 の枠に描く a の値（奇数の i の t[i] も同じ値）は add の後も " + fmtVal(MIN_NARROW) + "〜" + MAX_ABS_T + " にする");
    }
    if (tooBig) throw new Error("t の値と sum の途中の値が絶対値 " + MAX_ABS_T + " を超えない列と操作にする");
    return { n: n, a: a0.slice(), ops: out };
  }

  function bitsOf(n) {
    var b = 1;
    while (1 << b <= n) b++;
    return b;
  }

  function bin(v, width) {
    var s = v.toString(2);
    while (s.length < width) s = "0" + s;
    return s;
  }

  function fmtVal(v) {
    return v < 0 ? "−" + -v : String(v);
  }
  function fmtAdd(v) {
    return v < 0 ? "−" + -v : "+" + v;
  }
  function rangeA(lo, hi) {
    return lo === hi ? "a_" + hi : "a_" + lo + "〜a_" + hi;
  }
  function boxList(list) {
    return list.map(function (b) { return "t[" + b + "]"; }).join("・");
  }

  // 各ステップの状態：
  //   phase（init / start / step / end）、opIndex（いまの操作の番号。初期状態は −1）、
  //   a・t（1-indexed。添字 0 は使わない）、i（いまの i。ループの外なら止まった値。初期状態は null）、
  //   s（sum の途中の和。add と初期状態は null）、current（いま足す・直す箱。なければ null）、
  //   visited（この操作で通った箱。current を含む）、coveredFrom（sum で、足し終えた箱が覆う a の範囲 [coveredFrom, 操作の i] の
//   左端。覆っていなければ 0）、
  //   caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var w = bitsOf(n);
    var a = [0].concat(c.a);
    var t = buildT(a);
    var out = [];

    function b(v) {
      return v + "（" + bin(v, w) + "）";
    }
    function sumOf(lo, hi, v) {
      return lo === hi ? "a_" + hi + " = " + fmtVal(v) : "a_" + lo + "〜a_" + hi + " の和 " + fmtVal(v);
    }

    function snap(o) {
      out.push({
        phase: o.phase,
        opIndex: o.opIndex == null ? -1 : o.opIndex,
        a: a.slice(),
        t: t.slice(),
        i: o.i == null ? null : o.i,
        s: o.s == null ? null : o.s,
        current: o.current == null ? null : o.current,
        visited: (o.visited || []).slice(),
        coveredFrom: o.coveredFrom || 0,
        caption: o.caption,
      });
    }

    snap({
      phase: "init",
      caption: "N = " + n + " の BIT。t[i] は区間 (i − lowbit(i), i] の和、すなわち a の i で終わる長さ lowbit(i) の区間の和を持つ。" +
        "長い箱ほど上の段に描く。",
    });

    for (var j = 0; j < c.ops.length; j++) {
      var op = c.ops[j];
      var i = op.i;
      var visited = [];
      if (op.type === "sum") {
        var head = "sum(" + i + ")：";
        var s = 0;
        snap({
          phase: "start", opIndex: j, i: i, s: 0,
          caption: head + (i === 0
            ? "a_1 + … + a_0 は空の和である。s = 0、i = 0 から始める。"
            : (i === 1 ? "a_1" : i === 2 ? "a_1 + a_2" : "a_1 + … + a_" + i) +
              " を求める。s = 0、i = " + i + " から始める。"),
        });
        while (i > 0) {
          var lb = lowbit(i);
          s += t[i];
          visited.push(i);
          var next = i - lb;
          snap({
            phase: "step", opIndex: j, i: i, s: s, current: i, visited: visited, coveredFrom: next + 1,
            caption: head + "i = " + i + "（2 進で " + bin(i, w) + "）、lowbit(i) = " + lb + "。s += t[" + i + "]（" +
              sumOf(next + 1, i, t[i]) + "）で s = " + fmtVal(s) + "。次は i − lowbit(i) = " + i + " − " + lb + " = " +
              b(next) + "で、最下位の 1 が消える。",
          });
          i = next;
        }
        var direct = 0;
        for (var q = 1; q <= op.i; q++) direct += a[q];
        snap({
          phase: "end", opIndex: j, i: 0, s: s, visited: visited, coveredFrom: op.i > 0 ? 1 : 0,
          caption: head + (op.i === 0
            ? "i = 0 なのでループに入らずに止まる。sum(0) = 0 である。"
            : "i = 0 になったので止まる。sum(" + op.i + ") = s = " + fmtVal(s) + "。" + boxList(visited) + " の " +
              visited.length + " 箱が " + rangeA(1, op.i) + " を重なりなく覆う（直接足しても " + fmtVal(direct) + "）。"),
        });
      } else {
        var headA = "add(" + i + ", " + fmtAdd(op.x) + ")：";
        a[op.i] += op.x;
        snap({
          phase: "start", opIndex: j, i: i,
          caption: headA + "a_" + op.i + " に " + fmtVal(op.x) + " を足す（a_" + op.i + " = " + fmtVal(a[op.i]) +
            "）。a_" + op.i + " を含む箱をすべて直すため、i = " + i + " から始める。",
        });
        while (i <= n) {
          var lbA = lowbit(i);
          var before = t[i];
          t[i] += op.x;
          visited.push(i);
          var nextA = i + lbA;
          snap({
            phase: "step", opIndex: j, i: i, current: i, visited: visited,
            caption: headA + "i = " + i + "（2 進で " + bin(i, w) + "）、lowbit(i) = " + lbA + "。t[" + i + "]（" +
              (lbA === 1 ? "a_" + i : rangeA(i - lbA + 1, i) + " の和") + "）に " + fmtVal(op.x) + " を足して " +
              fmtVal(before) + " → " + fmtVal(t[i]) + "。次は i + lowbit(i) = " + i + " + " + lbA + " = " + b(nextA) +
              "で、最下位の 1 の桁で繰り上がる。",
          });
          i = nextA;
        }
        snap({
          phase: "end", opIndex: j, i: i, visited: visited,
          caption: headA + "i = " + i + " > N = " + n + " になったので止まる。a_" + op.i + " を含む箱は " + boxList(visited) +
            (visited.length === 1 ? " だけで、それを直した。" : " の " + visited.length + " つで、すべて 1 回ずつ直した。"),
        });
      }
    }
    return out;
  }

  // 描画の寸法：列 j（1〜N）を x = LEFT + (j − 1) × W に置く。段 k（長さ 2^k）は上から levels − 1 − k 番目の行
  var W = 40;
  var LEFT = 18; // 左に a の行の名前
  var RIGHT = 6;
  var STATUS_H = 26;
  var ROW = 44;
  var BOX_H = 38;
  var A_H = 30;
  var MIN_W = 250;

  function levelsOf(n) {
    var k = 0;
    while (1 << (k + 1) <= n) k++;
    return k + 1;
  }

  function layout(c) {
    var levels = levelsOf(c.n);
    var aY = STATUS_H + levels * ROW + 4;
    var idxY = aY + A_H + 11;
    var binY = idxY + 15;
    var markY = binY + 8;
    return {
      levels: levels,
      width: Math.max(MIN_W, LEFT + c.n * W + RIGHT),
      aY: aY, idxY: idxY, binY: binY, markY: markY,
      height: markY + 12,
    };
  }

  function viewBox(config) {
    var c = validate(config);
    var L = layout(c);
    return "0 0 " + L.width + " " + L.height;
  }

  function render(svg, s, config, h) {
    var c = validate(config);
    var n = c.n;
    var L = layout(c);
    var w = bitsOf(n);
    var op = s.opIndex >= 0 ? c.ops[s.opIndex] : null;
    function colX(j) { return LEFT + (j - 1) * W; }
    function cx(j) { return LEFT + (j - 0.5) * W; }

    // いまの操作と i・s を上の行に書く
    var status;
    if (!op) status = "初期状態（a から作った t）";
    else {
      status = op.type === "sum" ? "sum(" + op.i + ")" : "add(" + op.i + ", " + fmtAdd(op.x) + ")";
      if (s.i != null) status += "　i = " + s.i;
      if (s.s != null) status += "　s = " + fmtVal(s.s);
    }
    svg.appendChild(h("text", { x: L.width / 2, y: STATUS_H / 2, class: "kp-v-ptr is-focus" }, status));

    // 箱 t[1..N]
    for (var i = 1; i <= n; i++) {
      var lb = lowbit(i);
      var k = 0;
      while ((1 << k) < lb) k++;
      var y = STATUS_H + (L.levels - 1 - k) * ROW;
      var cls = ["kp-v-cell"];
      var isVisited = s.visited.indexOf(i) >= 0;
      var isCurrent = s.current === i;
      if (isVisited) cls.push("is-yes");
      if (isCurrent) cls.push("is-focus");
      var attrs = { x: colX(i - lb + 1) + 2, y: y, width: lb * W - 4, height: BOX_H, rx: 5, class: cls.join(" ") };
      if (isVisited && !isCurrent) attrs["stroke-dasharray"] = "5 3";
      svg.appendChild(h("rect", attrs));
      var mid = colX(i - lb + 1) + (lb * W) / 2;
      svg.appendChild(h("text", { x: mid, y: y + 11, class: "kp-v-text is-sub" }, "t[" + i + "]"));
      svg.appendChild(h("text", { x: mid, y: y + 27, class: "kp-v-text" }, fmtVal(s.t[i])));
    }

    // a の行。sum では足し終えた箱が覆う a の範囲を塗り、add では足した a_i を太枠にする
    svg.appendChild(h("text", { x: LEFT / 2, y: L.aY + A_H / 2, class: "kp-v-ptr is-a" }, "a"));
    for (var j = 1; j <= n; j++) {
      var acls = ["kp-v-cell"];
      if (op && op.type === "sum" && s.coveredFrom && j >= s.coveredFrom && j <= op.i) acls.push("is-yes");
      if (op && op.type === "add" && j === op.i) acls.push("is-yes", "is-focus");
      svg.appendChild(h("rect", { x: colX(j) + 3, y: L.aY, width: W - 6, height: A_H, rx: 5, class: acls.join(" ") }));
      svg.appendChild(h("text", { x: cx(j), y: L.aY + A_H / 2, class: "kp-v-text" }, fmtVal(s.a[j])));
      var here = s.current === j || (s.phase === "start" && s.i === j);
      svg.appendChild(h("text", { x: cx(j), y: L.idxY, class: here ? "kp-v-ptr is-focus" : "kp-v-text is-sub" }, j));
      svg.appendChild(h("text", { x: cx(j), y: L.binY, class: here ? "kp-v-ptr is-focus" : "kp-v-text is-sub" }, bin(j, w)));
      if (here) {
        svg.appendChild(h("path", { d: "M" + (cx(j) - 6) + " " + (L.markY + 9) + "h12l-6 -8z", class: "kp-v-mark is-focus" }));
      }
    }
  }

  return {
    title: "BIT で、sum は箱を下へ、add は箱を上へ、添字の最下位の 1 に従ってたどる",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

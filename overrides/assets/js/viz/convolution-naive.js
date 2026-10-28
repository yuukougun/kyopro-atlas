/*
 * 動く図：畳み込み c_k = Σ_{i+j=k} a_i b_j を素朴に計算する。b を反転して a の下に置き、右へ 1 つずつずらしながら、
 * 上下に重なった組の積を足す（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="convolution-naive" data-config='{"a": [1, 2, 3], "b": [4, 5, 6]}'></div>
 * config：
 *   a … 列 a（1 個以上の 0〜9 の整数）。長さを N とする
 *   b … 列 b（1 個以上の 0〜9 の整数）。長さを M とする
 *   反転した b は a の左右に最大 M − 1 マスはみ出すので、図の列の数は N + 2M − 2 になる。これを 10 以下にする
 *   （viewBox の幅は 40 + 40 × 列の数 + 8 で、最大 448。畳み込みは a と b を入れ替えても同じなので、長い方を a にする）。
 *   値を 1 桁にするのは、積（81 まで）と c_k（列の数の制限で min(N, M) ≤ 4 なので 4 × 81 = 324 まで）をマスに収めるため
 *
 * ステップ：(1) b を反転し、b_0 が a_0 の真下に来るように置く → (2) ずらし幅 k = 0, 1, …, N + M − 2 の順に、b_0 を
 * 列 k（a_k の真下。k ≥ N なら a の右端より右）に置き、上下に重なった組 (i, j)（ちょうど i + j = k のもの）の積を
 * 「積」の段に並べ、その和を c の段の c_k に書き込む（1 つのずらし幅に 1 状態）→ (3) c がそろい、
 * どの組も 1 回ずつ掛けたので掛け算は N × M 回だったことを示す。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/convolution-naive.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("convolution-naive", def);
})(function () {
  "use strict";

  var MAX_V = 9;
  var MAX_COLS = 10;

  function isInt(x) {
    return typeof x === "number" && isFinite(x) && Math.floor(x) === x;
  }

  function seq(x, name) {
    if (!Array.isArray(x) || x.length < 1) throw new Error(name + " は 1 個以上の 0〜" + MAX_V + " の整数の配列にする");
    for (var i = 0; i < x.length; i++) {
      if (!isInt(x[i]) || x[i] < 0 || x[i] > MAX_V) throw new Error(name + " の要素は 0〜" + MAX_V + " の整数にする");
    }
    return x.slice();
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var a = seq(config.a, "a");
    var b = seq(config.b, "b");
    if (a.length + 2 * b.length - 2 > MAX_COLS) {
      throw new Error("a の長さ N と b の長さ M は N + 2M − 2 ≤ " + MAX_COLS +
        " にする（反転した b が a の左右にはみ出す分だけ図が広がる。長い方を a にするとよい）");
    }
    return { a: a, b: b };
  }

  function tuple(x) {
    return "(" + x.join(", ") + ")";
  }

  // b_1 から b_{M−1} までを言葉にする（M ≥ 2）
  function restOfB(M) {
    if (M === 2) return "b_1";
    if (M === 3) return "b_1 と b_2";
    return "b_1〜b_" + (M - 1);
  }

  // 各ステップの状態：
  //   phase（start / step / done）、shift（b_0 を置く列。start は 0、done は最後のずらし幅）、
  //   k（step のときのずらし幅。ほかは null）、pairs（重なった組 {i, j, prod} を i の小さい順に）、
  //   sum（step のときの c_k）、c（長さ N + M − 1。まだ求めていない項は null）、caption
  function states(config) {
    var c = validate(config);
    var a = c.a, b = c.b, N = a.length, M = b.length;
    var K = N + M - 1; // ずらし幅は 0〜K − 1
    var last = K - 1;
    var cc = [];
    for (var t = 0; t < K; t++) cc.push(null);
    var out = [];

    var place = M === 1
      ? "b = " + tuple(b) + " を、b_0 が a_0 の真下に来るように下の段に置いた（1 個なので反転しても同じである）。"
      : "b = " + tuple(b) + " を反転して " + b.slice().reverse().join(", ") + " の順に、b_0 が a_0 の真下に来るように" +
        "下の段に置いた。";
    var plan = K === 1
      ? "ずらし幅は k = 0 だけで、上下に重なった組の積が c_0 になる。"
      : "この下の段を右へ 1 つずつずらし、ずらし幅 k = 0〜" + last + " のそれぞれで、上下に重なった組の積を足して c_k とする。";
    out.push({
      phase: "start", shift: 0, k: null, pairs: [], sum: null, c: cc.slice(),
      caption: "a = " + tuple(a) + " を上の段に置き、" + place +
        "上の段のマスの上の数が添字 i、下の段のマスの下の数が添字 j である。" + plan,
    });

    for (var k = 0; k < K; k++) {
      var pairs = [];
      var sum = 0;
      for (var i = Math.max(0, k - (M - 1)); i <= Math.min(k, N - 1); i++) {
        var p = a[i] * b[k - i];
        pairs.push({ i: i, j: k - i, prod: p });
        sum += p;
      }
      cc[k] = sum;

      // b の位置の説明。k = 0 では a の左にはみ出した b_j（j ≥ 1）を、k ≥ N では a の右端より右に出た b_j
      // （列 k − j ≥ N、つまり j = 0〜k − N）を言う
      var where;
      if (k === 0) {
        where = M > 1 ? "b_0 は a_0 の真下にあり、" + restOfB(M) + " は a の左にはみ出している。" : "b_0 は a_0 の真下にある。";
      } else if (k <= N - 1) {
        where = "下の段を右へ 1 つずらし、b_0 が a_" + k + " の真下に来た。";
      } else if (k === N) {
        where = "下の段を右へ 1 つずらし、b_0 は a の右端より右に出た。";
      } else {
        where = "下の段を右へ 1 つずらし、" + (k - N === 1 ? "b_0 と b_1" : "b_0〜b_" + (k - N)) +
          " は a の右端より右に出ている。";
      }
      var names = pairs.map(function (q) { return "a_" + q.i + " と b_" + q.j; }).join("、");
      var over = pairs.length === 1
        ? "重なるのは " + names + " の 1 組だけで、i + j = " + k + " である。"
        : "重なるのは " + names + " の " + pairs.length + " 組で、どれも i + j = " + k + " である。";
      var muls = pairs.map(function (q) { return a[q.i] + " × " + b[q.j]; }).join(" + ");
      var vals = pairs.map(function (q) { return q.prod; }).join(" + ");
      var eq = "c_" + k + " = " + muls + (pairs.length > 1 ? " = " + vals : "") + " = " + sum + " である。";
      var tail = k === last ? "これより右へずらすと重なる組がなくなるので、ずらし幅はここまでである。" : "";
      out.push({
        phase: "step", shift: k, k: k, pairs: pairs, sum: sum, c: cc.slice(),
        caption: "ずらし幅 k = " + k + "。" + where + over + eq + tail,
      });
    }

    out.push({
      phase: "done", shift: last, k: null, pairs: [], sum: null, c: cc.slice(),
      caption: (K === 1 ? "ずらし幅 0 の 1 通りで " : "ずらし幅 0〜" + last + " の N + M − 1 = " + K + " 通りを終え、") +
        "c = " + tuple(cc) + " が求まった。どの組 (i, j) も、ずらし幅 i + j のときにちょうど 1 回だけ重なるので、" +
        "掛け算は全部で N × M = " + N * M + " 回である。素朴な方法が O(NM) かかるのはこのためである。",
    });
    return out;
  }

  // 描画の寸法：列 t（−(M − 1)〜N + M − 2）の中心を x = LEFT + (t + M − 1) × P + P / 2 に置く
  var LEFT = 40; // 行の名前の幅
  var P = 40; // 列の間隔
  var CELL = 34;
  var RIGHT = 8;
  var MIN_W = 260; // 上の行の文字が収まる幅
  var Y_STATUS = 11; // いまの段階
  var Y_I = 32; // a の添字 i
  var Y_A = 42; // a の段の上端
  var Y_X = 86; // 重なった列の × の印
  var Y_B = 96; // 反転した b の段の上端
  var Y_J = 142; // b の添字 j
  var Y_P = 156; // 積の段の上端
  var Y_SUM = 208; // 和の式
  var Y_C = 222; // c の段の上端
  var Y_K = 268; // c の添字 k
  var HEIGHT = 280;

  function widthOf(N, M) {
    return Math.max(MIN_W, LEFT + (N + 2 * M - 2) * P + RIGHT);
  }

  function viewBox(config) {
    var c = validate(config);
    return "0 0 " + widthOf(c.a.length, c.b.length) + " " + HEIGHT;
  }

  // 文字の幅の見積もり（記号と全角は 1 字、ほかは 0.6 字。多めに見積もる）。中央にそろえた式を図の端で切らないために使う
  function textWidth(s, px) {
    var w = 0;
    for (var i = 0; i < s.length; i++) w += s.charCodeAt(i) >= 0x2000 ? px : px * 0.6;
    return w;
  }

  // 添字付きの式を 1 つの text に描く。segs は [文字, 添字か]。添字は tspan を dy で下げる（baseline-shift は使わない）
  function formula(svg, h, segs, center, y, width, cls) {
    var w = 0;
    segs.forEach(function (sg) { w += textWidth(sg[0], sg[1] ? 10 : 13); });
    var x = Math.min(Math.max(center, 4 + w / 2), width - 4 - w / 2);
    var t = h("text", { x: x, y: y, class: cls });
    var down = false;
    segs.forEach(function (sg) {
      var attrs = {};
      if (sg[1] && !down) attrs.dy = 4;
      if (!sg[1] && down) attrs.dy = -4;
      if (sg[1]) attrs.style = "font-size:10px";
      down = sg[1];
      t.appendChild(h("tspan", attrs, sg[0]));
    });
    svg.appendChild(t);
  }

  var DIM = "fill:none;stroke:var(--md-default-fg-color--lighter);stroke-width:1";

  function render(svg, s, config, h) {
    var c = validate(config);
    var a = c.a, b = c.b, N = a.length, M = b.length, K = N + M - 1;
    var width = widthOf(N, M);
    var step = s.phase === "step";
    function cx(t) { return LEFT + (t + M - 1) * P + P / 2; }
    function x0(t) { return cx(t) - CELL / 2; }
    function box(t, y, value, cls, tcls, style) {
      svg.appendChild(h("rect", { x: x0(t), y: y, width: CELL, height: CELL, rx: 5, class: cls, style: style || null }));
      if (value != null) svg.appendChild(h("text", { x: cx(t), y: y + CELL / 2, class: tcls }, value));
    }
    var on = {}; // 重なった列（a の添字 i）
    s.pairs.forEach(function (q) { on[q.i] = true; });

    // 上の行：いまの段階
    var status = s.phase === "start" ? "b を反転して a の下に置く"
      : step ? "ずらし幅 k = " + s.k + "（i + j = " + s.k + " の組）"
      : K === 1 ? "ずらし幅 0 の 1 通りを終えた" : "ずらし幅 0〜" + (K - 1) + " の " + K + " 通りを終えた";
    svg.appendChild(h("text", { x: width / 2, y: Y_STATUS, class: "kp-v-ptr is-focus" }, status));

    // 行の名前
    var lx = LEFT / 2;
    svg.appendChild(h("text", { x: lx, y: Y_I, class: "kp-v-text is-sub" }, "i"));
    svg.appendChild(h("text", { x: lx, y: Y_A + CELL / 2, class: "kp-v-ptr" }, "a"));
    svg.appendChild(h("text", { x: lx, y: Y_B + 10, class: "kp-v-ptr" }, "b"));
    svg.appendChild(h("text", { x: lx, y: Y_B + 26, class: "kp-v-text is-sub" }, "反転"));
    svg.appendChild(h("text", { x: lx, y: Y_J, class: "kp-v-text is-sub" }, "j"));
    svg.appendChild(h("text", { x: lx, y: Y_P + CELL / 2, class: "kp-v-ptr" }, "積"));
    svg.appendChild(h("text", { x: lx, y: Y_C + CELL / 2, class: "kp-v-ptr" }, "c"));
    svg.appendChild(h("text", { x: lx, y: Y_K, class: "kp-v-text is-sub" }, "k"));

    // a の段（列 0〜N − 1。動かない）と添字 i
    for (var i = 0; i < N; i++) {
      var hit = step && on[i];
      var faint = step && !on[i];
      box(i, Y_A, a[i], "kp-v-cell" + (hit ? " is-yes" : ""), "kp-v-text" + (faint ? " is-dim" : ""), faint ? DIM : null);
      svg.appendChild(h("text", { x: cx(i), y: Y_I, class: hit ? "kp-v-ptr is-b" : "kp-v-text is-sub" }, i));
      if (hit) svg.appendChild(h("text", { x: cx(i), y: Y_X, class: "kp-v-ptr is-b", style: "font-size:17px" }, "×"));
    }

    // 反転した b の段：b_j を列 shift − j に置く。a の下にない b_j ははみ出した分（薄い枠）
    for (var j = 0; j < M; j++) {
      var t = s.shift - j;
      var under = t >= 0 && t <= N - 1;
      var bOn = step && under;
      var bFaint = (step && !under) || s.phase === "done";
      box(t, Y_B, b[j], "kp-v-cell" + (bOn ? " is-yes" : ""), "kp-v-text" + (bFaint ? " is-dim" : ""), bFaint ? DIM : null);
      svg.appendChild(h("text", { x: cx(t), y: Y_J, class: bOn ? "kp-v-ptr is-b" : "kp-v-text is-sub" }, j));
    }

    // 最初の状態だけ、右へずらす向きを b_0 の右に書く（ずらすときで、入る幅があるとき）
    if (s.phase === "start" && K > 1) {
      var hx = x0(1) + 2;
      var hint = "右へずらす →";
      if (width - 4 - hx >= textWidth(hint, 12)) {
        svg.appendChild(h("text", { x: hx, y: Y_B + CELL / 2, class: "kp-v-text is-sub", style: "text-anchor:start" }, hint));
      }
    }

    // 積の段と和の式
    if (step) {
      s.pairs.forEach(function (q) { box(q.i, Y_P, q.prod, "kp-v-cell", "kp-v-text"); });
      var lo = s.pairs[0].i, hi = s.pairs[s.pairs.length - 1].i;
      var rhs = s.pairs.length > 1
        ? " = " + s.pairs.map(function (q) { return q.prod; }).join(" + ") + " = " + s.sum
        : " = " + s.sum;
      formula(svg, h, [["c", false], [String(s.k), true], [rhs, false]], (cx(lo) + cx(hi)) / 2, Y_SUM, width,
        "kp-v-ptr is-focus");
    } else if (s.phase === "done") {
      var muls = "掛け算は全部で N × M = " + N * M + " 回";
      svg.appendChild(h("text", { x: width / 2, y: Y_P + CELL / 2, class: "kp-v-ptr is-b" }, muls));
      formula(svg, h, [["c = " + tuple(s.c), false]], (cx(0) + cx(K - 1)) / 2, Y_SUM, width, "kp-v-ptr is-focus");
    } else {
      formula(svg, h, [["c", false], ["k", true], [" = Σ a", false], ["i", true], [" b", false], ["j", true],
        ["（i + j = k）", false]], (cx(0) + cx(K - 1)) / 2, Y_SUM, width, "kp-v-ptr");
    }

    // c の段（列 0〜N + M − 2。c_k は b_0 を置いた列の下）と添字 k
    for (var q = 0; q < K; q++) {
      var v = s.c[q];
      var now = step && q === s.k;
      if (v == null) {
        box(q, Y_C, null, "kp-v-cell is-sentinel", null);
      } else {
        box(q, Y_C, v, "kp-v-cell" + (now ? " is-answer" : s.phase === "done" ? " is-yes" : ""),
          "kp-v-text" + (now ? " is-on-answer" : ""));
      }
      svg.appendChild(h("text", { x: cx(q), y: Y_K, class: now ? "kp-v-ptr is-focus" : "kp-v-text is-sub" }, q));
    }
  }

  return {
    title: "畳み込みを素朴に計算する：反転した b を右へずらしながら、重なった組の積を足して c_k を求める",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

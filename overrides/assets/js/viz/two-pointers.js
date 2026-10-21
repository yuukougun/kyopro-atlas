/*
 * 動く図：尺取り法で、各左端 l に対する右端 r(l) を、r を戻さずに求める（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="two-pointers" data-config='{"array": [1, 2, 1, 3, 1, 1, 2], "K": 4, "mode": "at-most"}'></div>
 * config：
 *   array … 0 以上 99 以下の整数の配列（1〜8 個。N = 8 で viewBox の幅 404、スマホの幅 360 でも 0.76 倍ほどで字が読める。
 *           それより長いと 0.6 倍を下回り、添字や和の文字が小さくなりすぎるので受け付けない）
 *   K     … 整数。at-most なら 0 以上、at-least なら 1 以上
 *   mode  … "at-most"（既定。和が K 以下の区間。各 l で満たす最大の r を求める。部分区間も満たす型）か
 *            "at-least"（和が K 以上の区間。各 l で満たす最小の r を求める。より大きい区間も満たす型）
 *
 * 区間は半開区間 [l, r)、添字は 0-indexed。l を 0 から順に進め、各 l で次を行う。
 *   at-most ：a[r] を入れても和が K 以下なら r を伸ばす。伸ばせなければ（または r = N なら）r(l) = r と決め、a[l] を出して l を進める。
 *             l = r（空区間）のまま l を進めるときは r も一緒に進める
 *   at-least：和が K 未満なら r を伸ばす。K 以上になったら r(l) = r と決め、a[l] を出して l を進める。
 *             r = N まで伸ばしても K 未満なら、それより右の l でも満たさないので終わる
 * r は一度も戻らないので、r が動く回数も l が動く回数も合計 N 回以下である。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/two-pointers.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("two-pointers", def);
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
      if (!isInt(a[i]) || a[i] < 0 || a[i] > MAX_V) throw new Error("array の要素は 0 以上 " + MAX_V + " 以下の整数にする");
    }
    var mode = config.mode == null ? "at-most" : config.mode;
    if (mode !== "at-most" && mode !== "at-least") throw new Error('mode は "at-most" か "at-least" にする');
    var K = config.K;
    if (!isInt(K)) throw new Error("K は整数にする");
    if (mode === "at-most" && K < 0) throw new Error("at-most の K は 0 以上にする");
    if (mode === "at-least" && K < 1) throw new Error("at-least の K は 1 以上にする");
    return { array: a.slice(), K: K, mode: mode };
  }

  function rangeText(l, r) {
    return "[" + l + ", " + r + ")";
  }

  function startText(l, r) {
    return "左端 l = " + l + " から始まる空でない区間" + (r > l ? " " + (r - l) + " 個が条件を満たす" : "で条件を満たすものはない");
  }

  // 各ステップの状態：l・r（いまの区間 [l, r)）、sum（区間の和）、next（入れようとして断った位置。なければ null）、
  // rl（決まった r(l) の配列。未定は null）、count（ここまでに数えた区間の数）、
  // skipped（一度も区間に入れずに l と r を一緒に越えた位置なら true）、phase、caption
  function states(config) {
    var c = validate(config);
    var a = c.array;
    var n = a.length;
    var K = c.K;
    var most = c.mode === "at-most";
    var rl = [];
    for (var i = 0; i < n; i++) rl.push(null);
    var l = 0;
    var r = 0;
    var sum = 0;
    var count = 0;
    var skipped = [];
    for (var j0 = 0; j0 < n; j0++) skipped.push(false);
    var out = [];

    function push(phase, caption, extra) {
      var s = { phase: phase, l: l, r: r, sum: sum, next: null, rl: rl.slice(), count: count, skipped: skipped.slice(), caption: caption };
      if (extra) Object.keys(extra).forEach(function (k) { s[k] = extra[k]; });
      out.push(s);
    }

    push("start", (most
      ? "和が " + K + " 以下の区間 [l, r) を、各 l について右端 r をできるだけ伸ばして調べる。"
      : "和が " + K + " 以上の区間 [l, r) を、各 l について和が " + K + " 以上になるまで右端 r を伸ばして調べる。") +
      "左端 l = 0、右端 r = 0（空区間）、和 0 から始める。");

    var stopped = false;
    while (l < n && !stopped) {
      if (most) {
        while (r < n && sum + a[r] <= K) {
          sum += a[r];
          r++;
          push("extend", "a[" + (r - 1) + "] = " + a[r - 1] + " を入れても和は " + sum + " ≤ " + K + " なので、右端 r を " + r +
            " に伸ばす。区間は " + rangeText(l, r) + "。");
        }
        rl[l] = r;
        count += r - l;
        if (r < n) {
          push("decide", "a[" + r + "] = " + a[r] + " を入れると和が " + (sum + a[r]) + " > " + K + " になるので伸ばせない。r(" +
            l + ") = " + r + " と決まり、" + startText(l, r) + "。", { next: r });
        } else {
          push("decide", "r が N = " + n + " に達したので伸ばせない。r(" + l + ") = " + r + " と決まり、" +
            startText(l, r) + "。");
        }
      } else {
        while (r < n && sum < K) {
          sum += a[r];
          r++;
          push("extend", "和が " + K + " 未満なので a[" + (r - 1) + "] = " + a[r - 1] + " を入れ、右端 r を " + r + " に伸ばす。区間は " +
            rangeText(l, r) + "、和は " + sum + (sum >= K ? " ≥ " : " < ") + K + "。");
        }
        if (sum < K) {
          push("none", "右端 r を N = " + n + " まで伸ばしても和は " + sum + " < " + K + " である。左端を l = " + l +
            " より右へ進めると区間が縮むだけなので、もう条件を満たす区間はない。");
          stopped = true;
          break;
        }
        rl[l] = r;
        count += n - r + 1;
        push("decide", "和が " + sum + " ≥ " + K + " になった。r(" + l + ") = " + r + " と決まり、右端が " + (r < n ? r + "〜" + n : n) +
          " の区間 " + (n - r + 1) + " 個が条件を満たす。");
      }
      if (l === n - 1) break;
      if (l === r) {
        skipped[l] = true;
        l++;
        r++;
        push("advance", "区間が空なので、a[" + (l - 1) + "] は入れずに左端と右端を一緒に 1 つ進めて l = " + l + "、r = " + r +
          " にする。和は 0 のまま。");
      } else {
        sum -= a[l];
        l++;
        push("advance", "a[" + (l - 1) + "] = " + a[l - 1] + " を出して左端 l を " + l + " に進める。区間は " + rangeText(l, r) +
          "、和は " + sum + "。右端 r は戻さない。");
      }
    }

    var decided = rl.filter(function (v) { return v != null; });
    push("done", (most ? "すべての左端 l で r(l) が決まった：" : (decided.length ? "r(l) は " : "")) +
      (decided.length
        ? (most ? "" : "l = 0〜" + (decided.length - 1) + " で ") + decided.join(", ") + (most ? "。" : " と決まった。")
        : "条件を満たす区間はない。") +
      (stopped && decided.length ? "左端 l = " + l + " 以降は条件を満たす右端がない。" : "") +
      "右端 r は左へ戻らず、両端とも合計 " + n + " 回以下しか進まない。和が " + K + (most ? " 以下" : " 以上") +
      "の空でない区間は全部で " + count + " 個である。", { done: true });
    return out;
  }

  // 描画の寸法：マス k を x = LEFT + k × W に置く（境目 k は x = LEFT + k × W）
  var W = 44;
  var CELL = 38;
  var LEFT = 40;
  var RIGHT = 12;
  var TOP = 30; // マスの上端
  var PT = 162; // 折れ線の上端（r = N）
  var PH = 72; // 折れ線の高さ
  var HEIGHT = PT + PH + 26;

  function viewBox(config) {
    return "0 0 " + (LEFT + config.array.length * W + RIGHT) + " " + HEIGHT;
  }

  function render(svg, s, config, h) {
    var a = config.array;
    var n = a.length;
    var K = config.K;
    var most = (config.mode == null ? "at-most" : config.mode) === "at-most";
    var width = LEFT + n * W + RIGHT;
    function bx(k) { return LEFT + k * W; }
    function cx(k) { return LEFT + k * W + W / 2; }
    var pad = (W - CELL) / 2;

    // 区間 [l, r) の枠（マスより先に描き、マスの外側に太い縁が見える）
    if (s.r > s.l) {
      svg.appendChild(h("rect", {
        x: bx(s.l) - 1, y: TOP - 5, width: (s.r - s.l) * W + 2, height: CELL + 10, rx: 8,
        class: "kp-v-cell is-focus",
      }));
    } else {
      svg.appendChild(h("rect", { x: bx(s.l) - 1.5, y: TOP - 5, width: 3, height: CELL + 10, class: "kp-v-mark is-b" }));
    }

    for (var k = 0; k < n; k++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      // 出した要素は薄い塗り。入れずに越えた要素（空区間のまま l と r を一緒に進めたもの）は破線の枠のまま残す
      if (k < s.l) { cls.push(s.skipped && s.skipped[k] ? "is-sentinel" : "is-no"); tcls.push("is-dim"); }
      else if (k < s.r) cls.push("is-yes");
      if (s.next === k) cls.push("is-sentinel");
      svg.appendChild(h("rect", { x: bx(k) + pad, y: TOP, width: CELL, height: CELL, rx: 6, class: cls.join(" ") }));
      svg.appendChild(h("text", { x: cx(k), y: TOP + CELL / 2, class: tcls.join(" ") }, a[k]));
      svg.appendChild(h("text", { x: cx(k), y: TOP + CELL + 14, class: "kp-v-text is-sub" }, k));
    }
    svg.appendChild(h("text", { x: LEFT / 2, y: TOP + CELL / 2, class: "kp-v-text is-sub", "font-style": "italic" }, "a"));
    svg.appendChild(h("text", { x: LEFT / 2, y: TOP + CELL + 14, class: "kp-v-text is-sub", "font-style": "italic" }, "i"));

    // 入れられなかった要素の上に ×
    if (s.next != null) {
      svg.appendChild(h("text", { x: cx(s.next) + 10, y: 10, class: "kp-v-ptr is-focus" }, "×"));
    }
    // r は枠の上に下向きの三角、l は番号の下に上向きの三角
    var rx = bx(s.r);
    svg.appendChild(h("text", { x: rx, y: 8, class: "kp-v-ptr is-b", "font-style": "italic" }, "r"));
    svg.appendChild(h("path", { d: "M" + (rx - 6) + " 16h12l-6 8z", class: "kp-v-mark is-b" }));
    var lx = bx(s.l);
    var ly = TOP + CELL + 24;
    svg.appendChild(h("path", { d: "M" + (lx - 6) + " " + (ly + 8) + "h12l-6 -8z", class: "kp-v-mark is-a" }));
    svg.appendChild(h("text", { x: lx, y: ly + 18, class: "kp-v-ptr is-a", "font-style": "italic" }, "l"));

    // 区間と和
    var ok = most ? s.sum <= K : s.sum >= K;
    var rel = most ? (ok ? " ≤ " : " > ") : (ok ? " ≥ " : " < ");
    svg.appendChild(h("text", { x: width / 2, y: ly + 38, class: "kp-v-text" },
      rangeText(s.l, s.r) + "　和 " + s.sum + rel + K));

    // 下：決まった r(l) の折れ線。横はマスと同じ列（l）、縦は r（0〜N）
    var yb = PT + PH;
    function py(v) { return yb - (v / n) * PH; }
    [0, n].forEach(function (v) {
      svg.appendChild(h("rect", { x: LEFT, y: py(v) - 0.5, width: n * W, height: 1, class: "kp-v-cell is-no" }));
      svg.appendChild(h("text", { x: LEFT - 6, y: py(v), class: "kp-v-text is-sub", "text-anchor": "end" }, v));
    });
    svg.appendChild(h("text", { x: LEFT / 2 - 2, y: PT - 14, class: "kp-v-text is-sub", "font-style": "italic" }, "r(l)"));
    var prev = null;
    for (var j = 0; j < n; j++) {
      var v = s.rl[j];
      if (v == null) continue;
      var x = cx(j), y = py(v);
      if (prev) {
        // 細い多角形で線分を描く（塗りの色を class で付ける）
        svg.appendChild(h("path", {
          d: "M" + prev.x + " " + (prev.y - 1) + "L" + x + " " + (y - 1) + "L" + x + " " + (y + 1) + "L" + prev.x + " " + (prev.y + 1) + "Z",
          class: "kp-v-mark is-b",
        }));
      }
      prev = { x: x, y: y };
    }
    for (var m = 0; m < n; m++) {
      var w = s.rl[m];
      if (w == null) continue;
      var cur = !s.done && m === s.l && (s.phase === "decide");
      svg.appendChild(h("circle", { cx: cx(m), cy: py(w), r: cur ? 6 : 4, class: "kp-v-mark " + (cur ? "is-focus" : "is-b") }));
      svg.appendChild(h("text", { x: cx(m), y: py(w) - 12, class: "kp-v-ptr " + (cur ? "is-focus" : "is-a") }, w));
    }
    // 横の目盛り（l）
    for (var q = 0; q < n; q++) {
      svg.appendChild(h("text", { x: cx(q), y: yb + 14, class: "kp-v-text is-sub" }, q));
    }
    svg.appendChild(h("text", { x: LEFT / 2, y: yb + 14, class: "kp-v-text is-sub", "font-style": "italic" }, "l"));
  }

  return {
    title: "尺取り法で、各左端に対する右端を戻さずに求める",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

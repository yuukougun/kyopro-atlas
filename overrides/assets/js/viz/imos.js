/*
 * 動く図：1 次元のいもす法（区間加算を差分の配列 D に印として記録し、最後に左から累積して A を作る）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="imos" data-config='{"n": 8, "ops": [{"l": 1, "r": 5, "x": 1}, {"l": 3, "r": 7, "x": 2}]}'></div>
 * config：
 *   n   … 列 A の長さ（1〜12）。D は長さ n + 1 で、D[n] は累積に使わない番兵
 *   ops … 区間加算の配列（1〜4 個）。{"l", "r", "x"} は半開区間 [l, r) に整数 x（0 でない）を足す。0 ≤ l < r ≤ n（0-indexed）
 *
 * ステップ：(1) 0 で埋めた D と、まだ求めていない A を示す → (2) 操作ごとに D[l] += x、D[r] −= x を 1 つずつ書き込む
 * （操作の区間を上に帯で示す）→ (3) 累積のカーソルを左から 1 つずつ進め、cur = D[0] + … + D[i] を A[i] に書く。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/imos.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("imos", def);
})(function () {
  "use strict";

  var MAX_N = 12;
  var MAX_OPS = 4;
  var MAX_ABS_X = 99; // 枠に収まる桁数にとどめる（x だけでなく、途中の D と最後の A の値もこの範囲にする）

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var ops = config.ops;
    if (!Array.isArray(ops) || ops.length < 1 || ops.length > MAX_OPS) {
      throw new Error("ops は 1〜" + MAX_OPS + " 個の操作の配列にする");
    }
    var out = [];
    for (var j = 0; j < ops.length; j++) {
      var o = ops[j];
      if (!o || typeof o !== "object") throw new Error("ops の要素は {l, r, x} にする");
      if (!isInt(o.l) || !isInt(o.r) || o.l < 0 || o.r > n || o.l >= o.r) {
        throw new Error("ops の区間は 0 ≤ l < r ≤ " + n + " の整数にする（半開区間 [l, r)）");
      }
      if (!isInt(o.x) || o.x === 0 || Math.abs(o.x) > MAX_ABS_X) {
        throw new Error("ops の x は 0 でない整数（絶対値 " + MAX_ABS_X + " 以下）にする");
      }
      out.push({ l: o.l, r: o.r, x: o.x });
    }
    // 印を書き込む途中の D と、累積した A の値も絶対値 MAX_ABS_X 以下でないと、枠からはみ出す
    var d = new Array(n + 1).fill(0);
    var tooBig = false;
    for (var q = 0; q < out.length; q++) {
      d[out[q].l] += out[q].x;
      if (Math.abs(d[out[q].l]) > MAX_ABS_X) tooBig = true;
      d[out[q].r] -= out[q].x;
      if (Math.abs(d[out[q].r]) > MAX_ABS_X) tooBig = true;
    }
    for (var i = 0, cur = 0; i < n; i++) {
      cur += d[i];
      if (Math.abs(cur) > MAX_ABS_X) tooBig = true;
    }
    if (tooBig) throw new Error("D と A の値が絶対値 " + MAX_ABS_X + " を超えない操作にする");
    return { n: n, ops: out };
  }

  function fmtVal(v) {
    return v < 0 ? "−" + -v : String(v);
  }
  function fmtAdd(v) {
    return v < 0 ? "−" + -v : "+" + v;
  }
  function fmtD(v) {
    return v === 0 ? "0" : fmtAdd(v);
  }
  function rangeText(l, r) {
    return "[" + l + ", " + r + ")";
  }
  function change(x) {
    return x > 0 ? x + " 増える" : -x + " 減る";
  }

  // 各ステップの状態：
  //   phase（init / plus / minus / sweep / done）、d（長さ n + 1）、a（長さ n。まだ求めていない所は null）、
  //   opIndex（いま記録している操作の番号。記録の段階でなければ −1）、shown（帯を描く操作の数）、
  //   focusD（いま書き込んだ・足した D の位置。なければ null）、cursor（累積のカーソル。なければ null）、
  //   cur（累積の途中の値。累積の段階でなければ null）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var d = new Array(n + 1).fill(0);
    var a = new Array(n).fill(null);
    var out = [];

    function snap(o) {
      out.push({
        phase: o.phase,
        d: d.slice(),
        a: a.slice(),
        opIndex: o.opIndex == null ? -1 : o.opIndex,
        shown: o.shown,
        focusD: o.focusD == null ? null : o.focusD,
        cursor: o.cursor == null ? null : o.cursor,
        cur: o.cur == null ? null : o.cur,
        caption: o.caption,
      });
    }

    snap({
      phase: "init", shown: 0,
      caption: "長さ N + 1 = " + (n + 1) + " の配列 D を 0 で用意する。D[" + n +
        "] は右端が N の区間のための番兵である。A はまだ求めていない。",
    });

    for (var j = 0; j < c.ops.length; j++) {
      var op = c.ops[j];
      var head = "操作 " + (j + 1) + "：" + rangeText(op.l, op.r) + " に " + fmtAdd(op.x) + "。";
      var before = d[op.l];
      d[op.l] += op.x;
      snap({
        phase: "plus", opIndex: j, shown: j + 1, focusD: op.l,
        caption: head + "D[" + op.l + "] += " + fmtVal(op.x) + "：位置 " + op.l + " から先の A がすべて " +
          change(op.x) + "。" + (before !== 0 ? "前の印 " + fmtD(before) + " と合わせて D[" + op.l + "] = " + fmtD(d[op.l]) + "。" : ""),
      });
      before = d[op.r];
      d[op.r] -= op.x;
      snap({
        phase: "minus", opIndex: j, shown: j + 1, focusD: op.r,
        caption: head + "D[" + op.r + "] −= " + fmtVal(op.x) + "：" +
          (op.r === n
            ? "r = N なので、A の外にある番兵の D[" + n + "] に書く（累積には入らないので、打ち消す相手はない）。"
            : "位置 " + op.r + " から先は打ち消して元に戻る。") +
          (before !== 0 ? "前の印 " + fmtD(before) + " と合わせて D[" + op.r + "] = " + fmtD(d[op.r]) + "。" : ""),
      });
    }

    var cur = 0;
    for (var i = 0; i < n; i++) {
      var prev = cur;
      cur += d[i];
      a[i] = cur;
      snap({
        phase: "sweep", shown: c.ops.length, focusD: i, cursor: i, cur: cur,
        caption: (i === 0 ? "印を付け終えたので、左から累積する。" : "") +
          "cur = " + fmtVal(prev) + " + D[" + i + "]（" + fmtD(d[i]) + "）= " + fmtVal(cur) + "。A[" + i + "] = cur = " +
          (i === 0 ? "D[0]" : i === 1 ? "D[0] + D[1]" : "D[0] + … + D[" + i + "]") +
          " = " + fmtVal(cur) + "。",
      });
    }

    snap({
      phase: "done", shown: c.ops.length,
      caption: "累積が終わった。A = " + a.map(fmtVal).join(", ") + "。番兵の D[" + n + "] は累積に使わない。" +
        "印を置くのは操作 1 回につき 2 か所、累積は 1 回だけである。",
    });
    return out;
  }

  // 描画の寸法：左に行の名前の欄 LABEL_W、列 k（0〜n）を x = LABEL_W + k × W に置く
  var W = 38;
  var CELL = 34;
  var LABEL_W = 22;
  var BAND_ROW = 26; // 操作の帯 1 本の行の高さ
  var TOP = 4;

  function layout(c) {
    var bandsBottom = TOP + c.ops.length * BAND_ROW;
    var dY = bandsBottom + 8;
    var idxY = dY + CELL + 11;
    var aY = idxY + 13;
    var curY = aY + CELL + 4;
    return {
      width: LABEL_W + (c.n + 1) * W + 2,
      dY: dY, idxY: idxY, aY: aY, curY: curY,
      height: curY + 30,
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
    function x0(k) { return LABEL_W + k * W + (W - CELL) / 2; }
    function cx(k) { return LABEL_W + k * W + W / 2; }

    // 操作の帯：区間 [l, r) の上に、いま記録している操作は太く強調し、ほかは細く描く
    for (var j = 0; j < s.shown; j++) {
      var op = c.ops[j];
      var now = j === s.opIndex;
      var y = TOP + j * BAND_ROW;
      var bx = x0(op.l);
      var bw = (op.r - op.l) * W - (W - CELL);
      svg.appendChild(h("rect", {
        x: bx, y: y + 16, width: bw, height: now ? 6 : 3, rx: 2,
        class: "kp-v-mark" + (now ? " is-b" : ""),
      }));
      var label = (j + 1) + "：" + rangeText(op.l, op.r) + " に " + fmtAdd(op.x);
      var half = label.length * 3.6 + 4;
      var lx = Math.max(half, Math.min(L.width - half, bx + bw / 2));
      svg.appendChild(h("text", { x: lx, y: y + 8, class: "kp-v-ptr " + (now ? "is-b" : "is-a") }, label));
    }

    // 行の名前
    svg.appendChild(h("text", { x: LABEL_W / 2, y: L.dY + CELL / 2, class: "kp-v-ptr is-a" }, "D"));
    svg.appendChild(h("text", { x: LABEL_W / 2, y: L.aY + CELL / 2, class: "kp-v-ptr is-a" }, "A"));

    var sweeping = s.phase === "sweep";
    // D の行
    for (var k = 0; k <= n; k++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      // 番兵は点線の枠。いま書き込んでいる番兵は、ほかの位置の注目と同じ塗りと太枠にし、点線は属性で残す
      // （kp.css では is-sentinel が is-yes・is-focus より後にあり、塗りと色を消してしまうため）
      var sentinelFocus = k === n && s.focusD === k;
      if (k === n && !sentinelFocus) cls.push("is-sentinel");
      if (sweeping && k <= s.cursor) cls.push("is-yes"); // 累積に入れ終えた D
      if (!sweeping && s.focusD === k) cls.push("is-yes");
      if (s.focusD === k) cls.push("is-focus");
      if (s.d[k] === 0) tcls.push("is-dim");
      var cellAttrs = { x: x0(k), y: L.dY, width: CELL, height: CELL, rx: 6, class: cls.join(" ") };
      if (sentinelFocus) cellAttrs["stroke-dasharray"] = "4 3";
      svg.appendChild(h("rect", cellAttrs));
      svg.appendChild(h("text", { x: cx(k), y: L.dY + CELL / 2, class: tcls.join(" ") }, fmtD(s.d[k])));
      svg.appendChild(h("text", { x: cx(k), y: L.idxY, class: "kp-v-text is-sub" }, k));
    }

    // A の行（まだ求めていない所は空の枠と「?」）
    for (var i = 0; i < n; i++) {
      var acls = ["kp-v-cell"];
      var atcls = ["kp-v-text"];
      var v = s.a[i];
      if (v == null) { acls.push("is-no"); atcls.push("is-dim"); }
      if (s.cursor === i) acls.push("is-focus");
      if (s.phase === "done") { acls.push("is-answer"); atcls.push("is-on-answer"); }
      svg.appendChild(h("rect", { x: x0(i), y: L.aY, width: CELL, height: CELL, rx: 6, class: acls.join(" ") }));
      svg.appendChild(h("text", { x: cx(i), y: L.aY + CELL / 2, class: atcls.join(" ") }, v == null ? "?" : fmtVal(v)));
    }

    // 累積のカーソル：A の下に三角の印と cur の値
    if (s.cursor != null) {
      var px = cx(s.cursor);
      svg.appendChild(h("path", { d: "M" + (px - 6) + " " + (L.curY + 8) + "h12l-6 -8z", class: "kp-v-mark is-focus" }));
      var t = "cur = " + fmtVal(s.cur);
      var halfT = t.length * 3.8 + 4;
      var tx = Math.max(halfT, Math.min(L.width - halfT, px));
      svg.appendChild(h("text", { x: tx, y: L.curY + 19, class: "kp-v-ptr is-focus" }, t));
    }
  }

  return {
    title: "いもす法で、区間加算を差分の印に記録し、左から累積して列を作る",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

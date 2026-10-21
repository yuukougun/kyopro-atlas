/*
 * 動く図：遅延セグメント木（区間加算・区間最小値）で、保留中の加算が子へ降りていく様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="lazy-segment-tree"
 *        data-config='{"array": [5, 3, 7, 2, 6, 4, 8, 1], "ops": [{"type": "add", "l": 0, "r": 4, "x": 2}, {"type": "min", "l": 3, "r": 6}]}'></div>
 * config：
 *   array … 整数の配列（1〜8 個）。長さが 2 の冪でなければ、余りの葉を単位元 ∞ で埋める
 *   ops   … 操作の配列（1〜6 個）。{"type": "add", "l", "r", "x"}（[l, r) に x を加える）か
 *            {"type": "min", "l", "r"}（[l, r) の最小値を求める）。0 ≤ l < r ≤ 配列の長さ（半開区間・0-indexed）
 *
 * 再帰で書いた遅延セグメント木と同じ順にノードを訪れる。ノード k は値 d[k]（k より上の保留を除いた区間の最小値）と、
 * 内部ノードなら保留 lz[k]（d[k] には反映済みで、子にはまだ配っていない加算）を持つ。
 *   ・区間にすっぽり入るノード：加算なら d と lz に足して下へは進まない。最小値なら d を答えの候補にする
 *   ・一部だけ重なるノード：先に lz を両方の子へ降ろし（push）、子を処理し、加算なら d を子から作り直す（pull）
 *   ・重ならないノード：何もしない
 * 保留のない push と、重ならないノードは状態にしない（ステップを短くするため）。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/lazy-segment-tree.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("lazy-segment-tree", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_OPS = 6;

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
      if (!isInt(a[i])) throw new Error("array の要素は整数にする");
    }
    var ops = config.ops;
    if (!Array.isArray(ops) || ops.length < 1 || ops.length > MAX_OPS) {
      throw new Error("ops は 1〜" + MAX_OPS + " 個の操作の配列にする");
    }
    var out = [];
    for (var j = 0; j < ops.length; j++) {
      var o = ops[j];
      if (!o || (o.type !== "add" && o.type !== "min")) throw new Error('ops の type は "add" か "min" にする');
      if (!isInt(o.l) || !isInt(o.r) || o.l < 0 || o.r > a.length || o.l >= o.r) {
        throw new Error("ops の区間は 0 ≤ l < r ≤ " + a.length + " の整数にする");
      }
      if (o.type === "add" && !isInt(o.x)) throw new Error("add の x は整数にする");
      out.push(o.type === "add" ? { type: "add", l: o.l, r: o.r, x: o.x } : { type: "min", l: o.l, r: o.r });
    }
    return { array: a.slice(), ops: out };
  }

  function treeSize(n) {
    var s = 1;
    while (s < n) s *= 2;
    return s;
  }

  function fmtVal(v) {
    if (v === Infinity) return "∞";
    return v < 0 ? "−" + -v : String(v);
  }
  function fmtAdd(v) {
    return v < 0 ? "−" + -v : "+" + v;
  }
  function rangeText(l, r) {
    return "[" + l + ", " + r + ")";
  }

  // 各ステップの状態：
  //   size（葉の数）、d・lz（添字 1〜2size−1。lz は内部ノードだけ意味を持ち、葉は 0）、
  //   opIndex（いまの操作の番号。初期状態は −1）、phase（init / op / apply / push / pull / take / end）、
  //   focus（注目するノード。なければ null）、touched（このステップで値か保留が変わったノード）、
  //   taken（この取得で候補にしたノード）、acc（取得の途中の答え。なければ null）、caption
  function states(config) {
    var c = validate(config);
    var a = c.array;
    var n = a.length;
    var size = treeSize(n);
    var d = new Array(2 * size).fill(Infinity);
    var lz = new Array(2 * size).fill(0);
    for (var i = 0; i < n; i++) d[size + i] = a[i];
    for (var k = size - 1; k >= 1; k--) d[k] = Math.min(d[2 * k], d[2 * k + 1]);

    var out = [];
    var cur = null; // いまの操作の情報
    function rng(k) {
      var dep = Math.floor(Math.log2(k));
      var w = size >> dep;
      var l = (k - (1 << dep)) * w;
      return [l, l + w];
    }
    function name(k) {
      var r = rng(k);
      return (k >= size ? "葉 " : "ノード ") + rangeText(r[0], r[1]);
    }
    function snap(phase, focus, touched, caption) {
      out.push({
        phase: phase,
        opIndex: cur ? cur.index : -1,
        size: size,
        d: d.slice(),
        lz: lz.slice(),
        focus: focus,
        touched: touched.slice(),
        taken: cur ? cur.taken.slice() : [],
        acc: cur && cur.op.type === "min" ? cur.acc : null,
        caption: caption,
      });
    }

    function allApply(k, f) {
      d[k] += f;
      if (k < size) lz[k] += f;
    }

    function push(k) {
      if (lz[k] === 0) return; // 保留がなければ何も起きないので、状態にしない
      var f = lz[k];
      allApply(2 * k, f);
      allApply(2 * k + 1, f);
      lz[k] = 0;
      snap("push", k, [2 * k, 2 * k + 1],
        name(k) + " は区間と一部だけ重なるので、子を見る前に保留 " + fmtAdd(f) +
          " を両方の子へ降ろす。子の最小値に " + fmtAdd(f) + " を足し、子が内部ノードなら子の保留にも足す。" +
          name(k) + " の保留はなくなる。");
    }

    function applyRec(l, r, f, k, kl, kr) {
      if (r <= kl || kr <= l) return;
      if (l <= kl && kr <= r) {
        var before = lz[k];
        allApply(k, f);
        var text;
        if (k >= size) {
          text = name(k) + " は区間にすっぽり入る。値に " + fmtAdd(f) + " を足して " + fmtVal(d[k]) + " にする（葉は保留を持たない）。";
        } else {
          text = name(k) + " は区間にすっぽり入る。区間の全要素に同じ数を足すと最小値も同じだけ増えるので、最小値に " +
            fmtAdd(f) + " を足して " + fmtVal(d[k]) + " にし、子に配る分を保留として残す。" +
            (before !== 0 ? "前からの保留 " + fmtAdd(before) + " と合わせて保留は " + fmtAdd(lz[k]) + " になる。" : "") +
            "ここより下へは進まない。";
        }
        snap("apply", k, [k], text);
        return;
      }
      push(k);
      var m = (kl + kr) >> 1;
      applyRec(l, r, f, 2 * k, kl, m);
      applyRec(l, r, f, 2 * k + 1, m, kr);
      var old = d[k];
      d[k] = Math.min(d[2 * k], d[2 * k + 1]);
      snap("pull", k, d[k] !== old ? [k] : [],
        "子の処理が終わったので、" + name(k) + " の最小値を子から作り直す：min(" + fmtVal(d[2 * k]) + ", " +
          fmtVal(d[2 * k + 1]) + ") = " + fmtVal(d[k]) + "。");
    }

    function prodRec(l, r, k, kl, kr) {
      if (r <= kl || kr <= l) return;
      if (l <= kl && kr <= r) {
        cur.acc = Math.min(cur.acc, d[k]);
        cur.taken.push(k);
        snap("take", k, [],
          name(k) + " は区間にすっぽり入る。上の保留はここまでにすべて降りているので、最小値 " + fmtVal(d[k]) +
            " はこの区間の正しい値である。答えの候補にする（いまの候補 " + fmtVal(cur.acc) + "）。");
        return;
      }
      push(k);
      var m = (kl + kr) >> 1;
      prodRec(l, r, 2 * k, kl, m);
      prodRec(l, r, 2 * k + 1, m, kr);
    }

    snap("init", null, [],
      "初期状態。各ノードの上段はその区間の最小値、下段は子にまだ配っていない加算（保留。— はなし）。" +
        (size > n ? "余りの葉は単位元 ∞ で埋める。" : ""));

    for (var j = 0; j < c.ops.length; j++) {
      var op = c.ops[j];
      cur = { index: j, op: op, taken: [], acc: Infinity };
      if (op.type === "add") {
        snap("op", null, [],
          "操作 " + (j + 1) + "：" + rangeText(op.l, op.r) + " の全要素に " + fmtAdd(op.x) + " を加える。根から下りていく。");
        applyRec(op.l, op.r, op.x, 1, 0, size);
        snap("end", null, [],
          "操作 " + (j + 1) + " が終わった。値や保留が変わったのは、区間の両端へ向かう経路の近くのノードだけである。");
      } else {
        snap("op", null, [],
          "操作 " + (j + 1) + "：" + rangeText(op.l, op.r) + " の最小値を求める。根から下りていく。");
        prodRec(op.l, op.r, 1, 0, size);
        snap("end", null, [],
          "操作 " + (j + 1) + " の答えは " + fmtVal(cur.acc) + "。保留が降りたのは通った経路の上だけである。" +
            (lz.some(function (v) { return v !== 0; }) ? "ほかのノードの保留は残ったままでよい。" : ""));
      }
    }
    return out;
  }

  // 描画の寸法：葉 1 つの幅 W、段の間隔 GAP、ノードの箱 BW × BH（スマホで縮みすぎないよう、横幅は 8 葉で 416 にとどめる）
  var W = 52;
  var GAP = 74;
  var BW = 46;
  var BH = 44;
  var TOP = 6;

  function layout(size) {
    var levels = Math.round(Math.log2(size)) + 1;
    return { levels: levels, width: size * W, treeBottom: TOP + (levels - 1) * GAP + BH };
  }

  function viewBox(config) {
    var size = treeSize(config.array.length);
    var L = layout(size);
    return "0 0 " + L.width + " " + (L.treeBottom + 52);
  }

  function render(svg, s, config, h) {
    var size = s.size;
    var n = config.array.length;
    var L = layout(size);
    function pos(k) {
      var dep = Math.floor(Math.log2(k));
      var w = (size >> dep) * W;
      return { x: (k - (1 << dep)) * w + w / 2, y: TOP + dep * GAP };
    }
    // 辺（細い多角形で描き、塗りの色を class で付ける）
    for (var k = 1; k < size; k++) {
      var p = pos(k);
      [2 * k, 2 * k + 1].forEach(function (ch) {
        var q = pos(ch);
        var x1 = p.x, y1 = p.y + BH, x2 = q.x, y2 = q.y;
        svg.appendChild(h("path", {
          d: "M" + (x1 - 0.8) + " " + y1 + "L" + (x1 + 0.8) + " " + y1 + "L" + (x2 + 0.8) + " " + y2 + "L" + (x2 - 0.8) + " " + y2 + "Z",
          class: "kp-v-mark",
        }));
      });
    }
    var touched = {};
    s.touched.forEach(function (t) { touched[t] = true; });
    var taken = {};
    s.taken.forEach(function (t) { taken[t] = true; });
    var showAnswer = s.phase === "end" && s.acc != null;

    for (var v = 1; v < 2 * size; v++) {
      var c = pos(v);
      var leaf = v >= size;
      var pad = leaf && v - size >= n;
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      if (pad) { cls.push("is-sentinel"); tcls.push("is-dim"); }
      if (touched[v]) cls.push("is-yes");
      if (taken[v]) {
        if (showAnswer) { cls.push("is-answer"); tcls.push("is-on-answer"); }
        else cls.push("is-yes");
      }
      if (s.focus === v) cls.push("is-focus");
      var x0 = c.x - BW / 2;
      svg.appendChild(h("rect", { x: x0, y: c.y, width: BW, height: BH, rx: 6, class: cls.join(" ") }));
      if (leaf) {
        svg.appendChild(h("text", { x: c.x, y: c.y + BH / 2, class: tcls.join(" ") }, fmtVal(s.d[v])));
      } else {
        svg.appendChild(h("text", { x: c.x, y: c.y + 13, class: tcls.join(" ") }, fmtVal(s.d[v])));
        svg.appendChild(h("rect", { x: x0 + 6, y: c.y + BH / 2, width: BW - 12, height: 1, class: "kp-v-mark" }));
        if (s.lz[v] !== 0) {
          svg.appendChild(h("text", { x: c.x, y: c.y + 33, class: "kp-v-ptr is-b" }, fmtAdd(s.lz[v])));
        } else {
          svg.appendChild(h("text", { x: c.x, y: c.y + 33, class: "kp-v-text is-sub" }, "—"));
        }
      }
    }
    // 葉の番号
    for (var i = 0; i < size; i++) {
      svg.appendChild(h("text", { x: i * W + W / 2, y: L.treeBottom + 12, class: "kp-v-text is-sub" }, i));
    }
    // いまの操作の区間を、葉の下の帯と文字で示す
    if (s.opIndex >= 0) {
      var op = config.ops[s.opIndex];
      var bx = op.l * W + (W - BW) / 2;
      var bw = (op.r - op.l) * W - (W - BW);
      var by = L.treeBottom + 22;
      svg.appendChild(h("rect", { x: bx, y: by, width: bw, height: 5, rx: 2, class: "kp-v-mark is-b" }));
      var label = rangeText(op.l, op.r) + (op.type === "add" ? " に " + fmtAdd(op.x) : " の最小値") +
        (s.acc != null && s.acc !== Infinity ? "（候補 " + fmtVal(s.acc) + "）" : "");
      svg.appendChild(h("text", { x: L.width / 2, y: by + 18, class: "kp-v-ptr is-b" }, label));
    }
  }

  return {
    title: "遅延セグメント木で、区間加算の保留が子へ降りていく様子",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

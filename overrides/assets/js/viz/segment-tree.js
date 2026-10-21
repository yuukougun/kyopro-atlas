/*
 * 動く図：非再帰のセグメント木で、区間の取得（prod）が両端から 1 段ずつ上がってノードを拾う様子と、
 * 一点更新（set）が葉から根まで作り直す様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="segment-tree"
 *        data-config='{"array": [5, 3, 7, 2, 6, 4, 8, 1], "op": "min", "ops": [{"type": "prod", "l": 1, "r": 7}, {"type": "set", "p": 5, "x": 0}]}'></div>
 * config：
 *   array … 整数の配列（1〜8 個。絶対値 99 以下）。長さが 2 の冪でなければ、余りの葉を単位元で埋める
 *   op    … 載せる演算。"min"（単位元 ∞）・"max"（単位元 −∞）・"sum"（単位元 0）。省略すると "min"
 *   ops   … 操作の配列（1〜6 個）。{"type": "prod", "l", "r"}（[l, r) の総積。0 ≤ l ≤ r ≤ 配列の長さ。l = r なら空区間）か
 *            {"type": "set", "p", "x"}（a_p ← x。0 ≤ p < 配列の長さ、x は絶対値 99 以下の整数）。添字は 0-indexed
 *
 * 本文 docs/ds/segment-tree.md の擬似コード（ACL と同じ配置）と同じ順に進める。
 *   ・ノード 1 が根、ノード k の子は 2k と 2k+1、葉 i はノード size + i
 *   ・prod：l ← l + size、r ← r + size とし、l < r の間、l が奇数ならノード l を sL の右に積んで l を 1 進め、
 *     r が奇数なら r を 1 戻してノード r を sR の左に積み、l・r を半分にして親の段へ上がる。1 回のくり返しを 1 状態にする
 *   ・set：葉を書き換え、親を根まで 1 つずつ作り直す。作り直し 1 回を 1 状態にする
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/segment-tree.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("segment-tree", def);
})(function () {
  "use strict";

  var MAX_N = 8;
  var MAX_OPS = 6;
  var MAX_ABS = 99;

  var MONOIDS = {
    min: { e: Infinity, f: function (x, y) { return Math.min(x, y); }, name: "最小値", fn: "min" },
    max: { e: -Infinity, f: function (x, y) { return Math.max(x, y); }, name: "最大値", fn: "max" },
    sum: { e: 0, f: function (x, y) { return x + y; }, name: "和", fn: null },
  };

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
      if (!isInt(a[i]) || Math.abs(a[i]) > MAX_ABS) throw new Error("array の要素は絶対値 " + MAX_ABS + " 以下の整数にする");
    }
    var op = config.op == null ? "min" : config.op;
    if (!Object.prototype.hasOwnProperty.call(MONOIDS, op)) throw new Error('op は "min"・"max"・"sum" のどれかにする');
    var ops = config.ops;
    if (!Array.isArray(ops) || ops.length < 1 || ops.length > MAX_OPS) {
      throw new Error("ops は 1〜" + MAX_OPS + " 個の操作の配列にする");
    }
    var out = [];
    for (var j = 0; j < ops.length; j++) {
      var o = ops[j];
      if (!o || (o.type !== "prod" && o.type !== "set")) throw new Error('ops の type は "prod" か "set" にする');
      if (o.type === "prod") {
        if (!isInt(o.l) || !isInt(o.r) || o.l < 0 || o.r > a.length || o.l > o.r) {
          throw new Error("prod の区間は 0 ≤ l ≤ r ≤ " + a.length + " の整数にする");
        }
        out.push({ type: "prod", l: o.l, r: o.r });
      } else {
        if (!isInt(o.p) || o.p < 0 || o.p >= a.length) throw new Error("set の p は 0 ≤ p < " + a.length + " の整数にする");
        if (!isInt(o.x) || Math.abs(o.x) > MAX_ABS) throw new Error("set の x は絶対値 " + MAX_ABS + " 以下の整数にする");
        out.push({ type: "set", p: o.p, x: o.x });
      }
    }
    return { array: a.slice(), op: op, ops: out };
  }

  function treeSize(n) {
    var s = 1;
    while (s < n) s *= 2;
    return s;
  }

  function depthOf(k) {
    var d = 0;
    while ((2 << d) <= k) d++;
    return d;
  }

  function fmtVal(v) {
    if (v === Infinity) return "∞";
    if (v === -Infinity) return "−∞";
    return v < 0 ? "−" + -v : String(v);
  }
  function rangeText(l, r) {
    return "[" + l + ", " + r + ")";
  }

  // 各ステップの状態：
  //   size（葉の数）、d（添字 1〜2size−1）、opIndex（いまの操作の番号。初期状態は −1）、
  //   phase（init / start / step / end / leaf / pull）、
  //   focus（このステップで使った・書き換えたノードの配列。太枠で描く）、
  //   takenL・takenR（この取得で sL・sR に積んだノード。積んだ順）、path（この更新で書き換えたノード）、
  //   lp・rp（prod の l・r。このステップの始めの値。なければ null）、sL・sR・ans（なければ null）、caption
  function states(config) {
    var c = validate(config);
    var M = MONOIDS[c.op];
    var a = c.array;
    var n = a.length;
    var size = treeSize(n);
    var d = new Array(2 * size).fill(M.e);
    for (var i = 0; i < n; i++) d[size + i] = a[i];
    for (var k = size - 1; k >= 1; k--) d[k] = M.f(d[2 * k], d[2 * k + 1]);

    function rng(k) {
      var dep = depthOf(k);
      var w = size >> dep;
      var l = (k - (1 << dep)) * w;
      return [l, l + w];
    }
    function name(k) {
      var r = rng(k);
      return "ノード " + k + "（" + rangeText(r[0], r[1]) + "）";
    }
    // x・y を結ぶ式。skipX・skipY が真の側（まだ何も積んでいない sL・sR や、余りの葉）は省く。
    // 値が単位元と等しいかどうかでは省かない（sum の 0 などを消さないため）
    function expr(x, y, skipX, skipY) {
      if (skipX && skipY) return fmtVal(M.e);
      if (skipX) return fmtVal(y);
      if (skipY) return fmtVal(x);
      var body = M.fn ? M.fn + "(" + fmtVal(x) + ", " + fmtVal(y) + ")" : fmtVal(x) + " + " + (y < 0 ? "(" + fmtVal(y) + ")" : fmtVal(y));
      return body + " = " + fmtVal(M.f(x, y));
    }
    function levelName(dep) {
      var up = depthOf(size) - dep;
      return up === 0 ? "葉の段" : "葉から " + up + " 段上";
    }

    var out = [];
    var cur = null;
    function snap(phase, focus, caption) {
      out.push({
        phase: phase,
        opIndex: cur ? cur.index : -1,
        size: size,
        d: d.slice(),
        focus: focus.slice(),
        takenL: cur && cur.takenL ? cur.takenL.slice() : [],
        takenR: cur && cur.takenR ? cur.takenR.slice() : [],
        path: cur && cur.path ? cur.path.slice() : [],
        lp: cur && cur.lp != null ? cur.lp : null,
        dep: cur && cur.dep != null ? cur.dep : null,
        rp: cur && cur.rp != null ? cur.rp : null,
        sL: cur && cur.sL !== undefined ? cur.sL : null,
        sR: cur && cur.sR !== undefined ? cur.sR : null,
        ans: cur && cur.ans !== undefined ? cur.ans : null,
        caption: caption,
      });
    }

    snap("init", [],
      "初期状態。各ノードの上の小さな数はノードの番号、大きな数はそのノードが受け持つ区間の" + M.name + "である。" +
        "ノード k の子は 2k と 2k + 1 で、葉 i はノード " + size + " + i にある。" +
        (size > n ? "余りの葉は単位元 " + fmtVal(M.e) + " で埋める。" : ""));

    for (var j = 0; j < c.ops.length; j++) {
      var op = c.ops[j];
      var head = "操作 " + (j + 1) + "：";
      if (op.type === "prod") {
        cur = { index: j, takenL: [], takenR: [], sL: M.e, sR: M.e, lp: op.l + size, rp: op.r + size, dep: depthOf(size) };
        snap("start", [],
          head + rangeText(op.l, op.r) + " の" + M.name + "を求める。l ← " + op.l + " + " + size + " = " + cur.lp +
            "、r ← " + op.r + " + " + size + " = " + cur.rp + " として葉の段に置き、sL = sR = " + fmtVal(M.e) + "（単位元）から始める。");
        var l = cur.lp, r = cur.rp;
        while (l < r) {
          cur.lp = l;
          cur.rp = r;
          var parts = [levelName(cur.dep) + "で l = " + l + "、r = " + r + "。"];
          var focus = [];
          if (l & 1) {
            var oldL = cur.sL;
            var emptyL = cur.takenL.length === 0;
            cur.sL = M.f(cur.sL, d[l]);
            cur.takenL.push(l);
            focus.push(l);
            parts.push((l === 1 ? "l = 1 は根で、区間はこのノードの全体なので、" : "l は奇数（右の子）で親は左にはみ出すので、") + name(l) + "の値 " + fmtVal(d[l]) + " を sL の右に積み（sL = " +
              expr(oldL, d[l], emptyL, false) + "）、l を " + (l + 1) + " に進める。");
            l++;
          } else {
            parts.push("l は偶数（左の子）なので、ここでは使わずに親へ任せる。");
          }
          if (r & 1) {
            r--;
            var oldR = cur.sR;
            var emptyR = cur.takenR.length === 0;
            cur.sR = M.f(d[r], cur.sR);
            cur.takenR.push(r);
            focus.push(r);
            parts.push("r は奇数で、r − 1 = " + r + " は左の子なので親は右にはみ出す。r を " + r + " に戻し、" + name(r) + "の値 " + fmtVal(d[r]) + " を sR の左に積む（sR = " +
              expr(d[r], oldR, false, emptyR) + "）。");
          } else {
            parts.push(r === 2
              ? "r − 1 = 1 は根で、l の側で使ったので、r の側で使うノードはない。"
              : "r は偶数（r − 1 が右の子）なので、ここでは使わずに親へ任せる。");
          }
          l >>= 1;
          r >>= 1;
          parts.push(cur.dep === 0 ? "l・r を半分にすると、l = " + l + "、r = " + r + " になる。" : "l・r を半分にして親の段へ上がり、l = " + l + "、r = " + r + " になる。");
          snap("step", focus, parts.join(""));
          cur.dep--;
        }
        cur.lp = l;
        cur.rp = r;
        cur.ans = M.f(cur.sL, cur.sR);
        var used = cur.takenL.concat(cur.takenR.slice().reverse());
        var endText;
        if (used.length === 0) {
          endText = "l = r = " + l + " なのでくり返さない。空区間なので、答えは単位元 " + fmtVal(M.e) + " である。";
        } else {
          endText = "l = r = " + l + " になったので止まる。答えは sL と sR を結んだ " + expr(cur.sL, cur.sR, cur.takenL.length === 0, cur.takenR.length === 0) + " である。" +
            "使ったノードは " + used.map(function (u) { return u; }).join("・") + " の " + used.length +
            " 個で、受け持つ区間を左から並べるとちょうど " + rangeText(op.l, op.r) + " になる。";
        }
        snap("end", [], head.replace("：", "") + " の終わり。" + endText);
      } else {
        cur = { index: j, path: [] };
        var leaf = size + op.p;
        var old = d[leaf];
        d[leaf] = op.x;
        cur.path.push(leaf);
        snap("leaf", [leaf],
          head + "a" + op.p + " を " + fmtVal(op.x) + " にする。葉はノード " + op.p + " + " + size + " = " + leaf + " で、値を " +
            fmtVal(old) + " から " + fmtVal(op.x) + " に書き換える。" +
            (size === 1 ? "葉がそのまま根なので、作り直すノードはない。" : "次に、親を根まで 1 つずつ作り直す。"));
        var kk = leaf >> 1;
        while (kk >= 1) {
          var before = d[kk];
          d[kk] = M.f(d[2 * kk], d[2 * kk + 1]);
          cur.path.push(kk);
          var txt = name(kk) + "を子のノード " + 2 * kk + "・" + (2 * kk + 1) + " から作り直す：" + expr(d[2 * kk], d[2 * kk + 1], rng(2 * kk)[0] >= n, rng(2 * kk + 1)[0] >= n) + "。" +
            (before === d[kk] ? "値は " + fmtVal(before) + " のまま変わらない。" : "値は " + fmtVal(before) + " から " + fmtVal(d[kk]) + " に変わる。");
          if (kk === 1) {
            txt += "根まで作り直したので終わる。書き換えたのは葉から根までの " + cur.path.length + " ノード（" + cur.path.join("・") +
              "）だけである。";
          }
          snap("pull", [kk], txt);
          kk >>= 1;
        }
      }
    }
    return out;
  }

  // 描画の寸法：葉 1 つの幅 W、段の間隔 GAP、ノードの箱 BW × BH。8 葉で横幅 416
  var W = 52;
  var GAP = 82;
  var BW = 46;
  var BH = 52;
  var TOP = 28;

  function layout(size) {
    var levels = depthOf(size) + 1;
    var treeBottom = TOP + (levels - 1) * GAP + BH;
    return { levels: levels, width: Math.max(size * W, 260), treeBottom: treeBottom, height: treeBottom + 62 };
  }

  function viewBox(config) {
    var size = treeSize(config.array.length);
    var L = layout(size);
    return "0 0 " + L.width + " " + L.height;
  }

  function render(svg, s, config, h) {
    var size = s.size;
    var n = config.array.length;
    var L = layout(size);
    var X0 = (L.width - size * W) / 2;
    var M = MONOIDS[config.op == null ? "min" : config.op];
    function pos(k) {
      var dep = depthOf(k);
      var w = (size >> dep) * W;
      return { x: X0 + (k - (1 << dep)) * w + w / 2, y: TOP + dep * GAP };
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
    var focus = {};
    s.focus.forEach(function (t) { focus[t] = true; });
    var tag = {};
    s.takenL.forEach(function (t) { tag[t] = "sL へ"; });
    s.takenR.forEach(function (t) { tag[t] = "sR へ"; });
    var path = {};
    s.path.forEach(function (t) { path[t] = true; });
    var showAnswer = s.phase === "end";

    for (var v = 1; v < 2 * size; v++) {
      var c = pos(v);
      var pad = v >= size && v - size >= n;
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      var attrs = {};
      if (pad) { cls.push("is-sentinel"); tcls.push("is-dim"); }
      if (tag[v]) {
        if (showAnswer) { cls.push("is-answer"); tcls.push("is-on-answer"); }
        else cls.push("is-yes");
      }
      if (path[v]) {
        cls.push("is-yes");
        if (!focus[v]) attrs["stroke-dasharray"] = "5 3";
      }
      if (focus[v]) cls.push("is-focus");
      var x0 = c.x - BW / 2;
      attrs.x = x0; attrs.y = c.y; attrs.width = BW; attrs.height = BH; attrs.rx = 6; attrs.class = cls.join(" ");
      svg.appendChild(h("rect", attrs));
      var subCls = tcls.indexOf("is-on-answer") >= 0 ? "kp-v-text is-sub is-on-answer" : "kp-v-text is-sub";
      svg.appendChild(h("text", { x: c.x, y: c.y + 11, class: subCls }, v));
      svg.appendChild(h("text", { x: c.x, y: c.y + (tag[v] ? 27 : 32), class: tcls.join(" ") }, fmtVal(s.d[v])));
      if (tag[v]) {
        svg.appendChild(h("text", { x: c.x, y: c.y + 43, class: subCls }, tag[v]));
      }
    }

    // prod の l・r：その段の境目に縦の棒を立て、上に名前を書く（r は区間の右の外側の境目）
    if (s.lp != null && s.dep != null && s.dep >= 0) {
      var dep = s.dep;
      var w = (size >> dep) * W;
      var y = TOP + dep * GAP;
      var bx = function (k) { return X0 + (k - (1 << dep)) * w; };
      var marks = s.lp === s.rp ? [[s.lp, "l = r"]] : [[s.lp, "l"], [s.rp, "r"]];
      marks.forEach(function (m) {
        var x = bx(m[0]);
        var bxx = Math.min(Math.max(x - 1.5, 0), L.width - 3);
        svg.appendChild(h("rect", { x: bxx, y: y - 6, width: 3, height: BH + 12, class: "kp-v-mark is-focus" }));
        var tx = Math.min(Math.max(x, 18), L.width - 18);
        // 辺と重なっても読めるよう、文字の周りを背景の色で縁取る
        svg.appendChild(h("text", {
          x: tx, y: y - 15, class: "kp-v-ptr is-focus",
          style: "stroke: var(--md-default-bg-color); stroke-width: 4px; stroke-linejoin: round; paint-order: stroke",
        }, m[1] + " = " + m[0]));
      });
    }

    // 葉の添字
    for (var i = 0; i < size; i++) {
      svg.appendChild(h("text", { x: X0 + i * W + W / 2, y: L.treeBottom + 11, class: "kp-v-text is-sub" }, "a" + i));
    }
    // いまの操作：取得なら区間を帯で、更新なら位置を三角で示し、下に途中の値を書く
    var status;
    if (s.opIndex < 0) status = "列 (" + config.array.map(fmtVal).join(", ") + ") の" + M.name;
    else {
      var op = config.ops[s.opIndex];
      var by = L.treeBottom + 21;
      if (op.type === "prod") {
        if (op.r > op.l) {
          svg.appendChild(h("rect", {
            x: X0 + op.l * W + (W - BW) / 2, y: by, width: (op.r - op.l) * W - (W - BW), height: 5, rx: 2, class: "kp-v-mark is-b",
          }));
        }
        status = rangeText(op.l, op.r) + " の" + M.name + "　sL = " + fmtVal(s.sL) + "　sR = " + fmtVal(s.sR) +
          (s.ans != null ? "　答え " + fmtVal(s.ans) : "");
      } else {
        var cx = X0 + op.p * W + W / 2;
        svg.appendChild(h("path", { d: "M" + (cx - 6) + " " + (by + 9) + "h12l-6 -8z", class: "kp-v-mark is-b" }));
        status = "a" + op.p + " ← " + fmtVal(op.x) + "（葉から根へ作り直す）";
      }
    }
    svg.appendChild(h("text", { x: L.width / 2, y: L.treeBottom + 46, class: "kp-v-ptr is-b" }, status));
  }

  return {
    title: "セグメント木の区間の取得が両端から 1 段ずつ上がってノードを拾う様子と、一点更新が根まで作り直す様子",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

/*
 * 動く図：Z-algorithm で、Z-box の内側は値を写し、はみ出した分だけ比べる様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="z-algorithm" data-config='{"s": "aabaabaac"}'></div>
 * config：
 *   s … 英数字と # $ からなる 1〜10 文字の文字列（# と $ は P＋区切り＋T の区切りに使う）。
 *       N = 10 で viewBox の幅は 392、スマホの幅 360 でも 0.78 倍ほどで字が読める
 *
 * snippets/z-algorithm/own-z.cpp と同じ手順をたどる。z[0] = N とし、i = 1, 2, …, N − 1 の順に、
 * Z-box [l, r)（S[l, r) = S[0, r − l) で r が最も右のもの。最初は l = r = 0）を使って z[i] を決める。
 *   1：i ≥ r。S[0] と S[i] から 1 文字ずつ比べる
 *   2：i < r かつ z[i − l] < r − i。z[i] = z[i − l] を写し、比べない
 *   3：i < r かつ z[i − l] ≥ r − i。r − i 文字の一致を写し、箱の外の S[r] と S[r − i] から比べる
 * i + z[i] > r なら Z-box を [i, i + z[i]) に取り替える。本文の説明に合わせ、2 では比較を描かない
 * （実装ではここで 1 回比べて必ず失敗する）。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/z-algorithm.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("z-algorithm", def);
})(function () {
  "use strict";

  var MAX_N = 10;
  var CHARS = /^[A-Za-z0-9#$]+$/;

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var s = config.s;
    if (typeof s !== "string" || s.length < 1 || s.length > MAX_N) {
      throw new Error("s は 1〜" + MAX_N + " 文字の文字列にする");
    }
    if (!CHARS.test(s)) throw new Error("s の文字は英数字か # $ にする");
    return { s: s };
  }

  function rangeText(l, r) {
    return "[" + l + ", " + r + ")";
  }

  function boxText(l, r) {
    if (r === 0) return "Z-box はまだない（l = r = 0）";
    return "Z-box " + rangeText(l, r) + (l === r ? "（空）" : "");
  }

  // 比べた結果を文章にする。from は比べ始めた k、comps は比較の列
  function compareText(s, i, from, comps, lead) {
    var n = s.length;
    var ok = comps.filter(function (c) { return c.ok; }).length;
    var last = comps.length ? comps[comps.length - 1] : null;
    var head = lead + "S[" + (i + from) + "] と S[" + from + "] から 1 文字ずつ比べる。";
    if (last && !last.ok) {
      var a = i + last.k;
      return head + (ok > 0 ? ok + " 文字一致し、" : "") + "S[" + a + "] = " + s[a] + " と S[" + last.k + "] = " + s[last.k] +
        " で食い違う。";
    }
    // 食い違わずに文字列の終わりに着いた（最後の比較は成功か、比べる文字が残っていない）
    if (i + from >= n) return "箱の外に比べる文字は残っていない（文字列の終わり）。";
    return head + ok + " 文字一致し、文字列の終わりに着く。";
  }

  // 各ステップの状態：
  //   phase（start / step / done）、i（いまの位置。start と done は null）、
  //   l・r（z[i] を決めるのに使う Z-box。step 以外はその時点の箱）、kase（1・2・3）、
  //   ref（対応する位置 i − l。1 なら null）、copy（写した文字数）、
  //   comps（比較の列 {k, ok}。S[i + k] と S[k] を比べた）、z（決まった値。未定は null）、
  //   newBox（取り替えた後の箱 {l, r}。取り替えなければ null）、success（成功した比較の累計）、caption
  function states(config) {
    var c = validate(config);
    var s = c.s;
    var n = s.length;
    var z = new Array(n).fill(null);
    z[0] = n;
    var l = 0;
    var r = 0;
    var success = 0;
    var out = [];

    out.push({
      phase: "start", i: null, l: 0, r: 0, kase: null, ref: null, copy: 0, comps: [], z: z.slice(), newBox: null,
      success: 0,
      caption: "S = " + s + "（N = " + n + "）。z[0] は S 自身との比較なので N = " + n + " とする。" +
        (n > 1 ? "Z-box はまだなく l = r = 0 である。i = 1 から順に z[i] を決める。" : "ほかの位置はない。"),
    });

    for (var i = 1; i < n; i++) {
      var kase, ref = null, copy = 0, k = 0, from = 0;
      if (i >= r) {
        kase = 1;
      } else {
        ref = i - l;
        if (z[ref] < r - i) {
          kase = 2;
          copy = z[ref];
          k = copy;
        } else {
          kase = 3;
          copy = r - i;
          k = copy;
        }
      }
      var comps = [];
      if (kase !== 2) {
        from = k;
        while (i + k < n) {
          var eq = s[k] === s[i + k];
          comps.push({ k: k, ok: eq });
          if (!eq) break;
          k++;
          success++;
        }
      }
      z[i] = k;

      var text = "i = " + i + "。";
      if (kase === 1) {
        text += (r === 0 ? "Z-box はまだないので" : "i は " + boxText(l, r) + " の外にある（i ≥ r）ので") +
          "、使える情報はない。" + compareText(s, i, from, comps, "");
      } else if (kase === 2) {
        text += "i は " + boxText(l, r) + " の内側にある。対応する位置 i − l = " + ref + " の z[" + ref + "] = " + z[ref] +
          " は r − i = " + (r - i) + " より小さいので、比べずに写す。S[" + (i + copy) + "] ≠ S[" + copy +
          "] も、箱の内側の対応 S[" + (ref + copy) + "] ≠ S[" + copy + "] から分かっている。";
      } else {
        text += "i は " + boxText(l, r) + " の内側にある。対応する位置 i − l = " + ref + " の z[" + ref + "] = " + z[ref] +
          " は r − i = " + (r - i) + " 以上なので、" + copy + " 文字の一致だけを写す。" +
          compareText(s, i, from, comps, "箱の外の ");
      }
      text += "z[" + i + "] = " + k + "。";

      var newBox = null;
      if (i + k > r) {
        newBox = { l: i, r: i + k };
        text += "右端が i + z[i] = " + (i + k) + " に伸びたので、Z-box を " + rangeText(i, i + k) +
          (k === 0 ? "（空）" : " ") + "に取り替える。";
      }
      text = text.replace(/） /g, "）"); // 「（空） の」の空白を詰める
      out.push({
        phase: "step", i: i, l: l, r: r, kase: kase, ref: ref, copy: copy, comps: comps, z: z.slice(), newBox: newBox,
        success: success, caption: text,
      });
      if (newBox) {
        l = newBox.l;
        r = newBox.r;
      }
    }

    out.push({
      phase: "done", i: null, l: l, r: r, kase: null, ref: null, copy: 0, comps: [], z: z.slice(), newBox: null,
      success: success,
      caption: "Z 配列は (" + z.join(", ") + ") である。成功した比較は合計 " + success + " 回で、N = " + n +
        " を超えない。失敗した比較は各位置で高々 1 回である（写すだけの位置では 0 回）。",
    });
    return out;
  }

  // 描画の寸法：列 j（0〜N−1）を x = LEFT + j × W に置く
  var LEFT = 44;
  var W = 34;
  var CELL = 30;
  var RIGHT = 8;
  var MIN_WIDTH = 360; // 凡例が収まる幅
  var Y_NEW = 24; // 取り替えた後の Z-box の括弧の線（破線）。文字はその上
  var Y_BOX = 44; // Z-box の括弧の線
  var Y_S = 54; // S の行の上端
  var Y_IDX = 100; // 添字の行
  var Y_P = 144; // 先頭をずらした行の上端
  var Y_Z = 196; // z の行の上端
  var Y_LEG = 248;
  var Y_CNT = 270;
  var HEIGHT = 282;

  function viewBox(config) {
    var n = config.s.length;
    return "0 0 " + Math.max(MIN_WIDTH, LEFT + n * W + RIGHT) + " " + HEIGHT;
  }

  // 正方形の中に斜線を引く（pattern は id がページ内でぶつかるので使わない）
  function hatch(svg, h, x0, y0, size) {
    var step = 6;
    var d = "";
    for (var c = step; c < 2 * size; c += step) {
      var ax = x0 + Math.max(0, c - size), ay = y0 + Math.min(c, size);
      var bx = x0 + Math.min(c, size), by = y0 + Math.max(0, c - size);
      d += "M" + ax + " " + ay + "L" + bx + " " + by;
    }
    svg.appendChild(h("path", { d: d, style: "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.2" }));
  }

  var DASHED = "stroke-dasharray:5 3;stroke:var(--md-default-fg-color--light);stroke-width:1.8";
  var HALO = "paint-order:stroke;stroke:var(--md-default-bg-color);stroke-width:3px";

  // 1 マスを描く。kind：plain / dim / copy / ok / ng / known（比べずに分かる不一致）
  function cell(svg, h, x, y, ch, kind) {
    var cls = "kp-v-cell";
    var style = null;
    if (kind === "ok") cls += " is-yes";
    else if (kind === "copy") { cls += " is-no"; style = DASHED; }
    else if (kind === "dim") style = "fill:none;stroke:var(--md-default-fg-color--lighter);stroke-width:1";
    else if (kind === "known") style = "stroke-dasharray:1.5 2.5;stroke-width:2";
    svg.appendChild(h("rect", { x: x, y: y, width: CELL, height: CELL, rx: 5, class: cls, style: style }));
    if (kind === "ng") hatch(svg, h, x, y, CELL);
    if (kind === "known") {
      svg.appendChild(h("text", {
        x: x + CELL - 5, y: y + 7, class: "kp-v-text is-sub", style: "font-size:11px;font-weight:700",
      }, "≠"));
    }
    svg.appendChild(h("text", {
      x: x + CELL / 2, y: y + CELL / 2, class: "kp-v-text" + (kind === "dim" ? " is-dim" : ""),
      style: kind === "ng" ? HALO + ";font-weight:700" : kind === "ok" ? "font-weight:700" : null,
    }, ch));
  }

  function render(svg, st, config, h) {
    var s = config.s;
    var n = s.length;
    function x0(j) { return LEFT + j * W + (W - CELL) / 2; }
    function cx(j) { return LEFT + j * W + W / 2; }
    function edge(j) { return LEFT + j * W; } // 列 j の左の境目
    var i = st.i;

    // 行の名前
    [["S", Y_S + CELL / 2], ["添字", Y_IDX], ["先頭", Y_P + CELL / 2], ["z", Y_Z + CELL / 2]].forEach(function (p) {
      if (p[0] === "先頭" && st.phase !== "step") return; // 先頭をずらした行は z[i] を決めるステップだけ
      svg.appendChild(h("text", { x: 4, y: p[1], class: "kp-v-text is-sub", style: "text-anchor:start;font-size:13px" }, p[0]));
    });

    // 各位置の扱い（S の行の位置 i + k と、先頭の行の k に同じ印を付ける）
    var kinds = {};
    if (st.phase === "step") {
      for (var k = 0; k < st.copy; k++) kinds[k] = "copy";
      st.comps.forEach(function (c) { kinds[c.k] = c.ok ? "ok" : "ng"; });
      // 場合 2：z[i − l] の位置の不一致は、比べなくても箱の内側の対応から分かる
      if (st.kase === 2) kinds[st.copy] = "known";
    }
    var vbWidth = Math.max(MIN_WIDTH, LEFT + n * W + RIGHT);

    // Z-box の括弧（z[i] を決めるのに使う箱）。空の箱 [l, l) は境目の縦線で示す
    if (st.r > st.l) {
      var bl = edge(st.l) + 2, br = edge(st.r) - 2;
      svg.appendChild(h("path", {
        d: "M" + bl + " " + (Y_BOX + 7) + "V" + Y_BOX + "H" + br + "V" + (Y_BOX + 7),
        style: "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.5",
      }));
      svg.appendChild(h("text", { x: bl, y: Y_BOX - 9, class: "kp-v-ptr is-b", style: "font-style:italic" }, "l"));
      svg.appendChild(h("text", { x: br, y: Y_BOX - 9, class: "kp-v-ptr is-b", style: "font-style:italic" }, "r"));
      var mid = (bl + br) / 2;
      if (br - bl > 70) {
        svg.appendChild(h("text", { x: mid, y: Y_BOX - 9, class: "kp-v-ptr is-b", style: "font-size:12px" }, "Z-box"));
      }
    } else if (st.r > 0) {
      var ex = edge(st.l);
      svg.appendChild(h("path", {
        d: "M" + ex + " " + (Y_BOX - 2) + "V" + (Y_S - 1),
        style: "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.5",
      }));
      svg.appendChild(h("text", { x: ex, y: Y_BOX - 9, class: "kp-v-ptr is-b", style: "font-style:italic;font-size:12px" }, "l = r"));
    }

    // 取り替えた後の Z-box（破線の括弧。次のステップから上の括弧になる）
    if (st.newBox) {
      var nl = edge(st.newBox.l) + 2, nr = edge(st.newBox.r) - 2;
      var label = "新しい Z-box " + rangeText(st.newBox.l, st.newBox.r) + (st.newBox.l === st.newBox.r ? "（空）" : "");
      if (st.newBox.r > st.newBox.l) {
        svg.appendChild(h("path", {
          d: "M" + nl + " " + (Y_NEW + 7) + "V" + Y_NEW + "H" + nr + "V" + (Y_NEW + 7),
          style: "fill:none;stroke:var(--md-accent-fg-color);stroke-width:1.8;stroke-dasharray:5 3",
        }));
      } else {
        nl = nr = edge(st.newBox.l);
        svg.appendChild(h("path", {
          d: "M" + nl + " " + (Y_NEW - 4) + "V" + (Y_NEW + 8),
          style: "fill:none;stroke:var(--md-accent-fg-color);stroke-width:1.8;stroke-dasharray:3 2",
        }));
      }
      // 文字は括弧の上の中央に置き、図の端からはみ出さないようにずらす
      var lw = label.length * 8;
      var tx = Math.min(Math.max((nl + nr) / 2, lw / 2 + 2), vbWidth - lw / 2 - 2);
      svg.appendChild(h("text", {
        x: tx, y: Y_NEW - 13, class: "kp-v-ptr is-b", style: "font-size:12px;font-weight:400",
      }, label));
    }

    // S の行と添字
    for (var j = 0; j < n; j++) {
      var kind = "plain";
      if (st.phase === "step" && j >= i && kinds[j - i]) kind = kinds[j - i];
      cell(svg, h, x0(j), Y_S, s[j], kind);
      if (j === i) {
        svg.appendChild(h("circle", { cx: cx(j), cy: Y_IDX, r: 9, class: "kp-v-cell is-answer" }));
        svg.appendChild(h("text", { x: cx(j), y: Y_IDX, class: "kp-v-text is-sub is-on-answer" }, j));
      } else {
        svg.appendChild(h("text", { x: cx(j), y: Y_IDX, class: "kp-v-text is-sub" }, j));
      }
    }

    if (st.phase === "step") {
      // 対応する位置 i − l から i へ、値を写す矢印
      if (st.ref != null) {
        var ax = cx(st.ref), bx = cx(i), top = Y_IDX + 11, bottom = Y_IDX + 30;
        svg.appendChild(h("path", {
          d: "M" + ax + " " + top + "C" + ax + " " + bottom + " " + (bx - 6) + " " + bottom + " " + (bx - 2) + " " + (top + 6),
          style: "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.8",
        }));
        svg.appendChild(h("path", {
          d: "M" + (bx - 7) + " " + (top + 9) + "L" + bx + " " + top + "L" + (bx + 2) + " " + (top + 11) + "z",
          class: "kp-v-mark",
        }));
        svg.appendChild(h("text", {
          x: (ax + bx) / 2, y: bottom + 4, class: "kp-v-text is-sub", style: HALO,
        }, "z[" + st.ref + "]"));
      }
      // 先頭をずらして i にそろえた行
      for (var t = 0; i + t < n; t++) {
        var pk = kinds[t] || "dim";
        cell(svg, h, x0(i + t), Y_P, s[t], pk);
      }
      // 先頭の行の左端に「S[0]」の目印
      svg.appendChild(h("text", { x: cx(i), y: Y_P + CELL + 9, class: "kp-v-text is-sub", style: "font-size:11px" }, "S[0]"));
    }

    // z の行
    for (var q = 0; q < n; q++) {
      var v = st.z[q];
      var X = x0(q);
      if (v == null) {
        svg.appendChild(h("rect", { x: X, y: Y_Z, width: CELL, height: CELL, rx: 5, class: "kp-v-cell is-sentinel" }));
        continue;
      }
      var isNew = st.phase === "step" ? q === i : st.phase === "start" && q === 0;
      var isRef = st.phase === "step" && q === st.ref;
      svg.appendChild(h("rect", {
        x: X, y: Y_Z, width: CELL, height: CELL, rx: 5,
        class: "kp-v-cell" + (isNew ? " is-answer" : ""),
        style: isRef ? "stroke-dasharray:4 2;stroke-width:3" : null,
      }));
      svg.appendChild(h("text", {
        x: X + CELL / 2, y: Y_Z + CELL / 2, class: "kp-v-text" + (isNew ? " is-on-answer" : ""),
        style: isRef ? "font-weight:700" : null,
      }, v));
    }

    // 凡例（形で区別できるようにする）
    var lx = 4;
    [["ok", "比べて一致"], ["ng", "比べて不一致"], ["copy", "写した（比べない）"]].forEach(function (p) {
      var sz = 14;
      var cls = "kp-v-cell" + (p[0] === "ok" ? " is-yes" : p[0] === "copy" ? " is-no" : "");
      svg.appendChild(h("rect", {
        x: lx, y: Y_LEG - sz / 2, width: sz, height: sz, rx: 3, class: cls, style: p[0] === "copy" ? "stroke-dasharray:3 2" : null,
      }));
      if (p[0] === "ng") hatch(svg, h, lx, Y_LEG - sz / 2, sz);
      svg.appendChild(h("text", {
        x: lx + sz + 4, y: Y_LEG, class: "kp-v-text is-sub", style: "text-anchor:start;font-size:12px",
      }, p[1]));
      lx += sz + 10 + p[1].length * 12;
    });
    svg.appendChild(h("text", {
      x: 4, y: Y_CNT, class: "kp-v-text is-sub", style: "text-anchor:start;font-size:13px",
    }, "成功した比較の累計：" + st.success + " 回（N = " + n + " 以下）"));
  }

  return {
    title: "Z-algorithm で、Z-box の内側は値を写し、はみ出した分だけ比べる",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

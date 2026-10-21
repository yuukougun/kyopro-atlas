/*
 * 動く図：桁 DP の「N と一致しているか」のフラグ。一致の道が 1 本だけ伸び、各桁で未満の枝が分かれる（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="digit-dp-tight" data-config='{"digits": "253", "base": 10}'></div>
 * config：
 *   digits … N を base 進で書いた数字の列（1〜6 文字）。先頭は 0 にしない（N = 0 の "0" だけは可）
 *            横幅は桁数に比例する。幅 360px のスマホで箱の中の小さい文字まで読めるのは 4 桁ぐらいまでなので、本文では 4 桁以下にする
 *   base   … 2〜10 の整数（省略すると 10）
 *
 * 0 以上 N 以下の整数 X を、N と同じ桁数に 0 で埋めて上の桁から比べる。X ≠ N なら「初めて N と異なる桁 i」がちょうど
 * 1 つあり、そこで X の数字は N の数字 c_i より小さい（0〜c_i − 1 の c_i 通り）。桁 i より下は自由（base^(残りの桁数) 通り）。
 * だから 0〜N の個数は Σ c_i × base^(L−1−i) + 1（最後の 1 は N 自身）で、これは N + 1 に等しい。
 * 図では、一致の道（太線）を上の桁から 1 段ずつ伸ばし、各段で分かれる未満の枝に、置ける数字と個数のラベルを付ける。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/digit-dp-tight.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("digit-dp-tight", def);
})(function () {
  "use strict";

  var MAX_LEN = 6;
  var KANJI = ["一", "十", "百", "千", "万", "十万"];

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var base = config.base == null ? 10 : config.base;
    if (typeof base !== "number" || !isFinite(base) || Math.floor(base) !== base || base < 2 || base > 10) {
      throw new Error("base は 2〜10 の整数にする");
    }
    var s = config.digits;
    if (typeof s !== "string" || s.length < 1 || s.length > MAX_LEN) {
      throw new Error("digits は 1〜" + MAX_LEN + " 文字の数字の文字列にする");
    }
    var ds = [];
    for (var i = 0; i < s.length; i++) {
      var ch = s.charCodeAt(i) - 48;
      if (ch < 0 || ch > 9) throw new Error("digits は数字だけの文字列にする");
      if (ch >= base) throw new Error("digits の数字は " + base + " 進の数字（0〜" + (base - 1) + "）にする");
      ds.push(ch);
    }
    if (ds.length > 1 && ds[0] === 0) throw new Error("digits の先頭を 0 にしない");
    return { digits: ds, text: s, base: base };
  }

  function pow(b, e) {
    var r = 1;
    for (var i = 0; i < e; i++) r *= b;
    return r;
  }

  // 上から i 番目（0-indexed）の桁の名前
  function placeName(base, L, i) {
    var k = L - 1 - i;
    if (base === 10) return KANJI[k] + "の位";
    return pow(base, k) + " の位";
  }

  function repeat(ch, n) {
    var r = "";
    for (var i = 0; i < n; i++) r += ch;
    return r;
  }

  // 置ける数字の範囲（0〜c−1）の書き方
  function rangeText(c) {
    if (c === 1) return "0";
    if (c === 2) return "0・1";
    return "0〜" + (c - 1);
  }

  function termText(t) {
    return t.free === 1 ? String(t.count) : t.count + " × " + t.free;
  }

  // 各ステップの状態：
  //   phase（start / digit / done）、decided（一致の道が伸びた桁の数。0〜L）、focus（いま決める桁。なければ null）、
  //   branches（これまでに分かれた未満の枝。{pos, count, free, total}。count = 0 の桁も「なし」として入る）、
  //   sum（これまでに数えた個数。done では N 自身の 1 を含む）、caption
  function states(config) {
    var c = validate(config);
    var d = c.digits;
    var b = c.base;
    var L = d.length;
    var value = 0;
    for (var i = 0; i < L; i++) value = value * b + d[i];
    var nText = b === 10 ? "N = " + c.text : "N = " + c.text + "（" + b + " 進。10 進で " + value + "）";

    var out = [];
    var branches = [];
    var sum = 0;
    function snap(phase, decided, focus, caption) {
      out.push({
        phase: phase,
        decided: decided,
        focus: focus,
        branches: branches.map(function (x) { return { pos: x.pos, count: x.count, free: x.free, total: x.total }; }),
        sum: sum,
        caption: caption,
      });
    }

    snap("start", 0, null,
      nText + (b === 10 ? " の " : "の ") + L + " 桁を、上から 1 桁ずつ決める。何も決めていない数は N と一致している（一致の道の始点）とする。" +
        "各桁では、一致の道から「ここで初めて N より小さい数字を置く」未満の枝が分かれる。");

    for (var p = 0; p < L; p++) {
      var cd = d[p];
      var rest = L - 1 - p;
      var free = pow(b, rest);
      var br = { pos: p, count: cd, free: free, total: cd * free };
      branches.push(br);
      sum += br.total;
      var text = placeName(b, L, p) + "を決める。N の数字は " + cd + " である。";
      if (cd === 0) {
        text += "0 より小さい数字はないので、未満になる枝はない。";
      } else {
        text += rangeText(cd) + " を置くと N より小さいことが確定する（未満）。";
        if (rest === 0) {
          text += "残りの桁はないので " + cd + " 個である。";
        } else {
          text += "残りの " + rest + " 桁は " + repeat("0", rest) + "〜" + repeat(String(b - 1), rest) + " の " + free +
            " 通りを自由に選べるので、" + cd + " × " + free + " = " + br.total + " 個になる。";
        }
      }
      text += rest === 0 ? cd + " を置けば一致の道が終わり、N 自身になる。" : cd + " を置けば一致のまま次の桁へ進む。";
      snap("digit", p + 1, p, text);
    }

    sum += 1;
    var terms = branches.filter(function (x) { return x.count > 0; }).map(termText);
    terms.push("1");
    var formula = terms.length === 1 ? "1" : terms.join(" + ") + " = " + sum;
    snap("done", L, null,
      "一致の道の終点は N 自身で、1 個である。合計は " + formula + " で、0 から " + value + " までの整数の個数 " +
        (value + 1) + " と一致する。N より小さい数は「初めて N より小さくなる桁」がちょうど 1 つに決まるので、重複も漏れもない。");
    return out;
  }

  // 描画の寸法：桁 i の列は x = M + i × W から幅 W。一致の道のノード i（i 桁を決めた後）は列の左の境 x = M + i × W に置く
  var M = 46; // 左の余白（行の名前「一致」「未満」を書く）
  var W = 96;
  var RIGHT = 84; // N 自身の箱を置く右の余白
  var CELL = 36;
  var Y_HEAD = 10; // 位の名前
  var Y_DIGIT = 22; // N の数字の枠の上端
  var Y_TIGHT = 100; // 一致の道
  var Y_BOX = 140; // 未満の枝の箱の上端
  var BOX_W = 84;
  var BOX_H = 58;
  var HEIGHT = 262;

  function viewBox(config) {
    return "0 0 " + (M + config.digits.length * W + RIGHT) + " " + HEIGHT;
  }

  // 太さ w の線分を細い多角形で描く（色は塗りの class で付ける）
  function seg(h, x1, y1, x2, y2, w, cls) {
    var dx = x2 - x1, dy = y2 - y1;
    var len = Math.sqrt(dx * dx + dy * dy) || 1;
    var nx = (-dy / len) * (w / 2), ny = (dx / len) * (w / 2);
    return h("path", {
      d: "M" + (x1 + nx) + " " + (y1 + ny) + "L" + (x2 + nx) + " " + (y2 + ny) + "L" + (x2 - nx) + " " + (y2 - ny) +
        "L" + (x1 - nx) + " " + (y1 - ny) + "Z",
      class: cls,
    });
  }

  function render(svg, s, config, h) {
    var text = config.digits;
    var L = text.length;
    var b = config.base == null ? 10 : config.base;
    var width = M + L * W + RIGHT;
    function nodeX(i) { return M + i * W; }
    function colX(i) { return M + i * W + W / 2; }
    var done = s.phase === "done";

    // 行の名前（色だけに頼らず、どちらの行が一致か未満かを文字で示す）
    svg.appendChild(h("text", { x: M / 2 - 4, y: Y_DIGIT + CELL / 2, class: "kp-v-text is-sub" }, "N"));
    svg.appendChild(h("text", { x: M / 2 - 4, y: Y_TIGHT, class: "kp-v-ptr is-focus" }, "一致"));
    svg.appendChild(h("text", { x: M / 2 - 4, y: Y_BOX + BOX_H / 2, class: "kp-v-ptr is-b" }, "未満"));

    // 位の名前と N の数字
    for (var i = 0; i < L; i++) {
      var cls = ["kp-v-cell"];
      if (i < s.decided) cls.push("is-yes");
      if (s.focus === i) cls.push("is-focus");
      svg.appendChild(h("text", { x: colX(i), y: Y_HEAD, class: "kp-v-text is-sub" }, placeName(b, L, i)));
      svg.appendChild(h("rect", { x: colX(i) - CELL / 2, y: Y_DIGIT, width: CELL, height: CELL, rx: 6, class: cls.join(" ") }));
      svg.appendChild(h("text", { x: colX(i), y: Y_DIGIT + CELL / 2, class: "kp-v-text" }, text[i]));
    }

    // 一致の道：伸びた所は太線、まだの所は細い破線（短い線分を並べる）
    for (var j = 0; j < L; j++) {
      if (j < s.decided) {
        svg.appendChild(seg(h, nodeX(j), Y_TIGHT, nodeX(j + 1), Y_TIGHT, 6, "kp-v-mark is-focus"));
        svg.appendChild(h("text", { x: colX(j), y: Y_TIGHT - 13, class: "kp-v-ptr is-focus" }, text[j] + " を置く"));
      } else {
        for (var q = 0; q < 6; q++) {
          var sx = nodeX(j) + 10 + q * ((W - 20) / 6);
          svg.appendChild(seg(h, sx, Y_TIGHT, sx + (W - 20) / 12, Y_TIGHT, 1.5, "kp-v-mark"));
        }
      }
    }

    // 未満の枝
    s.branches.forEach(function (br) {
      var bx = colX(br.pos);
      var focus = s.focus === br.pos;
      var x0 = bx - BOX_W / 2;
      var empty = br.count === 0;
      if (!empty) svg.appendChild(seg(h, nodeX(br.pos), Y_TIGHT, bx, Y_BOX, focus ? 3 : 2, focus ? "kp-v-mark is-b" : "kp-v-mark"));
      var cls = ["kp-v-cell"];
      // 枝なしの箱は点線（is-sentinel）。ただし、いまの桁のときは is-sentinel が is-focus の枠の色を消すので、is-no で塗って太い枠を見せる
      if (empty) cls.push(focus ? "is-no" : "is-sentinel");
      else cls.push("is-yes");
      if (focus) cls.push("is-focus");
      svg.appendChild(h("rect", { x: x0, y: Y_BOX, width: BOX_W, height: BOX_H, rx: 6, class: cls.join(" ") }));
      if (empty) {
        svg.appendChild(h("text", { x: bx, y: Y_BOX + BOX_H / 2, class: "kp-v-text is-dim" }, "枝なし"));
        return;
      }
      var rest = L - 1 - br.pos;
      svg.appendChild(h("text", { x: bx, y: Y_BOX + 14, class: "kp-v-text" }, rangeText(br.count)));
      svg.appendChild(h("text", { x: bx, y: Y_BOX + 32, class: "kp-v-text is-sub" }, rest === 0 ? "残りなし" : "残り " + rest + " 桁自由"));
      svg.appendChild(h("text", { x: bx, y: Y_BOX + 48, class: "kp-v-text is-sub" }, br.free === 1 ? br.count + " 個" : termText(br)));
      svg.appendChild(h("text", { x: bx, y: Y_BOX + BOX_H + 14, class: "kp-v-ptr is-b" }, "= " + br.total));
    });

    // 一致の道のノード（伸びた所まで塗る）
    for (var k = 0; k <= L; k++) {
      var on = k <= s.decided;
      svg.appendChild(h("circle", { cx: nodeX(k), cy: Y_TIGHT, r: on ? 7 : 6, class: on ? "kp-v-cell is-answer" : "kp-v-cell is-sentinel" }));
    }

    // N 自身（一致の道の終点）
    var ex = nodeX(L) + 14;
    var ecls = ["kp-v-cell"];
    if (done) ecls.push("is-answer", "is-focus");
    else ecls.push("is-sentinel");
    svg.appendChild(h("rect", { x: ex, y: Y_TIGHT - 20, width: RIGHT - 20, height: 40, rx: 6, class: ecls.join(" ") }));
    svg.appendChild(h("text", { x: ex + (RIGHT - 20) / 2, y: Y_TIGHT - 8, class: done ? "kp-v-text is-on-answer" : "kp-v-text is-dim" }, "N 自身"));
    svg.appendChild(h("text", { x: ex + (RIGHT - 20) / 2, y: Y_TIGHT + 9, class: done ? "kp-v-text is-on-answer" : "kp-v-text is-dim" }, done ? "1 個" : "—"));

    // これまでの合計
    var label;
    if (s.phase === "start") label = "数えた個数：0";
    else if (done) label = "合計 " + s.sum + " 個（0〜" + (s.sum - 1) + " の個数）";
    else label = "未満の枝の合計：" + s.sum + " 個";
    svg.appendChild(h("text", { x: width / 2, y: HEIGHT - 12, class: done ? "kp-v-ptr is-focus" : "kp-v-ptr" }, label));
  }

  return {
    title: "桁 DP で、N と一致したままの道が 1 本だけ伸び、各桁で未満の枝が分かれる様子",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

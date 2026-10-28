/*
 * 動く図：包除原理で 3 つの集合の大きさを足し引きし、ベン図の各領域を数えた回数が打ち消し合う様子（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="inclusion-exclusion-venn" data-config='{"n": 30, "divisors": [2, 3, 5]}'></div>
 * config：
 *   n        … 1〜n の整数を数える（1〜100）
 *   divisors … 異なる 3 つの整数（2〜100）。円 i を「divisors[i] の倍数」の集合とし、左上・右上・下に置く
 *
 * ステップは包除の和 Σ(−1)^|S| N(S)（N(S) = ⌊n / lcm(S)⌋）の |S| = 0, 1, 2, 3 の 4 段：
 * (0) 全体 n を数える → (1) 各集合の大きさを引く → (2) 2 つの共通部分を足す → (3) 3 つの共通部分を引く。
 * 各段で、ベン図の 8 領域それぞれに「その時点で数えた回数」と、その領域に入る数を描く。ちょうど t 個の集合に入る数を
 * |S| ≤ k の項までで数えた回数は Σ_{j=0}^{k} (−1)^j C(t, j) で、最後の段ではどれにも入らない外側だけが 1 回、
 * ほかの領域は 0 回になる。caption には、その段で足し引きした値と累計を書く。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/inclusion-exclusion-venn.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("inclusion-exclusion-venn", def);
})(function () {
  "use strict";

  var MAX_N = 100;
  var MAX_D = 100;

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var d = config.divisors;
    if (!Array.isArray(d) || d.length !== 3) throw new Error("divisors は 3 つの整数の配列にする");
    for (var i = 0; i < 3; i++) {
      if (!isInt(d[i]) || d[i] < 2 || d[i] > MAX_D) throw new Error("divisors の各要素は 2〜" + MAX_D + " の整数にする");
    }
    if (d[0] === d[1] || d[0] === d[2] || d[1] === d[2]) throw new Error("divisors の 3 つの数は異なる値にする");
    return { n: n, divisors: d.slice() };
  }

  function gcd(a, b) {
    while (b) { var t = a % b; a = b; b = t; }
    return a;
  }
  function lcm(a, b) { return (a / gcd(a, b)) * b; }
  function bits(m) { return (m & 1) + ((m >> 1) & 1) + ((m >> 2) & 1); }
  var BINOM = [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1]];
  // ちょうど t 個の集合に入る数を、|S| ≤ k の項までで数えた回数 Σ_{j=0}^{min(t, k)} (−1)^j C(t, j)
  function timesAt(t, k) {
    var c = 0;
    for (var j = 0; j <= Math.min(t, k); j++) c += (j % 2 ? -1 : 1) * BINOM[t][j];
    return c;
  }
  function num(v) { return v < 0 ? "−" + -v : String(v); } // 負の数は U+2212 で書く

  // |S| ごとの条件の集合 S（円の番号の列）
  var SUBSETS = [[[]], [[0], [1], [2]], [[0, 1], [0, 2], [1, 2]], [[0, 1, 2]]];
  var TITLES = [
    "|S| = 0：全体を数える",
    "|S| = 1：1 つの集合の大きさを引く",
    "|S| = 2：2 つの共通部分を足す",
    "|S| = 3：3 つの共通部分を引く",
  ];

  // ---------- 説明文 ----------
  function listText(xs) { return xs.join("・"); }
  // 「3 つすべてに入る 30 は」「3 つすべてに入る 4 個の数は」（数で終わるときだけ助詞の前に空白を置く）
  function allThreeWa(e3) {
    return "3 つすべてに入る " + (e3.length <= 3 ? listText(e3) + " は" : e3.length + " 個の数は");
  }
  // その段の項：「2 の倍数は 15 個、3 の倍数は 10 個、5 の倍数は 6 個」。
  // 最小公倍数が同じ項があるときは「4・8 の公倍数（8 の倍数）」と書き分ける
  function termsText(terms, dv) {
    var l = terms.map(function (t) { return t.lcm; });
    var dup = l.some(function (v, i) { return l.indexOf(v) !== i; });
    return terms.map(function (t) {
      var name = dup
        ? t.sets.map(function (i) { return dv[i]; }).join("・") + " の公倍数（" + t.lcm + " の倍数）"
        : t.lcm + " の倍数";
      return name + "は " + t.value + " 個";
    }).join("、");
  }

  // E[t]：ちょうど t 個の集合に入る数の列
  function caption(k, c, terms, prevTotal, total, E) {
    var n = c.n;
    if (k === 0) {
      return "1〜" + n + " の整数のうち、" + listText(c.divisors) + " のどれでも割り切れないものを数える。まず全体の " + n +
        " 個を 1 回ずつ数え、累計は " + n + " になる。各領域の「○ 回」は、その領域の数をここまでに数えた回数" +
        "（足した回数 − 引いた回数）である。";
    }
    var op = k % 2 ? " − " : " + ";
    var calc = num(prevTotal) + op + terms.map(function (t) { return t.value; }).join(op) + " = " + num(total);
    var head = ["", "1 つの集合の大きさを引く。", "2 つの共通部分を足す。", "3 つの共通部分を引く。"][k] +
      termsText(terms, c.divisors) + "なので、累計は " + calc + " になる。";
    var e1 = E[1].length > 0, e2 = E[2].length > 0, e3 = E[3].length > 0;
    var body;
    if (k === 1) {
      var over = [];
      if (e2) over.push("2 つの集合に入る数は 2 回引かれて −1 回");
      if (e3) over.push(allThreeWa(E[3]) + " 3 回引かれて −2 回");
      if (e1 && over.length) body = "1 つの集合だけに入る数は 0 回になるが、" + over.join("、") + "になり、引きすぎている。";
      else if (e1) body = "1 つの集合だけに入る数は 0 回になる。";
      else body = over.length ? over.join("、") + "になり、引きすぎている。" : "";
    } else if (k === 2) {
      var much = allThreeWa(E[3]) + " 3 回足されて 1 回になり、まだ 1 回多い（足しすぎ）。";
      if (e2 && e3) body = "2 つの集合に入る数は 0 回に戻るが、" + much;
      else if (e2) body = "2 つの集合に入る数は 0 回に戻る。";
      else if (e3) body = much;
      else body = "2 つ以上の集合に入る数はないので、どの数の回数も変わらない。";
    } else {
      body = e3
        ? (E[3].length <= 3 ? listText(E[3]) + " も" : "3 つすべてに入る数も") + " 0 回になり、"
        : "3 つすべてに入る数はないので回数は変わらず、";
      // 1 はどの数でも割り切れないので、外側はいつも空でない
      var e0 = E[0];
      body += e0.length === 1
        ? "どれにも入らない " + e0[0] + " だけが 1 回残る。"
        : "どれにも入らない " + (e0.length <= 12 ? listText(e0) + " の " : "") + e0.length + " 個だけが 1 回残る。";
      body += "答えは " + num(total) + " である。";
    }
    return head + body;
  }

  // ---------- 状態の列 ----------
  // 各状態：stage（|S| = 0〜3）、n、divisors、sign（その段の符号）、terms（その段の項 {sets, lcm, value}）、
  //   groups（式に書く段ごとの値 {sign, values}。0〜stage 段）、delta（その段で足し引きした値）、prevTotal・total（累計）、
  //   regions（領域 mask = 0〜7 の {mask, t, members, times, prev}。mask の i ビットが円 i に入ること、t は入る円の数、
  //   times はその段までに数えた回数、prev は前の段の回数）、title、caption
  function states(config) {
    var c = validate(config);
    var n = c.n, dv = c.divisors;
    var members = [[], [], [], [], [], [], [], []];
    for (var x = 1; x <= n; x++) {
      var m = 0;
      for (var i = 0; i < 3; i++) if (x % dv[i] === 0) m |= 1 << i;
      members[m].push(x);
    }
    var E = [[], [], [], []];
    for (m = 0; m < 8; m++) E[bits(m)] = E[bits(m)].concat(members[m]);
    E.forEach(function (xs) { xs.sort(function (a, b) { return a - b; }); });

    var out = [];
    var total = 0;
    var groups = [];
    for (var k = 0; k <= 3; k++) {
      var sign = k % 2 ? -1 : 1;
      var terms = SUBSETS[k].map(function (S) {
        var l = S.reduce(function (a, i) { return lcm(a, dv[i]); }, 1);
        return { sets: S.slice(), lcm: l, value: Math.floor(n / l) };
      });
      var delta = sign * terms.reduce(function (a, t) { return a + t.value; }, 0) || 0; // −0 にしない
      var prevTotal = total;
      total += delta;
      groups.push({ sign: sign, values: terms.map(function (t) { return t.value; }) });
      var regions = [];
      for (m = 0; m < 8; m++) {
        var t = bits(m);
        regions.push({ mask: m, t: t, members: members[m].slice(), times: timesAt(t, k), prev: k ? timesAt(t, k - 1) : null });
      }
      out.push({
        stage: k, n: n, divisors: dv.slice(), sign: sign, terms: terms,
        groups: groups.map(function (g) { return { sign: g.sign, values: g.values.slice() }; }),
        delta: delta, prevTotal: prevTotal, total: total, regions: regions, title: TITLES[k],
        caption: caption(k, c, terms, prevTotal, total, E),
      });
    }
    return out;
  }

  // ---------- 描画の寸法 ----------
  // 3 つの円（半径 R）の中心は 1 辺 DIST の正三角形に置く。円 0 が左上、円 1 が右上、円 2 が下
  var W = 400;
  var R = 96;
  var DIST = 100;
  var C = [[200 - DIST / 2, 170], [200 + DIST / 2, 170], [200, 170 + (DIST * Math.sqrt(3)) / 2]];
  var BOX = { l: 6, t: 48, r: 394, b: Math.round(C[2][1] + R + 6) }; // 全体（1〜n）の長方形
  var HEIGHT = BOX.b + 5;
  var COUNT_PX = 15; // 回数の文字
  var NUM_PX = 13; // 領域の数・ラベルの文字（360px の幅で 10px ほどになる）
  var DASH = [null, "8 4", "2 4"]; // 円の線の種類（実線・破線・点線）。色だけに頼らず円を見分ける

  // 領域ごとの文字の置き場：{数の行の数: [中央の x, 回数の行の上端の y, 各行の幅の上限 [回数, 数の 1 行目, 2 行目]]}。
  // 行の帯（回数 18、数 16 の高さ）が上下左右に 2 の余白を取っても領域の内側に収まる位置と幅を、
  // この寸法（R = 96、DIST = 100）で求めた。mask は円 i に入るとき i ビット目が 1
  var SLOT = [
    { 1: [76, 316, [90, 125]], 2: [68, 299, [85, 107, 116]] }, // 0：外側（左下の隅）
    { 1: [106, 122, [71, 89]], 2: [106, 114, [61, 82, 92]] }, // 1：円 0 だけ
    { 1: [294, 122, [71, 89]], 2: [294, 114, [61, 82, 92]] }, // 2：円 1 だけ
    { 1: [200, 120, [57, 75]] }, // 3：円 0 と円 1
    { 1: [200, 270, [176, 160]], 2: [200, 268, [177, 163, 140]] }, // 4：円 2 だけ
    { 1: [142, 219, [44, 67]] }, // 5：円 0 と円 2
    { 1: [258, 219, [44, 67]] }, // 6：円 1 と円 2
    { 1: [200, 169, [64, 74]], 2: [200, 168, [59, 75, 59]] }, // 7：3 つすべて
  ];

  // 文字の幅の見積もり（数字・英字 0.6、空白 0.3、全角・記号 1 文字分）
  function textW(s, px) {
    var w = 0;
    for (var i = 0; i < s.length; i++) {
      var ch = s.charCodeAt(i);
      w += ch === 32 || ch === 0xa0 ? 0.3 : ch < 0x2000 ? 0.6 : 1;
    }
    return w * px;
  }

  // 領域の数を、置き場の行の幅に収まるように行へ分ける。収まらなければ「12 個」と個数だけを書く
  function layout(m, members) {
    var slot = SLOT[m];
    if (members.length === 0) return { at: slot[1], lines: ["なし"], list: false };
    var ks = Object.keys(slot).map(Number);
    for (var a = 0; a < ks.length; a++) {
      var k = ks[a];
      if (members.length < k) continue;
      var parts = [], at = 0;
      for (var i = 0; i < k; i++) {
        var len = Math.ceil((members.length - at) / (k - i));
        parts.push(members.slice(at, at + len).join(" "));
        at += len;
      }
      var ws = slot[k][2];
      if (parts.every(function (p, j) { return textW(p, NUM_PX) <= ws[j + 1] - 2; })) return { at: slot[k], lines: parts, list: true };
    }
    return { at: slot[1], lines: [members.length + " 個"], list: false };
  }

  // ---------- 円の交点と領域の形 ----------
  function inside(p, k) {
    var dx = p[0] - C[k][0], dy = p[1] - C[k][1];
    return dx * dx + dy * dy < R * R;
  }
  // 円 i と円 j の 2 つの交点：inn は 3 つ目の円の内側、out は外側
  var CROSS = {};
  [[0, 1, 2], [0, 2, 1], [1, 2, 0]].forEach(function (q) {
    var a = C[q[0]], b = C[q[1]];
    var dx = b[0] - a[0], dy = b[1] - a[1], len = Math.sqrt(dx * dx + dy * dy);
    var hh = Math.sqrt(R * R - (len / 2) * (len / 2));
    var mx = (a[0] + b[0]) / 2, my = (a[1] + b[1]) / 2;
    var p1 = [mx - (dy / len) * hh, my + (dx / len) * hh], p2 = [mx + (dy / len) * hh, my - (dx / len) * hh];
    var in1 = inside(p1, q[2]);
    CROSS[q[0] + "" + q[1]] = { inn: in1 ? p1 : p2, out: in1 ? p2 : p1 };
  });
  function cross(i, j) { return CROSS[Math.min(i, j) + "" + Math.max(i, j)]; }

  function f1(v) { return Math.round(v * 10) / 10; }
  function pt(p) { return f1(p[0]) + " " + f1(p[1]); }
  // 円 i の上を P から Q へ進む弧（SVG の A コマンド）。2 つの向きのうち、弧の中点が want を満たすほうを選ぶ。
  // want[j] は、弧の点が円 j の内側（true）か外側（false）か。null なら問わない
  function arc(i, P, Q, want) {
    var c = C[i];
    var a1 = Math.atan2(P[1] - c[1], P[0] - c[0]);
    var a2 = Math.atan2(Q[1] - c[1], Q[0] - c[0]);
    var pos = a2 - a1;
    while (pos <= 0) pos += 2 * Math.PI;
    var am = a1 + pos / 2, mid = [c[0] + R * Math.cos(am), c[1] + R * Math.sin(am)];
    var ok = want.every(function (w, j) { return w == null || inside(mid, j) === w; });
    var delta = ok ? pos : pos - 2 * Math.PI;
    return "A" + R + " " + R + " 0 " + (Math.abs(delta) > Math.PI ? 1 : 0) + " " + (delta > 0 ? 1 : 0) + " " + pt(Q);
  }
  // 領域 mask の境界。境界の弧は、ほかの 2 つの円について領域と同じ側にある
  function regionPath(m) {
    function along(i, P, Q) {
      var want = [0, 1, 2].map(function (j) { return j === i ? null : !!(m & (1 << j)); });
      return arc(i, P, Q, want);
    }
    var t = bits(m);
    if (t === 3) {
      var p01 = cross(0, 1).inn, p12 = cross(1, 2).inn, p02 = cross(0, 2).inn;
      return "M" + pt(p01) + along(1, p01, p12) + along(2, p12, p02) + along(0, p02, p01) + "Z";
    }
    if (t === 0) {
      // 全体の長方形から 3 つの円の和集合を除く（fill-rule: evenodd）
      var u01 = cross(0, 1).out, u02 = cross(0, 2).out, u12 = cross(1, 2).out;
      return "M" + BOX.l + " " + BOX.t + "H" + BOX.r + "V" + BOX.b + "H" + BOX.l + "Z" +
        "M" + pt(u01) + along(0, u01, u02) + along(2, u02, u12) + along(1, u12, u01) + "Z";
    }
    var ins = [0, 1, 2].filter(function (j) { return m & (1 << j); });
    var outs = [0, 1, 2].filter(function (j) { return !(m & (1 << j)); });
    var a, b, c, i, j, k;
    if (t === 2) {
      // 円 i と円 j だけ：外側の交点 → 円 i → (i, k) の内側の交点 → 円 k → (j, k) の内側の交点 → 円 j
      i = ins[0]; j = ins[1]; k = outs[0];
      a = cross(i, j).out; b = cross(i, k).inn; c = cross(j, k).inn;
    } else {
      // 円 i だけ：(i, j) の外側の交点 → 円 i の外回り → (i, k) の外側の交点 → 円 k → (j, k) の内側の交点 → 円 j
      i = ins[0]; j = outs[0]; k = outs[1];
      a = cross(i, j).out; b = cross(i, k).out; c = cross(j, k).inn;
    }
    return "M" + pt(a) + along(i, a, b) + along(k, b, c) + along(j, c, a) + "Z";
  }
  // 2 つの円の共通部分（レンズの形）の輪郭
  function lensPath(i, j) {
    var a = cross(i, j).out, b = cross(i, j).inn;
    var wi = [null, null, null], wj = [null, null, null];
    wi[j] = true;
    wj[i] = true;
    return "M" + pt(a) + arc(i, a, b, wi) + arc(j, b, a, wj) + "Z";
  }

  function viewBox() {
    return "0 0 " + W + " " + HEIGHT;
  }

  var OUTLINE = "fill:none";
  function dashStyle(i, base) {
    return base + (DASH[i] ? ";stroke-dasharray:" + DASH[i] : "");
  }

  function render(svg, s, config, h) {
    var k = s.stage;
    var last = k === 3;

    // 領域の塗り：1 回は色付き、負の回数は灰色、0 回は塗らない（回数は文字でも書く）
    s.regions.forEach(function (rg) {
      if (rg.times === 0) return;
      svg.appendChild(h("path", {
        d: regionPath(rg.mask), "fill-rule": "evenodd", class: rg.times > 0 ? "kp-v-cell is-yes" : "kp-v-cell is-no",
        style: "stroke:none", "data-part": "fill", "data-region": rg.mask,
      }));
    });

    // 全体の長方形と 3 つの円
    svg.appendChild(h("rect", {
      x: BOX.l, y: BOX.t, width: BOX.r - BOX.l, height: BOX.b - BOX.t, class: "kp-v-cell", style: OUTLINE, "data-part": "box",
    }));
    C.forEach(function (c, i) {
      svg.appendChild(h("circle", { cx: c[0], cy: c[1], r: R, class: "kp-v-cell", style: dashStyle(i, OUTLINE), "data-set": i }));
    });

    // この段で足し引きする項の形を太線で囲む（|S| = 0 は全体、1 は円、2 は 2 つの共通部分、3 は 3 つの共通部分）
    function term(tag, attrs) {
      attrs.class = "kp-v-cell is-focus";
      attrs["data-part"] = "term";
      svg.appendChild(h(tag, attrs));
    }
    if (k === 0) {
      term("rect", { x: BOX.l, y: BOX.t, width: BOX.r - BOX.l, height: BOX.b - BOX.t, style: OUTLINE });
    } else if (k === 1) {
      C.forEach(function (c, i) { term("circle", { cx: c[0], cy: c[1], r: R, style: dashStyle(i, OUTLINE) }); });
    } else if (k === 2) {
      [[0, 1], [0, 2], [1, 2]].forEach(function (p) { term("path", { d: lensPath(p[0], p[1]), style: OUTLINE }); });
    } else {
      term("path", { d: regionPath(7), style: OUTLINE });
    }

    // ラベル：全体（左上の隅）と、各円（線の種類の見本つき。円 0・1 は円の上、円 2 は右下）
    var LY = BOX.t + 13;
    svg.appendChild(h("text", {
      x: BOX.l + 6, y: LY, class: "kp-v-text is-sub", style: "font-size:" + NUM_PX + "px;text-anchor:start", "data-part": "label",
    }, "1〜" + s.n + " の整数"));
    s.divisors.forEach(function (d, i) {
      var text = d + " の倍数";
      var w = 23 + textW(text, NUM_PX);
      var x0 = i === 2 ? 290 : C[i][0] - w / 2;
      var y = i === 2 ? BOX.b - 17 : LY;
      svg.appendChild(h("line", {
        x1: x0, y1: y, x2: x0 + 18, y2: y, class: "kp-v-cell", style: dashStyle(i, "stroke-width:2"), "data-part": "sample",
      }));
      svg.appendChild(h("text", {
        x: x0 + 23, y: y, class: "kp-v-text is-sub", style: "font-size:" + NUM_PX + "px;text-anchor:start", "data-part": "label",
      }, text));
    });

    // 各領域：回数（太字）と、その領域に入る数
    s.regions.forEach(function (rg) {
      var m = rg.mask;
      var lay = layout(m, rg.members);
      var X = lay.at[0], Y = lay.at[1];
      var changed = rg.t >= k; // この段の項（|S| = k）に含まれ、回数が変わった（C(t, k) ≠ 0）
      var answer = last && m === 0;
      var ccls = answer ? "kp-v-ptr is-focus" : changed ? "kp-v-ptr is-b" : last ? "kp-v-text is-dim" : "kp-v-text";
      var label = (m === 0 ? "外側 " : "") + num(rg.times) + " 回";
      if (answer) {
        // 最後の段：1 回残る外側の数を枠で囲む
        var bw = Math.max(textW(label, COUNT_PX), Math.max.apply(null, lay.lines.map(function (l) { return textW(l, NUM_PX); })));
        var minSlot = Math.min.apply(null, lay.at[2].slice(0, lay.lines.length + 1));
        bw = Math.min(bw + 10, minSlot + 2);
        svg.appendChild(h("rect", {
          x: X - bw / 2, y: Y - 1, width: bw, height: 18 + 16 * lay.lines.length + 2, rx: 6,
          class: "kp-v-cell is-focus", style: OUTLINE, "data-part": "answer",
        }));
      }
      svg.appendChild(h("text", {
        x: X, y: Y + 9, class: ccls, style: "font-size:" + COUNT_PX + "px;font-weight:700",
        "data-part": "times", "data-region": m,
      }, label));
      lay.lines.forEach(function (line, j) {
        svg.appendChild(h("text", {
          x: X, y: Y + 26 + 16 * j, class: lay.list ? "kp-v-text" : "kp-v-text is-sub",
          style: "font-size:" + NUM_PX + "px" + (answer ? ";font-weight:700" : ""),
          "data-part": lay.list ? "members" : "summary", "data-region": m,
        }, line));
      });
    });

    // 見出し：段の名前と、ここまでの式（この段の項を色付きの太字に）と累計
    svg.appendChild(h("text", { x: W / 2, y: 13, class: "kp-v-text", style: "font-size:15px;font-weight:700", "data-part": "title" }, s.title));
    var f = h("text", { x: W / 2, y: 34, class: "kp-v-text", style: "font-size:15px", "data-part": "formula" });
    s.groups.forEach(function (g, j) {
      var body = g.values.length > 1 ? "(" + g.values.join(" + ") + ")" : String(g.values[0]);
      var text = j === 0 ? body : "\u00a0" + (g.sign < 0 ? "−" : "+") + " " + body;
      f.appendChild(h("tspan", j === k ? { class: "kp-v-ptr is-b", style: "font-size:15px" } : null, text));
    });
    if (k > 0) f.appendChild(h("tspan", { style: "font-weight:700" }, "\u00a0= " + num(s.total)));
    svg.appendChild(f);
  }

  return {
    title: "包除原理で 3 つの集合を足し引きし、各領域を数えた回数が打ち消し合う様子",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

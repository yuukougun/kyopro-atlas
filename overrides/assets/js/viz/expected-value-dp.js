/*
 * 動く図：期待値 DP を終状態から後ろ向きに埋める（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="expected-value-dp"
 *        data-config='{"hp": {"n": 4, "p": "1/2"}, "sugoroku": {"a": [3, 2, 1]}}'></div>
 * config（hp と sugoroku の少なくとも一方。両方あれば hp → sugoroku の順に見せる）：
 *   hp.n       … 最初の HP（1〜7）
 *   hp.p       … 2 のダメージを与える確率。"a/b" の文字列（0 ≤ a ≤ b ≤ 100）か、0〜1 の数（小数 6 桁まで）
 *   sugoroku.a … A_0, …, A_{N−2}（1〜6 個の整数）。マス 0〜N−1 のすごろくで、マス i では 0〜A_i の目が等確率で出て、
 *                出た目だけ進む。1 ≤ A_i かつ i + A_i ≤ N − 1（ゴールを越える目はない）
 *
 * 前半（hp）：E[h] = 1 + p E[max(h − 2, 0)] + (1 − p) E[h − 1]、E[0] = 0 を HP の小さい順に 1 状態ずつ埋める。
 * 後半（sugoroku）：0 の目は同じマスにとどまる（自己ループ）。マスごとに「移項前の式」と「移項後の式と値」の
 * 2 ステップで E[i] = (A_i + 1 + Σ_{k=1}^{A_i} E[i + k]) / A_i を後ろから埋める。
 * 値は BigInt の分数で正確に計算する。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/expected-value-dp.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("expected-value-dp", def);
})(function () {
  "use strict";

  var MAX_HP = 7;
  var MAX_A = 6; // マスの数 N は 7 まで
  var MAX_DEN = 100;

  // ---------- 分数（BigInt。分母はいつも正で、約分してある） ----------
  function gcd(a, b) {
    if (a < 0n) a = -a;
    if (b < 0n) b = -b;
    while (b) { var t = a % b; a = b; b = t; }
    return a;
  }
  function fr(n, d) {
    n = BigInt(n);
    d = d == null ? 1n : BigInt(d);
    if (d === 0n) throw new Error("0 で割った");
    if (d < 0n) { n = -n; d = -d; }
    var g = gcd(n, d) || 1n;
    return { n: n / g, d: d / g };
  }
  function add(a, b) { return fr(a.n * b.d + b.n * a.d, a.d * b.d); }
  function sub(a, b) { return fr(a.n * b.d - b.n * a.d, a.d * b.d); }
  function mul(a, b) { return fr(a.n * b.n, a.d * b.d); }
  function div(a, b) { return fr(a.n * b.d, a.d * b.n); }
  function isZero(a) { return a.n === 0n; }
  function toNum(a) { return Number(a.n) / Number(a.d); }
  function fracText(a) {
    var s = a.d === 1n ? String(a.n) : a.n + "/" + a.d;
    return s.charAt(0) === "-" ? "−" + s.slice(1) : s;
  }
  // 小数で書き切れる（分母が 2 と 5 だけで、小数 4 桁以内）なら小数の文字列、そうでなければ null
  function decimalText(a) {
    var d = a.d, k = 0;
    while (d % 2n === 0n) d /= 2n;
    while (d % 5n === 0n) d /= 5n;
    if (d !== 1n) return null;
    for (k = 0; k <= 4; k++) {
      var scale = 10n ** BigInt(k);
      if ((a.n * scale) % a.d === 0n) {
        var v = (a.n * scale) / a.d;
        if (k === 0) return String(v);
        var s = String(v).padStart(k + 1, "0");
        return s.slice(0, -k) + "." + s.slice(-k);
      }
    }
    return null;
  }
  // 図の箱の中：小数で書けるなら小数、そうでなければ分数。箱（幅 54）に入らない長さ（6 文字を超える）なら
  // 小数 2 桁の近似（≈5.44）にし、分数は説明文だけに書く
  var SHORT_MAX = 6;
  function shortText(a) {
    var s = decimalText(a) || fracText(a);
    return s.length <= SHORT_MAX ? s : "≈" + toNum(a).toFixed(2);
  }
  // 説明文の中：「9/4 = 2.25」「17/6 ≈ 2.833」「1」
  function longText(a) {
    if (a.d === 1n) return fracText(a);
    var dec = decimalText(a);
    return fracText(a) + (dec ? " = " + dec : " ≈ " + toNum(a).toFixed(3));
  }

  function parseProb(p) {
    if (typeof p === "string") {
      var m = /^\s*(\d+)\s*\/\s*(\d+)\s*$/.exec(p);
      if (!m) throw new Error('hp.p は "1/2" の形の文字列か、0〜1 の数にする');
      var a = Number(m[1]), b = Number(m[2]);
      if (b < 1 || b > MAX_DEN || a > b) throw new Error("hp.p の分数は 0 ≤ 分子 ≤ 分母 ≤ " + MAX_DEN + " にする");
      return fr(a, b);
    }
    if (typeof p === "number" && isFinite(p) && p >= 0 && p <= 1) {
      var scaled = Math.round(p * 1e6);
      if (Math.abs(scaled - p * 1e6) > 1e-6) throw new Error("hp.p を数で書くなら小数 6 桁までにする");
      return fr(scaled, 1000000);
    }
    throw new Error('hp.p は "1/2" の形の文字列か、0〜1 の数にする');
  }

  function isInt(v) {
    return typeof v === "number" && isFinite(v) && Math.floor(v) === v;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var out = { hp: null, sugoroku: null };
    if (config.hp != null) {
      var hp = config.hp;
      if (typeof hp !== "object") throw new Error("hp は {\"n\": …, \"p\": …} の形にする");
      if (!isInt(hp.n) || hp.n < 1 || hp.n > MAX_HP) throw new Error("hp.n は 1〜" + MAX_HP + " の整数にする");
      out.hp = { n: hp.n, p: parseProb(hp.p) };
    }
    if (config.sugoroku != null) {
      var a = config.sugoroku && config.sugoroku.a;
      if (!Array.isArray(a) || a.length < 1 || a.length > MAX_A) {
        throw new Error("sugoroku.a は 1〜" + MAX_A + " 個の整数の配列にする");
      }
      var goal = a.length; // マス N − 1
      for (var i = 0; i < a.length; i++) {
        if (!isInt(a[i]) || a[i] < 1 || i + a[i] > goal) {
          throw new Error("sugoroku.a の各要素は 1 ≤ A_i かつ i + A_i ≤ " + goal + "（ゴールのマス）の整数にする");
        }
      }
      out.sugoroku = { a: a.slice() };
    }
    if (!out.hp && !out.sugoroku) throw new Error("hp と sugoroku の少なくとも一方を書く");
    return out;
  }

  // ---------- 状態の列 ----------
  // 各状態：part（"hp" / "sugoroku"）、phase（start / terminal / fill / before / after / done）、
  //   e（各状態の期待値。まだ決まっていなければ null。数）、eText（同じく分数の文字列）、eShort（箱に書く文字列）、
  //   focus（いま式を当てはめている状態の番号。なければ null）、caption
  //   part が hp なら状態の番号は HP（0〜n）、sugoroku ならマスの番号（0〜N−1）
  function states(config) {
    var c = validate(config);
    var out = [];
    var ONE = fr(1);

    function snap(part, phase, e, focus, caption) {
      out.push({
        part: part,
        phase: phase,
        e: e.map(function (v) { return v ? toNum(v) : null; }),
        eText: e.map(function (v) { return v ? fracText(v) : null; }),
        eShort: e.map(function (v) { return v ? shortText(v) : null; }),
        focus: focus,
        caption: caption,
      });
    }

    if (c.hp) {
      var n = c.hp.n, p = c.hp.p, q = sub(ONE, p);
      var pt = fracText(p), qt = fracText(q);
      var e = new Array(n + 1).fill(null);
      snap("hp", "start", e, null,
        "HP " + n + " の相手に、確率 p = " + pt + " で 2、確率 1 − p = " + qt + " で 1 のダメージを与える攻撃を、" +
          "HP が 0 以下になるまで繰り返す。E[h] を HP h から終わるまでの攻撃回数の期待値とし、" +
          "E[h] = 1 + p E[max(h − 2, 0)] + (1 − p) E[h − 1] を後ろから埋める。");
      e[0] = fr(0);
      snap("hp", "terminal", e, 0, "HP 0 は終状態で、もう攻撃しない。残りの回数は 0 なので E[0] = 0 を書く。");
      for (var h = 1; h <= n; h++) {
        var t2 = Math.max(h - 2, 0), t1 = h - 1;
        var val = add(ONE, add(mul(p, e[t2]), mul(q, e[t1])));
        var symb = ["1"], nums = ["1"];
        if (!isZero(p)) { symb.push(pt + " × E[" + t2 + "]"); nums.push(pt + " × " + fracText(e[t2])); }
        if (!isZero(q)) { symb.push(qt + " × E[" + t1 + "]"); nums.push(qt + " × " + fracText(e[t1])); }
        // p = 0 なら破線（2 減る）を、p = 1 なら実線（1 減る）を描かないので、その矢印の先は挙げない
        var where;
        if (h === 1) {
          where = isZero(p) ? "HP 1 からは、1 のダメージで HP 0 になる。"
            : isZero(q) ? "HP 1 からは、2 のダメージで HP 0 になる。"
            : "HP 1 からは、どちらのダメージでも HP 0 になる。";
        } else if (isZero(p)) {
          where = "矢印の先の HP " + t1 + " の値はもう決まっている（確率 1）。";
        } else if (isZero(q)) {
          where = "矢印の先の HP " + t2 + " の値はもう決まっている（確率 1）。";
        } else {
          where = "矢印の先の HP " + t2 + " と HP " + t1 + " の値はもう決まっている（確率の和 " + pt + " + " + qt + " = 1）。";
        }
        e[h] = val;
        snap("hp", "fill", e, h,
          where + "E[" + h + "] = " + symb.join(" + ") + " = " + nums.join(" + ") + " = " + longText(val) + " である。");
      }
      snap("hp", "done", e, null,
        "HP の小さい順に埋め終わった。HP " + n + " から倒すまでの攻撃回数の期待値は E[" + n + "] = " + longText(e[n]) +
          " である。");
    }

    if (c.sugoroku) {
      var a = c.sugoroku.a;
      var N = a.length + 1, goal = N - 1;
      var f = new Array(N).fill(null);
      snap("sugoroku", "start", f, null,
        (c.hp ? "後半は、自分自身へ戻る遷移（自己ループ）のある例である。" : "自己ループのある例である。") +
          "マス 0〜" + goal + " のすごろくで、マス i では 0〜A_i の目が等確率で出て、出た目だけ進む（A = " + a.join(", ") +
          "）。0 の目ではそのマスにとどまるので、自分へ戻る矢印（下の輪）がある。");
      f[goal] = fr(0);
      snap("sugoroku", "terminal", f, goal, "ゴールのマス " + goal + " は終状態なので E[" + goal + "] = 0 を書く。");
      for (var i = goal - 1; i >= 0; i--) {
        var A = a[i], r = fr(1, A + 1), rt = fracText(r);
        var dice = [];
        for (var k = 0; k <= A; k++) dice.push(k);
        var others = [], othersNum = [];
        var sum = fr(0);
        for (k = 1; k <= A; k++) {
          others.push(rt + " × E[" + (i + k) + "]");
          othersNum.push(rt + " × " + fracText(f[i + k]));
          sum = add(sum, mul(r, f[i + k]));
        }
        snap("sugoroku", "before", f, i,
          "マス " + i + " では " + dice.join("・") + " の目がそれぞれ確率 " + rt + " で出る。そのまま書くと E[" + i + "] = 1 + " +
            rt + " × E[" + i + "] + " + others.join(" + ") + " で、右辺に求めたい E[" + i + "] 自身がある。");
        var stay = sub(ONE, r);
        var v = div(add(ONE, sum), stay);
        f[i] = v;
        snap("sugoroku", "after", f, i,
          "E[" + i + "] の項を左辺へ移すと (1 − " + rt + ") E[" + i + "] = 1 + " + others.join(" + ") + " なので、E[" + i +
            "] = (1 + " + othersNum.join(" + ") + ") / " + (stay.d === 1n ? fracText(stay) : "(" + fracText(stay) + ")") + " = " + longText(v) + " である。");
      }
      snap("sugoroku", "done", f, null,
        "後ろから埋め終わった。マス 0 からゴールまでに振る回数の期待値は E[0] = " + longText(f[0]) + " である。");
    }
    return out;
  }

  // ---------- 描画 ----------
  // 状態を横 1 列に並べ、終状態を右端に置く（hp は HP n … 0、sugoroku はマス 0 … N−1）。
  var SP = 84; // 箱の中心の間隔
  var BW = 54;
  var BH = 40;
  var MX = 14;
  var TITLE_H = 26;

  function arcH(span) {
    return 16 + 13 * (span - 1);
  }

  function dims(config) {
    var c = validate(config);
    var m = 0, span = 1;
    if (c.hp) { m = Math.max(m, c.hp.n + 1); span = Math.max(span, c.hp.n >= 2 ? 2 : 1); }
    if (c.sugoroku) {
      m = Math.max(m, c.sugoroku.a.length + 1);
      c.sugoroku.a.forEach(function (v) { span = Math.max(span, v); });
    }
    var width = Math.max(2 * MX + (m - 1) * SP + BW, 330);
    var top = TITLE_H + arcH(span) + 10; // 箱の上端
    return { c: c, m: m, width: width, top: top, height: top + BH + 134 };
  }

  function viewBox(config) {
    var d = dims(config);
    return "0 0 " + d.width + " " + d.height;
  }

  // 狭い幅（360px）では図が 0.75 倍ほどに縮むので、名前と凡例は kp.css の is-sub（12px）より大きくする
  var SMALL = "font-size:14px";
  var EDGE = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.5";
  var EDGE_ON = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.6";
  var EDGE_OFF = "fill:none;stroke:var(--md-default-fg-color--lighter);stroke-width:1.2";

  function render(svg, s, config, h) {
    var D = dims(config);
    var c = D.c;
    var hp = s.part === "hp";
    var count = s.e.length;
    var x0 = (D.width - ((count - 1) * SP + BW)) / 2; // 左の箱の左端（中央に寄せる）
    var top = D.top, bottom = D.top + BH;
    // 状態の番号 → 左からの位置
    function col(k) { return hp ? count - 1 - k : k; }
    function cx(k) { return x0 + col(k) * SP + BW / 2; }

    function head(x, y, dx, dy, on) {
      var len = Math.sqrt(dx * dx + dy * dy) || 1;
      var ux = dx / len, uy = dy / len, L = 9, W2 = 4.5;
      var bx = x - ux * L, by = y - uy * L;
      svg.appendChild(h("path", {
        d: "M" + x + " " + y + "L" + (bx - uy * W2) + " " + (by + ux * W2) + "L" + (bx + uy * W2) + " " + (by - ux * W2) + "Z",
        class: on ? "kp-v-mark is-b" : "kp-v-mark",
      }));
    }
    function edgeStyle(from) {
      if (s.focus == null || s.phase === "terminal") return EDGE;
      return from === s.focus ? EDGE_ON : EDGE_OFF;
    }
    // from → to（左から右へ）。span 1 で dashed でなければ直線、ほかは上の弧。
    // 弧の端は arcEnds で決める（入る弧は箱の上辺の左半分、出る弧は右半分に、本数に応じて均等に並べる）
    function isStraight(e) { return Math.abs(col(e.to) - col(e.from)) === 1 && !e.dashed; }
    function arcEnds(list) {
      var outs = {}, ins = {};
      list.forEach(function (e) {
        if (isStraight(e)) return;
        (outs[e.from] = outs[e.from] || []).push(e);
        (ins[e.to] = ins[e.to] || []).push(e);
      });
      function spanOf(e) { return Math.abs(col(e.to) - col(e.from)); }
      function spread(group, lo, hi, key) {
        // 長い弧ほど外側（出る側は左、入る側は右）に置くと、弧どうしが交わらない
        group.sort(function (u, v) { return key * (spanOf(u) - spanOf(v)); });
        group.forEach(function (e, i) {
          var t = group.length === 1 ? 0.5 : i / (group.length - 1);
          e[key > 0 ? "ex" : "sx"] = lo + (hi - lo) * t;
        });
      }
      Object.keys(outs).forEach(function (k) { var c0 = cx(Number(k)); spread(outs[k], c0 + 3, c0 + 24, -1); });
      Object.keys(ins).forEach(function (k) { var c0 = cx(Number(k)); spread(ins[k], c0 - 24, c0 - 3, 1); });
    }
    function edge(e) {
      var from = e.from, to = e.to, dashed = e.dashed;
      var on = s.focus === from && s.phase !== "terminal";
      var style = edgeStyle(from) + (dashed ? ";stroke-dasharray:6 4" : "");
      var span = Math.abs(col(to) - col(from));
      if (isStraight(e)) {
        var ya = top + BH / 2;
        var xs = cx(from) + BW / 2 + 2, xe = cx(to) - BW / 2 - 2;
        svg.appendChild(h("path", { d: "M" + xs + " " + ya + "L" + (xe - 6) + " " + ya, style: style }));
        head(xe, ya, 1, 0, on);
        return;
      }
      var sx = e.sx, ex = e.ex, ah = arcH(span);
      var qx = (sx + ex) / 2, qy = top - 2 * ah;
      // 終点を少し手前で止め、矢じりを弧の向きに付ける
      var tdx = ex - qx, tdy = top - qy, tl = Math.sqrt(tdx * tdx + tdy * tdy);
      var endX = ex - (tdx / tl) * 6, endY = top - (tdy / tl) * 6;
      svg.appendChild(h("path", { d: "M" + sx + " " + top + "Q" + qx + " " + qy + " " + endX + " " + endY, style: style }));
      head(ex, top, tdx, tdy, on);
    }

    // 見出し
    var title = hp
      ? "HP を減らす攻撃（p = " + fracText(c.hp.p) + "）"
      : "自己ループのあるすごろく（A = " + c.sugoroku.a.join(", ") + "）";
    svg.appendChild(h("text", { x: D.width / 2, y: 12, class: "kp-v-ptr is-a", style: "font-size:15px" }, title));

    // 矢印（強調する矢印が上に来るよう、ほかの矢印を先に描く）
    var k, edges = [];
    var p = hp ? c.hp.p : null;
    var pZero = hp && isZero(p), qZero = hp && p.n === p.d;
    if (hp) {
      for (k = 1; k < count; k++) {
        if (!qZero) edges.push({ from: k, to: k - 1, dashed: false });
        if (!pZero) edges.push({ from: k, to: Math.max(k - 2, 0), dashed: true });
      }
    } else {
      for (k = 0; k < c.sugoroku.a.length; k++) {
        for (var j = 1; j <= c.sugoroku.a[k]; j++) edges.push({ from: k, to: k + j, dashed: false });
      }
    }
    arcEnds(edges);
    edges.filter(function (e) { return e.from !== s.focus; }).forEach(edge);
    edges.filter(function (e) { return e.from === s.focus; }).forEach(edge);
    if (!hp) {
      var a = c.sugoroku.a;
      for (k = 0; k < a.length; k++) {
        // 自己ループ（箱の下の輪）
        var on = s.focus === k && s.phase !== "terminal";
        var lx = cx(k), st = edgeStyle(k);
        svg.appendChild(h("path", {
          d: "M" + (lx - 10) + " " + bottom + "C" + (lx - 22) + " " + (bottom + 26) + " " + (lx + 22) + " " + (bottom + 26) + " " +
            (lx + 12) + " " + (bottom + 6),
          style: st,
        }));
        head(lx + 10, bottom, -2, -5, on);
      }
    }

    // 箱と値
    for (k = 0; k < count; k++) {
      var x = cx(k);
      var cls = ["kp-v-cell"], tcls = ["kp-v-text"];
      var known = s.e[k] != null;
      var isNew = s.focus === k && (s.phase === "fill" || s.phase === "after" || s.phase === "terminal");
      if (s.phase === "done" && k === (hp ? count - 1 : 0)) { cls.push("is-answer"); tcls.push("is-on-answer"); }
      else if (isNew) cls.push("is-yes");
      else if (!known) { cls.push("is-no"); tcls.push("is-dim"); }
      if (s.focus === k) cls.push("is-focus");
      svg.appendChild(h("rect", { x: x - BW / 2, y: top, width: BW, height: BH, rx: 6, class: cls.join(" ") }));
      var txt = known ? s.eShort[k] : "?";
      svg.appendChild(h("text", { x: x, y: top + BH / 2, class: tcls.join(" ") }, txt));
      // 名前（終状態には印）
      var name = hp ? "HP " + k : "マス " + k;
      svg.appendChild(h("text", { x: x, y: bottom + 34, class: "kp-v-text is-sub", style: SMALL }, name));
      var sub2 = null;
      if (hp) { if (k === 0) sub2 = "終状態"; }
      else sub2 = k === count - 1 ? "ゴール" : "各 " + fracText(fr(1, c.sugoroku.a[k] + 1));
      if (sub2) svg.appendChild(h("text", { x: x, y: bottom + 51, class: "kp-v-text is-sub", style: SMALL }, sub2));
    }

    // いま式を当てはめている状態の印
    if (s.focus != null) {
      var fx = cx(s.focus), py = bottom + 60;
      svg.appendChild(h("path", { d: "M" + (fx - 6) + " " + (py + 8) + "h12l-6 -8z", class: "kp-v-mark is-b" }));
      var label = s.phase === "terminal" ? "E = 0" : s.phase === "before" ? "移項前" : s.phase === "after" ? "移項後" : "計算";
      svg.appendChild(h("text", { x: fx, y: py + 20, class: "kp-v-ptr is-b", style: SMALL }, label));
    }

    // 凡例（線の種類と言葉で区別する）
    var ly = bottom + 106;
    if (hp) {
      // 描かない種類の矢印（確率 0）は凡例にも書かない
      var lines = [];
      if (!qZero) lines.push("実線：1 減る（確率 1 − p = " + fracText(sub(fr(1), p)) + "）");
      if (!pZero) lines.push("破線：2 減る（確率 p = " + fracText(p) + "）");
      lines.forEach(function (t, i) {
        svg.appendChild(h("text", { x: D.width / 2, y: ly + 18 * i, class: "kp-v-text is-sub", style: SMALL }, t));
      });
    } else {
      svg.appendChild(h("text", { x: D.width / 2, y: ly, class: "kp-v-text is-sub", style: SMALL },
        "右向きの矢印（横と上）：1〜A_i の目で進む"));
      svg.appendChild(h("text", { x: D.width / 2, y: ly + 18, class: "kp-v-text is-sub", style: SMALL }, "下の輪：0 の目でとどまる"));
    }
  }

  return {
    title: "期待値 DP で、終状態から後ろ向きに期待値を埋める",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

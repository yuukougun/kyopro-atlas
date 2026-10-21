/*
 * 動く図：0-1 ナップサックの表 dp[i][j] を 1 行ずつ、1 マスずつ埋める（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="knapsack-table"
 *        data-config='{"W": 5, "items": [{"w": 2, "v": 3}, {"w": 1, "v": 2}, {"w": 3, "v": 4}], "mode": "at-most"}'></div>
 * config：
 *   W     … 重さの上限（1〜10 の整数）。横幅は W + 1 列に比例する。幅 360px のスマホで読めるのは W = 8 ぐらいまで
 *   items … 品物の配列（1〜6 個）。各品物は {"w": 重さ（1〜10 の整数）, "v": 価値（0〜99 の整数）}
 *   mode  … "at-most"（既定。dp[i][j] は重さの合計が j 以下での価値の最大。初期値はすべて 0、答えは dp[N][W]）か
 *            "exact"（重さの合計がちょうど j での価値の最大。dp[0][0] = 0、ほかは −∞、答えは最後の行の最大）
 *
 * 遷移：dp[i + 1][j] = max(dp[i][j], dp[i][j − w_i] + v_i)（j ≥ w_i のとき。j < w_i なら dp[i][j] だけ）。
 * 選ばない遷移は真上のマスから真下へ、選ぶ遷移は w_i だけ左のマスから斜めに来る。max を取った側を太線で示す。
 * 最後に、答えのマスから表を逆にたどって選んだ品物を示す（同じ値なら選ばない側をたどる）。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/knapsack-table.test.mjs が Node で試験する。
 * 状態の表の −∞ は null で持つ（JSON にしても失われないように）。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("knapsack-table", def);
})(function () {
  "use strict";

  var MAX_W = 10;
  var MAX_N = 6;
  var MAX_WEIGHT = 10;
  var MAX_V = 99;

  function isInt(x) {
    return typeof x === "number" && isFinite(x) && Math.floor(x) === x;
  }

  function validate(config) {
    if (!config || typeof config !== "object") throw new Error("data-config がない");
    var W = config.W;
    if (!isInt(W) || W < 1 || W > MAX_W) throw new Error("W は 1〜" + MAX_W + " の整数にする");
    var items = config.items;
    if (!Array.isArray(items) || items.length < 1 || items.length > MAX_N) {
      throw new Error("items は 1〜" + MAX_N + " 個の品物の配列にする");
    }
    var out = [];
    for (var i = 0; i < items.length; i++) {
      var it = items[i];
      if (!it || typeof it !== "object") throw new Error("items の要素は {\"w\": 重さ, \"v\": 価値} にする");
      if (!isInt(it.w) || it.w < 1 || it.w > MAX_WEIGHT) throw new Error("品物の重さ w は 1〜" + MAX_WEIGHT + " の整数にする");
      if (!isInt(it.v) || it.v < 0 || it.v > MAX_V) throw new Error("品物の価値 v は 0〜" + MAX_V + " の整数にする");
      out.push({ w: it.w, v: it.v });
    }
    var mode = config.mode == null ? "at-most" : config.mode;
    if (mode !== "at-most" && mode !== "exact") throw new Error('mode は "at-most" か "exact" にする');
    return { W: W, items: out, mode: mode };
  }

  // null は −∞
  function fmt(x) { return x === null ? "−∞" : String(x); }
  function plus(x, v) { return x === null ? null : x + v; }
  function bigger(a, b) { // a > b（null は −∞）
    if (b === null) return a !== null;
    return a !== null && a > b;
  }
  function itemText(i, it) { return "品物 " + i + "（重さ " + it.w + "・価値 " + it.v + "）"; }

  function copyTable(t) { return t.map(function (r) { return r.slice(); }); }

  // 各ステップの状態：
  //   phase（init / cell / done）、table（(N + 1) × (W + 1)。null は −∞）、filled（行の順に埋めたマスの数）、
  //   focus（いま埋めたマス {i, j}。i は表の行 1〜N。なければ null）、
  //   keep（選ばない側の値）、take（選ぶ側の値。選べないときは undefined）、choice（keep / take / tie / only）、
  //   formula（図の下に出す短い式）、
  //   done のときだけ answer {i, j, value}・picked（選んだ品物の番号）・path（たどったマス {i, j} の列）、caption
  function states(config) {
    var c = validate(config);
    var W = c.W, items = c.items, N = items.length, exact = c.mode === "exact";
    var cols = W + 1;
    var table = [];
    for (var r = 0; r <= N; r++) {
      var row = [];
      for (var j = 0; j <= W; j++) row.push(r === 0 ? (exact ? (j === 0 ? 0 : null) : 0) : null);
      table.push(row);
    }
    var out = [];
    function snap(o) {
      o.table = copyTable(table);
      out.push(o);
    }

    snap({
      phase: "init", filled: cols, focus: null,
      formula: exact ? "dp[0][0] = 0、ほかは −∞" : "dp[0][j] = 0",
      caption: exact
        ? "dp[0][j] は品物を 1 つも使わないときの値である。「重さちょうど j」の定義では、何も選ばないと重さは 0 なので " +
          "dp[0][0] = 0 とし、ほかはまだ作れないので −∞ にする。"
        : "dp[0][j] は品物を 1 つも使わないときの値である。「重さ j 以下」の定義では、何も選ばない選び方がどの j でも" +
          "条件を満たすので、すべて 0 にする。",
    });

    for (var i = 0; i < N; i++) {
      var it = items[i];
      for (j = 0; j <= W; j++) {
        var keep = table[i][j];
        var name = "dp[" + (i + 1) + "][" + j + "]";
        var st = { phase: "cell", focus: { i: i + 1, j: j }, keep: keep };
        var val, cap;
        if (j < it.w) {
          val = keep;
          st.choice = "only";
          st.formula = name + " = dp[" + i + "][" + j + "] = " + fmt(val);
          cap = (j === 0 ? "行 " + (i + 1) + " では" + itemText(i, it) + "を選ぶかを決める。" : "") +
            "重さ " + it.w + " は " + j + " を超えるので品物 " + i + " は選べない。真上の値をそのまま下ろし、" +
            name + " = dp[" + i + "][" + j + "] = " + fmt(val) + " である。";
        } else {
          var take = plus(table[i][j - it.w], it.v);
          st.take = take;
          val = bigger(take, keep) ? take : keep;
          st.choice = bigger(take, keep) ? "take" : bigger(keep, take) ? "keep" : val === null ? "none" : "tie";
          var expr = "max(dp[" + i + "][" + j + "], dp[" + i + "][" + (j - it.w) + "] + " + it.v + ")";
          var nums = "max(" + fmt(keep) + ", " + fmt(table[i][j - it.w]) + " + " + it.v + ")";
          st.formula = name + " = " + nums + " = " + fmt(val);
          cap = (j === 0 ? "行 " + (i + 1) + " では" + itemText(i, it) + "を選ぶかを決める。" : "") +
            name + " = " + expr + " = " + nums + " = " + fmt(val) + " である。";
          if (st.choice === "take") cap += "品物 " + i + " を選ぶ方（斜めの矢印）が大きい。";
          else if (st.choice === "keep") cap += "選ばない方（真下の矢印）が大きい。";
          else if (st.choice === "none") cap += "どちらもまだ作れない重さなので、どちらの矢印も取らない。";
          else cap += "どちらも同じ値である。";
        }
        table[i + 1][j] = val;
        st.filled = cols * (i + 1) + j + 1;
        st.caption = cap;
        snap(st);
      }
    }

    // 答えのマスと、逆にたどった選び方
    var last = table[N];
    var aj = W;
    if (exact) {
      aj = 0;
      for (j = 1; j <= W; j++) if (bigger(last[j], last[aj])) aj = j;
    }
    var path = [{ i: N, j: aj }];
    var picked = [];
    var cj = aj;
    for (i = N - 1; i >= 0; i--) {
      if (table[i + 1][cj] !== table[i][cj]) {
        picked.push(i);
        cj -= items[i].w;
      }
      path.push({ i: i, j: cj });
    }
    picked.reverse();
    var pickText = picked.length === 0 ? "何も選ばない" :
      picked.map(function (k) { return "品物 " + k; }).join(" と") + " を選ぶ";
    var lastText = "最後の行は " + last.map(fmt).join(", ") + " である。";
    var ansCap;
    if (exact) {
      ansCap = "答えは最後の行の最大で、dp[" + N + "][" + aj + "] = " + last[aj] + "（" + pickText + "）である。" +
        "−∞ のマスは、その重さちょうどには詰められないことを表す。";
    } else {
      ansCap = "答えは dp[" + N + "][" + W + "] = " + last[W] + "（" + pickText + "）である。" +
        "各行は左から右へ減らない。重さの上限が大きいほど選べる組が増えるからである。";
    }
    snap({
      phase: "done", filled: cols * (N + 1), focus: null,
      answer: { i: N, j: aj, value: last[aj] },
      picked: picked,
      path: path,
      formula: "答え：dp[" + N + "][" + aj + "] = " + last[aj],
      caption: "表が埋まった。" + lastText + ansCap + (picked.length === 0
        ? "太線は答えのマスから表を逆にたどった道で、どの段も真下なので品物を選ばない。"
        : "太線は答えのマスから表を逆にたどった道で、斜めの段で品物を選んでいる。"),
    });
    return out;
  }

  // 描画の寸法：列 j のマスは x = LW + j × CW、行 r のマスは y = TOP + r × RP
  var LW = 104; // 左の行の名前の幅
  var CW = 48;
  var CELL_W = 42;
  var CELL_H = 32;
  var TOP = 30;
  var RP = 66; // 行の間隔（マスの間の 34 に矢印と足す価値を描く）
  var BOTTOM = 40;
  var RIGHT = 6;

  function sizeOf(config) {
    return { w: LW + (config.W + 1) * CW + RIGHT, h: TOP + config.items.length * RP + CELL_H + BOTTOM };
  }

  function viewBox(config) {
    var s = sizeOf(config);
    return "0 0 " + s.w + " " + s.h;
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

  // 矢印：選んだ側は太い実線、選ばなかった側は細い破線。先に三角を付ける
  function arrow(svg, h, x1, y1, x2, y2, strong, cls) {
    var dx = x2 - x1, dy = y2 - y1;
    var len = Math.sqrt(dx * dx + dy * dy) || 1;
    var ux = dx / len, uy = dy / len;
    var head = strong ? 9 : 7;
    var bx = x2 - ux * head, by = y2 - uy * head;
    if (strong) {
      svg.appendChild(seg(h, x1, y1, bx, by, 3.5, cls));
    } else {
      var n = Math.max(2, Math.round((len - head) / 7));
      for (var k = 0; k < n; k += 2) {
        var t0 = k / n, t1 = Math.min(1, (k + 1) / n);
        svg.appendChild(seg(h, x1 + (bx - x1) * t0, y1 + (by - y1) * t0, x1 + (bx - x1) * t1, y1 + (by - y1) * t1, 1.5, cls));
      }
    }
    var px = -uy * (head * 0.6), py = ux * (head * 0.6);
    svg.appendChild(h("path", {
      d: "M" + x2 + " " + y2 + "L" + (bx + px) + " " + (by + py) + "L" + (bx - px) + " " + (by - py) + "Z",
      class: cls,
    }));
  }

  function render(svg, s, config, h) {
    var c = validate(config);
    var W = c.W, items = c.items, N = items.length;
    var size = sizeOf(c);
    var cols = W + 1;
    function cx(j) { return LW + j * CW + CW / 2; }
    function ry(r) { return TOP + r * RP; }

    // 列の見出し
    svg.appendChild(h("text", { x: LW / 2, y: 12, class: "kp-v-text is-sub" }, "重さ j →"));
    for (var j = 0; j <= W; j++) {
      svg.appendChild(h("text", { x: cx(j), y: 12, class: "kp-v-text is-sub" }, j));
    }

    // 行の名前
    for (var r = 0; r <= N; r++) {
      var y = ry(r);
      var cur = s.focus && s.focus.i === r;
      var head = "dp[" + r + "]" + (r === 0 ? "：なし" : "：品物 " + (r - 1));
      svg.appendChild(h("text", { x: LW / 2 - 2, y: y + 8, class: cur ? "kp-v-ptr is-focus" : "kp-v-ptr" }, head));
      var sub = r === 0 ? "何も選ばない" : "重さ " + items[r - 1].w + "・価値 " + items[r - 1].v;
      svg.appendChild(h("text", { x: LW / 2 - 2, y: y + 25, class: "kp-v-text is-sub" }, sub));
    }

    // 強調するマス
    var role = {}; // "r,j" → "keep" / "take" / "path"
    var arrows = [];
    if (s.focus) {
      var f = s.focus, it = items[f.i - 1];
      var keepStrong = s.choice === "keep" || s.choice === "tie" || s.choice === "only";
      var takeStrong = s.choice === "take" || s.choice === "tie";
      role[(f.i - 1) + "," + f.j] = keepStrong ? "src" : "other";
      arrows.push({ r: f.i - 1, j1: f.j, j2: f.j, strong: keepStrong, kind: "keep" });
      if (f.j >= it.w) {
        var key = (f.i - 1) + "," + (f.j - it.w);
        role[key] = takeStrong ? "src" : "other";
        arrows.push({ r: f.i - 1, j1: f.j - it.w, j2: f.j, strong: takeStrong, kind: "take", v: it.v });
      }
    }
    if (s.phase === "done") {
      for (var p = 0; p < s.path.length; p++) {
        var q = s.path[p];
        role[q.i + "," + q.j] = "path";
        if (p + 1 < s.path.length) {
          var nq = s.path[p + 1];
          arrows.push({ r: nq.i, j1: nq.j, j2: q.j, strong: true, kind: nq.j === q.j ? "keep" : "take", v: items[nq.i].v, path: true });
        }
      }
    }

    // マス
    for (r = 0; r <= N; r++) {
      for (j = 0; j <= W; j++) {
        var idx = r * cols + j;
        var x0 = cx(j) - CELL_W / 2, y0 = ry(r);
        var filled = idx < s.filled;
        var cls = ["kp-v-cell"], tcls = ["kp-v-text"];
        var rl = role[r + "," + j];
        if (!filled) {
          cls.push("is-sentinel");
        } else if (s.phase === "done" && s.answer.i === r && s.answer.j === j) {
          cls.push("is-answer", "is-focus");
          tcls.push("is-on-answer");
        } else if (s.focus && s.focus.i === r && s.focus.j === j) {
          cls.push("is-yes", "is-focus");
        } else if (rl === "src" || rl === "path") {
          cls.push("is-yes");
        } else if (rl === "other") {
          cls.push("is-no");
          tcls.push("is-dim");
        } else if (s.table[r][j] === null) {
          tcls.push("is-dim");
        }
        svg.appendChild(h("rect", { x: x0, y: y0, width: CELL_W, height: CELL_H, rx: 5, class: cls.join(" ") }));
        if (filled) {
          svg.appendChild(h("text", { x: cx(j), y: y0 + CELL_H / 2, class: tcls.join(" ") }, fmt(s.table[r][j])));
        }
      }
    }

    // 矢印（前の行のマスの下端から、次の行のマスの上端へ）
    arrows.forEach(function (a) {
      var x1 = cx(a.j1), y1 = ry(a.r) + CELL_H + 1;
      var x2 = cx(a.j2), y2 = ry(a.r + 1) - 1;
      if (a.kind === "take") { x2 -= 6; } // 真下の矢印と先が重ならないように少しずらす
      else if (a.j1 === a.j2 && !a.path) { x1 += 6; x2 += 6; }
      var cls = a.kind === "take" ? "kp-v-mark is-b" : "kp-v-mark is-focus";
      arrow(svg, h, x1, y1, x2, y2, a.strong, cls);
      if (a.kind === "take") {
        // 斜めの矢印の中ほどの右上に、線から離して足す価値を書く
        var dx = x2 - x1, dy = y2 - y1, len = Math.sqrt(dx * dx + dy * dy) || 1;
        var mx = (x1 + x2) / 2 + (dy / len) * 11, my = (y1 + y2) / 2 - (dx / len) * 10;
        svg.appendChild(h("text", { x: mx, y: my, class: "kp-v-ptr is-b" }, "+" + a.v));
      }
    });

    // 図の下の式
    var yb = size.h - 14;
    svg.appendChild(h("text", {
      x: size.w / 2, y: yb,
      class: s.phase === "done" ? "kp-v-ptr is-focus" : "kp-v-ptr",
    }, s.formula));
  }

  return {
    title: "0-1 ナップサックの表を、選ばない遷移（真下）と選ぶ遷移（斜め）で 1 マスずつ埋める",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

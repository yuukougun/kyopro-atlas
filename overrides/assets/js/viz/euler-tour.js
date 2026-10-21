/*
 * 動く図：オイラーツアー（行きがけ順に in を振り、出るときに out を記録すると、部分木が列の区間 [in, out) になる）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="euler-tour" data-config='{"n": 7, "parents": [-1, 6, 0, 2, 5, 0, 2], "select": [2, 5, 6, 0]}'></div>
 * config：
 *   n       … 頂点数（1〜10）。頂点は 0-indexed で、根は 0。列のマスが n 個並ぶので、幅 360 で読めるよう 10 までにする
 *   parents … 長さ n の整数の配列。parents[0] = −1（根）、それ以外は親の番号（0 以上 n 未満）。親をたどるとどの頂点も根に着く
 *             葉（子のない頂点）は 6 個まで（木の横幅が葉の数で決まるため）
 *   select  … 省略可。DFS の後で部分木と区間を順に示す頂点の配列（0 以上 n 未満、10 個まで）。省略すると示さない
 *
 * DFS は本文のコードと同じく、根 0 から子を番号の小さい順に回る。
 *   入るとき in[v] ← timer、列の位置 timer に v を置き、timer ← timer + 1。出るとき out[v] ← timer（次に振る番号）。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/euler-tour.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("euler-tour", def);
})(function () {
  "use strict";

  var MAX_N = 10;
  var MAX_LEAVES = 6;
  var MAX_SELECT = 10;

  function isInt(x) { return typeof x === "number" && Number.isInteger(x); }

  function validate(config) {
    if (!config || typeof config !== "object" || Array.isArray(config)) throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var p = config.parents;
    if (!Array.isArray(p) || p.length !== n) throw new Error("parents は長さ n（" + n + "）の配列にする");
    if (p[0] !== -1) throw new Error("parents[0] は −1 にする（根は 0）");
    for (var i = 1; i < n; i++) {
      if (!isInt(p[i]) || p[i] < 0 || p[i] >= n) throw new Error("parents[" + i + "] は 0 以上 n 未満の整数にする");
      if (p[i] === i) throw new Error("parents[" + i + "] が自分自身を指している");
    }
    var dep = new Array(n).fill(-1);
    dep[0] = 0;
    for (var v = 1; v < n; v++) {
      var chain = [];
      var x = v;
      while (dep[x] < 0) {
        if (chain.indexOf(x) >= 0) throw new Error("parents に閉路がある（頂点 " + x + "）。木にする");
        chain.push(x);
        x = p[x];
      }
      for (var j = chain.length - 1; j >= 0; j--) dep[chain[j]] = dep[p[chain[j]]] + 1;
    }
    var ch = [];
    for (i = 0; i < n; i++) ch.push([]);
    for (i = 1; i < n; i++) ch[p[i]].push(i); // 番号の小さい順
    var leaves = ch.filter(function (c) { return c.length === 0; }).length;
    if (leaves > MAX_LEAVES) {
      throw new Error("葉（子のない頂点）が " + leaves + " 個ある。幅 360 で読めるよう " + MAX_LEAVES + " 個までにする");
    }
    var sel = config.select == null ? [] : config.select;
    if (!Array.isArray(sel) || sel.length > MAX_SELECT) throw new Error("select は " + MAX_SELECT + " 個までの頂点の配列にする");
    for (i = 0; i < sel.length; i++) {
      if (!isInt(sel[i]) || sel[i] < 0 || sel[i] >= n) throw new Error("select[" + i + "] は 0 以上 n 未満の整数にする");
    }
    return { n: n, parents: p.slice(), dep: dep, ch: ch, select: sel.slice() };
  }

  function listJa(a) { return a.join("・"); }

  // 状態：phase（start・enter・exit・built・subtree）、cur（いまの頂点）、stack（根から cur までの DFS の道）、
  //   tin・tout（長さ n、未定は null）、ord（列 ord。長さ n、未定は null）、timer、sel（subtree のときの頂点）、
  //   range（subtree のときの [l, r)）、members（subtree のときの部分木の頂点。列の順）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n, ch = c.ch;
    var tin = new Array(n).fill(null);
    var tout = new Array(n).fill(null);
    var ord = new Array(n).fill(null);
    var timer = 0;
    var out = [];
    function push(s, stack) {
      s.tin = tin.slice();
      s.tout = tout.slice();
      s.ord = ord.slice();
      s.timer = timer;
      s.stack = stack ? stack.slice() : [];
      if (s.cur == null) s.cur = null;
      if (s.sel == null) s.sel = null;
      if (s.range == null) s.range = null;
      if (s.members == null) s.members = [];
      out.push(s);
    }

    push({
      phase: "start",
      caption: "根 0 から DFS を始める。番号 timer は 0 から振り、子は番号の小さい順に回る。",
    });

    // 反復の DFS（[頂点, 次に見る子の添字]）
    var st = [[0, 0]];
    var path = [];
    function enter(v) {
      var t = timer;
      tin[v] = t;
      ord[t] = v;
      timer = t + 1;
      path.push(v);
      var pv = c.parents[v];
      push({
        phase: "enter", cur: v,
        caption: (pv < 0 ? "根 0" : "頂点 " + pv + " の子 " + v) + " に入る。in[" + v + "] = " + t + " とし、列の位置 " + t +
          " に " + v + " を置く。timer は " + (t + 1) + " になる。",
      }, path);
    }
    enter(0);
    while (st.length) {
      var top = st[st.length - 1];
      var v = top[0];
      if (top[1] < ch[v].length) {
        var w = ch[v][top[1]++];
        st.push([w, 0]);
        enter(w);
        continue;
      }
      tout[v] = timer;
      push({
        phase: "exit", cur: v,
        caption: ch[v].length === 0
          ? "頂点 " + v + " には子がないので、すぐ出る。出るときの次の番号 " + timer + " を out[" + v + "] とする。"
          : "頂点 " + v + " の子孫をすべて回り終えた。出るときの次の番号 " + timer + " を out[" + v + "] とする。",
      }, path);
      path.pop();
      st.pop();
    }

    push({
      phase: "built",
      caption: "DFS が終わった。列 ord は " + ord.join(", ") + " で、どの頂点 v の部分木も列の区間 [in[v], out[v]) になる。",
    });

    c.select.forEach(function (s) {
      var l = tin[s], r = tout[s];
      var mem = ord.slice(l, r);
      var nums = r - l === 1 ? "番号 " + l + " は" : "番号 " + l + "〜" + (r - 1) + " は";
      var cap = "頂点 " + s + " の部分木（" + listJa(mem) + "）は区間 [" + l + ", " + r + ")。" + nums + "頂点 " + s +
        " に入ってから出るまでに振られ、長さ " + r + " − " + l + " = " + (r - l) + " は部分木の頂点数に等しい。";
      if (s === 0) cap += "根の部分木は列の全体である。";
      push({ phase: "subtree", sel: s, cur: s, range: [l, r], members: mem, caption: cap });
    });
    return out;
  }

  // 描画の寸法
  var PITCH = 64; // 葉の間隔
  var DY = 54; // 深さ 1 の間隔
  var R = 16; // 頂点の半径
  var SIDE = 16; // 木の左右の余白
  var LABEL_W = 60; // 列と表の左の見出しの幅
  var CW = 40; // マスの幅
  var CH = 32; // マスの高さ
  var MIN_W = 380;
  var LINE = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.4";
  var LINE_ON = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3.5";
  var BRACKET = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.5";

  function layout(c) {
    var n = c.n, ch = c.ch;
    var col = new Array(n).fill(0);
    var leaves = 0;
    var stack = [[0, 0]];
    while (stack.length) {
      var top = stack[stack.length - 1];
      var x = top[0];
      if (top[1] < ch[x].length) {
        stack.push([ch[x][top[1]++], 0]);
        continue;
      }
      stack.pop();
      if (ch[x].length === 0) col[x] = leaves++;
      else col[x] = (col[ch[x][0]] + col[ch[x][ch[x].length - 1]]) / 2;
    }
    return { col: col, leaves: leaves, maxDep: Math.max.apply(null, c.dep) };
  }

  function dims(config) {
    var c = validate(config);
    var lay = layout(c);
    var treeW = 2 * SIDE + (lay.leaves - 1) * PITCH + 2 * R;
    var gridW = LABEL_W + c.n * CW;
    var width = Math.max(MIN_W, treeW, gridW + 16);
    var treeTop = 48;
    var arrHead = treeTop + lay.maxDep * DY + R + 30; // 「列 ord」の見出し
    var arrTop = arrHead + 36; // 列のマスの上端（見出しとの間に区間の括弧）
    var tabHead = arrTop + CH + 20 + 26; // 「in・out」の見出し（列の下に位置の行）
    var tabTop = tabHead + 14;
    var height = tabTop + CH * 3 + 8;
    var gridX = (width - gridW) / 2;
    return {
      c: c, lay: lay, width: width, height: height, treeTop: treeTop,
      treeX: (width - treeW) / 2 + SIDE + R, arrHead: arrHead, arrTop: arrTop, tabHead: tabHead, tabTop: tabTop,
      gridX: gridX, cellX: gridX + LABEL_W,
    };
  }

  function viewBox(config) {
    var D = dims(config);
    return "0 0 " + D.width + " " + D.height;
  }

  var cache = typeof WeakMap === "function" ? new WeakMap() : null;
  function dimsFor(config) {
    var d = cache && cache.get(config);
    if (!d) {
      d = dims(config);
      if (cache) cache.set(config, d);
    }
    return d;
  }

  function render(svg, s, config, h) {
    var D = dimsFor(config);
    var c = D.c, lay = D.lay, n = c.n;
    function nx(x) { return D.treeX + lay.col[x] * PITCH; }
    function ny(x) { return D.treeTop + c.dep[x] * DY; }
    var sub = s.phase === "subtree";
    var inSub = new Array(n).fill(false);
    s.members.forEach(function (x) { inSub[x] = true; });
    var onPath = new Array(n).fill(false);
    s.stack.forEach(function (x) { onPath[x] = true; });

    // 見出し
    var title;
    if (s.phase === "start") title = "DFS を始める（timer = 0）";
    else if (s.phase === "enter") title = "頂点 " + s.cur + " に入る：in[" + s.cur + "] = " + s.tin[s.cur];
    else if (s.phase === "exit") title = "頂点 " + s.cur + " から出る：out[" + s.cur + "] = " + s.tout[s.cur];
    else if (s.phase === "built") title = "列ができた";
    else title = "頂点 " + s.sel + " の部分木 = 区間 [" + s.range[0] + ", " + s.range[1] + ")";
    svg.appendChild(h("text", { x: D.width / 2, y: 16, class: "kp-v-ptr is-a", style: "font-size:15px" }, title));

    // 辺：DFS の道（根からいまの頂点まで）と、示している部分木の中の辺は太線
    for (var x = 1; x < n; x++) {
      var p = c.parents[x];
      var on = sub ? inSub[x] && inSub[p] : onPath[x] && onPath[p];
      svg.appendChild(h("line", { x1: nx(p), y1: ny(p), x2: nx(x), y2: ny(x), style: on ? LINE_ON : LINE }));
    }

    // 頂点
    for (x = 0; x < n; x++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      var bold = false;
      if (sub) {
        if (inSub[x]) cls.push("is-yes");
        else { cls.push("is-no"); tcls.push("is-dim"); }
        if (x === s.sel) { cls.push("is-focus"); bold = true; }
      } else {
        if (s.tin[x] == null) { cls.push("is-no"); tcls.push("is-dim"); }
        else if (onPath[x]) cls.push("is-yes");
        if (x === s.cur) { cls.push("is-focus"); bold = true; }
      }
      // 塗りが半透明の class もあるので、下に背景色の円を敷いて辺を隠す
      svg.appendChild(h("circle", { cx: nx(x), cy: ny(x), r: R, style: "fill:var(--md-default-bg-color);stroke:none" }));
      svg.appendChild(h("circle", { cx: nx(x), cy: ny(x), r: R, class: cls.join(" ") }));
      svg.appendChild(h("text", { x: nx(x), y: ny(x), class: tcls.join(" "), style: bold ? "font-weight:700" : null }, x));
    }

    function cellX(i) { return D.cellX + i * CW; }
    function label(y, text) {
      svg.appendChild(h("text", {
        x: D.gridX + LABEL_W - 8, y: y, class: "kp-v-text is-sub", style: "text-anchor:end;font-size:13px",
      }, text));
    }

    // 列 ord
    svg.appendChild(h("text", {
      x: D.width / 2, y: D.arrHead, class: "kp-v-ptr is-a", style: "font-size:14px",
    }, sub || s.phase === "built" ? "列 ord（位置 t の頂点）" : "列 ord（行きがけ順の頂点）　timer = " + s.timer));
    label(D.arrTop + CH / 2, "ord[t]");
    label(D.arrTop + CH + 12, "位置 t");
    for (var t = 0; t < n; t++) {
      var v = s.ord[t];
      var ccls = ["kp-v-cell"];
      var ttcls = ["kp-v-text"];
      var b2 = false;
      if (v == null) ccls.push("is-sentinel");
      else if (sub) {
        if (t >= s.range[0] && t < s.range[1]) ccls.push("is-yes");
        else { ccls.push("is-no"); ttcls.push("is-dim"); }
      } else if (s.phase === "enter" && v === s.cur) { ccls.push("is-focus"); b2 = true; }
      svg.appendChild(h("rect", { x: cellX(t) + 2, y: D.arrTop, width: CW - 4, height: CH, rx: 5, class: ccls.join(" ") }));
      if (v != null) {
        svg.appendChild(h("text", {
          x: cellX(t) + CW / 2, y: D.arrTop + CH / 2, class: ttcls.join(" "), style: b2 ? "font-weight:700" : null,
        }, v));
      }
      svg.appendChild(h("text", { x: cellX(t) + CW / 2, y: D.arrTop + CH + 12, class: "kp-v-text is-sub" }, t));
    }
    // 区間の括弧と [l, r)
    if (sub) {
      var x1 = cellX(s.range[0]) + 3, x2 = cellX(s.range[1]) - 3;
      var by = D.arrTop - 6;
      svg.appendChild(h("path", { d: "M" + x1 + " " + (by + 5) + "V" + by + "H" + x2 + "V" + (by + 5), style: BRACKET }));
      svg.appendChild(h("text", {
        x: (x1 + x2) / 2, y: by - 11, class: "kp-v-ptr is-b", style: "font-size:14px",
      }, "[" + s.range[0] + ", " + s.range[1] + ")"));
    }

    // in・out の表（頂点ごと）
    svg.appendChild(h("text", {
      x: D.width / 2, y: D.tabHead, class: "kp-v-ptr is-a", style: "font-size:14px",
    }, "頂点ごとの in と out"));
    var rows = [["頂点 v", null], ["in[v]", s.tin], ["out[v]", s.tout]];
    rows.forEach(function (row, ri) {
      var y = D.tabTop + ri * CH;
      label(y + CH / 2, row[0]);
      for (var u = 0; u < n; u++) {
        if (ri === 0) {
          svg.appendChild(h("text", {
            x: cellX(u) + CW / 2, y: y + CH / 2, class: "kp-v-text" + (sub && !inSub[u] ? " is-dim" : ""),
            style: "font-size:14px" + ((sub ? u === s.sel : u === s.cur) ? ";font-weight:700" : ""),
          }, u));
          continue;
        }
        var val = row[1][u];
        var focus = sub ? u === s.sel
          : u === s.cur && ((ri === 1 && s.phase === "enter") || (ri === 2 && s.phase === "exit"));
        var rc = "kp-v-cell" + (val == null ? " is-sentinel" : focus ? " is-focus" : "");
        svg.appendChild(h("rect", { x: cellX(u) + 2, y: y + 2, width: CW - 4, height: CH - 4, rx: 5, class: rc }));
        if (val != null) {
          svg.appendChild(h("text", {
            x: cellX(u) + CW / 2, y: y + CH / 2, class: "kp-v-text" + (sub && !inSub[u] ? " is-dim" : ""),
            style: "font-size:14px" + (focus ? ";font-weight:700" : ""),
          }, val));
        }
      }
    });
  }

  return {
    title: "オイラーツアー：行きがけ順に番号を振ると部分木が列の区間になる",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

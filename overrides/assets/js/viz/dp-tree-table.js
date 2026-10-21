/*
 * 動く図：全探索の木と DP の表（同じ状態の枝が表の 1 マスにまとまる）、同じ表を貰う形と配る形で埋める
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="dp-tree-table" data-config='{"h": [8, 1, 7, 2, 9, 6]}'></div>
 * config：
 *   h     … 足場の高さ h_0, …, h_{N−1}（2〜6 個の 0〜99 の整数）。1 つ先か 2 つ先へ跳び、|h_j − h_i| のコストがかかる
 *   parts … 省略可。見せる部分の配列で、"tree"・"pull"・"push" から選ぶ（既定は 3 つすべて。並びはいつもこの順）
 *
 * 前半（tree）：足場 N−1 から「どこから来たか」を逆向きに分岐する素朴な再帰 f(i) → f(i−1), f(i−2) の木を描き、
 * 帰りがけ順に進める。足場 i の呼び出しが初めて返ったら表の dp[i] に書く（実線で結ぶ）。同じ足場の呼び出しが
 * もう一度現れたら、その部分木をまとめて灰色（破線の枠）にし、表の dp[i] へ破線を引く。呼び出しの回数を数える。
 * 後半（pull・push）：同じ表の上で、貰う形（dp[i] へ実線の矢印を集める）と配る形（dp[i] から破線の矢印を出す）を
 * 1 マスずつ進める。どちらも辺（i → i+1 が N−1 本、i → i+2 が N−2 本、計 2N − 3 本）を 1 回ずつ使う。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/dp-tree-table.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("dp-tree-table", def);
})(function () {
  "use strict";

  var MIN_N = 2;
  var MAX_N = 6; // N = 6 で呼び出し 20 回・葉 8 個。7 にすると 33 回・葉 13 個で、狭い幅に収まらない
  var MAX_H = 99;
  var PARTS = ["tree", "pull", "push"];

  function validate(config) {
    if (!config || typeof config !== "object" || Array.isArray(config)) throw new Error("data-config がない");
    var h = config.h;
    if (!Array.isArray(h) || h.length < MIN_N || h.length > MAX_N) {
      throw new Error("h は " + MIN_N + "〜" + MAX_N + " 個の整数の配列にする");
    }
    for (var i = 0; i < h.length; i++) {
      if (typeof h[i] !== "number" || !Number.isInteger(h[i])) throw new Error("h の要素は整数にする");
      if (h[i] < 0 || h[i] > MAX_H) throw new Error("h の要素は 0 以上 " + MAX_H + " 以下にする");
    }
    var parts = PARTS.slice();
    if (config.parts != null) {
      if (!Array.isArray(config.parts) || config.parts.length === 0) {
        throw new Error('parts は "tree"・"pull"・"push" から選んだ空でない配列にする');
      }
      config.parts.forEach(function (p) {
        if (PARTS.indexOf(p) < 0) throw new Error('parts の要素は "tree"・"pull"・"push" のどれかにする：' + p);
      });
      parts = PARTS.filter(function (p) { return config.parts.indexOf(p) >= 0; });
    }
    return { h: h.slice(), parts: parts };
  }

  // 素朴な再帰の木。節は行きがけ順に番号を振る。x は葉の並び（0, 1, …）から決める（葉は帰りがけ順に左から）
  function buildTree(n) {
    var nodes = [];
    var leaf = 0;
    function rec(foot, depth, parent) {
      var id = nodes.length;
      var node = { id: id, foot: foot, depth: depth, parent: parent, children: [], x: 0 };
      nodes.push(node);
      if (foot >= 1) node.children.push(rec(foot - 1, depth + 1, id));
      if (foot >= 2) node.children.push(rec(foot - 2, depth + 1, id));
      if (node.children.length === 0) node.x = leaf++;
      else {
        node.x = node.children.reduce(function (s, c) { return s + nodes[c].x; }, 0) / node.children.length;
      }
      return id;
    }
    rec(n - 1, 0, -1);
    return { nodes: nodes, leaves: leaf, depth: n - 1 };
  }

  function subtree(nodes, id) {
    var out = [id];
    nodes[id].children.forEach(function (c) { out = out.concat(subtree(nodes, c)); });
    return out;
  }

  function cost(h, i, j) { return Math.abs(h[i] - h[j]); }

  // 貰う形の 1 マスの式：遷移元の値と足すコスト
  function pullTerms(h, dp, i) {
    var t = [{ from: i - 1, base: dp[i - 1], c: cost(h, i, i - 1) }];
    if (i >= 2) t.push({ from: i - 2, base: dp[i - 2], c: cost(h, i, i - 2) });
    return t;
  }

  function pullText(h, dp, i) {
    var t = pullTerms(h, dp, i);
    var v = Math.min.apply(null, t.map(function (x) { return x.base + x.c; }));
    if (t.length === 1) {
      return "dp[1] = dp[0] + |" + h[1] + " − " + h[0] + "| = " + t[0].base + " + " + t[0].c + " = " + v;
    }
    return "dp[" + i + "] = min(dp[" + (i - 1) + "] + |" + h[i] + " − " + h[i - 1] + "|, dp[" + (i - 2) + "] + |" + h[i] +
      " − " + h[i - 2] + "|) = min(" + t[0].base + " + " + t[0].c + ", " + t[1].base + " + " + t[1].c + ") = " + v;
  }

  function solve(h) {
    var dp = [0];
    for (var i = 1; i < h.length; i++) {
      dp.push(Math.min.apply(null, pullTerms(h, dp, i).map(function (x) { return x.base + x.c; })));
    }
    return dp;
  }

  function fill(n, v) {
    var a = [];
    for (var i = 0; i < n; i++) a.push(v);
    return a;
  }

  function tupleText(a) { return "(" + a.join(", ") + ")"; }

  // 各状態：part（"tree" | "pull" | "push"）、table（dp の値。決まっていなければ null）、confirmed（値が確定したか）、
  // focus（注目するマス）、answer（答えのマスを示すか）、caption。
  // tree：status（節ごとに 0 未計算・1 計算した・2 計算済みの呼び直し）、current（いま変わった節）、
  //       link（{node, cell, kind: "write" | "read"}）、calls（返った呼び出しの数）、total（呼び出しの総数）
  // pull・push：active（いま使う辺 [元, 先]）、used（使い終えた辺。active を含む）、updates（配る形の更新 {to, old, now}）
  function states(config) {
    var c = validate(config);
    var h = c.h;
    var n = h.length;
    var last = n - 1;
    var dp = solve(h);
    var edgesAll = 2 * n - 3;
    var out = [];

    function hasPart(p) { return c.parts.indexOf(p) >= 0; }

    if (hasPart("tree")) {
      var T = buildTree(n);
      var nodes = T.nodes;
      var total = nodes.length;
      var status = fill(total, 0);
      var table = fill(n, null);
      var calls = 0;
      out.push({
        part: "tree", status: status.slice(), current: [], link: null, calls: 0, total: total,
        table: table.slice(), confirmed: fill(n, false), focus: null, answer: false,
        caption: "足場 " + last + " から「どこから来たか」を逆向きに分岐する素朴な再帰の木である（f(i) が f(i − 1) と f(i − 2) を呼ぶ）。" +
          "呼び出しは全部で " + total + " 回ある。下の dp の表はまだ空である。",
      });
      var seen = fill(n, false);
      var visit = function (id) {
        var nd = nodes[id];
        var f = nd.foot;
        if (seen[f]) {
          var sub = subtree(nodes, id);
          sub.forEach(function (k) { status[k] = 2; });
          calls += sub.length;
          out.push({
            part: "tree", status: status.slice(), current: sub, link: { node: id, cell: f, kind: "read" }, calls: calls,
            total: total, table: table.slice(), confirmed: table.map(function (v) { return v !== null; }), focus: f,
            answer: false,
            caption: "足場 " + f + " をもう一度呼ぶ。素朴な再帰はここから " + sub.length + " 回の呼び出しをやり直すが、" +
              "返る値は表の dp[" + f + "] = " + dp[f] + " と同じである。表があれば引くだけで済む（返った呼び出しはここまで " + calls + " 回）。",
          });
          return;
        }
        nd.children.forEach(visit);
        seen[f] = true;
        status[id] = 1;
        table[f] = dp[f];
        calls += 1;
        var how = f === 0 ? "出発点なので dp[0] = 0" : pullText(h, dp, f);
        out.push({
          part: "tree", status: status.slice(), current: [id], link: { node: id, cell: f, kind: "write" }, calls: calls,
          total: total, table: table.slice(), confirmed: table.map(function (v) { return v !== null; }), focus: f,
          answer: false,
          caption: "足場 " + f + " の呼び出しが初めて返る。" + how + "。表の dp[" + f + "] に書く（返った呼び出しはここまで " + calls + " 回）。",
        });
      };
      visit(0);
      out.push({
        part: "tree", status: status.slice(), current: [], link: null, calls: calls, total: total,
        table: table.slice(), confirmed: fill(n, true), focus: null, answer: true,
        caption: (total > n
          ? "木の呼び出しは " + total + " 回だが、異なる足場は " + n + " つしかない。同じ足場の枝は表の 1 マスにまとまり、" +
            "表なら各マスを 1 回ずつ計算すれば済む。"
          : "足場が " + n + " つでは同じ足場の呼び直しは起きず、木の呼び出しと表のマスはどちらも " + n + " つである。") +
          "表は " + tupleText(dp) + "、答えは dp[" + last + "] = " + dp[last] + " である。",
      });
    }

    if (hasPart("pull")) {
      var pt = fill(n, null);
      pt[0] = 0;
      var used = [];
      out.push({
        part: "pull", table: pt.slice(), confirmed: pt.map(function (v) { return v !== null; }), focus: 0, answer: false,
        active: [], used: [], updates: [],
        caption: "貰う形で同じ表を埋める。dp[0] = 0 から始め、dp[i] には i − 1 と i − 2 から矢印（実線）を集める。" +
          "辺は全部で 2N − 3 = " + edgesAll + " 本ある。",
      });
      for (var i = 1; i < n; i++) {
        var act = pullTerms(h, dp, i).map(function (x) { return [x.from, i]; }).reverse(); // 遠い元から
        used = used.concat(act);
        pt[i] = dp[i];
        var from = i >= 2 ? "dp[" + (i - 1) + "] と dp[" + (i - 2) + "] から" : "dp[0] から";
        out.push({
          part: "pull", table: pt.slice(), confirmed: pt.map(function (v) { return v !== null; }), focus: i,
          answer: i === last, active: act, used: used.slice(), updates: [],
          caption: "dp[" + i + "] に " + from + "貰う：" + pullText(h, dp, i) + "。使った辺は " + used.length + " / " + edgesAll +
            " 本。" + (i === last ? "答えは dp[" + last + "] = " + dp[last] + " である。" : ""),
        });
      }
    }

    if (hasPart("push")) {
      var qt = fill(n, null); // null は ∞（まだどこからも遷移が来ていない）
      qt[0] = 0;
      var qused = [];
      var conf = fill(n, false);
      conf[0] = true;
      out.push({
        part: "push", table: qt.slice(), confirmed: conf.slice(), focus: 0, answer: false,
        active: [], used: [], updates: [],
        caption: "配る形で同じ表を埋める。dp[0] = 0、ほかは ∞ から始め、確定した dp[i] から i + 1 と i + 2 へ矢印（破線）を出し、" +
          "送り先では min を取る。",
      });
      for (var j = 0; j + 1 < n; j++) {
        var acts = [];
        var ups = [];
        var parts = []; // 送り先ごとの式
        for (var d = 1; d <= 2 && j + d < n; d++) {
          var to = j + d;
          var old = qt[to];
          var cand = qt[j] + cost(h, j, to);
          var now = old === null ? cand : Math.min(old, cand);
          qt[to] = now;
          acts.push([j, to]);
          ups.push({ to: to, old: old, now: now });
          parts.push({ text: "dp[" + to + "] は min(" + (old === null ? "∞" : old) + ", " + qt[j] + " + " + cost(h, j, to) +
            ") = " + now, same: old === now });
        }
        qused = qused.concat(acts);
        conf[j + 1] = true; // j + 1 へ入る辺（j − 1 から・j から）はこれで使い終えた
        var end = j + 1 === last;
        out.push({
          part: "push", table: qt.slice(), confirmed: conf.slice(), focus: j, answer: end, active: acts,
          used: qused.slice(), updates: ups,
          caption: "dp[" + j + "] = " + qt[j] + " は確定したので配る：" + parts.map(function (p, k) {
            var tail = k + 1 < parts.length;
            return p.text + (p.same ? (tail ? " のままで" : " のままである") : (tail ? " になり" : " になる"));
          }).join("、") + "。使った辺は " + qused.length + " / " + edgesAll + " 本。" +
            (end ? (hasPart("pull") ? "どちらの形も各辺を 1 回ずつ使い、表は同じ " : "各辺を 1 回ずつ使い、表は ") +
              tupleText(qt) + " になった。答えは dp[" + last + "] = " +
              qt[last] + " である。" : ""),
        });
      }
    }
    return out;
  }

  // ---------- 描画 ----------
  var MX = 10;
  var PITCH = 58; // 表のマスの間隔
  var CW = 48;
  var CH = 34;
  var LABEL_W = 40; // 表の左の行の名前
  var LP = 40; // 木の葉の間隔
  var R = 13; // 木の節の半径
  var DY = 36; // 木の段の間隔
  var TREE_TOP = 44;
  var ARC_ROOM = 120; // 後半の弧と、その上のコストの文字に要る高さ

  function dims(config) {
    var c = validate(config);
    var n = c.h.length;
    var leaves = buildTree(n).leaves;
    var tableW = LABEL_W + n * PITCH;
    var width = Math.max(tableW, leaves * LP, 300) + 2 * MX;
    var treeBottom = c.parts.indexOf("tree") >= 0 ? TREE_TOP + (n - 1) * DY + R : 0;
    var top = Math.max(treeBottom + 30, 26 + ARC_ROOM); // 表のマスの上端
    var hasPush = c.parts.indexOf("push") >= 0;
    var height = top + CH + 36 + (hasPush ? 22 : 0) + 6;
    return { c: c, n: n, width: width, top: top, tableX: (width - tableW) / 2 + LABEL_W, height: height };
  }

  function viewBox(config) {
    var d = dims(config);
    return "0 0 " + d.width + " " + d.height;
  }

  // 狭い幅（360px）では図が 0.75 倍ほどに縮むので、補助の文字は kp.css の is-sub（12px）より大きくする
  var SMALL = "font-size:14px";
  // 線の上に置く文字の縁取り（背景色）。交わる弧に数字が隠れないようにする
  var HALO = "paint-order:stroke;stroke:var(--md-default-bg-color);stroke-width:4px;stroke-linejoin:round";
  var LINE = "fill:none;stroke:var(--md-default-fg-color--lighter);stroke-width:1.3";
  var LINE_ON = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.6";
  var LINE_UNUSED = "fill:none;stroke:var(--md-default-fg-color--lightest);stroke-width:1.2;stroke-dasharray:2 4";

  function render(svg, s, config, h) {
    var D = dims(config);
    var hs = D.c.h;
    var n = D.n;
    var top = D.top;
    function cx(i) { return D.tableX + i * PITCH + PITCH / 2; }

    function head(x, y, dx, dy, cls) {
      var len = Math.sqrt(dx * dx + dy * dy) || 1;
      var ux = dx / len, uy = dy / len, L = 9, W2 = 4.5;
      var bx = x - ux * L, by = y - uy * L;
      svg.appendChild(h("path", {
        d: "M" + x + " " + y + "L" + (bx - uy * W2) + " " + (by + ux * W2) + "L" + (bx + uy * W2) + " " + (by - ux * W2) + "Z",
        class: cls,
      }));
    }

    // 見出し
    var title;
    if (s.part === "tree") title = "素朴な再帰の木（返った呼び出し " + s.calls + " / " + s.total + "）";
    else if (s.part === "pull") title = "貰う形：dp[i] へ矢印を集める（実線）";
    else title = "配る形：dp[i] から矢印を出す（破線）";
    svg.appendChild(h("text", { x: D.width / 2, y: 13, class: "kp-v-ptr is-a", style: "font-size:15px" }, title));

    if (s.part === "tree") drawTree();
    else drawEdges();
    drawTable();

    function drawTree() {
      var T = buildTree(n);
      var nodes = T.nodes;
      var x0 = (D.width - (T.leaves - 1) * LP) / 2;
      function nx(nd) { return x0 + nd.x * LP; }
      function ny(nd) { return TREE_TOP + nd.depth * DY; }
      nodes.forEach(function (nd) {
        if (nd.parent < 0) return;
        var p = nodes[nd.parent];
        svg.appendChild(h("line", { x1: nx(p), y1: ny(p), x2: nx(nd), y2: ny(nd), style: LINE }));
      });
      // いまの節と表のマスを結ぶ線（書くときは実線、表を引くときは破線）
      if (s.link) {
        var ln = nodes[s.link.node];
        var tx = cx(s.link.cell), ty = top - 2;
        var sx = nx(ln), sy = ny(ln);
        var dx = tx - sx, dy = ty - sy, len = Math.sqrt(dx * dx + dy * dy) || 1;
        sx += (dx / len) * (R + 2);
        sy += (dy / len) * (R + 2);
        var ex = tx - (dx / len) * 7, ey = ty - (dy / len) * 7;
        svg.appendChild(h("path", {
          d: "M" + sx + " " + sy + "L" + ex + " " + ey,
          style: LINE_ON + (s.link.kind === "read" ? ";stroke-dasharray:6 4" : ""),
        }));
        head(tx, ty, dx, dy, "kp-v-mark is-b");
      }
      var cur = {};
      s.current.forEach(function (k) { cur[k] = true; });
      nodes.forEach(function (nd) {
        var st = s.status[nd.id];
        var cls = ["kp-v-cell"];
        var tcls = ["kp-v-text"];
        var attrs = { cx: nx(nd), cy: ny(nd), r: R };
        if (st === 0) { attrs.style = "fill:var(--md-default-bg-color)"; tcls.push("is-dim"); }
        else if (st === 1) { cls.push("is-yes"); }
        else {
          cls.push("is-no");
          tcls.push("is-dim");
          attrs["stroke-dasharray"] = "4 3";
          // いま呼び直した部分木は枠をアクセント色にする（根はさらに太枠）
          if (cur[nd.id]) {
            var root = s.link && nd.id === s.link.node;
            attrs.style = "stroke:var(--md-accent-fg-color);stroke-width:" + (root ? 3.5 : 2);
          }
        }
        if (cur[nd.id] && (st === 1 || nd.id === (s.link && s.link.node))) cls.push("is-focus");
        attrs.class = cls.join(" ");
        svg.appendChild(h("circle", attrs));
        var ta = { x: nx(nd), y: ny(nd), class: tcls.join(" "), style: "font-size:14px" + (st === 1 ? ";font-weight:700" : "") };
        svg.appendChild(h("text", ta, nd.foot));
      });
    }

    // 後半：状態を頂点、遷移を辺とした弧。i → i+1 は低い弧、i → i+2 は高い弧
    function drawEdges() {
      var dashed = s.part === "push";
      var used = {}, act = {};
      s.used.forEach(function (e) { used[e[0] + "-" + e[1]] = true; });
      s.active.forEach(function (e) { act[e[0] + "-" + e[1]] = true; });
      var labels = [];
      for (var span = 2; span >= 1; span--) {
        for (var a = 0; a + span < n; a++) {
          var b = a + span;
          var key = a + "-" + b;
          var on = !!act[key];
          var style = on ? LINE_ON : used[key] ? LINE : LINE_UNUSED;
          if ((on || used[key]) && dashed) style += ";stroke-dasharray:6 4";
          var off = span === 1 ? 6 : 16;
          var sx = cx(a) + off, ex = cx(b) - off;
          var peak = span === 1 ? 36 : 84;
          var qx = (sx + ex) / 2, qy = top - 2 * peak;
          var tdx = ex - qx, tdy = top - qy, tl = Math.sqrt(tdx * tdx + tdy * tdy);
          var endX = ex - (tdx / tl) * 7, endY = top - (tdy / tl) * 7;
          svg.appendChild(h("path", { d: "M" + sx + " " + top + "Q" + qx + " " + qy + " " + endX + " " + endY, style: style }));
          if (on || used[key]) head(ex, top, tdx, tdy, on ? "kp-v-mark is-b" : "kp-v-mark");
          if (on) labels.push({ x: qx, y: top - peak - 9, t: "+" + Math.abs(hs[b] - hs[a]) });
        }
      }
      labels.forEach(function (l) {
        svg.appendChild(h("text", { x: l.x, y: l.y, class: "kp-v-ptr is-b", style: "font-size:14px;" + HALO }, l.t));
      });
    }

    function drawTable() {
      var ly = top + CH / 2;
      var rows = [["dp", ly], ["h", top + CH + 13], ["足場", top + CH + 31]];
      if (s.part === "push") rows.push(["更新", top + CH + 51]);
      rows.forEach(function (r) {
        svg.appendChild(h("text", {
          x: D.tableX - 8, y: r[1], class: "kp-v-text is-sub", style: SMALL + ";text-anchor:end",
        }, r[0]));
      });
      var ups = {};
      (s.updates || []).forEach(function (u) { ups[u.to] = u; });
      for (var i = 0; i < n; i++) {
        var v = s.table[i];
        var conf = s.confirmed[i];
        var cls = ["kp-v-cell"];
        var tcls = ["kp-v-text"];
        var attrs = { x: cx(i) - CW / 2, y: top, width: CW, height: CH, rx: 6 };
        var isAns = s.answer && i === n - 1;
        if (isAns) { cls.push("is-answer"); tcls.push("is-on-answer"); }
        else if (conf) cls.push("is-yes");
        else { attrs["stroke-dasharray"] = "4 3"; tcls.push("is-dim"); }
        if (s.focus === i || ups[i]) cls.push("is-focus");
        attrs.class = cls.join(" ");
        svg.appendChild(h("rect", attrs));
        var txt = v === null ? (s.part === "push" ? "∞" : "?") : v;
        if (s.part === "tree" && v === null) txt = "";
        svg.appendChild(h("text", { x: cx(i), y: ly, class: tcls.join(" ") }, txt));
        svg.appendChild(h("text", { x: cx(i), y: top + CH + 13, class: "kp-v-text", style: SMALL }, hs[i]));
        svg.appendChild(h("text", { x: cx(i), y: top + CH + 31, class: "kp-v-text is-sub", style: SMALL }, i));
        if (ups[i]) {
          var u = ups[i];
          svg.appendChild(h("text", {
            x: cx(i), y: top + CH + 51, class: "kp-v-ptr is-b", style: "font-size:14px",
          }, (u.old === null ? "∞" : u.old) + "→" + u.now));
        }
      }
    }
  }

  return {
    title: "素朴な再帰の木で同じ足場の呼び出しが表の 1 マスにまとまる様子と、同じ表を貰う形・配る形で埋める様子",
    states: states,
    render: render,
    viewBox: viewBox,
    solve: solve,
  };
});

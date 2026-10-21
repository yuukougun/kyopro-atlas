/*
 * 動く図：Union-Find の併合（union by size）と find の経路圧縮（viz.js の部品で描く）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="union-find" data-config='{"n": 8, "ops": [{"type": "merge", "a": 0, "b": 1}, {"type": "find", "x": 1}]}'></div>
 * config：
 *   n   … 要素の数（1〜10）。要素は 0, 1, …, n − 1
 *   ops … 操作の列（1〜24 個）。{"type": "merge", "a", "b"} か {"type": "find", "x"}（どれも 0 以上 n 未満の整数）
 *
 * 配列 par 1 本で森を持つ。par[v] ≥ 0 なら v の親、par[v] < 0 なら v は根で −par[v] がグループの大きさである。
 * find(v) は親をたどって根を求め、帰りがけに通った要素の親を根に書き換える（経路圧縮）。
 * merge(a, b) は x = find(a)、y = find(b) を求め、違えば小さい方の根を大きい方の根の下につなぐ。
 * 大きさが同じなら a 側の根 x を残す（ACL の dsu と同じ）。
 *
 * 状態の列：初め → 操作ごとに
 *   merge：根を求める（たどった道を太線）→ 経路圧縮で親が変わったときだけ書き換え → つなぐ（または同じグループで何もしない）
 *   find ：始め → 親へ 1 段ずつ（最後の段で根に着く）→ 親が変わるときだけ経路圧縮
 * → 終わり（グループの数と par）。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/union-find.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("union-find", def);
})(function () {
  "use strict";

  var MAX_N = 10; // 幅 360 で節の番号が読める上限
  var MAX_OPS = 24;

  function isIndex(v, n) {
    return typeof v === "number" && Number.isInteger(v) && v >= 0 && v < n;
  }

  function validate(config) {
    if (!config || typeof config !== "object" || Array.isArray(config)) throw new Error("data-config がない");
    var n = config.n;
    if (typeof n !== "number" || !Number.isInteger(n) || n < 1 || n > MAX_N) {
      throw new Error("n は 1 以上 " + MAX_N + " 以下の整数にする");
    }
    var ops = config.ops;
    if (!Array.isArray(ops) || ops.length < 1 || ops.length > MAX_OPS) {
      throw new Error("ops は 1〜" + MAX_OPS + " 個の操作の配列にする");
    }
    var out = ops.map(function (op, k) {
      var where = "ops[" + k + "]";
      if (!op || typeof op !== "object" || Array.isArray(op)) throw new Error(where + " は操作のオブジェクトにする");
      if (op.type === "merge") {
        if (!isIndex(op.a, n) || !isIndex(op.b, n)) {
          throw new Error(where + "（merge）の a と b は 0 以上 n 未満の整数にする");
        }
        return { type: "merge", a: op.a, b: op.b };
      }
      if (op.type === "find") {
        if (!isIndex(op.x, n)) throw new Error(where + "（find）の x は 0 以上 n 未満の整数にする");
        return { type: "find", x: op.x };
      }
      throw new Error(where + ' の type は "merge" か "find" にする');
    });
    return { n: n, ops: out };
  }

  // 負の数は数学の負号（−）で書く
  function num(v) {
    return v < 0 ? "−" + -v : String(v);
  }

  function parText(par) {
    return "[" + par.map(num).join(", ") + "]";
  }

  function listText(vs) {
    return vs.join(" と ");
  }

  // v から根までの道（v と根を含む）
  function pathToRoot(par, v) {
    var p = [v];
    while (par[v] >= 0) {
      v = par[v];
      p.push(v);
    }
    return p;
  }

  // 道の上で、親を根に書き換える要素（根と根の子は除く）
  function toCompress(path) {
    return path.slice(0, Math.max(0, path.length - 2));
  }

  function countRoots(par) {
    return par.filter(function (v) { return v < 0; }).length;
  }

  function walkText(path) {
    if (path.length === 1) return path[0] + " は根なので、find(" + path[0] + ") = " + path[0];
    return path.join(" → ") + " と " + (path.length - 1) + " 回たどり、find(" + path[0] + ") = " + path[path.length - 1];
  }

  // 各状態：phase、op（操作の番号。初めと終わりは −1）、opText、par（その時点の配列）、
  //   focus（太枠の節）、path（たどった節）、pathEdges（たどった矢印の子）、newEdges（書き換えた矢印の子）、
  //   changed（par の値が変わった添字）、caption
  function states(config) {
    var c = validate(config);
    var n = c.n;
    var par = [];
    for (var i = 0; i < n; i++) par.push(-1);
    var out = [];

    function push(s) {
      out.push({
        phase: s.phase,
        op: s.op == null ? -1 : s.op,
        opText: s.opText || "",
        par: par.slice(),
        focus: s.focus || [],
        path: s.path || [],
        pathEdges: s.pathEdges || [],
        newEdges: s.newEdges || [],
        changed: s.changed || [],
        caption: s.caption,
      });
    }

    // 経路圧縮：書き換えた要素を返す
    function compress(path) {
      var root = path[path.length - 1];
      var ch = toCompress(path);
      ch.forEach(function (v) { par[v] = root; });
      return ch;
    }

    push({
      phase: "start",
      caption: n + " 個の要素が、それぞれ大きさ 1 のグループ（1 個だけの木の根）である。par はすべて −1 にする。",
    });

    c.ops.forEach(function (op, k) {
      if (op.type === "merge") {
        var a = op.a, b = op.b;
        var opText = "merge(" + a + ", " + b + ")";
        var pa = pathToRoot(par, a);
        var pb = pathToRoot(par, b);
        var x = pa[pa.length - 1], y = pb[pb.length - 1];
        var sx = -par[x], sy = -par[y];
        // 同じ根のとき、find(b) は a 側の経路圧縮の後にたどるので回数が変わりうる。b 側の道は出さない
        var nodes = [], edges = [];
        (x === y ? [pa] : [pa, pb]).forEach(function (p) {
          p.forEach(function (v, j) {
            if (nodes.indexOf(v) < 0) nodes.push(v);
            if (j + 1 < p.length && edges.indexOf(v) < 0) edges.push(v);
          });
        });
        var bText = x === y
          ? (a === b ? "find(" + b + ") も同じく " + y : "find(" + b + ") も同じ根 " + y + " を返す（a 側の経路圧縮の後にたどる）")
          : walkText(pb);
        var sizes = x === y ? "" : "大きさは根 " + x + " が " + sx + "、根 " + y + " が " + sy + " である。";
        push({
          phase: "merge-find", op: k, opText: opText,
          focus: x === y ? [x] : [x, y], path: nodes, pathEdges: edges,
          caption: opText + "：まず両方の根を求める。" + walkText(pa) + "。" + bText + "。" + sizes,
        });
        // find の帰りがけの経路圧縮（a 側、b 側の順）
        var chA = compress(pa);
        var chB = compress(pathToRoot(par, b));
        var ch = chA.slice();
        chB.forEach(function (v) { if (ch.indexOf(v) < 0) ch.push(v); });
        if (ch.length > 0) {
          var parts = [];
          if (chA.length > 0) {
            parts.push("find(" + a + ") の帰りがけに、通った " + listText(chA) + " の親を根 " + x + " に書き換えた（経路圧縮）。");
          }
          if (chB.length > 0) {
            parts.push("find(" + b + ") の帰りがけに、通った " + listText(chB) + " の親を根 " + y + " に書き換えた（経路圧縮）。");
          }
          push({
            phase: "merge-compress", op: k, opText: opText,
            focus: x === y ? [x] : [x, y], newEdges: ch, changed: ch,
            caption: parts.join(""),
          });
        }
        if (x === y) {
          push({
            phase: "merge-same", op: k, opText: opText, focus: [x],
            caption: "根がどちらも " + x + " なので、" + a + " と " + b + " はもう同じグループである。何もしない。",
          });
          return;
        }
        var keep = x, put = y, sk = sx, sp = sy;
        var how;
        if (sx < sy) {
          keep = y; put = x; sk = sy; sp = sx;
          how = "根 " + x + " の方が小さい（" + sx + " < " + sy + "）ので入れ替え、小さい方の根 " + put +
            " を大きい方の根 " + keep + " の下につなぐ。";
        } else if (sx > sy) {
          how = "小さい方の根 " + put + "（大きさ " + sp + "）を、大きい方の根 " + keep + "（大きさ " + sk + "）の下につなぐ。";
        } else {
          how = "大きさが同じ（" + sx + "）なので、a 側の根 " + keep + " を残し、根 " + put + " をその下につなぐ。";
        }
        var before = par[keep];
        par[keep] += par[put];
        par[put] = keep;
        push({
          phase: "merge-link", op: k, opText: opText,
          focus: [keep], newEdges: [put], changed: [keep, put],
          caption: how + "par[" + put + "] = " + keep + "、par[" + keep + "] = " + num(before) + " + (" + num(-sp) + ") = " +
            num(par[keep]) + " にする。グループは " + countRoots(par) + " 個になった。",
        });
      } else {
        var v = op.x;
        var fText = "find(" + v + ")";
        var p = pathToRoot(par, v);
        var root = p[p.length - 1];
        if (p.length === 1) {
          push({
            phase: "find-start", op: k, opText: fText, focus: [v], path: [v],
            caption: fText + "：par[" + v + "] = " + num(par[v]) + " < 0 なので、" + v + " 自身が根である。大きさは " + -par[v] + "。",
          });
          return;
        }
        push({
          phase: "find-start", op: k, opText: fText, focus: [v], path: [v],
          caption: fText + "：" + v + " から親をたどって根を探す。",
        });
        var willChange = toCompress(p);
        for (var j = 1; j < p.length; j++) {
          var cap = "par[" + p[j - 1] + "] = " + p[j] + " なので " + p[j] + " へ進む（" + j + " 回目）。";
          if (j === p.length - 1) {
            cap += "par[" + root + "] = " + num(par[root]) + " < 0 なので " + root + " が根である。" + fText + "：" +
              p.join(" → ") + " と " + (p.length - 1) + " 回たどって根 " + root + " を見つけた。";
            if (willChange.length === 0) cap += v + " はもともと根の子なので、書き換える親はない。";
          }
          push({
            phase: "find-step", op: k, opText: fText,
            focus: [p[j]], path: p.slice(0, j + 1), pathEdges: p.slice(0, j),
            caption: cap,
          });
        }
        if (willChange.length > 0) {
          compress(p);
          var direct = p[p.length - 2];
          push({
            phase: "find-compress", op: k, opText: fText,
            focus: [root], path: p, newEdges: willChange, changed: willChange,
            caption: "帰りがけに、通った " + listText(willChange) + " の親を根 " + root + " に書き換えた（経路圧縮）。" +
              direct + " はもともと根の子である。次からは " + listText(willChange) + " から 1 回たどるだけで根に着く。",
          });
        }
      }
    });

    var g = countRoots(par);
    push({
      phase: "end",
      focus: par.map(function (v, i) { return v < 0 ? i : -1; }).filter(function (i) { return i >= 0; }),
      caption: "すべての操作を終えた。グループは " + g + " 個で、par = " + parText(par) + "。",
    });
    return out;
  }

  // 森の配置：根は番号の小さい順、子も番号の小さい順。葉に 1 列ずつ割り当て、親は子の真ん中に置く
  function layout(par) {
    var n = par.length;
    var children = [];
    var i;
    for (i = 0; i < n; i++) children.push([]);
    var roots = [];
    for (i = 0; i < n; i++) {
      if (par[i] < 0) roots.push(i);
      else children[par[i]].push(i);
    }
    var col = new Array(n), depth = new Array(n);
    var leaf = 0, maxDepth = 0;
    function rec(v, d) {
      depth[v] = d;
      if (d > maxDepth) maxDepth = d;
      if (children[v].length === 0) {
        col[v] = leaf++;
        return;
      }
      children[v].forEach(function (cv) { rec(cv, d + 1); });
      var cs = children[v];
      col[v] = (col[cs[0]] + col[cs[cs.length - 1]]) / 2;
    }
    roots.forEach(function (r) { rec(r, 0); });
    return { col: col, depth: depth, leaves: leaf, maxDepth: maxDepth };
  }

  // 描画の寸法
  var SLOT = 44; // 木の列の幅と配列のマスの間隔
  var CELL = 38;
  var R = 15; // 節の半径
  var RING = 4; // 根の外側の輪
  var LEFT = 36; // 配列の行の名前の幅
  var RIGHT = 6;
  var DY = 54;
  var LINE = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.4";
  var LINE_PATH = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3.2";
  var LINE_NEW = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:3.2;stroke-dasharray:7 4";
  var SMALL = "font-size:12px";
  var MIN_W = 380; // 見出し「merge(9, 9)：根どうしをつなぐ（グループ 10 個）」と凡例が収まる幅

  function dims(config, sts) {
    var n = config.n;
    var md = 0;
    (sts || []).forEach(function (s) { md = Math.max(md, layout(s.par).maxDepth); });
    var inner = LEFT + n * SLOT + RIGHT;
    var width = Math.max(inner, MIN_W);
    // 上から見出し・配列 par・凡例・森の順に置く（森の高さはステップで変わるので、余白は下に寄せる）
    var arrTop = 38; // 添字の行
    var cellTop = arrTop + 10;
    var legendY = cellTop + CELL + 18;
    var treeTop = legendY + 26 + R + RING; // 根の中心
    return {
      n: n, width: width, ox: (width - inner) / 2 + LEFT, height: treeTop + md * DY + R + 8,
      arrTop: arrTop, cellTop: cellTop, legendY: legendY, treeTop: treeTop,
    };
  }

  // viewBox は全ステップの最大の深さで決め、ステップによらない
  function viewBox(config, sts) {
    var D = dims(config, sts || states(config));
    return "0 0 " + D.width + " " + D.height;
  }

  // 描くたびに全状態を作り直さないよう、config ごとに寸法を覚えておく
  var cache = typeof WeakMap === "function" ? new WeakMap() : null;
  function dimsFor(config) {
    var d = cache && cache.get(config);
    if (!d) {
      d = dims(config, states(config));
      if (cache) cache.set(config, d);
    }
    return d;
  }

  function render(svg, s, config, h) {
    var D = dimsFor(config);
    var n = D.n;
    var L = layout(s.par);
    var treeW = L.leaves * SLOT;
    var x0 = D.ox + (n * SLOT - treeW) / 2 + SLOT / 2;
    function nx(v) { return x0 + L.col[v] * SLOT; }
    function ny(v) { return D.treeTop + L.depth[v] * DY; }
    function has(arr, v) { return arr.indexOf(v) >= 0; }
    function isRoot(v) { return s.par[v] < 0; }

    function head(x, y, dx, dy, cls) {
      var len = Math.sqrt(dx * dx + dy * dy) || 1;
      var ux = dx / len, uy = dy / len, AL = 10, AW = 5;
      var bx = x - ux * AL, by = y - uy * AL;
      svg.appendChild(h("path", {
        d: "M" + x + " " + y + "L" + (bx - uy * AW) + " " + (by + ux * AW) + "L" + (bx + uy * AW) + " " + (by - ux * AW) + "Z",
        class: cls,
      }));
    }

    // 見出し：いまの操作
    var title = s.opText ? s.opText : s.phase === "start" ? "初め" : "終わり";
    var sub = {
      "merge-find": "根を求める", "merge-compress": "経路圧縮", "merge-link": "根どうしをつなぐ",
      "merge-same": "同じグループ", "find-start": "根を探す", "find-step": "親へ進む", "find-compress": "経路圧縮",
    }[s.phase];
    svg.appendChild(h("text", {
      x: D.width / 2, y: 14, class: "kp-v-ptr is-a", style: "font-size:15px",
    }, title + (sub ? "：" + sub : "") + "（グループ " + countRoots(s.par) + " 個）"));

    // 矢印：子から親へ。たどった矢印は太線、書き換えた矢印は太い破線
    for (var v = 0; v < n; v++) {
      if (isRoot(v)) continue;
      var p = s.par[v];
      var dx = nx(p) - nx(v), dy = ny(p) - ny(v);
      var len = Math.sqrt(dx * dx + dy * dy) || 1;
      var ux = dx / len, uy = dy / len;
      var rp = R + (isRoot(p) ? RING : 0) + 1;
      var sx = nx(v) + ux * R, sy = ny(v) + uy * R;
      var tx = nx(p) - ux * rp, ty = ny(p) - uy * rp;
      var isNew = has(s.newEdges, v), onPath = has(s.pathEdges, v);
      var style = isNew ? LINE_NEW : onPath ? LINE_PATH : LINE;
      svg.appendChild(h("path", { d: "M" + sx + " " + sy + "L" + (tx - ux * 8) + " " + (ty - uy * 8), style: style }));
      head(tx, ty, dx, dy, isNew || onPath ? "kp-v-mark is-b" : "kp-v-mark");
    }

    // 節：根は二重の輪、たどった節は塗り、いま注目する節は太枠
    for (var u = 0; u < n; u++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      if (has(s.path, u)) cls.push("is-yes");
      if (has(s.focus, u)) cls.push("is-focus");
      if (isRoot(u)) {
        svg.appendChild(h("circle", {
          cx: nx(u), cy: ny(u), r: R + RING, style: "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.4",
        }));
      }
      svg.appendChild(h("circle", { cx: nx(u), cy: ny(u), r: R, class: cls.join(" ") }));
      svg.appendChild(h("text", {
        x: nx(u), y: ny(u), class: tcls.join(" "), style: has(s.focus, u) ? "font-weight:700" : null,
      }, u));
    }

    // 配列 par：添字の行と値の行。値が変わったマスは太枠
    function ax(i) { return D.ox + i * SLOT + SLOT / 2; }
    svg.appendChild(h("text", {
      x: D.ox - 6, y: D.arrTop, class: "kp-v-text is-sub", style: "text-anchor:end",
    }, "v"));
    svg.appendChild(h("text", {
      x: D.ox - 6, y: D.cellTop + CELL / 2, class: "kp-v-text", style: "text-anchor:end;font-size:13px",
    }, "par"));
    for (var k = 0; k < n; k++) {
      var cc = ["kp-v-cell"];
      var ct = ["kp-v-text"];
      var changed = has(s.changed, k);
      if (changed) cc.push("is-focus");
      svg.appendChild(h("text", { x: ax(k), y: D.arrTop, class: "kp-v-text is-sub" }, k));
      svg.appendChild(h("rect", {
        x: ax(k) - CELL / 2, y: D.cellTop, width: CELL, height: CELL, rx: 5, class: cc.join(" "),
      }));
      svg.appendChild(h("text", {
        x: ax(k), y: D.cellTop + CELL / 2, class: ct.join(" "), style: changed ? "font-weight:700" : null,
      }, num(s.par[k])));
    }

    // 凡例（線の形で区別する）
    var lx = (D.width - 276) / 2; // 凡例の全体の幅は約 276
    var ly = D.legendY;
    svg.appendChild(h("path", { d: "M" + lx + " " + ly + "h22", style: LINE_PATH }));
    svg.appendChild(h("text", { x: lx + 28, y: ly, class: "kp-v-text is-sub", style: SMALL + ";text-anchor:start" }, "たどった矢印"));
    lx += 28 + 84;
    svg.appendChild(h("path", { d: "M" + lx + " " + ly + "h22", style: LINE_NEW }));
    svg.appendChild(h("text", { x: lx + 28, y: ly, class: "kp-v-text is-sub", style: SMALL + ";text-anchor:start" }, "書き換えた矢印"));
    lx += 28 + 96;
    svg.appendChild(h("circle", { cx: lx + 10, cy: ly, r: 6, style: "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.2" }));
    svg.appendChild(h("circle", { cx: lx + 10, cy: ly, r: 3, style: "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.2" }));
    svg.appendChild(h("text", { x: lx + 22, y: ly, class: "kp-v-text is-sub", style: SMALL + ";text-anchor:start" }, "根"));
  }

  return {
    title: "Union-Find：union by size の併合と find の経路圧縮",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

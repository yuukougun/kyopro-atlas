/*
 * 動く図：2 回の最遠点探索で木の直径を求める（double sweep）
 *
 * 本文での書き方：
 *   <div class="kp-viz" data-viz="tree-diameter" data-config='{"n": 9, "edges": [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [2, 6], [6, 7], [3, 8]], "start": 7}'></div>
 * config：
 *   n     … 頂点数（1〜12）。頂点は 0-indexed
 *   edges … 長さ n − 1 の配列で、各要素は辺の両端 [u, v]（0 以上 n 未満の整数、u ≠ v）。全体で木（連結で閉路なし）にする。
 *           重みはない（どの辺も長さ 1）
 *   start … 1 回目の探索を始める頂点 s（省略すると 0）
 *   幅 360 で読めるよう、s を根にした描き方の葉の数と、直径を横一列に並べた描き方の列の数がどちらも 7 以下でなければ Error にする
 *
 * ① s から距離を層ごとに求め、最も遠い点を a とする。② a から距離を求め直し、最も遠い点を b とする。
 * a–b のパスが直径である。最も遠い点が複数あるときは、本文のコード（max_element）と同じく番号の最も小さいものを選ぶ。
 * 最後に直径を横一列に並べ直し、残りの頂点を枝としてぶら下げた形にする（本文の静的な図 spine.svg と同じ描き方）。
 *
 * states(config) は DOM を使わない純粋な関数で、tests/viz/tree-diameter.test.mjs が Node で試験する。
 */
(function (factory) {
  var def = factory();
  if (typeof module === "object" && module && module.exports) module.exports = def;
  if (typeof window !== "undefined" && window.KPViz) window.KPViz.register("tree-diameter", def);
})(function () {
  "use strict";

  var MAX_N = 12;
  var MAX_COLS = 7; // 列 7 つで viewBox の幅 472（幅 360 で約 0.76 倍）

  function isInt(x) { return typeof x === "number" && Number.isInteger(x); }

  function validate(config) {
    if (!config || typeof config !== "object" || Array.isArray(config)) throw new Error("data-config がない");
    var n = config.n;
    if (!isInt(n) || n < 1 || n > MAX_N) throw new Error("n は 1〜" + MAX_N + " の整数にする");
    var e = config.edges;
    if (!Array.isArray(e) || e.length !== n - 1) throw new Error("edges は長さ n − 1（" + (n - 1) + "）の配列にする");
    var adj = [];
    var uf = [];
    for (var i = 0; i < n; i++) { adj.push([]); uf.push(i); }
    function find(x) { while (uf[x] !== x) x = uf[x] = uf[uf[x]]; return x; }
    for (i = 0; i < e.length; i++) {
      var ed = e[i];
      if (!Array.isArray(ed) || ed.length !== 2 || !isInt(ed[0]) || !isInt(ed[1]) ||
          ed[0] < 0 || ed[0] >= n || ed[1] < 0 || ed[1] >= n) {
        throw new Error("edges[" + i + "] は 0 以上 n 未満の 2 頂点 [u, v] にする");
      }
      if (ed[0] === ed[1]) throw new Error("edges[" + i + "] が自己ループになっている");
      var ru = find(ed[0]), rv = find(ed[1]);
      if (ru === rv) throw new Error("edges[" + i + "]（" + ed[0] + "–" + ed[1] + "）で閉路ができる。木にする");
      uf[ru] = rv;
      adj[ed[0]].push(ed[1]);
      adj[ed[1]].push(ed[0]);
    }
    for (i = 0; i < n; i++) adj[i].sort(function (x, y) { return x - y; });
    var s = config.start == null ? 0 : config.start;
    if (!isInt(s) || s < 0 || s >= n) throw new Error("start は 0 以上 n 未満の整数にする");
    return { n: n, edges: e.map(function (p) { return [p[0], p[1]]; }), adj: adj, start: s };
  }

  // 1 点からの距離（重みなし）と親。BFS で層の順に求める
  function bfs(c, src) {
    var dist = new Array(c.n).fill(-1);
    var par = new Array(c.n).fill(-1);
    dist[src] = 0;
    var q = [src];
    for (var h = 0; h < q.length; h++) {
      var v = q[h];
      c.adj[v].forEach(function (to) {
        if (dist[to] !== -1) return;
        dist[to] = dist[v] + 1;
        par[to] = v;
        q.push(to);
      });
    }
    return { dist: dist, par: par };
  }

  // 最も遠い点（同点なら番号の最も小さいもの。max_element と同じ）と、同点の候補
  function farthest(dist) {
    var best = 0;
    for (var v = 1; v < dist.length; v++) if (dist[v] > dist[best]) best = v;
    var cands = [];
    for (v = 0; v < dist.length; v++) if (dist[v] === dist[best]) cands.push(v);
    return { v: best, d: dist[best], cands: cands };
  }

  function listJa(xs) {
    if (xs.length <= 1) return String(xs[0]);
    return xs.slice(0, -1).join("・") + " と " + xs[xs.length - 1];
  }

  // 直径（a から b への頂点列）と、その各頂点からぶら下がる枝
  function spineOf(c, a, b, par2) {
    var path = [];
    for (var v = b; v !== -1; v = par2[v]) path.push(v);
    path.reverse(); // a → b
    var onPath = new Array(c.n).fill(false);
    path.forEach(function (x) { onPath[x] = true; });
    // 枝の中の頂点の付け根と深さ
    var root = new Array(c.n).fill(-1);
    var depth = new Array(c.n).fill(0);
    path.forEach(function (r) {
      root[r] = r;
      var st = [r];
      while (st.length) {
        var x = st.pop();
        c.adj[x].forEach(function (to) {
          if (onPath[to] || root[to] !== -1) return;
          root[to] = r;
          depth[to] = depth[x] + 1;
          st.push(to);
        });
      }
    });
    var D = path.length - 1;
    var branches = [];
    path.forEach(function (r, i) {
      var h = 0;
      for (var x = 0; x < c.n; x++) if (root[x] === r) h = Math.max(h, depth[x]);
      if (h > 0) branches.push({ at: r, depth: h, near: Math.min(i, D - i) });
    });
    return { path: path, onPath: onPath, root: root, depth: depth, branches: branches };
  }

  // 状態：sweep（1・2・3。3 は並べ直した図）、phase（start・layer・far・path・spine）、src（探索の始点）、
  //   dist（いまの探索で求まった距離。未定は null）、layer（いま求めた距離。なければ null）、
  //   cands（最も遠い点の候補）、a・b（決まった端点。未定は null）、path（直径の頂点列。未定は空）、caption
  function states(config) {
    var c = dims(config).c; // 幅の制限もここで確かめる（viewBox より先に呼ばれ、誤りを図の代わりに出せる）
    var n = c.n, s = c.start;
    var out = [];
    var a = null, b = null, path = [];

    function sweep(no, src) {
      var r = bfs(c, src);
      var maxD = Math.max.apply(null, r.dist);
      var shown = new Array(n).fill(null);
      shown[src] = 0;
      function push(o) {
        o.sweep = no;
        o.src = src;
        o.dist = shown.slice();
        o.a = a;
        o.b = b;
        o.path = path.slice();
        if (o.layer == null) o.layer = null;
        if (!o.cands) o.cands = [];
        out.push(o);
      }
      push({
        phase: "start",
        caption: no === 1
          ? "1 回目の探索：適当な点 s = " + src + " から各頂点への距離を求める。s の距離は 0 である。"
          : "2 回目の探索：a = " + src + " から各頂点への距離を求め直す。a の距離は 0 である。",
      });
      for (var k = 1; k <= maxD; k++) {
        var layer = [];
        for (var v = 0; v < n; v++) if (r.dist[v] === k) { shown[v] = k; layer.push(v); }
        push({
          phase: "layer", layer: k,
          caption: "距離 " + k + " の頂点は " + listJa(layer) + " である（距離 " + (k - 1) + " の頂点の隣で、まだ距離のない頂点）。",
        });
      }
      return r;
    }

    // ① 1 回目
    var r1 = sweep(1, s);
    var f1 = farthest(r1.dist);
    a = f1.v;
    var cap1;
    if (n === 1) {
      cap1 = "頂点は s = " + s + " だけなので、最も遠い点も " + s + "（距離 0）である。a = " + a + " とする。";
    } else if (f1.cands.length === 1) {
      cap1 = "1 回目の探索が終わった。最も遠いのは距離 " + f1.d + " の頂点 " + a + " なので、a = " + a +
        " とする。どの点から始めても、最も遠い点は直径の端点になる。";
    } else {
      cap1 = "1 回目の探索が終わった。最も遠いのは距離 " + f1.d + " の頂点 " + listJa(f1.cands) + " で、番号の小さい " + a +
        " を a とする。どれを選んでも直径の端点になる。";
    }
    out.push({
      sweep: 1, phase: "far", src: s, dist: r1.dist.slice(), layer: null, cands: f1.cands, a: a, b: null, path: [],
      caption: cap1,
    });

    // ② 2 回目
    var r2 = sweep(2, a);
    var f2 = farthest(r2.dist);
    b = f2.v;
    var cap2;
    if (n === 1) {
      cap2 = "2 回目も最も遠い点は " + a + " 自身（距離 0）なので、b = " + b + " とする。";
    } else if (f2.cands.length === 1) {
      cap2 = "2 回目の探索が終わった。最も遠いのは距離 " + f2.d + " の頂点 " + b + " なので、b = " + b + " とする。";
    } else {
      cap2 = "2 回目の探索が終わった。最も遠いのは距離 " + f2.d + " の頂点 " + listJa(f2.cands) + " で、番号の小さい " + b +
        " を b とする。" +
        listJa(f2.cands.filter(function (x) { return x !== b; })) + " を選んでも長さ " + f2.d + " の直径になる。";
    }
    out.push({
      sweep: 2, phase: "far", src: a, dist: r2.dist.slice(), layer: null, cands: f2.cands, a: a, b: b, path: [],
      caption: cap2,
    });
    var sp = spineOf(c, a, b, r2.par);
    path = sp.path;
    var D = path.length - 1;
    out.push({
      sweep: 2, phase: "path", src: a, dist: r2.dist.slice(), layer: null, cands: [], a: a, b: b, path: path.slice(),
      caption: n === 1
        ? "直径は頂点 " + a + " だけで、長さは 0 である。"
        : "a から b へのパス " + path.join("–") + " が直径で、長さは " + D + " である（2 回目の探索の親を b からたどると求まる）。",
    });

    // 並べ直した図
    var cap3 = "直径 " + path.join("–") + " を横一列に並べ、残りの頂点を枝としてぶら下げた。";
    if (sp.branches.length === 0) {
      cap3 += "枝はない。";
    } else {
      cap3 += "どの枝も、付け根から近い方の端までの長さより深くない（" + sp.branches.map(function (br) {
        return "頂点 " + br.at + " の枝は深さ " + br.depth + " ≤ " + br.near;
      }).join("、") + "）。";
    }
    out.push({
      sweep: 3, phase: "spine", src: a, dist: r2.dist.slice(), layer: null, cands: [], a: a, b: b, path: path.slice(),
      branches: sp.branches, caption: cap3,
    });
    return out;
  }

  // 描画の寸法
  var PITCH = 60; // 列の間隔
  var DY = 52; // 段の間隔
  var R = 16; // 頂点の半径
  var SIDE = 40; // 左右の余白（名札と距離の数の分）
  var MIN_W = 380;
  var TOP1 = 48; // 木の描き方の一番上の段
  var TOP2 = 76; // 並べ直した図の直径の段（上に長さの目盛り）
  var LINE = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.4";
  var LINE_ON = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:5;stroke-linecap:round";
  var LINE_BRANCH = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.6;stroke-dasharray:6 4";
  var RING_CMP = "fill:none;stroke:var(--md-accent-fg-color);stroke-width:2.5;stroke-dasharray:5 3";
  var MEASURE = "fill:none;stroke:var(--md-default-fg-color--light);stroke-width:1.4";
  var HALO = "paint-order:stroke;stroke:var(--md-default-bg-color);stroke-width:4px;stroke-linejoin:round";

  // s を根にした描き方：子を番号の順に並べ、葉を左から 1 列ずつ、内側の頂点は最初と最後の子の真ん中
  function rootedLayout(c) {
    var n = c.n;
    var ch = [], dep = new Array(n).fill(0);
    for (var i = 0; i < n; i++) ch.push([]);
    var seen = new Array(n).fill(false);
    var order = [c.start];
    seen[c.start] = true;
    for (var h = 0; h < order.length; h++) {
      var v = order[h];
      c.adj[v].forEach(function (to) {
        if (seen[to]) return;
        seen[to] = true;
        ch[v].push(to);
        dep[to] = dep[v] + 1;
        order.push(to);
      });
    }
    var col = new Array(n).fill(0);
    var leaves = 0;
    var stack = [[c.start, 0]];
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
    return { col: col, row: dep, cols: leaves, rows: Math.max.apply(null, dep) + 1 };
  }

  // 並べ直した描き方：直径の各頂点に、ぶら下がる枝の葉の数（1 以上）だけ列を割り当てる
  function spineLayout(c, sp) {
    var n = c.n;
    var col = new Array(n).fill(0), row = new Array(n).fill(0);
    var ch = [];
    for (var i = 0; i < n; i++) ch.push([]);
    // 枝の中の親子（付け根から外へ）
    sp.path.forEach(function (r) {
      var st = [r], seen = {};
      seen[r] = true;
      while (st.length) {
        var x = st.pop();
        c.adj[x].forEach(function (to) {
          if (sp.onPath[to] || seen[to]) return;
          seen[to] = true;
          ch[x].push(to);
          st.push(to);
        });
      }
    });
    for (i = 0; i < n; i++) ch[i].sort(function (x, y) { return x - y; });
    var next = 0;
    var maxRow = 0;
    function place(x, d) {
      row[x] = d;
      maxRow = Math.max(maxRow, d);
      if (ch[x].length === 0) { col[x] = next++; return; }
      ch[x].forEach(function (y) { place(y, d + 1); });
      col[x] = (col[ch[x][0]] + col[ch[x][ch[x].length - 1]]) / 2;
    }
    sp.path.forEach(function (r) {
      if (ch[r].length === 0) { col[r] = next++; return; }
      place(r, 0);
    });
    return { col: col, row: row, cols: next, rows: maxRow + 1 };
  }

  function dims(config) {
    var c = validate(config);
    var lay1 = rootedLayout(c);
    if (lay1.cols > MAX_COLS) {
      throw new Error("s = " + c.start + " を根にすると葉が " + lay1.cols + " 個ある。幅 360 で読めるよう " + MAX_COLS + " 個までにする");
    }
    var a = farthest(bfs(c, c.start).dist).v;
    var r2 = bfs(c, a);
    var b = farthest(r2.dist).v;
    var sp = spineOf(c, a, b, r2.par);
    var lay2 = spineLayout(c, sp);
    if (lay2.cols > MAX_COLS) {
      throw new Error("直径を横一列に並べると " + lay2.cols + " 列になる。幅 360 で読めるよう " + MAX_COLS + " 列まで（直径の長さ 6 以下で、枝の葉も含めて）にする");
    }
    function w(cols) { return 2 * SIDE + (cols - 1) * PITCH + 2 * R; }
    var width = Math.max(MIN_W, w(lay1.cols), w(lay2.cols));
    var h1 = TOP1 + (lay1.rows - 1) * DY + R + 14;
    var h2 = TOP2 + (lay2.rows - 1) * DY + R + 14;
    return { c: c, lay1: lay1, lay2: lay2, sp: sp, width: width, height: Math.max(h1, h2) };
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
    var c = D.c, n = c.n;
    var spine = s.phase === "spine";
    var lay = spine ? D.lay2 : D.lay1;
    var x0 = (D.width - (lay.cols - 1) * PITCH) / 2;
    // 並べ直した図は木の描き方より低いことが多いので、上下の真ん中に置く
    var top = spine ? TOP2 + Math.max(0, (D.height - (TOP2 + (lay.rows - 1) * DY + R + 14)) / 2) : TOP1;
    function nx(v) { return x0 + lay.col[v] * PITCH; }
    function ny(v) { return top + lay.row[v] * DY; }

    var onPath = new Array(n).fill(false);
    s.path.forEach(function (v) { onPath[v] = true; });
    var pathEdge = {};
    for (var i = 0; i + 1 < s.path.length; i++) {
      pathEdge[Math.min(s.path[i], s.path[i + 1]) + "-" + Math.max(s.path[i], s.path[i + 1])] = true;
    }

    // 見出し
    var title = spine ? "直径を横一列に並べ直す"
      : s.sweep === 1 ? "① s = " + s.src + " から最も遠い点 a を探す"
        : "② a = " + s.src + " から最も遠い点 b を探す";
    svg.appendChild(h("text", { x: D.width / 2, y: 14, class: "kp-v-ptr is-a", style: "font-size:16px" }, title));

    // 辺：直径は太線、並べ直した図の枝は破線
    c.edges.forEach(function (e) {
      var on = pathEdge[Math.min(e[0], e[1]) + "-" + Math.max(e[0], e[1])];
      svg.appendChild(h("line", {
        x1: nx(e[0]), y1: ny(e[0]), x2: nx(e[1]), y2: ny(e[1]),
        style: on ? LINE_ON : spine ? LINE_BRANCH : LINE,
      }));
    });

    // 並べ直した図：直径の長さの目盛り
    if (spine && s.path.length > 1) {
      var lx = nx(s.path[0]), rx = nx(s.path[s.path.length - 1]), my = top - R - 14;
      svg.appendChild(h("path", {
        d: "M" + lx + " " + (my - 5) + "V" + (my + 5) + "M" + lx + " " + my + "H" + rx + "M" + rx + " " + (my - 5) + "V" + (my + 5),
        style: MEASURE,
      }));
      svg.appendChild(h("text", {
        x: (lx + rx) / 2, y: my - 11, class: "kp-v-ptr is-b", style: "font-size:14px;" + HALO,
      }, "直径の長さ " + (s.path.length - 1)));
    }

    // 最も遠い点の候補（破線の輪）
    s.cands.forEach(function (v) {
      svg.appendChild(h("circle", { cx: nx(v), cy: ny(v), r: R + 6, style: RING_CMP }));
    });

    // 頂点
    for (var v = 0; v < n; v++) {
      var cls = ["kp-v-cell"];
      var tcls = ["kp-v-text"];
      var end = (s.phase === "far" && s.sweep === 1 && v === s.a) ||
        (s.phase === "far" && s.sweep === 2 && v === s.b) ||
        ((s.phase === "path" || spine) && (v === s.a || v === s.b));
      var known = s.dist[v] != null;
      if (end) { cls.push("is-answer"); tcls.push("is-on-answer"); }
      else if (spine ? onPath[v] : known) cls.push("is-yes");
      if (s.phase === "layer" && s.dist[v] === s.layer) cls.push("is-focus");
      if (s.phase === "start" && v === s.src) cls.push("is-focus");
      // 下地を塗ってから頂点を描く（半透明の塗りの下に辺が透けて数字に重ならないように）
      svg.appendChild(h("circle", { cx: nx(v), cy: ny(v), r: R, style: "fill:var(--md-default-bg-color)" }));
      svg.appendChild(h("circle", { cx: nx(v), cy: ny(v), r: R, class: cls.join(" ") }));
      svg.appendChild(h("text", {
        x: nx(v), y: ny(v), class: tcls.join(" "), style: end || cls.indexOf("is-focus") >= 0 ? "font-weight:700" : null,
      }, v));
      // 距離の数（右下）。並べ直した図では出さない
      if (!spine && known) {
        svg.appendChild(h("text", {
          x: nx(v) + R + 7, y: ny(v) + R, class: "kp-v-ptr is-b",
          style: "font-size:15px;text-anchor:start;" + HALO,
        }, s.dist[v]));
      }
      // 名札（左上）：s・a・b
      var tags = [];
      if (s.sweep === 1 && v === s.src) tags.push("s");
      if (s.a === v && (s.sweep > 1 || s.phase === "far")) tags.push("a");
      if (s.b === v) tags.push("b");
      if (tags.length) {
        svg.appendChild(h("text", {
          x: nx(v) - R - 7, y: ny(v) - R - 1, class: "kp-v-ptr is-focus",
          style: "font-size:15px;text-anchor:end;" + HALO,
        }, tags.join("=")));
      }
    }
  }

  return {
    title: "2 回の最遠点探索で木の直径を求める",
    states: states,
    render: render,
    viewBox: viewBox,
  };
});

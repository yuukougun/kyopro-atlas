// 動く図 warshall-floyd（ワーシャルフロイド法の表の更新）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/warshall-floyd.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/warshall-floyd.js", import.meta.url);

function loadViz(name) {
  const registered = new Map();
  const window = { KPViz: { register: (n, def) => registered.set(n, def) } };
  vm.runInNewContext(readFileSync(SRC, "utf8"), { window }, { filename: SRC.pathname });
  const def = registered.get(name);
  assert.ok(def, `${name} が登録されない`);
  assert.equal(typeof def.states, "function");
  assert.equal(typeof def.render, "function");
  return def;
}

const viz = loadViz("warshall-floyd");

// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
const run = (config) => structuredClone(viz.states(config));

// 本文（docs/graph/warshall-floyd.md）の 2 つの config
const EDGES = [[0, 1, 5], [0, 3, 1], [3, 2, 1], [2, 1, 1], [1, 0, 2]];
const POS = [[0, 0], [1, 0], [1, 1], [0, 1]];
const PAGE1 = { n: 4, directed: true, edges: EDGES, pos: POS };
const PAGE2 = { n: 4, directed: true, order: "ijk", edges: EDGES, pos: POS };

test("試験の config は本文の div と同じ", () => {
  const md = readFileSync(new URL("../../docs/graph/warshall-floyd.md", import.meta.url), "utf8");
  const configs = [...md.matchAll(/data-viz="warshall-floyd" data-config='([^']*)'/g)].map((m) => JSON.parse(m[1]));
  assert.deepEqual(configs, [PAGE1, PAGE2]);
});

// 正しい全点対の最短距離（各頂点からベルマンフォード法。届かなければ null）
function allPairs(c) {
  const arcs = [];
  for (const [u, v, w] of c.edges) {
    arcs.push([u, v, w]);
    if (!c.directed) arcs.push([v, u, w]);
  }
  const res = [];
  for (let s = 0; s < c.n; s++) {
    const dist = new Array(c.n).fill(null);
    dist[s] = 0;
    for (let it = 0; it < c.n; it++) {
      for (const [u, v, w] of arcs) {
        if (dist[u] !== null && (dist[v] === null || dist[u] + w < dist[v])) dist[v] = dist[u] + w;
      }
    }
    res.push(dist);
  }
  return res;
}

function hasNegCycle(c) {
  const arcs = [];
  for (const [u, v, w] of c.edges) {
    arcs.push([u, v, w]);
    if (!c.directed) arcs.push([v, u, w]);
  }
  const dist = new Array(c.n).fill(0);
  for (let it = 0; it <= c.n; it++) {
    let ch = false;
    for (const [u, v, w] of arcs) if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; ch = true; }
    if (!ch) return false;
  }
  return true;
}

function checkCommon(sts) {
  assert.equal(sts[0].phase, "init");
  for (const [k, s] of sts.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(!/undefined|NaN|null/.test(s.caption + s.formula), `状態 ${k}: caption に undefined・NaN・null`);
    assert.equal(s.last, k === sts.length - 1);
  }
}

test("本文の例（k, i, j の順）：各段の変化と最後の表が本文と一致する", () => {
  const sts = run(PAGE1);
  checkCommon(sts);
  // 最初は辺だけの表
  assert.deepEqual(sts[0].d, [[0, 5, null, 1], [2, 0, null, null], [null, 1, 0, null], [null, null, 1, 0]]);
  // 初期 1 + 各段（始まり 1 + マス 6）× 4
  assert.equal(sts.length, 1 + 4 * 7);
  // 段ごとに更新したマスと値（本文の箇条書き）
  const byK = [[], [], [], []];
  for (const s of sts) {
    if (s.phase === "cell" && s.updated) byK[s.k].push([s.i, s.j, s.d[s.i][s.j]]);
  }
  const sortCells = (a) => a.slice().sort((x, y) => x[0] - y[0] || x[1] - y[1]);
  assert.deepEqual(sortCells(byK[0]), [[1, 3, 3]]);
  assert.deepEqual(sortCells(byK[1]), [[2, 0, 3], [2, 3, 4]]);
  assert.deepEqual(sortCells(byK[2]), [[3, 0, 4], [3, 1, 2]]);
  assert.deepEqual(sortCells(byK[3]), [[0, 1, 3], [0, 2, 2], [1, 2, 4]]);
  // d[0][1] は k = 3 で 5 → 3（d[0][3] + d[3][1] = 1 + 2）
  const s01 = sts.find((s) => s.phase === "cell" && s.k === 3 && s.i === 0 && s.j === 1);
  assert.deepEqual([s01.old, s01.a, s01.b, s01.cand, s01.updated], [5, 1, 2, 3, true]);
  assert.equal(s01.formula, "d[0][1] = min(5, 1 + 2) = 3（更新）");
  // 最後の表は本文の表
  assert.deepEqual(sts.at(-1).d, [[0, 3, 2, 1], [2, 0, 4, 3], [3, 1, 0, 4], [4, 2, 1, 0]]);
  assert.deepEqual(sts.at(-1).d, allPairs(PAGE1));
  assert.match(sts.at(-1).caption, /k = 3 の段で変わったのは d\[0\]\[1\]・d\[0\]\[2\]・d\[1\]\[2\] である。/);
  assert.match(sts.at(-1).caption, /全点対の最短距離/);
  // 段の始まりの状態
  const ks = sts.filter((s) => s.phase === "k").map((s) => s.k);
  assert.deepEqual(ks, [0, 1, 2, 3]);
  // k 行目・k 列目・対角のマスは比べない
  for (const s of sts) if (s.phase === "cell") assert.ok(s.i !== s.j && s.i !== s.k && s.j !== s.k);
  // changed はその段で更新したマスだけを、更新した順に持つ
  const lastOfK1 = sts.filter((s) => s.phase === "cell" && s.k === 1).at(-1);
  assert.deepEqual(lastOfK1.changed, [[2, 0], [2, 3]]);
  assert.deepEqual(sts.find((s) => s.phase === "k" && s.k === 2).changed, []);
  // ∞ を経由する候補の説明
  const inf = sts.find((s) => s.phase === "cell" && s.k === 0 && s.i === 1 && s.j === 2);
  assert.equal(inf.cand, null);
  assert.match(inf.caption, /d\[0\]\[2\] が ∞ なので/);
});

test("本文の確認問題（i, j, k の順）：d[0][1] が 5 のまま残る", () => {
  const sts = run(PAGE2);
  checkCommon(sts);
  assert.equal(sts.length, 1 + 4 * 3);
  const s01 = sts.find((s) => s.i === 0 && s.j === 1);
  assert.equal(s01.updated, false);
  assert.deepEqual(s01.cands.map((x) => [x.k, x.a, x.b]), [[2, null, 1], [3, 1, null]]);
  assert.equal(s01.formula, "d[0][1] = min(5, ∞ + 1, 1 + ∞) = 5");
  const last = sts.at(-1);
  assert.deepEqual(last.d, [[0, 5, 2, 1], [2, 0, 4, 3], [3, 1, 0, 4], [4, 2, 1, 0]]);
  assert.deepEqual(last.wrong, [[0, 1, 3]]);
  assert.match(last.caption, /d\[0\]\[1\] が 5（正しくは 3）/);
  // k = i・k = j を除く理由を最初のマスで述べる
  assert.match(s01.caption, /k = 0（= i）と k = 1（= j）の候補は d\[0\]\[0\] \+ d\[0\]\[1\] のように今の d\[0\]\[1\] そのものなので除く。/);
  assert.ok(sts.slice(2).every((s) => !/そのものなので除く/.test(s.caption)));
  // 行の順に 1 マスずつ
  assert.deepEqual(sts.slice(1).map((s) => [s.i, s.j]),
    [[0, 1], [0, 2], [0, 3], [1, 0], [1, 2], [1, 3], [2, 0], [2, 1], [2, 3], [3, 0], [3, 1], [3, 2]]);
});

test("端の場合：頂点 1 つ・2 つ、辺なし、届かない組、無向、負の辺、重み 0", () => {
  let sts = run({ n: 1 });
  assert.deepEqual(sts.map((s) => s.phase), ["init", "k"]);
  assert.deepEqual(sts.at(-1).d, [[0]]);
  assert.ok(sts.at(-1).last);
  assert.match(sts.at(-1).caption, /全点対の最短距離/);

  sts = run({ n: 2, directed: true, edges: [[0, 1, 3]] });
  assert.deepEqual(sts.map((s) => s.phase), ["init", "k", "k"]);
  assert.deepEqual(sts.at(-1).d, [[0, 3], [null, 0]]);
  assert.match(sts[1].caption, /ほかに比べるマスはない/);

  sts = run({ n: 3 });
  checkCommon(sts);
  assert.ok(sts.every((s) => !s.updated));
  assert.deepEqual(sts.at(-1).d, [[0, null, null], [null, 0, null], [null, null, 0]]);
  assert.match(sts.at(-1).caption, /変わったマスはない/);

  // 無向：両向きに書く
  const und = { n: 3, edges: [[0, 1, 2], [1, 2, 3]] };
  sts = run(und);
  assert.deepEqual(sts[0].d, [[0, 2, null], [2, 0, 3], [null, 3, 0]]);
  assert.deepEqual(sts.at(-1).d, [[0, 2, 5], [2, 0, 3], [5, 3, 0]]);

  // 負の辺（負閉路なし）と重み 0。同じ値の候補では更新しない
  const neg = { n: 4, directed: true, edges: [[0, 1, 4], [0, 2, 1], [2, 1, -3], [1, 0, 3], [2, 3, 0]] };
  sts = run(neg);
  assert.deepEqual(sts.at(-1).d, allPairs(neg));
  assert.ok(sts.some((s) => s.formula.includes("1 − 3")));
  const eq = run({ n: 3, directed: true, edges: [[0, 1, 1], [1, 2, 1], [0, 2, 2]] });
  const c02 = eq.find((s) => s.phase === "cell" && s.i === 0 && s.j === 2);
  assert.equal(c02.updated, false);
  assert.match(c02.caption, /2 は今の 2 と同じなので、2 のまま。/);

  // 有向で両向きの辺（u → v と v → u）は受け付ける
  assert.doesNotThrow(() => run({ n: 2, directed: true, edges: [[0, 1, 1], [1, 0, 1]] }));
});

test("ランダムなグラフで、最後の表が全点対の最短距離と一致し、ijk の × が正しい表との違いと一致する", () => {
  let seed = 12345;
  const rnd = (m) => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed % m;
  };
  let checked = 0;
  for (let t = 0; t < 3000; t++) {
    const n = 1 + rnd(6);
    const directed = rnd(3) !== 0;
    const edges = [];
    const seen = new Set();
    const m = rnd(Math.min(15, n * (n - 1)) + 1);
    for (let e = 0; e < m * 2 && edges.length < m; e++) {
      const u = rnd(n), v = rnd(n);
      if (u === v) continue;
      const key = directed ? `${u}>${v}` : `${Math.min(u, v)}-${Math.max(u, v)}`;
      if (seen.has(key)) continue;
      seen.add(key);
      const w = directed && rnd(4) === 0 ? -1 - rnd(9) : rnd(20);
      edges.push([u, v, w]);
    }
    const c = { n, directed, edges };
    if (hasNegCycle(c)) {
      assert.throws(() => viz.states(c), /負閉路/);
      continue;
    }
    const truth = allPairs(c);
    const sts = run(c);
    checkCommon(sts);
    assert.deepEqual(sts.at(-1).d, truth);
    // 各マスの説明と値が合っている
    for (let q = 1; q < sts.length; q++) {
      const s = sts[q], prev = sts[q - 1].d;
      if (s.phase !== "cell") {
        assert.deepEqual(s.d, prev);
        continue;
      }
      assert.equal(s.a, prev[s.i][s.k]);
      assert.equal(s.b, prev[s.k][s.j]);
      assert.equal(s.old, prev[s.i][s.j]);
      const cand = s.a === null || s.b === null ? null : s.a + s.b;
      assert.equal(s.cand, cand);
      const up = cand !== null && (s.old === null || cand < s.old);
      assert.equal(s.updated, up);
      const want = prev.map((r) => r.slice());
      if (up) want[s.i][s.j] = cand;
      assert.deepEqual(s.d, want);
    }
    // ijk：最後の表と正しい表の違いが wrong
    const wr = run({ ...c, order: "ijk" });
    checkCommon(wr);
    const last = wr.at(-1);
    const diff = [];
    for (let i = 0; i < n; i++) for (let j = 0; j < n; j++) if (last.d[i][j] !== truth[i][j]) diff.push([i, j, truth[i][j]]);
    assert.deepEqual(last.wrong, diff);
    // ijk の値は正しい値以上（短すぎる値は出ない）
    for (let i = 0; i < n; i++) {
      for (let j = 0; j < n; j++) assert.ok(last.d[i][j] === null || (truth[i][j] !== null && last.d[i][j] >= truth[i][j]));
    }
    checked++;
  }
  assert.ok(checked > 1500);
});

test("入力の config を書き換えない", () => {
  const c = structuredClone(PAGE1);
  viz.states(c);
  assert.deepEqual(c, PAGE1);
});

test("誤った config は Error にする", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ n: 0 }), /n は/);
  assert.throws(() => viz.states({ n: 7 }), /n は/);
  assert.throws(() => viz.states({ n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ n: 2, directed: "yes" }), /directed/);
  assert.throws(() => viz.states({ n: 2, order: "jik" }), /order/);
  assert.throws(() => viz.states({ n: 2, edges: "x" }), /edges/);
  assert.throws(() => viz.states({ n: 6, edges: new Array(16).fill([0, 1, 1]) }), /edges/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1]] }), /\[u, v, w\]/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 2, 1]] }), /辺の端/);
  assert.throws(() => viz.states({ n: 2, edges: [[1, 1, 1]] }), /自己ループ/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 100]] }), /重み/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1.5]] }), /重み/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, -1]] }), /無向/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1], [1, 0, 2]] }), /同じ向き/);
  assert.throws(() => viz.states({ n: 2, directed: true, edges: [[0, 1, 1], [0, 1, 2]] }), /同じ向き/);
  assert.throws(() => viz.states({ n: 2, directed: true, edges: [[0, 1, 1], [1, 0, -2]] }), /負閉路/);
  assert.throws(() => viz.states({ n: 2, labels: ["a"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, labels: ["a", "abcd"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, labels: ["a", "a"] }), /同じ名前/);
  assert.throws(() => viz.states({ n: 2, pos: [[0, 0]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, pos: [[0, 0], [0, "1"]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, pos: [[0, 0], [0, 0]] }), /同じ位置/);
});

test("viewBox は幅 440 で、どのステップでも同じ", () => {
  const vb = viz.viewBox(PAGE1, viz.states(PAGE1)).split(" ").map(Number);
  assert.deepEqual(vb.slice(0, 3), [0, 0, 440]);
  assert.ok(vb[3] > 150 && vb[3] < 400);
  for (let n = 1; n <= 6; n++) assert.ok(Number(viz.viewBox({ n }).split(" ")[3]) > 0);
});

test("render は中継点・比べるマス・足す 2 マス・更新を、色以外（枠の線・文字）でも描き分ける", () => {
  const draw = (s, config = PAGE1) => {
    const nodes = [];
    const svg = { appendChild: (e) => nodes.push(e) };
    viz.render(svg, s, config, (tag, attrs, text) => ({ tag, attrs, text }));
    return nodes;
  };
  const sts = viz.states(PAGE1);
  const idx = sts.findIndex((s) => s.phase === "cell" && s.k === 3 && s.i === 0 && s.j === 1);
  let nodes = draw(sts[idx]);
  const by = (attr, v) => nodes.find((e) => e.attrs && e.attrs[attr] === v);
  // 中継点の行と列の見出しに「k=3」
  assert.equal(by("data-colhead", 3).text, "k=3");
  assert.equal(by("data-rowhead", 3).text, "k=3");
  assert.equal(by("data-colhead", 0).text, "0");
  // 中継点の行と列のマスは is-yes
  assert.match(by("data-cell", "3,0").attrs.class, /is-yes/);
  assert.match(by("data-cell", "1,3").attrs.class, /is-yes/);
  assert.doesNotMatch(by("data-cell", "1,2").attrs.class, /is-yes/);
  // 比べるマスは太い枠、足す 2 マスは破線の枠
  assert.ok(by("data-focus", "0,1"));
  assert.equal(by("data-operand", "0,3").attrs["stroke-dasharray"], "4 3");
  assert.equal(by("data-operand", "3,1").attrs["stroke-dasharray"], "4 3");
  assert.equal(nodes.filter((e) => e.attrs && e.attrs["data-operand"]).length, 2);
  // 更新したマスは「5→3」
  assert.equal(by("data-value", "0,1").text, "5→3");
  // 頂点 k は塗り、i と j は輪と印
  const circle = (v) => nodes.find((e) => e.tag === "circle" && e.attrs["data-vertex"] === v);
  assert.match(circle(3).attrs.class, /is-answer/);
  assert.doesNotMatch(circle(0).attrs.class, /is-answer/);
  assert.ok(by("data-ring", 0) && by("data-ring", 1));
  assert.equal(by("data-mark", 0).text, "i");
  assert.equal(by("data-mark", 1).text, "j");
  assert.equal(by("data-mark", 3).text, "k");
  assert.equal(by("data-formula", 1).text, "d[0][1] = min(5, 1 + 2) = 3（更新）");
  // 次のステップでは、更新済みのマスに三角の印
  nodes = draw(sts[idx + 1]);
  assert.ok(by("data-changed", "0,1"));
  assert.equal(by("data-value", "0,1").text, "3");
  // 両向きの辺 0 → 1 と 1 → 0 は曲げて描く（Q の制御点を持ち、矢じりが 5 つ）
  const edges = nodes.filter((e) => e.tag === "path" && e.attrs["data-edge"] !== undefined);
  assert.equal(edges.length, 5);
  assert.equal(nodes.filter((e) => e.tag === "path" && e.attrs.class === "kp-v-mark").length, 5);
  // ijk の最後は × と is-no
  const s2 = viz.states(PAGE2);
  nodes = draw(s2.at(-1), PAGE2);
  assert.ok(by("data-wrong", "0,1"));
  assert.equal(by("data-truth", "0,1").text, "正 3");
  assert.ok(by("data-wrong-frame", "0,1"), "誤ったマスに色以外の印（太い枠）");
  assert.match(by("data-cell", "0,1").attrs.class, /is-no/);
  assert.equal(nodes.filter((e) => e.attrs && e.attrs["data-wrong"]).length, 1);
  // 初期状態でも描ける（中継点なし）
  nodes = draw(sts[0]);
  assert.ok(!nodes.some((e) => e.attrs && (e.attrs["data-focus"] || e.attrs["data-operand"])));
});

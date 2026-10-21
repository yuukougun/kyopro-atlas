// 動く図 dijkstra（ヒープ版のダイクストラ法）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/dijkstra.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/dijkstra.js", import.meta.url);

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

const viz = loadViz("dijkstra");

// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
const run = (config) => structuredClone(viz.states(config));

// 本文（docs/graph/dijkstra.md）の 2 つの config
const PAGE1 = {
  n: 5, directed: false, source: 0,
  edges: [[0, 1, 4], [0, 2, 1], [2, 1, 2], [1, 3, 1], [2, 3, 5], [3, 4, 3]],
  pos: [[60, 120], [200, 50], [200, 190], [340, 120], [480, 120]],
};
const PAGE2 = {
  n: 3, directed: true, source: 0, labels: ["s", "a", "b"],
  edges: [[0, 1, 2], [0, 2, 3], [2, 1, -2]],
  pos: [[60, 120], [240, 40], [240, 190]],
};

// 本文の div の config と同じか（本文を直したら試験も直す）
test("試験の config は本文の div と同じ", () => {
  const md = readFileSync(new URL("../../docs/graph/dijkstra.md", import.meta.url), "utf8");
  const configs = [...md.matchAll(/data-viz="dijkstra" data-config='([^']*)'/g)].map((m) => JSON.parse(m[1]));
  assert.deepEqual(configs, [PAGE1, PAGE2]);
});

// 正しい最短距離（ベルマンフォード法。届かなければ null）
function bellmanFord(c) {
  const dist = new Array(c.n).fill(null);
  dist[c.source ?? 0] = 0;
  const arcs = [];
  for (const [u, v, w] of c.edges) {
    arcs.push([u, v, w]);
    if (!c.directed) arcs.push([v, u, w]);
  }
  for (let it = 0; it < c.n; it++) {
    for (const [u, v, w] of arcs) {
      if (dist[u] !== null && (dist[v] === null || dist[u] + w < dist[v])) dist[v] = dist[u] + w;
    }
  }
  return dist;
}

const lessPair = (a, b) => a[0] < b[0] || (a[0] === b[0] && a[1] < b[1]);

// どの状態にも成り立つこと
function checkInvariants(c, sts) {
  assert.equal(sts[0].phase, "init");
  assert.deepEqual(sts[0].heap, [[0, c.source ?? 0]]);
  assert.equal(sts[0].popped, null);
  for (const [k, s] of sts.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(!/undefined|NaN/.test(s.caption), `状態 ${k}: caption に undefined か NaN`);
    for (let j = 1; j < s.heap.length; j++) assert.ok(!lessPair(s.heap[j], s.heap[j - 1]), `状態 ${k}: ヒープが小さい順でない`);
    for (const [d, v] of s.heap) assert.ok(s.dist[v] !== null && d >= s.dist[v], `状態 ${k}: ヒープの組が dist より小さい`);
    // 暫定距離を与えた辺は、その頂点に届く辺で、dist と一致する
    for (let v = 0; v < c.n; v++) {
      if (s.prev[v] === null) {
        assert.ok(v === (c.source ?? 0) ? s.dist[v] === 0 : s.dist[v] === null);
        continue;
      }
      const [a, b, w] = c.edges[s.prev[v]];
      const from = b === v ? a : b;
      assert.ok(b === v || (!c.directed && a === v));
      assert.ok(s.dist[from] !== null);
      assert.ok(s.dist[from] + w <= s.dist[v], `状態 ${k}: 暫定距離を与えた辺と dist が合わない`);
    }
    if (k > 0) {
      const p = sts[k - 1];
      assert.ok(s.popped !== null);
      // 取り出した組は、前の状態のヒープの先頭
      assert.deepEqual(s.popped, p.heap[0], `状態 ${k}: 最小の組を取り出していない`);
      assert.equal(s.stale, s.popped[0] > p.dist[s.popped[1]]);
      assert.equal(s.phase, s.stale ? "stale" : "pop");
      if (s.stale) {
        assert.deepEqual(s.dist, p.dist);
        assert.deepEqual(s.heap, p.heap.slice(1));
        assert.equal(s.updated.length, 0);
      } else {
        assert.ok(s.done[s.popped[1]]);
        assert.equal(s.again, p.done[s.popped[1]]);
      }
      // 確定済みの集合は減らない
      for (let v = 0; v < c.n; v++) if (p.done[v]) assert.ok(s.done[v]);
      for (const u of s.updated) {
        assert.equal(u.next, s.popped[0] + u.w);
        assert.ok(u.old === null || u.next < u.old);
        assert.equal(s.dist[u.to], u.next);
        assert.equal(s.prev[u.to], u.edge);
        assert.equal(u.wasDone, p.done[u.to]);
      }
    }
  }
  const last = sts.at(-1);
  assert.ok(last.last);
  assert.equal(last.heap.length, 0);
  for (const s of sts.slice(0, -1)) assert.ok(!s.last);
  return last;
}

test("本文の 5 頂点の例：表の 7 ステップと一致する", () => {
  const sts = run(PAGE1);
  checkInvariants(PAGE1, sts);
  assert.equal(sts.length, 8); // 初期状態 + 取り出し 7 回
  assert.deepEqual(sts.slice(1).map((s) => s.popped), [[0, 0], [1, 2], [3, 1], [4, 1], [4, 3], [6, 3], [7, 4]]);
  // 4 番目と 6 番目が古い組の読み飛ばし
  assert.deepEqual(sts.slice(1).map((s) => s.stale), [false, false, false, true, false, true, false]);
  // 処理の後のヒープ（表の 3 列目）
  assert.deepEqual(sts.slice(1).map((s) => s.heap), [
    [[1, 2], [4, 1]],
    [[3, 1], [4, 1], [6, 3]],
    [[4, 1], [4, 3], [6, 3]],
    [[4, 3], [6, 3]],
    [[6, 3], [7, 4]],
    [[7, 4]],
    [],
  ]);
  // 更新（表の 2 列目）：0 で 1 を 4、2 を 1 / 2 で 1 を 3、3 を 6 / 1 で 3 を 4 / 3 で 4 を 7 / 4 で更新なし
  const ups = sts.slice(1).map((s) => s.updated.map((u) => [u.to, u.next]));
  assert.deepEqual(ups, [[[1, 4], [2, 1]], [[1, 3], [3, 6]], [[3, 4]], [], [[4, 7]], [], []]);
  const last = sts.at(-1);
  assert.deepEqual(last.dist, [0, 3, 1, 4, 7]);
  assert.deepEqual(last.dist, bellmanFord(PAGE1));
  assert.deepEqual(last.done, [true, true, true, true, true]);
  // 最短路の木は 0-2-1-3-4（辺の番号 1・2・3・5）
  assert.deepEqual(last.prev, [null, 2, 1, 3, 5]);
  assert.match(sts[4].caption, /dist\[1\] = 3 < 4 なので古い組/);
  assert.match(sts[1].caption, /1 を ∞ → 4（0 \+ 4）、2 を ∞ → 1（0 \+ 1）に更新/);
  assert.match(last.caption, /0、3、1、4、7 である/);
  assert.match(last.caption, /細い実線の辺が最短路の木である/);
  assert.ok(sts.every((s) => !s.again));
});

test("本文の負の辺の例：確定済みの a が 2 から 1 に縮み、入れ直して正しい答えになる", () => {
  const sts = run(PAGE2);
  checkInvariants(PAGE2, sts);
  assert.equal(sts.length, 5);
  assert.deepEqual(sts.slice(1).map((s) => s.popped), [[0, 0], [2, 1], [3, 2], [1, 1]]);
  assert.ok(sts.every((s) => !s.stale));
  // a（頂点 1）は 2 で確定した後、b から −2 の辺で 1 に縮む
  assert.deepEqual(sts[2].done, [true, true, false]);
  assert.equal(sts[2].dist[1], 2);
  assert.deepEqual(sts[3].updated, [{ to: 1, edge: 2, from: 2, old: 2, next: 1, w: -2, wasDone: true }]);
  assert.match(sts[3].caption, /確定済みの a の距離が 2 から 1 に縮む/);
  assert.match(sts[3].caption, /入れ直す書き方なので \(1, a\) を入れ、あとで a をもう一度取り出して出る辺も見直す/);
  assert.match(sts[3].caption, /done\[v\] で捨てる書き方では \(1, a\) を取り出しても読み飛ばすので、a から出る辺が見直されず/);
  assert.doesNotMatch(sts[3].caption, /のまま誤る/);
  assert.match(sts[3].caption, /3 − 2 = 1 < 2/);
  // 確定済みの a をもう一度取り出す
  assert.ok(sts[4].again);
  assert.match(sts[4].caption, /もう一度取り出して/);
  assert.match(sts[4].caption, /計算量の保証はなくなる/);
  assert.deepEqual(sts.at(-1).dist, [0, 1, 3]);
  assert.match(sts.at(-1).caption, /s: 0、a: 1、b: 3 である/);
});

test("端の場合：頂点 1 つ・辺なし・届かない頂点・始点が 0 でない・重み 0", () => {
  let sts = run({ n: 1, edges: [] });
  assert.equal(sts.length, 2);
  assert.deepEqual(sts.at(-1).dist, [0]);
  assert.match(sts.at(-1).caption, /出る辺はなく/);
  checkInvariants({ n: 1, edges: [] }, sts);

  sts = run({ n: 2 });
  assert.deepEqual(sts.at(-1).dist, [0, null]);
  assert.match(sts.at(-1).caption, /1 には始点から届かず、∞ のまま/);

  const c = { n: 4, directed: true, source: 2, edges: [[2, 0, 5], [0, 1, 0], [3, 2, 1]] };
  sts = run(c);
  checkInvariants(c, sts);
  assert.deepEqual(sts.at(-1).dist, [5, 5, 0, null]);
  assert.match(sts.at(-1).caption, /3 には始点から届かず/);

  // 同じ距離の組は頂点の番号の小さい順に取り出す（pair の比べ方）
  const tie = { n: 4, edges: [[0, 3, 1], [0, 2, 1], [0, 1, 1]] };
  sts = run(tie);
  assert.deepEqual(sts.slice(2).map((s) => s.popped[1]), [1, 2, 3]);
});

test("ランダムなグラフで最短距離が正しく、非負なら各頂点を 1 回だけ確定する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  let negCount = 0;
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const directed = rand() < 0.5;
    const negative = directed && rand() < 0.4;
    const edges = [];
    const used = new Set();
    const m = Math.floor(rand() * 13);
    for (let k = 0; k < m && n > 1; k++) {
      const u = Math.floor(rand() * n);
      const v = Math.floor(rand() * n);
      const key = `${Math.min(u, v)}-${Math.max(u, v)}`;
      if (u === v || used.has(key)) continue;
      used.add(key);
      const w = negative ? Math.floor(rand() * 21) - 6 : Math.floor(rand() * 10);
      edges.push([u, v, w]);
    }
    const c = { n, directed, source: Math.floor(rand() * n), edges };
    let sts;
    try {
      sts = run(c);
    } catch (e) {
      assert.ok(negative, `非負なのに Error：${e.message}`);
      assert.match(e.message, /負閉路/);
      negCount++;
      continue;
    }
    const last = checkInvariants(c, sts);
    assert.deepEqual(last.dist, bellmanFord(c), JSON.stringify(c));
    // 届く頂点はすべて確定し、届かない頂点は確定しない
    for (let v = 0; v < n; v++) assert.equal(last.done[v], last.dist[v] !== null);
    // 取り出しの回数 = 入れた回数（始点の 1 回 + 更新の回数）
    const pushes = 1 + sts.reduce((a, s) => a + s.updated.length, 0);
    assert.equal(sts.length - 1, pushes);
    if (edges.every((e) => e[2] >= 0)) {
      // 非負なら：確定済みの距離は変わらず、同じ頂点を 2 回処理しない（古い組以外の取り出しは頂点ごとに 1 回）
      assert.ok(sts.every((s) => !s.again && s.updated.every((u) => !u.wasDone)));
      for (let k = 1; k < sts.length; k++) {
        for (let v = 0; v < n; v++) if (sts[k - 1].done[v]) assert.equal(sts[k].dist[v], sts[k - 1].dist[v]);
      }
      // 確定する順に距離は小さくならない
      const order = sts.filter((s) => s.phase === "pop").map((s) => s.popped[0]);
      for (let k = 1; k < order.length; k++) assert.ok(order[k - 1] <= order[k]);
    }
  }
  assert.ok(negCount > 0, "負閉路の場合が試されていない");
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const before = JSON.stringify(PAGE2);
  assert.deepEqual(run(PAGE2), run(PAGE2));
  assert.equal(JSON.stringify(PAGE2), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const e = [[0, 1, 1]];
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ n: 0 }), /n は/);
  assert.throws(() => viz.states({ n: 9 }), /n は/);
  assert.throws(() => viz.states({ n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ n: 2, directed: "yes" }), /directed/);
  assert.throws(() => viz.states({ n: 2, source: 2 }), /source/);
  assert.throws(() => viz.states({ n: 2, edges: "x" }), /edges/);
  assert.throws(() => viz.states({ n: 8, edges: new Array(13).fill([0, 1, 1]) }), /edges/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1]] }), /\[u, v, w\]/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 2, 1]] }), /辺の端/);
  assert.throws(() => viz.states({ n: 2, edges: [[1, 1, 1]] }), /自己ループ/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 100]] }), /重み/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1.5]] }), /重み/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, -1]] }), /無向/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1], [1, 0, 2]] }), /1 本/);
  assert.throws(() => viz.states({ n: 2, directed: true, edges: [[0, 1, 1], [1, 0, 2]] }), /1 本/);
  assert.throws(() => viz.states({ n: 3, directed: true, edges: [[0, 1, 1], [1, 2, -3], [2, 0, 1]] }), /負閉路/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a", "abcd"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a", "a"] }), /同じ名前/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0], [0, "1"]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0], [0, 0]] }), /同じ位置/);
  // 始点から届かない負閉路は終わるので受け付ける
  assert.deepEqual(run({ n: 4, directed: true, edges: [[1, 2, -3], [2, 3, 1], [3, 1, 1]] }).at(-1).dist, [0, null, null, null]);
});

test("viewBox はステップによらず、ヒープの最大の大きさに合わせた高さになる", () => {
  const vb = viz.viewBox(PAGE1, viz.states(PAGE1)).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.equal(vb[2], 440);
  assert.deepEqual(viz.viewBox(PAGE1).split(" ").map(Number), vb);
  // ヒープが 6 個以上になると 2 行目を使うので高くなる
  const star = { n: 8, edges: [[0, 1, 9], [0, 2, 8], [0, 3, 7], [0, 4, 6], [0, 5, 5], [0, 6, 4], [0, 7, 3]] };
  const vb2 = viz.viewBox(star).split(" ").map(Number);
  assert.ok(vb2[3] > viz.viewBox({ n: 8, edges: star.edges.slice(0, 5) }).split(" ").map(Number)[3]);
});

test("render は取り出した頂点の輪・更新した辺・古い組の取り消し線を、線の種類でも描き分ける", () => {
  const sts = viz.states(PAGE1);
  const draw = (s, config = PAGE1) => {
    const nodes = [];
    const svg = { appendChild: (e) => nodes.push(e) };
    viz.render(svg, s, config, (tag, attrs, text) => ({ tag, attrs, text }));
    return nodes;
  };
  // 3 番目の取り出し (3, 1)：1 を確定し、辺 1-3（番号 3）で 3 を 4 に更新。ヒープの (4, 1)・(6, 3) は古い組
  let nodes = draw(sts[3]);
  const edge = (k) => nodes.find((e) => e.tag === "line" && e.attrs["data-edge"] === k);
  assert.match(edge(3).attrs.class, /is-focus/);
  assert.equal(edge(3).attrs["stroke-dasharray"], null);
  assert.equal(edge(0).attrs["stroke-dasharray"], "5 4"); // 0-1 は暫定距離を与えていない
  assert.equal(edge(1).attrs["stroke-dasharray"], null); // 0-2 は 2 の距離を与えている
  assert.doesNotMatch(edge(1).attrs.class, /is-focus/);
  const ring = nodes.find((e) => e.attrs && e.attrs["data-ring"] === 1);
  assert.ok(ring);
  assert.equal(ring.attrs["stroke-dasharray"], null);
  const circle = (v) => nodes.find((e) => e.tag === "circle" && e.attrs["data-vertex"] === v);
  assert.match(circle(1).attrs.class, /is-answer/);
  assert.doesNotMatch(circle(3).attrs.class, /is-answer/);
  assert.equal(nodes.find((e) => e.attrs && e.attrs["data-dist"] === 3).text, "6→4");
  assert.equal(nodes.filter((e) => e.attrs && e.attrs["data-strike"]).length, 2);
  // 読み飛ばしのステップは破線の輪
  nodes = draw(sts[4]);
  assert.equal(nodes.find((e) => e.attrs && e.attrs["data-ring"] === 1).attrs["stroke-dasharray"], "4 3");
  // 負の辺の例：確定済みへの更新に「！」を付け、矢じりを描く
  const s2 = viz.states(PAGE2);
  nodes = draw(s2[3], PAGE2);
  assert.equal(nodes.find((e) => e.attrs && e.attrs["data-dist"] === 1).text, "2→1！");
  assert.ok(nodes.some((e) => e.tag === "text" && e.text === "−2"));
  assert.ok(nodes.filter((e) => e.tag === "path").length >= 3);
});

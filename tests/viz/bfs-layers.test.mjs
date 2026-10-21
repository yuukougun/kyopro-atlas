// 動く図 bfs-layers（幅優先探索の距離の層とキュー）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/bfs-layers.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/bfs-layers.js", import.meta.url);

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

const viz = loadViz("bfs-layers");

// vm の中で作った配列は別の realm なので、比べる前に JSON で写す
const plain = (x) => JSON.parse(JSON.stringify(x));

// 本文（docs/graph/bfs.md）の data-config と同じ
const PAGE = {
  labels: ["s", "a", "b", "c", "d", "e"],
  edges: [[0, 1], [0, 2], [1, 2], [1, 3], [2, 3], [2, 4], [3, 4], [3, 5], [4, 5]],
  source: 0,
};

// 別に書いた BFS（距離だけ）
function refDist(n, edges, src) {
  const adj = Array.from({ length: n }, () => []);
  for (const [u, v] of edges) {
    adj[u].push(v);
    adj[v].push(u);
  }
  const dist = new Array(n).fill(-1);
  dist[src] = 0;
  const q = [src];
  for (let h = 0; h < q.length; h++) {
    for (const v of adj[q[h]]) if (dist[v] === -1) { dist[v] = dist[q[h]] + 1; q.push(v); }
  }
  return dist;
}

// どの状態でも成り立つこと
function checkInvariants(cfg, states) {
  const n = cfg.labels ? cfg.labels.length : cfg.n;
  const src = cfg.source ?? 0;
  const truth = refDist(n, cfg.edges ?? [], src);
  const pushCount = new Array(n).fill(0);
  pushCount[src] = 1;
  let prevDone = 0;
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(!/です|ます/.test(s.caption), `状態 ${k}: だ・である調でない`);
    // 書き込まれた距離は真の距離と一致する（見つけたその場で正しい）
    for (let v = 0; v < n; v++) {
      if (s.dist[v] !== -1) assert.equal(s.dist[v], truth[v], `状態 ${k}: dist[${v}]`);
    }
    // キューの距離は広義単調増加で、最大と最小の差は 1 以下（2 種類まで）
    const qd = s.queue.map((v) => s.dist[v]);
    for (let i = 1; i < qd.length; i++) assert.ok(qd[i - 1] <= qd[i], `状態 ${k}: キューが単調でない`);
    if (qd.length) assert.ok(qd.at(-1) - qd[0] <= 1, `状態 ${k}: キューに 3 種類の距離`);
    assert.equal(new Set(s.queue).size, s.queue.length, `状態 ${k}: キューに同じ頂点が 2 つ`);
    // キューの中は見つけていて、まだ取り出していない
    for (const v of s.queue) assert.ok(s.dist[v] >= 0 && !s.done[v]);
    // 親への辺は親の距離 + 1
    for (let v = 0; v < n; v++) {
      if (s.par[v] >= 0) assert.equal(s.dist[v], s.dist[s.par[v]] + 1);
      else if (v !== src) assert.equal(s.dist[v], -1);
    }
    for (const v of s.pushed) pushCount[v]++;
    const doneNow = s.done.filter(Boolean).length;
    if (s.phase === "pop") assert.equal(doneNow, prevDone + 1, `状態 ${k}: 1 ステップで 1 頂点を取り出していない`);
    prevDone = doneNow;
  }
  // 各頂点は高々 1 回しか push しない
  for (let v = 0; v < n; v++) assert.equal(pushCount[v], truth[v] === -1 ? 0 : 1, `頂点 ${v} の push の回数`);
  const last = states.at(-1);
  assert.equal(last.phase, "done");
  assert.deepEqual(plain(last.dist), truth);
  assert.equal(last.queue.length, 0);
}

test("本文のグラフで、距離が s〜e の順に 0, 1, 1, 2, 2, 3、親が静的な図の太い辺になる", () => {
  const states = viz.states(PAGE);
  assert.equal(states.length, 8); // 初期状態・6 回の取り出し・まとめ
  assert.equal(states[0].phase, "init");
  assert.deepEqual(plain(states[0].queue), [0]);
  const last = states.at(-1);
  assert.deepEqual(plain(last.dist), [0, 1, 1, 2, 2, 3]);
  assert.deepEqual(plain(last.par), [-1, 0, 0, 1, 2, 3]); // a←s, b←s, c←a, d←b, e←c
  // 太い辺の番号：s-a(0)・s-b(1)・a-c(3)・b-d(5)・c-e(7)
  assert.deepEqual(plain(last.parEdge.filter((k) => k >= 0).sort((x, y) => x - y)), [0, 1, 3, 5, 7]);
  const pops = states.filter((s) => s.phase === "pop");
  assert.deepEqual(plain(pops.map((s) => s.popped)), [0, 1, 2, 3, 4, 5]);
  assert.deepEqual(plain(pops.map((s) => s.queue)), [[1, 2], [2, 3], [3, 4], [4, 5], [5], []]);
  assert.deepEqual(plain(pops.map((s) => s.pushed)), [[1, 2], [3], [4], [5], [], []]);
  // a を取り出したとき：s と b は飛ばし、c を見つける。キューの距離は 1, 2 の 2 種類
  assert.match(pops[1].caption, /s・b はもう距離が書いてある/);
  assert.match(pops[1].caption, /1, 2 で、1 と 2 の 2 種類/);
  assert.match(last.caption, /s: 0、a: 1、b: 1、c: 2、d: 2、e: 3/);
  checkInvariants(PAGE, states);
});

test("頂点 1 個で辺がない", () => {
  const states = viz.states({ n: 1 });
  assert.deepEqual(plain(states.map((s) => s.phase)), ["init", "pop", "done"]);
  assert.match(states[1].caption, /隣の頂点はない/);
  assert.deepEqual(plain(states.at(-1).dist), [0]);
});

test("始点から届かない頂点は −1 のまま残り、まとめで名前を挙げる", () => {
  const cfg = { labels: ["p", "q", "x", "y"], edges: [[0, 1], [2, 3]], source: 1 };
  const states = viz.states(cfg);
  assert.deepEqual(plain(states.at(-1).dist), [1, 0, -1, -1]);
  assert.match(states.at(-1).caption, /x・y には始点から届かず/);
  checkInvariants(cfg, states);
  // 描画の寸法も作れる
  const vb = viz.viewBox(cfg).split(" ").map(Number);
  assert.equal(vb[2], 440);
});

test("ランダムなグラフで、距離が別に書いた BFS と一致し、不変条件が保たれる", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 2000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const all = [];
    for (let u = 0; u < n; u++) for (let v = u + 1; v < n; v++) all.push(rand() < 0.5 ? [u, v] : [v, u]);
    for (let i = all.length - 1; i > 0; i--) {
      const j = Math.floor(rand() * (i + 1));
      [all[i], all[j]] = [all[j], all[i]];
    }
    const m = Math.floor(rand() * (Math.min(14, all.length) + 1));
    const cfg = { n, edges: all.slice(0, m), source: Math.floor(rand() * n) };
    const states = viz.states(cfg);
    checkInvariants(cfg, states);
    const reached = refDist(n, cfg.edges, cfg.source).filter((d) => d >= 0).length;
    assert.equal(states.length, reached + 2);
    // 寸法は全ステップで同じ式から作る（例外を投げない）
    assert.match(viz.viewBox(cfg), /^0 0 440 \d+$/);
  }
});

// 偽の h で描き、置いた要素を集める
function draw(cfg, state) {
  const els = [];
  const svg = { appendChild: (e) => els.push(e) };
  const h = (tag, attrs, text) => ({ tag, attrs: attrs || {}, text: text == null ? "" : String(text) });
  viz.render(svg, state, cfg, h);
  return els;
}

// 距離の文字の箱（1 文字 8 px・高さ 14 px と見積もる）
function distBox(e) {
  const w = [...e.text].length * 8;
  const st = e.attrs.style || "";
  const x = Number(e.attrs.x), y = Number(e.attrs.y);
  const left = /text-anchor: start/.test(st) ? x : /text-anchor: end/.test(st) ? x - w : x - w / 2;
  return { l: left, r: left + w, t: y - 7, b: y + 7 };
}

function randomConfigs(count, seed0) {
  let seed = seed0;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  const out = [];
  for (let t = 0; t < count; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const all = [];
    for (let u = 0; u < n; u++) for (let v = u + 1; v < n; v++) all.push([u, v]);
    for (let i = all.length - 1; i > 0; i--) {
      const j = Math.floor(rand() * (i + 1));
      [all[i], all[j]] = [all[j], all[i]];
    }
    const m = Math.floor(rand() * (Math.min(14, all.length) + 1));
    out.push({ n, edges: all.slice(0, m), source: Math.floor(rand() * n) });
  }
  return out;
}

test("描画：距離の文字どうしが重ならず（同じ列の上下・隣の列も）、辺の弧が枠の中に収まる", () => {
  const cfgs = [
    PAGE,
    { n: 5, edges: [[0, 3], [1, 2]], source: 0 },
    { n: 8, edges: [[0, 1], [1, 2], [3, 4], [3, 7], [4, 5], [5, 6]], source: 0 },
    ...randomConfigs(3000, 777),
  ];
  for (const cfg of cfgs) {
    const states = viz.states(cfg);
    const W = Number(viz.viewBox(cfg).split(" ")[2]);
    for (const s of states) {
      const els = draw(cfg, s);
      const boxes = els.filter((e) => e.attrs["data-dist"] != null).map(distBox);
      for (let i = 0; i < boxes.length; i++) {
        for (let j = i + 1; j < boxes.length; j++) {
          const a = boxes[i], b = boxes[j];
          const hit = a.l < b.r && b.l < a.r && a.t < b.b && b.t < a.b;
          assert.ok(!hit, `${JSON.stringify(cfg)}: 距離の文字が重なる`);
        }
      }
      for (const e of els.filter((x) => x.tag === "path" && x.attrs["data-edge"] != null)) {
        // M ax ay Q mx my bx by：一番右は (ax + 2 mx + bx) / 4
        const v = e.attrs.d.match(/-?[\d.]+/g).map(Number);
        const peak = (v[0] + 2 * v[2] + v[4]) / 4;
        assert.ok(peak + 2.25 <= W, `${JSON.stringify(cfg)}: 弧が枠から出る（${peak}）`);
      }
    }
  }
});

test("描画：今見た辺が親への辺でもあるときは、太い線に細い破線を重ねて前からの親への辺と区別する", () => {
  const states = viz.states(PAGE);
  // s を取り出した状態：s-a(0)・s-b(1) は今見た親への辺
  const els = draw(PAGE, states[1]);
  const marks = els.filter((e) => e.attrs["data-focus-tree"] != null).map((e) => e.attrs["data-focus-tree"]);
  assert.deepEqual(marks.sort(), [0, 1]);
  // b を取り出した状態：b-d(5) は今見た親への辺、s-b(1) は b の親への辺で今見た辺。s-a(0)・a-c(3) は前からの辺なので印なし
  const els3 = draw(PAGE, states[3]);
  const marks3 = els3.filter((e) => e.attrs["data-focus-tree"] != null).map((e) => e.attrs["data-focus-tree"]);
  assert.deepEqual(marks3.sort((x, y) => x - y), [1, 5]);
});

test("labels を省いたとき、caption では頂点を「頂点 k」と書いて距離の数と区別する", () => {
  const cfg = { n: 4, edges: [[0, 1], [1, 2]], source: 1 };
  const states = viz.states(cfg);
  assert.match(states[0].caption, /始点 頂点 1 に dist = 0/);
  assert.match(states[1].caption, /先頭の 頂点 1（距離 0）を取り出す/);
  assert.match(states.at(-1).caption, /頂点 0: 1、頂点 1: 0、頂点 2: 1、頂点 3: −1/);
  assert.match(states.at(-1).caption, /頂点 3 には始点から届かず/);
  // 図の中の名前は短いまま
  const texts = draw(cfg, states[0]).filter((e) => e.tag === "text").map((e) => e.text);
  assert.ok(texts.includes("1") && !texts.includes("頂点 1"));
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const cfg = JSON.parse(JSON.stringify(PAGE));
  const before = JSON.stringify(cfg);
  assert.deepEqual(plain(viz.states(cfg)), plain(viz.states(cfg)));
  assert.equal(JSON.stringify(cfg), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({}), /n は/);
  assert.throws(() => viz.states({ n: 9 }), /n は/);
  assert.throws(() => viz.states({ labels: [] }), /labels/);
  assert.throws(() => viz.states({ labels: ["a", "a"] }), /同じ名前/);
  assert.throws(() => viz.states({ labels: ["abcd"] }), /1〜3 文字/);
  assert.throws(() => viz.states({ labels: ["a", "b"], n: 3 }), /個数/);
  assert.throws(() => viz.states({ n: 2, source: 2 }), /source/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 2]] }), /辺の端/);
  assert.throws(() => viz.states({ n: 2, edges: [[1, 1]] }), /自己ループ/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1], [1, 0]] }), /1 本/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 5]] }), /\[u, v\]/);
  assert.throws(() => viz.states({ n: 8, edges: new Array(15).fill([0, 1]) }), /edges/);
});

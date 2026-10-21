// 動く図 zero-one-bfs（01-BFS）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/zero-one-bfs.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/zero-one-bfs.js", import.meta.url);

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

const viz = loadViz("zero-one-bfs");

// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
const run = (config) => structuredClone(viz.states(config));

// 本文（docs/graph/zero-one-bfs.md）の config
const PAGE = {
  n: 5, source: 0,
  edges: [[0, 1, 1], [0, 2, 1], [0, 3, 0], [3, 2, 0], [1, 4, 0], [2, 4, 1]],
  pos: [[70, 150], [220, 240], [370, 150], [220, 60], [520, 240]],
};

test("試験の config は本文の div と同じ", () => {
  const md = readFileSync(new URL("../../docs/graph/zero-one-bfs.md", import.meta.url), "utf8");
  const configs = [...md.matchAll(/data-viz="zero-one-bfs" data-config='([^']*)'/g)].map((m) => JSON.parse(m[1]));
  assert.deepEqual(configs, [PAGE]);
});

// 正しい最短距離（ベルマンフォード法。届かなければ null）
function bellmanFord(c) {
  const dist = new Array(c.n).fill(null);
  dist[c.source ?? 0] = 0;
  const arcs = [];
  for (const [u, v, w] of c.edges) {
    arcs.push([u, v, w]);
    if (c.directed === false) arcs.push([v, u, w]);
  }
  for (let it = 0; it < c.n; it++) {
    for (const [u, v, w] of arcs) {
      if (dist[u] !== null && (dist[v] === null || dist[u] + w < dist[v])) dist[v] = dist[u] + w;
    }
  }
  return dist;
}

// どの状態にも成り立つこと
function checkInvariants(c, sts) {
  const src = c.source ?? 0;
  assert.equal(sts[0].phase, "init");
  assert.deepEqual(sts[0].deque, [[0, src]]);
  assert.equal(sts[0].popped, null);
  for (const [k, s] of sts.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(!/undefined|NaN|null/.test(s.caption), `状態 ${k}: caption に undefined・NaN・null`);
    // 不変条件：deque の距離は先頭から広義単調増加で、先頭の距離 d と d + 1 の 2 種類以下
    const ds = s.deque.map((q) => q[0]);
    for (let j = 1; j < ds.length; j++) assert.ok(ds[j - 1] <= ds[j], `状態 ${k}: deque が単調増加でない`);
    if (ds.length) assert.ok(ds.at(-1) - ds[0] <= 1, `状態 ${k}: deque の距離が 3 種類以上`);
    for (const [d, v] of s.deque) assert.ok(s.dist[v] !== null && d >= s.dist[v], `状態 ${k}: deque の組が dist より小さい`);
    assert.ok(s.newFront + s.newBack <= s.deque.length);
    if (k > 0) {
      const p = sts[k - 1];
      // 取り出した組は、前の状態の deque の先頭
      assert.deepEqual(s.popped, p.deque[0], `状態 ${k}: 先頭の組を取り出していない`);
      assert.equal(s.stale, s.popped[0] > p.dist[s.popped[1]]);
      assert.equal(s.phase, s.stale ? "stale" : "pop");
      if (s.stale) {
        assert.deepEqual(s.dist, p.dist);
        assert.deepEqual(s.deque, p.deque.slice(1));
        assert.equal(s.updated.length, 0);
      } else {
        // 取り出した頂点は初めて確定する（同じ頂点を 2 回確定しない）
        assert.ok(!p.done[s.popped[1]]);
        assert.ok(s.done[s.popped[1]]);
        // 確定した距離は最短距離と一致する
        assert.equal(s.popped[0], bellmanFord(c)[s.popped[1]]);
        // deque = 先頭に入れた組（後に入れたものほど前）+ 残り + 末尾に入れた組
        const fronts = s.updated.filter((u) => u.front).map((u) => [u.next, u.to]).reverse();
        const backs = s.updated.filter((u) => !u.front).map((u) => [u.next, u.to]);
        assert.deepEqual(s.deque, [...fronts, ...p.deque.slice(1), ...backs]);
        assert.equal(s.newFront, fronts.length);
        assert.equal(s.newBack, backs.length);
      }
      for (let v = 0; v < c.n; v++) if (p.done[v]) assert.ok(s.done[v]);
      for (const u of s.updated) {
        assert.equal(u.next, s.popped[0] + u.w);
        assert.equal(u.front, u.w === 0);
        assert.ok(u.old === null || u.next < u.old);
        assert.equal(s.dist[u.to], u.next);
        assert.ok(!p.done[u.to], "確定済みの頂点の距離が縮んだ");
      }
    }
  }
  const last = sts.at(-1);
  assert.ok(last.last);
  assert.equal(last.deque.length, 0);
  for (const s of sts.slice(0, -1)) assert.ok(!s.last);
  return last;
}

test("本文の 5 頂点の例：手順を追う表の 7 行と一致する", () => {
  const sts = run(PAGE);
  checkInvariants(PAGE, sts);
  assert.equal(sts.length, 7); // 始め + 取り出し 6 回
  assert.deepEqual(sts.slice(1).map((s) => s.popped), [[0, 0], [0, 3], [0, 2], [1, 1], [1, 2], [1, 4]]);
  // 5 回目の取り出し (1, 2) だけが古い組の読み飛ばし
  assert.deepEqual(sts.slice(1).map((s) => s.stale), [false, false, false, false, true, false]);
  // 操作の後の deque（表の 3 列目）
  assert.deepEqual(sts.map((s) => s.deque), [
    [[0, 0]],
    [[0, 3], [1, 1], [1, 2]],
    [[0, 2], [1, 1], [1, 2]],
    [[1, 1], [1, 2], [1, 4]],
    [[1, 2], [1, 4]],
    [[1, 4]],
    [],
  ]);
  // 更新（表の 2 列目）：0→1 で 1、0→2 で 1、0→3 で 0 / 3→2 で 0（1 から縮む）/ 2→4 で 1 / 1→4 は縮まない
  const ups = sts.slice(1).map((s) => s.updated.map((u) => [u.from, u.to, u.old, u.next]));
  assert.deepEqual(ups, [
    [[0, 1, null, 1], [0, 2, null, 1], [0, 3, null, 0]],
    [[3, 2, 1, 0]],
    [[2, 4, null, 1]],
    [],
    [],
    [],
  ]);
  assert.deepEqual(sts[4].kept, [{ to: 4, edge: 4, w: 0, cand: 1, cur: 1 }]);
  assert.deepEqual(sts.map((s) => [s.newFront, s.newBack]), [[0, 0], [1, 2], [1, 0], [0, 1], [0, 0], [0, 0], [0, 0]]);
  const last = sts.at(-1);
  assert.deepEqual(last.dist, [0, 1, 0, 0, 1]);
  assert.deepEqual(last.dist, bellmanFord(PAGE));
  assert.deepEqual(last.done, [true, true, true, true, true]);
  // caption
  assert.match(sts[1].caption, /0 → 3（重み 0）で dist\[3\] を ∞ → 0 にし、\(0, 3\) を先頭へ入れる/);
  assert.match(sts[1].caption, /0 → 1（重み 1）で dist\[1\] を ∞ → 1 にし、\(1, 1\) を末尾へ入れる/);
  assert.match(sts[2].caption, /dist\[2\] を 1 → 0 に縮め、\(0, 2\) を先頭へ入れる。\(1, 2\) は古い組になる/);
  assert.match(sts[4].caption, /1 \+ 0 = 1 で、dist\[4\] = 1 より小さくならない/);
  assert.match(sts[5].caption, /dist\[2\] = 0 < 1 なので古い組であり、読み飛ばす/);
  assert.match(last.caption, /4 から出る辺はない/);
  assert.match(last.caption, /頂点 0〜4 の順に 0、1、0、0、1 である/);
});

test("端の場合：頂点 1 つ・辺なし・届かない頂点・始点が 0 でない・無向・名前付き", () => {
  let sts = run({ n: 1, edges: [] });
  checkInvariants({ n: 1, edges: [] }, sts);
  assert.equal(sts.length, 2);
  assert.deepEqual(sts.at(-1).dist, [0]);
  assert.match(sts.at(-1).caption, /出る辺はない/);
  assert.match(sts.at(-1).caption, /最短距離は頂点 0 が 0 である。/);
  assert.doesNotMatch(sts.at(-1).caption, /0〜0/);

  sts = run({ n: 2 });
  assert.deepEqual(sts.at(-1).dist, [0, null]);
  assert.match(sts.at(-1).caption, /1 には始点から届かず、∞ のまま/);

  const c = { n: 4, source: 2, edges: [[2, 0, 1], [0, 1, 0], [3, 2, 0]] };
  sts = run(c);
  checkInvariants(c, sts);
  assert.deepEqual(sts.at(-1).dist, [1, 1, 0, null]);
  assert.match(sts.at(-1).caption, /3 には始点から届かず/);

  // 無向では逆向きにもたどる
  const u = { n: 3, directed: false, source: 2, edges: [[0, 1, 1], [1, 2, 0]] };
  sts = run(u);
  checkInvariants(u, sts);
  assert.deepEqual(sts.at(-1).dist, [1, 0, 0]);

  // 名前付き：caption に名前を使う
  const named = { n: 3, labels: ["s", "a", "b"], edges: [[0, 1, 1], [1, 2, 0], [0, 2, 1]] };
  sts = run(named);
  checkInvariants(named, sts);
  assert.match(sts[1].caption, /\(1, a\) を末尾へ/);
  assert.match(sts.at(-1).caption, /s: 0、a: 1、b: 1 である/);

  // 重み 0 だけなら deque の距離はずっと 0、重み 1 だけなら BFS と同じく末尾へだけ入れる
  const zeros = { n: 4, edges: [[0, 1, 0], [1, 2, 0], [2, 3, 0]] };
  sts = run(zeros);
  checkInvariants(zeros, sts);
  assert.ok(sts.every((s) => s.deque.every((q) => q[0] === 0)));
  const ones = { n: 4, edges: [[0, 1, 1], [0, 2, 1], [1, 3, 1]] };
  sts = run(ones);
  checkInvariants(ones, sts);
  assert.ok(sts.every((s) => s.newFront === 0));
  assert.deepEqual(sts.at(-1).dist, [0, 1, 1, 2]);
});

test("ランダムなグラフで最短距離が正しく、不変条件を保つ", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  let staleCount = 0;
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const directed = rand() < 0.7;
    const edges = [];
    const used = new Set();
    const m = Math.floor(rand() * 13);
    for (let k = 0; k < m && n > 1; k++) {
      const u = Math.floor(rand() * n);
      const v = Math.floor(rand() * n);
      const key = `${Math.min(u, v)}-${Math.max(u, v)}`;
      if (u === v || used.has(key)) continue;
      used.add(key);
      edges.push([u, v, rand() < 0.5 ? 0 : 1]);
    }
    const c = { n, directed, source: Math.floor(rand() * n), edges };
    const sts = run(c);
    const last = checkInvariants(c, sts);
    assert.deepEqual(last.dist, bellmanFord(c), JSON.stringify(c));
    for (let v = 0; v < n; v++) assert.equal(last.done[v], last.dist[v] !== null);
    // 取り出しの回数 = 入れた回数（始点の 1 回 + 更新の回数）
    const pushes = 1 + sts.reduce((a, s) => a + s.updated.length, 0);
    assert.equal(sts.length - 1, pushes);
    // 確定する順に距離は小さくならない
    const order = sts.filter((s) => s.phase === "pop").map((s) => s.popped[0]);
    for (let k = 1; k < order.length; k++) assert.ok(order[k - 1] <= order[k]);
    staleCount += sts.filter((s) => s.stale).length;
  }
  assert.ok(staleCount > 0, "古い組の場合が試されていない");
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const before = JSON.stringify(PAGE);
  assert.deepEqual(run(PAGE), run(PAGE));
  assert.equal(JSON.stringify(PAGE), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const e = [[0, 1, 1]];
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ n: 0 }), /n は/);
  assert.throws(() => viz.states({ n: 9 }), /n は/);
  assert.throws(() => viz.states({ n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ n: 2, directed: "yes" }), /directed/);
  assert.throws(() => viz.states({ n: 2, source: 2 }), /source/);
  assert.throws(() => viz.states({ n: 2, source: -1 }), /source/);
  assert.throws(() => viz.states({ n: 2, edges: "x" }), /edges/);
  assert.throws(() => viz.states({ n: 8, edges: new Array(13).fill([0, 1, 1]) }), /edges/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1]] }), /\[u, v, w\]/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 2, 1]] }), /辺の端/);
  assert.throws(() => viz.states({ n: 2, edges: [[1, 1, 1]] }), /自己ループ/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 2]] }), /0 か 1/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, -1]] }), /0 か 1/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, "0"]] }), /0 か 1/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1], [1, 0, 0]] }), /1 本/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a", "abcd"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a", "a"] }), /同じ名前/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0], [0, "1"]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0], [0, 0]] }), /同じ位置/);
});

test("viewBox はステップによらず、deque の最大の長さに合わせた高さになる", () => {
  const vb = viz.viewBox(PAGE, viz.states(PAGE)).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.equal(vb[2], 440);
  assert.deepEqual(viz.viewBox(PAGE).split(" ").map(Number), vb);
  // deque が 6 個以上になると 2 行目を使うので高くなる
  const star = { n: 8, edges: [[0, 1, 1], [0, 2, 1], [0, 3, 1], [0, 4, 1], [0, 5, 1], [0, 6, 1], [0, 7, 1]] };
  const vb2 = viz.viewBox(star).split(" ").map(Number);
  assert.ok(vb2[3] > viz.viewBox({ n: 8, edges: star.edges.slice(0, 5) }).split(" ").map(Number)[3]);
});

test("render は重みを線の種類で、入れた側を文字で、古い組を取り消し線で描き分ける", () => {
  const sts = viz.states(PAGE);
  const draw = (s, config = PAGE) => {
    const nodes = [];
    const svg = { appendChild: (e) => nodes.push(e) };
    viz.render(svg, s, config, (tag, attrs, text) => ({ tag, attrs, text }));
    return nodes;
  };
  // 2 番目の状態：(0, 3) を取り出し、3→2（辺 3、重み 0）で 2 を 1 → 0 に縮めて先頭へ。(1, 2) は古い組
  let nodes = draw(sts[2]);
  const edge = (k) => nodes.find((e) => e.tag === "line" && e.attrs["data-edge"] === k);
  assert.match(edge(3).attrs.class, /is-focus/);
  assert.equal(edge(3).attrs["stroke-dasharray"], null); // 重み 0 は実線
  assert.equal(edge(0).attrs["stroke-dasharray"], "6 4"); // 重み 1 は破線
  assert.doesNotMatch(edge(0).attrs.class, /is-focus/);
  const ring = nodes.find((e) => e.attrs && e.attrs["data-ring"] === 3);
  assert.ok(ring);
  assert.equal(ring.attrs["stroke-dasharray"], null);
  const circle = (v) => nodes.find((e) => e.tag === "circle" && e.attrs["data-vertex"] === v);
  assert.match(circle(3).attrs.class, /is-answer/);
  assert.doesNotMatch(circle(2).attrs.class, /is-answer/);
  assert.equal(nodes.find((e) => e.attrs && e.attrs["data-dist"] === 2).text, "1→0");
  assert.equal(nodes.filter((e) => e.attrs && e.attrs["data-strike"]).length, 1);
  const pushes = nodes.filter((e) => e.attrs && e.attrs["data-push"] !== undefined);
  assert.deepEqual(pushes.map((e) => [e.attrs["data-push"], e.text]), [[0, "先頭へ"]]);
  // 1 番目の状態：先頭へ 1 つ、末尾へ 2 つ
  nodes = draw(sts[1]);
  assert.deepEqual(
    nodes.filter((e) => e.attrs && e.attrs["data-push"] !== undefined).map((e) => [e.attrs["data-push"], e.text]),
    [[0, "先頭へ"], [1, "末尾へ"], [2, "末尾へ"]],
  );
  assert.ok(nodes.filter((e) => e.tag === "path").length >= 6); // 矢じり
  // 読み飛ばしのステップは破線の輪
  nodes = draw(sts[5]);
  assert.equal(nodes.find((e) => e.attrs && e.attrs["data-ring"] === 2).attrs["stroke-dasharray"], "4 3");
  assert.ok(nodes.some((e) => e.tag === "text" && e.text === "古い組なので読み飛ばす"));
});

test("距離の文字は左右に置いても枠（幅 440）の中に収まる", () => {
  // 文字の幅の見積もり：「∞→7」まで（太字 14px で約 32px）
  const TEXT_W = 34;
  const configs = [PAGE, { n: 3, edges: [[0, 1, 1], [1, 2, 0]], pos: [[0, 0], [100, 0], [200, 0]] }];
  for (let k = 0; k < 6; k++) configs.push({ n: k + 3, edges: [[0, 1, 1], [1, 2, 0]] });
  for (const config of configs) {
    for (const s of viz.states(config)) {
      const nodes = [];
      viz.render({ appendChild: (e) => nodes.push(e) }, s, config, (tag, attrs, text) => ({ tag, attrs, text }));
      for (const e of nodes.filter((e) => e.attrs && e.attrs["data-dist"] !== undefined)) {
        const st = e.attrs.style || "";
        const x = e.attrs.x;
        if (/text-anchor: start/.test(st)) assert.ok(x + TEXT_W <= 440, `${JSON.stringify(config)} ${x}`);
        else if (/text-anchor: end/.test(st)) assert.ok(x - TEXT_W >= 0, `${JSON.stringify(config)} ${x}`);
        else assert.ok(x - TEXT_W / 2 >= 0 && x + TEXT_W / 2 <= 440);
        assert.ok(e.attrs.y >= 10, `${e.attrs.y}`); // y は文字の中央。上に置いても上端（中央 − 約 8）に余白がある
      }
    }
  }
});

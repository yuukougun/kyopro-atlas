// 動く図 max-flow-residual（最大流の残余グラフと増加路）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/max-flow-residual.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/max-flow-residual.js", import.meta.url);

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

const viz = loadViz("max-flow-residual");

// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
const run = (config) => structuredClone(viz.states(config));

// 本文（docs/graph/max-flow.md の #residual）の config
const PAGE = {
  n: 4, labels: ["s", "a", "b", "t"],
  edges: [[0, 1, 1], [0, 2, 1], [1, 2, 1], [1, 3, 1], [2, 3, 1]],
  s: 0, t: 3, paths: [[0, 1, 2, 3], [0, 2, 1, 3]],
};
const AUTO = { ...PAGE, paths: undefined };

test("試験の config は本文の div と同じ", () => {
  const md = readFileSync(new URL("../../docs/graph/max-flow.md", import.meta.url), "utf8");
  const configs = [...md.matchAll(/data-viz="max-flow-residual" data-config='([^']*)'/g)].map((m) => JSON.parse(m[1]));
  assert.deepEqual(configs, [PAGE]);
});

const srcOf = (c) => c.s ?? 0;
const sinkOf = (c) => c.t ?? c.n - 1;

// 最小カットの全探索：s を含み t を含まない頂点の集合ごとに、外へ出る辺の容量の和の最小
function minCutBrute(c) {
  const s = srcOf(c), t = sinkOf(c);
  let best = Infinity;
  for (let mask = 0; mask < 1 << c.n; mask++) {
    if (!((mask >> s) & 1) || (mask >> t) & 1) continue;
    let sum = 0;
    for (const [u, v, cap] of c.edges ?? []) if ((mask >> u) & 1 && !((mask >> v) & 1)) sum += cap;
    best = Math.min(best, sum);
  }
  return best;
}

// 残余グラフ（順辺 c − f・逆辺 f）で s から届く頂点
function reachOf(c, flow) {
  const E = c.edges ?? [];
  const reach = new Array(c.n).fill(false);
  reach[srcOf(c)] = true;
  const queue = [srcOf(c)];
  while (queue.length) {
    const v = queue.shift();
    E.forEach(([a, b, cap], i) => {
      if (a === v && cap - flow[i] > 0 && !reach[b]) { reach[b] = true; queue.push(b); }
      if (b === v && flow[i] > 0 && !reach[a]) { reach[a] = true; queue.push(a); }
    });
  }
  return reach;
}

// どの状態の列にも成り立つこと
function checkInvariants(c, sts) {
  const s0 = srcOf(c), t0 = sinkOf(c);
  const E = c.edges ?? [];
  assert.match(sts.map((s) => s.phase).join(" "), /^init( path push)* end$/);
  assert.deepEqual(sts[0].flow, E.map(() => 0));
  assert.equal(sts[0].total, 0);
  for (const [k, s] of sts.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(!/undefined|NaN|Infinity|null/.test(s.caption), `状態 ${k}: caption に undefined などが出る`);
    assert.equal(s.last, k === sts.length - 1);
    // 容量の制約・流量の保存・流量 = s から出る量 − 入る量
    E.forEach(([, , cap], i) => assert.ok(s.flow[i] >= 0 && s.flow[i] <= cap, `状態 ${k}: 辺 ${i} の流量が容量の外`));
    const net = new Array(c.n).fill(0);
    E.forEach(([u, v], i) => { net[u] += s.flow[i]; net[v] -= s.flow[i]; });
    for (let v = 0; v < c.n; v++) if (v !== s0 && v !== t0) assert.equal(net[v], 0, `状態 ${k}: 頂点 ${v} で流量が保存されない`);
    assert.equal(net[s0], s.total);
    assert.equal(net[t0] + s.total, 0);
    if (s.phase === "path") {
      const p = sts[k - 1];
      assert.deepEqual(s.flow, p.flow);
      assert.equal(s.total, p.total);
      assert.equal(s.path[0], s0);
      assert.equal(s.path.at(-1), t0);
      assert.equal(new Set(s.path).size, s.path.length, `状態 ${k}: 増加路が同じ頂点を 2 度通る`);
      assert.equal(s.arcs.length, s.path.length - 1);
      s.arcs.forEach((a, i) => {
        assert.equal(a.from, s.path[i]);
        assert.equal(a.to, s.path[i + 1]);
        const [u, v, cap] = E[a.edge];
        if (a.rev) {
          assert.deepEqual([u, v], [a.to, a.from]);
          assert.equal(a.cap, s.flow[a.edge]);
        } else {
          assert.deepEqual([u, v], [a.from, a.to]);
          assert.equal(a.cap, cap - s.flow[a.edge]);
        }
        assert.ok(a.cap > 0, `状態 ${k}: 増加路に容量 0 の辺がある`);
      });
      assert.equal(s.d, Math.min(...s.arcs.map((a) => a.cap)));
    }
    if (s.phase === "push") {
      const p = sts[k - 1];
      assert.equal(p.phase, "path");
      assert.deepEqual(s.path, p.path);
      assert.deepEqual(s.arcs, p.arcs);
      assert.equal(s.d, p.d);
      assert.equal(s.auto, p.auto);
      assert.deepEqual(s.before, p.flow);
      const expect = p.flow.slice();
      for (const a of s.arcs) expect[a.edge] += a.rev ? -s.d : s.d;
      assert.deepEqual(s.flow, expect);
      assert.equal(s.total, p.total + s.d);
      // d は道の上の最小の容量なので、流した後はどれかの辺が使い切られる
      assert.ok(s.arcs.some((a) => (a.rev ? s.flow[a.edge] : E[a.edge][2] - s.flow[a.edge]) === 0));
    }
  }
  const last = sts.at(-1);
  assert.equal(last.phase, "end");
  assert.deepEqual(last.flow, sts.at(-2).flow);
  assert.deepEqual(last.reach, reachOf(c, last.flow));
  assert.ok(!last.reach[t0], "最後に t へ届く");
  const idx = E.map((e, i) => i);
  assert.deepEqual(last.cut, idx.filter((i) => last.reach[E[i][0]] && !last.reach[E[i][1]]));
  assert.deepEqual(last.back, idx.filter((i) => !last.reach[E[i][0]] && last.reach[E[i][1]]));
  // 最大流最小カット：届く側から出る辺は容量いっぱい、入る辺は流量 0 で、容量の和が流量に等しく、全探索の最小カットとも等しい
  for (const i of last.cut) assert.equal(last.flow[i], E[i][2]);
  for (const i of last.back) assert.equal(last.flow[i], 0);
  assert.equal(last.cut.reduce((a, i) => a + E[i][2], 0), last.total);
  assert.equal(last.total, minCutBrute(c), JSON.stringify(c));
  return last;
}

test("本文の例：2 本の増加路で流量 2 になり、2 本目は逆辺 b → a で a → b の流れを押し戻す", () => {
  const sts = run(PAGE);
  checkInvariants(PAGE, sts);
  assert.equal(sts.length, 6); // 元のグラフ + 道 2 本 × 2 + 最後
  assert.deepEqual(sts.map((s) => s.phase), ["init", "path", "push", "path", "push", "end"]);
  assert.deepEqual(sts[1].path, [0, 1, 2, 3]);
  assert.deepEqual(sts[3].path, [0, 2, 1, 3]);
  assert.deepEqual(sts[1].arcs.map((a) => [a.edge, a.rev]), [[0, false], [2, false], [4, false]]);
  assert.deepEqual(sts[3].arcs.map((a) => [a.edge, a.rev]), [[1, false], [2, true], [3, false]]);
  assert.ok(sts.every((s) => !s.auto));
  assert.deepEqual([sts[1].d, sts[3].d], [1, 1]);
  // 流量：1 本目で s→a・a→b・b→t に 1、2 本目で a→b の 1 が打ち消され、s→a→t と s→b→t に 1 ずつ（本文の図の (3)）
  assert.deepEqual(sts[2].flow, [1, 0, 1, 0, 1]);
  assert.deepEqual(sts[4].flow, [1, 1, 0, 1, 1]);
  assert.deepEqual(sts.map((s) => s.total), [0, 0, 1, 1, 2, 2]);
  const last = sts.at(-1);
  assert.deepEqual(last.reach, [true, false, false, false]);
  assert.deepEqual(last.cut, [0, 1]);
  assert.deepEqual(last.back, []);
  assert.equal(last.total, 2);
  // caption
  assert.match(sts[0].caption, /^始点 s から終点 t へ流す。/);
  assert.match(sts[0].caption, /逆辺（破線）は流した分を押し戻すための辺で、まだ容量 0 なので薄く描く/);
  assert.match(sts[1].caption, /^増加路 s → a → b → t を選ぶ。道の上の残りの容量は 1、1、1 で、最小の d = 1 だけ流せる。$/);
  assert.match(sts[2].caption, /通った順辺 s → a・a → b・b → t の容量が 1 減り、その逆辺 a → s・b → a・t → b の容量が 1 増える/);
  assert.match(sts[2].caption, /流量は 0 \+ 1 = 1 になる。$/);
  assert.match(sts[3].caption, /b → a は逆辺で、a → b に流している 1 まで押し戻せる/);
  assert.match(sts[4].caption, /通った辺 s → b・b → a・a → t の容量が 1 減り、逆向きの辺 b → s・a → b・t → a の容量が 1 増える/);
  assert.match(sts[4].caption, /b → a は逆辺なので、元の辺 a → b の流量が 1 から 0 に減る（押し戻す）/);
  assert.match(sts[4].caption, /流量は 1 \+ 1 = 2 になる。$/);
  assert.match(last.caption, /^s から t への増加路はもうない。/);
  assert.match(last.caption, /s から届く頂点（塗った頂点）は s だけで、t には届かない/);
  assert.match(last.caption, /元の辺 s → a・s → b はどれも容量いっぱいに流れていて、容量の和 1 \+ 1 = 2 が今の流量に等しい/);
  assert.match(last.caption, /これが最小カットで、流量 2 が最大である。$/);
  // 1 本目は順辺だけなので「押し戻す」と言わない
  assert.doesNotMatch(sts[1].caption + sts[2].caption, /押し戻/);
});

test("paths を省くと、辺の番号の順に見る DFS が本文と同じ 2 本の道を見つける", () => {
  const sts = run(AUTO);
  checkInvariants(AUTO, sts);
  const page = run(PAGE);
  assert.deepEqual(sts.map((s) => s.path), page.map((s) => s.path));
  assert.deepEqual(sts.map((s) => s.flow), page.map((s) => s.flow));
  assert.ok(sts.filter((s) => s.phase === "path").every((s) => s.auto));
  assert.match(sts[1].caption, /^残余グラフを辺の並びの順に DFS でたどり、増加路 s → a → b → t を見つける。/);
  // 辺の順を変えると、DFS は先に s → a → t を選び、逆辺を使わずに終わる
  const reordered = { ...AUTO, edges: [[0, 1, 1], [0, 2, 1], [1, 3, 1], [1, 2, 1], [2, 3, 1]] };
  const sts2 = run(reordered);
  checkInvariants(reordered, sts2);
  assert.deepEqual(sts2.filter((s) => s.phase === "path").map((s) => s.path), [[0, 1, 3], [0, 2, 3]]);
  assert.ok(sts2.every((s) => !s.arcs || s.arcs.every((a) => !a.rev)));
});

test("渡した道を流し終えても増加路が残れば、続きを DFS で探して最大まで流す", () => {
  const c = { ...PAGE, paths: [[0, 1, 3]] };
  const sts = run(c);
  checkInvariants(c, sts);
  const paths = sts.filter((s) => s.phase === "path");
  assert.deepEqual(paths.map((s) => [s.path, s.auto]), [[[0, 1, 3], false], [[0, 2, 3], true]]);
  assert.equal(sts.at(-1).total, 2);
  // 渡した道だけで最大になれば、DFS の道は足さない
  const c2 = { ...PAGE, paths: [[0, 1, 3], [0, 2, 3]] };
  assert.equal(run(c2).filter((s) => s.phase === "path").length, 2);
});

test("端の場合：辺なし・t へ届かない・s と t が端でない・1 本の辺だけの道・外から入る辺・容量の大きい辺", () => {
  // 辺なし：元のグラフと最後だけ
  let c = { n: 2 };
  let sts = run(c);
  checkInvariants(c, sts);
  assert.deepEqual(sts.map((s) => s.phase), ["init", "end"]);
  assert.match(sts[0].caption, /辺はない/);
  assert.match(sts[1].caption, /増加路は、はじめからない/);
  assert.match(sts[1].caption, /外へ出る元の辺はなく、その容量の和は 0 である/);
  assert.match(sts[1].caption, /流量 0 が最大/);

  // t へ向かう辺がない
  c = { n: 3, edges: [[0, 1, 4], [2, 1, 3]] };
  sts = run(c);
  checkInvariants(c, sts);
  assert.equal(sts.length, 2);
  assert.deepEqual(sts.at(-1).reach, [true, true, false]);
  assert.deepEqual(sts.at(-1).cut, []);
  assert.deepEqual(sts.at(-1).back, [1]);
  assert.match(sts.at(-1).caption, /頂点（塗った頂点）は 0・1 で、2 には届かない/);
  assert.match(sts.at(-1).caption, /外から塗った頂点へ入る元の辺 2 → 1 の流量は 0 である/);

  // s と t が 0 と n−1 でない、1 本の辺だけの道、カットが 1 本
  c = { n: 4, s: 2, t: 1, edges: [[2, 1, 7], [2, 0, 3], [0, 3, 5], [3, 1, 2]] };
  sts = run(c);
  checkInvariants(c, sts);
  assert.deepEqual(sts[1].path, [2, 1]);
  assert.match(sts[1].caption, /道の上の残りの容量は 7 で、d = 7 だけ流せる/);
  assert.doesNotMatch(sts[1].caption, /最小の/);
  assert.equal(sts.at(-1).total, 9);

  c = { n: 3, edges: [[0, 1, 99], [1, 2, 98]] };
  sts = run(c);
  checkInvariants(c, sts);
  assert.match(sts.at(-1).caption, /元の辺 1 → 2 は容量いっぱいに流れていて、その容量 98 が今の流量に等しい/);
  assert.deepEqual(sts.at(-1).reach, [true, true, false]);
});

test("ランダムなグラフで、流量が最小カットの全探索と一致し、渡した増加路の列でも同じ最大に着く", () => {
  let seed = 20261029;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  const pick = (k) => Math.floor(rand() * k);
  let withRev = 0;
  let withRev2 = 0;
  let withBack = 0;
  for (let it = 0; it < 4000; it++) {
    // 偶数回目は向きも乱数のグラフ、奇数回目は辺の 85% を s の側から t の側へ向けたグラフ（増加路が多く、逆辺も使う）
    const layered = it % 2 === 1;
    const n = layered ? 3 + pick(6) : 2 + pick(7);
    const s = pick(n);
    let t = pick(n - 1);
    if (t >= s) t++;
    const rank = Array.from({ length: n }, () => rand());
    rank[s] = -1;
    rank[t] = 2;
    const edges = [];
    const used = new Set();
    const m = layered ? 6 + pick(7) : pick(13);
    for (let k = 0; k < (layered ? 60 : m) && edges.length < m; k++) {
      let u = pick(n), v = pick(n);
      const key = `${Math.min(u, v)}-${Math.max(u, v)}`;
      if (u === v || used.has(key)) continue;
      if (layered && (rank[u] > rank[v]) === (rand() < 0.85)) [u, v] = [v, u];
      used.add(key);
      edges.push([u, v, 1 + pick(rand() < 0.5 ? 3 : 20)]);
    }
    const c = { n, s, t, edges };
    const sts = run(c);
    checkInvariants(c, sts);
    if (sts.some((x) => x.arcs && x.arcs.some((a) => a.rev))) withRev++;
    if (sts.at(-1).back.length > 0) withBack++;

    // 乱択の DFS で作った増加路の列を paths に渡しても受け付け、同じ最大の流量になる
    const flow = edges.map(() => 0);
    const paths = [];
    while (paths.length < 20) {
      const seen = new Array(n).fill(false);
      const stack = [];
      const dfs = (v) => {
        if (v === t) return true;
        seen[v] = true;
        const order = edges.map((e, i) => i).sort(() => rand() - 0.5);
        for (const i of order) {
          const [a, b, cap] = edges[i];
          const step = a === v && cap - flow[i] > 0 ? [b, i, 1] : b === v && flow[i] > 0 ? [a, i, -1] : null;
          if (!step || seen[step[0]]) continue;
          stack.push(step);
          if (dfs(step[0])) return true;
          stack.pop();
        }
        return false;
      };
      if (!dfs(s)) break;
      const d = Math.min(...stack.map(([, i, dir]) => (dir > 0 ? edges[i][2] - flow[i] : flow[i])));
      for (const [, i, dir] of stack) flow[i] += dir * d;
      paths.push([s, ...stack.map(([v]) => v)]);
    }
    const c2 = { n, s, t, edges, paths };
    const sts2 = run(c2);
    checkInvariants(c2, sts2);
    if (sts2.some((x) => x.arcs && x.arcs.some((a) => a.rev))) withRev2++;
    const chosen = sts2.filter((x) => x.phase === "path");
    assert.deepEqual(chosen.slice(0, paths.length).map((x) => x.path), paths);
    assert.ok(chosen.every((x, k) => x.auto === k >= paths.length));
  }
  assert.ok(withRev > 60, `DFS が逆辺を通る場合が少ない：${withRev}`);
  assert.ok(withRev2 > 100, `渡した道が逆辺を通る場合が少ない：${withRev2}`);
  assert.ok(withBack > 300, `外から入る辺がある場合が少ない：${withBack}`);
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const before = JSON.stringify(PAGE);
  assert.deepEqual(run(PAGE), run(PAGE));
  assert.equal(JSON.stringify(PAGE), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const e = [[0, 1, 1]];
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ n: 1 }), /n は/);
  assert.throws(() => viz.states({ n: 9 }), /n は/);
  assert.throws(() => viz.states({ n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ n: 2, s: 2 }), /s は/);
  assert.throws(() => viz.states({ n: 2, t: -1 }), /t は/);
  assert.throws(() => viz.states({ n: 2, s: 1 }), /別の頂点/);
  assert.throws(() => viz.states({ n: 2, edges: "x" }), /edges/);
  assert.throws(() => viz.states({ n: 8, edges: new Array(13).fill([0, 1, 1]) }), /edges/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1]] }), /\[u, v, c\]/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 2, 1]] }), /辺の端/);
  assert.throws(() => viz.states({ n: 2, edges: [[1, 1, 1]] }), /自己ループ/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 0]] }), /容量/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 100]] }), /容量/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1.5]] }), /容量/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1], [0, 1, 2]] }), /1 本/);
  assert.throws(() => viz.states({ n: 2, edges: [[0, 1, 1], [1, 0, 2]] }), /逆向き/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a", "abcd"] }), /labels/);
  assert.throws(() => viz.states({ n: 2, edges: e, labels: ["a", "a"] }), /同じ名前/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0], [0, "1"]] }), /pos/);
  assert.throws(() => viz.states({ n: 2, edges: e, pos: [[0, 0], [0, 0]] }), /同じ位置/);
  assert.throws(() => viz.states({ n: 3, edges: e, pos: [[0, 0], [100, 0], [101, 0]] }), /近すぎ/);
  // paths
  assert.throws(() => viz.states({ ...PAGE, paths: "x" }), /paths は/);
  assert.throws(() => viz.states({ ...PAGE, paths: new Array(21).fill([0, 1, 3]) }), /paths は/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[0]] }), /1 本目：頂点の列/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[0, 4]] }), /1 本目：頂点は/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[0, 1, 0, 3]] }), /1 本目：同じ頂点を 2 度通る/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[1, 3]] }), /1 本目：s から始めて t で終える/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[0, 1, 2]] }), /1 本目：s から始めて t で終える/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[0, 3]] }), /1 本目：s と t を結ぶ辺がない/);
  // 流した後の残余グラフで容量 0 の辺（2 本目の s → a）や、まだ流していない逆辺（1 本目の b → a）は通れない
  assert.throws(() => viz.states({ ...PAGE, paths: [[0, 1, 3], [0, 1, 2, 3]] }), /2 本目：s → a の残りの容量が 0/);
  assert.throws(() => viz.states({ ...PAGE, paths: [[0, 2, 1, 3]] }), /1 本目：b → a の残りの容量が 0/);
});

test("viewBox はステップによらず同じ大きさで、頂点の並ぶ高さに合わせる", () => {
  const vb = viz.viewBox(PAGE, viz.states(PAGE)).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.deepEqual(vb.slice(0, 3), [0, 0, 440]);
  assert.deepEqual(viz.viewBox(PAGE).split(" ").map(Number), vb);
  // 頂点が 2 つ（横一列）なら低く、上下の弧に並ぶと高くなる
  const flat = viz.viewBox({ n: 2, edges: [[0, 1, 1]] }).split(" ").map(Number);
  assert.ok(flat[3] < vb[3]);
});

// 偽の h で render を呼び、作った要素を返す
function draw(s, config) {
  const nodes = [];
  viz.render({ appendChild: (e) => nodes.push(e) }, s, config, (tag, attrs, text) => ({ tag, attrs: attrs || {}, text }));
  return nodes;
}

test("既定の配置：s を左端、t を右端に置き、ほかの頂点を上の弧・下の弧に番号の順に並べる", () => {
  const nodes = draw(viz.states(PAGE)[0], PAGE);
  const at = (v) => {
    const e = nodes.find((x) => x.tag === "circle" && x.attrs["data-vertex"] === v);
    return [e.attrs.cx, e.attrs.cy];
  };
  const [s, a, b, t] = [0, 1, 2, 3].map(at);
  assert.ok(s[0] < a[0] && a[0] < t[0]);
  assert.ok(Math.abs(a[0] - b[0]) < 1e-9);
  assert.ok(a[1] < s[1] && s[1] < b[1]);
  assert.ok(Math.abs(s[1] - t[1]) < 1e-9);
});

test("render は増加路を太線、逆辺を破線、容量 0 を薄く、流した辺の数を「前→後」、届く頂点を塗り、カットを印で描き分ける", () => {
  const sts = viz.states(PAGE);
  const line = (nodes, key) => nodes.find((e) => e.tag === "line" && e.attrs["data-arc"] === key);
  const cap = (nodes, key) => nodes.find((e) => e.tag === "text" && e.attrs["data-cap"] === key);
  const row = (nodes, name) => nodes.find((e) => e.attrs["data-row"] === name);

  // 元のグラフ：順辺は実線で容量 1、逆辺は破線・薄い線で 0
  let nodes = draw(sts[0], PAGE);
  for (let k = 0; k < 5; k++) {
    assert.equal(line(nodes, k + "f").attrs.class, "kp-v-cell");
    assert.equal(line(nodes, k + "f").attrs["stroke-dasharray"], null);
    assert.equal(cap(nodes, k + "f").text, "1");
    assert.match(line(nodes, k + "r").attrs.class, /is-no/);
    assert.equal(line(nodes, k + "r").attrs["stroke-dasharray"], "5 4");
    assert.equal(cap(nodes, k + "r").text, "0");
    assert.match(cap(nodes, k + "r").attrs.class, /is-dim/);
  }
  assert.equal(nodes.filter((e) => e.tag === "path" && e.attrs["data-head"]).length, 10); // 矢じり
  assert.equal(row(nodes, "total").text, "0");
  assert.equal(nodes.filter((e) => e.attrs["data-cut"] !== undefined).length, 0);

  // 1 本目を選ぶ：s→a・a→b・b→t が太線、流す量の行に min
  nodes = draw(sts[1], PAGE);
  for (const key of ["0f", "2f", "4f"]) {
    assert.match(line(nodes, key).attrs.class, /is-focus/);
    assert.match(cap(nodes, key).attrs.class, /is-focus/);
  }
  for (const key of ["1f", "3f", "0r", "2r"]) assert.doesNotMatch(line(nodes, key).attrs.class, /is-focus/);
  assert.equal(row(nodes, "path").text, "s → a → b → t");
  assert.equal(row(nodes, "d").text, "d = min(1, 1, 1) = 1");
  // 太線は薄い線・ふつうの線より後に描く（上に重なる）
  const lines = nodes.filter((e) => e.tag === "line" && e.attrs["data-arc"]);
  assert.ok(lines.slice(-3).every((e) => /is-focus/.test(e.attrs.class)));

  // 1 本目を流す：使い切った順辺は薄く「1→0」、逆辺はふつうの破線で「0→1」
  nodes = draw(sts[2], PAGE);
  assert.equal(cap(nodes, "0f").text, "1→0");
  assert.equal(cap(nodes, "0r").text, "0→1");
  assert.equal(cap(nodes, "2r").text, "0→1");
  assert.equal(cap(nodes, "1f").text, "1");
  assert.match(cap(nodes, "0f").attrs.class, /is-focus/);
  assert.doesNotMatch(cap(nodes, "1f").attrs.class, /is-focus/);
  assert.match(line(nodes, "0f").attrs.class, /is-no/);
  assert.equal(line(nodes, "0r").attrs.class, "kp-v-cell");
  assert.equal(line(nodes, "0r").attrs["stroke-dasharray"], "5 4");
  assert.equal(row(nodes, "total").text, "0 + 1 = 1");

  // 2 本目を選ぶ：逆辺 b→a（2r）が太い破線
  nodes = draw(sts[3], PAGE);
  assert.match(line(nodes, "2r").attrs.class, /is-focus/);
  assert.equal(line(nodes, "2r").attrs["stroke-dasharray"], "7 4");
  assert.equal(row(nodes, "path").text, "s → b → a → t");

  // 2 本目を流す：b→a は「1→0」、a→b は「0→1」（押し戻し）
  nodes = draw(sts[4], PAGE);
  assert.equal(cap(nodes, "2r").text, "1→0");
  assert.equal(cap(nodes, "2f").text, "0→1");
  assert.equal(line(nodes, "2f").attrs.class, "kp-v-cell");

  // 最後：s だけ塗り、s→a・s→b にカットの印、行に流量の最大とカット
  nodes = draw(sts[5], PAGE);
  const circle = (v) => nodes.find((e) => e.tag === "circle" && e.attrs["data-vertex"] === v);
  assert.match(circle(0).attrs.class, /is-answer/);
  for (const v of [1, 2, 3]) assert.doesNotMatch(circle(v).attrs.class, /is-answer/);
  assert.deepEqual(nodes.filter((e) => e.attrs["data-cut"] !== undefined).map((e) => e.attrs["data-cut"]), [0, 1]);
  assert.equal(row(nodes, "path").text, "なし（t に届かない）");
  assert.equal(row(nodes, "total").text, "2（最大）");
  assert.equal(row(nodes, "cut").text, "s → a・s → b（容量の和 2）");
  assert.ok(nodes.some((e) => e.tag === "text" && e.text === "s から届く頂点"));
  // 名前のない頂点では「始点から届く頂点」
  assert.ok(draw(viz.states({ n: 2 })[0], { n: 2 }).some((e) => e.tag === "text" && e.text === "始点から届く頂点"));
});

test("線と矢じりは辺の向き（順辺は u → v、逆辺は v → u）に合い、矢じりの先は行き先の頂点のすぐ外にある", () => {
  const num = String.raw`(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)`;
  const shape = new RegExp(`^M${num} ${num}L${num} ${num}L${num} ${num}z$`);
  const dist = (p, q) => Math.hypot(p[0] - q[0], p[1] - q[1]);
  const configs = [
    PAGE, AUTO,
    // 縦・横・斜めの辺と、s・t が端でない向き
    { n: 4, edges: [[0, 1, 21], [1, 3, 20], [0, 2, 37], [2, 3, 36], [1, 2, 15]], pos: [[0, 0], [0, 1], [3, 0], [3, 1]] },
    { n: 5, s: 3, t: 1, edges: [[3, 0, 4], [0, 1, 2], [3, 4, 3], [4, 2, 3], [2, 1, 5], [0, 2, 2]] },
  ];
  for (const config of configs) {
    const E = config.edges;
    for (const s of viz.states(config)) {
      const nodes = draw(s, config);
      const center = (v) => {
        const e = nodes.find((x) => x.tag === "circle" && x.attrs["data-vertex"] === v);
        return [e.attrs.cx, e.attrs.cy];
      };
      const heads = nodes.filter((e) => e.tag === "path" && e.attrs["data-head"]);
      assert.equal(heads.length, 2 * E.length);
      for (const head of heads) {
        const key = head.attrs["data-head"];
        const [u, v] = E[Number(key.slice(0, -1))];
        const rev = key.endsWith("r");
        const from = center(rev ? v : u), to = center(rev ? u : v);
        const where = `${JSON.stringify(config)} ${s.phase} ${key}`;
        const m = head.attrs.d.match(shape);
        assert.ok(m, `${where}：矢じりの形が読めない（${head.attrs.d}）`);
        const [tx, ty, ax, ay, bx, by] = m.slice(1).map(Number);
        const tip = [tx, ty], base = [(ax + bx) / 2, (ay + by) / 2];
        // 先は行き先の円（半径 17）のすぐ外で、出どころより行き先に近く、底辺の中点より行き先に近い（行き先を向く）
        assert.ok(dist(tip, to) > 17 && dist(tip, to) < 22, `${where}：矢じりの先が行き先の頂点から ${dist(tip, to).toFixed(1)}`);
        assert.ok(dist(tip, to) < dist(tip, from), `${where}：矢じりが出どころの側にある`);
        assert.ok(dist(tip, to) < dist(base, to), `${where}：矢じりが逆を向く`);
        // 線も出どころの側から行き先の側へ引く
        const line = nodes.find((e) => e.tag === "line" && e.attrs["data-arc"] === key);
        const start = [line.attrs.x1, line.attrs.y1], end = [line.attrs.x2, line.attrs.y2];
        assert.ok(dist(end, to) < dist(start, to) && dist(start, from) < dist(end, from), `${where}：線の向きが逆`);
      }
    }
  }
});

// 文字の幅の見積もり（描く側より大きめ：数字・英字・記号 0.62 字、空白 0.35 字、ほか 1 字）
function textBox(e) {
  const style = e.attrs.style || "";
  const m = style.match(/font-size: (\d+)px/);
  const cls = e.attrs.class || "";
  const size = m ? Number(m[1]) : /is-sub/.test(cls) ? 12 : /kp-v-ptr/.test(cls) ? 13 : 16;
  let w = 0;
  for (const ch of String(e.text)) w += /[0-9A-Za-z.,()=+\-]/.test(ch) ? 0.62 : ch === " " ? 0.35 : 1;
  w *= size;
  const anchor = (style.match(/text-anchor: (\w+)/) || [, "middle"])[1];
  const x0 = anchor === "start" ? e.attrs.x : anchor === "end" ? e.attrs.x - w : e.attrs.x - w / 2;
  return { x0, x1: x0 + w, y0: e.attrs.y - size / 2, y1: e.attrs.y + size / 2 };
}

test("文字と図形は枠の中に収まり、座標に NaN がなく、辺の数は自分の線に重ならない", () => {
  const configs = [PAGE, AUTO, { ...PAGE, edges: PAGE.edges.map(([u, v]) => [u, v, 99]) }, { n: 2, edges: [[0, 1, 99]] }];
  for (let n = 3; n <= 8; n++) {
    // 既定の配置で、s から全頂点・全頂点から t・となりどうしに辺を張る
    const edges = [];
    for (let v = 1; v < n - 1 && edges.length < 12; v++) edges.push([0, v, 10 + v], [v, n - 1, 99]);
    configs.push({ n, edges: edges.slice(0, 12) });
  }
  configs.push({ n: 4, edges: [[0, 1, 12], [1, 2, 34], [2, 3, 56], [0, 3, 78]], pos: [[0, 0], [0, 100], [100, 100], [100, 0]] });
  // 左右の端の列に縦の辺があり、2 桁の数（「21→20」など）が端の側に出る配置
  configs.push({ n: 4, edges: [[0, 1, 21], [1, 3, 20], [0, 2, 37], [2, 3, 36], [1, 2, 15]], pos: [[0, 0], [0, 1], [3, 0], [3, 1]] });
  configs.push({ n: 4, edges: [[1, 0, 21], [0, 3, 20], [1, 2, 37], [3, 2, 36]], s: 1, t: 2, pos: [[0, 0], [0, 1], [3, 0], [3, 1]] });
  for (const config of configs) {
    const vb = viz.viewBox(config).split(" ").map(Number);
    for (const s of viz.states(config)) {
      const nodes = draw(s, config);
      for (const e of nodes) {
        for (const [k, v] of Object.entries(e.attrs)) {
          if (typeof v === "number") assert.ok(isFinite(v), `${k} が ${v}`);
          if (k === "d") assert.ok(!/NaN|Infinity/.test(v));
        }
        if (e.tag === "text") {
          const b = textBox(e);
          const where = `${JSON.stringify(config)} ${s.phase} 「${e.text}」`;
          assert.ok(b.x0 >= 0 && b.x1 <= vb[2], `${where} が左右にはみ出す（${b.x0.toFixed(1)}〜${b.x1.toFixed(1)}）`);
          assert.ok(b.y0 >= 0 && b.y1 <= vb[3], `${where} が上下にはみ出す`);
        }
        if (e.tag === "circle") {
          assert.ok(e.attrs.cx - e.attrs.r >= 0 && e.attrs.cx + e.attrs.r <= vb[2]);
          assert.ok(e.attrs.cy - e.attrs.r >= 0 && e.attrs.cy + e.attrs.r <= vb[3]);
        }
      }
      // 辺の数の文字の箱が、同じ辺の線（太線の太さの分を足す）に触れない
      for (const t of nodes.filter((e) => e.attrs["data-cap"])) {
        const l = nodes.find((e) => e.tag === "line" && e.attrs["data-arc"] === t.attrs["data-cap"]);
        const b = textBox(t);
        for (let i = 0; i <= 40; i++) {
          const x = l.attrs.x1 + ((l.attrs.x2 - l.attrs.x1) * i) / 40;
          const y = l.attrs.y1 + ((l.attrs.y2 - l.attrs.y1) * i) / 40;
          const inside = x > b.x0 - 1.5 && x < b.x1 + 1.5 && y > b.y0 - 1.5 && y < b.y1 + 1.5;
          assert.ok(!inside, `${JSON.stringify(config)} ${s.phase}：${t.attrs["data-cap"]} の数「${t.text}」が線に重なる`);
        }
      }
    }
  }
});

test("本文の例では、辺の数どうしが重ならず、数の位置はステップで動かない", () => {
  const sts = viz.states(PAGE);
  const first = new Map();
  for (const s of sts) {
    const caps = draw(s, PAGE).filter((e) => e.attrs["data-cap"]);
    assert.equal(caps.length, 10);
    for (const e of caps) {
      const key = e.attrs["data-cap"];
      if (!first.has(key)) first.set(key, [e.attrs.x, e.attrs.y]);
      assert.deepEqual([e.attrs.x, e.attrs.y], first.get(key), `${key} の数が動く`);
    }
    const boxes = caps.map(textBox);
    for (let i = 0; i < boxes.length; i++) {
      for (let j = 0; j < i; j++) {
        const a = boxes[i], b = boxes[j];
        const overlap = a.x0 < b.x1 && b.x0 < a.x1 && a.y0 < b.y1 && b.y0 < a.y1;
        assert.ok(!overlap, `${s.phase}：${caps[i].attrs["data-cap"]} と ${caps[j].attrs["data-cap"]} の数が重なる`);
      }
    }
  }
});

// 動く図（0-1 ナップサックの表）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/knapsack-table.js", import.meta.url);

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

const raw = loadViz("knapsack-table");
// vm の別の realm で作られた配列は deepStrictEqual で比べられないので、JSON を通してこちらの realm に移す
const viz = { ...raw, states: (c) => JSON.parse(JSON.stringify(raw.states(c))) };

// 本文（docs/dp/knapsack-01.md の meaning の節）の config
const PAGE_CONFIG = { W: 5, items: [{ w: 2, v: 3 }, { w: 1, v: 2 }, { w: 3, v: 4 }], mode: "at-most" };

// 全探索：最初の i 個の部分集合をすべて試す。null は −∞
function brute(config) {
  const { W, items } = config;
  const exact = config.mode === "exact";
  const N = items.length;
  const t = [];
  for (let i = 0; i <= N; i++) {
    const row = [];
    for (let j = 0; j <= W; j++) {
      let best = null;
      for (let m = 0; m < 1 << i; m++) {
        let w = 0, v = 0;
        for (let k = 0; k < i; k++) if (m >> k & 1) { w += items[k].w; v += items[k].v; }
        if (exact ? w === j : w <= j) best = best === null ? v : Math.max(best, v);
      }
      row.push(best);
    }
    t.push(row);
  }
  return t;
}

function checkStates(config, states) {
  const N = config.items.length, cols = config.W + 1;
  assert.equal(states.length, N * cols + 2);
  assert.equal(states[0].phase, "init");
  assert.equal(states.at(-1).phase, "done");
  const truth = brute(config);
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(s.caption.endsWith("。"), `状態 ${k}: caption が句点で終わらない`);
    assert.equal(s.filled, Math.min(cols * (N + 1), cols + k - (s.phase === "done" ? 1 : 0)), `状態 ${k}: filled`);
    // 埋めたマスは全探索の値と一致する
    for (let idx = 0; idx < s.filled; idx++) {
      const r = Math.floor(idx / cols), j = idx % cols;
      assert.equal(s.table[r][j], truth[r][j], `状態 ${k}: dp[${r}][${j}]`);
    }
    if (s.phase === "cell") {
      const i = Math.floor((k - 1) / cols) + 1, j = (k - 1) % cols;
      assert.deepEqual(s.focus, { i, j });
      const it = config.items[i - 1];
      if (j < it.w) assert.equal(s.choice, "only");
      else assert.ok(["keep", "take", "tie", "none"].includes(s.choice));
      assert.match(s.caption, new RegExp(`dp\\[${i}\\]\\[${j}\\]`));
    }
  }
  // 逆にたどった選び方が答えを実現する
  const last = states.at(-1);
  const w = last.picked.reduce((a, k) => a + config.items[k].w, 0);
  const v = last.picked.reduce((a, k) => a + config.items[k].v, 0);
  assert.equal(v, last.answer.value);
  if (config.mode === "exact") {
    assert.equal(w, last.answer.j);
    const row = truth[N].filter((x) => x !== null);
    assert.equal(last.answer.value, Math.max(...row));
  } else {
    assert.ok(w <= config.W);
    assert.equal(last.answer.j, config.W);
    assert.equal(last.answer.value, truth[N][config.W]);
  }
  assert.equal(last.path.length, N + 1);
}

test("本文の例で、最後の行が 0, 2, 3, 5, 6, 7、答えが dp[3][5] = 7（品物 0 と品物 2）になる", () => {
  const states = viz.states(PAGE_CONFIG);
  checkStates(PAGE_CONFIG, states);
  const last = states.at(-1);
  assert.deepEqual(last.table[3], [0, 2, 3, 5, 6, 7]);
  assert.deepEqual(last.answer, { i: 3, j: 5, value: 7 });
  assert.deepEqual(last.picked, [0, 2]);
  assert.match(last.caption, /最後の行は 0, 2, 3, 5, 6, 7 である/);
  assert.match(last.caption, /dp\[3\]\[5\] = 7（品物 0 と品物 2 を選ぶ）/);
  // 各行は左から右へ減らない（本文の記述）
  for (const row of last.table) for (let j = 1; j < row.length; j++) assert.ok(row[j - 1] <= row[j]);
  // 執筆者の報告の caption の例：dp[2][3] = max(dp[1][3], dp[1][2] + 2) = 5
  const s23 = states.find((s) => s.focus && s.focus.i === 2 && s.focus.j === 3);
  assert.match(s23.caption, /dp\[2\]\[3\] = max\(dp\[1\]\[3\], dp\[1\]\[2\] \+ 2\) = max\(3, 3 \+ 2\) = 5 である/);
  assert.equal(s23.choice, "take");
  assert.match(states[0].caption, /すべて 0/);
});

test("全探索と一致する（乱数の品物、以下とちょうどの両方）", () => {
  let seed = 12345;
  const rnd = (n) => { seed = (seed * 1103515245 + 12345) % 2147483648; return seed % n; };
  for (let t = 0; t < 400; t++) {
    const N = 1 + rnd(6), W = 1 + rnd(10);
    const items = Array.from({ length: N }, () => ({ w: 1 + rnd(10), v: rnd(100) }));
    for (const mode of ["at-most", "exact"]) checkStates({ W, items, mode }, viz.states({ W, items, mode }));
  }
});

test("ちょうどの定義：作れない重さは −∞（null）で、答えは最後の行の最大", () => {
  const config = { ...PAGE_CONFIG, mode: "exact" };
  const states = viz.states(config);
  checkStates(config, states);
  assert.deepEqual(states[0].table[0], [0, null, null, null, null, null]);
  assert.match(states[0].caption, /−∞/);
  const last = states.at(-1);
  // 重さ 0〜5 ちょうど：{}, {1}, {0}, {0,1}, {1,2}, {0,2} で 0, 2, 3, 5, 6, 7
  assert.deepEqual(last.table[3], [0, 2, 3, 5, 6, 7]);
  assert.deepEqual(last.answer, { i: 3, j: 5, value: 7 });
  // 品物 0 だけの行では重さ 1・3・4・5 が作れない
  assert.deepEqual(last.table[1], [0, null, 3, null, null, null]);
  const s = states.find((x) => x.focus && x.focus.i === 1 && x.focus.j === 3);
  assert.match(s.caption, /max\(−∞, −∞ \+ 3\) = −∞/);
});

test("端の場合：どの品物も入らない、W ちょうどに詰められない、同じ値", () => {
  // 品物が重すぎて何も入らない
  const big = viz.states({ W: 2, items: [{ w: 5, v: 9 }] });
  assert.equal(big.length, 3 + 2);
  assert.ok(big.slice(1, -1).every((s) => s.choice === "only"));
  assert.deepEqual(big.at(-1).picked, []);
  assert.match(big.at(-1).caption, /何も選ばない/);
  // ちょうど：重さ 2 の品物だけで W = 3 は作れず、答えは重さ 2
  const ex = viz.states({ W: 3, items: [{ w: 2, v: 5 }], mode: "exact" });
  assert.deepEqual(ex.at(-1).table[1], [0, null, 5, null]);
  assert.deepEqual(ex.at(-1).answer, { i: 1, j: 2, value: 5 });
  // 同じ値（選んでも選ばなくても同じ）は tie、たどるときは選ばない側
  const tie = viz.states({ W: 2, items: [{ w: 1, v: 0 }] });
  assert.equal(tie[1].choice, "only");
  assert.equal(tie[2].choice, "tie");
  assert.equal(tie[3].choice, "tie");
  assert.match(tie[2].caption, /どちらも同じ値/);
  assert.deepEqual(tie.at(-1).picked, []);
  assert.match(tie.at(-1).caption, /どの段も真下なので品物を選ばない。$/);
  assert.doesNotMatch(tie.at(-1).caption, /斜めの段/);

  // ちょうどの定義で両方が −∞ のマスは none（どちらも取らない）。値のある同じ値は tie のまま
  const ex3 = viz.states({ W: 3, items: [{ w: 2, v: 3 }], mode: "exact" });
  const c13 = ex3.find((s) => s.focus && s.focus.i === 1 && s.focus.j === 3);
  assert.equal(c13.keep, null);
  assert.equal(c13.take, null);
  assert.equal(c13.choice, "none");
  assert.match(c13.caption, /どちらもまだ作れない重さ/);
  for (const s of ex3) if (s.choice === "tie") assert.notEqual(s.keep, null);
  const picks = viz.states({ W: 5, items: [{ w: 2, v: 3 }] }).at(-1).caption;
  assert.match(picks, /斜めの段で品物を選んでいる。$/);
  // 上限いっぱいの大きさ
  const max = { W: 10, items: Array.from({ length: 6 }, (_, k) => ({ w: k + 1, v: 99 - k })), mode: "at-most" };
  checkStates(max, viz.states(max));
  // mode の省略は at-most
  assert.deepEqual(viz.states({ W: 5, items: PAGE_CONFIG.items }), viz.states(PAGE_CONFIG));
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = JSON.parse(JSON.stringify(PAGE_CONFIG));
  const before = JSON.stringify(config);
  assert.deepEqual(viz.states(config), viz.states(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const items = PAGE_CONFIG.items;
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ items }), /W/);
  assert.throws(() => viz.states({ W: 0, items }), /W/);
  assert.throws(() => viz.states({ W: 11, items }), /W/);
  assert.throws(() => viz.states({ W: 2.5, items }), /W/);
  assert.throws(() => viz.states({ W: "5", items }), /W/);
  assert.throws(() => viz.states({ W: 5 }), /items/);
  assert.throws(() => viz.states({ W: 5, items: [] }), /items/);
  assert.throws(() => viz.states({ W: 5, items: Array(7).fill({ w: 1, v: 1 }) }), /items/);
  assert.throws(() => viz.states({ W: 5, items: [3] }), /items/);
  assert.throws(() => viz.states({ W: 5, items: [{ w: 0, v: 1 }] }), /重さ/);
  assert.throws(() => viz.states({ W: 5, items: [{ w: 11, v: 1 }] }), /重さ/);
  assert.throws(() => viz.states({ W: 5, items: [{ w: 1, v: -1 }] }), /価値/);
  assert.throws(() => viz.states({ W: 5, items: [{ w: 1, v: 100 }] }), /価値/);
  assert.throws(() => viz.states({ W: 5, items: [{ w: 1 }] }), /価値/);
  assert.throws(() => viz.states({ W: 5, items, mode: "unbounded" }), /mode/);
});

test("viewBox は W と品物の数で決まり、ステップによらない", () => {
  const vb = raw.viewBox(PAGE_CONFIG).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  const vb2 = raw.viewBox({ ...PAGE_CONFIG, W: 7 }).split(" ").map(Number);
  assert.equal(vb2[2] - vb[2], 2 * 48);
  assert.equal(vb2[3], vb[3]);
});

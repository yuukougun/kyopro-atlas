// 動く図の見本（二分探索）の、状態の列を作る関数の単体試験（design.md §8.5、design-review D8）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/binary-search.js", import.meta.url);

// ブラウザと同じく window.KPViz.register で登録させて取り出す（package.json の type に左右されない）
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

const viz = loadViz("binary-search");

// 全探索の答え：条件を満たす最初の位置（なければ N）
function firstTrue(a, x, upper) {
  const i = a.findIndex((v) => (upper ? v > x : v >= x));
  return i < 0 ? a.length : i;
}

// どの状態でも「a[0..ng] は条件を満たさず、a[ok..N-1] は満たす」が成り立つ
function checkInvariants(a, x, upper, states) {
  const cond = (v) => (upper ? v > x : v >= x);
  for (const [k, s] of states.entries()) {
    assert.ok(s.ng < s.ok, `状態 ${k}: ng < ok でない`);
    for (let i = 0; i <= s.ng; i++) assert.ok(!cond(a[i]), `状態 ${k}: a[${i}] は満たさないはず`);
    for (let i = s.ok; i < a.length; i++) assert.ok(cond(a[i]), `状態 ${k}: a[${i}] は満たすはず`);
    if (s.mid != null) assert.ok(s.ng < s.mid && s.mid < s.ok, `状態 ${k}: mid が ng と ok の間にない`);
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
  }
}

test("例の配列で a[i] ≥ 8 を満たす最初の位置を見つける", () => {
  const a = [1, 3, 3, 5, 8, 13, 21, 34];
  const states = viz.states({ array: a, target: 8 });
  assert.equal(states[0].phase, "start");
  assert.equal(states[0].ng, -1);
  assert.equal(states[0].ok, a.length);
  const last = states.at(-1);
  assert.equal(last.phase, "done");
  assert.equal(last.ok, 4);
  assert.equal(last.ng, 3);
  checkInvariants(a, 8, false, states);
  // 調べるたびに「調べる」「端を動かす」の2つの状態がある
  const probes = states.filter((s) => s.phase === "probe").length;
  assert.equal(states.length, 2 + 2 * probes);
});

test("同じ値が続くときは lower は最初、upper はその次の位置になる", () => {
  const a = [2, 2, 2, 2];
  assert.equal(viz.states({ array: a, target: 2 }).at(-1).ok, 0);
  assert.equal(viz.states({ array: a, target: 2, mode: "upper" }).at(-1).ok, 4);
  assert.equal(viz.states({ array: a, target: 3 }).at(-1).ok, 4); // 満たす位置がない
  assert.equal(viz.states({ array: a, target: 1 }).at(-1).ok, 0);
});

test("ランダムな単調な配列で全探索の答えと一致し、不変条件と調べる回数の上限が保たれる", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 16);
    const a = [];
    let v = Math.floor(rand() * 5) - 2;
    for (let i = 0; i < n; i++) {
      v += Math.floor(rand() * 3);
      a.push(v);
    }
    const x = Math.floor(rand() * (a[n - 1] - a[0] + 5)) + a[0] - 2;
    for (const mode of ["lower", "upper"]) {
      const upper = mode === "upper";
      const states = viz.states({ array: a, target: x, mode });
      const last = states.at(-1);
      assert.equal(last.phase, "done");
      assert.equal(last.ok, firstTrue(a, x, upper), `a=${JSON.stringify(a)} x=${x} mode=${mode}`);
      assert.equal(last.ok - last.ng, 1);
      checkInvariants(a, x, upper, states);
      const probes = states.filter((s) => s.phase === "probe").length;
      assert.ok(probes <= Math.ceil(Math.log2(n + 1)), `調べる回数 ${probes} が多い（N=${n}）`);
    }
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { array: [1, 4, 4, 9], target: 4, mode: "upper" };
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(JSON.parse(JSON.stringify(s1)), JSON.parse(JSON.stringify(s2)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states({ array: [3, 1, 2], target: 2 }), /単調/);
  assert.throws(() => viz.states({ array: [], target: 1 }), /array/);
  assert.throws(() => viz.states({ array: new Array(17).fill(0), target: 1 }), /array/);
  assert.throws(() => viz.states({ array: [1, 2], target: "2" }), /target/);
  assert.throws(() => viz.states({ array: [1, Number.NaN], target: 1 }), /数/);
  assert.throws(() => viz.states({ array: [1, 2], target: 2, mode: "middle" }), /mode/);
  assert.throws(() => viz.states(null), /data-config/);
});

test("viewBox は配列の長さと番兵の2列分の幅になる", () => {
  const vb = viz.viewBox({ array: [1, 2, 3] }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  const vb2 = viz.viewBox({ array: [1, 2, 3, 4, 5, 6] }).split(" ").map(Number);
  assert.equal(vb2[2] / vb[2], 8 / 5);
});

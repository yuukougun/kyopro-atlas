// 動く図（最長増加部分列の二分探索版）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/lis.js", import.meta.url);

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

const viz = loadViz("lis");
// vm の別の realm で作られた配列を、この realm の値に直してから比べる
const plain = (x) => JSON.parse(JSON.stringify(x));
const run = (config) => plain(viz.states(config));

// 素朴な O(N^2) の DP（図とは別に書いた答え）
function naiveDp(a, strict) {
  const dp = [];
  for (let i = 0; i < a.length; i++) {
    let best = 0;
    for (let j = 0; j < i; j++) if ((strict ? a[j] < a[i] : a[j] <= a[i]) && dp[j] > best) best = dp[j];
    dp.push(best + 1);
  }
  return dp;
}

// 部分列の全探索で LIS の長さ（N ≤ 8 なので 2^N 通り）
function bruteLis(a, strict) {
  let best = 0;
  for (let mask = 1; mask < 1 << a.length; mask++) {
    const s = a.filter((_, i) => mask & (1 << i));
    if (s.every((v, i) => i === 0 || (strict ? s[i - 1] < v : s[i - 1] <= v))) best = Math.max(best, s.length);
  }
  return best;
}

// どの状態でも L が昇順（狭義なら狭義、広義なら広義）で、状態の並びが start・(find, update)×N・done になる
function checkInvariants(a, strict, states) {
  const n = a.length;
  assert.equal(states.length, 2 * n + 2);
  assert.equal(states[0].phase, "start");
  assert.equal(states.at(-1).phase, "done");
  for (const [t, s] of states.entries()) {
    for (let k = 1; k < s.L.length; k++) {
      assert.ok(strict ? s.L[k - 1] < s.L[k] : s.L[k - 1] <= s.L[k], `状態 ${t}: L が昇順でない`);
    }
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${t}: caption が空`);
    if (t >= 1 && t <= 2 * n) {
      const i = Math.floor((t - 1) / 2);
      assert.equal(s.i, i);
      assert.equal(s.phase, t % 2 === 1 ? "find" : "update");
    }
  }
}

test("本文の例 (3, 1, 4, 1, 5, 9, 2, 6) で、表と同じ位置・L・dp になる", () => {
  const a = [3, 1, 4, 1, 5, 9, 2, 6];
  const states = run({ array: a, strict: true });
  checkInvariants(a, true, states);
  const updates = states.filter((s) => s.phase === "update");
  // 本文の表：位置 k、置換か追加か、入れた後の L、a_i で終わる最長
  assert.deepEqual(updates.map((s) => s.k), [0, 0, 1, 0, 2, 3, 1, 3]);
  assert.deepEqual(updates.map((s) => s.old), [null, 3, null, 1, null, null, 4, 9]);
  assert.deepEqual(plain(updates.map((s) => s.L)), [
    [3], [1], [1, 4], [1, 4], [1, 4, 5], [1, 4, 5, 9], [1, 2, 5, 9], [1, 2, 5, 6],
  ]);
  assert.deepEqual(plain(states.at(-1).dp), [1, 1, 2, 1, 3, 4, 2, 4]);
  assert.deepEqual(plain(states.at(-1).dp), naiveDp(a, true));
  assert.equal(states.at(-1).L.length, 4);
  // 4 つ目の 1 は値が同じ置換、6 つ目の 9 は追加
  assert.match(updates[3].caption, /値は変わらない/);
  assert.match(updates[5].caption, /追加/);
  assert.match(states.at(-1).caption, /長さは L の要素数の 4/);
  // find の状態の L は入れる前のもの
  const finds = states.filter((s) => s.phase === "find");
  assert.deepEqual(plain(finds[6].L), [1, 4, 5, 9]);
  assert.equal(finds[6].k, 1);
});

test("確認問題 (1, 1, 1)：狭義は長さ 1、広義は長さ 3", () => {
  const s1 = run({ array: [1, 1, 1], strict: true });
  assert.deepEqual(plain(s1.at(-1).L), [1]);
  assert.deepEqual(s1.filter((s) => s.phase === "update").map((s) => s.k), [0, 0, 0]);
  const s2 = run({ array: [1, 1, 1], strict: false });
  assert.deepEqual(plain(s2.at(-1).L), [1, 1, 1]);
  assert.deepEqual(s2.filter((s) => s.phase === "update").map((s) => s.k), [0, 1, 2]);
  assert.match(s2[0].caption, /upper_bound/);
});

test("端の場合：1 要素・減少列・増加列・負の値・strict の省略", () => {
  assert.deepEqual(plain(run({ array: [7] }).at(-1).L), [7]);
  const dec = run({ array: [5, 4, 3, 2, 1] });
  assert.deepEqual(plain(dec.at(-1).L), [1]);
  assert.ok(dec.filter((s) => s.phase === "update").every((s) => s.k === 0));
  const inc = run({ array: [-3, 0, 2, 99] });
  assert.deepEqual(plain(inc.at(-1).L), [-3, 0, 2, 99]);
  assert.ok(inc.filter((s) => s.phase === "update").every((s) => s.old === null));
  assert.match(inc[1].caption, /−3/);
  // strict の省略は狭義
  assert.deepEqual(plain(run({ array: [2, 2] }).at(-1).L), [2]);
});

test("ランダムな列で、L の長さが全探索の LIS と、k + 1 が素朴な DP と一致する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const span = 1 + Math.floor(rand() * 10);
    const a = Array.from({ length: n }, () => Math.floor(rand() * span) - 3);
    for (const strict of [true, false]) {
      const states = run({ array: a, strict });
      checkInvariants(a, strict, states);
      const last = states.at(-1);
      assert.equal(last.L.length, bruteLis(a, strict), `a=${JSON.stringify(a)} strict=${strict}`);
      const ref = naiveDp(a, strict);
      assert.deepEqual(plain(last.dp), ref);
      const updates = states.filter((s) => s.phase === "update");
      updates.forEach((s, i) => {
        assert.equal(s.k + 1, ref[i]);
        // find と update の差は位置 k の 1 か所だけ
        const before = states[2 * i + 1].L;
        assert.equal(s.L.length, before.length + (s.old === null ? 1 : 0));
        s.L.forEach((v, k) => assert.equal(v, k === s.k ? a[i] : before[k]));
      });
    }
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { array: [3, 1, 4, 1, 5], strict: false };
  const before = JSON.stringify(config);
  assert.deepEqual(run(config), run(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => run(null), /data-config/);
  assert.throws(() => run({ array: [] }), /array/);
  assert.throws(() => run({ array: new Array(9).fill(0) }), /array/);
  assert.throws(() => run({ array: [1, 2.5] }), /整数/);
  assert.throws(() => run({ array: [100] }), /99/);
  assert.throws(() => run({ array: [1, "2"] }), /整数/);
  assert.throws(() => run({ array: [1, 2], strict: "yes" }), /strict/);
});

test("viewBox は N = 8 で幅 404 に収まる", () => {
  const vb = viz.viewBox({ array: new Array(8).fill(0) }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.equal(vb[2], 404);
  assert.ok(360 / vb[2] >= 0.75);
});

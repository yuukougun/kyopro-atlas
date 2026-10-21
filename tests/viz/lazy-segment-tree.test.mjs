// 動く図（遅延セグメント木）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/lazy-segment-tree.js", import.meta.url);

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

const viz = loadViz("lazy-segment-tree");

const PAGE_CONFIG = {
  array: [5, 3, 7, 2, 6, 4, 8, 1],
  ops: [
    { type: "add", l: 0, r: 4, x: 2 },
    { type: "add", l: 1, r: 4, x: -3 },
    { type: "min", l: 3, r: 6 },
  ],
};

// ノード k が受け持つ半開区間
function rangeOf(k, size) {
  const dep = Math.floor(Math.log2(k));
  const w = size >> dep;
  const l = (k - (1 << dep)) * w;
  return [l, l + w];
}

// 保つ性質：各ノードの d[k] に、真の祖先の保留の和を足すと、その区間の本当の最小値になる。葉は保留を持たない
function checkInvariant(s, arr, label) {
  const size = s.size;
  for (let k = 1; k < 2 * size; k++) {
    let up = 0;
    for (let p = k >> 1; p >= 1; p >>= 1) up += s.lz[p];
    const [l, r] = rangeOf(k, size);
    let truth = Infinity;
    for (let i = l; i < Math.min(r, arr.length); i++) truth = Math.min(truth, arr[i]);
    assert.equal(s.d[k] + up, truth, `${label}: ノード ${k} の値が保つ性質に合わない`);
  }
  for (let k = size; k < 2 * size; k++) assert.equal(s.lz[k], 0, `${label}: 葉 ${k} が保留を持つ`);
}

// 状態の列を素朴な配列と突き合わせる：各操作の終わりで保つ性質、取得の答えが一致
// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
function runAndCheck(config) {
  const states = structuredClone(viz.states(config));
  const arr = config.array.slice();
  assert.equal(states[0].phase, "init");
  checkInvariant(states[0], arr, "初期状態");
  const answers = [];
  for (const [i, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${i}: caption が空`);
    if (s.phase === "push") {
      assert.equal(s.lz[s.focus], 0, `状態 ${i}: push の後に保留が残る`);
      assert.deepEqual(s.touched, [2 * s.focus, 2 * s.focus + 1]);
    }
    if (s.phase === "take" || s.phase === "apply") {
      const op = config.ops[s.opIndex];
      const [l, r] = rangeOf(s.focus, s.size);
      assert.ok(op.l <= l && r <= op.r, `状態 ${i}: すっぽり入らないノードで止まった`);
    }
    if (s.phase === "end") {
      const op = config.ops[s.opIndex];
      if (op.type === "add") {
        for (let j = op.l; j < op.r; j++) arr[j] += op.x;
      } else {
        let m = Infinity;
        for (let j = op.l; j < op.r; j++) m = Math.min(m, arr[j]);
        assert.equal(s.acc, m, `状態 ${i}: 取得の答えが違う`);
        answers.push(s.acc);
        // 候補にしたノードは互いに重ならず、合わせると区間ちょうどになる
        const covered = [];
        for (const k of s.taken) {
          const [l, r] = rangeOf(k, s.size);
          for (let j = l; j < r; j++) covered.push(j);
        }
        covered.sort((x, y) => x - y);
        assert.deepEqual(covered, Array.from({ length: op.r - op.l }, (_, t) => op.l + t));
      }
      checkInvariant(s, arr, `操作 ${s.opIndex + 1} の終わり`);
    }
  }
  assert.equal(states.filter((s) => s.phase === "end").length, config.ops.length);
  return { states, answers };
}

test("本文の例：加算が保留として止まり、後の操作で子へ降りる", () => {
  const { states, answers } = runAndCheck(PAGE_CONFIG);
  assert.deepEqual(answers, [1]);
  // 操作 1 は [0, 4) のノード（添字 2）に保留 +2 を付けて止まる
  const op1 = states.filter((s) => s.opIndex === 0);
  const ap = op1.filter((s) => s.phase === "apply");
  assert.equal(ap.length, 1);
  assert.equal(ap[0].focus, 2);
  assert.equal(ap[0].lz[2], 2);
  // 操作 2 で、その保留が子へ降りる
  const op2push = states.filter((s) => s.opIndex === 1 && s.phase === "push").map((s) => s.focus);
  assert.deepEqual(op2push, [2, 4]);
  // [2, 4) のノード（添字 5）は +2 と −3 を合わせた保留 −1 を持つ
  const end2 = states.find((s) => s.opIndex === 1 && s.phase === "end");
  assert.equal(end2.lz[5], -1);
  // 取得でも保留が降りる
  const op3push = states.filter((s) => s.opIndex === 2 && s.phase === "push").map((s) => s.focus);
  assert.deepEqual(op3push, [5]);
});

test("取得の終わりの説明は、保留が残っているときだけ「残ったままでよい」と言う", () => {
  const none = viz.states(PAGE_CONFIG).at(-1);
  assert.ok(!none.caption.includes("残ったまま"));
  const some = viz.states({ array: [1, 2, 3, 4], ops: [{ type: "add", l: 0, r: 4, x: 2 }, { type: "min", l: 0, r: 1 }] }).at(-1);
  assert.ok(some.lz.some((v) => v !== 0));
  assert.ok(some.caption.includes("残ったまま"));
});

test("長さが 2 の冪でないときは余りの葉を ∞ で埋める", () => {
  const { states } = runAndCheck({ array: [4, -2, 9], ops: [{ type: "add", l: 1, r: 3, x: 5 }, { type: "min", l: 0, r: 3 }] });
  assert.equal(states[0].size, 4);
  assert.equal(states[0].d[7], Infinity);
  const { answers } = runAndCheck({ array: [7], ops: [{ type: "min", l: 0, r: 1 }, { type: "add", l: 0, r: 1, x: -9 }, { type: "min", l: 0, r: 1 }] });
  assert.deepEqual(answers, [7, -2]);
});

test("ランダムな入力で素朴な方法と一致し、保つ性質が各操作の終わりで成り立つ", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 2000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const array = Array.from({ length: n }, () => Math.floor(rand() * 21) - 10);
    const q = 1 + Math.floor(rand() * 6);
    const ops = [];
    for (let j = 0; j < q; j++) {
      let l = Math.floor(rand() * n);
      let r = l + 1 + Math.floor(rand() * (n - l));
      if (rand() < 0.5) ops.push({ type: "add", l, r, x: Math.floor(rand() * 11) - 5 });
      else ops.push({ type: "min", l, r });
    }
    const { states } = runAndCheck({ array, ops });
    // 1 回の操作で状態になるノードの数は O(log N)（葉の数 8 なら 4 段 × 4 個まで）
    for (let j = 0; j < q; j++) {
      const cnt = states.filter((s) => s.opIndex === j && s.focus != null).length;
      assert.ok(cnt <= 16, `操作 ${j}: 状態が多すぎる（${cnt}）`);
    }
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = JSON.parse(JSON.stringify(PAGE_CONFIG));
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(JSON.parse(JSON.stringify(s1)), JSON.parse(JSON.stringify(s2)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ array: [], ops: [{ type: "min", l: 0, r: 1 }] }), /array/);
  assert.throws(() => viz.states({ array: new Array(9).fill(0), ops: [{ type: "min", l: 0, r: 1 }] }), /array/);
  assert.throws(() => viz.states({ array: [1.5], ops: [{ type: "min", l: 0, r: 1 }] }), /整数/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [] }), /ops/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "set", l: 0, r: 1 }] }), /type/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "min", l: 1, r: 1 }] }), /区間/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "min", l: 0, r: 3 }] }), /区間/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "add", l: 0, r: 2 }] }), /x/);
});

test("viewBox は葉の数に応じた大きさになる", () => {
  const vb = viz.viewBox({ array: [1, 2, 3, 4, 5, 6, 7, 8] }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  const vb2 = viz.viewBox({ array: [1, 2, 3] }).split(" ").map(Number);
  assert.equal(vb[2] / vb2[2], 2);
});

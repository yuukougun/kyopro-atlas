// 動く図（BIT）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/fenwick-tree.js", import.meta.url);

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

const viz = loadViz("fenwick-tree");

// 本文（docs/ds/fenwick-tree.md の #invariants）の config。本文に書いてある値：
// sum(7) は t[7]・t[6]・t[4] を足し（7 → 6 → 4 → 0）、add(3) は t[3]・t[4]・t[8] を直す（3 → 4 → 8）
const PAGE_CONFIG = {
  a: [3, 1, 4, 1, 5, 9, 2, 6],
  ops: [{ type: "sum", i: 7 }, { type: "add", i: 3, x: 2 }],
};

// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
function run(config) {
  return structuredClone(viz.states(config));
}

const lowbit = (i) => i & -i;

// 素朴な t：t[i] = a_{i−lowbit(i)+1} + … + a_i（1-indexed、t[0] = 0）
function naiveT(a1) {
  const n = a1.length - 1;
  const t = new Array(n + 1).fill(0);
  for (let i = 1; i <= n; i++) for (let j = i - lowbit(i) + 1; j <= i; j++) t[i] += a1[j];
  return t;
}

// 状態の列を、操作ごとに素朴な計算と照らし合わせる。各 sum の答えを返す
function checkStates(config, states) {
  const n = config.a.length;
  const a = [0, ...config.a];
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.equal(s.a.length, n + 1);
    assert.equal(s.t.length, n + 1);
  }
  assert.equal(states[0].phase, "init");
  assert.deepEqual(states[0].t, naiveT(a));
  let k = 1;
  const answers = [];
  for (const [j, op] of config.ops.entries()) {
    const start = states[k++];
    assert.equal(start.phase, "start");
    assert.equal(start.opIndex, j);
    assert.equal(start.i, op.i);
    if (op.type === "sum") {
      // i から最下位の 1 を消していき、通った箱の区間が [1, i] を右から隙間なく覆う
      let i = op.i;
      let s = 0;
      const visited = [];
      while (i > 0) {
        const st = states[k++];
        assert.equal(st.phase, "step");
        assert.equal(st.current, i);
        s += st.t[i];
        visited.push(i);
        assert.equal(st.s, s);
        assert.deepEqual(st.visited, visited);
        assert.equal(st.coveredFrom, i - lowbit(i) + 1);
        assert.deepEqual(st.t, naiveT(a), "sum で t が変わった");
        i -= lowbit(i);
      }
      const end = states[k++];
      assert.equal(end.phase, "end");
      assert.equal(end.i, 0);
      let direct = 0;
      for (let q = 1; q <= op.i; q++) direct += a[q];
      assert.equal(end.s, direct, `sum(${op.i}) が素朴な和と違う`);
      assert.deepEqual(end.visited, visited);
      answers.push(end.s);
    } else {
      a[op.i] += op.x;
      assert.deepEqual(start.a, a);
      // i から lowbit を足していき、a_i を含む箱だけをすべて 1 回ずつ通る
      let i = op.i;
      const visited = [];
      while (i <= n) {
        const st = states[k++];
        assert.equal(st.phase, "step");
        assert.equal(st.current, i);
        assert.equal(st.s, null);
        visited.push(i);
        assert.deepEqual(st.visited, visited);
        i += lowbit(i);
      }
      const containing = [];
      for (let b = 1; b <= n; b++) if (b - lowbit(b) < op.i && op.i <= b) containing.push(b);
      assert.deepEqual(visited, containing, `add(${op.i}) が a_${op.i} を含む箱をちょうど通らない`);
      const end = states[k++];
      assert.equal(end.phase, "end");
      assert.ok(end.i > n);
      assert.deepEqual(end.t, naiveT(a), `add(${op.i}) の後の t が定義と違う`);
    }
  }
  assert.equal(k, states.length, "状態の数が合わない");
  return answers;
}

test("本文の例：sum(7) は t[7]・t[6]・t[4] で 25、add(3, +2) は t[3]・t[4]・t[8] を直す", () => {
  const states = run(PAGE_CONFIG);
  assert.deepEqual(checkStates(PAGE_CONFIG, states), [25]);
  assert.deepEqual(states[0].t, [0, 3, 4, 4, 9, 5, 14, 2, 31]);
  const steps = (j) => states.filter((s) => s.opIndex === j && s.phase === "step");
  assert.deepEqual(steps(0).map((s) => s.current), [7, 6, 4]);
  assert.deepEqual(steps(0).map((s) => s.s), [2, 16, 25]);
  assert.deepEqual(steps(1).map((s) => s.current), [3, 4, 8]);
  assert.deepEqual(states.at(-1).t, [0, 3, 4, 6, 11, 5, 14, 2, 33]);
  assert.equal(states.at(-1).i, 16);
  assert.equal(states.length, 1 + (1 + 3 + 1) + (1 + 3 + 1));
  // caption：2 進数と次の i への式
  assert.ok(steps(0)[0].caption.includes("i = 7（2 進で 0111）"), steps(0)[0].caption);
  assert.ok(steps(0)[0].caption.includes("7 − 1 = 6（0110）"), steps(0)[0].caption);
  assert.ok(steps(0)[2].caption.includes("4 − 4 = 0（0000）"), steps(0)[2].caption);
  assert.ok(steps(1)[0].caption.includes("3 + 1 = 4（0100）"), steps(1)[0].caption);
  assert.ok(steps(1)[2].caption.includes("8 + 8 = 16（10000）"), steps(1)[2].caption);
  assert.ok(states[5].caption.includes("sum(7) = s = 25"), states[5].caption);
  assert.ok(states[5].caption.includes("t[7]・t[6]・t[4]"), states[5].caption);
  assert.ok(states.at(-1).caption.includes("t[3]・t[4]・t[8]"), states.at(-1).caption);
});

test("端の場合：sum(0)、sum(N)、N = 1、2 の冪でない N、add(N)、負の x、add の後の sum", () => {
  // sum(0) はループに入らずに 0
  let cfg = { a: [5, 6, 7], ops: [{ type: "sum", i: 0 }] };
  let states = run(cfg);
  assert.deepEqual(checkStates(cfg, states), [0]);
  assert.equal(states.length, 3);
  assert.ok(states[2].caption.includes("sum(0) = 0"), states[2].caption);
  // N = 1
  cfg = { a: [-4], ops: [{ type: "add", i: 1, x: 9 }, { type: "sum", i: 1 }] };
  assert.deepEqual(checkStates(cfg, run(cfg)), [5]);
  // N = 12（2 の冪でない）。sum(12) は t[12]・t[8]、add(5) は t[5]・t[6]・t[8] で、16 > 12 で止まる
  const a12 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12];
  cfg = { a: a12, ops: [{ type: "sum", i: 12 }, { type: "add", i: 5, x: -3 }, { type: "sum", i: 11 }, { type: "add", i: 12, x: 1 }] };
  states = run(cfg);
  assert.deepEqual(checkStates(cfg, states), [78, 63]);
  assert.deepEqual(states.filter((s) => s.opIndex === 0 && s.phase === "step").map((s) => s.current), [12, 8]);
  assert.deepEqual(states.filter((s) => s.opIndex === 1 && s.phase === "step").map((s) => s.current), [5, 6, 8]);
  assert.deepEqual(states.filter((s) => s.opIndex === 2 && s.phase === "step").map((s) => s.current), [11, 10, 8]);
  assert.deepEqual(states.filter((s) => s.opIndex === 3 && s.phase === "step").map((s) => s.current), [12]);
  // 2 進数の桁数は N に合わせる（N = 12 なら 4 桁）
  assert.ok(states.find((s) => s.current === 5).caption.includes("（2 進で 0101）"));
});

test("ランダムな列と操作で、sum が素朴な和と一致し、t が定義どおりに保たれる", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let tc = 0; tc < 3000; tc++) {
    const n = 1 + Math.floor(rand() * 12);
    const a = Array.from({ length: n }, () => Math.floor(rand() * 19) - 9);
    const m = 1 + Math.floor(rand() * 4);
    const ops = [];
    for (let j = 0; j < m; j++) {
      if (rand() < 0.5) ops.push({ type: "sum", i: Math.floor(rand() * (n + 1)) });
      else {
        let x = Math.floor(rand() * 19) - 9;
        if (x === 0) x = 1;
        ops.push({ type: "add", i: 1 + Math.floor(rand() * n), x });
      }
    }
    const cfg = { a, ops };
    checkStates(cfg, run(cfg));
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = structuredClone(PAGE_CONFIG);
  const before = JSON.stringify(config);
  assert.deepEqual(run(config), run(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const sum1 = [{ type: "sum", i: 1 }];
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ ops: sum1 }), /a は/);
  assert.throws(() => viz.states({ a: [], ops: sum1 }), /a は/);
  assert.throws(() => viz.states({ a: new Array(13).fill(0), ops: sum1 }), /a は/);
  assert.throws(() => viz.states({ a: [1.5], ops: sum1 }), /a の要素/);
  assert.throws(() => viz.states({ a: ["1"], ops: sum1 }), /a の要素/);
  assert.throws(() => viz.states({ a: [100], ops: sum1 }), /a の要素/);
  assert.throws(() => viz.states({ a: [1, 2] }), /ops は/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [] }), /ops は/);
  assert.throws(() => viz.states({ a: [1, 2], ops: new Array(5).fill(sum1[0]) }), /ops は/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [null] }), /type/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "min", i: 1 }] }), /type/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "sum", i: 3 }] }), /sum の i/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "sum", i: -1 }] }), /sum の i/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "sum", i: 1.5 }] }), /sum の i/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "add", i: 0, x: 1 }] }), /止まらない/); // i = 0 の add
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "add", i: 3, x: 1 }] }), /add の i/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "add", i: 1 }] }), /add の x/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "add", i: 1, x: 0 }] }), /add の x/);
  assert.throws(() => viz.states({ a: [1, 2], ops: [{ type: "add", i: 1, x: 100 }] }), /add の x/);
  // 各値は範囲内でも、t や sum が絶対値 999 を超えると枠からはみ出す
  const big = new Array(12).fill(99); // t[8] = 792、sum(12) = 1188
  assert.doesNotThrow(() => viz.states({ a: big, ops: [{ type: "sum", i: 8 }] }));
  assert.throws(() => viz.states({ a: big, ops: [{ type: "sum", i: 12 }] }), /絶対値 999/);
  const add1 = { type: "add", i: 1, x: 99 };
  assert.doesNotThrow(() => viz.states({ a: big.slice(0, 8), ops: [add1, add1] })); // t[8] = 990
  assert.throws(() => viz.states({ a: big.slice(0, 8), ops: [add1, add1, add1] }), /絶対値 999/); // t[8] = 1089
  // 幅 1 の枠（a の行と奇数の i の t[i]）に 4 文字の値（−100 以下）が入ると枠の線にかかる
  const neg = { type: "add", i: 9, x: -99 };
  const negA = new Array(12).fill(-99);
  assert.doesNotThrow(() => viz.states({ a: [-99, 5], ops: [{ type: "add", i: 1, x: 99 }] }));
  assert.throws(() => viz.states({ a: [-99, 5], ops: [{ type: "add", i: 1, x: -1 }] }), /幅 1 の枠/); // a_1 = −100
  assert.throws(() => viz.states({ a: negA, ops: [neg, neg, neg, neg] }), /幅 1 の枠/); // a_9 = t[9] = −495
});

test("caption は項や箱の数が少ないときも自然に書く", () => {
  const s1 = viz.states({ a: [-4, 2], ops: [{ type: "sum", i: 1 }, { type: "sum", i: 2 }, { type: "sum", i: 0 }] });
  const starts = s1.filter((s) => s.phase === "start").map((s) => s.caption);
  assert.ok(starts[0].includes("sum(1)：a_1 を求める。"), starts[0]);
  assert.ok(starts[1].includes("sum(2)：a_1 + a_2 を求める。"), starts[1]);
  assert.ok(!starts[0].includes("…") && !starts[1].includes("…"));
  const s3 = run(PAGE_CONFIG).find((s) => s.phase === "start" && s.opIndex === 0).caption;
  assert.ok(s3.includes("a_1 + … + a_7 を求める。"), s3);
  const one = viz.states({ a: Array.from({ length: 12 }, (_, k) => k + 1), ops: [{ type: "add", i: 12, x: 1 }] }).at(-1).caption;
  assert.ok(one.includes("a_12 を含む箱は t[12] だけで、それを直した。"), one);
  assert.ok(!one.includes("すべて"), one);
  const many = run(PAGE_CONFIG).at(-1).caption;
  assert.ok(many.includes("t[3]・t[4]・t[8] の 3 つで、すべて 1 回ずつ直した。"), many);
});

test("viewBox は N と段の数で決まり、ステップによらない。本文の例は狭い画面でも縮みすぎない", () => {
  const vb = viz.viewBox(PAGE_CONFIG).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  assert.ok(vb[2] <= 440, `幅 ${vb[2]} が広すぎる（狭い画面で縮みすぎる）`);
  const more = viz.viewBox({ a: new Array(12).fill(0), ops: PAGE_CONFIG.ops }).split(" ").map(Number);
  assert.ok(more[2] > vb[2]);
  assert.equal(more[3], vb[3]); // N = 8 と N = 12 はどちらも 4 段
  const one = viz.viewBox({ a: [1], ops: [{ type: "sum", i: 1 }] }).split(" ").map(Number);
  assert.ok(one[3] < vb[3]);
});

test("色だけに頼らない：今の箱は太枠、この操作で通った箱は点線、今の i は三角の印", () => {
  const states = viz.states(PAGE_CONFIG);
  const draw = (s) => {
    const nodes = [];
    const svg = { appendChild: (e) => nodes.push(e) };
    viz.render(svg, s, PAGE_CONFIG, (tag, attrs, text) => ({ tag, attrs, text }));
    return nodes;
  };
  const nodes = draw(states[4]); // sum(7) で t[4] を足すステップ（t[7]・t[6] は通った後）
  const box = (label) => {
    const k = nodes.findIndex((e) => e.tag === "text" && e.text === label);
    return nodes[k - 1];
  };
  assert.match(box("t[4]").attrs.class, /is-focus/);
  assert.equal(box("t[4]").attrs["stroke-dasharray"], undefined);
  assert.equal(box("t[7]").attrs["stroke-dasharray"], "5 3");
  assert.equal(box("t[6]").attrs["stroke-dasharray"], "5 3");
  assert.doesNotMatch(box("t[8]").attrs.class, /is-yes|is-focus/);
  assert.equal(nodes.filter((e) => e.tag === "path").length, 1);
  // 箱の幅は lowbit(i) 列ぶん
  assert.ok(Math.abs(box("t[8]").attrs.width + 4 - 8 * (box("t[1]").attrs.width + 4)) < 1e-9);
});

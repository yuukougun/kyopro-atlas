// 動く図（尺取り法）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/two-pointers.js", import.meta.url);

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

const viz = loadViz("two-pointers");

const sumOf = (a, l, r) => a.slice(l, r).reduce((x, y) => x + y, 0);

// 全探索の答え：各 l の r(l)（at-least で満たす r がなければ null）と、条件を満たす空でない区間の数
function brute(a, K, mode) {
  const n = a.length;
  const rl = [];
  let count = 0;
  for (let l = 0; l < n; l++) {
    if (mode === "at-most") {
      let r = l;
      while (r < n && sumOf(a, l, r + 1) <= K) r++;
      rl.push(r);
    } else {
      let r = l;
      while (r <= n && sumOf(a, l, r) < K) r++;
      rl.push(r <= n ? r : null);
    }
    for (let r = l + 1; r <= n; r++) {
      const s = sumOf(a, l, r);
      if (mode === "at-most" ? s <= K : s >= K) count++;
    }
  }
  return { rl, count };
}

// どの状態でも和が区間の中身と一致し、l ≤ r で、l も r も戻らない。at-most なら和はいつも K 以下
function checkInvariants(a, K, mode, states) {
  let pl = 0;
  let pr = 0;
  for (const [k, s] of states.entries()) {
    assert.ok(0 <= s.l && s.l <= s.r && s.r <= a.length, `状態 ${k}: 0 ≤ l ≤ r ≤ N でない`);
    assert.equal(s.sum, sumOf(a, s.l, s.r), `状態 ${k}: 和が区間の中身と違う`);
    if (mode === "at-most") assert.ok(s.sum <= K, `状態 ${k}: 和が K を超えた`);
    assert.ok(s.l >= pl && s.r >= pr, `状態 ${k}: 端が戻った`);
    assert.ok(s.l - pl + s.r - pr <= 2, `状態 ${k}: 一度に動きすぎ`);
    pl = s.l;
    pr = s.r;
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.equal(s.rl.length, a.length);
  }
}

test("本文の例（A = (1, 2, 1, 3, 1, 1, 2)、和が 4 以下）で r(l) = 3, 3, 4, 5, 7, 7, 7 になる", () => {
  const a = [1, 2, 1, 3, 1, 1, 2];
  const states = viz.states({ array: a, K: 4, mode: "at-most" });
  assert.equal(states[0].phase, "start");
  assert.equal(states[0].l, 0);
  assert.equal(states[0].r, 0);
  const last = states.at(-1);
  assert.equal(last.phase, "done");
  assert.deepEqual([...last.rl], [3, 3, 4, 5, 7, 7, 7]);
  assert.equal(last.count, 15);
  assert.match(last.caption, /3, 3, 4, 5, 7, 7, 7/);
  checkInvariants(a, 4, "at-most", states);
  // r(l) は l を進める直前に 1 つずつ決まる。伸ばす 7 回・決める 7 回・進める 6 回
  const cnt = (p) => states.filter((s) => s.phase === p).length;
  assert.equal(cnt("extend"), 7);
  assert.equal(cnt("decide"), 7);
  assert.equal(cnt("advance"), 6);
  assert.equal(states.length, 22);
  // 断った要素の位置（破線の ×）：l = 0〜3 では a[3]・a[3]・a[4]・a[5]、l = 4〜6 は r = N
  assert.deepEqual([...states.filter((s) => s.phase === "decide").map((s) => s.next)], [3, 3, 4, 5, null, null, null]);
});

test("mode を省くと at-most になる", () => {
  const a = [1, 2, 1, 3, 1, 1, 2];
  assert.equal(JSON.stringify(viz.states({ array: a, K: 4 })), JSON.stringify(viz.states({ array: a, K: 4, mode: "at-most" })));
});

test("at-least：同じ列で和が 4 以上になる最小の r と区間の数", () => {
  const a = [1, 2, 1, 3, 1, 1, 2];
  const last = viz.states({ array: a, K: 4, mode: "at-least" }).at(-1);
  const b = brute(a, 4, "at-least");
  assert.deepEqual([...last.rl], b.rl);
  assert.deepEqual([...last.rl], [3, 4, 4, 5, 7, null, null]);
  // 打ち切ったとき、最後の caption は決まった l の範囲と、それより右に答えがないことを書く
  assert.match(last.caption, /l = 0〜4 で 3, 4, 4, 5, 7 と決まった/);
  assert.match(last.caption, /左端 l = 5 以降は条件を満たす右端がない/);
  assert.equal(last.count, b.count);
});

test("端の場合：K = 0、1 要素、要素が K より大きい、0 が並ぶ、全体でも K に届かない", () => {
  // K = 0 で正の要素：どの l でも空区間のまま。l と r が一緒に進む
  let st = viz.states({ array: [2, 1, 3], K: 0 });
  assert.deepEqual([...st.at(-1).rl], [0, 1, 2]);
  assert.equal(st.at(-1).count, 0);
  checkInvariants([2, 1, 3], 0, "at-most", st);
  // 入れずに越えた要素は skipped に残り、出した要素とは区別される
  assert.deepEqual([...st.at(-1).skipped], [true, true, false]);
  assert.deepEqual([...viz.states({ array: [1, 2, 1, 3, 1, 1, 2], K: 4 }).at(-1).skipped], new Array(7).fill(false));
  // 0 は K = 0 でも入れられる
  st = viz.states({ array: [0, 0, 5, 0], K: 0 });
  assert.deepEqual([...st.at(-1).rl], [2, 2, 2, 4]);
  assert.equal(st.at(-1).count, brute([0, 0, 5, 0], 0, "at-most").count);
  // 1 要素
  assert.deepEqual([...viz.states({ array: [5], K: 4 }).at(-1).rl], [0]);
  assert.deepEqual([...viz.states({ array: [5], K: 5 }).at(-1).rl], [1]);
  assert.deepEqual([...viz.states({ array: [5], K: 5, mode: "at-least" }).at(-1).rl], [1]);
  // 全体でも K に届かない：最初の l で打ち切り、区間は 0 個
  st = viz.states({ array: [1, 1, 1], K: 10, mode: "at-least" });
  assert.deepEqual([...st.at(-1).rl], [null, null, null]);
  assert.equal(st.at(-1).count, 0);
  assert.equal(st.filter((s) => s.phase === "none").length, 1);
  // 全体が K 以下：r は最初の l で N まで伸び、あとは l だけが進む
  st = viz.states({ array: [1, 1, 1], K: 10 });
  assert.deepEqual([...st.at(-1).rl], [3, 3, 3]);
  assert.equal(st.at(-1).count, 6);
});

test("ランダムな列で全探索の答えと一致し、不変条件が保たれる", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const a = Array.from({ length: n }, () => Math.floor(rand() * (rand() < 0.3 ? 3 : 10)));
    for (const mode of ["at-most", "at-least"]) {
      const K = Math.floor(rand() * 25) + (mode === "at-least" ? 1 : 0);
      const states = viz.states({ array: a, K, mode });
      const last = states.at(-1);
      const b = brute(a, K, mode);
      assert.equal(last.phase, "done");
      assert.deepEqual([...last.rl], b.rl, `a=${JSON.stringify(a)} K=${K} mode=${mode}`);
      assert.equal(last.count, b.count, `a=${JSON.stringify(a)} K=${K} mode=${mode}`);
      checkInvariants(a, K, mode, states);
      // 端の動きは合計 2N 回以下（O(N)）
      assert.ok(states.length <= 2 + 3 * n, `状態が多すぎる（N=${n}、${states.length}）`);
    }
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { array: [3, 1, 4, 1, 5], K: 5, mode: "at-most" };
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(JSON.parse(JSON.stringify(s1)), JSON.parse(JSON.stringify(s2)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ array: [], K: 1 }), /array/);
  assert.throws(() => viz.states({ array: new Array(9).fill(1), K: 1 }), /array/);
  assert.throws(() => viz.states({ array: [1, -1], K: 1 }), /0 以上/);
  assert.throws(() => viz.states({ array: [1, 1.5], K: 1 }), /整数/);
  assert.throws(() => viz.states({ array: [1, 100], K: 1 }), /99/);
  assert.throws(() => viz.states({ array: [1, 2], K: "3" }), /K/);
  assert.throws(() => viz.states({ array: [1, 2], K: -1 }), /K/);
  assert.throws(() => viz.states({ array: [1, 2], K: 0, mode: "at-least" }), /K/);
  assert.throws(() => viz.states({ array: [1, 2], K: 3, mode: "exact" }), /mode/);
});

test("viewBox は配列の長さに合わせた幅で、高さは一定", () => {
  const vb = viz.viewBox({ array: [1, 2, 3] }).split(" ").map(Number);
  const vb2 = viz.viewBox({ array: [1, 2, 3, 4, 5, 6] }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  assert.ok(vb2[2] > vb[2]);
  assert.equal(vb[3], vb2[3]);
  // 本文の例（N = 7）はスマホの幅 360px に収まる
  assert.ok(viz.viewBox({ array: [1, 2, 1, 3, 1, 1, 2] }).split(" ").map(Number)[2] <= 360);
  // 上限の N = 8 でも、幅 360 の画面で 0.75 倍以上に収まる
  assert.ok(360 / viz.viewBox({ array: new Array(8).fill(1) }).split(" ").map(Number)[2] >= 0.75);
});

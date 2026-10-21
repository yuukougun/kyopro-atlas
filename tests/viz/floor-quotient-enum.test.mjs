// 動く図「商の列挙」の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/floor-quotient-enum.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/floor-quotient-enum.js", import.meta.url);

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

const viz = loadViz("floor-quotient-enum");

const isqrt = (n) => {
  let s = 0;
  while ((s + 1) * (s + 1) <= n) s++;
  return s;
};

// 全探索：i = 1〜N の ⌊N/i⌋ を並べ、同じ値の連続を区間にまとめる
function bruteBlocks(n) {
  const out = [];
  for (let i = 1; i <= n; i++) {
    const q = Math.floor(n / i);
    if (out.length && out.at(-1).q === q) out.at(-1).r = i;
    else out.push({ l: i, r: i, q });
  }
  return out;
}

function checkStates(n, states) {
  const blocks = bruteBlocks(n);
  const s = isqrt(n);
  assert.equal(states.length, blocks.length + 2, `N=${n}: 状態の数`);
  assert.equal(states[0].phase, "start");
  assert.equal(states[0].cur, -1);
  assert.equal(states[0].sum, 0);
  assert.equal(states.at(-1).phase, "done");
  assert.equal(states.at(-1).cur, blocks.length);
  let sum = 0;
  for (const [k, b] of blocks.entries()) {
    const st = states[k + 1];
    sum += (b.r - b.l + 1) * b.q;
    assert.equal(st.phase, "block");
    assert.equal(st.cur, k);
    assert.deepEqual([st.l, st.q, st.r], [b.l, b.q, b.r], `N=${n} 区間 ${k}`);
    // 右端の式 r = ⌊N/⌊N/l⌋⌋ と、左端は前の右端 + 1
    assert.equal(st.r, Math.floor(n / Math.floor(n / st.l)));
    assert.equal(st.l, k === 0 ? 1 : blocks[k - 1].r + 1);
    assert.equal(st.sum, sum);
    // l ≤ √N の区間は幅 1、l > √N の区間は商が √N 未満
    if (st.l <= s) assert.equal(st.r, st.l, `N=${n}: l=${st.l} ≤ √N なのに幅が 1 でない`);
    else assert.ok(st.q * st.q < n, `N=${n}: l=${st.l} > √N なのに q=${st.q} が √N 以上`);
    assert.ok(st.caption.includes(`和に (${b.r} − ${b.l} + 1) × ${b.q} = ${(b.r - b.l + 1) * b.q} を足して ${sum} になる`));
  }
  let brute = 0;
  for (let i = 1; i <= n; i++) brute += Math.floor(n / i);
  assert.equal(states.at(-1).sum, brute, `N=${n}: 和`);
  // 区間の数は 2s か、⌊N/s⌋ = s のときだけ 2s − 1（本文 #why-sqrt）
  assert.equal(blocks.length, Math.floor(n / s) === s ? 2 * s - 1 : 2 * s, `N=${n}: 区間の数`);
  for (const [k, st] of states.entries()) {
    assert.equal(typeof st.caption, "string");
    assert.ok(st.caption.length > 0, `状態 ${k}: caption が空`);
    assert.equal(st.s, s);
  }
}

test("本文の N = 20：8 区間で和は 66、区間 [7, 10] で 8 を足す", () => {
  const states = viz.states({ n: 20 });
  checkStates(20, states);
  const got = JSON.parse(JSON.stringify(states.filter((s) => s.phase === "block").map((s) => [s.l, s.r, s.q])));
  assert.deepEqual(got, [[1, 1, 20], [2, 2, 10], [3, 3, 6], [4, 4, 5], [5, 5, 4], [6, 6, 3], [7, 10, 2], [11, 20, 1]]);
  assert.equal(states.at(-1).sum, 66);
  assert.equal(states.at(-1).blocks.length, 8);
  assert.equal(states[0].s, 4);
  const b7 = states.find((s) => s.l === 7);
  assert.ok(b7.caption.startsWith("l = 7、q = ⌊20/7⌋ = 2、r = ⌊20/2⌋ = 10。和に (10 − 7 + 1) × 2 = 8 を足して"));
  assert.match(b7.caption, /l > √N の側なので、商 q = 2 は √N より小さい/);
  assert.match(states[1].caption, /l ≤ √N の側なので、幅 1 の区間である/);
  assert.match(states[0].caption, /√20 ≈ 4\.47/);
  assert.match(states.at(-1).caption, /区間は 8 個（√N より左に 4 個、右に 4 個）で、Σ ⌊20\/i⌋ = 66 である/);
});

test("確認問題の N = 10：5 区間（⌊10/3⌋ = 3 = s なので 2s − 1）", () => {
  const states = viz.states({ n: 10 });
  checkStates(10, states);
  const got = JSON.parse(JSON.stringify(states.filter((s) => s.phase === "block").map((s) => [s.l, s.r, s.q])));
  assert.deepEqual(got, [[1, 1, 10], [2, 2, 5], [3, 3, 3], [4, 5, 2], [6, 10, 1]]);
  assert.equal(states.at(-1).sum, 27);
});

test("端の場合：N = 1、平方数、N = 2・3、上限の 30", () => {
  const one = viz.states({ n: 1 });
  checkStates(1, one);
  assert.equal(one.length, 3);
  assert.equal(one[1].l, 1);
  assert.equal(one[1].r, 1);
  assert.equal(one.at(-1).sum, 1);
  // N = 1 には i > √N の棒がないので、右側を説明しない
  assert.doesNotMatch(one[0].caption, /i > √N/);
  assert.match(one[0].caption, /1 本だけ/);
  assert.match(viz.states({ n: 20 })[0].caption, /右（i > √N）の値はどれも √N 未満である。/);
  const sq = viz.states({ n: 16 });
  checkStates(16, sq);
  assert.match(sq[0].caption, /√16 = 4/);
  checkStates(2, viz.states({ n: 2 }));
  checkStates(3, viz.states({ n: 3 }));
  checkStates(30, viz.states({ n: 30 }));
});

test("N = 1〜30 のすべてで全探索の区間・和と一致する", () => {
  for (let n = 1; n <= 30; n++) checkStates(n, viz.states({ n }));
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { n: 12 };
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(JSON.parse(JSON.stringify(s1)), JSON.parse(JSON.stringify(s2)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({}), /n は/);
  assert.throws(() => viz.states({ n: 0 }), /n は/);
  assert.throws(() => viz.states({ n: -3 }), /n は/);
  assert.throws(() => viz.states({ n: 31 }), /n は/);
  assert.throws(() => viz.states({ n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ n: "20" }), /n は/);
  assert.throws(() => viz.states({ n: Number.NaN }), /n は/);
  assert.throws(() => viz.states({ n: Infinity }), /n は/);
});

test("render が全ステップで描け、座標に NaN が出ない。viewBox はステップによらない", () => {
  // 偽の h：属性を記録するだけ
  const h = (tag, attrs, text) => ({ tag, attrs: attrs || {}, text });
  for (const n of [1, 2, 10, 16, 20, 30]) {
    const config = { n };
    const states = viz.states(config);
    const vb = viz.viewBox(config, states).split(" ").map(Number);
    assert.equal(vb.length, 4);
    assert.ok(vb.every((v) => Number.isFinite(v)) && vb[2] > 0 && vb[3] > 0);
    for (const st of states) {
      const els = [];
      viz.render({ appendChild: (e) => els.push(e) }, st, config, h);
      assert.ok(els.length > n, `N=${n}: 描いた要素が少ない`);
      for (const e of els) {
        for (const [k, v] of Object.entries(e.attrs)) {
          if (typeof v === "number") assert.ok(Number.isFinite(v), `N=${n}: ${e.tag} の ${k} が ${v}`);
          if (["x", "x1", "x2"].includes(k)) assert.ok(v >= 0 && v <= vb[2], `N=${n}: ${e.tag} の ${k}=${v} が幅の外`);
          if (["y", "y1", "y2"].includes(k)) assert.ok(v >= 0 && v <= vb[3], `N=${n}: ${e.tag} の ${k}=${v} が高さの外`);
        }
      }
      // いまの区間だけが太枠（is-focus）
      const focus = els.filter((e) => e.tag === "rect" && /is-focus/.test(e.attrs.class));
      assert.equal(focus.length, st.phase === "block" ? 1 : 0);
    }
  }
});

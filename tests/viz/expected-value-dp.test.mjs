// 動く図（期待値 DP）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/expected-value-dp.js", import.meta.url);

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

const raw = loadViz("expected-value-dp");
// vm の中で作った配列は、こちらの Array と別物で deepEqual が通らないので、JSON を通してこちらの値にする
const viz = {
  states: (config) => JSON.parse(JSON.stringify(raw.states(config))),
  viewBox: (config) => raw.viewBox(config),
};

// 本文（docs/comb/expected-value-dp.md）の div の config
const PAGE_CONFIG = { hp: { n: 4, p: "1/2" }, sugoroku: { a: [3, 2, 1] } };

const close = (x, y, eps = 1e-9) => Math.abs(x - y) <= eps;

// 素朴な方法 1（HP）：漸化式を使わず、「いまの HP と攻撃回数」の確率分布を前から配り、
// HP が 0 以下になった時点の回数に確率を掛けて足す
function hpBrute(n, p) {
  if (n <= 0) return 0;
  let dist = new Map([[n, 1]]);
  let ans = 0;
  for (let step = 1; dist.size > 0; step++) {
    const next = new Map();
    for (const [hp, pr] of dist) {
      for (const [d, q] of [[2, p], [1, 1 - p]]) {
        if (q === 0) continue;
        const t = hp - d;
        if (t <= 0) ans += step * pr * q;
        else next.set(t, (next.get(t) ?? 0) + pr * q);
      }
    }
    dist = next;
  }
  return ans;
}

// 素朴な方法 2（すごろく）：位置の確率分布を 1 回ずつ前に進め、ゴールに着いた回数に確率を掛けて足す。
// 自己ループで分布は終わらないので、残りの確率が十分小さくなるまで回す
function sugorokuBrute(a) {
  const goal = a.length;
  let dist = new Array(goal + 1).fill(0);
  dist[0] = 1;
  let ans = 0;
  for (let step = 1; step < 100000; step++) {
    const next = new Array(goal + 1).fill(0);
    for (let i = 0; i < goal; i++) {
      if (dist[i] === 0) continue;
      const q = dist[i] / (a[i] + 1);
      for (let k = 0; k <= a[i]; k++) next[i + k] += q;
    }
    ans += step * next[goal];
    next[goal] = 0;
    dist = next;
    if (dist.reduce((s, v) => s + v, 0) < 1e-15) break;
  }
  return ans;
}

// 埋めた値は二度と変わらず、値は後ろ（終状態の側）から順に決まり、caption は空でない
function checkStates(states) {
  let prev = null;
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(!/です|ます。/.test(s.caption), `状態 ${k}: だ・である調でない`);
    if (prev && prev.part === s.part) {
      prev.e.forEach((v, i) => {
        if (v != null) assert.equal(s.e[i], v, `状態 ${k}: 決まった値 E[${i}] が変わった`);
      });
      const added = s.e.filter((v) => v != null).length - prev.e.filter((v) => v != null).length;
      assert.ok(added === 0 || added === 1, `状態 ${k}: 1 ステップに 2 つ以上の値が決まった`);
      if (added === 1) assert.ok(prev.e[s.focus] == null && s.e[s.focus] != null, `状態 ${k}: 決まった値が focus にない`);
    }
    // 決まっている値の集合は、終状態の側から連続している
    const known = s.e.map((v) => v != null);
    if (s.part === "hp") {
      const cnt = known.filter(Boolean).length;
      known.forEach((b, i) => assert.equal(b, i < cnt, `状態 ${k}: HP の小さい順に埋まっていない`));
    } else {
      const cnt = known.filter(Boolean).length;
      known.forEach((b, i) => assert.equal(b, i >= known.length - cnt, `状態 ${k}: 後ろから埋まっていない`));
    }
    if (s.focus != null) assert.ok(s.focus >= 0 && s.focus < s.e.length, `状態 ${k}: focus が範囲の外`);
    prev = s;
  }
}

test("本文の config：前半の HP の例の値が 0・1・1.5・2.25・2.875 になる", () => {
  const states = viz.states(PAGE_CONFIG);
  checkStates(states);
  const hp = states.filter((s) => s.part === "hp");
  assert.equal(hp[0].phase, "start");
  assert.deepEqual(hp.map((s) => s.phase), ["start", "terminal", "fill", "fill", "fill", "fill", "done"]);
  const last = hp.at(-1);
  assert.deepEqual(last.e, [0, 1, 1.5, 2.25, 2.875]);
  assert.deepEqual(last.eText, ["0", "1", "3/2", "9/4", "23/8"]);
  assert.ok(close(last.e[4], hpBrute(4, 0.5)));
  // 本文の式の例：E[2] = 1 + 1/2 · 0 + 1/2 · 1 = 1.5、E[3] = 2.25
  assert.match(hp[3].caption, /E\[2\] = 1 \+ 1\/2 × E\[0\] \+ 1\/2 × E\[1\]/);
  assert.match(hp[4].caption, /9\/4 = 2\.25/);
  assert.match(last.caption, /23\/8 = 2\.875/);
});

test("本文の config：後半の自己ループのすごろくの値が self-loop.cpp と同じ 17/6・2.5・2・0 になる", () => {
  const states = viz.states(PAGE_CONFIG);
  const sg = states.filter((s) => s.part === "sugoroku");
  assert.deepEqual(sg.map((s) => s.phase),
    ["start", "terminal", "before", "after", "before", "after", "before", "after", "done"]);
  const last = sg.at(-1);
  assert.deepEqual(last.eText, ["17/6", "5/2", "2", "0"]);
  assert.ok(close(last.e[0], 2.8333333333, 1e-9));
  assert.ok(close(last.e[0], sugorokuBrute([3, 2, 1]), 1e-9));
  // 移項前の状態では値はまだ決まらず、右辺に自分自身がある。移項後の状態で値が決まる
  for (let j = 2; j < sg.length - 1; j += 2) {
    const before = sg[j], after = sg[j + 1];
    assert.equal(before.focus, after.focus);
    const i = before.focus;
    assert.equal(before.e[i], null);
    assert.notEqual(after.e[i], null);
    assert.ok(before.caption.includes(`E[${i}] = 1 + `) && before.caption.includes(`× E[${i}]`), "移項前の式がない");
    assert.ok(after.caption.includes("左辺へ移す"), "移項後の式がない");
  }
});

test("ランダムな config で、素朴な方法（確率の分布を前に配る）と一致する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 300; t++) {
    const n = 1 + Math.floor(rand() * 7);
    const b = 1 + Math.floor(rand() * 10);
    const a0 = Math.floor(rand() * (b + 1));
    const N = 2 + Math.floor(rand() * 6);
    const a = [];
    for (let i = 0; i < N - 1; i++) a.push(1 + Math.floor(rand() * (N - 1 - i)));
    const states = viz.states({ hp: { n, p: `${a0}/${b}` }, sugoroku: { a } });
    checkStates(states);
    const hp = states.filter((s) => s.part === "hp").at(-1);
    for (let h = 0; h <= n; h++) assert.ok(close(hp.e[h], hpBrute(h, a0 / b), 1e-9), `n=${h} p=${a0}/${b}`);
    const sg = states.filter((s) => s.part === "sugoroku").at(-1);
    assert.ok(close(sg.e[0], sugorokuBrute(a), 1e-7), `a=${JSON.stringify(a)}`);
  }
});

test("端の場合：p = 0 なら E[h] = h、p = 1 なら ⌈h/2⌉、HP 1 は 1、A がすべて 1 なら 2 × 残りのマス数", () => {
  const z = viz.states({ hp: { n: 5, p: "0/1" } }).at(-1);
  assert.deepEqual(z.e, [0, 1, 2, 3, 4, 5]);
  assert.ok(!z.caption.includes("0 ×"));
  const o = viz.states({ hp: { n: 5, p: 1 } }).at(-1);
  assert.deepEqual(o.e, [0, 1, 1, 2, 2, 3]);
  const one = viz.states({ hp: { n: 1, p: 0.25 } });
  assert.deepEqual(one.map((s) => s.phase), ["start", "terminal", "fill", "done"]);
  assert.deepEqual(one.at(-1).e, [0, 1]);
  assert.equal(viz.states({ hp: { n: 3, p: 0.5 } }).at(-1).e[3], 2.25); // 数で書いても同じ
  const ones = viz.states({ sugoroku: { a: [1, 1, 1] } }).at(-1);
  assert.deepEqual(ones.e, [6, 4, 2, 0]);
  const tiny = viz.states({ sugoroku: { a: [1] } });
  assert.deepEqual(tiny.map((s) => s.phase), ["start", "terminal", "before", "after", "done"]);
  assert.deepEqual(tiny.at(-1).e, [2, 0]);
  // 片方だけなら、その部分だけの状態になる
  assert.ok(viz.states({ hp: { n: 2, p: "1/3" } }).every((s) => s.part === "hp"));
  assert.ok(viz.states({ sugoroku: { a: [2, 1] } }).every((s) => s.part === "sugoroku"));
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
  assert.throws(() => viz.states({}), /少なくとも一方/);
  assert.throws(() => viz.states({ hp: { n: 0, p: "1/2" } }), /hp\.n/);
  assert.throws(() => viz.states({ hp: { n: 8, p: "1/2" } }), /hp\.n/);
  assert.throws(() => viz.states({ hp: { n: 2.5, p: "1/2" } }), /hp\.n/);
  assert.throws(() => viz.states({ hp: { n: 3, p: "3/2" } }), /hp\.p/);
  assert.throws(() => viz.states({ hp: { n: 3, p: "1/0" } }), /hp\.p/);
  assert.throws(() => viz.states({ hp: { n: 3, p: "half" } }), /hp\.p/);
  assert.throws(() => viz.states({ hp: { n: 3, p: 1.5 } }), /hp\.p/);
  assert.throws(() => viz.states({ hp: { n: 3, p: 1 / 3 } }), /hp\.p/);
  assert.throws(() => viz.states({ hp: { n: 3 } }), /hp\.p/);
  assert.throws(() => viz.states({ sugoroku: { a: [] } }), /sugoroku\.a/);
  assert.throws(() => viz.states({ sugoroku: { a: [1, 1, 1, 1, 1, 1, 1] } }), /sugoroku\.a/);
  assert.throws(() => viz.states({ sugoroku: { a: [3, 1] } }), /sugoroku\.a/); // ゴールを越える
  assert.throws(() => viz.states({ sugoroku: { a: [0, 1] } }), /sugoroku\.a/);
  assert.throws(() => viz.states({ sugoroku: [3, 2, 1] }), /sugoroku\.a/);
});

test("viewBox は全ステップで同じ 1 つの大きさで、状態の数が増えると広がる", () => {
  const vb = viz.viewBox(PAGE_CONFIG).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  const wide = viz.viewBox({ hp: { n: 7, p: "1/2" } }).split(" ").map(Number);
  assert.ok(wide[2] > vb[2]);
});

test("箱の文字列は 6 文字以下で、長い分数は小数 2 桁の近似になる（すべての HP の config と、すべてのすごろくの config）", () => {
  const check = (states, label) => {
    for (const s of states) {
      s.eShort.forEach((t, i) => {
        if (t == null) return;
        assert.ok(t.length <= 6, `${label}：箱 ${i} の「${t}」が長い`);
        if (t.startsWith("≈")) assert.ok(close(Number(t.slice(1)), s.e[i], 0.005), `${label}：箱 ${i} の近似`);
        else if (t.includes("/")) {
          const [x, y] = t.split("/").map(Number);
          assert.ok(close(x / y, s.e[i], 1e-12));
        } else assert.ok(close(Number(t), s.e[i], 1e-12));
      });
    }
  };
  for (let n = 1; n <= 7; n++) {
    for (let b = 1; b <= 100; b++) {
      for (let a0 = 0; a0 <= b; a0++) check(viz.states({ hp: { n, p: `${a0}/${b}` } }), `n=${n} p=${a0}/${b}`);
    }
  }
  // 長さ L（1〜6）の A で、1 ≤ A_i かつ i + A_i ≤ L を満たすものすべて
  for (let L = 1; L <= 6; L++) {
    const a = new Array(L).fill(1);
    const go = (i) => {
      if (i === L) { check(viz.states({ sugoroku: { a: a.slice() } }), `a=${a}`); return; }
      for (let v = 1; i + v <= L; v++) { a[i] = v; go(i + 1); }
    };
    go(0);
  }
  // 本文の config は近似を使わない
  const page = viz.states(PAGE_CONFIG).at(-1);
  assert.ok(page.eShort.every((t) => t == null || !t.startsWith("≈")));
});

test("p = 0 か p = 1 のとき、説明文は描かない側の矢印の先を挙げない", () => {
  const z = viz.states({ hp: { n: 3, p: 0 } }).filter((s) => s.phase === "fill");
  assert.match(z[0].caption, /1 のダメージで HP 0/);
  assert.match(z[2].caption, /HP 2 の値はもう決まっている（確率 1）/);
  assert.ok(!z[2].caption.includes("HP 1 と"));
  const o = viz.states({ hp: { n: 3, p: 1 } }).filter((s) => s.phase === "fill");
  assert.match(o[0].caption, /2 のダメージで HP 0/);
  assert.match(o[2].caption, /HP 1 の値はもう決まっている（確率 1）/);
  assert.ok(!o[2].caption.includes("HP 2"));
});

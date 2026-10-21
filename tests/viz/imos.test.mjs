// 動く図（いもす法）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/imos.js", import.meta.url);

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

const viz = loadViz("imos");

// 本文（docs/basics/imos.md の #imos-1d）の config と、本文と図 imos-1d.svg に書いてある値
const PAGE_CONFIG = { n: 8, ops: [{ l: 1, r: 5, x: 1 }, { l: 3, r: 7, x: 2 }] };
const PAGE_D = [0, 1, 0, 2, 0, -1, 0, -2, 0];
const PAGE_A = [0, 1, 1, 3, 3, 2, 2, 0];

// 素朴に区間を 1 つずつ塗った答え
function naive(n, ops) {
  const a = new Array(n).fill(0);
  for (const { l, r, x } of ops) for (let i = l; i < r; i++) a[i] += x;
  return a;
}

// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
function run(config) {
  return structuredClone(viz.states(config));
}

// 状態の列の形と、各段階で成り立つ性質を確かめ、最後の A を返す
function checkStates(config, states) {
  const { n, ops } = config;
  assert.equal(states.length, 1 + 2 * ops.length + n + 1, "状態の数が 初期 + 2×操作 + N + 終わり でない");
  assert.equal(states[0].phase, "init");
  assert.deepEqual(states[0].d, new Array(n + 1).fill(0));
  assert.deepEqual(states[0].a, new Array(n).fill(null));
  const d = new Array(n + 1).fill(0);
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.equal(s.d.length, n + 1);
    assert.equal(s.a.length, n);
  }
  // 記録の段階：D[l] += x、D[r] −= x の順に 1 か所ずつ変わる
  for (const [j, op] of ops.entries()) {
    const plus = states[1 + 2 * j];
    const minus = states[2 + 2 * j];
    assert.equal(plus.phase, "plus");
    assert.equal(minus.phase, "minus");
    assert.equal(plus.opIndex, j);
    assert.equal(plus.focusD, op.l);
    assert.equal(minus.focusD, op.r);
    d[op.l] += op.x;
    assert.deepEqual(plus.d, d, `操作 ${j + 1} の D[l] += x の後の D`);
    d[op.r] -= op.x;
    assert.deepEqual(minus.d, d, `操作 ${j + 1} の D[r] −= x の後の D`);
    assert.ok(plus.caption.includes(`D[${op.l}] +=`));
    assert.ok(minus.caption.includes(`D[${op.r}] −=`));
  }
  // 累積の段階：cur = D[0] + … + D[i] で、A は 0〜i まで埋まり、D はもう変わらない
  const sweeps = states.filter((s) => s.phase === "sweep");
  assert.equal(sweeps.length, n);
  let cur = 0;
  for (const [i, s] of sweeps.entries()) {
    cur += d[i];
    assert.equal(s.cursor, i);
    assert.equal(s.cur, cur);
    assert.equal(s.a[i], cur);
    for (let k = i + 1; k < n; k++) assert.equal(s.a[k], null, `累積 ${i}: A[${k}] がもう埋まっている`);
    assert.deepEqual(s.d, d);
  }
  const last = states.at(-1);
  assert.equal(last.phase, "done");
  assert.deepEqual(last.d, d);
  assert.ok(last.a.every((v) => v !== null));
  return last.a;
}

test("本文の例（N = 8、[1, 5) に +1、[3, 7) に +2）で、D と A が本文の値になる", () => {
  const states = run(PAGE_CONFIG);
  const a = checkStates(PAGE_CONFIG, states);
  assert.deepEqual(states.filter((s) => s.phase === "minus").at(-1).d, PAGE_D);
  assert.deepEqual(a, PAGE_A);
  assert.ok(states.at(-1).caption.includes("A = 0, 1, 1, 3, 3, 2, 2, 0"));
  assert.equal(states.length, 1 + 4 + 8 + 1);
});

test("端の場合：l = 0、r = N（番兵に書く）、N = 1、同じ位置に印が重なる、負の x", () => {
  // r = N は番兵 D[N] に書き、累積には入らない
  let cfg = { n: 4, ops: [{ l: 0, r: 4, x: 3 }] };
  let states = run(cfg);
  assert.deepEqual(checkStates(cfg, states), [3, 3, 3, 3]);
  assert.equal(states.at(-1).d[4], -3);
  assert.ok(states[2].caption.includes("番兵"));
  assert.ok(!states[2].caption.includes("から先は打ち消して"), "r = N なのに打ち消す先があるように書いている");
  assert.ok(states[3].caption.includes("A[0] = cur = D[0] = 3"), states[3].caption);
  assert.ok(states[4].caption.includes("A[1] = cur = D[0] + D[1] = 3"), states[4].caption);
  assert.ok(states[5].caption.includes("D[0] + … + D[2]"), states[5].caption);
  // N = 1
  cfg = { n: 1, ops: [{ l: 0, r: 1, x: 5 }] };
  assert.deepEqual(checkStates(cfg, run(cfg)), [5]);
  // 区間がちょうど接する（前の r と次の l が同じ位置）と、印が打ち消し合って 0 になる
  cfg = { n: 5, ops: [{ l: 0, r: 2, x: 1 }, { l: 2, r: 5, x: 1 }] };
  states = run(cfg);
  assert.deepEqual(checkStates(cfg, states), [1, 1, 1, 1, 1]);
  assert.equal(states.at(-1).d[2], 0);
  assert.ok(states[3].caption.includes("前の印"));
  // 負の x と、同じ区間をくり返す
  cfg = { n: 3, ops: [{ l: 1, r: 3, x: -2 }, { l: 1, r: 3, x: -2 }, { l: 0, r: 2, x: 7 }] };
  assert.deepEqual(checkStates(cfg, run(cfg)), [7, 3, -4]);
  // 1 要素の区間
  cfg = { n: 12, ops: [{ l: 11, r: 12, x: 99 }, { l: 0, r: 1, x: -99 }] };
  assert.deepEqual(checkStates(cfg, run(cfg)), [-99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99]);
});

test("ランダムな操作で、素朴に塗った答えと一致する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 12);
    const m = 1 + Math.floor(rand() * 4);
    const ops = [];
    for (let j = 0; j < m; j++) {
      const l = Math.floor(rand() * n);
      const r = l + 1 + Math.floor(rand() * (n - l));
      let x = Math.floor(rand() * 19) - 9;
      if (x === 0) x = 1;
      ops.push({ l, r, x });
    }
    const cfg = { n, ops };
    assert.deepEqual(checkStates(cfg, run(cfg)), naive(n, ops), JSON.stringify(cfg));
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = structuredClone(PAGE_CONFIG);
  const before = JSON.stringify(config);
  assert.deepEqual(run(config), run(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ n: 0, ops: [{ l: 0, r: 1, x: 1 }] }), /n は/);
  assert.throws(() => viz.states({ n: 13, ops: [{ l: 0, r: 1, x: 1 }] }), /n は/);
  assert.throws(() => viz.states({ n: 2.5, ops: [{ l: 0, r: 1, x: 1 }] }), /n は/);
  assert.throws(() => viz.states({ n: 4, ops: [] }), /ops は/);
  assert.throws(() => viz.states({ n: 4 }), /ops は/);
  assert.throws(() => viz.states({ n: 4, ops: new Array(5).fill({ l: 0, r: 1, x: 1 }) }), /ops は/);
  assert.throws(() => viz.states({ n: 4, ops: [null] }), /ops の要素/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 2, r: 2, x: 1 }] }), /区間/); // 空の区間
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 3, r: 1, x: 1 }] }), /区間/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: -1, r: 1, x: 1 }] }), /区間/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 5, x: 1 }] }), /区間/); // r > N
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 1, x: 0 }] }), /x/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 1, x: 1.5 }] }), /x/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 1, x: "1" }] }), /x/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 1, x: 100 }] }), /x/);
  // 各 x は範囲内でも、重なって D や A が絶対値 99 を超えると枠からはみ出す
  const big = { l: 0, r: 2, x: -99 };
  assert.throws(() => viz.states({ n: 12, ops: [big, big, big, big] }), /D と A の値/);
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 2, x: 60 }, { l: 1, r: 3, x: 60 }] }), /D と A の値/); // A[1] = 120
  assert.throws(() => viz.states({ n: 4, ops: [{ l: 0, r: 2, x: 60 }, { l: 2, r: 4, x: -60 }] }), /D と A の値/); // D[2] = −120
  assert.doesNotThrow(() => viz.states({ n: 4, ops: [{ l: 0, r: 2, x: 99 }, { l: 2, r: 4, x: 99 }] })); // D[2] は 0 に打ち消す
});

test("viewBox は N + 1 列と操作の数に応じた大きさで、ステップによらない", () => {
  const vb = viz.viewBox(PAGE_CONFIG).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  assert.ok(vb[2] <= 440, `幅 ${vb[2]} が広すぎる（狭い画面で縮みすぎる）`);
  const more = viz.viewBox({ n: 8, ops: [...PAGE_CONFIG.ops, { l: 0, r: 1, x: 1 }] }).split(" ").map(Number);
  assert.equal(more[2], vb[2]);
  assert.ok(more[3] > vb[3]);
});

test("番兵に書き込むステップでは、番兵の枠を注目の塗りと太枠にし、点線を属性で残す", () => {
  const cfg = { n: 4, ops: [{ l: 0, r: 4, x: 3 }] };
  const states = viz.states(cfg);
  const cellsOf = (s) => {
    const nodes = [];
    const svg = { appendChild: (e) => nodes.push(e) };
    const h = (tag, attrs, text) => ({ tag, attrs, text });
    viz.render(svg, s, cfg, h);
    return nodes.filter((e) => e.tag === "rect" && /kp-v-cell/.test(e.attrs.class));
  };
  // D の枠は先頭の n + 1 個。D[4] が番兵
  const minusCell = cellsOf(states[2])[4];
  assert.ok(/is-focus/.test(minusCell.attrs.class) && /is-yes/.test(minusCell.attrs.class));
  assert.ok(!/is-sentinel/.test(minusCell.attrs.class));
  assert.equal(minusCell.attrs["stroke-dasharray"], "4 3");
  const initCell = cellsOf(states[0])[4];
  assert.ok(/is-sentinel/.test(initCell.attrs.class));
});

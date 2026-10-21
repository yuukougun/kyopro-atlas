// 動く図（桁 DP の一致フラグ）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/digit-dp-tight.js", import.meta.url);

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

const raw = loadViz("digit-dp-tight");
// vm の別の realm で作られた配列は deepStrictEqual で比べられないので、JSON を通してこちらの realm に移す
const viz = { ...raw, states: (c) => JSON.parse(JSON.stringify(raw.states(c))) };

// 本文（docs/dp/digit-dp.md の tight-flag の節）の config
const PAGE_CONFIG = { digits: "253", base: 10 };

// 全探索：0〜N の各 X を L 桁にそろえ、初めて N と異なる桁ごとに数える（N 自身は別に数える）
function bruteByFirstDiff(digits, base) {
  const L = digits.length;
  const n = parseInt(digits, base);
  const byPos = new Array(L).fill(0);
  let self = 0;
  for (let x = 0; x <= n; x++) {
    const s = x.toString(base).padStart(L, "0");
    const p = [...s].findIndex((ch, i) => ch !== digits[i]);
    if (p < 0) self++;
    else {
      assert.ok(s[p] < digits[p], `X = ${s} は桁 ${p} で N より大きい`);
      byPos[p]++;
    }
  }
  return { byPos, self, n };
}

function checkStates(config, states) {
  const L = config.digits.length;
  assert.equal(states.length, L + 2);
  assert.equal(states[0].phase, "start");
  assert.equal(states.at(-1).phase, "done");
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.ok(s.caption.endsWith("。"), `状態 ${k}: caption が句点で終わらない`);
    assert.equal(s.branches.length, Math.min(k, L), `状態 ${k}: 枝の数`);
    if (k >= 1 && k <= L) {
      assert.equal(s.phase, "digit");
      assert.equal(s.focus, k - 1);
      assert.equal(s.decided, k);
    }
    // sum は枝の合計（done では N 自身の 1 を足す）
    const t = s.branches.reduce((a, b) => a + b.total, 0);
    assert.equal(s.sum, t + (s.phase === "done" ? 1 : 0), `状態 ${k}: sum`);
  }
}

test("本文の N = 253 で、枝が 2 × 100・5 × 10・3 × 1 になり、合計 254 が 0〜253 の個数と一致する", () => {
  const states = viz.states(PAGE_CONFIG);
  checkStates(PAGE_CONFIG, states);
  const last = states.at(-1);
  assert.deepEqual(
    last.branches.map((b) => [b.count, b.free, b.total]),
    [[2, 100, 200], [5, 10, 50], [3, 1, 3]],
  );
  assert.equal(last.sum, 254);
  assert.match(last.caption, /2 × 100 \+ 5 × 10 \+ 3 \+ 1 = 254/);
  assert.match(last.caption, /0 から 253 までの整数の個数 254/);
  // 本文の箇条と同じ内容が各ステップの説明にある
  assert.match(states[1].caption, /百の位/);
  assert.match(states[1].caption, /0・1 を置くと/);
  assert.match(states[1].caption, /00〜99 の 100 通り/);
  assert.match(states[2].caption, /0〜4 を置くと/);
  assert.match(states[3].caption, /0〜2 を置くと/);
  assert.match(states[3].caption, /N 自身/);
});

test("全探索で、初めて N と異なる桁ごとの個数と、N 自身の 1 個が一致する（10 進と 2 進・3 進）", () => {
  const cases = [];
  for (let n = 0; n <= 1200; n++) cases.push({ digits: String(n), base: 10 });
  for (let n = 0; n < 64; n++) cases.push({ digits: n.toString(2), base: 2 });
  for (let n = 0; n < 243; n++) cases.push({ digits: n.toString(3), base: 3 });
  cases.push({ digits: "999999", base: 10 }, { digits: "100000", base: 10 }, { digits: "777777", base: 8 });
  for (const config of cases) {
    const states = viz.states(config);
    checkStates(config, states);
    const last = states.at(-1);
    const { byPos, self, n } = bruteByFirstDiff(config.digits, config.base);
    assert.deepEqual(last.branches.map((b) => b.total), byPos, JSON.stringify(config));
    assert.equal(self, 1);
    assert.equal(last.sum, n + 1, JSON.stringify(config));
  }
});

test("端の場合：N = 0、数字 0 を含む N、2 進の N", () => {
  const z = viz.states({ digits: "0" });
  assert.equal(z.length, 3);
  assert.equal(z.at(-1).sum, 1);
  assert.match(z[1].caption, /未満になる枝はない/);

  const s = viz.states({ digits: "100" });
  assert.deepEqual(s.at(-1).branches.map((b) => b.total), [100, 0, 0]);
  assert.equal(s.at(-1).sum, 101);
  assert.match(s.at(-1).caption, /1 × 100 \+ 1 = 101/);

  const bin = viz.states({ digits: "1101", base: 2 });
  assert.equal(bin.at(-1).sum, 14);
  assert.match(bin[0].caption, /2 進。10 進で 13/);
  assert.match(bin.at(-1).caption, /1 × 8 \+ 1 × 4 \+ 1 \+ 1 = 14/);
  assert.match(bin[1].caption, /8 の位/);
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { digits: "4096", base: 10 };
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(JSON.parse(JSON.stringify(s1)), JSON.parse(JSON.stringify(s2)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ digits: 253 }), /digits/);
  assert.throws(() => viz.states({ digits: "" }), /digits/);
  assert.throws(() => viz.states({ digits: "1234567" }), /digits/);
  assert.throws(() => viz.states({ digits: "2a3" }), /数字/);
  assert.throws(() => viz.states({ digits: "0253" }), /先頭/);
  assert.throws(() => viz.states({ digits: "102", base: 2 }), /2 進/);
  assert.throws(() => viz.states({ digits: "1", base: 1 }), /base/);
  assert.throws(() => viz.states({ digits: "1", base: 16 }), /base/);
  assert.throws(() => viz.states({ digits: "1", base: 2.5 }), /base/);
});

test("viewBox は桁数に比例した幅で、ステップによらない", () => {
  const vb = viz.viewBox({ digits: "253" }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  const vb6 = viz.viewBox({ digits: "253253" }).split(" ").map(Number);
  assert.equal(vb6[2] - vb[2], 3 * 96);
  assert.equal(vb6[3], vb[3]);
});

test("10 進の位の名前はすべて漢数字で書く（6 桁目は十万の位）", () => {
  const s = viz.states({ digits: "905017", base: 10 });
  const names = s.filter((x) => x.phase === "digit").map((x) => x.caption.split("を決める")[0]);
  assert.deepEqual(names, ["十万の位", "万の位", "千の位", "百の位", "十の位", "一の位"]);
  for (const n of names) assert.doesNotMatch(n, /[0-9]/);
});

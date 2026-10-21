// 動く図（セグメント木）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/segment-tree.js", import.meta.url);

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

const viz = loadViz("segment-tree");

// 本文 docs/ds/segment-tree.md の div と同じ config
const PAGE_CONFIG = {
  array: [5, 3, 7, 2, 6, 4, 8, 1],
  op: "min",
  ops: [
    { type: "prod", l: 1, r: 7 },
    { type: "set", p: 5, x: 0 },
    { type: "prod", l: 1, r: 7 },
  ],
};

const MON = {
  min: { e: Infinity, f: (x, y) => Math.min(x, y) },
  max: { e: -Infinity, f: (x, y) => Math.max(x, y) },
  sum: { e: 0, f: (x, y) => x + y },
};

function rangeOf(k, size) {
  const dep = Math.floor(Math.log2(k));
  const w = size >> dep;
  const l = (k - (1 << dep)) * w;
  return [l, l + w];
}

// 保つ性質：d[k] はノード k が受け持つ区間の総積（余りの葉は単位元）
function checkTree(s, arr, M, label) {
  for (let k = 1; k < 2 * s.size; k++) {
    const [l, r] = rangeOf(k, s.size);
    let t = M.e;
    for (let i = l; i < Math.min(r, arr.length); i++) t = M.f(t, arr[i]);
    assert.equal(s.d[k], t, `${label}: ノード ${k} の値が区間の総積と違う`);
  }
}

// 状態の列を素朴な配列と突き合わせる
// vm の中で作られた配列は別の realm のものなので、structuredClone でこちらの realm に移してから比べる
function runAndCheck(config) {
  const M = MON[config.op ?? "min"];
  const states = structuredClone(viz.states(config));
  const arr = config.array.slice();
  assert.equal(states[0].phase, "init");
  checkTree(states[0], arr, M, "初期状態");
  const answers = [];
  for (const [i, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${i}: caption が空`);
    assert.ok(!/undefined|NaN|null/.test(s.caption), `状態 ${i}: caption に変な語：${s.caption}`);
    const op = s.opIndex >= 0 ? config.ops[s.opIndex] : null;
    if (op && op.type === "prod") {
      // sL は積んだノードを左から、sR は右から結んだもの（可換でなくても順序が合う）
      let sL = M.e;
      for (const k of s.takenL) sL = M.f(sL, s.d[k]);
      let sR = M.e;
      for (const k of s.takenR) sR = M.f(s.d[k], sR);
      assert.equal(s.sL, sL, `状態 ${i}: sL が違う`);
      assert.equal(s.sR, sR, `状態 ${i}: sR が違う`);
      if (s.phase === "step") {
        assert.ok(s.lp < s.rp, `状態 ${i}: l < r でないのにくり返した`);
        assert.ok(s.focus.length <= 2, `状態 ${i}: 1 段で 3 個以上使った`);
        for (const k of s.focus) assert.equal(Math.floor(Math.log2(k)), s.dep, `状態 ${i}: 段の違うノードを使った`);
      }
    }
    if (s.phase === "end") {
      let m = M.e;
      for (let j = op.l; j < op.r; j++) m = M.f(m, arr[j]);
      assert.equal(s.ans, m, `状態 ${i}: 取得の答えが違う`);
      assert.equal(s.lp, s.rp);
      answers.push(s.ans);
      // 使ったノードを左から並べると、互いに重ならず区間ちょうどになる
      const used = s.takenL.concat(s.takenR.slice().reverse());
      const covered = [];
      for (const k of used) {
        const [l, r] = rangeOf(k, s.size);
        for (let j = l; j < r; j++) covered.push(j);
      }
      assert.deepEqual(covered, Array.from({ length: op.r - op.l }, (_, t) => op.l + t));
    }
    if (s.phase === "leaf") {
      arr[op.p] = op.x;
      assert.deepEqual(s.focus, [s.size + op.p]);
    }
    if (s.phase === "pull") {
      const k = s.focus[0];
      assert.equal(s.d[k], M.f(s.d[2 * k], s.d[2 * k + 1]), `状態 ${i}: 子から作り直していない`);
    }
    // 更新の最後の状態（次の状態が別の操作か、列の終わり）で木全体が正しい
    const next = states[i + 1];
    if (op && op.type === "set" && (!next || next.opIndex !== s.opIndex)) {
      checkTree(s, arr, M, `操作 ${s.opIndex + 1} の終わり`);
      // 書き換えたのは葉から根までの経路だけ
      const want = [];
      for (let k = s.size + op.p; k >= 1; k >>= 1) want.push(k);
      assert.deepEqual(s.path, want);
    }
  }
  assert.equal(states.filter((s) => s.phase === "end").length, config.ops.filter((o) => o.type === "prod").length);
  return { states, answers };
}

test("本文の例：[1, 7) は 4 ノードに分かれ、set(5, 0) の後は答えが 0 になる", () => {
  const { states, answers } = runAndCheck(PAGE_CONFIG);
  assert.deepEqual(answers, [2, 0]);
  // 操作 1：葉の段で l = 9、r = 15、1 つ上で l = 5、r = 7、上がると l = r = 3
  const steps1 = states.filter((s) => s.opIndex === 0 && s.phase === "step");
  assert.deepEqual(steps1.map((s) => [s.lp, s.rp]), [[9, 15], [5, 7]]);
  assert.deepEqual(steps1.map((s) => s.focus), [[9, 14], [5, 6]]);
  const end1 = states.find((s) => s.opIndex === 0 && s.phase === "end");
  assert.deepEqual([end1.lp, end1.rp], [3, 3]);
  assert.deepEqual(end1.takenL, [9, 5]);
  assert.deepEqual(end1.takenR, [14, 6]);
  assert.equal(end1.sL, 2); // min(3, 2)
  assert.equal(end1.sR, 4); // min(4, 8)
  assert.ok(end1.caption.includes("min(2, 4) = 2"));
  // 操作 2：葉 13 を 0 にし、ノード 6・3・1 を作り直す
  const op2 = states.filter((s) => s.opIndex === 1);
  assert.deepEqual(op2.map((s) => s.focus[0]), [13, 6, 3, 1]);
  const last2 = op2.at(-1);
  assert.equal(last2.d[13], 0);
  assert.equal(last2.d[6], 0);
  assert.equal(last2.d[3], 0);
  assert.equal(last2.d[1], 0);
  assert.equal(last2.d[2], 2); // 左の部分木は変わらない
  // 操作 3：同じ 4 ノードを使い、[4, 6) の値が 0 になっている
  const end3 = states.find((s) => s.opIndex === 2 && s.phase === "end");
  assert.deepEqual(end3.takenL, [9, 5]);
  assert.deepEqual(end3.takenR, [14, 6]);
  assert.equal(end3.sR, 0);
  // 状態の数：初期 1 + 取得（始め・2 段・終わり）4 + 更新（葉・3 ノード）4 + 取得 4
  assert.equal(states.length, 13);
});

test("空区間はくり返さずに単位元を返す", () => {
  const { states, answers } = runAndCheck({ array: [5, 3, 7], ops: [{ type: "prod", l: 2, r: 2 }, { type: "prod", l: 3, r: 3 }] });
  assert.deepEqual(answers, [Infinity, Infinity]);
  assert.equal(states.filter((s) => s.phase === "step").length, 0);
  assert.ok(states.at(-1).caption.includes("空区間"));
  const max = runAndCheck({ array: [1, 2], op: "max", ops: [{ type: "prod", l: 0, r: 0 }] });
  assert.deepEqual(max.answers, [-Infinity]);
  const sum = runAndCheck({ array: [1, 2], op: "sum", ops: [{ type: "prod", l: 1, r: 1 }] });
  assert.deepEqual(sum.answers, [0]);
});

test("全体の区間は根の 1 ノードで答え、根を越えた段で止まる", () => {
  const { states, answers } = runAndCheck({ array: [5, 3, 7, 2, 6, 4, 8, 1], ops: [{ type: "prod", l: 0, r: 8 }] });
  assert.deepEqual(answers, [1]);
  const end = states.at(-1);
  assert.deepEqual(end.takenL, [1]);
  assert.deepEqual(end.takenR, []);
  assert.equal(end.dep, -1);
  // 右半分 [4, 8) はノード 3
  const half = runAndCheck({ array: [5, 3, 7, 2, 6, 4, 8, 1], ops: [{ type: "prod", l: 4, r: 8 }] });
  assert.deepEqual(half.states.at(-1).takenL, [3]);
});

test("根の段の caption は r − 1 を右の子と呼ばない", () => {
  const states = viz.states({ array: [5, 3, 7, 2, 6, 4, 8, 1], ops: [{ type: "prod", l: 0, r: 8 }] });
  const root = states.filter((s) => s.phase === "step").at(-1);
  assert.equal(root.lp, 1);
  assert.equal(root.rp, 2);
  assert.ok(root.caption.includes("l = 1 は根"));
  assert.ok(root.caption.includes("r − 1 = 1 は根"));
  assert.ok(!root.caption.includes("右の子"), root.caption);
  const one = viz.states({ array: [4], op: "max", ops: [{ type: "prod", l: 0, r: 1 }] });
  assert.ok(!one.find((s) => s.phase === "step").caption.includes("右の子"));
});

test("式は値が単位元と同じでも省かず、省くのは空の sL・sR と余りの葉だけ", () => {
  const states = viz.states({ array: [0, 5, -3], op: "sum", ops: [{ type: "set", p: 2, x: 0 }, { type: "prod", l: 0, r: 3 }] });
  const pulls = states.filter((s) => s.phase === "pull");
  // ノード 3 の子は葉 a2 = 0 と余りの葉：余りの葉は省く
  assert.ok(pulls[0].caption.includes("作り直す：0。"), pulls[0].caption);
  // ノード 1 = 5 + 0：0 を省かない
  assert.ok(pulls[1].caption.includes("5 + 0 = 5"), pulls[1].caption);
  // sR が空なら答えは sL の値だけ。両方に積めば 0 でも式を残す
  const mn = viz.states({ array: [0, 0], op: "sum", ops: [{ type: "prod", l: 0, r: 2 }] });
  assert.ok(mn.at(-1).caption.includes("答えは sL と sR を結んだ 0 である"), mn.at(-1).caption);
  const two = viz.states({ array: [0, 0, 0], op: "sum", ops: [{ type: "prod", l: 1, r: 3 }] });
  assert.ok(two.at(-1).caption.includes("0 + 0 = 0"), two.at(-1).caption);
});

test("長さ 1 の set は「親を根まで作り直す」と書かない", () => {
  const states = viz.states({ array: [4], op: "max", ops: [{ type: "set", p: 0, x: -2 }] });
  const leaf = states.find((s) => s.phase === "leaf");
  assert.ok(leaf.caption.includes("作り直すノードはない"));
  assert.ok(!leaf.caption.includes("親を根まで"));
  assert.ok(leaf.caption.includes("a0 を −2") || leaf.caption.includes("a0 を -2"), leaf.caption);
});

test("長さが 2 の冪でないときは余りの葉を単位元で埋め、長さ 1 も動く", () => {
  const { states, answers } = runAndCheck({ array: [4, -2, 9], ops: [{ type: "set", p: 2, x: -5 }, { type: "prod", l: 0, r: 3 }] });
  assert.equal(states[0].size, 4);
  assert.equal(states[0].d[7], Infinity);
  assert.ok(states[0].caption.includes("余りの葉"));
  assert.deepEqual(answers, [-5]);
  const one = runAndCheck({ array: [7], ops: [{ type: "prod", l: 0, r: 1 }, { type: "set", p: 0, x: -9 }, { type: "prod", l: 0, r: 1 }] });
  assert.deepEqual(one.answers, [7, -9]);
  assert.ok(one.states.find((s) => s.phase === "leaf").caption.includes("作り直すノードはない"));
});

test("値が変わらない作り直しは「変わらない」と書く", () => {
  const states = viz.states({ array: [1, 5], ops: [{ type: "set", p: 1, x: 3 }] });
  assert.ok(states.at(-1).caption.includes("変わらない"));
});

test("ランダムな入力で素朴な方法と一致し、各段で使うノードは 2 個以下", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 3000; t++) {
    const n = 1 + Math.floor(rand() * 8);
    const op = ["min", "max", "sum"][Math.floor(rand() * 3)];
    const array = Array.from({ length: n }, () => Math.floor(rand() * 199) - 99);
    const q = 1 + Math.floor(rand() * 6);
    const ops = [];
    for (let j = 0; j < q; j++) {
      if (rand() < 0.5) ops.push({ type: "set", p: Math.floor(rand() * n), x: Math.floor(rand() * 199) - 99 });
      else {
        const l = Math.floor(rand() * (n + 1));
        const r = l + Math.floor(rand() * (n - l + 1));
        ops.push({ type: "prod", l, r });
      }
    }
    runAndCheck({ array, op, ops });
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
  const P = [{ type: "prod", l: 0, r: 1 }];
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({ array: [], ops: P }), /array/);
  assert.throws(() => viz.states({ array: new Array(9).fill(0), ops: P }), /array/);
  assert.throws(() => viz.states({ array: [1.5], ops: P }), /整数/);
  assert.throws(() => viz.states({ array: [100], ops: P }), /絶対値/);
  assert.throws(() => viz.states({ array: [1], op: "gcd", ops: P }), /op/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [] }), /ops/);
  assert.throws(() => viz.states({ array: [1, 2], ops: new Array(7).fill(P[0]) }), /ops/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "add", l: 0, r: 1 }] }), /type/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "prod", l: 2, r: 1 }] }), /区間/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "prod", l: 0, r: 3 }] }), /区間/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "prod", l: -1, r: 1 }] }), /区間/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "set", p: 2, x: 0 }] }), /p/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "set", p: 0 }] }), /x/);
  assert.throws(() => viz.states({ array: [1, 2], ops: [{ type: "set", p: 0, x: -100 }] }), /x/);
});

test("viewBox は葉の数に応じた大きさで、render は偽の h で例外を出さない", () => {
  const vb = viz.viewBox({ array: [1, 2, 3, 4, 5, 6, 7, 8] }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.equal(vb[2], 416);
  const vb4 = viz.viewBox({ array: [1, 2, 3] }).split(" ").map(Number);
  assert.ok(vb4[3] < vb[3]);
  // 偽の h と svg で全状態を描き、l・r の棒と「sL へ」「sR へ」の印が出ることを確かめる
  const made = [];
  const h = (tag, attrs, text) => {
    const e = { tag, attrs, text };
    made.push(e);
    return e;
  };
  const svg = { appendChild: () => {} };
  const states = viz.states(PAGE_CONFIG);
  for (const s of states) viz.render(svg, s, PAGE_CONFIG, h);
  const texts = made.filter((e) => e.tag === "text").map((e) => String(e.text));
  assert.ok(texts.includes("l = 9"));
  assert.ok(texts.includes("r = 15"));
  assert.ok(texts.includes("l = r = 3"));
  assert.ok(texts.includes("sL へ"));
  assert.ok(texts.includes("sR へ"));
  assert.ok(made.some((e) => e.attrs && e.attrs["stroke-dasharray"]));
  for (const e of made) {
    for (const v of Object.values(e.attrs || {})) assert.ok(!/NaN|undefined/.test(String(v)), `属性に ${v}`);
  }
  // 根の 1 ノードで答える場合（l・r が根より上の段で止まる）も描ける
  const whole = { array: [1, 2, 3, 4], ops: [{ type: "prod", l: 0, r: 4 }] };
  for (const s of viz.states(whole)) viz.render(svg, s, whole, h);
});

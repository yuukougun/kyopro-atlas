// 動く図（Z-algorithm）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/z-algorithm.js", import.meta.url);

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

const viz = loadViz("z-algorithm");

// 素朴な Z 配列（z[0] = N）
function naiveZ(s) {
  const n = s.length;
  const z = [];
  for (let i = 0; i < n; i++) {
    let k = 0;
    while (i + k < n && s[k] === s[i + k]) k++;
    z.push(k);
  }
  return z;
}

// どの状態でも保つ性質と、最後の状態が素朴な方法と一致すること
function checkAll(s, states) {
  const n = s.length;
  const want = naiveZ(s);
  assert.equal(states[0].phase, "start");
  assert.equal(states.at(-1).phase, "done");
  assert.equal(states.length, n + 1);
  assert.deepEqual([...states.at(-1).z], want, `s=${s}`);
  let prevR = 0;
  let prevSuccess = 0;
  for (const [idx, st] of states.entries()) {
    assert.equal(typeof st.caption, "string");
    assert.ok(st.caption.length > 0, `状態 ${idx}: caption が空`);
    // Z-box は S[l, r) = S[0, r − l) を満たし、右端は戻らない
    assert.ok(0 <= st.l && st.l <= st.r && st.r <= n, `状態 ${idx}: 箱が範囲外`);
    assert.equal(s.slice(st.l, st.r), s.slice(0, st.r - st.l), `状態 ${idx}: 箱が接頭辞と一致しない`);
    assert.ok(st.r >= prevR, `状態 ${idx}: r が戻った`);
    prevR = st.newBox ? st.newBox.r : st.r;
    assert.ok(st.success >= prevSuccess);
    prevSuccess = st.success;
    if (st.phase !== "step") continue;
    const i = st.i;
    assert.equal(idx, i, "i は 1 から 1 つずつ進む");
    // 決まった値は素朴な方法と一致し、まだの位置は未定
    for (let q = 0; q < n; q++) assert.equal(st.z[q], q <= i ? want[q] : null, `状態 ${idx}: z[${q}]`);
    // 場合分けが本文の 3 通りの条件どおり
    if (i >= st.r) {
      assert.equal(st.kase, 1);
      assert.equal(st.ref, null);
      assert.equal(st.copy, 0);
    } else {
      assert.equal(st.ref, i - st.l);
      const zr = want[st.ref];
      assert.equal(st.kase, zr < st.r - i ? 2 : 3);
      assert.equal(st.copy, st.kase === 2 ? zr : st.r - i);
    }
    // 比較は copy の位置から連続し、成功の後に失敗が高々 1 回。写す場合は比べない
    if (st.kase === 2) assert.equal(st.comps.length, 0);
    st.comps.forEach((c, t) => {
      assert.equal(c.k, st.copy + t);
      assert.equal(c.ok, s[c.k] === s[i + c.k]);
      if (t < st.comps.length - 1) assert.ok(c.ok, "失敗の後に比較が続く");
    });
    const ok = st.comps.filter((c) => c.ok).length;
    assert.equal(st.z[i], st.copy + ok);
    // 成功した比較が読む位置 i + k はそれまでの r 以上（右端が進む理由）
    for (const c of st.comps) if (c.ok) assert.ok(i + c.k >= st.r);
    // 箱の取り替え
    if (i + st.z[i] > st.r) assert.deepEqual({ ...st.newBox }, { l: i, r: i + st.z[i] });
    else assert.equal(st.newBox, null);
  }
  // 成功した比較は合計 N 回以下（i = 1 からなので N − 1 以下）
  const last = states.at(-1);
  assert.ok(last.success <= n - 1, `成功 ${last.success} が多い（N=${n}）`);
}

test("本文の例 S = aabaabaac の Z 配列と場合分け（静的な図と同じ）", () => {
  const s = "aabaabaac";
  const states = viz.states({ s });
  checkAll(s, states);
  assert.deepEqual([...states.at(-1).z], [9, 1, 0, 5, 1, 0, 2, 1, 0]);
  const steps = states.filter((st) => st.phase === "step");
  assert.deepEqual([...steps.map((st) => st.kase)], [1, 1, 1, 2, 2, 3, 3, 1]);
  // i = 4：Z-box [3, 8) で z[1] = 1 < r − i = 4 を写す
  const s4 = steps[3];
  assert.deepEqual([s4.i, s4.l, s4.r, s4.ref, s4.copy, s4.comps.length], [4, 3, 8, 1, 1, 0]);
  // 比べなくても、箱の内側の対応 S[2] ≠ S[1] から S[5] ≠ S[1] が分かる
  assert.match(s4.caption, /S\[5\] ≠ S\[1\] も、箱の内側の対応 S\[2\] ≠ S\[1\] から分かっている/);
  // i = 6：z[3] = 5 ≥ 2 なので箱の外の S[8] と S[2] を比べて失敗し、z[6] = 2
  const s6 = steps[5];
  assert.deepEqual([s6.i, s6.l, s6.r, s6.ref, s6.copy], [6, 3, 8, 3, 2]);
  assert.deepEqual([...s6.comps.map((c) => ({ ...c }))], [{ k: 2, ok: false }]);
  assert.match(s6.caption, /S\[8\] = c と S\[2\] = b で食い違う/);
  // 成功した比較は i = 1 の 1 回と i = 3 の 5 回で合計 6 回
  assert.equal(states.at(-1).success, 6);
  assert.match(states.at(-1).caption, /\(9, 1, 0, 5, 1, 0, 2, 1, 0\)/);
  assert.match(states.at(-1).caption, /合計 6 回で、N = 9 を超えない/);
});

test("定義の例 aabxaab と、パターン検索の P＋#＋T", () => {
  checkAll("aabxaab", viz.states({ s: "aabxaab" }));
  assert.deepEqual([...viz.states({ s: "aabxaab" }).at(-1).z], [7, 1, 0, 0, 3, 1, 0]);
  const z = viz.states({ s: "ab#abab" }).at(-1).z;
  assert.deepEqual([...z], [7, 0, 0, 2, 0, 2, 0]);
});

test("端の場合：1 文字・同じ文字だけ・先頭と食い違う・文字列の終わりで止まる", () => {
  const one = viz.states({ s: "x" });
  assert.equal(one.length, 2);
  assert.deepEqual([...one.at(-1).z], [1]);
  // aaaa：i = 1 で終わりまで一致し、あとは写すだけ（箱の外に比べる文字がない）
  const a4 = viz.states({ s: "aaaa" });
  checkAll("aaaa", a4);
  assert.deepEqual([...a4.filter((st) => st.phase === "step").map((st) => st.kase)], [1, 3, 3]);
  assert.equal(a4[2].comps.length, 0);
  assert.match(a4[2].caption, /比べる文字は残っていない/);
  // ab：z[1] = 0 でも右端が 1 に進み、空の箱 [1, 1) になる（own-z.cpp と同じ）
  const ab = viz.states({ s: "ab" });
  checkAll("ab", ab);
  assert.deepEqual({ ...ab[1].newBox }, { l: 1, r: 1 });
  assert.match(ab[1].caption, /\[1, 1\)（空）に取り替える/);
  // abcab：空の箱 [2, 2) のあとの i = 3 は、文でも「（空）」と書く
  const abcab = viz.states({ s: "abcab" });
  checkAll("abcab", abcab);
  assert.match(abcab[3].caption, /Z-box \[2, 2\)（空）の外にある/);
  // 10 文字の a：成功した比較は N − 1 = 9 回
  assert.equal(viz.states({ s: "aaaaaaaaaa" }).at(-1).success, 9);
});

test("a と b からなる 10 文字以下の文字列すべてで素朴な方法と一致し、性質が保たれる", () => {
  let count = 0;
  for (let n = 1; n <= 10; n++) {
    for (let mask = 0; mask < 1 << n; mask++) {
      let s = "";
      for (let i = 0; i < n; i++) s += mask >> i & 1 ? "b" : "a";
      checkAll(s, viz.states({ s }));
      count++;
    }
  }
  assert.equal(count, 2046);
  // 3 種類の文字でも乱数で試す
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 2000; t++) {
    const n = 1 + Math.floor(rand() * 10);
    let s = "";
    for (let i = 0; i < n; i++) s += "abc"[Math.floor(rand() * (rand() < 0.5 ? 2 : 3))];
    checkAll(s, viz.states({ s }));
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { s: "abab" };
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(JSON.parse(JSON.stringify(s1)), JSON.parse(JSON.stringify(s2)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({}), /s は/);
  assert.throws(() => viz.states({ s: "" }), /s は/);
  assert.throws(() => viz.states({ s: "abcdefghijk" }), /s は/);
  assert.throws(() => viz.states({ s: 12 }), /s は/);
  assert.throws(() => viz.states({ s: "a b" }), /文字/);
  assert.throws(() => viz.states({ s: "あい" }), /文字/);
});

test("viewBox は文字数に合わせ、凡例が収まる幅 360 を下回らない", () => {
  const w = (s) => Number(viz.viewBox({ s }).split(" ")[2]);
  assert.equal(w("a"), 360);
  assert.equal(w("aabaabaac"), 360);
  assert.equal(w("aaaaaaaaaa"), 392);
  assert.ok(Number(viz.viewBox({ s: "ab" }).split(" ")[3]) > 0);
});

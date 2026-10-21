// 動く図（Union-Find の併合と経路圧縮）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/union-find.js", import.meta.url);

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

const raw = loadViz("union-find");
// vm の別の文脈で作った配列は deepStrictEqual で比べられないので、JSON を通してこちらの文脈の値にする
const plain = (x) => JSON.parse(JSON.stringify(x));
const viz = { ...raw, states: (config) => plain(raw.states(config)) };

// 本文（docs/ds/union-find.md の「各操作の手順」の節）の config
const PAGE = {
  n: 8,
  ops: [
    { type: "merge", a: 0, b: 1 },
    { type: "merge", a: 2, b: 3 },
    { type: "merge", a: 0, b: 2 },
    { type: "merge", a: 4, b: 5 },
    { type: "merge", a: 6, b: 7 },
    { type: "merge", a: 4, b: 6 },
    { type: "merge", a: 0, b: 4 },
    { type: "find", x: 7 },
  ],
};

// 素朴な実装：本文の擬似コードどおり（union by size、同じ大きさなら a 側の根を残す、find は経路圧縮）
function naive(n, ops) {
  const par = new Array(n).fill(-1);
  const find = (v) => {
    if (par[v] < 0) return v;
    const r = find(par[v]);
    par[v] = r;
    return r;
  };
  for (const op of ops) {
    if (op.type === "find") find(op.x);
    else {
      let x = find(op.a), y = find(op.b);
      if (x === y) continue;
      if (-par[x] < -par[y]) [x, y] = [y, x];
      par[x] += par[y];
      par[y] = x;
    }
  }
  return par;
}

// どの状態でも par が森（閉路なし）で、根の −par の和が n になる。caption は空でない
function checkForest(n, states) {
  for (const [k, s] of states.entries()) {
    assert.equal(s.par.length, n);
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    let total = 0;
    for (let v = 0; v < n; v++) {
      if (s.par[v] < 0) total += -s.par[v];
      let u = v, steps = 0;
      while (s.par[u] >= 0) {
        u = s.par[u];
        assert.ok(++steps <= n, `状態 ${k}: 閉路がある`);
      }
    }
    assert.equal(total, n, `状態 ${k}: 大きさの和が n でない`);
    // 根の −par は、その根に着く要素の数に一致する
    const cnt = new Array(n).fill(0);
    for (let v = 0; v < n; v++) {
      let u = v;
      while (s.par[u] >= 0) u = s.par[u];
      cnt[u]++;
    }
    for (let v = 0; v < n; v++) if (s.par[v] < 0) assert.equal(-s.par[v], cnt[v], `状態 ${k}: 根 ${v} の大きさ`);
  }
}

function depthOf(par, v) {
  let d = 0;
  while (par[v] >= 0) { v = par[v]; d++; }
  return d;
}

test("本文の例：最後の par は [−8, 0, 0, 2, 0, 4, 0, 0] で、静的な図の右側と一致する", () => {
  const st = viz.states(PAGE);
  checkForest(8, st);
  assert.equal(st[0].phase, "start");
  assert.deepEqual(st[0].par, new Array(8).fill(-1));
  const last = st.at(-1);
  assert.equal(last.phase, "end");
  assert.deepEqual(last.par, [-8, 0, 0, 2, 0, 4, 0, 0]);
  assert.deepEqual(last.par, naive(8, PAGE.ops));
  assert.match(last.caption, /グループは 1 個/);
  assert.match(last.caption, /\[−8, 0, 0, 2, 0, 4, 0, 0\]/);
});

test("本文の例：最後の併合の直前は 0 の木も 4 の木も大きさ 4・深さ 2 で、併合すると深さ 3 になる", () => {
  const st = viz.states(PAGE);
  const find7 = st.findIndex((s) => s.op === 6 && s.phase === "merge-find");
  const before = st[find7].par;
  assert.equal(before[0], -4);
  assert.equal(before[4], -4);
  const depth = (root) => Math.max(...before.map((_, v) => {
    let u = v; while (before[u] >= 0) u = before[u];
    return u === root ? depthOf(before, v) : 0;
  }));
  assert.equal(depth(0), 2);
  assert.equal(depth(4), 2);
  const link = st.find((s) => s.op === 6 && s.phase === "merge-link");
  assert.equal(link.par[4], 0, "大きさが同じなので a 側の根 0 を残す");
  assert.equal(link.par[0], -8);
  assert.equal(Math.max(...link.par.map((_, v) => depthOf(link.par, v))), 3);
  // この ops では、merge の中の find で親は変わらない（経路圧縮の状態がない）
  assert.ok(!st.some((s) => s.phase === "merge-compress"));
  assert.ok(!st.some((s) => s.phase === "merge-same"));
});

test("本文の例：find(7) は 7 → 6 → 4 → 0 と 3 回たどり、7 と 6 の親を 0 に書き換える", () => {
  const st = viz.states(PAGE);
  const f = st.filter((s) => s.op === 7);
  assert.deepEqual(f.map((s) => s.phase), ["find-start", "find-step", "find-step", "find-step", "find-compress"]);
  assert.deepEqual(f.slice(1, 4).map((s) => s.focus[0]), [6, 4, 0]);
  assert.deepEqual(f[3].path, [7, 6, 4, 0]);
  assert.match(f[3].caption, /7 → 6 → 4 → 0 と 3 回たどって根 0 を見つけた/);
  assert.deepEqual(f[3].par, [-8, 0, 0, 2, 0, 4, 4, 6], "たどる間は par を変えない");
  const comp = f[4];
  assert.deepEqual(comp.changed.slice().sort(), [6, 7]);
  assert.deepEqual(comp.newEdges.slice().sort(), [6, 7]);
  assert.match(comp.caption, /7 と 6 の親を根 0 に書き換えた（経路圧縮）/);
  assert.match(comp.caption, /4 はもともと根の子/);
  // 状態の数：初め 1 ＋ merge 7 回×2 ＋ find 5 ＋ 終わり 1
  assert.equal(st.length, 1 + 7 * 2 + 5 + 1);
});

test("各 merge の状態：根を求めて、小さい方の根を大きい方の根の下につなぐ", () => {
  const st = viz.states(PAGE);
  const links = st.filter((s) => s.phase === "merge-link");
  // 本文の ops の順に、下につく根と残る根
  assert.deepEqual(links.map((s) => [s.newEdges[0], s.focus[0]]), [[1, 0], [3, 2], [2, 0], [5, 4], [7, 6], [6, 4], [4, 0]]);
  assert.match(links[6].caption, /par\[4\] = 0、par\[0\] = −4 \+ \(−4\) = −8/);
  assert.match(links[6].caption, /大きさが同じ（4）/);
});

test("端の場合：大きい方が b 側なら入れ替える、同じグループの merge、根の find、根の子の find、n = 1", () => {
  // b 側が大きい：merge(1, 2) で根は 1。merge(0, 2) では find(2) = 1 の方が大きいので入れ替え、0 が 1 の下につく
  let st = viz.states({ n: 3, ops: [{ type: "merge", a: 1, b: 2 }, { type: "merge", a: 0, b: 2 }] });
  let link = st.filter((s) => s.phase === "merge-link")[1];
  assert.match(link.caption, /入れ替え/);
  assert.deepEqual(link.par, [1, -3, 1]);
  // a 側が大きい：入れ替えずに 0 が 1 の下につく
  st = viz.states({ n: 3, ops: [{ type: "merge", a: 1, b: 2 }, { type: "merge", a: 2, b: 0 }] });
  link = st.filter((s) => s.phase === "merge-link")[1];
  assert.doesNotMatch(link.caption, /入れ替え/);
  assert.match(link.caption, /小さい方の根 0（大きさ 1）を、大きい方の根 1（大きさ 2）の下/);
  assert.deepEqual(link.par, [1, -3, 1]);

  // 同じグループどうしの merge は何もしない
  st = viz.states({ n: 2, ops: [{ type: "merge", a: 0, b: 1 }, { type: "merge", a: 1, b: 0 }, { type: "merge", a: 1, b: 1 }] });
  const same = st.filter((s) => s.phase === "merge-same");
  assert.equal(same.length, 2);
  same.forEach((s) => assert.deepEqual(s.par, [-2, 0]));
  assert.match(same[0].caption, /もう同じグループ/);

  // 根の find は 1 状態、根の子の find は書き換えなし
  st = viz.states({ n: 2, ops: [{ type: "find", x: 1 }, { type: "merge", a: 0, b: 1 }, { type: "find", x: 1 }] });
  const fr = st.filter((s) => s.op === 0);
  assert.equal(fr.length, 1);
  assert.match(fr[0].caption, /1 自身が根/);
  const fc = st.filter((s) => s.op === 2);
  assert.deepEqual(fc.map((s) => s.phase), ["find-start", "find-step"]);
  assert.match(fc[1].caption, /書き換える親はない/);

  // n = 1
  st = viz.states({ n: 1, ops: [{ type: "find", x: 0 }] });
  assert.deepEqual(st.at(-1).par, [-1]);
  assert.match(st.at(-1).caption, /グループは 1 個/);
});

test("merge の中の find でも経路圧縮が起き、その状態が入る", () => {
  // 0-1, 2-3, 0-2 で 3 は深さ 2。4-5, 6-7, 4-6 で 7 は深さ 2。merge(3, 7) の find で 3 と 7 の親が根に替わる
  const ops = [
    { type: "merge", a: 0, b: 1 }, { type: "merge", a: 2, b: 3 }, { type: "merge", a: 0, b: 2 },
    { type: "merge", a: 4, b: 5 }, { type: "merge", a: 6, b: 7 }, { type: "merge", a: 4, b: 6 },
    { type: "merge", a: 3, b: 7 },
  ];
  const st = viz.states({ n: 8, ops });
  const comp = st.find((s) => s.phase === "merge-compress");
  assert.ok(comp);
  assert.equal(comp.op, 6);
  assert.deepEqual(comp.changed.slice().sort(), [3, 7]);
  assert.equal(comp.par[3], 0);
  assert.equal(comp.par[7], 4);
  assert.match(comp.caption, /find\(3\) の帰りがけに、通った 3 の親を根 0 に書き換えた/);
  assert.match(comp.caption, /find\(7\) の帰りがけに、通った 7 の親を根 4 に書き換えた/);
  assert.deepEqual(st.at(-1).par, naive(8, ops));
  checkForest(8, st);
});

test("同じグループどうしの merge では、b 側のたどる回数を圧縮の前の par で書かない", () => {
  // 7 → 0 → 5 の深さ 2 を作り、merge(7, 7) と merge(7, 2)（2 は 5 の子）を呼ぶ
  const ops = [
    { type: "merge", a: 5, b: 2 }, { type: "merge", a: 0, b: 7 }, { type: "merge", a: 5, b: 0 },
    { type: "merge", a: 7, b: 7 },
  ];
  const st = viz.states({ n: 8, ops });
  const f = st.find((s) => s.op === 3 && s.phase === "merge-find");
  assert.equal((f.caption.match(/回たどり/g) || []).length, 1);
  assert.match(f.caption, /7 → 0 → 5 と 2 回たどり/);
  assert.match(f.caption, /find\(7\) も同じく 5/);
  assert.deepEqual(f.pathEdges.slice().sort(), [0, 7]);
  const c = st.find((s) => s.op === 3 && s.phase === "merge-compress");
  assert.match(c.caption, /find\(7\) の帰りがけに、通った 7 の親を根 5 に書き換えた/);
  assert.equal((c.caption.match(/帰りがけ/g) || []).length, 1);
  const ops2 = ops.slice(0, 3).concat([{ type: "merge", a: 7, b: 2 }]);
  const f2 = viz.states({ n: 8, ops: ops2 }).find((s) => s.op === 3 && s.phase === "merge-find");
  assert.match(f2.caption, /find\(2\) も同じ根 5 を返す（a 側の経路圧縮の後にたどる）/);
  assert.deepEqual(st.at(-1).par, naive(8, ops));
  checkForest(8, st);
});

test("ランダムな操作列で素朴な実装と一致し、どの状態でも森の性質が保たれる", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 2000; t++) {
    const n = 1 + Math.floor(rand() * 10);
    const m = 1 + Math.floor(rand() * 24);
    const ops = [];
    for (let i = 0; i < m; i++) {
      if (rand() < 0.65) ops.push({ type: "merge", a: Math.floor(rand() * n), b: Math.floor(rand() * n) });
      else ops.push({ type: "find", x: Math.floor(rand() * n) });
    }
    const st = viz.states({ n, ops });
    checkForest(n, st);
    assert.deepEqual(st.at(-1).par, naive(n, ops), JSON.stringify({ n, ops }));
    // 各操作が終わった時点の par も素朴な実装と一致する
    for (let k = 0; k < m; k++) {
      const lastOfOp = st.filter((s) => s.op === k).at(-1);
      assert.deepEqual(lastOfOp.par, naive(n, ops.slice(0, k + 1)));
    }
    // union by size なので深さは log2(n) 以下
    for (const s of st) {
      for (let v = 0; v < n; v++) assert.ok(depthOf(s.par, v) <= Math.floor(Math.log2(n)));
    }
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = JSON.parse(JSON.stringify(PAGE));
  const before = JSON.stringify(config);
  assert.deepEqual(viz.states(config), viz.states(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const ok = [{ type: "merge", a: 0, b: 1 }];
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states([]), /data-config/);
  assert.throws(() => viz.states({ ops: ok }), /n は/);
  assert.throws(() => viz.states({ n: 0, ops: ok }), /n は/);
  assert.throws(() => viz.states({ n: 11, ops: ok }), /n は/);
  assert.throws(() => viz.states({ n: 2.5, ops: ok }), /n は/);
  assert.throws(() => viz.states({ n: "8", ops: ok }), /n は/);
  assert.throws(() => viz.states({ n: 4 }), /ops は/);
  assert.throws(() => viz.states({ n: 4, ops: [] }), /ops は/);
  assert.throws(() => viz.states({ n: 4, ops: new Array(25).fill({ type: "find", x: 0 }) }), /ops は/);
  assert.throws(() => viz.states({ n: 4, ops: [null] }), /ops\[0\]/);
  assert.throws(() => viz.states({ n: 4, ops: [{ type: "unite", a: 0, b: 1 }] }), /type/);
  assert.throws(() => viz.states({ n: 4, ops: [{ type: "merge", a: 0, b: 4 }] }), /a と b/);
  assert.throws(() => viz.states({ n: 4, ops: [{ type: "merge", a: -1, b: 0 }] }), /a と b/);
  assert.throws(() => viz.states({ n: 4, ops: [{ type: "merge", a: 0 }] }), /a と b/);
  assert.throws(() => viz.states({ n: 4, ops: [ok[0], { type: "find", x: 1.5 }] }), /ops\[1\]（find）/);
  assert.throws(() => viz.states({ n: 4, ops: [{ type: "find" }] }), /x は/);
});

test("viewBox は全ステップで同じで、最大の深さと n で決まる", () => {
  const vb = raw.viewBox(PAGE, raw.states(PAGE)).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  const flat = raw.viewBox({ n: 8, ops: [{ type: "find", x: 0 }] }).split(" ").map(Number);
  assert.equal(flat[2], vb[2]);
  assert.ok(flat[3] < vb[3], "深さ 0 の森は低い");
  const one = raw.viewBox({ n: 1, ops: [{ type: "find", x: 0 }] }).split(" ").map(Number);
  assert.ok(one[2] >= 380, "見出しと凡例が収まる幅を保つ");
});

test("render は偽の h で例外なく描け、根の二重の輪・破線の矢印・変わったマスの太枠を出す", () => {
  const els = [];
  const h = (tag, attrs, text) => {
    const e = { tag, attrs: attrs || {}, text };
    els.push(e);
    return e;
  };
  const svg = { appendChild: () => {} };
  const st = raw.states(PAGE);
  for (const s of st) raw.render(svg, s, PAGE, h);
  els.length = 0;
  const comp = st.find((s) => s.phase === "find-compress");
  raw.render(svg, comp, PAGE, h);
  const dashed = els.filter((e) => e.tag === "path" && /dasharray/.test(e.attrs.style || ""));
  assert.equal(dashed.length, 2 + 1, "書き換えた 2 本と凡例");
  const circles = els.filter((e) => e.tag === "circle" && e.attrs.r === 19);
  assert.equal(circles.length, 1, "根は 0 だけ");
  const thickCells = els.filter((e) => e.tag === "rect" && /is-focus/.test(e.attrs.class));
  assert.equal(thickCells.length, 2);
  const texts = els.filter((e) => e.tag === "text").map((e) => String(e.text));
  assert.ok(texts.includes("−8"));
  assert.ok(texts.some((t) => t.startsWith("find(7)：経路圧縮")));
});

// 動く図（オイラーツアー：部分木が列の区間になる）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/euler-tour.js", import.meta.url);

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

const raw = loadViz("euler-tour");
// vm の別の文脈で作った配列は deepStrictEqual で比べられないので、JSON を通してこちらの文脈の値にする
const plain = (x) => JSON.parse(JSON.stringify(x));
const viz = { ...raw, states: (config) => plain(raw.states(config)) };

// 本文の div の config
const PAGE = { n: 7, parents: [-1, 6, 0, 2, 5, 0, 2], select: [2, 5, 6, 0] };

// 素朴な方法：再帰の DFS（子は番号の小さい順）で in・out を求め、部分木は親をたどって集める
function naive(par) {
  const n = par.length;
  const ch = par.map(() => []);
  par.forEach((p, x) => { if (p >= 0) ch[p].push(x); });
  const tin = Array(n), tout = Array(n), ord = [];
  let timer = 0;
  const dfs = (v) => {
    tin[v] = timer++;
    ord.push(v);
    ch[v].forEach(dfs);
    tout[v] = timer;
  };
  dfs(0);
  return { tin, tout, ord };
}
function isAnc(par, a, x) {
  for (; x >= 0; x = par[x]) if (x === a) return true;
  return false;
}

function checkCommon(cfg, sts) {
  const n = cfg.n;
  const N = naive(cfg.parents);
  const sel = cfg.select || [];
  assert.equal(sts.length, 2 * n + 2 + sel.length);
  assert.equal(sts[0].phase, "start");
  const dfs = sts.slice(1, 1 + 2 * n);
  // 入る順は行きがけ順、in は 0, 1, 2, … と順に振られる
  const enters = dfs.filter((s) => s.phase === "enter");
  assert.deepEqual(enters.map((s) => s.cur), N.ord);
  enters.forEach((s, i) => {
    assert.equal(s.tin[s.cur], i);
    assert.equal(s.ord[i], s.cur);
    assert.equal(s.timer, i + 1);
    assert.equal(s.stack.at(-1), s.cur);
  });
  // 出るのは子孫をすべて回った後で、out はそのときの timer
  for (const s of dfs.filter((s) => s.phase === "exit")) {
    assert.equal(s.tout[s.cur], s.timer);
    assert.equal(s.tout[s.cur], N.tout[s.cur]);
    for (let x = 0; x < n; x++) if (isAnc(cfg.parents, s.cur, x)) assert.notEqual(s.tin[x], null);
  }
  // DFS の道は根から cur までの祖先の列
  for (const s of dfs) {
    const path = [];
    for (let x = s.cur; x >= 0; x = cfg.parents[x]) path.unshift(x);
    assert.deepEqual(s.stack, path);
  }
  const built = sts[1 + 2 * n];
  assert.equal(built.phase, "built");
  assert.deepEqual(built.tin, N.tin);
  assert.deepEqual(built.tout, N.tout);
  assert.deepEqual(built.ord, N.ord);
  // 部分木はちょうど区間 [in, out) の頂点
  sts.slice(2 + 2 * n).forEach((s, i) => {
    assert.equal(s.phase, "subtree");
    assert.equal(s.sel, sel[i]);
    assert.deepEqual(s.range, [N.tin[s.sel], N.tout[s.sel]]);
    const want = [...Array(n).keys()].filter((x) => isAnc(cfg.parents, s.sel, x));
    assert.deepEqual([...s.members].sort((a, b) => a - b), want);
    assert.deepEqual(s.members, N.ord.slice(s.range[0], s.range[1]));
  });
  for (const [i, s] of sts.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${i}: caption が空`);
    assert.equal(s.tin.length, n);
    assert.equal(s.tout.length, n);
    assert.equal(s.ord.length, n);
  }
}

test("本文の例：入る順は 0, 2, 3, 6, 1, 5, 4、頂点 2・5・6・0 の部分木は [1, 5)・[5, 7)・[3, 5)・[0, 7)", () => {
  const sts = viz.states(PAGE);
  checkCommon(PAGE, sts);
  assert.equal(sts.length, 20);
  // 入ると出るの順
  const ev = sts.slice(1, 15).map((s) => (s.phase === "enter" ? "+" : "-") + s.cur);
  assert.deepEqual(ev, ["+0", "+2", "+3", "-3", "+6", "+1", "-1", "-6", "-2", "+5", "+4", "-4", "-5", "-0"]);
  const built = sts[15];
  assert.deepEqual(built.ord, [0, 2, 3, 6, 1, 5, 4]);
  assert.deepEqual(built.tin, [0, 4, 1, 2, 6, 5, 3]);
  assert.deepEqual(built.tout, [7, 5, 5, 3, 7, 7, 5]);
  const sub = sts.slice(16).map((s) => [s.sel, s.range, s.members]);
  assert.deepEqual(sub, [
    [2, [1, 5], [2, 3, 6, 1]],
    [5, [5, 7], [5, 4]],
    [6, [3, 5], [6, 1]],
    [0, [0, 7], [0, 2, 3, 6, 1, 5, 4]],
  ]);
  assert.equal(sts[16].caption,
    "頂点 2 の部分木（2・3・6・1）は区間 [1, 5)。番号 1〜4 は頂点 2 に入ってから出るまでに振られ、長さ 5 − 1 = 4 は部分木の頂点数に等しい。");
  assert.match(sts[19].caption, /根の部分木は列の全体である。$/);
  assert.match(sts[9].caption, /^頂点 2 の子孫をすべて回り終えた。出るときの次の番号 5 を out\[2\] とする。$/);
  assert.match(sts[4].caption, /^頂点 3 には子がないので、すぐ出る/);
  assert.match(sts[2].caption, /^頂点 0 の子 2 に入る。in\[2\] = 1/);
  assert.match(sts[15].caption, /列 ord は 0, 2, 3, 6, 1, 5, 4 で/);
});

test("n = 1・パス状の木・星・葉の部分木・select の省略と重複", () => {
  const one = { n: 1, parents: [-1], select: [0] };
  const os = viz.states(one);
  checkCommon(one, os);
  assert.deepEqual(os.at(-1).range, [0, 1]);
  assert.match(os.at(-1).caption, /番号 0 は頂点 0 に入って/);
  const path = { n: 10, parents: [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8], select: [9, 4, 0] };
  const ps = viz.states(path);
  checkCommon(path, ps);
  assert.deepEqual(ps.at(-3).range, [9, 10]);
  assert.deepEqual(ps.at(-2).range, [4, 10]);
  const star = { n: 7, parents: [-1, 0, 0, 0, 0, 0, 0], select: [3, 0] };
  checkCommon(star, viz.states(star));
  const leaf = { ...PAGE, select: [3, 3] };
  const ls = viz.states(leaf);
  checkCommon(leaf, ls);
  assert.deepEqual(ls.at(-1).members, [3]);
  const none = { n: PAGE.n, parents: PAGE.parents };
  const ns = viz.states(none);
  checkCommon(none, ns);
  assert.equal(ns.at(-1).phase, "built");
  checkCommon({ ...none, select: [] }, viz.states({ ...none, select: [] }));
});

test("番号の順でない親のランダムな木で、素朴な DFS と一致する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 300; ) {
    const n = 1 + Math.floor(rand() * 10);
    const order = [0, ...Array.from({ length: n - 1 }, (_, i) => i + 1).sort(() => rand() - 0.5)];
    const parents = Array(n).fill(-1);
    for (let i = 1; i < n; i++) parents[order[i]] = order[Math.floor(rand() * i)];
    const leaves = [...Array(n).keys()].filter((x) => !parents.includes(x)).length;
    if (leaves > 6) continue;
    t++;
    const cfg = { n, parents, select: [...Array(n).keys()] };
    checkCommon(cfg, viz.states(cfg));
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const cfg = JSON.parse(JSON.stringify(PAGE));
  const before = JSON.stringify(cfg);
  assert.deepEqual(viz.states(cfg), viz.states(cfg));
  assert.equal(JSON.stringify(cfg), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states([1]), /data-config/);
  assert.throws(() => viz.states({ ...PAGE, n: 0 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, n: 11 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, parents: [-1, 0] }), /parents は長さ/);
  assert.throws(() => viz.states({ ...PAGE, parents: "x" }), /parents は長さ/);
  assert.throws(() => viz.states({ n: 3, parents: [0, 0, 1] }), /parents\[0\]/);
  assert.throws(() => viz.states({ n: 3, parents: [-1, 3, 0] }), /parents\[1\]/);
  assert.throws(() => viz.states({ n: 3, parents: [-1, -1, 0] }), /parents\[1\]/);
  assert.throws(() => viz.states({ n: 3, parents: [-1, 1, 0] }), /自分自身/);
  assert.throws(() => viz.states({ n: 4, parents: [-1, 2, 1, 0] }), /閉路/);
  assert.throws(() => viz.states({ n: 8, parents: [-1, 0, 0, 0, 0, 0, 0, 0] }), /葉.*7 個.*6 個まで/);
  assert.throws(() => viz.states({ ...PAGE, select: 2 }), /select は/);
  assert.throws(() => viz.states({ ...PAGE, select: Array(11).fill(0) }), /select は/);
  assert.throws(() => viz.states({ ...PAGE, select: [7] }), /select\[0\]/);
  assert.throws(() => viz.states({ ...PAGE, select: [1, -1] }), /select\[1\]/);
  assert.throws(() => viz.states({ ...PAGE, select: ["2"] }), /select\[0\]/);
});

test("viewBox は全ステップで同じで、幅は 360 以上 480 以下", () => {
  const vb = raw.viewBox(PAGE).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] >= 360 && vb[2] <= 480 && vb[3] > 0);
  const path = { n: 10, parents: [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8] };
  const pv = raw.viewBox(path).split(" ").map(Number);
  assert.ok(pv[2] <= 480 && pv[3] > vb[3]);
  const six = { n: 10, parents: [-1, 0, 0, 0, 1, 1, 2, 2, 3, 3] };
  assert.ok(raw.viewBox(six).split(" ").map(Number)[2] <= 480);
});

test("偽の h で render を呼ぶと、DFS の道の太線・区間の括弧と文字が出る", () => {
  const sts = raw.states(PAGE);
  const make = () => {
    const kids = [];
    return { kids, appendChild: (e) => kids.push(e) };
  };
  const h = (tag, attrs, text) => ({ tag, attrs: attrs || {}, text: text == null ? null : String(text) });
  const draw = (s) => {
    const svg = make();
    raw.render(svg, s, PAGE, h);
    return svg.kids;
  };
  const thick = (els) => els.filter((e) => e.tag === "line" && /width:3\.5/.test(e.attrs.style || "")).length;
  // 頂点 1 に入ったとき：道 0-2-6-1 の 3 本が太線
  const at1 = draw(sts[6]);
  assert.equal(sts[6].cur, 1);
  assert.equal(thick(at1), 3);
  assert.ok(at1.some((e) => e.tag === "text" && e.text === "頂点 1 に入る：in[1] = 4"));
  // 頂点 2 の部分木：部分木の中の辺 2-3・2-6・6-1 の 3 本が太線、括弧と [1, 5)
  const s2 = draw(sts[16]);
  assert.equal(thick(s2), 3);
  assert.ok(s2.some((e) => e.tag === "path"));
  assert.ok(s2.some((e) => e.tag === "text" && e.text === "[1, 5)"));
  assert.equal(s2.filter((e) => e.tag === "circle" && /is-yes/.test(e.attrs.class || "")).length, 4);
  // 最初はどのマスも空（点線）
  const st = draw(sts[0]);
  assert.equal(st.filter((e) => e.tag === "rect" && /is-sentinel/.test(e.attrs.class)).length, 3 * PAGE.n);
  // 最後まで描けて、空のマスは残らない
  assert.equal(draw(sts[15]).filter((e) => e.tag === "rect" && /is-sentinel/.test(e.attrs.class)).length, 0);
});

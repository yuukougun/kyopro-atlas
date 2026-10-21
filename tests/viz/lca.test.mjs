// 動く図（ダブリングで LCA を求める）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/lca.js", import.meta.url);

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

const raw = loadViz("lca");
// vm の別の文脈で作った配列は deepStrictEqual で比べられないので、JSON を通してこちらの文脈の値にする
const plain = (x) => JSON.parse(JSON.stringify(x));
const viz = { ...raw, states: (config) => plain(raw.states(config)) };

// 本文の div の config
const PAGE = { n: 12, parents: [-1, 0, 0, 1, 1, 2, 3, 4, 6, 7, 5, 8], query: [11, 9] };

function depths(par) {
  const dep = par.map(() => -1);
  dep[0] = 0;
  const get = (x) => (dep[x] >= 0 ? dep[x] : (dep[x] = get(par[x]) + 1));
  par.forEach((_, x) => get(x));
  return dep;
}

// 素朴な方法：u の祖先を全部集め、v から上って最初に当たったもの
function naiveLca(par, u, v) {
  const anc = new Set();
  for (let x = u; x >= 0; x = par[x]) anc.add(x);
  for (let x = v; ; x = par[x]) if (anc.has(x)) return x;
}

// x の K 個上（根で止まる）
function upK(par, x, K) {
  for (let i = 0; i < K && par[x] >= 0; i++) x = par[x];
  return x;
}

function checkCommon(cfg, sts) {
  const dep = depths(cfg.parents);
  let L = 1;
  while (1 << L < cfg.n) L++;
  assert.ok(sts.length >= 3);
  assert.equal(sts[0].phase, "start");
  const last = sts.at(-1);
  assert.equal(last.phase, "done");
  assert.equal(last.answer, naiveLca(cfg.parents, cfg.query[0], cfg.query[1]), JSON.stringify(cfg));
  for (const [i, s] of sts.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${i}: caption が空`);
    assert.equal(s.L, L);
    assert.equal(s.rows.length, L);
    if (i < sts.length - 1) assert.equal(s.answer, null, `状態 ${i}: 答えが早く出ている`);
    // ② の間は深さがそろい、u と v はいつも LCA の真下以下にいる（LCA を通り過ぎない）
    if (s.table === "jump" && s.phase !== "done") {
      assert.equal(dep[s.u], dep[s.v], `状態 ${i}: 深さがそろっていない`);
      assert.notEqual(s.u, s.v, `状態 ${i}: 合流してしまった`);
    }
    if (s.phase === "compare") {
      const step = 1 << s.focus;
      assert.deepEqual(s.cmp, [upK(cfg.parents, s.u, step), upK(cfg.parents, s.v, step)]);
      assert.equal(s.same, s.cmp[0] === s.cmp[1]);
    }
  }
  // ② では k = L−1, …, 0 を 1 回ずつ、大きいほうから試す
  const ks = sts.filter((s) => s.phase === "compare").map((s) => s.focus);
  if (ks.length) assert.deepEqual(ks, [...Array(L).keys()].reverse());
}

test("本文の例：lca(11, 9) は 11 を 1 個上げて 8、k = 3, 2 は跳ばず、k = 1 で 3 と 4 へ跳び、k = 0 は跳ばず、答えは 1", () => {
  const sts = viz.states(PAGE);
  checkCommon(PAGE, sts);
  assert.deepEqual(
    sts.map((s) => s.phase),
    ["start", "align", "aligned", "compare", "compare", "compare", "jump", "compare", "done"],
  );
  assert.equal(sts[0].u, 11);
  assert.equal(sts[0].v, 9);
  assert.equal(sts[0].L, 4);
  assert.deepEqual(sts[1].arrows, [[11, 8, "u"]]);
  assert.equal(sts[1].focus, 0);
  assert.equal(sts[2].u, 8);
  // 比べる値：k = 3, 2 はどちらも根 0、k = 1 は 3 と 4、k = 0 はどちらも 1
  const cmp = sts.filter((s) => s.phase === "compare").map((s) => [s.focus, ...s.cmp, s.same]);
  assert.deepEqual(cmp, [[3, 0, 0, true], [2, 0, 0, true], [1, 3, 4, false], [0, 1, 1, true]]);
  assert.deepEqual(sts[6].arrows, [[8, 3, "u"], [9, 4, "v"]]);
  assert.equal(sts[6].u, 3);
  assert.equal(sts[6].v, 4);
  const last = sts.at(-1);
  assert.equal(last.answer, 1);
  assert.deepEqual(last.rows.map((r) => r.res), ["跳ばない", "跳ぶ", "跳ばない", "跳ばない"]);
  assert.match(sts[4].caption, /4 個上.*どちらも 0。同じなので跳ばない/);
  assert.match(sts[3].caption, /根より上は根 0 で止まる/);
  assert.match(last.caption, /up\[0\]\[3\] = 1/);
});

test("u が v の祖先になる場合（[8, 3] と入れ替えの [3, 8]）は ① だけで終わる", () => {
  for (const q of [[8, 3], [3, 8]]) {
    const cfg = { ...PAGE, query: q };
    const sts = viz.states(cfg);
    checkCommon(cfg, sts);
    assert.deepEqual(sts.map((s) => s.phase), ["start", "align", "aligned", "done"]);
    assert.equal(sts[0].u, 8);
    assert.equal(sts[0].v, 3);
    assert.deepEqual(sts[1].arrows, [[8, 3, "u"]]);
    assert.equal(sts.at(-1).answer, 3);
  }
  assert.match(viz.states({ ...PAGE, query: [3, 8] })[0].caption, /入れ替え/);
});

test("同じ頂点・根・深さが同じ頂点・n = 1・パス状の木", () => {
  const same = viz.states({ ...PAGE, query: [5, 5] });
  assert.deepEqual(same.map((s) => s.phase), ["start", "aligned", "done"]);
  assert.equal(same.at(-1).answer, 5);
  assert.match(same.at(-1).caption, /^u = v = 5 で同じ頂点なので/);
  assert.match(viz.states({ ...PAGE, query: [8, 3] }).at(-1).caption, /u = v = 3 になった。v = 3 は u = 8 の祖先/);
  const root = { ...PAGE, query: [0, 11] };
  checkCommon(root, viz.states(root));
  const flat = { ...PAGE, query: [10, 6] }; // 深さ 3 どうし、d = 0 で ② へ
  const fs = viz.states(flat);
  checkCommon(flat, fs);
  assert.equal(fs[1].phase, "aligned");
  assert.equal(fs.at(-1).answer, 0);
  const one = { n: 1, parents: [-1], query: [0, 0] };
  const os = viz.states(one);
  checkCommon(one, os);
  assert.equal(os[0].L, 1);
  // パス状の 16 頂点：d = 15 = 1111（2 進数）なので ① で 4 回上げる
  const path = { n: 16, parents: [-1, ...Array.from({ length: 15 }, (_, i) => i)], query: [15, 0] };
  const ps = viz.states(path);
  checkCommon(path, ps);
  assert.equal(ps.filter((s) => s.phase === "align").length, 4);
  assert.equal(ps.at(-1).answer, 0);
});

test("ランダムな木のすべての組で素朴な LCA と一致し、跳ぶ回数が L 回以下", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 150; ) {
    const n = 1 + Math.floor(rand() * 16);
    // 番号の順でない親も作る：頂点の並びを混ぜてから、前の頂点を親にする。親はおもに直前の数個から選び、深い木も作る
    const order = [0, ...Array.from({ length: n - 1 }, (_, i) => i + 1).sort(() => rand() - 0.5)];
    const parents = Array(n).fill(-1);
    const near = 1 + Math.floor(rand() * 4);
    for (let i = 1; i < n; i++) parents[order[i]] = order[Math.max(0, i - 1 - Math.floor(rand() * Math.min(i, near)))];
    // 葉が 6 個を超える木は図が受け付けないので作り直す
    const leaves = parents.filter((_, x) => !parents.includes(x)).length;
    if (leaves > 6) continue;
    t++;
    for (let u = 0; u < n; u++) {
      for (let v = 0; v < n; v++) {
        const cfg = { n, parents, query: [u, v] };
        const sts = viz.states(cfg);
        checkCommon(cfg, sts);
        assert.ok(sts.filter((s) => s.phase === "jump").length <= sts[0].L);
      }
    }
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
  assert.throws(() => viz.states({ ...PAGE, n: 17 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, parents: [-1, 0] }), /parents は長さ/);
  assert.throws(() => viz.states({ ...PAGE, parents: "x" }), /parents は長さ/);
  assert.throws(() => viz.states({ n: 3, parents: [0, 0, 1], query: [1, 2] }), /parents\[0\]/);
  assert.throws(() => viz.states({ n: 3, parents: [-1, 3, 0], query: [1, 2] }), /parents\[1\]/);
  assert.throws(() => viz.states({ n: 3, parents: [-1, -1, 0], query: [1, 2] }), /parents\[1\]/);
  assert.throws(() => viz.states({ n: 3, parents: [-1, 1, 0], query: [1, 2] }), /自分自身/);
  assert.throws(() => viz.states({ n: 4, parents: [-1, 2, 1, 0], query: [1, 2] }), /閉路/);
  assert.throws(() => viz.states({ ...PAGE, query: [1] }), /query/);
  assert.throws(() => viz.states({ ...PAGE, query: [1, 12] }), /query/);
  assert.throws(() => viz.states({ ...PAGE, query: [-1, 2] }), /query/);
  assert.throws(() => viz.states({ ...PAGE, query: ["1", 2] }), /query/);
  // 葉が 7 個以上（幅 360 で読めない）
  const star = { n: 16, parents: [-1, ...Array(15).fill(0)], query: [3, 15] };
  assert.throws(() => viz.states(star), /葉.*15 個.*6 個まで/);
  const six = { n: 7, parents: [-1, 0, 0, 0, 0, 0, 0], query: [1, 6] };
  assert.equal(viz.states(six).at(-1).answer, 0);
  assert.throws(() => viz.states({ n: 8, parents: [-1, 0, 0, 0, 0, 0, 0, 0], query: [1, 6] }), /葉/);
});

test("viewBox は木の深さと表の段数で決まり、狭い幅の下限を守る", () => {
  const vb = raw.viewBox(PAGE).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] >= 360 && vb[3] > 0);
  const path = { n: 16, parents: [-1, ...Array.from({ length: 15 }, (_, i) => i)], query: [15, 0] };
  assert.ok(raw.viewBox(path).split(" ").map(Number)[3] > vb[3]);
  // 葉 6 個（許す上限）の幅は 480 以下
  const six = { n: 7, parents: [-1, 0, 0, 0, 0, 0, 0], query: [1, 6] };
  assert.ok(raw.viewBox(six).split(" ").map(Number)[2] <= 480);
});

test("偽の h で render を呼ぶと、比べる輪・矢印・答えの印が出る", () => {
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
  const cmp = draw(sts[5]);
  assert.equal(cmp.filter((e) => e.tag === "circle" && /dasharray/.test(e.attrs.style || "")).length, 2);
  const jump = draw(sts[6]);
  assert.equal(jump.filter((e) => e.tag === "path" && /^M[^L]*Q/.test(e.attrs.d || "")).length, 2);
  // 同じ頂点を比べる段（k = 3：どちらも 0）でも輪は 2 つで、半径が違う
  const same = draw(sts[3]).filter((e) => e.tag === "circle" && /dasharray/.test(e.attrs.style || ""));
  assert.equal(same.length, 2);
  assert.equal(same[0].attrs.cx, same[1].attrs.cx);
  assert.notEqual(same[0].attrs.r, same[1].attrs.r);
  const done = draw(sts.at(-1));
  assert.ok(done.some((e) => e.tag === "text" && e.text === "LCA"));
  // 「LCA」は頂点の真上に置かない（親への辺に重ねない）
  const lab = done.find((e) => e.tag === "text" && e.text === "LCA");
  const node1 = done.find((e) => e.tag === "text" && e.text === "1");
  assert.notEqual(lab.attrs.x, node1.attrs.x);
  assert.ok(done.some((e) => e.tag === "circle" && /is-answer/.test(e.attrs.class || "")));
  assert.ok(done.some((e) => e.tag === "text" && e.text === "u"));
  assert.ok(done.some((e) => e.tag === "text" && e.text === "v"));
});

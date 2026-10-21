// 動く図（2 回の最遠点探索で木の直径を求める）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/tree-diameter.js", import.meta.url);

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

const raw = loadViz("tree-diameter");
// vm の別の文脈で作った配列は deepStrictEqual で比べられないので、JSON を通してこちらの文脈の値にする
const plain = (x) => JSON.parse(JSON.stringify(x));
const viz = { ...raw, states: (config) => plain(raw.states(config)) };

// 本文の div の config
const PAGE = { n: 9, edges: [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [2, 6], [6, 7], [3, 8]], start: 7 };

// 素朴な方法：全点対の距離（Floyd–Warshall）
function allDist(n, edges) {
  const d = Array.from({ length: n }, (_, i) => Array.from({ length: n }, (_, j) => (i === j ? 0 : Infinity)));
  for (const [u, v] of edges) d[u][v] = d[v][u] = 1;
  for (let k = 0; k < n; k++)
    for (let i = 0; i < n; i++) for (let j = 0; j < n; j++) d[i][j] = Math.min(d[i][j], d[i][k] + d[k][j]);
  return d;
}

function checkCommon(cfg, sts) {
  const n = cfg.n;
  const d = allDist(n, cfg.edges);
  const s = cfg.start ?? 0;
  const diam = Math.max(...d.flat());
  for (const [i, st] of sts.entries()) {
    assert.equal(typeof st.caption, "string");
    assert.ok(st.caption.length > 0, `状態 ${i}: caption が空`);
    assert.equal(st.dist.length, n);
    // 見えている距離は、その探索の始点からの本当の距離に一致する
    st.dist.forEach((x, v) => {
      if (x != null) assert.equal(x, d[st.src][v], `状態 ${i}: 頂点 ${v} の距離`);
    });
    // 層：距離 layer までの頂点がちょうど見えている
    if (st.phase === "layer") st.dist.forEach((x, v) => assert.equal(x != null, d[st.src][v] <= st.layer));
  }
  const sw1 = sts.filter((x) => x.sweep === 1);
  const sw2 = sts.filter((x) => x.sweep === 2);
  assert.equal(sw1[0].src, s);
  const far1 = sw1.at(-1);
  assert.equal(far1.phase, "far");
  const m1 = Math.max(...d[s]);
  // a は s から最も遠い点（同点なら番号最小）で、直径の端点になる
  assert.equal(far1.a, d[s].indexOf(m1));
  assert.deepEqual(far1.cands, d[s].flatMap((x, v) => (x === m1 ? [v] : [])));
  const a = far1.a;
  assert.equal(Math.max(...d[a]), diam, "a が直径の端点でない");
  assert.equal(sw2[0].src, a);
  const far2 = sw2.find((x) => x.phase === "far");
  assert.equal(far2.b, d[a].indexOf(diam));
  const last = sts.at(-1);
  assert.equal(last.phase, "spine");
  // 直径のパス：a から b へ隣どうしが辺でつながり、長さが直径
  const p = last.path;
  assert.equal(p[0], a);
  assert.equal(p.at(-1), far2.b);
  assert.equal(p.length - 1, diam);
  for (let i = 0; i + 1 < p.length; i++) assert.equal(d[p[i]][p[i + 1]], 1);
  assert.equal(new Set(p).size, p.length);
  // 層の数：各探索で 1〜最大距離を 1 回ずつ
  assert.deepEqual(sw1.filter((x) => x.phase === "layer").map((x) => x.layer), [...Array(m1).keys()].map((k) => k + 1));
  assert.deepEqual(sw2.filter((x) => x.phase === "layer").map((x) => x.layer), [...Array(diam).keys()].map((k) => k + 1));
  // 枝の深さは付け根から近い方の端までの長さ以下（本文の性質）
  for (const br of last.branches) assert.ok(br.depth <= br.near, JSON.stringify(br));
}

test("本文の例：s = 7 から最も遠いのは距離 5 の頂点 5、5 から最も遠いのは距離 5 の 0 と 7 で、直径の長さは 5", () => {
  const sts = viz.states(PAGE);
  checkCommon(PAGE, sts);
  assert.deepEqual(
    sts.map((s) => s.phase),
    ["start", "layer", "layer", "layer", "layer", "layer", "far",
      "start", "layer", "layer", "layer", "layer", "layer", "far", "path", "spine"],
  );
  const far1 = sts[6];
  assert.deepEqual(far1.dist, [4, 3, 2, 3, 4, 5, 1, 0, 4]);
  assert.deepEqual(far1.cands, [5]);
  assert.equal(far1.a, 5);
  const far2 = sts[13];
  assert.deepEqual(far2.dist, [5, 4, 3, 2, 1, 0, 4, 5, 3]);
  assert.deepEqual(far2.cands, [0, 7]);
  assert.equal(far2.b, 0);
  assert.match(far2.caption, /距離 5 の頂点 0 と 7 で、番号の小さい 0 を b とする。7 を選んでも長さ 5 の直径になる/);
  assert.deepEqual(sts[14].path, [5, 4, 3, 2, 1, 0]);
  assert.match(sts[14].caption, /5–4–3–2–1–0 が直径で、長さは 5/);
  assert.deepEqual(sts[15].branches, [{ at: 3, depth: 1, near: 2 }, { at: 2, depth: 2, near: 2 }]);
  assert.match(sts[3].caption, /距離 3 の頂点は 1 と 3/);
  assert.match(sts[4].caption, /距離 4 の頂点は 0・4 と 8/);
});

test("1 頂点・2 頂点・パス・星・始点が直径の端点", () => {
  const one = { n: 1, edges: [], start: 0 };
  const os = viz.states(one);
  checkCommon(one, os);
  assert.deepEqual(os.map((s) => s.phase), ["start", "far", "start", "far", "path", "spine"]);
  assert.equal(os.at(-1).a, 0);
  assert.equal(os.at(-1).b, 0);
  assert.match(os.at(-1).caption, /枝はない/);
  const two = { n: 2, edges: [[1, 0]] };
  checkCommon(two, viz.states(two)); // start の省略は 0
  assert.equal(viz.states(two).at(-1).path.join(), "1,0");
  const path = { n: 7, edges: [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6]], start: 3 };
  const ps = viz.states(path);
  checkCommon(path, ps);
  assert.deepEqual(ps[ps.findIndex((s) => s.phase === "far")].cands, [0, 6]);
  assert.equal(ps.at(-1).path.join(), "0,1,2,3,4,5,6");
  const star = { n: 7, edges: [[0, 1], [0, 2], [0, 3], [0, 4], [0, 5], [0, 6]], start: 0 };
  const ss = viz.states(star);
  checkCommon(star, ss);
  assert.equal(ss.at(-1).path.join(), "1,0,2");
  // 始点が直径の端点なら、a はもう一方の端
  const endS = { ...PAGE, start: 5 };
  const es = viz.states(endS);
  checkCommon(endS, es);
  assert.equal(es.find((s) => s.phase === "far").a, 0);
});

test("ランダムな木で、2 回の探索の結果が全点対の最大距離と一致する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  let ok = 0;
  for (let t = 0; t < 2000 && ok < 300; t++) {
    const n = 1 + Math.floor(rand() * 12);
    const perm = [...Array(n).keys()].sort(() => rand() - 0.5);
    const edges = [];
    for (let i = 1; i < n; i++) {
      const e = [perm[i], perm[Math.floor(rand() * i)]];
      edges.push(rand() < 0.5 ? e : e.reverse());
    }
    const cfg = { n, edges, start: Math.floor(rand() * n) };
    let sts;
    try {
      sts = viz.states(cfg);
    } catch (e) {
      assert.match(e.message, /幅 360/); // 幅の制限で断るのはよい
      continue;
    }
    ok++;
    checkCommon(cfg, sts);
  }
  assert.ok(ok >= 300);
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
  assert.throws(() => viz.states({ ...PAGE, n: 13 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, n: 2.5 }), /n は/);
  assert.throws(() => viz.states({ ...PAGE, edges: [[0, 1]] }), /edges は長さ/);
  assert.throws(() => viz.states({ ...PAGE, edges: "x" }), /edges は長さ/);
  assert.throws(() => viz.states({ n: 3, edges: [[0, 1], [1, 3]] }), /edges\[1\]/);
  assert.throws(() => viz.states({ n: 3, edges: [[0, 1], [1]] }), /edges\[1\]/);
  assert.throws(() => viz.states({ n: 3, edges: [[0, 1], ["1", 2]] }), /edges\[1\]/);
  assert.throws(() => viz.states({ n: 3, edges: [[0, 1], [2, 2]] }), /自己ループ/);
  assert.throws(() => viz.states({ n: 3, edges: [[0, 1], [1, 0]] }), /閉路/);
  assert.throws(() => viz.states({ ...PAGE, start: 9 }), /start/);
  assert.throws(() => viz.states({ ...PAGE, start: -1 }), /start/);
  assert.throws(() => viz.states({ ...PAGE, start: "7" }), /start/);
  // 幅 360 で読めない形
  const star = { n: 9, edges: [1, 2, 3, 4, 5, 6, 7, 8].map((v) => [0, v]), start: 0 };
  assert.throws(() => viz.states(star), /葉が 8 個.*7 個まで/);
  const path8 = { n: 8, edges: [...Array(7).keys()].map((i) => [i, i + 1]), start: 0 };
  assert.throws(() => viz.states(path8), /8 列.*7 列まで/);
  const path7 = { n: 7, edges: [...Array(6).keys()].map((i) => [i, i + 1]), start: 0 };
  assert.equal(viz.states(path7).at(-1).path.length, 7);
});

test("viewBox は全ステップで同じで、幅 360 の下限を守り、7 列で 480 以下", () => {
  const vb = raw.viewBox(PAGE).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] >= 360 && vb[3] > 0);
  const path7 = { n: 7, edges: [...Array(6).keys()].map((i) => [i, i + 1]), start: 0 };
  assert.ok(raw.viewBox(path7).split(" ").map(Number)[2] <= 480);
});

test("偽の h で render を呼ぶと、距離の数・候補の輪・直径の太線・並べ直した形が出る", () => {
  const sts = raw.states(PAGE);
  const h = (tag, attrs, text) => ({ tag, attrs: attrs || {}, text: text == null ? null : String(text) });
  const draw = (s) => {
    const kids = [];
    raw.render({ appendChild: (e) => kids.push(e) }, s, PAGE, h);
    return kids;
  };
  const texts = (els) => els.filter((e) => e.tag === "text").map((e) => e.text);
  // 1 回目の層 3：距離の数 0〜3 が見え、名札 s がある
  const l3 = draw(sts[3]);
  assert.ok(texts(l3).includes("s"));
  assert.equal(l3.filter((e) => e.tag === "circle" && /is-focus/.test(e.attrs.class || "")).length, 2); // 頂点 1 と 3
  // 2 回目の終わり：候補 0 と 7 に破線の輪、b に塗り
  const f2 = draw(sts[13]);
  assert.equal(f2.filter((e) => e.tag === "circle" && /dasharray/.test(e.attrs.style || "")).length, 2);
  assert.ok(f2.some((e) => e.tag === "circle" && /is-answer/.test(e.attrs.class || "")));
  assert.ok(texts(f2).includes("b"));
  // パス：太線が 5 本
  const pa = draw(sts[14]);
  assert.equal(pa.filter((e) => e.tag === "line" && /stroke-width:5/.test(e.attrs.style || "")).length, 5);
  // 並べ直した図：直径の頂点が同じ高さに並び、枝は破線、長さの目盛り
  const sp = draw(sts[15]);
  const ys = new Set([5, 4, 3, 2, 1, 0].map((v) => sp.find((e) => e.tag === "text" && e.text === String(v)).attrs.y));
  assert.equal(ys.size, 1);
  assert.equal(sp.filter((e) => e.tag === "line" && /dasharray/.test(e.attrs.style || "")).length, 3);
  assert.ok(texts(sp).includes("直径の長さ 5"));
  // 7 は 6 の真下、6 は 2 の真下にぶら下がる
  const at = (v) => sp.find((e) => e.tag === "text" && e.text === String(v)).attrs;
  assert.equal(at(7).x, at(2).x);
  assert.ok(at(7).y > at(6).y && at(6).y > at(2).y);
});

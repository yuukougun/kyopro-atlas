// 動く図（包除原理のベン図）の、状態の列を作る関数と描画の単体試験（design.md §8.5）
// 実行：node --test tests/viz/inclusion-exclusion-venn.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/inclusion-exclusion-venn.js", import.meta.url);
const PAGE = new URL("../../docs/comb/inclusion-exclusion.md", import.meta.url);

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

const raw = loadViz("inclusion-exclusion-venn");
// vm の中で作った配列は、こちらの Array と別物で deepEqual が通らないので、JSON を通してこちらの値にする
const viz = {
  states: (config) => JSON.parse(JSON.stringify(raw.states(config))),
  viewBox: (config) => raw.viewBox(config),
};

// 本文（docs/comb/inclusion-exclusion.md の #general）の div の config
const PAGE_CONFIG = { n: 30, divisors: [2, 3, 5] };

const gcd = (a, b) => (b ? gcd(b, a % b) : a);
const lcm = (a, b) => (a / gcd(a, b)) * b;
const popcount = (m) => (m & 1) + ((m >> 1) & 1) + ((m >> 2) & 1);

// 素朴な方法：数 x ごとに、x を割り切る数の集合の部分集合 S（|S| ≤ k）を符号 (−1)^|S| 付きで数える。
// 累計は、|S| ≤ k の S について ⌊n / lcm(S)⌋ を符号付きで足したもの
function brute(n, dv) {
  const regionOf = (x) => dv.reduce((m, d, i) => (x % d === 0 ? m | (1 << i) : m), 0);
  const timesOf = (x, k) => {
    let c = 0;
    for (let S = 0; S < 8; S++) {
      if (popcount(S) > k) continue;
      if ([0, 1, 2].every((i) => !((S >> i) & 1) || x % dv[i] === 0)) c += popcount(S) % 2 ? -1 : 1;
    }
    return c;
  };
  const totalAt = (k) => {
    let t = 0;
    for (let S = 0; S < 8; S++) {
      if (popcount(S) > k) continue;
      const l = [0, 1, 2].filter((i) => (S >> i) & 1).reduce((a, i) => lcm(a, dv[i]), 1);
      t += (popcount(S) % 2 ? -1 : 1) * Math.floor(n / l);
    }
    return t;
  };
  return { regionOf, timesOf, totalAt };
}

function checkStates(config, states) {
  const { n, divisors: dv } = config;
  const b = brute(n, dv);
  assert.equal(states.length, 4, "状態は |S| = 0〜3 の 4 段");
  const seen = new Array(n + 1).fill(0);
  for (const [k, s] of states.entries()) {
    assert.equal(s.stage, k);
    assert.equal(s.sign, k % 2 ? -1 : 1);
    assert.deepEqual(s.divisors, dv);
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `段 ${k}: caption が空`);
    assert.ok(!/です|ます[。、]/.test(s.caption), `段 ${k}: だ・である調でない`);
    // 空白は半角と全角の間だけに置く（全角どうしの間に空白を入れない。手引き §7）
    assert.ok(!/[\u3000-\u30ff\u4e00-\u9fff\uff00-\uffef] [\u3000-\u30ff\u4e00-\u9fff\uff00-\uffef]/.test(s.caption), `段 ${k}: 全角どうしの間に空白：${s.caption}`);
    // この段の項は |S| = k の部分集合すべてで、値は ⌊n / lcm(S)⌋
    assert.equal(s.terms.length, [1, 3, 3, 1][k]);
    for (const t of s.terms) {
      assert.equal(t.sets.length, k);
      assert.equal(t.lcm, t.sets.reduce((a, i) => lcm(a, dv[i]), 1));
      assert.equal(t.value, Math.floor(n / t.lcm));
    }
    assert.ok(Object.is(s.delta, s.sign * s.terms.reduce((a, t) => a + t.value, 0) || 0), `段 ${k}: delta`);
    assert.equal(s.total, b.totalAt(k), `段 ${k}: 累計`);
    assert.equal(s.prevTotal, k ? b.totalAt(k - 1) : 0);
    assert.equal(s.total, s.prevTotal + s.delta);
    assert.equal(s.groups.length, k + 1);
    assert.deepEqual(s.groups.at(-1).values, s.terms.map((t) => t.value));
    // 8 領域：数は 1〜n をちょうど 1 回ずつ含み、回数は素朴な方法と一致する
    assert.equal(s.regions.length, 8);
    let sumTimes = 0;
    for (const [m, rg] of s.regions.entries()) {
      assert.equal(rg.mask, m);
      assert.equal(rg.t, popcount(m));
      for (const x of rg.members) {
        assert.equal(b.regionOf(x), m, `x=${x} の領域`);
        assert.equal(rg.times, b.timesOf(x, k), `段 ${k}: x=${x} の回数`);
        if (k === 0) seen[x]++;
      }
      // 回数は入る集合の数 t だけで決まる：Σ_{j ≤ k} (−1)^j C(t, j)
      const C = [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1]][rg.t];
      let want = 0;
      for (let j = 0; j <= Math.min(rg.t, k); j++) want += (j % 2 ? -1 : 1) * C[j];
      assert.equal(rg.times, want);
      assert.equal(rg.prev, k ? states[k - 1].regions[m].times : null);
      // 段 k で回数が変わるのは、この段の項に含まれる領域（t ≥ k）だけで、変わる量は (−1)^k C(t, k)
      if (k > 0) assert.equal(rg.times - rg.prev, rg.t >= k ? (k % 2 ? -1 : 1) * C[k] : 0, `段 ${k}: 領域 ${m} の回数の変化`);
      sumTimes += rg.times * rg.members.length;
    }
    assert.equal(sumTimes, s.total, `段 ${k}: 回数 × 個数の和が累計と合わない`);
  }
  assert.ok(seen.slice(1).every((c) => c === 1), "1〜n が 8 領域にちょうど 1 回ずつ入っていない");
  // 最後：外側だけが 1 回、ほかは 0 回で、答えはどれでも割り切れない数の個数
  const last = states.at(-1);
  assert.deepEqual(last.regions.map((r) => r.times), [1, 0, 0, 0, 0, 0, 0, 0]);
  let none = 0;
  for (let x = 1; x <= n; x++) if (dv.every((d) => x % d !== 0)) none++;
  assert.equal(last.total, none);
  assert.equal(last.regions[0].members.length, none);
  assert.match(last.caption, new RegExp(`答えは ${none} である。$`));
}

test("本文の div の config が試験の config と同じ", () => {
  const md = readFileSync(PAGE, "utf8");
  const m = md.match(/<div class="kp-viz" data-viz="inclusion-exclusion-venn" data-config='([^']*)'><\/div>/);
  assert.ok(m, "本文に置き場の div がない");
  assert.deepEqual(JSON.parse(m[1]), PAGE_CONFIG);
});

test("本文の config：足し引きした値が 30・−15−10−6・+5+3+2・−1、累計が 30・−1・9・8", () => {
  const states = viz.states(PAGE_CONFIG);
  checkStates(PAGE_CONFIG, states);
  assert.deepEqual(states.map((s) => s.terms.map((t) => t.value)), [[30], [15, 10, 6], [5, 3, 2], [1]]);
  assert.deepEqual(states.map((s) => s.terms.map((t) => t.lcm)), [[1], [2, 3, 5], [6, 10, 15], [30]]);
  assert.deepEqual(states.map((s) => s.delta), [30, -31, 10, -1]);
  assert.deepEqual(states.map((s) => s.total), [30, -1, 9, 8]);
  // caption に、その段で足し引きした値と累計がある（本文 80 行の式と同じ値）
  assert.match(states[0].caption, /全体の 30 個を 1 回ずつ数え、累計は 30 になる/);
  assert.match(states[1].caption, /2 の倍数は 15 個、3 の倍数は 10 個、5 の倍数は 6 個なので、累計は 30 − 15 − 10 − 6 = −1 になる/);
  assert.match(states[2].caption, /6 の倍数は 5 個、10 の倍数は 3 個、15 の倍数は 2 個なので、累計は −1 \+ 5 \+ 3 \+ 2 = 9 になる/);
  assert.match(states[3].caption, /30 の倍数は 1 個なので、累計は 9 − 1 = 8 になる/);
  assert.deepEqual(states.map((s) => s.title), [
    "|S| = 0：全体を数える",
    "|S| = 1：1 つの集合の大きさを引く",
    "|S| = 2：2 つの共通部分を足す",
    "|S| = 3：3 つの共通部分を引く",
  ]);
});

test("本文の config：8 領域の数と回数が、図の後の段落の流れ（2 回引かれ・3 回引かれ・0 回に戻り・1 回に戻る）と合う", () => {
  const states = viz.states(PAGE_CONFIG);
  const reg = states[0].regions.map((r) => r.members);
  assert.deepEqual(reg, [
    [1, 7, 11, 13, 17, 19, 23, 29], // どれにも入らない（本文 83 行の 8 個）
    [2, 4, 8, 14, 16, 22, 26, 28], // 2 の倍数だけ
    [3, 9, 21, 27], // 3 の倍数だけ
    [6, 12, 18, 24], // 2 と 3
    [5, 25], // 5 の倍数だけ
    [10, 20], // 2 と 5
    [15], // 3 と 5
    [30], // 3 つすべて
  ]);
  // 回数の流れ（外側・1 つ・2 つ・3 つに入る数）。1 → 0/−1/−2 → 0/0/1 → 0/0/0
  const byT = (s, t) => s.regions.filter((r) => r.t === t).map((r) => r.times);
  assert.deepEqual(states.map((s) => byT(s, 0)), [[1], [1], [1], [1]]);
  assert.deepEqual(states.map((s) => byT(s, 1)), [[1, 1, 1], [0, 0, 0], [0, 0, 0], [0, 0, 0]]);
  assert.deepEqual(states.map((s) => byT(s, 2)), [[1, 1, 1], [-1, -1, -1], [0, 0, 0], [0, 0, 0]]);
  assert.deepEqual(states.map((s) => byT(s, 3)), [[1], [-2], [1], [0]]);
  assert.match(states[1].caption, /2 つの集合に入る数は 2 回引かれて −1 回、3 つすべてに入る 30 は 3 回引かれて −2 回になり、引きすぎている/);
  assert.match(states[2].caption, /2 つの集合に入る数は 0 回に戻るが、3 つすべてに入る 30 は 3 回足されて 1 回になり、まだ 1 回多い（足しすぎ）/);
  // 最後の段：外側の 8 個だけが 1 回残ることを書く
  assert.match(states[3].caption, /30 も 0 回になり、どれにも入らない 1・7・11・13・17・19・23・29 の 8 個だけが 1 回残る。答えは 8 である。$/);
});

test("ランダムな config で、素朴な方法（数ごとに部分集合を符号付きで数える）と一致する", () => {
  let seed = 20261029;
  const rand = (m) => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return Math.floor((seed / 2147483648) * m);
  };
  for (let t = 0; t < 400; t++) {
    const n = 1 + rand(100);
    const dv = [];
    while (dv.length < 3) {
      const d = 2 + rand(t % 2 ? 99 : 14); // 半分は小さい数（共通部分が空でない例を増やす）
      if (!dv.includes(d)) dv.push(d);
    }
    const config = { n, divisors: dv };
    checkStates(config, viz.states(config));
  }
});

test("端の場合：n = 1、共通部分が空（n < lcm）、倍数の関係（空の領域・同じ最小公倍数）、外側が 1 だけ", () => {
  const one = viz.states({ n: 1, divisors: [2, 3, 5] });
  checkStates({ n: 1, divisors: [2, 3, 5] }, one);
  assert.deepEqual(one.map((s) => s.total), [1, 1, 1, 1]);
  assert.match(one[1].caption, /累計は 1 − 0 − 0 − 0 = 1 になる。$/); // どの集合も空なので、回数の話はしない
  assert.match(one[2].caption, /2 つ以上の集合に入る数はないので、どの数の回数も変わらない。/);
  assert.match(one[3].caption, /3 つすべてに入る数はないので回数は変わらず、どれにも入らない 1 だけが 1 回残る。答えは 1 である。/);

  // n = 20 < 30：3 つすべてに入る数はない
  const c20 = { n: 20, divisors: [2, 3, 5] };
  const s20 = viz.states(c20);
  checkStates(c20, s20);
  assert.equal(s20[3].delta, 0);
  assert.match(s20[1].caption, /2 つの集合に入る数は 2 回引かれて −1 回になり、引きすぎている。$/);
  assert.match(s20[2].caption, /2 つの集合に入る数は 0 回に戻る。$/);
  assert.match(s20[3].caption, /30 の倍数は 0 個なので、累計は 6 − 0 = 6 になる。3 つすべてに入る数はないので回数は変わらず/);

  // 2・4・8：4 の倍数は 2 の倍数なので空の領域があり、2 つの共通部分の最小公倍数が重なる
  const c248 = { n: 30, divisors: [2, 4, 8] };
  const s248 = viz.states(c248);
  checkStates(c248, s248);
  assert.deepEqual(s248[0].regions.filter((r) => r.members.length === 0).map((r) => r.mask), [2, 4, 5, 6]);
  assert.match(s248[2].caption, /2・4 の公倍数（4 の倍数）は 7 個、2・8 の公倍数（8 の倍数）は 3 個、4・8 の公倍数（8 の倍数）は 3 個なので/);
  assert.match(s248[1].caption, /^1 つの集合の大きさを引く。2 の倍数は 15 個、4 の倍数は 7 個、8 の倍数は 3 個なので/);

  // 3 つすべてに入る数が 4 個以上なら、数を並べずに個数で書く
  const big = viz.states({ n: 100, divisors: [2, 3, 4] });
  checkStates({ n: 100, divisors: [2, 3, 4] }, big);
  assert.match(big[1].caption, /3 つすべてに入る 8 個の数は 3 回引かれて −2 回/);
  assert.match(big[2].caption, /3 つすべてに入る 8 個の数は 3 回足されて 1 回になり/);
  assert.match(big[3].caption, /3 つすべてに入る数も 0 回になり、どれにも入らない 33 個だけが 1 回残る。/);

  // 確認問題の 1〜100：答えは 26
  const quiz = viz.states({ n: 100, divisors: [2, 3, 5] });
  checkStates({ n: 100, divisors: [2, 3, 5] }, quiz);
  assert.deepEqual(quiz.map((s) => s.total), [100, -3, 29, 26]);
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = JSON.parse(JSON.stringify(PAGE_CONFIG));
  const before = JSON.stringify(config);
  const s1 = viz.states(config);
  const s2 = viz.states(config);
  assert.deepEqual(s1, s2);
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states({}), /n は/);
  assert.throws(() => viz.states({ n: 0, divisors: [2, 3, 5] }), /n は/);
  assert.throws(() => viz.states({ n: 101, divisors: [2, 3, 5] }), /n は/);
  assert.throws(() => viz.states({ n: 2.5, divisors: [2, 3, 5] }), /n は/);
  assert.throws(() => viz.states({ n: "30", divisors: [2, 3, 5] }), /n は/);
  assert.throws(() => viz.states({ n: Number.NaN, divisors: [2, 3, 5] }), /n は/);
  assert.throws(() => viz.states({ n: 30 }), /divisors は/);
  assert.throws(() => viz.states({ n: 30, divisors: [2, 3] }), /divisors は/);
  assert.throws(() => viz.states({ n: 30, divisors: [2, 3, 5, 7] }), /divisors は/);
  assert.throws(() => viz.states({ n: 30, divisors: "2,3,5" }), /divisors は/);
  assert.throws(() => viz.states({ n: 30, divisors: [1, 3, 5] }), /各要素/);
  assert.throws(() => viz.states({ n: 30, divisors: [2, 3, 101] }), /各要素/);
  assert.throws(() => viz.states({ n: 30, divisors: [2, 3.5, 5] }), /各要素/);
  assert.throws(() => viz.states({ n: 30, divisors: [2, "3", 5] }), /各要素/);
  assert.throws(() => viz.states({ n: 30, divisors: [2, 3, 2] }), /異なる/);
});

// ---------- 描画 ----------

// 偽の h：属性と子を記録する
function fakeH(tag, attrs, text) {
  const e = { tag, attrs: attrs || {}, text: text == null ? null : String(text), kids: [] };
  e.appendChild = (k) => { e.kids.push(k); return k; };
  return e;
}
function draw(config, s) {
  const kids = [];
  raw.render({ appendChild: (e) => kids.push(e) }, s, config, fakeH);
  return kids;
}
const fullText = (e) => (e.text ?? "") + e.kids.map(fullText).join("");
const part = (els, p) => els.filter((e) => e.attrs["data-part"] === p);

// 文字の幅の見積もり（図の中の見積もりと同じ：数字・英字 0.6、空白 0.3、全角・記号 1 文字分）
function textW(s, px) {
  let w = 0;
  for (const ch of s) {
    const c = ch.codePointAt(0);
    w += c === 32 || c === 0xa0 ? 0.3 : c < 0x2000 ? 0.6 : 1;
  }
  return w * px;
}
const fontPx = (e) => Number(/font-size:(\d+)px/.exec(e.attrs.style || "")?.[1] ?? 16);
// 文字の外接の長方形（text-anchor が start か middle か）
function textBox(e) {
  const s = fullText(e), px = fontPx(e), w = textW(s, px);
  const start = /text-anchor:start/.test(e.attrs.style || "");
  const x0 = start ? e.attrs.x : e.attrs.x - w / 2;
  return { x0, x1: x0 + w, y0: e.attrs.y - px / 2, y1: e.attrs.y + px / 2, s };
}

function checkRender(config, states) {
  const vb = raw.viewBox(config, states).split(" ").map(Number);
  assert.equal(vb.length, 4);
  for (const s of states) {
    const els = draw(config, s);
    const all = [];
    const walk = (e) => { all.push(e); e.kids.forEach(walk); };
    els.forEach(walk);
    // 座標に NaN がなく、viewBox の内側にある
    for (const e of all) {
      for (const [k, v] of Object.entries(e.attrs)) {
        if (typeof v === "number") assert.ok(Number.isFinite(v), `${e.tag} の ${k} が ${v}`);
        if (["x", "x1", "x2", "cx"].includes(k)) assert.ok(v >= 0 && v <= vb[2], `${e.tag} の ${k}=${v} が幅の外`);
        if (["y", "y1", "y2", "cy"].includes(k)) assert.ok(v >= 0 && v <= vb[3], `${e.tag} の ${k}=${v} が高さの外`);
      }
      if (e.tag === "path") assert.ok(/^M[\d. AHVZM-]+$/.test(e.attrs.d) && !/NaN/.test(e.attrs.d), `path の d：${e.attrs.d}`);
    }
    // 3 つの円と全体の長方形
    const circles = all.filter((e) => e.tag === "circle" && e.attrs["data-set"] != null);
    assert.equal(circles.length, 3);
    const [box] = part(els, "box");
    const B = [box.attrs.x, box.attrs.y, box.attrs.x + box.attrs.width, box.attrs.y + box.attrs.height];
    for (const c of circles) {
      assert.ok(c.attrs.cx - c.attrs.r > B[0] && c.attrs.cx + c.attrs.r < B[2] && c.attrs.cy - c.attrs.r > B[1] && c.attrs.cy + c.attrs.r < B[3], "円が全体の長方形からはみ出す");
    }
    const maskAt = (x, y) => circles.reduce((m, c, i) => (((x - c.attrs.cx) ** 2 + (y - c.attrs.cy) ** 2 < c.attrs.r ** 2) ? m | (1 << i) : m), 0);
    // 領域の文字（回数・数）は自分の領域に、ラベルはどの円にも入らない場所に収まり、文字どうしは重ならない
    const texts = all.filter((e) => e.tag === "text");
    const boxes = texts.map((e) => ({ e, b: textBox(e) }));
    for (const { e, b } of boxes) {
      const reg = e.attrs["data-region"];
      if (reg == null && e.attrs["data-part"] !== "label") continue;
      const want = reg == null ? 0 : reg;
      for (let i = 0; i <= 10; i++) {
        for (let j = 0; j <= 4; j++) {
          const x = b.x0 + ((b.x1 - b.x0) * i) / 10, y = b.y0 + ((b.y1 - b.y0) * j) / 4;
          assert.ok(x > B[0] && x < B[2] && y > B[1] && y < B[3], `「${b.s}」が全体の長方形の外（段 ${s.stage}）`);
          assert.equal(maskAt(x, y), want, `「${b.s}」が領域 ${want} からはみ出す（段 ${s.stage}、点 ${x.toFixed(1)}, ${y.toFixed(1)}）`);
        }
      }
    }
    for (let a = 0; a < boxes.length; a++) {
      for (let c = a + 1; c < boxes.length; c++) {
        const p = boxes[a].b, q = boxes[c].b;
        assert.ok(!(p.x0 < q.x1 && q.x0 < p.x1 && p.y0 < q.y1 && q.y0 < p.y1), `「${p.s}」と「${q.s}」が重なる（段 ${s.stage}）`);
      }
      assert.ok(boxes[a].b.x0 >= 0 && boxes[a].b.x1 <= vb[2], `「${boxes[a].b.s}」が viewBox の幅の外`);
    }
    // 回数の文字：8 領域に 1 つずつ、その段の回数を書く
    const times = part(all, "times");
    assert.deepEqual(times.map((e) => e.attrs["data-region"]), [0, 1, 2, 3, 4, 5, 6, 7]);
    times.forEach((e, m) => {
      const v = s.regions[m].times;
      assert.equal(e.text, (m === 0 ? "外側 " : "") + (v < 0 ? "−" + -v : v) + " 回");
    });
    // 領域の数：書いた数を並べ直すと領域の数になる（書ききれない領域は「k 個」、空の領域は「なし」）
    for (const rg of s.regions) {
      const lines = all.filter((e) => e.attrs["data-region"] === rg.mask && ["members", "summary"].includes(e.attrs["data-part"]));
      if (rg.members.length === 0) assert.deepEqual(lines.map((e) => e.text), ["なし"]);
      else if (lines[0].attrs["data-part"] === "summary") assert.deepEqual(lines.map((e) => e.text), [rg.members.length + " 個"]);
      else assert.deepEqual(lines.flatMap((e) => e.text.split(" ").map(Number)), rg.members);
    }
    // 塗り：1 回は色付き、負は灰色、0 回は塗らない
    const fills = part(all, "fill");
    assert.deepEqual(fills.map((e) => e.attrs["data-region"]), s.regions.filter((r) => r.times !== 0).map((r) => r.mask));
    for (const e of fills) assert.match(e.attrs.class, s.regions[e.attrs["data-region"]].times > 0 ? /is-yes/ : /is-no/);
    // この段の項の形：|S| = 0 は全体、1 は 3 つの円、2 は 3 つのレンズ、3 は中央
    const terms = part(all, "term");
    assert.deepEqual(terms.map((e) => e.tag), [["rect"], ["circle", "circle", "circle"], ["path", "path", "path"], ["path"]][s.stage]);
    // 最後の段だけ、外側の数を枠で囲む
    assert.equal(part(all, "answer").length, s.stage === 3 ? 1 : 0);
    // 見出しの式：その段までの項と累計
    const [f] = part(all, "formula");
    const g = s.groups.map((gr, j) => (j === 0 ? "" : (gr.sign < 0 ? " − " : " + ")) + (gr.values.length > 1 ? "(" + gr.values.join(" + ") + ")" : gr.values[0]));
    assert.equal(fullText(f).replaceAll("\u00a0", " "), g.join("") + (s.stage ? " = " + (s.total < 0 ? "−" + -s.total : s.total) : ""));
    assert.equal(fullText(part(all, "title")[0]), s.title);
  }
}

test("描画：本文の config で、すべての数を書き、式・回数・塗り・項の形が状態と合い、文字が領域に収まる", () => {
  const states = viz.states(PAGE_CONFIG);
  checkRender(PAGE_CONFIG, states);
  for (const s of states) {
    const all = [];
    const walk = (e) => { all.push(e); e.kids.forEach(walk); };
    draw(PAGE_CONFIG, s).forEach(walk);
    assert.equal(part(all, "summary").length, 0, "本文の config で、数を個数に縮めた領域がある");
  }
  const f = (k) => {
    const all = [];
    const walk = (e) => { all.push(e); e.kids.forEach(walk); };
    draw(PAGE_CONFIG, states[k]).forEach(walk);
    return fullText(part(all, "formula")[0]).replaceAll("\u00a0", " ");
  };
  assert.equal(f(0), "30");
  assert.equal(f(1), "30 − (15 + 10 + 6) = −1");
  assert.equal(f(3), "30 − (15 + 10 + 6) + (5 + 3 + 2) − 1 = 8"); // 本文 80 行の式
});

test("描画：いろいろな config でも文字が領域に収まり、重ならない（n = 1〜100、大きな数のラベル）", () => {
  const configs = [
    { n: 1, divisors: [2, 3, 5] }, { n: 20, divisors: [2, 3, 5] }, { n: 30, divisors: [2, 4, 8] },
    { n: 100, divisors: [2, 3, 5] }, { n: 100, divisors: [97, 98, 99] }, { n: 100, divisors: [2, 3, 4] },
    { n: 60, divisors: [6, 10, 15] }, { n: 100, divisors: [100, 99, 98] },
  ];
  let seed = 7;
  const rand = (m) => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return Math.floor((seed / 2147483648) * m);
  };
  for (let t = 0; t < 120; t++) {
    const dv = [];
    while (dv.length < 3) {
      const d = 2 + rand(t % 2 ? 99 : 10);
      if (!dv.includes(d)) dv.push(d);
    }
    configs.push({ n: 1 + rand(100), divisors: dv });
  }
  for (const c of configs) checkRender(c, viz.states(c));
});

test("viewBox は config とステップによらず同じ大きさで、幅は 400", () => {
  const vb = viz.viewBox(PAGE_CONFIG).split(" ").map(Number);
  assert.deepEqual(vb.slice(0, 3), [0, 0, 400]);
  assert.ok(vb[3] > 300 && vb[3] <= 400);
  assert.equal(viz.viewBox({ n: 100, divisors: [97, 98, 99] }), viz.viewBox(PAGE_CONFIG));
});

// 動く図「畳み込みを素朴に計算する」の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test tests/viz/convolution-naive.test.mjs
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/convolution-naive.js", import.meta.url);
const PAGE = new URL("../../docs/math/convolution-ntt.md", import.meta.url);

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

const raw = loadViz("convolution-naive");
// vm の別の realm で作られた配列は deepStrictEqual で比べられないので、JSON を通してこちらの realm に移す
const viz = { ...raw, states: (c) => JSON.parse(JSON.stringify(raw.states(c))) };

// 本文（docs/math/convolution-ntt.md の sum-pairs の節）の config
const PAGE_CONFIG = { a: [1, 2, 3], b: [4, 5, 6] };

// 定義どおりの畳み込み
function conv(a, b) {
  const c = Array(a.length + b.length - 1).fill(0);
  for (let i = 0; i < a.length; i++) for (let j = 0; j < b.length; j++) c[i + j] += a[i] * b[j];
  return c;
}

// 許す大きさ（図の列の数 N + 2M − 2 が 10 まで）のすべての (N, M)
function* sizes() {
  for (let N = 1; N <= 10; N++) for (let M = 1; N + 2 * M - 2 <= 10; M++) yield [N, M];
}

function checkStates(config, states) {
  const { a, b } = config;
  const N = a.length, M = b.length, K = N + M - 1;
  const truth = conv(a, b);
  const tag = `a=${JSON.stringify(a)} b=${JSON.stringify(b)}`;
  assert.equal(states.length, K + 2, `${tag}: 状態の数`);
  assert.equal(states[0].phase, "start");
  assert.equal(states[0].shift, 0);
  assert.deepEqual(states[0].pairs, []);
  assert.deepEqual(states[0].c, Array(K).fill(null));
  const seen = new Set();
  for (let k = 0; k < K; k++) {
    const s = states[k + 1];
    assert.equal(s.phase, "step");
    assert.equal(s.k, k);
    assert.equal(s.shift, k, `${tag}: ずらし幅 ${k} で b_0 を置く列`);
    // 反転した b を b_0 が列 k に来るように置くと、b_j は列 k − j にある。a の列 0〜N − 1 と重なる組を位置から作る
    const byPlace = [];
    for (let j = M - 1; j >= 0; j--) {
      const col = s.shift - j;
      if (col >= 0 && col < N) byPlace.push({ i: col, j, prod: a[col] * b[j] });
    }
    assert.deepEqual(s.pairs, byPlace, `${tag}: ずらし幅 ${k} で重なる組`);
    // 重なった組は、ちょうど i + j = k を満たす組の全体
    const byDef = [];
    for (let i = 0; i < N; i++) for (let j = 0; j < M; j++) if (i + j === k) byDef.push({ i, j, prod: a[i] * b[j] });
    assert.deepEqual(s.pairs, byDef, `${tag}: ずらし幅 ${k} の組が i + j = k の組と違う`);
    for (const q of s.pairs) {
      const key = `${q.i},${q.j}`;
      assert.ok(!seen.has(key), `${tag}: 組 (${key}) を 2 回掛けた`);
      seen.add(key);
    }
    assert.equal(s.sum, truth[k], `${tag}: c_${k}`);
    // c はいまのずらし幅までが求まり、残りは null
    assert.deepEqual(s.c, truth.map((v, t) => (t <= k ? v : null)), `${tag}: ずらし幅 ${k} での c`);
    assert.ok(s.caption.startsWith(`ずらし幅 k = ${k}。`));
    const muls = s.pairs.map((q) => `${a[q.i]} × ${b[q.j]}`).join(" + ");
    const vals = s.pairs.map((q) => q.prod).join(" + ");
    const eq = `c_${k} = ${muls}${s.pairs.length > 1 ? ` = ${vals}` : ""} = ${truth[k]} である。`;
    assert.ok(s.caption.includes(eq), `${tag}: ずらし幅 ${k} の caption に「${eq}」がない：${s.caption}`);
    const names = s.pairs.map((q) => `a_${q.i} と b_${q.j}`).join("、");
    assert.ok(s.caption.includes(`重なるのは ${names} の ${s.pairs.length} 組`), `${tag}: 重なる組の説明`);
    assert.equal(s.caption.includes("ずらし幅はここまで"), k === K - 1);
    // a の右端より右に出た b_j は、列 k − j ≥ N の j = 0〜k − N。k = N で b_0 が出て、k > N では出ている b_j を全部言う
    const right = k < N ? null
      : k === N ? "b_0 は a の右端より右に出た。"
      : `${k - N === 1 ? "b_0 と b_1" : `b_0〜b_${k - N}`} は a の右端より右に出ている。`;
    if (right === null) assert.doesNotMatch(s.caption, /右端より右/, `${tag}: ずらし幅 ${k} は右に出ていない`);
    else assert.ok(s.caption.includes(`下の段を右へ 1 つずらし、${right}`), `${tag}: ずらし幅 ${k} の右に出た b の言い方：${s.caption}`);
  }
  // どの組もちょうど 1 回ずつ掛けた
  assert.equal(seen.size, N * M, `${tag}: 掛けた組の数`);
  const done = states.at(-1);
  assert.equal(done.phase, "done");
  assert.equal(done.shift, K - 1);
  assert.deepEqual(done.pairs, []);
  assert.deepEqual(done.c, truth, `${tag}: 最後の c`);
  assert.ok(done.caption.includes(`c = (${truth.join(", ")}) が求まった`));
  assert.ok(done.caption.includes(`掛け算は全部で N × M = ${N * M} 回である`));
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `${tag}: 状態 ${k} の caption が空`);
    assert.ok(s.caption.endsWith("。"), `${tag}: 状態 ${k} の caption が句点で終わらない`);
    assert.doesNotMatch(s.caption, /undefined|NaN|null/, `${tag}: 状態 ${k} の caption`);
  }
}

test("本文の div の config は試験の config と同じである", () => {
  const md = readFileSync(PAGE, "utf8");
  const m = md.match(/<div class="kp-viz" data-viz="convolution-naive" data-config='([^']*)'><\/div>/);
  assert.ok(m, "本文に convolution-naive の置き場がない");
  assert.deepEqual(JSON.parse(m[1]), PAGE_CONFIG);
});

test("本文の例：c = (4, 13, 28, 27, 18)。各ずらし幅の式が本文の図の後の文と一致する", () => {
  const states = viz.states(PAGE_CONFIG);
  checkStates(PAGE_CONFIG, states);
  assert.equal(states.length, 7);
  assert.deepEqual(states.map((s) => s.phase), ["start", "step", "step", "step", "step", "step", "done"]);
  assert.deepEqual(states.slice(1, 6).map((s) => s.sum), [4, 13, 28, 27, 18]);
  assert.deepEqual(states.slice(1, 6).map((s) => s.pairs.length), [1, 2, 3, 2, 1]);
  assert.match(states[0].caption, /b = \(4, 5, 6\) を反転して 6, 5, 4 の順に、b_0 が a_0 の真下に来るように下の段に置いた/);
  assert.match(states[0].caption, /ずらし幅 k = 0〜4 のそれぞれで、上下に重なった組の積を足して c_k とする。$/);
  // 本文 78 行：幅 0 では a_0 と b_0 だけが重なり c_0 = 4、幅 1 では a_0 b_1 + a_1 b_0 = 5 + 8 = 13、幅 2 では 3 組で 6 + 10 + 12 = 28
  assert.match(states[1].caption, /b_0 は a_0 の真下にあり、b_1 と b_2 は a の左にはみ出している。/);
  assert.match(states[1].caption, /重なるのは a_0 と b_0 の 1 組だけで、i \+ j = 0 である。c_0 = 1 × 4 = 4 である。$/);
  assert.match(states[2].caption, /b_0 が a_1 の真下に来た。重なるのは a_0 と b_1、a_1 と b_0 の 2 組で、どれも i \+ j = 1 である。/);
  assert.match(states[2].caption, /c_1 = 1 × 5 \+ 2 × 4 = 5 \+ 8 = 13 である。$/);
  assert.match(states[3].caption, /a_0 と b_2、a_1 と b_1、a_2 と b_0 の 3 組/);
  assert.match(states[3].caption, /c_2 = 1 × 6 \+ 2 × 5 \+ 3 × 4 = 6 \+ 10 \+ 12 = 28 である。$/);
  assert.match(states[4].caption, /b_0 は a の右端より右に出た。/);
  // k = 4 では b_0 は前の段ですでに出ていて、b_1 も出る（列 4 − 1 = 3 ≥ N）
  assert.match(states[5].caption, /^ずらし幅 k = 4。下の段を右へ 1 つずらし、b_0 と b_1 は a の右端より右に出ている。/);
  assert.match(states[4].caption, /c_3 = 2 × 6 \+ 3 × 5 = 12 \+ 15 = 27 である。$/);
  assert.match(states[5].caption, /c_4 = 3 × 6 = 18 である。これより右へずらすと重なる組がなくなるので、ずらし幅はここまでである。$/);
  // 本文 78 行：ずらし幅は N + M − 1 通りあり、全体で O(NM)
  assert.equal(
    states[6].caption,
    "ずらし幅 0〜4 の N + M − 1 = 5 通りを終え、c = (4, 13, 28, 27, 18) が求まった。" +
      "どの組 (i, j) も、ずらし幅 i + j のときにちょうど 1 回だけ重なるので、掛け算は全部で N × M = 9 回である。" +
      "素朴な方法が O(NM) かかるのはこのためである。",
  );
});

test("許すすべての長さで、乱数の値の畳み込みが定義どおりになる", () => {
  let seed = 20261029;
  const rnd = (n) => { seed = (seed * 1103515245 + 12345) % 2147483648; return seed % n; };
  let count = 0;
  for (const [N, M] of sizes()) {
    for (let t = 0; t < 30; t++) {
      const config = { a: Array.from({ length: N }, () => rnd(10)), b: Array.from({ length: M }, () => rnd(10)) };
      checkStates(config, viz.states(config));
      count++;
    }
  }
  assert.ok(count >= 30 * 30, `試した数 ${count}`);
});

test("端の場合：1 個どうし、b が 1 個、a が 1 個、0 だけ、値の上限", () => {
  // 1 個どうし：ずらし幅は 0 だけ
  const one = viz.states({ a: [2], b: [3] });
  checkStates({ a: [2], b: [3] }, one);
  assert.equal(one.length, 3);
  assert.match(one[0].caption, /b = \(3\) を、b_0 が a_0 の真下に来るように下の段に置いた（1 個なので反転しても同じである）。/);
  assert.match(one[0].caption, /ずらし幅は k = 0 だけで、上下に重なった組の積が c_0 になる。$/);
  assert.equal(one[1].caption, "ずらし幅 k = 0。b_0 は a_0 の真下にある。重なるのは a_0 と b_0 の 1 組だけで、i + j = 0 である。" +
    "c_0 = 2 × 3 = 6 である。これより右へずらすと重なる組がなくなるので、ずらし幅はここまでである。");
  assert.match(one[2].caption, /^ずらし幅 0 の 1 通りで c = \(6\) が求まった。/);
  // b が 1 個：c_k = a_k b_0。列の数の上限 10 の a
  const longA = { a: [1, 2, 3, 4, 5, 6, 7, 8, 9, 0], b: [3] };
  const la = viz.states(longA);
  checkStates(longA, la);
  assert.deepEqual(la.at(-1).c, [3, 6, 9, 12, 15, 18, 21, 24, 27, 0]);
  assert.ok(la.slice(1, -1).every((s) => s.pairs.length === 1));
  // a が 1 個：反転した b の各項が 1 つずつ a_0 の下を通る
  const longB = { a: [2], b: [1, 2, 3, 4, 5] };
  const lb = viz.states(longB);
  checkStates(longB, lb);
  assert.deepEqual(lb.at(-1).c, [2, 4, 6, 8, 10]);
  assert.match(lb[1].caption, /b_1〜b_4 は a の左にはみ出している。/);
  assert.match(lb[2].caption, /b_0 は a の右端より右に出た。/);
  assert.match(lb[3].caption, /b_0 と b_1 は a の右端より右に出ている。/);
  assert.match(lb[4].caption, /b_0〜b_2 は a の右端より右に出ている。/);
  assert.match(lb[5].caption, /b_0〜b_3 は a の右端より右に出ている。/);
  assert.match(viz.states({ a: [1, 1], b: [1, 1] })[1].caption, /b_0 は a_0 の真下にあり、b_1 は a の左にはみ出している。/);
  // 0 だけ
  const zeros = { a: [0, 0, 0], b: [0, 0] };
  checkStates(zeros, viz.states(zeros));
  assert.deepEqual(viz.states(zeros).at(-1).c, [0, 0, 0, 0]);
  // 値の上限：c_k は 4 × 81 = 324 まで（3 桁でマスに収まる）
  const big = { a: [9, 9, 9, 9], b: [9, 9, 9, 9] };
  const bs = viz.states(big);
  checkStates(big, bs);
  assert.equal(Math.max(...bs.at(-1).c), 324);
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = JSON.parse(JSON.stringify(PAGE_CONFIG));
  const before = JSON.stringify(config);
  assert.deepEqual(viz.states(config), viz.states(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  const b = PAGE_CONFIG.b;
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states("a"), /data-config/);
  assert.throws(() => viz.states({ b }), /a は 1 個以上/);
  assert.throws(() => viz.states({ a: [], b }), /a は 1 個以上/);
  assert.throws(() => viz.states({ a: "123", b }), /a は 1 個以上/);
  assert.throws(() => viz.states({ a: [1, 10], b }), /a の要素は 0〜9 の整数/);
  assert.throws(() => viz.states({ a: [1, -1], b }), /a の要素/);
  assert.throws(() => viz.states({ a: [1, 2.5], b }), /a の要素/);
  assert.throws(() => viz.states({ a: [1, "2"], b }), /a の要素/);
  assert.throws(() => viz.states({ a: [1, Number.NaN], b }), /a の要素/);
  assert.throws(() => viz.states({ a: [1, null], b }), /a の要素/);
  assert.throws(() => viz.states({ a: [1] }), /b は 1 個以上/);
  assert.throws(() => viz.states({ a: [1], b: [] }), /b は 1 個以上/);
  assert.throws(() => viz.states({ a: [1], b: [Infinity] }), /b の要素/);
  // 図の列の数 N + 2M − 2 が 10 を超える
  assert.throws(() => viz.states({ a: [1, 2, 3], b: [1, 2, 3, 4, 5] }), /N \+ 2M − 2 ≤ 10/);
  assert.throws(() => viz.states({ a: Array(11).fill(1), b: [1] }), /N \+ 2M − 2 ≤ 10/);
  assert.throws(() => viz.states({ a: [1], b: Array(6).fill(1) }), /長い方を a にする/);
  // 境目ちょうどは通る（入れ替えれば通る例も）
  assert.doesNotThrow(() => viz.states({ a: [1, 2, 3, 4, 5], b: [1, 2, 3] }));
  assert.doesNotThrow(() => viz.states({ a: [1, 2], b: [1, 2, 3, 4, 5] }));
});

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

test("viewBox は a・b の長さだけで決まり、幅は 448 以下", () => {
  const vb = raw.viewBox(PAGE_CONFIG).split(" ").map(Number);
  assert.deepEqual(vb, [0, 0, 40 + 7 * 40 + 8, 280]);
  assert.equal(raw.viewBox({ a: [9, 9, 9], b: [0, 0, 0] }), raw.viewBox(PAGE_CONFIG));
  for (const [N, M] of sizes()) {
    const w = Number(raw.viewBox({ a: Array(N).fill(1), b: Array(M).fill(1) }).split(" ")[2]);
    assert.equal(w, Math.max(260, 40 + 40 * (N + 2 * M - 2) + 8), `N=${N} M=${M}`);
    assert.ok(w <= 448);
  }
});

// render の試験に使う config（本文の例・1 個どうし・列の数が上限の 3 つ・値が同じ並び）
const RENDER_CONFIGS = [PAGE_CONFIG, { a: [2], b: [3] }, { a: [1, 2, 3, 4, 5, 6, 7, 8, 9, 0], b: [3] },
  { a: [2], b: [1, 2, 3, 4, 5] }, { a: [9, 9, 9, 9], b: [9, 9, 9, 9] }, { a: [1, 0, 1, 1, 0, 1], b: [1, 0, 1] },
  { a: [3, 1, 4, 1], b: [5, 9, 2, 6] }, { a: [2, 7], b: [1, 8, 2] }];

test("render が全ステップで描け、重なった組は上下にそろい、積と c_k が出る", () => {
  for (const config of RENDER_CONFIGS) {
    const vb = raw.viewBox(config).split(" ").map(Number);
    const states = viz.states(config);
    for (const s of states) {
      const els = draw(config, s);
      const tag = `${JSON.stringify(config)} ${s.phase} ${s.k}`;
      for (const e of els) {
        for (const [k, v] of Object.entries(e.attrs)) {
          if (typeof v === "number") assert.ok(Number.isFinite(v), `${tag}: ${e.tag} の ${k} が ${v}`);
          if (["x", "cx"].includes(k)) assert.ok(v >= 0 && v <= vb[2], `${tag}: ${e.tag} の ${k}=${v} が幅の外`);
          if (["y", "cy"].includes(k)) assert.ok(v >= 0 && v <= vb[3], `${tag}: ${e.tag} の ${k}=${v} が高さの外`);
        }
        if (e.tag === "rect") {
          assert.ok(e.attrs.x + e.attrs.width <= vb[2] && e.attrs.y + e.attrs.height <= vb[3], `${tag}: マスが外`);
        }
      }
      const rects = els.filter((e) => e.tag === "rect");
      const texts = els.filter((e) => e.tag === "text");
      // 重なった a と b のマスは塗り（is-yes）で、上下で同じ x にそろう
      const yes = rects.filter((e) => /\bis-yes\b/.test(e.attrs.class));
      const times = texts.filter((e) => e.text === "×");
      const answer = rects.filter((e) => /\bis-answer\b/.test(e.attrs.class));
      if (s.phase === "step") {
        const ys = [...new Set(yes.map((e) => e.attrs.y))].sort((p, q) => p - q);
        assert.equal(ys.length, 2, `${tag}: 塗りのマスの段`);
        const xsA = yes.filter((e) => e.attrs.y === ys[0]).map((e) => e.attrs.x).sort((p, q) => p - q);
        const xsB = yes.filter((e) => e.attrs.y === ys[1]).map((e) => e.attrs.x).sort((p, q) => p - q);
        assert.equal(xsA.length, s.pairs.length);
        assert.deepEqual(xsB, xsA, `${tag}: 重なった a と b が上下にそろわない`);
        assert.equal(times.length, s.pairs.length, `${tag}: × の数`);
        assert.equal(answer.length, 1, `${tag}: いまの c_k は 1 マス`);
        // 積のマスは重なった列の真下に、積の値で並ぶ
        const prod = rects.filter((e) => e.attrs.y > ys[1] && e.attrs.y < answer[0].attrs.y && e.attrs.class === "kp-v-cell");
        assert.deepEqual(prod.map((e) => e.attrs.x).sort((p, q) => p - q), xsA, `${tag}: 積のマス`);
        for (const q of s.pairs) assert.ok(texts.some((e) => e.text === String(q.prod)), `${tag}: 積 ${q.prod} がない`);
        // c_k のマスは、b の段の右端（反転した b の b_0）の真下の列にある
        const bRow = rects.filter((e) => e.attrs.y === ys[1]);
        assert.equal(bRow.length, config.b.length, `${tag}: b の段のマスの数`);
        assert.equal(Math.max(...bRow.map((e) => e.attrs.x)), answer[0].attrs.x, `${tag}: b_0 と c_k の列`);
        // 和の式（添字は tspan で下げる）
        const sumLine = texts.find((e) => e.kids.length > 0);
        const rhs = s.pairs.length > 1 ? ` = ${s.pairs.map((q) => q.prod).join(" + ")} = ${s.sum}` : ` = ${s.sum}`;
        assert.equal(fullText(sumLine), `c${s.k}${rhs}`, `${tag}: 和の式`);
        assert.equal(sumLine.kids[1].attrs.dy, 4);
        assert.equal(sumLine.kids[2].attrs.dy, -4);
      } else {
        assert.equal(yes.length, s.phase === "done" ? s.c.length : 0, `${tag}: 塗りのマス`);
        assert.equal(times.length, 0);
        assert.equal(answer.length, 0);
      }
      if (s.phase === "done") {
        assert.ok(texts.some((e) => fullText(e) === `c = (${s.c.join(", ")})`), `${tag}: 最後の c の式`);
        const n = config.a.length * config.b.length;
        assert.ok(texts.some((e) => e.text === `掛け算は全部で N × M = ${n} 回`), `${tag}: 掛け算の回数`);
      }
      if (s.phase === "start") {
        assert.equal(rects.filter((e) => /is-sentinel/.test(e.attrs.class)).length, s.c.length, `${tag}: c は空のマス`);
        assert.equal(texts.some((e) => e.text === "右へずらす →"), s.c.length > 1, `${tag}: 向きの案内`);
      }
    }
  }
});

// 描いた図を位置だけで読み直す（states の pairs・c に頼らない）。マスの段は上から a・b・（積）・c で、
// 列の番号は c の段のマスから決める（c_0 の列が 0、マスの間隔が 1 列）
function readBack(config, s) {
  const els = draw(config, s);
  const rects = els.filter((e) => e.tag === "rect");
  const nums = els.filter((e) => e.tag === "text" && e.text !== null && /^\d+$/.test(e.text));
  const ys = [...new Set(rects.map((e) => e.attrs.y))].sort((p, q) => p - q);
  const row = (y) => rects.filter((e) => e.attrs.y === y).sort((p, q) => p.attrs.x - q.attrs.x);
  const cRow = row(ys.at(-1));
  const pitch = cRow.length >= 2 ? cRow[1].attrs.x - cRow[0].attrs.x : null;
  const col = (e) => (pitch === null ? (e.attrs.x === cRow[0].attrs.x ? 0 : NaN) : (e.attrs.x - cRow[0].attrs.x) / pitch);
  const mid = (e) => e.attrs.x + e.attrs.width / 2;
  // マスの中の文字（なければ null）
  const value = (e) => {
    const t = nums.filter((n) => n.attrs.x === mid(e) && n.attrs.y === e.attrs.y + e.attrs.height / 2);
    return t.length === 1 ? Number(t[0].text) : null;
  };
  const cell = (e) => ({ col: col(e), value: value(e), cls: e.attrs.class });
  const yB = ys[1], next = ys[2];
  return {
    rows: ys.length,
    a: row(ys[0]).map(cell),
    // b のマスと、その真下（積か c の段より上）に書いた添字 j
    b: row(yB).map((e) => {
      const lab = nums.filter((n) => n.attrs.x === mid(e) && n.attrs.y > yB + e.attrs.height && n.attrs.y < next);
      return { ...cell(e), j: lab.length === 1 ? Number(lab[0].text) : null };
    }),
    prod: ys.length === 4 ? row(ys[2]).map(cell) : [],
    c: cRow.map(cell),
  };
}

test("render を位置で読み直す：b は反転して並び、a_i の真下に b_{k−i} と添字 k − i、その真下に積 a_i b_{k−i}", () => {
  for (const config of RENDER_CONFIGS) {
    const { a, b } = config;
    const N = a.length, M = b.length, K = N + M - 1;
    const truth = conv(a, b);
    for (const s of viz.states(config)) {
      const tag = `${JSON.stringify(config)} ${s.phase} ${s.k}`;
      const g = readBack(config, s);
      assert.equal(g.rows, s.phase === "step" ? 4 : 3, `${tag}: マスの段の数`);
      // a は列 0〜N − 1 に a_0, …, a_{N−1}
      assert.deepEqual(g.a.map((x) => [x.col, x.value]), a.map((v, i) => [i, v]), `${tag}: a の段`);
      // b は左から添字 M − 1, …, 0 の順（反転）で、b_j は列 shift − j にある（start は shift = 0 なので列 −j）
      const shift = s.phase === "start" ? 0 : s.phase === "step" ? s.k : K - 1;
      assert.deepEqual(g.b.map((x) => x.j), b.map((_, t) => M - 1 - t), `${tag}: b が反転して並ばない`);
      for (const x of g.b) {
        assert.equal(x.value, b[x.j], `${tag}: b_${x.j} のマスの値`);
        assert.equal(x.col, shift - x.j, `${tag}: b_${x.j} の列`);
      }
      // c の段：列 0〜K − 1。step では k までが定義どおりの値で、いまの c_k だけ濃い塗り。残りは空。done はすべて値
      assert.deepEqual(g.c.map((x) => x.col), truth.map((_, t) => t), `${tag}: c の段の列`);
      const upto = s.phase === "start" ? -1 : s.phase === "step" ? s.k : K - 1;
      assert.deepEqual(g.c.map((x) => x.value), truth.map((v, t) => (t <= upto ? v : null)), `${tag}: c の段の値`);
      assert.deepEqual(g.c.filter((x) => /is-answer/.test(x.cls)).map((x) => x.col), s.phase === "step" ? [s.k] : [],
        `${tag}: 濃い塗りの c`);
      if (s.phase !== "step") continue;
      // 重なる列は、a と b の両方のマスがある列で、ちょうど 0 ≤ i < N かつ 0 ≤ k − i < M の i
      const k = s.k;
      const over = [];
      for (let i = 0; i < N; i++) if (k - i >= 0 && k - i < M) over.push(i);
      assert.deepEqual(g.b.filter((x) => x.col >= 0 && x.col < N).map((x) => x.col).sort((p, q) => p - q), over, `${tag}: 重なる列`);
      for (const i of over) {
        const under = g.b.find((x) => x.col === i);
        assert.equal(under.value, b[k - i], `${tag}: a_${i} の真下の b のマスの値`);
        assert.equal(under.j, k - i, `${tag}: a_${i} の真下の添字 j`);
        assert.match(under.cls, /is-yes/, `${tag}: a_${i} の真下の b が塗られていない`);
        assert.match(g.a[i].cls, /is-yes/, `${tag}: a_${i} が塗られていない`);
      }
      // 重ならないマスは塗らない
      for (const x of g.b) if (!over.includes(x.col)) assert.doesNotMatch(x.cls, /is-yes/, `${tag}: 重ならない b_${x.j}`);
      for (const x of g.a) if (!over.includes(x.col)) assert.doesNotMatch(x.cls, /is-yes/, `${tag}: 重ならない a_${x.col}`);
      // 積の段：重なる列の真下にだけ、a_i × b_{k−i}
      assert.deepEqual(g.prod.map((x) => [x.col, x.value]), over.map((i) => [i, a[i] * b[k - i]]), `${tag}: 積の段`);
      // c_k = 積の段の和
      assert.equal(g.prod.reduce((sum, x) => sum + x.value, 0), g.c[k].value, `${tag}: 積の和と c_k`);
    }
  }
});

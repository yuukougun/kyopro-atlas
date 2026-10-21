// 動く図（全探索の木と DP の表、貰う形と配る形）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/dp-tree-table.js", import.meta.url);

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

const raw = loadViz("dp-tree-table");
// vm の別の文脈で作った配列は deepStrictEqual で比べられないので、JSON を通してこちらの文脈の値にする
const plain = (x) => JSON.parse(JSON.stringify(x));
const viz = { ...raw, states: (config) => plain(raw.states(config)) };

// 素朴な方法：跳び方をすべて試した最小コスト（足場 0 から i まで）と、素朴な再帰の呼び出しの回数
function bruteMin(h, i) {
  if (i === 0) return 0;
  let best = bruteMin(h, i - 1) + Math.abs(h[i] - h[i - 1]);
  if (i >= 2) best = Math.min(best, bruteMin(h, i - 2) + Math.abs(h[i] - h[i - 2]));
  return best;
}
function allPaths(h) {
  // 0 から N−1 への跳び方を列挙して、各足場までの最小を求める（再帰とは別の作り方）
  const n = h.length;
  const best = new Array(n).fill(Infinity);
  const walk = (pos, c) => {
    best[pos] = Math.min(best[pos], c);
    for (const d of [1, 2]) if (pos + d < n) walk(pos + d, c + Math.abs(h[pos + d] - h[pos]));
  };
  walk(0, 0);
  return best;
}
function calls(i) {
  let cnt = 1;
  if (i >= 1) cnt += calls(i - 1);
  if (i >= 2) cnt += calls(i - 2);
  return cnt;
}

// どの部分にも当てはまる性質：caption が空でない、確定した値は変わらない
function checkCommon(h, states) {
  const n = h.length;
  for (const [k, s] of states.entries()) {
    assert.equal(typeof s.caption, "string");
    assert.ok(s.caption.length > 0, `状態 ${k}: caption が空`);
    assert.equal(s.table.length, n);
    assert.equal(s.confirmed.length, n);
  }
  const truth = allPaths(h);
  for (const s of states) {
    s.table.forEach((v, i) => {
      if (s.confirmed[i]) assert.equal(v, truth[i], `確定した dp[${i}] が正しくない`);
    });
  }
}

test("本文の例（h = (8, 1, 7, 2, 9, 6)）：表は (0, 7, 1, 6, 3, 6)、答え 6、呼び出し 20 回、辺 9 本", () => {
  const h = [8, 1, 7, 2, 9, 6];
  const states = viz.states({ h });
  checkCommon(h, states);
  const tree = states.filter((s) => s.part === "tree");
  const pull = states.filter((s) => s.part === "pull");
  const push = states.filter((s) => s.part === "push");
  assert.equal(states.length, tree.length + pull.length + push.length);
  // 前半：最初は空、帰りがけ順で dp[0]・dp[1]・(0 の呼び直し)・dp[2]・(1)・dp[3]・(2)・dp[4]・(3)・dp[5]
  assert.equal(tree.length, 12);
  assert.deepEqual(tree[0].table, [null, null, null, null, null, null]);
  assert.equal(tree[0].total, 20);
  assert.match(tree[0].caption, /20 回/);
  const steps = tree.slice(1, -1).map((s) => `${s.link.kind}${s.link.cell}`);
  assert.deepEqual(steps, ["write0", "write1", "read0", "write2", "read1", "write3", "read2", "write4", "read3", "write5"]);
  assert.deepEqual(tree.slice(1, -1).map((s) => s.calls), [1, 2, 3, 4, 6, 7, 11, 12, 19, 20]);
  // calls は返った（終わった）呼び出しの累計で、caption でもそう書く
  for (const s of tree.slice(1, -1)) assert.match(s.caption, new RegExp(`返った呼び出しはここまで ${s.calls} 回`));
  // 呼び直しの部分木の大きさは、その足場の呼び出しの回数 C(i)
  for (const s of tree.slice(1, -1)) {
    if (s.link.kind === "read") assert.equal(s.current.length, calls(s.link.cell));
    else assert.equal(s.current.length, 1);
  }
  const lastTree = tree.at(-1);
  assert.deepEqual(lastTree.table, [0, 7, 1, 6, 3, 6]);
  assert.ok(lastTree.answer);
  assert.equal(lastTree.calls, 20);
  assert.ok(lastTree.status.every((x) => x === 1 || x === 2));
  assert.equal(lastTree.status.filter((x) => x === 1).length, 6); // 初めて返る呼び出しは足場ごとに 1 回
  assert.match(lastTree.caption, /20 回/);
  assert.match(lastTree.caption, /\(0, 7, 1, 6, 3, 6\)/);
  assert.match(lastTree.caption, /dp\[5\] = 6/);
  // 本文の比べ方：足場 2・4 は 2 つ先から、3・5 は 1 つ先から来るのが安い
  assert.match(tree.find((s) => s.link && s.link.kind === "write" && s.link.cell === 2).caption, /min\(7 \+ 6, 0 \+ 1\) = 1/);
  assert.match(tree.find((s) => s.link && s.link.kind === "write" && s.link.cell === 3).caption, /min\(1 \+ 5, 7 \+ 1\) = 6/);
  assert.match(tree.find((s) => s.link && s.link.kind === "write" && s.link.cell === 4).caption, /min\(6 \+ 7, 1 \+ 2\) = 3/);
  assert.match(tree.find((s) => s.link && s.link.kind === "write" && s.link.cell === 5).caption, /min\(3 \+ 3, 6 \+ 4\) = 6/);

  // 貰う形：各ステップで 1 マス決まり、遷移元は i − 1 と i − 2
  assert.equal(pull.length, 6);
  assert.deepEqual(pull.at(-1).table, [0, 7, 1, 6, 3, 6]);
  assert.equal(pull.at(-1).used.length, 9);
  assert.match(pull[0].caption, /2N − 3 = 9 本/);
  pull.slice(1).forEach((s, k) => {
    const i = k + 1;
    assert.equal(s.focus, i);
    assert.deepEqual(s.active.map((e) => e[1]), s.active.map(() => i));
    assert.deepEqual(s.active.map((e) => e[0]).sort(), (i >= 2 ? [i - 2, i - 1] : [0]).sort());
  });

  // 配る形：dp[3] は 8 → 6、dp[4] は ∞ → 3（push-pull.svg と同じ）、dp[5] は 10 → 6
  assert.equal(push.length, 6);
  assert.deepEqual(push.at(-1).table, [0, 7, 1, 6, 3, 6]);
  assert.equal(push.at(-1).used.length, 9);
  const from2 = push.find((s) => s.focus === 2 && s.active.length);
  assert.deepEqual(plain(from2.updates), [{ to: 3, old: 8, now: 6 }, { to: 4, old: null, now: 3 }]);
  assert.match(from2.caption, /min\(8, 1 \+ 5\) = 6/);
  assert.match(from2.caption, /min\(∞, 1 \+ 2\) = 3/);
  assert.deepEqual(plain(push.at(-1).updates), [{ to: 5, old: 10, now: 6 }]);
  assert.match(push.at(-1).caption, /\(0, 7, 1, 6, 3, 6\)/);
  assert.ok(push.at(-1).answer);
});

test("貰う形と配る形は同じ辺の集合（2N − 3 本）を 1 回ずつ使う", () => {
  for (let n = 2; n <= 6; n++) {
    const h = Array.from({ length: n }, (_, i) => (i * 7) % 10);
    const st = viz.states({ h });
    const key = (e) => e.join("-");
    for (const part of ["pull", "push"]) {
      const ps = st.filter((s) => s.part === part);
      const used = ps.at(-1).used.map(key);
      assert.equal(used.length, 2 * n - 3, `N=${n} ${part}`);
      assert.equal(new Set(used).size, used.length, `N=${n} ${part}: 同じ辺を 2 回使った`);
      // used は各ステップの active をつなげたもの
      assert.deepEqual(ps.flatMap((s) => s.active).map(key), used);
      // 使った辺はいつも i → i+1 か i → i+2
      for (const [a, b] of ps.at(-1).used) assert.ok(b - a === 1 || b - a === 2);
    }
    const a = new Set(st.filter((s) => s.part === "pull").at(-1).used.map(key));
    const b = st.filter((s) => s.part === "push").at(-1).used.map(key);
    assert.ok(b.every((e) => a.has(e)));
  }
});

test("配る形：辺を使うときに遷移元の値は確定している", () => {
  const h = [8, 1, 7, 2, 9, 6];
  const truth = allPaths(h);
  const push = viz.states({ h, parts: ["push"] });
  for (const s of push) {
    for (const [a] of s.active) {
      assert.equal(s.table[a], truth[a]);
      assert.ok(s.confirmed[a]);
    }
  }
});

test("ランダムな高さで、表が全探索の最小と一致し、呼び出しの回数が再帰の回数と一致する", () => {
  let seed = 20261021;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  for (let t = 0; t < 500; t++) {
    const n = 2 + Math.floor(rand() * 5);
    const h = Array.from({ length: n }, () => Math.floor(rand() * (rand() < 0.3 ? 3 : 100)));
    const st = viz.states({ h });
    checkCommon(h, st);
    const truth = allPaths(h);
    for (let i = 0; i < n; i++) assert.equal(truth[i], bruteMin(h, i));
    for (const part of ["tree", "pull", "push"]) {
      const last = st.filter((s) => s.part === part).at(-1);
      assert.deepEqual(last.table, truth, `h=${JSON.stringify(h)} ${part}`);
      assert.ok(last.confirmed.every(Boolean));
      assert.ok(last.answer);
    }
    const tree = st.filter((s) => s.part === "tree");
    assert.equal(tree[0].total, calls(n - 1));
    assert.equal(tree.at(-1).calls, calls(n - 1));
    // 呼び出しの数は増えるだけで、表のマスは 1 ステップに高々 1 つ埋まる
    for (let k = 1; k < tree.length; k++) {
      assert.ok(tree[k].calls >= tree[k - 1].calls);
      const filled = (s) => s.table.filter((v) => v !== null).length;
      assert.ok(filled(tree[k]) - filled(tree[k - 1]) <= 1);
    }
    // 呼び直しのステップでは、引くマスがすでに埋まっている
    for (const s of tree) if (s.link && s.link.kind === "read") assert.notEqual(s.table[s.link.cell], null);
  }
});

test("端の場合：N = 2（呼び直しなし・辺 1 本）、同じ高さ、parts を絞る", () => {
  let st = viz.states({ h: [3, 3] });
  const tree = st.filter((s) => s.part === "tree");
  assert.equal(tree.length, 4); // 空・dp[0]・dp[1]・まとめ
  assert.ok(tree.every((s) => !s.link || s.link.kind === "write"));
  assert.match(tree.at(-1).caption, /呼び直しは起きず/);
  assert.deepEqual(tree.at(-1).table, [0, 0]);
  assert.equal(st.filter((s) => s.part === "pull").at(-1).used.length, 1);
  assert.equal(st.filter((s) => s.part === "push").at(-1).used.length, 1);
  // N = 3：呼び出し 4 回、呼び直しは足場 0 の 1 回だけ
  st = viz.states({ h: [0, 99, 0] });
  const t3 = st.filter((s) => s.part === "tree");
  assert.equal(t3[0].total, 4);
  assert.deepEqual(t3.filter((s) => s.link && s.link.kind === "read").map((s) => s.link.cell), [0]);
  assert.deepEqual(t3.at(-1).table, [0, 99, 0]);
  // 高さがすべて同じなら表はすべて 0
  assert.deepEqual(viz.states({ h: [5, 5, 5, 5, 5, 5] }).at(-1).table, [0, 0, 0, 0, 0, 0]);
  // parts は並びによらず tree → pull → push の順で、指定したものだけ
  st = viz.states({ h: [1, 2, 3], parts: ["push", "tree"] });
  assert.deepEqual([...new Set(st.map((s) => s.part))], ["tree", "push"]);
  assert.match(st.at(-1).caption, /各辺を 1 回ずつ使い、表は \(0, 1, 2\)/);
  assert.doesNotMatch(st.at(-1).caption, /どちらの形も/);
  st = viz.states({ h: [1, 2, 3], parts: ["pull"] });
  assert.ok(st.every((s) => s.part === "pull"));
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { h: [8, 1, 7, 2, 9, 6], parts: ["pull", "tree"] };
  const before = JSON.stringify(config);
  assert.deepEqual(plain(viz.states(config)), plain(viz.states(config)));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states([1, 2]), /data-config/);
  assert.throws(() => viz.states({}), /h は/);
  assert.throws(() => viz.states({ h: [1] }), /h は 2〜6/);
  assert.throws(() => viz.states({ h: [1, 2, 3, 4, 5, 6, 7] }), /h は 2〜6/);
  assert.throws(() => viz.states({ h: "1,2" }), /h は/);
  assert.throws(() => viz.states({ h: [1, 1.5] }), /整数/);
  assert.throws(() => viz.states({ h: [1, "2"] }), /整数/);
  assert.throws(() => viz.states({ h: [1, -1] }), /0 以上/);
  assert.throws(() => viz.states({ h: [1, 100] }), /99/);
  assert.throws(() => viz.states({ h: [1, 2], parts: [] }), /parts/);
  assert.throws(() => viz.states({ h: [1, 2], parts: "tree" }), /parts/);
  assert.throws(() => viz.states({ h: [1, 2], parts: ["tree", "graph"] }), /parts/);
});

test("viewBox は全ステップで同じで、本文の例は幅 360 の画面で 0.75 倍以上に収まる", () => {
  const vb = viz.viewBox({ h: [8, 1, 7, 2, 9, 6] }).split(" ").map(Number);
  assert.equal(vb.length, 4);
  assert.ok(vb[2] > 0 && vb[3] > 0);
  // 360px の画面では本文の幅が約 310px（左右の余白と枠を除く）
  assert.ok(310 / vb[2] >= 0.75, `幅 ${vb[2]}`);
  const small = viz.viewBox({ h: [1, 2] }).split(" ").map(Number);
  assert.ok(small[3] < vb[3]);
});

test("render は偽の h で全ステップを描け、座標に NaN が出ない", () => {
  for (const h of [[8, 1, 7, 2, 9, 6], [3, 3], [0, 99, 0, 99]]) {
    const config = { h };
    for (const s of viz.states(config)) {
      const items = [];
      const svg = { appendChild: (e) => items.push(e) };
      const mk = (tag, attrs, text) => ({ tag, attrs, text });
      viz.render(svg, s, config, mk);
      assert.ok(items.length > 0);
      for (const it of items) {
        for (const [k, v] of Object.entries(it.attrs || {})) {
          if (typeof v === "number") assert.ok(Number.isFinite(v), `${it.tag}.${k} = ${v}`);
          if (k === "d") assert.doesNotMatch(String(v), /NaN|Infinity/);
        }
      }
    }
  }
});

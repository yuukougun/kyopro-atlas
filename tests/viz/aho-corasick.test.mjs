// 動く図（Aho-Corasick 法：BFS 順に失敗リンクを張り、テキストを流して出現を見つける）の、状態の列を作る関数の単体試験（design.md §8.5）
// 実行：node --test "tests/viz/*.test.mjs"
import { test } from "node:test";
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import vm from "node:vm";

const SRC = new URL("../../overrides/assets/js/viz/aho-corasick.js", import.meta.url);

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

const raw = loadViz("aho-corasick");
// vm の別の文脈で作った値は deepStrictEqual で比べられないので、JSON を通してこちらの文脈の値にする
const plain = (x) => JSON.parse(JSON.stringify(x));
const viz = { ...raw, states: (config) => plain(raw.states(config)) };

// 本文（docs/string/aho-corasick.md の failure-links の節）の config
const PAGE = { patterns: ["he", "she", "his", "hers"], text: "ushers" };

// ---------- 素朴な方法（定義どおりに求める。図の JS とは別に書く） ----------

// Trie にある文字列（パターンの接頭辞すべて。根は ""）
function prefixSet(patterns) {
  const set = new Set([""]);
  for (const p of patterns) for (let i = 1; i <= p.length; i++) set.add(p.slice(0, i));
  return set;
}
// s の接尾辞のうち Trie にある最長のもの（proper なら s 自身を除く）
function longestSuffix(set, s, proper) {
  for (let k = proper ? 1 : 0; k <= s.length; k++) if (set.has(s.slice(k))) return s.slice(k);
  return "";
}
const naiveLink = (set, s) => (s === "" ? "" : longestSuffix(set, s, true));
const naiveNext = (set, s, c) => longestSuffix(set, s + c, false);
// BFS 順（子は文字の順）と、各取り出しの後のキュー
function naiveBfs(set) {
  const order = [], queues = [];
  const q = [""];
  while (q.length) {
    const s = q.shift();
    order.push(s);
    const kids = [...set].filter((t) => t.length === s.length + 1 && t.startsWith(s)).sort();
    q.push(...kids);
    queues.push([...q]);
  }
  return { order, queues };
}
// テキストの [0, end) の中で end で終わる出現（end ごと、長い順）
function naiveOccurrences(patterns, text) {
  const out = [];
  for (let end = 1; end <= text.length; end++) {
    const here = [];
    patterns.forEach((p, j) => {
      if (end >= p.length && text.slice(end - p.length, end) === p) here.push({ pattern: j, start: end - p.length, end });
    });
    here.sort((a, b) => a.start - b.start);
    out.push(...here);
  }
  return out;
}
const key = (o) => `${o.pattern}:${o.start}:${o.end}`;
const keys = (list) => list.map(key).sort();

// どの状態でも保つ性質と、素朴な方法との一致
function checkAll(config, states) {
  const { patterns, text } = config;
  const set = prefixSet(patterns);
  const sigma = [...new Set(patterns.join(""))].sort();
  const { order, queues } = naiveBfs(set);
  const isPat = (s) => patterns.includes(s);
  const markOf = (s) => patterns.some((p) => s.endsWith(p));
  const n = set.size;
  assert.equal(states.length, 1 + n + 1 + text.length + 1, "状態の数");
  const phases = states.map((s) => s.phase);
  assert.deepEqual(phases, ["init", ...Array(n).fill("pop"), "scan", ...Array(text.length).fill("read"), "done"]);
  for (const [idx, st] of states.entries()) {
    assert.equal(typeof st.caption, "string");
    assert.ok(st.caption.length > 0, `状態 ${idx}: caption が空`);
    // 「根」に助詞が続くときは空白を入れない（式の後の「= 根 の行」は式なので空白を入れる）
    assert.ok(!/根 (に子|へ(進む|移る)|のまま)/.test(st.caption), `状態 ${idx}: 「根」の後に余分な空白：${st.caption}`);
  }

  // 前半：初期状態
  const init = states[0];
  assert.deepEqual(init.queue, [""]);
  for (const s of set) {
    assert.equal(init.link[s], s === "" ? "" : null, `init: link(${s})`);
    assert.equal(init.mark[s], isPat(s), `init: mark(${s})`);
  }
  // 前半：取り出し 1 回ごと
  const decided = new Set([""]);
  for (let t = 0; t < n; t++) {
    const st = states[1 + t];
    const v = order[t];
    assert.equal(st.popped, v, `取り出す順が BFS 順と違う（${t} 番目）`);
    assert.deepEqual(st.done, order.slice(0, t + 1));
    assert.deepEqual(st.queue, queues[t], `${v} の後のキュー`);
    // 失敗リンク先と行
    const from = v === "" ? null : naiveLink(set, v);
    assert.equal(st.from, from, `link(${v})`);
    for (const c of sigma) assert.equal(st.row[c], naiveNext(set, v, c), `nxt[${v}][${c}]`);
    if (from === null) assert.equal(st.fromRow, null);
    else for (const c of sigma) assert.equal(st.fromRow[c], naiveNext(set, from, c), `nxt[${from}][${c}]`);
    // 子と、子の失敗リンク：link(u) = nxt[link(v)][c]。子のない欄は link(v) の行を写す
    const kids = sigma.filter((c) => set.has(v + c));
    assert.deepEqual(st.kids.map((k) => k.c), kids);
    for (const k of st.kids) {
      assert.equal(k.u, v + k.c);
      assert.equal(k.link, naiveLink(set, k.u), `link(${k.u})`);
      assert.equal(k.link, from === null ? "" : st.fromRow[k.c], "link(u) = nxt[link(v)][c]");
      assert.equal(st.row[k.c], k.u, "子のある欄は自分の子");
      decided.add(k.u);
    }
    for (const c of sigma) if (!kids.includes(c)) assert.equal(st.row[c], from === null ? "" : st.fromRow[c], "子のない欄は写す");
    // 決まった失敗リンクだけが値を持つ
    for (const s of set) assert.equal(st.link[s], decided.has(s) ? naiveLink(set, s) : null, `${v} の後の link(${s})`);
    // 終端の印：取り出し済みの節点は「接尾辞にパターンがある」、まだのものは自分がパターンか
    const doneSet = new Set(order.slice(0, t + 1));
    for (const s of set) assert.equal(st.mark[s], doneSet.has(s) ? markOf(s) : isPat(s), `${v} の後の mark(${s})`);
    assert.equal(st.inherited, from !== null && markOf(from), `${v} は印を受け継ぐか`);
  }

  // 後半
  const all = naiveOccurrences(patterns, text);
  const scan = states[n + 1];
  assert.equal(scan.cur, "");
  assert.deepEqual(scan.trail, []);
  assert.deepEqual(scan.counts, patterns.map(() => 0));
  let prev = "";
  for (let i = 0; i < text.length; i++) {
    const st = states[n + 2 + i];
    const c = text[i];
    const want = longestSuffix(set, text.slice(0, i + 1), false);
    assert.equal(st.pos, i + 1);
    assert.equal(st.char, c);
    assert.equal(st.prev, prev);
    assert.equal(st.cur, want, `${i + 1} 文字目の後の状態`);
    assert.equal(st.cur, naiveNext(set, prev, c), "遷移表どおりに動く");
    assert.equal(st.via, set.has(prev + c) ? "child" : prev === "" ? "root" : "jump");
    assert.deepEqual(st.trail, [...Array(i + 1).keys()].map((k) => longestSuffix(set, text.slice(0, k + 1), false)));
    // 連鎖：cur から失敗リンクで根まで
    const chain = [want];
    while (chain.at(-1) !== "") chain.push(naiveLink(set, chain.at(-1)));
    assert.deepEqual(st.chain, chain);
    // ここで終わる出現 = 連鎖の上の終端
    const here = all.filter((o) => o.end === i + 1);
    assert.deepEqual(keys(st.found), keys(here), `${i + 1} 文字目で終わる出現`);
    assert.deepEqual(keys(st.found), keys(chain.filter(isPat).map((s) => ({ pattern: patterns.indexOf(s), start: i + 1 - s.length, end: i + 1 }))));
    assert.deepEqual(keys(st.all), keys(all.filter((o) => o.end <= i + 1)));
    assert.deepEqual(st.counts, patterns.map((_, j) => all.filter((o) => o.pattern === j && o.end <= i + 1).length));
    prev = want;
  }
  const done = states.at(-1);
  assert.equal(done.pos, text.length);
  assert.deepEqual(keys(done.all), keys(all));
  assert.deepEqual(done.counts, patterns.map((_, j) => all.filter((o) => o.pattern === j).length));
  for (const st of states.slice(n + 1)) {
    for (const s of set) {
      assert.equal(st.link[s], naiveLink(set, s));
      assert.equal(st.mark[s], markOf(s));
    }
  }
}

test("試験の config が本文の div と同じ", () => {
  const md = readFileSync(new URL("../../docs/string/aho-corasick.md", import.meta.url), "utf8");
  const configs = [...md.matchAll(/data-viz="aho-corasick" data-config='([^']*)'/g)].map((m) => JSON.parse(m[1]));
  assert.equal(configs.length, 1);
  assert.deepEqual(configs[0], PAGE);
});

test("本文の例 he, she, his, hers と ushers（静的な図・本文の説明と同じ）", () => {
  const states = viz.states(PAGE);
  checkAll(PAGE, states);
  assert.equal(states.length, 19);
  // 取り出す順（BFS 順）と、決まった失敗リンク（静的な図 failure-links.svg と同じ）
  const pops = states.filter((s) => s.phase === "pop");
  assert.deepEqual(pops.map((s) => s.popped), ["", "h", "s", "he", "hi", "sh", "her", "his", "she", "hers"]);
  assert.deepEqual(states.at(-1).link, { "": "", h: "", he: "", s: "", sh: "h", she: "he", hi: "", his: "s", her: "", hers: "s" });
  // 手引きの caption の例：sh を取り出すと、子 she の失敗リンクは nxt[link(sh) = h][e] = he
  const sh = pops[5];
  assert.equal(sh.popped, "sh");
  assert.equal(sh.from, "h");
  assert.deepEqual(sh.fromRow, { e: "he", h: "h", i: "hi", r: "", s: "s" });
  assert.deepEqual(sh.row, { e: "she", h: "h", i: "hi", r: "", s: "s" });
  assert.deepEqual(sh.kids, [{ c: "e", u: "she", link: "he" }]);
  assert.match(sh.caption, /^sh を取り出す。/);
  assert.match(sh.caption, /子 she の失敗リンクは nxt\[link\(sh\) = h\]\[e\] = he である。/);
  assert.deepEqual(sh.queue, ["her", "his", "she"]);
  // 根を取り出すと、根の子 h, s の失敗リンクは根
  assert.match(pops[0].caption, /根の子 h, s の失敗リンクは根にする/);
  // she は link(she) = he の終端の印を受け継ぐ（本文の inherit-terminal、静的な図の注記）
  const she = pops[8];
  assert.equal(she.popped, "she");
  assert.equal(she.inherited, true);
  assert.match(she.caption, /link\(she\) = he が終端の印を持つので、she もその印を受け継ぐ。/);
  // 状態は 根 → s → sh → she → her → hers と動く（最初の u は根のまま）
  const reads = states.filter((s) => s.phase === "read");
  assert.deepEqual(reads.map((s) => s.cur), ["", "s", "sh", "she", "her", "hers"]);
  assert.deepEqual(reads.map((s) => s.via), ["root", "child", "child", "child", "jump", "child"]);
  assert.match(reads[0].caption, /根に子 u はないので、根のままである/);
  // 4 文字目：失敗リンクをたどると she・he・根 で、出現は she と he の 2 つ
  assert.deepEqual(reads[3].chain, ["she", "he", ""]);
  assert.deepEqual(reads[3].found, [{ pattern: 1, start: 1, end: 4 }, { pattern: 0, start: 2, end: 4 }]);
  assert.match(reads[3].caption, /失敗リンクをたどると she・he・根 で、ここで終わる出現は she と he の 2 つである。/);
  // 5 文字目：she に子 r はなく、遷移表の nxt[she][r] = her（he の行から写した値）へ移る
  assert.equal(reads[4].prev, "she");
  assert.match(reads[4].caption, /nxt\[she\]\[r\] = her（link\(she\) = he の行から写した値）なので、her へ移る/);
  assert.deepEqual(reads[4].found, []);
  // 6 文字目：hers・s・根 をたどり、hers の出現が分かる
  assert.deepEqual(reads[5].chain, ["hers", "s", ""]);
  assert.deepEqual(reads[5].found, [{ pattern: 3, start: 2, end: 6 }]);
  // 回数は he 1・she 1・his 0・hers 1（静的な図 fail-tree.svg の部分木の和と同じ）
  assert.deepEqual(states.at(-1).counts, [1, 1, 0, 1]);
  assert.match(states.at(-1).caption, /出現は she・he（4 文字目で終わる）と hers（6 文字目で終わる）の 3 つである。/);
});

test("終端の印の受け継ぎ（本文の inherit-terminal の例 bc・abcd と abcx）", () => {
  const config = { patterns: ["bc", "abcd"], text: "abcx" };
  const states = viz.states(config);
  checkAll(config, states);
  const abc = states.find((s) => s.popped === "abc");
  assert.equal(abc.from, "bc");
  assert.equal(abc.inherited, true);
  assert.equal(abc.mark.abc, true);
  assert.match(abc.caption, /abc 自身はパターンの終端ではない/);
  // 状態は a → ab → abc → 根。3 文字目で bc が現れ、x で根へ移る
  const reads = states.filter((s) => s.phase === "read");
  assert.deepEqual(reads.map((s) => s.cur), ["a", "ab", "abc", ""]);
  assert.deepEqual(reads[2].found, [{ pattern: 0, start: 1, end: 3 }]);
  assert.equal(reads[3].via, "jump");
  assert.match(reads[3].caption, /nxt\[abc\]\[x\] = 根（link\(abc\) = bc の行から写した値）なので、根へ移る。状態が根なので/);
});

test("端の場合：1 文字・パターンに現れない文字だけ・入れ子のパターン・同じ節点にとどまる移動", () => {
  const one = { patterns: ["a"], text: "a" };
  const s1 = viz.states(one);
  checkAll(one, s1);
  assert.equal(s1.length, 1 + 2 + 1 + 1 + 1);
  assert.deepEqual(s1.at(-1).counts, [1]);
  const none = { patterns: ["ab"], text: "xyz" };
  const s2 = viz.states(none);
  checkAll(none, s2);
  assert.ok(s2.filter((s) => s.phase === "read").every((s) => s.cur === "" && s.via === "root"));
  assert.match(s2.at(-1).caption, /パターンの出現はなかった/);
  const nest = { patterns: ["a", "aa", "aaa"], text: "aaaa" };
  const s3 = viz.states(nest);
  checkAll(nest, s3);
  assert.deepEqual(s3.at(-1).counts, [4, 3, 2]);
  // aaa で a を読むと aaa のまま（nxt[aaa][a] = aaa）
  const last = s3.filter((s) => s.phase === "read").at(-1);
  assert.equal(last.prev, "aaa");
  assert.equal(last.cur, "aaa");
  assert.equal(last.via, "jump");
  assert.match(last.caption, /aaa のままである/);
  assert.deepEqual(last.chain, ["aaa", "aa", "a", ""]);
  // 1 つ目のパターンが 2 つ目の接尾辞（Wikipedia の例に近い 6 パターン）
  const wiki = { patterns: ["a", "ab", "bab", "bc", "bca", "caa"], text: "abccab" };
  checkAll(wiki, viz.states(wiki));
  // 上限ちょうど：テキスト 8 文字・深さ 5・文字 6 種類・パターン 6 個・葉 4 個
  const big = { patterns: ["abcde", "abf", "bcd", "b", "bc", "f"], text: "abcdefbc" };
  checkAll(big, viz.states(big));
});

test("乱数で作った多数の config で、素朴な方法と一致し、性質が保たれる", () => {
  let seed = 20261029;
  const rand = () => {
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return seed / 2147483648;
  };
  const pick = (s) => s[Math.floor(rand() * s.length)];
  let tested = 0, rejected = 0;
  for (let t = 0; t < 3000; t++) {
    const alpha = rand() < 0.5 ? "ab" : "abc";
    const k = 1 + Math.floor(rand() * 5);
    const pats = [];
    for (let j = 0; j < k; j++) {
      const len = 1 + Math.floor(rand() * 4);
      let p = "";
      for (let i = 0; i < len; i++) p += pick(alpha);
      if (!pats.includes(p)) pats.push(p);
    }
    const tl = 1 + Math.floor(rand() * 8);
    let text = "";
    for (let i = 0; i < tl; i++) text += pick(alpha + (rand() < 0.2 ? "d" : ""));
    const config = { patterns: pats, text };
    let states;
    try {
      states = viz.states(config);
    } catch (e) {
      // 葉が多すぎる Trie などは描けない。理由は Error の文で分かる
      assert.match(e.message, /葉|節点/);
      rejected++;
      continue;
    }
    checkAll(config, states);
    tested++;
  }
  assert.ok(tested >= 2000, `試した config が少ない（${tested}）`);
  assert.ok(rejected > 0);
  // a と b の 6 文字以下のテキストすべてで、本文と同じ形の 2 つのパターン集合を試す
  for (const patterns of [["ab", "bab", "b"], ["aa", "aba", "baa"]]) {
    for (let len = 1; len <= 6; len++) {
      for (let m = 0; m < 1 << len; m++) {
        let text = "";
        for (let i = 0; i < len; i++) text += m >> i & 1 ? "b" : "a";
        checkAll({ patterns, text }, viz.states({ patterns, text }));
      }
    }
  }
});

test("同じ入力からは同じ状態の列ができ、入力を書き換えない", () => {
  const config = { patterns: ["he", "she", "his", "hers"], text: "ushers" };
  const before = JSON.stringify(config);
  assert.deepEqual(viz.states(config), viz.states(config));
  assert.equal(JSON.stringify(config), before);
});

test("入力が正しくないときは Error を投げる", () => {
  assert.throws(() => viz.states(null), /data-config/);
  assert.throws(() => viz.states([1]), /data-config/);
  assert.throws(() => viz.states({ text: "ab" }), /patterns は/);
  assert.throws(() => viz.states({ patterns: "he", text: "ab" }), /patterns は/);
  assert.throws(() => viz.states({ patterns: [], text: "ab" }), /patterns は/);
  assert.throws(() => viz.states({ patterns: ["a", "b", "c", "d", "e", "f", "g"], text: "ab" }), /patterns は 1〜6 個/);
  assert.throws(() => viz.states({ patterns: [""], text: "ab" }), /各要素/);
  assert.throws(() => viz.states({ patterns: ["abcdef"], text: "ab" }), /各要素は英小文字 1〜5 文字/);
  assert.throws(() => viz.states({ patterns: ["He"], text: "ab" }), /各要素/);
  assert.throws(() => viz.states({ patterns: [12], text: "ab" }), /各要素/);
  assert.throws(() => viz.states({ patterns: ["a b"], text: "ab" }), /各要素/);
  assert.throws(() => viz.states({ patterns: ["ab", "ab"], text: "ab" }), /同じ文字列が 2 回ある：ab/);
  assert.throws(() => viz.states({ patterns: ["ab"] }), /text は/);
  assert.throws(() => viz.states({ patterns: ["ab"], text: "" }), /text は/);
  assert.throws(() => viz.states({ patterns: ["ab"], text: "abcdefghi" }), /text は 1〜8 文字/);
  assert.throws(() => viz.states({ patterns: ["ab"], text: "aB" }), /text の文字/);
  assert.throws(() => viz.states({ patterns: ["ab"], text: "a1" }), /text の文字/);
  assert.throws(() => viz.states({ patterns: ["abcde", "bcdea", "cdeab", "deabc"], text: "ab" }), /節点が根を含めて 21 個ある。16 個まで/);
  assert.throws(() => viz.states({ patterns: ["a", "b", "c", "d", "e"], text: "ab" }), /葉が 5 個ある。.*4 個まで/);
  assert.throws(() => viz.states({ patterns: ["abcd", "efg"], text: "ab" }), /文字が 7 種類ある。6 種類まで/);
});

test("viewBox は全ステップで同じで、幅 400・高さは深さと出現の重なりに合わせる", () => {
  const vb = raw.viewBox(PAGE).split(" ").map(Number);
  assert.deepEqual(vb.slice(0, 3), [0, 0, 400]);
  // 幅 390 の画面（図の幅 約 337px）で、22em（352px）の高さの上限にかからない
  assert.ok(vb[3] > 300 && vb[3] * 337 / 400 <= 352, `高さ ${vb[3]}`);
  const shallow = raw.viewBox({ patterns: ["a"], text: "a" }).split(" ").map(Number);
  const deep = raw.viewBox({ patterns: ["abcde"], text: "a" }).split(" ").map(Number);
  assert.ok(deep[3] > shallow[3]);
  assert.ok(deep[3] <= 470);
});

// ---------- 描画（偽の h で render を呼ぶ） ----------

const h = (tag, attrs, text) => ({ tag, attrs: attrs || {}, text: text == null ? null : String(text) });
function draw(state, config) {
  const kids = [];
  raw.render({ appendChild: (e) => kids.push(e) }, state, config, h);
  return kids;
}
const sts = raw.states(PAGE);
const byAttr = (els, name, value) => els.filter((e) => e.attrs[name] === value);

test("前半の描画：このステップで決まった失敗リンクを太く、写す元に輪、行の表は子の欄と写した欄を描き分ける", () => {
  // 根を取り出す：子 h, s の「根」の札が太い。写す元の行はない（点線の空の欄）
  const root = draw(sts[1], PAGE);
  for (const v of ["h", "s"]) assert.match(byAttr(root, "data-root-tag", v)[0].attrs.style, /stroke-width:3;/);
  assert.equal(root.filter((e) => e.attrs["data-root-tag"] != null).length, 2);
  // he を取り出すと、子 her の札が太く、前に決まった h・s・he・hi の札は細い
  const he = draw(sts[4], PAGE);
  assert.match(byAttr(he, "data-root-tag", "her")[0].attrs.style, /stroke-width:3;/);
  for (const v of ["h", "s", "he", "hi"]) assert.match(byAttr(he, "data-root-tag", v)[0].attrs.style, /stroke-width:1\.6;/);
  assert.equal(root.filter((e) => e.tag === "rect" && /^from:/.test(e.attrs["data-cell"] || "") && /is-sentinel/.test(e.attrs.class)).length, 5);
  // sh を取り出す：she → he の新しい失敗リンクが太く、h に写す元の輪、表は e の欄が子 she
  const sh = draw(sts[6], PAGE);
  const link = byAttr(sh, "data-link", "she");
  assert.equal(link.length, 1);
  assert.match(link[0].attrs.style, /stroke-width:3\.2/);
  assert.match(byAttr(sh, "data-link", "his")[0].attrs.style, /stroke-width:1\.6/);
  assert.equal(byAttr(sh, "data-source", "h").length, 1);
  const cellText = (data) => {
    const i = sh.findIndex((e) => e.attrs["data-cell"] === data);
    assert.ok(i >= 0, data);
    return { rect: sh[i], text: sh[i + 1].text };
  };
  assert.equal(cellText("row:e").text, "she");
  assert.match(cellText("row:e").rect.attrs.class, /is-yes/);
  assert.equal(cellText("row:h").rect.attrs["stroke-dasharray"], "4 3"); // 写した値は破線
  assert.equal(cellText("row:r").text, "根");
  assert.equal(cellText("from:e").text, "he");
  assert.match(cellText("from:e").rect.attrs.class, /is-focus/); // 子の失敗リンクになる値
  assert.ok(sh.some((e) => e.tag === "text" && e.text === "キュー（先頭 → 末尾）：her, his, she"));
  assert.ok(sh.some((e) => e.tag === "text" && e.text === "link(sh) = h"));
  // 取り出す前の節点は点線の円（失敗リンクが未定）
  const init = draw(sts[0], PAGE);
  assert.equal(init.filter((e) => e.tag === "circle" && e.attrs["data-node"] != null && /is-sentinel/.test(e.attrs.class)).length, 9);
  assert.equal(init.filter((e) => e.attrs["data-link"] != null || e.attrs["data-root-tag"] != null).length, 0);
});

test("後半の描画：いまの状態・連鎖・出現の括弧・回数と、子へ進まない移動の矢印", () => {
  const r4 = draw(sts[15], PAGE); // 4 文字目 e
  assert.equal(sts[15].cur, "she");
  const nodeCls = (s) => byAttr(r4, "data-node", s)[0].attrs.class;
  assert.match(nodeCls("she"), /is-answer/);
  assert.match(nodeCls("he"), /is-yes/);
  assert.match(nodeCls(""), /is-yes/);
  assert.doesNotMatch(nodeCls("sh"), /is-yes|is-answer/);
  // sh → she の辺が太線、she → he のリンクが太く、he の「根」の札も太い
  assert.match(byAttr(r4, "data-edge", "she")[0].attrs.class, /is-focus/);
  assert.match(byAttr(r4, "data-link", "she")[0].attrs.style, /stroke-width:3\.2/);
  // 終端の輪：she と he は出現として太く、hers は細い
  assert.match(byAttr(r4, "data-terminal", "she")[0].attrs.class, /is-focus/);
  assert.match(byAttr(r4, "data-terminal", "he")[0].attrs.class, /is-focus/);
  assert.doesNotMatch(byAttr(r4, "data-terminal", "hers")[0].attrs.class, /is-focus/);
  // 出現の括弧は she（1 文字目から）と he（2 文字目から）
  assert.deepEqual(r4.filter((e) => e.attrs["data-occ"]).map((e) => e.attrs["data-occ"]).sort(), ["he@2", "she@1"]);
  assert.deepEqual(r4.filter((e) => e.attrs["data-trail"] != null).map((e) => e.text), ["根", "s", "sh", "she"]);
  assert.deepEqual(r4.filter((e) => e.attrs["data-count"]).map((e) => e.text), ["he 1・", "she 1・", "his 0・", "hers 0"]);
  // 5 文字目 r：she から her へ、実線の矢印
  const r5 = draw(sts[16], PAGE);
  assert.equal(byAttr(r5, "data-move", "she>her").length, 1);
  assert.equal(r5.filter((e) => e.attrs["data-move"] != null).length, 1);
  assert.equal(r4.filter((e) => e.attrs["data-move"] != null).length, 0);
  // 読み終わり：括弧 3 つ、節点の強調なし
  const end = draw(sts.at(-1), PAGE);
  assert.equal(end.filter((e) => e.attrs["data-occ"]).length, 3);
  assert.equal(end.filter((e) => e.attrs["data-node"] != null && /is-answer|is-yes/.test(e.attrs.class)).length, 0);
});

test("辺の文字は、写す元の輪・出現の太い輪に隠れないよう、どのステップでも節点と輪より後に縁取り付きで描く", () => {
  for (const [i, s] of sts.entries()) {
    const els = draw(s, PAGE);
    const labels = els.map((e, k) => [e, k]).filter(([e]) => e.attrs["data-edge-label"] != null);
    assert.equal(labels.length, 9, `状態 ${i}: 辺の文字の数`);
    const isNodeOrRing = (e) => e.tag === "circle" &&
      (e.attrs["data-node"] != null || e.attrs["data-terminal"] != null || e.attrs["data-source"] != null);
    const lastRing = Math.max(...els.map((e, k) => (isNodeOrRing(e) ? k : -1)));
    for (const [e, k] of labels) {
      assert.ok(k > lastRing, `状態 ${i}: 辺の文字 ${e.text} が節点や輪より先に描かれる`);
      assert.match(e.attrs.style, /paint-order:stroke/);
    }
  }
  // 10 / 19（she を取り出す。写す元 he の輪）でも、he → her の「r」は輪の後に描く
  assert.equal(sts[9].popped, "she");
  const s10 = draw(sts[9], PAGE);
  const ringAt = s10.findIndex((e) => e.attrs["data-source"] === "he");
  const rAt = s10.findIndex((e) => e.attrs["data-edge-label"] === "her");
  assert.ok(ringAt >= 0 && rAt > ringAt);
  assert.equal(s10[rAt].text, "r");
});

// path の d（M・Q・L だけ）から点を拾う
function pathPoints(d) {
  const nums = d.match(/-?\d+(\.\d+)?/g).map(Number);
  const cmds = d.match(/[MQLHVz]/g);
  const pts = [];
  if (cmds[0] === "M" && cmds[1] === "Q" && nums.length === 6) {
    const [x0, y0, cx, cy, x2, y2] = nums;
    for (let i = 0; i <= 40; i++) {
      const t = i / 40, u = 1 - t;
      pts.push([u * u * x0 + 2 * u * t * cx + t * t * x2, u * u * y0 + 2 * u * t * cy + t * t * y2]);
    }
  }
  return pts;
}

test("本文の例では、失敗リンクの曲線がほかの節点の円に重ならず、文字が枠に収まる", () => {
  const [, , vw, vh] = raw.viewBox(PAGE).split(" ").map(Number);
  for (const [i, s] of sts.entries()) {
    const els = draw(s, PAGE);
    const circles = els.filter((e) => e.tag === "circle" && e.attrs["data-node"] != null)
      .map((e) => ({ s: e.attrs["data-node"], x: Number(e.attrs.cx), y: Number(e.attrs.cy), r: Number(e.attrs.r) }));
    const terminals = new Set(els.filter((e) => e.attrs["data-terminal"] != null).map((e) => e.attrs["data-terminal"]));
    for (const e of els.filter((x) => x.attrs["data-link"] != null || x.attrs["data-move"] != null)) {
      const from = e.attrs["data-link"] ?? e.attrs["data-move"].split(">")[0];
      const to = e.attrs["data-link"] != null ? plain(s.link)[from] : e.attrs["data-move"].split(">")[1];
      for (const p of pathPoints(e.attrs.d)) {
        for (const c of circles) {
          if (c.s === from || c.s === to) continue;
          const clear = Math.hypot(p[0] - c.x, p[1] - c.y) - c.r - (terminals.has(c.s) ? 4 : 0);
          assert.ok(clear >= 4, `状態 ${i}: ${from} → ${to} の線が ${c.s} に近い（${clear.toFixed(1)}）`);
        }
      }
    }
    // 文字（中央・左・右そろえの幅の見積もり）が枠の中
    for (const e of els.filter((x) => x.tag === "text")) {
      const fs = Number(((e.attrs.style || "").match(/font-size:([\d.]+)px/) || [0, 16])[1]);
      let w = 0;
      for (const ch of e.text) w += ch.charCodeAt(0) >= 0x2000 ? fs : 0.56 * fs;
      const anchor = ((e.attrs.style || "").match(/text-anchor:(\w+)/) || [0, "middle"])[1];
      const x = Number(e.attrs.x), y = Number(e.attrs.y);
      const x0 = anchor === "start" ? x : anchor === "end" ? x - w : x - w / 2;
      assert.ok(x0 >= 2 && x0 + w <= vw - 2 && y - fs / 2 >= 0 && y + fs / 2 <= vh, `状態 ${i}: 文字「${e.text}」が枠の外`);
    }
  }
});

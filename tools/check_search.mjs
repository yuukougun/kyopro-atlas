#!/usr/bin/env node
// サイト内検索の上位を確かめる（Issue #52）。
//
// ビルドしたサイトの検索の索引（search/search_index.json）と Material for MkDocs の検索の worker
// （assets/javascripts/workers/search.*.min.js。言語の追加の lunr のファイルも）を、node の vm の中でそのまま動かし、
// 検索欄に語を入れたときと同じ順のページの並び（検索の結果の 1 件 = 1 ページ）を出す。ブラウザも npm のパッケージも要らない
// （node 20 以上）。ヘッドレスの Chrome で検索欄に入れた結果と、上位 6 件と件数が 45 語すべてで一致することを確かめてある。
//
// 使い方:
//   uv run mkdocs build -q -d <フォルダ>                       サイトをビルドする（作業中は site/ でなく別のフォルダへ）
//   python3 -m http.server -d <ビルドしたサイト> 8000 &      ビルドしたサイトを http で配っておく
//   node tools/check_search.mjs                                代表の語（下の CASES）で、目的のページが上位 3 件に入るかを見る
//   node tools/check_search.mjs --base http://127.0.0.1:8000/  配っている場所（既定は http://127.0.0.1:8000/）
//   node tools/check_search.mjs --site <ビルドしたフォルダ>        http を使わずにファイルから読む
//   node tools/check_search.mjs セグ木 'BIT=fenwick-tree'      語ごとの上位を出す（「語=id」で目的のページを指定できる）
//   node tools/check_search.mjs --sweep                        全ページの題名と別名（docs/ の front matter）でも引き、
//                                                              そのページが上位 K 件にないものの数を出す（-v で一覧）
//   node tools/check_search.mjs --json out.json                結果を JSON に書く
//   node tools/check_search.mjs --compare before.json          前の --json の結果と順位を比べる（直す前と後）
//   --top N（出す件数。既定 6）、--within K（合格の順位。既定 3）、--docs DIR（--sweep で読む docs。既定はリポジトリの docs）
// 終了コード: 0＝代表の語がすべて上位 K 件に入る、1＝入らない語がある、2＝索引や worker を読めない
//
// 検索の重みの仕組み（mkdocs-material 9.7.7 で確かめた。報告 planning/batches/fix/lookup/search.md）:
//   - 題名（h1 と各見出し）は本文の 1000 倍、front matter の tags は 1,000,000 倍の重みで索引に入る（fields の既定）。
//     front matter の search.boost は、そのページの全部の節の点を掛け算で上げる。aliases は本文の「別名」の行に
//     入るだけなので、本文と同じ重みしかない
//   - 語の後ろには * が付き、前方一致で引く。漢字の続きは索引にある語で区切り直されるが、続きの最後の 1 字は落ちる
//     （「累積和」は「累積*」、「区間」のような 2 字の語は「区*」として引かれる）
import fs from 'node:fs';
import path from 'node:path';
import vm from 'node:vm';
import zlib from 'node:zlib';
import { fileURLToPath } from 'node:url';

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');

// 代表の語と目的のページの id（「|」で区切ると、どれか 1 つが入ればよい）。
// #52 の 19 語は調査（2026-10-29）で目的のページが 1 位でなかった語。そのほかは 1 位だった語と、用語集の略称・直す表記から足した別名
const CASES = [
  // #52：上位 6 件にない・見つからなかった語
  ['BIT', 'fenwick-tree', '#52'],
  ['UF', 'union-find', '#52'],
  ['全方位木DP', 'rerooting', '#52'],
  ['全方位木 DP', 'rerooting', '#52'],
  ['ビットDP', 'bit-dp', '#52'],
  ['ビット DP', 'bit-dp', '#52'],
  ['フェニック木', 'fenwick-tree', '#52'],
  ['01BFS', 'zero-one-bfs', '#52'],
  ['にぶたん', 'binary-search', '#52'],
  ['グランディ', 'grundy-number', '#52'],
  // #52：1 位でなかった語
  ['セグ木', 'segment-tree', '#52'],
  ['Union-Find', 'union-find', '#52'],
  ['DSU', 'union-find', '#52'],
  ['Mo', 'mo-algorithm', '#52'],
  ['CHT', 'cht', '#52'],
  ['累積和', 'prefix-sum', '#52'],
  ['最小全域木', 'minimum-spanning-tree', '#52'],
  ['LIS', 'lis', '#52'],
  ['いもす', 'imos', '#52'],
  // 調査で 1 位だった語（崩していないかを見る）
  ['桁DP', 'digit-dp'], ['桁 DP', 'digit-dp'], ['ダイクストラ', 'dijkstra'], ['遅延セグ木', 'lazy-segment-tree'],
  ['座圧', 'coordinate-compression'], ['LCA', 'lca'], ['nCr', 'binomial-precompute|binomial-coefficient'],
  ['bit全探索', 'bit-full-search'], ['フェニック', 'fenwick-tree'], ['Fenwick', 'fenwick-tree'], ['全方位', 'rerooting'],
  ['01-BFS', 'zero-one-bfs'], ['尺取り', 'two-pointers'], ['クラスカル', 'minimum-spanning-tree'],
  ['期待値DP', 'expected-value-dp'], ['二分探索', 'binary-search'], ['ローリングハッシュ', 'rolling-hash'],
  ['ワーシャルフロイド', 'warshall-floyd'], ['ロリハ', 'rolling-hash'], ['Li Chao', 'cht'], ['主客転倒', 'contribution'],
  ['なもり', 'namori-graph'], ['Grundy', 'grundy-number'], ['トポロジカルソート', 'topological-sort'],
  ['二部マッチング', 'bipartite-matching'], ['最大流', 'max-flow'],
  // 用語集の略称・直す表記から別名に足した語（#52）
  ['グランディ数', 'grundy-number'], ['ユニオンファインド', 'union-find'], ['バイナリサーチ', 'binary-search'],
  ['bit DP', 'bit-dp'], ['セグメントツリー', 'segment-tree'], ['セグツリー', 'segment-tree'],
  ['プライオリティキュー', 'priority-queue'], ['ビットセット', 'bitset-speedup'], ['サフィックスアレイ', 'suffix-array'],
  ['マナカー', 'palindrome'], ['フロイドワーシャル法', 'warshall-floyd'], ['Z アルゴリズム', 'z-algorithm'],
  ['エイホコラシック法', 'aho-corasick'], ['尺とり法', 'two-pointers'], ['シャクトリ法', 'two-pointers'],
  ['エラトステネスのふるい', 'sieve-eratosthenes'], ['形式的べき級数', 'fps-basics'], ['スパニングツリー', 'minimum-spanning-tree'],
  ['優先順位付きキュー', 'priority-queue'], ['二分グラフ', 'bipartite-graph'],
];

// ---- 引数
function usage(msg) {
  if (msg) console.error(msg);
  console.error('使い方: node tools/check_search.mjs [--base URL | --site DIR] [--top N] [--within K] [--sweep] [-v] [--json FILE] [--compare FILE] [--docs DIR] [語[=id] ...]');
  process.exit(2);
}
const opt = { base: 'http://127.0.0.1:8000/', site: null, top: 6, within: 3, sweep: false, verbose: false, json: null, compare: null, docs: path.join(ROOT, 'docs'), queries: [] };
{
  const a = process.argv.slice(2);
  for (let i = 0; i < a.length; i++) {
    const need = () => (i + 1 < a.length ? a[++i] : usage(`${a[i]} の値がない`));
    if (a[i] === '--base') opt.base = need();
    else if (a[i] === '--site') opt.site = need();
    else if (a[i] === '--top') opt.top = Number(need());
    else if (a[i] === '--within') opt.within = Number(need());
    else if (a[i] === '--sweep') opt.sweep = true;
    else if (a[i] === '-v' || a[i] === '--verbose') opt.verbose = true;
    else if (a[i] === '--json') opt.json = need();
    else if (a[i] === '--compare') opt.compare = need();
    else if (a[i] === '--docs') opt.docs = need();
    else if (a[i] === '-h' || a[i] === '--help') usage();
    else if (a[i].startsWith('--')) usage(`知らない引数: ${a[i]}`);
    else opt.queries.push(a[i]);
  }
  if (!(opt.top >= 1) || !(opt.within >= 1)) usage('--top・--within は 1 以上');
  if (!opt.base.endsWith('/')) opt.base += '/';
}

// ---- サイトのファイルを読む（http か、フォルダから）
async function get(rel) {
  if (opt.site) return fs.readFileSync(path.join(opt.site, rel), 'utf8');
  const url = new URL(rel, opt.base);
  const r = await fetch(url);
  if (!r.ok) throw new Error(`HTTP ${r.status}: ${url}`);
  return r.text();
}

// ---- Material の検索の worker を vm の中で動かす。ブラウザの worker と同じく、SETUP で索引を渡し、QUERY で語を渡す
async function openSearch() {
  const html = await get('index.html');
  const m = html.match(/<script id="__config" type="application\/json">([\s\S]*?)<\/script>/);
  if (!m) throw new Error('index.html に __config がない（Material for MkDocs のサイトではない？）');
  const workerRel = JSON.parse(m[1]).search;
  if (!workerRel) throw new Error('__config に search（worker の場所）がない。検索が無効になっている？');
  const workerDir = path.posix.dirname(workerRel);
  const raw = await get('search/search_index.json');
  const listeners = [];
  let pending = null;
  const sandbox = {
    console: { log() {}, info() {}, warn() {}, error: (...x) => console.error(...x) },
    setTimeout, clearTimeout, queueMicrotask,
    addEventListener(type, fn) { if (type === 'message') listeners.push(fn); },
    postMessage(msg) { const p = pending; pending = null; if (p) p(msg); },
    // worker は await importScripts(...) と書いてあるので、Promise を返してよい
    async importScripts(...urls) {
      for (const u of urls) {
        const rel = path.posix.normalize(path.posix.join(workerDir, u));
        vm.runInContext(await get(rel), ctx, { filename: rel });
      }
    },
  };
  sandbox.self = sandbox;
  const ctx = vm.createContext(sandbox);
  vm.runInContext(await get(workerRel), ctx, { filename: workerRel });
  const send = (msg) => new Promise((resolve) => { pending = resolve; for (const fn of listeners) fn({ data: msg }); });
  sandbox.__raw = raw;
  const index = vm.runInContext('JSON.parse(__raw)', ctx); // worker の側の realm で読む
  delete sandbox.__raw;
  const ready = await send({ type: 0, data: { config: index.config, docs: index.docs, options: { suggest: false } } }); // SETUP
  if (ready.type !== 1) throw new Error('worker の準備ができない');
  const articles = new Set(index.docs.filter((d) => !d.location.includes('#')).map((d) => d.location));
  return {
    bytes: Buffer.byteLength(raw),
    gzip: zlib.gzipSync(raw, { level: 6 }).length,
    docs: index.docs.length,
    articles,
    // 結果の並び（ページごと）。表示と同じく、グループの中のページの項目（# のない location）の題名を使う
    async search(q) {
      const res = await send({ type: 2, data: q }); // QUERY → RESULT
      return res.data.items.map((group) => {
        const art = group.find((d) => !d.location.includes('#')) || group[0];
        return { location: art.location, title: String(art.title).replace(/<[^>]+>/g, '') };
      });
    },
  };
}

const idOf = (location) => location.replace(/\/$/, '').split('/').pop() || '(home)';
const rankOf = (list, want) => {
  const ws = want.split('|');
  const k = list.findIndex((x) => ws.includes(idOf(x.location)));
  return k < 0 ? 0 : k + 1;
};

// ---- front matter の題名と別名を読む（--sweep。PyYAML を使わず、title: と 1 行の aliases: [..] だけを読む）
function parseScalar(s) {
  s = s.trim();
  if (s.startsWith("'") && s.endsWith("'")) return s.slice(1, -1).replace(/''/g, "'");
  if (s.startsWith('"') && s.endsWith('"')) return JSON.parse(s);
  return s;
}
function parseFlowSeq(s) {
  s = s.trim();
  if (!s.startsWith('[') || !s.endsWith(']')) return null;
  const body = s.slice(1, -1), out = [];
  let cur = '', q = null;
  for (let i = 0; i < body.length; i++) {
    const c = body[i];
    if (q === "'") { if (c === "'" && body[i + 1] === "'") { cur += "'"; i++; } else if (c === "'") q = null; else cur += c; continue; }
    if (q === '"') { if (c === '\\') { cur += JSON.parse(`"\\${body[++i]}"`); } else if (c === '"') q = null; else cur += c; continue; }
    if ((c === "'" || c === '"') && cur.trim() === '') { q = c; cur = ''; continue; }
    if (c === ',') { out.push(cur.trim()); cur = ''; continue; }
    cur += c;
  }
  if (cur.trim() !== '') out.push(cur.trim());
  return out.filter((x) => x !== '');
}
function readPages(docs) {
  const pages = [];
  for (const field of fs.readdirSync(docs).sort()) {
    const dir = path.join(docs, field);
    if (!fs.statSync(dir).isDirectory() || field === 'lists' || field === 'index' || field === 'img') continue;
    for (const f of fs.readdirSync(dir).sort()) {
      if (!f.endsWith('.md') || f === 'index.md') continue;
      const text = fs.readFileSync(path.join(dir, f), 'utf8');
      const fm = text.match(/^---\n([\s\S]*?)\n---\n/);
      if (!fm) continue;
      const line = (key) => (fm[1].match(new RegExp(`^${key}:(.*)$`, 'm')) || [])[1];
      const id = f.slice(0, -3), title = line('title'), al = line('aliases');
      if (title === undefined) continue;
      pages.push({ id, location: `${field}/${id}/`, title: parseScalar(title), aliases: al === undefined ? [] : (parseFlowSeq(al) || []) });
    }
  }
  return pages;
}

// ---- 実行
let s;
try {
  s = await openSearch();
} catch (e) {
  console.error(`検索の索引か worker を読めない: ${e.message}`);
  console.error(opt.site ? `（${opt.site} はビルドしたサイトのフォルダか。例: uv run mkdocs build -d <フォルダ>）`
    : `（${opt.base} でビルドしたサイトを配っているか。例: python3 -m http.server -d <サイト> 8000）`);
  process.exit(2);
}
console.log(`索引: ${s.bytes.toLocaleString('en-US')} バイト（gzip 約 ${s.gzip.toLocaleString('en-US')} バイト）、項目 ${s.docs}、ページ ${s.articles.size}`);

const show = (list) => list.slice(0, opt.top).map((x) => idOf(x.location)).join(' ');
const result = { index: { bytes: s.bytes, gzip: s.gzip, docs: s.docs, pages: s.articles.size }, cases: [], sweep: null };

if (opt.queries.length) {
  // 語ごとの上位（「語=id」なら目的のページの順位も）
  for (const arg of opt.queries) {
    const k = arg.lastIndexOf('=');
    const [q, want] = k > 0 ? [arg.slice(0, k), arg.slice(k + 1)] : [arg, null];
    const list = await s.search(q);
    console.log(`\n## ${q}（${list.length} 件${want ? `、${want} は ${rankOf(list, want) || '-'} 位` : ''}）`);
    list.slice(0, opt.top).forEach((x, i) => console.log(`${i + 1}. ${x.title} <${x.location}>`));
    result.cases.push({ q, want, rank: want ? rankOf(list, want) : null, n: list.length, top: list.slice(0, opt.top).map((x) => idOf(x.location)) });
  }
} else {
  let bad = 0;
  console.log(`\n代表の語（${CASES.length} 語。目的のページが ${opt.within} 位以内なら合格）`);
  for (const [q, want, tag] of CASES) {
    const list = await s.search(q);
    const rank = rankOf(list, want);
    const ok = rank >= 1 && rank <= opt.within;
    if (!ok) bad++;
    result.cases.push({ q, want, tag: tag || null, rank, n: list.length, top: list.slice(0, opt.top).map((x) => idOf(x.location)) });
    if (!ok || opt.verbose || tag) console.log(`${ok ? '  ' : '✗ '}${String(rank || '-').padStart(3)} 位  ${q} → ${want}${tag ? `（${tag}）` : ''}  | ${show(list)}`);
  }
  const ok52 = result.cases.filter((c) => c.tag === '#52' && c.rank >= 1 && c.rank <= opt.within).length;
  const n52 = result.cases.filter((c) => c.tag === '#52').length;
  console.log(`合格 ${CASES.length - bad} / ${CASES.length}（#52 の語 ${ok52} / ${n52}）`);
  result.failed = bad;
}

if (opt.sweep) {
  const pages = readPages(opt.docs).filter((p) => s.articles.has(p.location)); // 検索から外したページは見ない
  const sweep = { titles: [], aliases: [] };
  for (const p of pages) {
    for (const [kind, q] of [['titles', p.title], ...p.aliases.map((a) => ['aliases', a])]) {
      const list = await s.search(q);
      sweep[kind].push({ q, want: p.id, rank: rankOf(list, p.id), top: list.slice(0, 3).map((x) => idOf(x.location)) });
    }
  }
  console.log(`\n全ページの題名と別名（${pages.length} ページ）`);
  for (const kind of ['titles', 'aliases']) {
    const rows = sweep[kind];
    const r1 = rows.filter((r) => r.rank === 1).length, rk = rows.filter((r) => r.rank >= 1 && r.rank <= opt.within).length;
    console.log(`${kind === 'titles' ? '題名' : '別名'}: ${rows.length} 語、1 位 ${r1}、${opt.within} 位以内 ${rk}、${opt.within} 位より下 ${rows.length - rk}`);
    if (opt.verbose) for (const r of rows) if (!(r.rank >= 1 && r.rank <= opt.within)) console.log(`  ${String(r.rank || '-').padStart(3)} 位  ${r.q} → ${r.want}  | ${r.top.join(' ')}`);
  }
  result.sweep = sweep;
}

if (opt.compare) {
  const prev = JSON.parse(fs.readFileSync(opt.compare, 'utf8'));
  const key = (c) => `${c.q}\t${c.want}`;
  const pm = new Map((prev.cases || []).map((c) => [key(c), c]));
  console.log(`\n前の結果（${opt.compare}）との比較`);
  console.log(`索引: ${prev.index.bytes.toLocaleString('en-US')} → ${s.bytes.toLocaleString('en-US')} バイト（gzip 約 ${prev.index.gzip.toLocaleString('en-US')} → ${s.gzip.toLocaleString('en-US')}）、項目 ${prev.index.docs} → ${s.docs}`);
  for (const c of result.cases) {
    const p = pm.get(key(c));
    if (!p || !c.want) continue;
    if (p.rank !== c.rank || c.tag) console.log(`  ${String(p.rank || '-').padStart(3)} 位 → ${String(c.rank || '-').padStart(3)} 位  ${c.q} → ${c.want}${c.tag ? `（${c.tag}）` : ''}`);
  }
  if (result.sweep && prev.sweep) {
    for (const kind of ['titles', 'aliases']) {
      const pmap = new Map(prev.sweep[kind].map((r) => [key(r), r]));
      const cnt = { g1: 0, l1: 0, gk: 0, lk: 0 }; const lost = [];
      const inK = (r) => r.rank >= 1 && r.rank <= opt.within;
      for (const r of result.sweep[kind]) {
        const p = pmap.get(key(r)); if (!p) continue;
        if (p.rank !== 1 && r.rank === 1) cnt.g1++;
        if (p.rank === 1 && r.rank !== 1) { cnt.l1++; lost.push(`  ${p.rank} 位 → ${r.rank || '-'} 位  ${r.q} → ${r.want}  | ${r.top.join(' ')}`); }
        if (!inK(p) && inK(r)) cnt.gk++;
        if (inK(p) && !inK(r)) cnt.lk++;
      }
      console.log(`${kind === 'titles' ? '題名' : '別名'}: 1 位になった ${cnt.g1}・1 位でなくなった ${cnt.l1}、${opt.within} 位以内に入った ${cnt.gk}・落ちた ${cnt.lk}`);
      if (opt.verbose) for (const l of lost) console.log(l);
    }
  }
}

if (opt.json) fs.writeFileSync(opt.json, JSON.stringify(result, null, 1) + '\n');
process.exit(result.failed ? 1 : 0);

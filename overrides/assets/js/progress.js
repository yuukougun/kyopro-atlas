/*
 * kyopro-atlas：進捗の記録（planning/interfaces.md §6・§7、design.md §9.1）
 *
 * - 記録は localStorage の1つのキー kyopro-atlas:v1 に JSON で持つ。
 *     {"solved": {"abc340_e": true}, "understood": {"lazy-segment-tree": {"水": true}},
 *      "wishlist": {"segment-tree": "2026-10-29T12:00:00+09:00"},
 *      "updatedAt": "2026-10-29T12:00:00+09:00", "exportedAt": "2026-10-29T12:30:00+09:00"}
 *   wishlist（勉強したいリスト：ページ id → 入れた時刻）と exportedAt（最後に書き出した時刻）は 2026-10-29 に足した（#1・#74）。
 *   この 2 つのない古い形の記録・書き出しも、そのまま読める（ない項目は空とみなす）。
 *   記録はこのブラウザの中だけにある。端末間の同期はしない（書き出し・読み込みで手動で退避する）
 * - 「解いた」：.kp-problems の各行の先頭にチェック欄を付ける（問題 ID はリンクの URL から取る）
 * - 「理解した」：テンプレートが出す input[data-kp-understood][data-kp-level] と結ぶ（ページ×レベル）。
 *   ロードマップの色ごとの列（h3#reading-order-<色> の後の表）の行の先頭にも、同じ記録のチェック欄を付ける（#74）。
 *   <div class="kp-order-tools"></div> に「理解した行を隠す」の切り替えを出す
 * - 「勉強したい」：テンプレートが出す input[data-kp-wish] と結ぶ。<div class="kp-wishlist"></div> に一覧を出す（#1）
 * - 書き出し・読み込み：<div class="kp-progress-io"></div> に UI を出す（ファイルに保存・ファイルから読み込む・
 *   コピー用に表示・貼り付けて読み込む。最後に書き出した日も出す）
 * - ロードマップの集計：<div class="kp-roadmap-stats"></div> に、レベル・分野ごとの理解した数・解いた数と、
 *   問題の difficulty の色ごとの解いた数を出す（graph.json）
 * - 別のタブの変更は storage イベントで反映する。変更のたびに document に "kp:progress" イベントを出す（知識マップが使う）
 * - localStorage が使えない環境（保存の拒否など）でも壊れない。そのときはこのページを開いている間だけメモリに持つ
 * - instant navigation（Material の document$）のたびに、入れ替わったページへ取り付け直す。
 *   イベントは document で1回だけ受け、切り替え（理解した行を隠す・一覧の並べ方）はこのタブの間だけ覚えておく
 */
(function () {
  "use strict";

  var KEY = "kyopro-atlas:v1";
  var LEVELS = ["基礎", "水", "青", "黄", "発展"];
  var LV_CLASS = { 基礎: "kiso", 水: "mizu", 青: "ao", 黄: "ki", 発展: "hatten" };
  var SRC = document.currentScript ? document.currentScript.src : "";
  var GRAPH_URL = SRC ? new URL("../data/graph.json", SRC).href : null;
  var SITE_ROOT = SRC ? new URL("../../", SRC).href : null; // graph.json の url はサイトのルートからの相対
  var PROBLEM_URL = /^https:\/\/atcoder\.jp\/contests\/[^/]+\/tasks\/([A-Za-z0-9_]+)\/?$/;
  var PAGE_ID = /^[a-z0-9][a-z0-9-]*$/;
  var PROBLEM_ID = /^[A-Za-z0-9_]+$/;
  // 地方時の ISO 8601（日付だけでもよい）。勉強したいの入れた時刻と exportedAt に使う
  var TIME = /^\d{4}-\d{2}-\d{2}(?:T\d{2}:\d{2}(?::\d{2}(?:\.\d+)?)?(?:Z|[+-]\d{2}:\d{2})?)?$/;

  // ---------------------------------------------------------------- 保存

  var memory = null; // localStorage が使えないとき・書けなかったときの記録
  var usable = null; // localStorage に書けたか（null は未確認）

  function storage() {
    try {
      return window.localStorage || null;
    } catch (e) {
      return null; // 保存を拒否する設定では、localStorage を参照しただけで例外になる
    }
  }

  // 書けるかどうかを最初に1回だけ確かめる（書き出し・読み込みの欄に注意を出すため）
  (function probe() {
    var s = storage();
    if (!s) { usable = false; return; }
    try {
      s.setItem(KEY + ":probe", "1");
      s.removeItem(KEY + ":probe");
      usable = true;
    } catch (e) {
      usable = false;
    }
  })();

  function dict() { return Object.create(null); }

  function empty() { return { solved: dict(), understood: dict(), wishlist: dict(), updatedAt: null, exportedAt: null }; }

  function isObject(v) { return !!v && typeof v === "object" && !Array.isArray(v); }

  // 形の崩れた値を捨て、決まった形だけを残す（古い形の記録は、ない項目を空にして読む）
  function normalize(raw) {
    var out = empty();
    if (!isObject(raw)) return out;
    if (isObject(raw.solved)) {
      Object.keys(raw.solved).forEach(function (id) {
        if (raw.solved[id] === true && PROBLEM_ID.test(id) && id !== "__proto__") out.solved[id] = true;
      });
    }
    if (isObject(raw.understood)) {
      Object.keys(raw.understood).forEach(function (pid) {
        var lv = raw.understood[pid];
        if (!PAGE_ID.test(pid) || !isObject(lv)) return;
        var o = dict();
        LEVELS.forEach(function (l) { if (lv[l] === true) o[l] = true; });
        if (Object.keys(o).length) out.understood[pid] = o;
      });
    }
    if (isObject(raw.wishlist)) {
      Object.keys(raw.wishlist).forEach(function (pid) {
        var v = raw.wishlist[pid];
        if (!PAGE_ID.test(pid)) return;
        if (typeof v === "string" && TIME.test(v)) out.wishlist[pid] = v;
        else if (v === true) out.wishlist[pid] = true; // 入れた日の分からない記録（手で書いたものなど）
      });
    }
    if (typeof raw.updatedAt === "string") out.updatedAt = raw.updatedAt;
    if (typeof raw.exportedAt === "string" && TIME.test(raw.exportedAt)) out.exportedAt = raw.exportedAt;
    return out;
  }

  function load() {
    if (usable === false && memory) return normalize(memory); // 書けなくなってからはメモリの記録が新しい
    var s = storage();
    if (s) {
      var text = null;
      try {
        text = s.getItem(KEY);
        return normalize(text ? JSON.parse(text) : null);
      } catch (e) {
        // 壊れた JSON は、上書きする前に別のキーへ退避しておく
        if (text) { try { s.setItem(KEY + ":broken", text); } catch (e2) { /* 何もしない */ } }
        return empty();
      }
    }
    return memory ? normalize(memory) : empty();
  }

  function pad(n) { return String(Math.floor(Math.abs(n))).padStart(2, "0"); }

  // 地方時の ISO 8601（例：2026-10-21T12:00:00+09:00）
  function localISO(d) {
    d = d || new Date();
    var off = -d.getTimezoneOffset();
    return d.getFullYear() + "-" + pad(d.getMonth() + 1) + "-" + pad(d.getDate()) +
      "T" + pad(d.getHours()) + ":" + pad(d.getMinutes()) + ":" + pad(d.getSeconds()) +
      (off >= 0 ? "+" : "-") + pad(off / 60) + ":" + pad(off % 60);
  }

  // そのまま書く（updatedAt を変えない。書き出した時刻を残すときに使う）
  function store(state) {
    memory = state;
    var s = storage();
    if (!s) { usable = false; return false; }
    try {
      s.setItem(KEY, JSON.stringify(state));
      usable = true;
      return true;
    } catch (e) {
      usable = false; // 容量の超過・保存の拒否。以後はメモリの記録を使う
      return false;
    }
  }

  // 記録を変えたときに書く（updatedAt を今にする）
  function save(state) {
    state.updatedAt = localISO();
    return store(state);
  }

  function isSolved(st, id) { return st.solved[id] === true; }

  function isUnderstood(st, pid, lv) {
    var o = st.understood[pid];
    return !!(o && o[lv] === true);
  }

  function isWished(st, pid) { return !!st.wishlist[pid]; }

  function counts(st) {
    var u = 0;
    Object.keys(st.understood).forEach(function (pid) { u += Object.keys(st.understood[pid]).length; });
    return { solved: Object.keys(st.solved).length, understood: u, wishlist: Object.keys(st.wishlist).length };
  }

  function countText(c) {
    return "解いた " + c.solved + " 問・理解した " + c.understood + " 件・勉強したい " + c.wishlist + " ページ";
  }

  function update(fn) {
    var st = load();
    fn(st);
    save(st);
    changed(st);
  }

  function setSolved(id, on) {
    update(function (st) {
      if (on) st.solved[id] = true;
      else delete st.solved[id];
    });
  }

  function setUnderstood(pid, lv, on) {
    update(function (st) {
      var o = st.understood[pid] || (st.understood[pid] = dict());
      if (on) o[lv] = true;
      else delete o[lv];
      if (!Object.keys(o).length) delete st.understood[pid];
    });
  }

  // 勉強したいリストに入れる・外す。when は入れた時刻（元に戻すときに前の時刻を渡す）
  function setWished(pid, on, when) {
    if (!PAGE_ID.test(pid)) return;
    update(function (st) {
      if (on) { if (!st.wishlist[pid]) st.wishlist[pid] = when || localISO(); }
      else delete st.wishlist[pid];
    });
  }

  // 書き出した時刻を残す（記録の中身は変えないので updatedAt は変えない）
  function markExported(at) {
    var st = load();
    if (st.exportedAt === at) return true;
    st.exportedAt = at;
    var ok = store(st);
    changed(st);
    return ok;
  }

  // 2 つの時刻の早い方（日付の分からない true より、日付のある方を残す）
  function earlier(x, y) {
    if (!x) return y;
    if (!y) return x;
    if (typeof x !== "string") return typeof y === "string" ? y : x;
    if (typeof y !== "string") return x;
    var tx = Date.parse(x), ty = Date.parse(y);
    if (isNaN(tx) || isNaN(ty)) return x <= y ? x : y;
    return ty < tx ? y : x;
  }

  // 合わせる：解いた・理解した・勉強したいのどれかが true（ある）なら true（ある）。勉強したいの入れた時刻は早い方。
  // updatedAt と exportedAt は a（今の記録）のものを残す
  function merge(a, b) {
    var out = normalize(a);
    var nb = normalize(b);
    Object.keys(nb.solved).forEach(function (id) { out.solved[id] = true; });
    Object.keys(nb.understood).forEach(function (pid) {
      var o = out.understood[pid] || (out.understood[pid] = dict());
      Object.keys(nb.understood[pid]).forEach(function (l) { o[l] = true; });
    });
    Object.keys(nb.wishlist).forEach(function (pid) { out.wishlist[pid] = earlier(out.wishlist[pid], nb.wishlist[pid]); });
    return out;
  }

  function changed(st) {
    refresh(document, st);
    document.dispatchEvent(new CustomEvent("kp:progress", { detail: { state: st } }));
  }

  // ---------------------------------------------------------------- 小さな部品

  function el(tag, attrs, text) {
    var e = document.createElement(tag);
    if (attrs) Object.keys(attrs).forEach(function (k) { e.setAttribute(k, attrs[k]); });
    if (text != null) e.textContent = text;
    return e;
  }

  function formatDate(iso) {
    if (!iso) return "なし";
    var m = /^(\d{4}-\d{2}-\d{2})T(\d{2}:\d{2})/.exec(iso);
    return m ? m[1] + " " + m[2] : iso;
  }

  function formatDay(iso) {
    var m = typeof iso === "string" ? /^(\d{4}-\d{2}-\d{2})/.exec(iso) : null;
    return m ? m[1] : "—";
  }

  // 今日から何日前か（このブラウザの地方時の日付で数える）
  function daysAgo(iso) {
    var t = Date.parse(iso);
    if (isNaN(t)) return null;
    var d = new Date(t), now = new Date();
    var a = Date.UTC(d.getFullYear(), d.getMonth(), d.getDate());
    var b = Date.UTC(now.getFullYear(), now.getMonth(), now.getDate());
    return Math.round((b - a) / 86400000);
  }

  function agoText(iso) {
    var n = daysAgo(iso);
    if (n === null) return "";
    if (n <= 0) return "今日";
    if (n === 1) return "昨日";
    return n + " 日前";
  }

  // ---------------------------------------------------------------- 問題の行（解いた）

  // difficulty の色の帯（AtCoder Problems と同じ区切り）。[上限（未満）, class, 色の名前, 範囲]
  var DIFF_BANDS = [
    [400, "gray", "灰", "〜399"], [800, "brown", "茶", "400〜799"], [1200, "green", "緑", "800〜1199"],
    [1600, "cyan", "水", "1200〜1599"], [2000, "blue", "青", "1600〜1999"], [2400, "yellow", "黄", "2000〜2399"],
    [2800, "orange", "橙", "2400〜2799"], [Infinity, "red", "赤", "2800〜"],
  ];
  var DIFF_TEXT = /（(diff (\d+))）/;

  function diffBand(d) {
    if (typeof d !== "number" || !isFinite(d)) return -1;
    var k = 0;
    while (d >= DIFF_BANDS[k][0]) k++;
    return k;
  }

  // 行の「（diff NNNN）」の「diff NNNN」を色の帯の class を付けた span で包む。丸は帯の中の位置だけ塗る
  // （AtCoder Problems の表し方）。「diff —」（difficulty なし）は色を付けない
  function markDifficulty(body) {
    var walker = document.createTreeWalker(body, NodeFilter.SHOW_TEXT);
    var node;
    while ((node = walker.nextNode())) {
      var m = DIFF_TEXT.exec(node.nodeValue);
      if (!m) continue;
      var d = Number(m[2]);
      var k = diffBand(d);
      // 帯の幅は 400。3200 以上は全部塗る（AtCoder Problems は金属の色にするが、ここでは赤のまま）
      var fill = d >= 3200 ? 100 : Math.round(((d % 400) / 400) * 100);
      var target = node.splitText(m.index + 1); // 「（」の次から
      target.splitText(m[1].length); // 「diff NNNN」だけを切り出す
      var span = document.createElement("span");
      span.className = "kp-diff kp-diff--" + DIFF_BANDS[k][1];
      span.title = "difficulty " + d + "（" + DIFF_BANDS[k][2] + "）";
      span.style.setProperty("--kp-diff-fill", fill + "%");
      target.parentNode.replaceChild(span, target);
      span.appendChild(target);
      return;
    }
  }

  // .kp-problems の各行に「解いた」のチェック欄を付け、difficulty に色を付ける（何度呼んでもよい）
  function mountProblems(root) {
    root.querySelectorAll(".kp-problems li").forEach(function (li) {
      if (li.classList.contains("kp-problem")) return;
      var a = li.querySelector('a[href^="https://atcoder.jp/contests/"]');
      var m = a && PROBLEM_URL.exec(a.getAttribute("href"));
      if (!m) return;
      var body = document.createElement("span");
      body.className = "kp-problem__body";
      while (li.firstChild) body.appendChild(li.firstChild);
      markDifficulty(body);
      var label = document.createElement("label");
      label.className = "kp-solved";
      var cb = document.createElement("input");
      cb.type = "checkbox";
      cb.dataset.kpSolved = m[1];
      cb.setAttribute("aria-label", "解いた：" + a.textContent.trim());
      cb.title = "解いた";
      label.appendChild(cb);
      li.appendChild(label);
      li.appendChild(body);
      li.classList.add("kp-problem");
    });
  }

  // チェック欄と、記録を映す欄を記録に合わせる
  function refresh(root, st) {
    st = st || load();
    root.querySelectorAll("input[data-kp-solved]").forEach(function (cb) {
      cb.checked = isSolved(st, cb.dataset.kpSolved);
      var li = cb.closest(".kp-problem");
      if (li) li.classList.toggle("kp-is-solved", cb.checked);
    });
    root.querySelectorAll("input[data-kp-understood][data-kp-level]").forEach(function (cb) {
      cb.checked = isUnderstood(st, cb.dataset.kpUnderstood, cb.dataset.kpLevel);
      var label = cb.closest(".kp-check");
      if (label) label.classList.toggle("kp-is-checked", cb.checked);
      var tr = cb.closest("tr[data-kp-row]");
      if (tr) tr.classList.toggle("kp-is-understood", cb.checked);
    });
    // title は変えない（content.tooltips の Material が title を預かり、表示の後に元の値へ戻すため）
    root.querySelectorAll("input[data-kp-wish]").forEach(function (cb) {
      cb.checked = isWished(st, cb.dataset.kpWish);
      var label = cb.closest(".kp-wish__toggle");
      if (label) label.classList.toggle("kp-is-checked", cb.checked);
    });
    updateOrderCounts(root);
    root.querySelectorAll(".kp-progress-io[data-kp-mounted]").forEach(function (box) { ioSummary(box, st); });
    root.querySelectorAll(".kp-roadmap-stats[data-kp-mounted]").forEach(function (box) { renderStats(box, st); });
    root.querySelectorAll(".kp-wishlist[data-kp-mounted]").forEach(function (box) { renderWishlist(box, st); });
  }

  // チェック欄の変更は document で1回だけ受ける（instant navigation で入れ替わった要素にも効く）
  document.addEventListener("change", function (e) {
    var t = e.target;
    if (!(t instanceof HTMLInputElement) || t.type !== "checkbox") return;
    if (t.dataset.kpSolved) setSolved(t.dataset.kpSolved, t.checked);
    else if (t.dataset.kpUnderstood && t.dataset.kpLevel) setUnderstood(t.dataset.kpUnderstood, t.dataset.kpLevel, t.checked);
    else if (t.dataset.kpWish) setWished(t.dataset.kpWish, t.checked);
  });

  // 別のタブでの変更（e.key が null なのは clear() のとき）
  window.addEventListener("storage", function (e) {
    if (e.key === KEY || e.key === null) changed(load());
  });

  // ---------------------------------------------------------------- 書き出し・読み込み

  // 書き出す記録：今の記録に、書き出す時刻を入れたもの（まだ保存はしない）
  function snapshot() {
    var st = load();
    st.exportedAt = localISO();
    return st;
  }

  function exportText(st) { return JSON.stringify(st, null, 1); }

  // 記録の中身（時刻を除く）。merge は今の記録の鍵の順を保つので、増えたものがなければ同じ文字になる
  function contentText(st) { return JSON.stringify([st.solved, st.understood, st.wishlist]); }

  function parseRecord(text) {
    var raw;
    try {
      raw = JSON.parse(text);
    } catch (e) {
      return { error: "JSON として読めない" };
    }
    if (!isObject(raw) || !("solved" in raw || "understood" in raw || "wishlist" in raw)) {
      return { error: "この教材の記録の形ではない（solved・understood・wishlist のどれもない）" };
    }
    return { state: normalize(raw) };
  }

  // 文字をファイルとして保存させる。a[download] は文書の中に置いてから押す（Firefox）。
  // blob: の URL は sitemap にないので、Material の instant navigation は横取りしない
  function download(host, name, text) {
    try {
      var url = URL.createObjectURL(new Blob([text], { type: "application/json" }));
      var a = el("a", { href: url, download: name });
      a.hidden = true;
      host.appendChild(a);
      a.click();
      a.remove();
      setTimeout(function () { URL.revokeObjectURL(url); }, 10000);
      return true;
    } catch (e) {
      return false;
    }
  }

  function backupText(st, c) {
    var some = c.solved || c.understood || c.wishlist;
    if (!st.exportedAt) {
      return some ? "まだ書き出していない。ブラウザのデータが消えたときに戻せるよう、ファイルに保存しておく。" : "まだ書き出していない。";
    }
    var s = "最後に書き出した日：" + formatDay(st.exportedAt);
    var ago = agoText(st.exportedAt);
    if (ago) s += "（" + ago + "）";
    var tu = Date.parse(st.updatedAt || ""), te = Date.parse(st.exportedAt);
    if (!isNaN(tu) && !isNaN(te) && tu > te) s += "。その後に記録が変わっている";
    return s + "。";
  }

  function ioSummary(box, st) {
    var c = counts(st);
    box.querySelector(".kp-io__summary").textContent =
      "この端末の記録：" + countText(c) + "（最終更新 " + formatDate(st.updatedAt) + "）";
    box.querySelector(".kp-io__backup").textContent = backupText(st, c);
    box.querySelector(".kp-io__warn").hidden = usable !== false;
  }

  function mountIO(box) {
    if (box.dataset.kpMounted) return;
    box.dataset.kpMounted = "1";
    box.textContent = "";
    var wrap = el("div", { class: "kp-io" });
    var summary = el("p", { class: "kp-io__summary" });
    var backup = el("p", { class: "kp-io__backup" });
    var warn = el("p", { class: "kp-io__warn" },
      "このブラウザでは記録を保存できない（保存を拒否する設定など）。記録はこのページを開いている間だけ残る。");
    warn.hidden = true;
    var note = el("p", { class: "kp-stats__note" },
      "記録はこのブラウザの中だけにあり、端末の間では同期しない。ブラウザのデータを消すと記録も消えるので、ときどきファイルに保存しておく。");
    var buttons = el("div", { class: "kp-io__buttons" });
    var bSave = el("button", { type: "button", class: "md-button md-button--primary" }, "ファイルに保存");
    var bOpen = el("button", { type: "button", class: "md-button" }, "ファイルから読み込む");
    var bExport = el("button", { type: "button", class: "md-button", "aria-expanded": "false" }, "コピー用に表示");
    var bImport = el("button", { type: "button", class: "md-button", "aria-expanded": "false" }, "貼り付けて読み込む");
    buttons.append(bSave, bOpen, bExport, bImport);
    var file = el("input", { type: "file", accept: ".json,application/json,.txt,text/plain", class: "kp-io__file", tabindex: "-1", "aria-hidden": "true" });
    file.hidden = true;

    var pExport = el("div", { class: "kp-io__panel" });
    pExport.hidden = true;
    var lExport = el("label", null, "記録の JSON（「コピーする」で全体を写し、メモなどに保存する）");
    var tExport = el("textarea", { rows: "6", readonly: "", spellcheck: "false" });
    lExport.appendChild(tExport);
    var bCopy = el("button", { type: "button", class: "md-button md-button--primary" }, "コピーする");
    pExport.append(lExport, bCopy);

    var pImport = el("div", { class: "kp-io__panel" });
    pImport.hidden = true;
    var lImport = el("label", null, "書き出した JSON を貼り付ける（「ファイルから読み込む」で選んだファイルの中身もここに入る）");
    var tImport = el("textarea", { rows: "6", spellcheck: "false" });
    lImport.appendChild(tImport);
    var bMerge = el("button", { type: "button", class: "md-button md-button--primary" }, "今の記録と合わせる");
    var bReplace = el("button", { type: "button", class: "md-button" }, "今の記録を置き換える");
    var importButtons = el("div", { class: "kp-io__buttons" });
    importButtons.append(bMerge, bReplace);
    pImport.append(lImport, importButtons);

    var status = el("p", { class: "kp-io__status", role: "status", "aria-live": "polite" });
    wrap.append(summary, backup, warn, note, buttons, file, pExport, pImport, status);
    box.appendChild(wrap);

    var shownAt = null; // 「コピー用に表示」で出した JSON の exportedAt

    function say(msg, isError) {
      status.textContent = msg;
      status.classList.toggle("kp-is-error", !!isError);
    }
    function showOnly(panel) {
      pExport.hidden = panel !== pExport;
      bExport.setAttribute("aria-expanded", String(panel === pExport));
      pImport.hidden = panel !== pImport;
      bImport.setAttribute("aria-expanded", String(panel === pImport));
    }
    function showExport() {
      var st = snapshot();
      shownAt = st.exportedAt;
      tExport.value = exportText(st);
      return tExport.value;
    }

    bSave.addEventListener("click", function () {
      showOnly(null);
      var st = snapshot();
      var name = "kyopro-atlas-progress-" + formatDay(st.exportedAt) + ".json";
      if (download(box, name, exportText(st) + "\n")) {
        var ok = markExported(st.exportedAt);
        say("「" + name + "」に書き出した。保存先はブラウザのダウンロードの設定による。" + (ok ? "" : "（書き出した日はこのブラウザに保存できない）"));
      } else {
        say("ファイルに保存できなかった。「コピー用に表示」で写して保存する。", true);
      }
    });

    bOpen.addEventListener("click", function () {
      say("");
      file.value = ""; // 同じファイルをもう一度選んでも change が起きるように
      file.click();
    });

    file.addEventListener("change", function () {
      var f = file.files && file.files[0];
      if (!f) return;
      if (f.size > 2 * 1024 * 1024) {
        say("「" + f.name + "」は大きすぎる（2 MB まで）。この教材で書き出したファイルを選ぶ。", true);
        return;
      }
      var reader = new FileReader();
      reader.onload = function () {
        showOnly(pImport);
        tImport.value = String(reader.result || "");
        resetConfirm();
        var r = parseRecord(tImport.value);
        if (r.error) {
          say("「" + f.name + "」を読めない（" + r.error + "）。この教材で書き出したファイルを選ぶ。", true);
          return;
        }
        say("「" + f.name + "」を読んだ：" + countText(counts(r.state)) +
          (r.state.exportedAt ? "（" + formatDay(r.state.exportedAt) + " に書き出したもの）" : "") +
          "。下のボタンで、今の記録と合わせるか置き換えるかを選ぶ。");
        bMerge.focus();
      };
      reader.onerror = function () { say("「" + f.name + "」を読めなかった。", true); };
      reader.readAsText(f);
    });

    bExport.addEventListener("click", function () {
      var open = pExport.hidden;
      showOnly(open ? pExport : null);
      say("");
      if (open) {
        showExport();
        tExport.focus();
        tExport.select();
      }
    });
    bImport.addEventListener("click", function () {
      var open = pImport.hidden;
      showOnly(open ? pImport : null);
      say("");
      if (open) tImport.focus();
    });

    // 手でコピーしたときも、書き出したことにする
    tExport.addEventListener("copy", function () { if (shownAt) markExported(shownAt); });

    bCopy.addEventListener("click", function () {
      var text = showExport(); // 最新の記録で作り直してから写す
      var at = shownAt;
      function done() {
        markExported(at);
        say("コピーした。メモなどに貼り付けて保存する。");
      }
      function fallback() {
        tExport.focus();
        tExport.select();
        var ok = false;
        try { ok = document.execCommand("copy"); } catch (e) { ok = false; }
        if (ok) done();
        else say("コピーできなかった。選んだ文字を手でコピーする。", true);
      }
      if (navigator.clipboard && window.isSecureContext) {
        navigator.clipboard.writeText(text).then(done, fallback);
      } else {
        fallback();
      }
    });

    function parseInput() {
      var r = parseRecord(tImport.value);
      if (r.error) {
        say(r.error + "。書き出した文字を全部そのまま貼り付けるか、書き出したファイルを選ぶ。", true);
        return null;
      }
      return r.state;
    }

    var confirmUntil = 0;
    function resetConfirm() {
      confirmUntil = 0;
      bReplace.textContent = "今の記録を置き換える";
    }
    tImport.addEventListener("input", resetConfirm);

    bMerge.addEventListener("click", function () {
      resetConfirm();
      var inc = parseInput();
      if (!inc) return;
      var cur = load();
      var st = merge(cur, inc);
      // 増えたものがなければ、記録も updatedAt も変えない（書き出した後に変わったように見せない）
      if (contentText(st) === contentText(cur)) {
        say("合わせた。今の記録にないものはなかった（" + countText(counts(cur)) + "のまま）。");
        return;
      }
      var ok = save(st);
      changed(st);
      say("合わせた。" + countText(counts(st)) + "になった。" + (ok ? "" : "（このブラウザには保存できない）"), !ok);
    });

    bReplace.addEventListener("click", function () {
      var inc = parseInput();
      if (!inc) { resetConfirm(); return; }
      var now = counts(load());
      if ((now.solved || now.understood || now.wishlist) && Date.now() > confirmUntil) {
        confirmUntil = Date.now() + 10000;
        bReplace.textContent = "もう一度押すと置き換える";
        say("置き換えると、今の記録（" + countText(now) + "）は消える。よければ 10 秒以内にもう一度押す。");
        return;
      }
      resetConfirm();
      // 中身は読み込んだ記録そのものなので、updatedAt と exportedAt も読み込んだ記録のものを使う
      // （その記録はファイルなどに残っている。updatedAt のない記録は今にする）
      if (!inc.updatedAt) inc.updatedAt = localISO();
      var ok = store(inc);
      changed(inc);
      say("置き換えた。" + countText(counts(inc)) + "になった。" + (ok ? "" : "（このブラウザには保存できない）"), !ok);
    });

    ioSummary(box, load());
  }

  // ---------------------------------------------------------------- ロードマップの集計

  var graphPromise = null;

  function loadGraph() {
    if (!GRAPH_URL) return Promise.reject(new Error("graph.json の場所が分からない"));
    if (!graphPromise) {
      graphPromise = fetch(GRAPH_URL).then(function (r) {
        if (!r.ok) throw new Error("graph.json を読めない（" + r.status + "）");
        return r.json();
      });
      graphPromise.catch(function () { graphPromise = null; }); // 失敗したら次の機会に読み直す
    }
    return graphPromise;
  }

  // ページの「理解した」の単位：ページの level と、sections にある上位の level
  function itemLevels(p) {
    var r = LEVELS.indexOf(p.level);
    if (r < 0) return [];
    var out = [p.level];
    (p.sections || []).forEach(function (s) {
      var k = LEVELS.indexOf(s.level);
      if (k > r && out.indexOf(s.level) < 0) out.push(s.level);
    });
    return out;
  }

  function computeStats(g, st) {
    function row(label) { return { label: label, items: 0, understood: 0, problems: new Set() }; }
    var byLevel = LEVELS.map(function (l) { return row(l); });
    var fields = (g.fields || []).slice().sort(function (a, b) { return a.order - b.order; });
    var byField = new Map(fields.map(function (f) { return [f.id, row(f.title)]; }));
    var total = row("合計");
    (g.pages || []).forEach(function (p) {
      var f = byField.get(p.field);
      itemLevels(p).forEach(function (l) {
        var u = isUnderstood(st, p.id, l) ? 1 : 0;
        var L = byLevel[LEVELS.indexOf(l)];
        [L, f, total].forEach(function (r) { if (r) { r.items++; r.understood += u; } });
      });
      (p.problems || []).forEach(function (pr) {
        var L = byLevel[LEVELS.indexOf(p.level)];
        [L, f, total].forEach(function (r) { if (r) r.problems.add(pr.id); });
      });
    });
    function finish(r) {
      var solved = 0;
      r.problems.forEach(function (id) { if (isSolved(st, id)) solved++; });
      return { label: r.label, items: r.items, understood: r.understood, problems: r.problems.size, solved: solved };
    }
    // 問題の difficulty の色ごと（ページのレベルではなく、問題そのものの difficulty で分ける。#74）
    var bands = DIFF_BANDS.map(function (b) { return { label: b[2], range: b[3], band: b[1], problems: 0, solved: 0 }; });
    var noDiff = { label: "difficulty なし", range: "", band: null, problems: 0, solved: 0 };
    var diffTotal = { label: "合計", range: "", band: null, problems: 0, solved: 0 };
    var probs = g.problems || {};
    Object.keys(probs).forEach(function (id) {
      var k = diffBand(probs[id] && probs[id].difficulty);
      var r = k < 0 ? noDiff : bands[k];
      var s = isSolved(st, id) ? 1 : 0;
      r.problems++;
      r.solved += s;
      diffTotal.problems++;
      diffTotal.solved += s;
    });
    return {
      levels: byLevel.map(finish),
      fields: Array.from(byField.values()).map(finish).filter(function (r) { return r.items || r.problems; }),
      total: finish(total),
      diffs: bands.concat(noDiff.problems ? [noDiff] : []),
      diffTotal: diffTotal,
    };
  }

  function cell(num, den) {
    var td = el("td", { class: "kp-num" });
    if (!den) { td.textContent = "—"; return td; }
    td.appendChild(document.createTextNode(num + " / " + den));
    var bar = el("span", { class: "kp-bar", "aria-hidden": "true" });
    var fill = el("span");
    fill.style.width = Math.round((100 * num) / den) + "%";
    bar.appendChild(fill);
    td.appendChild(bar);
    return td;
  }

  var COL_UNDERSTOOD = ["理解した", "understood", "items"];
  var COL_SOLVED = ["解いた問題", "solved", "problems"];

  // 集計の表。cols は [見出し, 分子のキー, 分母のキー] の並び。label(r) は行の見出しのセルの中身（null なら文字だけ）
  function statTable(caption, head, cols, rows, label) {
    var scroll = el("div", { class: "md-typeset__scrollwrap" });
    var wrapper = el("div", { class: "md-typeset__table" });
    var t = el("table");
    t.appendChild(el("caption", null, caption));
    var thead = el("thead");
    var tr = el("tr");
    tr.appendChild(el("th", null, head));
    cols.forEach(function (c) { tr.appendChild(el("th", { class: "kp-num" }, c[0])); });
    thead.appendChild(tr);
    var tbody = el("tbody");
    rows.forEach(function (r) {
      var row = el("tr");
      var td = el("td");
      var node = label ? label(r) : null;
      if (node) td.appendChild(node);
      else td.textContent = r.label;
      row.appendChild(td);
      cols.forEach(function (c) { row.appendChild(cell(r[c[1]], r[c[2]])); });
      tbody.appendChild(row);
    });
    t.append(thead, tbody);
    wrapper.appendChild(t);
    scroll.appendChild(wrapper);
    return scroll;
  }

  function levelLabel(r) {
    return LV_CLASS[r.label] ? el("span", { class: "kp-mini kp-lv-" + LV_CLASS[r.label] }, r.label) : null;
  }

  function diffLabel(r) {
    if (!r.band) return null;
    var f = document.createDocumentFragment();
    var span = el("span", { class: "kp-diff kp-diff--" + r.band }, r.label);
    span.style.setProperty("--kp-diff-fill", "100%");
    f.append(span, document.createTextNode(" " + r.range));
    return f;
  }

  var statsData = new WeakMap();

  function renderStats(box, st) {
    var g = statsData.get(box);
    if (!g) return;
    var s = computeStats(g, st || load());
    box.textContent = "";
    var wrap = el("div", { class: "kp-stats" });
    wrap.appendChild(statTable("レベル別", "レベル", [COL_UNDERSTOOD, COL_SOLVED], s.levels.concat([s.total]), levelLabel));
    wrap.appendChild(statTable("分野別", "分野", [COL_UNDERSTOOD, COL_SOLVED], s.fields, null));
    if (s.diffTotal.problems) {
      wrap.appendChild(statTable("問題の difficulty の色別", "difficulty", [COL_SOLVED], s.diffs.concat([s.diffTotal]), diffLabel));
    }
    wrap.appendChild(el("p", { class: "kp-stats__note" },
      "「理解した」は、ページのレベルと、ページの中の上の帯の節のレベルを 1 件ずつ数える。解いた問題は、各ページの例題・練習・力試しから数える。" +
      "レベル別・分野別では問題を載せたページのレベル・分野で数え（レベルや分野の違う 2 つのページに載る問題は、両方に入る）、" +
      "色別では問題の difficulty（AtCoder Problems の推定値。載せた時点の値）で数える。"));
    box.appendChild(wrap);
  }

  function mountStats(box) {
    if (box.dataset.kpMounted) return;
    box.dataset.kpMounted = "1";
    box.textContent = "集計を読み込んでいる…";
    loadGraph().then(function (g) {
      statsData.set(box, g);
      renderStats(box);
    }, function (e) {
      box.dataset.kpMounted = "";
      box.textContent = "集計を読み込めなかった（" + e.message + "）。";
    });
  }

  // ---------------------------------------------------------------- ロードマップの色ごとの列（#74）

  // 生成された列の見出し h3#reading-order-<色> の色（tools/gen_site.py の LEVEL_SLUGS）
  var ORDER_LEVEL = { basic: "基礎", cyan: "水", blue: "青", yellow: "黄", advanced: "発展" };
  var ORDER_PREFIX = "reading-order-";
  var orderHide = false; // 理解した行を隠すか（instant navigation で行き来しても、このタブの間は覚えておく）
  var orderCount = new WeakMap(); // 表 → 理解した行の数を出す段落

  // 見出しの後の、次の見出しまでにある最初の表（Material が表を包む前でも後でも見つける）
  function orderTables(root) {
    var out = [];
    root.querySelectorAll('h3[id^="' + ORDER_PREFIX + '"]').forEach(function (h) {
      var lv = ORDER_LEVEL[h.id.slice(ORDER_PREFIX.length)];
      if (!lv) return;
      for (var n = h.nextElementSibling; n && !/^H[1-6]$/.test(n.tagName); n = n.nextElementSibling) {
        var t = n.tagName === "TABLE" ? n : n.querySelector("table");
        if (t) { out.push({ heading: h, table: t, level: lv }); break; }
      }
    });
    return out;
  }

  // ページへのリンクからページの id を取る（URL は <field>/<id>/。interfaces.md §1）
  function pageIdOf(a) {
    var parts = a.pathname.split("/").filter(Boolean);
    if (parts.length && parts[parts.length - 1] === "index.html") parts.pop();
    var id = parts.length ? parts[parts.length - 1] : "";
    return PAGE_ID.test(id) ? id : null;
  }

  // 列の各行の先頭（# の欄）に「理解した」のチェック欄を付ける。行のページの id と、列の色の組で記録と結ぶ。
  // 表には class を付けない（Material は class のない表だけを整える）。印は data-kp-order・data-kp-row で付ける
  function mountOrder(root) {
    orderTables(root).forEach(function (o) {
      var t = o.table;
      if (t.hasAttribute("data-kp-order")) return;
      t.setAttribute("data-kp-order", o.level);
      t.querySelectorAll("tbody tr").forEach(function (tr) {
        var cells = tr.cells;
        if (cells.length < 2) return;
        var a = cells[1].querySelector("a[href]");
        var id = a && pageIdOf(a);
        if (!id) return;
        var isSection = !!a.hash;
        var label = el("label", { class: "kp-order__check kp-lv-" + LV_CLASS[o.level],
          title: "理解した（" + o.level + (isSection ? "の節" : "") + "）" });
        var cb = el("input", { type: "checkbox" });
        cb.dataset.kpUnderstood = id;
        cb.dataset.kpLevel = o.level;
        cb.setAttribute("aria-label", "理解した：" + cells[1].textContent.trim() + "（" + o.level + (isSection ? "の節" : "") + "）");
        label.appendChild(cb);
        while (cells[0].firstChild) label.appendChild(cells[0].firstChild); // 番号もチェック欄の文字にする
        cells[0].appendChild(label);
        tr.setAttribute("data-kp-row", "");
      });
      var count = el("p", { class: "kp-order__count" });
      o.heading.insertAdjacentElement("afterend", count);
      orderCount.set(t, count);
    });
    root.querySelectorAll(".kp-order-tools").forEach(function (box) {
      if (box.dataset.kpMounted) return;
      box.dataset.kpMounted = "1";
      box.textContent = "";
      var label = el("label", { class: "kp-order-tools__toggle" });
      var cb = el("input", { type: "checkbox" });
      label.append(cb, document.createTextNode("理解した行を隠す（まだのものだけを出す）"));
      var note = el("p", { class: "kp-stats__note" },
        "同じページの同じ帯の節が 2 行以上ある列では、それらの行はまとめて 1 つの記録になる（1 行に付けると、ほかの行にも付く）。");
      box.append(label, note);
      cb.addEventListener("change", function () {
        orderHide = cb.checked;
        applyOrderHide(document);
      });
    });
    applyOrderHide(root);
  }

  function applyOrderHide(root) {
    root.querySelectorAll("table[data-kp-order]").forEach(function (t) { t.toggleAttribute("data-kp-hide", orderHide); });
    root.querySelectorAll(".kp-order-tools input").forEach(function (cb) { cb.checked = orderHide; });
    updateOrderCounts(root);
  }

  function updateOrderCounts(root) {
    root.querySelectorAll("table[data-kp-order]").forEach(function (t) {
      var p = orderCount.get(t);
      if (!p) return;
      var rows = t.querySelectorAll("tr[data-kp-row]").length;
      var done = t.querySelectorAll("tr[data-kp-row].kp-is-understood").length;
      var s = "理解した行：" + done + " / " + rows;
      if (orderHide && done) s += done === rows ? "（すべて理解したので、行をすべて隠している）" : "（理解した " + done + " 行を隠している）";
      p.textContent = s;
    });
  }

  // ---------------------------------------------------------------- 勉強したいリスト（#1）

  var wishSort = "added-desc"; // 並べ方（このタブの間は覚えておく）
  var WISH_SORTS = [["added-desc", "入れた日の新しい順"], ["added-asc", "入れた日の古い順"], ["level", "レベルの順"], ["field", "分野の順"]];
  var wishData = new WeakMap(); // 一覧の箱 → graph.json（読めなかったときは failedGraph() の代わり）

  // graph.json を読めなかったときの代わり。題名・レベル・分野は出せないが、id・入れた日と外す操作は出す。
  // どのページが実在するかも分からないので、行に「見つからない」とは書かず、一覧の上に注記を残す（failed で見分ける）
  function failedGraph(reason) { return { pages: [], fields: [], failed: true, reason: reason || "" }; }

  function addedTime(v) {
    var t = typeof v === "string" ? Date.parse(v) : NaN;
    return isNaN(t) ? null : t;
  }

  function sortWishes(items, fieldOrder) {
    function byTitle(a, b) { return a.title < b.title ? -1 : a.title > b.title ? 1 : 0; }
    function byAdded(a, b, dir) {
      var ta = addedTime(a.at), tb = addedTime(b.at);
      if (ta === null || tb === null) return ta === null ? (tb === null ? 0 : 1) : -1; // 日付の分からないものは最後
      return dir * (ta - tb);
    }
    function byPlace(a, b) {
      var fa = a.page ? (fieldOrder.get(a.page.field) || 0) : Infinity, fb = b.page ? (fieldOrder.get(b.page.field) || 0) : Infinity;
      if (fa !== fb) return fa < fb ? -1 : 1;
      var oa = a.page ? a.page.order || 0 : 0, ob = b.page ? b.page.order || 0 : 0;
      return oa - ob;
    }
    function byLevel(a, b) {
      var la = a.page ? LEVELS.indexOf(a.page.level) : -1, lb = b.page ? LEVELS.indexOf(b.page.level) : -1;
      if (la < 0) la = LEVELS.length; // レベルのない案内のページと、見つからないページは最後
      if (lb < 0) lb = LEVELS.length;
      return la - lb;
    }
    items.sort(function (a, b) {
      var r = 0;
      if (wishSort === "added-asc") r = byAdded(a, b, 1);
      else if (wishSort === "level") r = byLevel(a, b) || byPlace(a, b);
      else if (wishSort === "field") r = byPlace(a, b);
      else r = byAdded(a, b, -1);
      return r || byTitle(a, b);
    });
    return items;
  }

  function renderWishlist(box, st) {
    var g = wishData.get(box);
    if (!g) return;
    st = st || load();
    var byId = new Map((g.pages || []).map(function (p) { return [p.id, p]; }));
    var fieldTitle = new Map((g.fields || []).map(function (f) { return [f.id, f.title]; }));
    var fieldOrder = new Map((g.fields || []).map(function (f) { return [f.id, f.order]; }));
    var items = Object.keys(st.wishlist).map(function (id) {
      var p = byId.get(id) || null;
      return { id: id, at: st.wishlist[id], page: p, title: p ? p.title : id };
    });
    sortWishes(items, fieldOrder);
    box.querySelector(".kp-wishlist__count").textContent = items.length + " ページ";
    box.querySelector(".kp-wishlist__sort").hidden = items.length < 2;
    box.querySelector(".kp-wishlist__bar").hidden = !items.length;
    // 読めなかった旨は、外す・元に戻すの知らせ（status）で上書きされないよう、別の段落に出し続ける
    var note = box.querySelector(".kp-wishlist__note");
    if (note) {
      var noteText = g.failed && items.length
        ? "ページの一覧を読み込めなかった" + (g.reason ? "（" + g.reason + "）" : "") +
          "。題名・レベル・分野の代わりに id を出す。ページを読み込み直すと出ることがある。"
        : "";
      if (note.textContent !== noteText) note.textContent = noteText;
      note.hidden = !noteText;
    }
    var body = box.querySelector(".kp-wishlist__body");
    body.textContent = "";
    if (!items.length) {
      body.appendChild(el("p", { class: "kp-wishlist__empty" },
        "まだ何も入れていない。各ページの上の「勉強したい」を押すと、ここに並ぶ。"));
      return;
    }
    var ul = el("ul", { class: "kp-wishlist__list" });
    items.forEach(function (it) {
      var p = it.page;
      var li = el("li", { class: "kp-wishlist__item" });
      var main = el("div", { class: "kp-wishlist__main" });
      var head = el("p", { class: "kp-wishlist__title" });
      if (p && LV_CLASS[p.level]) {
        head.append(el("span", { class: "kp-mini kp-lv-" + LV_CLASS[p.level], title: "レベル" }, p.level), document.createTextNode(" "));
      }
      if (p && SITE_ROOT) {
        var a = el("a", { href: new URL(p.url, SITE_ROOT).href }, p.title);
        if (p.summary) a.title = p.summary;
        head.appendChild(a);
      } else {
        head.appendChild(el("span", null, it.id));
      }
      var meta = el("p", { class: "kp-wishlist__meta" });
      var parts = [];
      if (p) parts.push(fieldTitle.get(p.field) || p.field);
      else if (!g.failed) parts.push("このページは見つからない（id が変わったか、なくなった）");
      parts.push("入れた日 " + formatDay(it.at));
      meta.textContent = parts.join("・");
      if (p && LV_CLASS[p.level] && isUnderstood(st, p.id, p.level)) {
        meta.append("・", el("span", { class: "kp-wishlist__done" }, "✓ 理解した"));
      }
      main.append(head, meta);
      var remove = el("button", { type: "button", class: "kp-wishlist__remove", "aria-label": "勉強したいリストから外す：" + it.title }, "外す");
      remove.dataset.kpUnwish = it.id;
      li.append(main, remove);
      ul.appendChild(li);
    });
    body.appendChild(ul);
  }

  function mountWishlist(box) {
    if (box.dataset.kpMounted) return;
    box.dataset.kpMounted = "1";
    box.textContent = "";
    var bar = el("div", { class: "kp-wishlist__bar" });
    var count = el("p", { class: "kp-wishlist__count" });
    var sortLabel = el("label", { class: "kp-wishlist__sort" }, "並べ方 ");
    var sel = el("select");
    WISH_SORTS.forEach(function (o) { sel.appendChild(el("option", { value: o[0] }, o[1])); });
    sel.value = wishSort;
    sortLabel.appendChild(sel);
    bar.append(count, sortLabel);
    var note = el("p", { class: "kp-io__warn kp-wishlist__note" }); // ページの一覧を読めなかったときの注記
    note.hidden = true;
    var status = el("p", { class: "kp-io__status kp-wishlist__status", role: "status", "aria-live": "polite" });
    var body = el("div", { class: "kp-wishlist__body" }, "リストを読み込んでいる…");
    box.append(bar, note, status, body);

    sel.addEventListener("change", function () {
      wishSort = sel.value;
      renderWishlist(box);
    });

    box.addEventListener("click", function (e) {
      var b = e.target instanceof Element ? e.target.closest("button[data-kp-unwish], button[data-kp-undo]") : null;
      if (!b) return;
      if (b.dataset.kpUnwish) {
        var id = b.dataset.kpUnwish;
        var at = load().wishlist[id];
        var title = (b.getAttribute("aria-label") || "").replace(/^勉強したいリストから外す：/, "") || id;
        setWished(id, false);
        status.textContent = "「" + title + "」を外した。";
        var undo = el("button", { type: "button", class: "kp-wishlist__undo" }, "元に戻す");
        undo.dataset.kpUndo = id;
        undo.dataset.kpAt = typeof at === "string" ? at : "";
        undo.dataset.kpTitle = title;
        status.appendChild(undo);
        undo.focus();
      } else {
        var uid = b.dataset.kpUndo;
        setWished(uid, true, b.dataset.kpAt || true);
        status.textContent = "「" + (b.dataset.kpTitle || uid) + "」を戻した。";
        var again = box.querySelector('button[data-kp-unwish="' + uid + '"]');
        if (again) again.focus();
      }
    });

    loadGraph().then(function (g) {
      // ページの一覧のない graph.json は、読めなかったときと同じに扱う（実在するページを「見つからない」と出さない）
      wishData.set(box, g && Array.isArray(g.pages) ? g : failedGraph("graph.json にページの一覧がない"));
      renderWishlist(box);
    }, function (e) {
      wishData.set(box, failedGraph(e && e.message));
      renderWishlist(box);
    });
  }

  // ---------------------------------------------------------------- 取り付け

  function mount(root) {
    mountProblems(root);
    mountOrder(root);
    root.querySelectorAll(".kp-progress-io").forEach(mountIO);
    root.querySelectorAll(".kp-roadmap-stats").forEach(mountStats);
    root.querySelectorAll(".kp-wishlist").forEach(mountWishlist);
    refresh(root);
  }

  window.KPProgress = {
    KEY: KEY,
    LEVELS: LEVELS,
    load: load,
    save: save,
    merge: merge,
    normalize: normalize,
    isSolved: isSolved,
    isUnderstood: isUnderstood,
    isWished: isWished,
    setSolved: setSolved,
    setUnderstood: setUnderstood,
    setWished: setWished,
    loadGraph: loadGraph,
    storageUsable: function () { return usable !== false; },
  };

  if (window.document$) {
    window.document$.subscribe(function (doc) { mount(doc.body || document.body); });
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function () { mount(document.body); });
  } else {
    mount(document.body);
  }
})();

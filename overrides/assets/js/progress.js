/*
 * kyopro-atlas：進捗の記録（planning/interfaces.md §6・§7、design.md §9.1）
 *
 * - 記録は localStorage の1つのキー kyopro-atlas:v1 に JSON で持つ。
 *     {"solved": {"abc340_e": true}, "understood": {"lazy-segment-tree": {"水": true}}, "updatedAt": "2026-10-21T12:00:00+09:00"}
 *   記録はこのブラウザの中だけにある。端末間の同期はしない（書き出し・読み込みで手動で退避する）
 * - 「解いた」：.kp-problems の各行の先頭にチェック欄を付ける（問題 ID はリンクの URL から取る）
 * - 「理解した」：テンプレートが出す input[data-kp-understood][data-kp-level] と結ぶ（ページ×レベル）
 * - 書き出し・読み込み：<div class="kp-progress-io"></div> に UI を出す
 * - ロードマップの集計：<div class="kp-roadmap-stats"></div> に、レベル・分野ごとの理解した数・解いた数を出す（graph.json）
 * - 別のタブの変更は storage イベントで反映する。変更のたびに document に "kp:progress" イベントを出す（知識マップが使う）
 * - localStorage が使えない環境（保存の拒否など）でも壊れない。そのときはこのページを開いている間だけメモリに持つ
 */
(function () {
  "use strict";

  var KEY = "kyopro-atlas:v1";
  var LEVELS = ["基礎", "水", "青", "黄", "発展"];
  var LV_CLASS = { 基礎: "kiso", 水: "mizu", 青: "ao", 黄: "ki", 発展: "hatten" };
  var SRC = document.currentScript ? document.currentScript.src : "";
  var GRAPH_URL = SRC ? new URL("../data/graph.json", SRC).href : null;
  var PROBLEM_URL = /^https:\/\/atcoder\.jp\/contests\/[^/]+\/tasks\/([A-Za-z0-9_]+)\/?$/;
  var PAGE_ID = /^[a-z0-9][a-z0-9-]*$/;
  var PROBLEM_ID = /^[A-Za-z0-9_]+$/;

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

  function empty() { return { solved: dict(), understood: dict(), updatedAt: null }; }

  // 形の崩れた値を捨て、true だけを残す
  function normalize(raw) {
    var out = empty();
    if (!raw || typeof raw !== "object" || Array.isArray(raw)) return out;
    if (raw.solved && typeof raw.solved === "object") {
      Object.keys(raw.solved).forEach(function (id) {
        if (raw.solved[id] === true && PROBLEM_ID.test(id) && id !== "__proto__") out.solved[id] = true;
      });
    }
    if (raw.understood && typeof raw.understood === "object") {
      Object.keys(raw.understood).forEach(function (pid) {
        var lv = raw.understood[pid];
        if (!PAGE_ID.test(pid) || !lv || typeof lv !== "object") return;
        var o = dict();
        LEVELS.forEach(function (l) { if (lv[l] === true) o[l] = true; });
        if (Object.keys(o).length) out.understood[pid] = o;
      });
    }
    if (typeof raw.updatedAt === "string") out.updatedAt = raw.updatedAt;
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

  function save(state) {
    state.updatedAt = localISO();
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

  function isSolved(st, id) { return st.solved[id] === true; }

  function isUnderstood(st, pid, lv) {
    var o = st.understood[pid];
    return !!(o && o[lv] === true);
  }

  function counts(st) {
    var u = 0;
    Object.keys(st.understood).forEach(function (pid) { u += Object.keys(st.understood[pid]).length; });
    return { solved: Object.keys(st.solved).length, understood: u };
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

  // 合わせる：解いた・理解したのどちらかが true なら true
  function merge(a, b) {
    var out = normalize(a);
    var nb = normalize(b);
    Object.keys(nb.solved).forEach(function (id) { out.solved[id] = true; });
    Object.keys(nb.understood).forEach(function (pid) {
      var o = out.understood[pid] || (out.understood[pid] = dict());
      Object.keys(nb.understood[pid]).forEach(function (l) { o[l] = true; });
    });
    return out;
  }

  function changed(st) {
    refresh(document, st);
    document.dispatchEvent(new CustomEvent("kp:progress", { detail: { state: st } }));
  }

  // ---------------------------------------------------------------- チェック欄

  // difficulty の色の帯（AtCoder Problems と同じ区切り）。[上限（未満）, class, 色の名前]
  var DIFF_BANDS = [
    [400, "gray", "灰"], [800, "brown", "茶"], [1200, "green", "緑"], [1600, "cyan", "水"],
    [2000, "blue", "青"], [2400, "yellow", "黄"], [2800, "orange", "橙"], [Infinity, "red", "赤"],
  ];
  // 問題の行の difficulty の 3 つの形（tools/check_pages.py の PROBLEM_LINE_RE。#5・#76）：
  // 「（diff 1354）」・台帳で参考値のもの「（diff 1856・参考値）」・値のないもの「（diff なし）」
  var DIFF_TEXT = /（(diff (\d+))(・参考値)?）|（diff なし）/;

  // 行の「（diff NNNN）」「（diff NNNN・参考値）」の「diff NNNN」を色の帯の class を付けた span で包む。丸は帯の中の
  // 位置だけ塗る（AtCoder Problems の表し方）。「・参考値」は span の外の文字のまま残し、title に添える。
  // 「diff なし」は色を付けない
  function markDifficulty(body) {
    var walker = document.createTreeWalker(body, NodeFilter.SHOW_TEXT);
    var node;
    while ((node = walker.nextNode())) {
      var m = DIFF_TEXT.exec(node.nodeValue);
      if (!m) continue;
      if (!m[1]) return; // 「diff なし」。行の difficulty はこれで終わり（後ろの要約は見ない）
      var d = Number(m[2]);
      var k = 0;
      while (d >= DIFF_BANDS[k][0]) k++;
      // 帯の幅は 400。3200 以上は全部塗る（AtCoder Problems は金属の色にするが、ここでは赤のまま）
      var fill = d >= 3200 ? 100 : Math.round(((d % 400) / 400) * 100);
      var target = node.splitText(m.index + 1); // 「（」の次から
      target.splitText(m[1].length); // 「diff NNNN」だけを切り出す
      var span = document.createElement("span");
      span.className = "kp-diff kp-diff--" + DIFF_BANDS[k][1];
      span.title = "difficulty " + d + (m[3] || "") + "（" + DIFF_BANDS[k][2] + "）"; // 参考値は「difficulty 1856・参考値（青）」
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

  // チェック欄の状態を記録に合わせる
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
    });
    root.querySelectorAll(".kp-progress-io[data-kp-mounted]").forEach(function (box) { ioSummary(box, st); });
    root.querySelectorAll(".kp-roadmap-stats[data-kp-mounted]").forEach(function (box) { renderStats(box, st); });
  }

  // チェック欄の変更は document で1回だけ受ける（instant navigation で入れ替わった要素にも効く）
  document.addEventListener("change", function (e) {
    var t = e.target;
    if (!(t instanceof HTMLInputElement) || t.type !== "checkbox") return;
    if (t.dataset.kpSolved) setSolved(t.dataset.kpSolved, t.checked);
    else if (t.dataset.kpUnderstood && t.dataset.kpLevel) setUnderstood(t.dataset.kpUnderstood, t.dataset.kpLevel, t.checked);
  });

  // 別のタブでの変更（e.key が null なのは clear() のとき）
  window.addEventListener("storage", function (e) {
    if (e.key === KEY || e.key === null) changed(load());
  });

  // ---------------------------------------------------------------- 書き出し・読み込み

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

  function ioSummary(box, st) {
    var c = counts(st);
    box.querySelector(".kp-io__summary").textContent =
      "この端末の記録：解いた " + c.solved + " 問・理解した " + c.understood + " 件（最終更新 " + formatDate(st.updatedAt) + "）";
    box.querySelector(".kp-io__warn").hidden = usable !== false;
  }

  function mountIO(box) {
    if (box.dataset.kpMounted) return;
    box.dataset.kpMounted = "1";
    box.textContent = "";
    var wrap = el("div", { class: "kp-io" });
    var summary = el("p", { class: "kp-io__summary" });
    var warn = el("p", { class: "kp-io__warn" },
      "このブラウザでは記録を保存できない（保存を拒否する設定など）。記録はこのページを開いている間だけ残る。");
    warn.hidden = true;
    var note = el("p", { class: "kp-stats__note" },
      "記録はこのブラウザの中だけにあり、端末の間では同期しない。ブラウザのデータを消すと記録も消えるので、ときどき書き出して保存しておく。");
    var buttons = el("div", { class: "kp-io__buttons" });
    var bExport = el("button", { type: "button", class: "md-button", "aria-expanded": "false" }, "書き出す");
    var bImport = el("button", { type: "button", class: "md-button", "aria-expanded": "false" }, "読み込む");
    buttons.append(bExport, bImport);

    var pExport = el("div", { class: "kp-io__panel" });
    pExport.hidden = true;
    var lExport = el("label", null, "記録の JSON（全体をコピーして、メモなどに保存する）");
    var tExport = el("textarea", { rows: "6", readonly: "", spellcheck: "false" });
    lExport.appendChild(tExport);
    var bCopy = el("button", { type: "button", class: "md-button md-button--primary" }, "コピーする");
    pExport.append(lExport, bCopy);

    var pImport = el("div", { class: "kp-io__panel" });
    pImport.hidden = true;
    var lImport = el("label", null, "書き出した JSON を貼り付ける");
    var tImport = el("textarea", { rows: "6", spellcheck: "false" });
    lImport.appendChild(tImport);
    var bMerge = el("button", { type: "button", class: "md-button md-button--primary" }, "今の記録と合わせる");
    var bReplace = el("button", { type: "button", class: "md-button" }, "今の記録を置き換える");
    var importButtons = el("div", { class: "kp-io__buttons" });
    importButtons.append(bMerge, bReplace);
    pImport.append(lImport, importButtons);

    var status = el("p", { class: "kp-io__status", role: "status", "aria-live": "polite" });
    wrap.append(summary, warn, note, buttons, pExport, pImport, status);
    box.appendChild(wrap);

    function say(msg, isError) {
      status.textContent = msg;
      status.classList.toggle("kp-is-error", !!isError);
    }
    function toggle(panel, button, other, otherButton) {
      var open = panel.hidden;
      panel.hidden = !open;
      button.setAttribute("aria-expanded", String(open));
      other.hidden = true;
      otherButton.setAttribute("aria-expanded", "false");
      say("");
      return open;
    }

    bExport.addEventListener("click", function () {
      if (toggle(pExport, bExport, pImport, bImport)) {
        tExport.value = JSON.stringify(load(), null, 1);
        tExport.focus();
        tExport.select();
      }
    });
    bImport.addEventListener("click", function () {
      if (toggle(pImport, bImport, pExport, bExport)) tImport.focus();
    });

    bCopy.addEventListener("click", function () {
      var text = tExport.value;
      function fallback() {
        tExport.focus();
        tExport.select();
        var ok = false;
        try { ok = document.execCommand("copy"); } catch (e) { ok = false; }
        say(ok ? "コピーした。" : "コピーできなかった。選んだ文字を手でコピーする。", !ok);
      }
      if (navigator.clipboard && window.isSecureContext) {
        navigator.clipboard.writeText(text).then(function () { say("コピーした。"); }, fallback);
      } else {
        fallback();
      }
    });

    function parseInput() {
      var raw;
      try {
        raw = JSON.parse(tImport.value);
      } catch (e) {
        say("JSON として読めない。書き出した文字を全部そのまま貼り付ける。", true);
        return null;
      }
      if (!raw || typeof raw !== "object" || Array.isArray(raw) || !("solved" in raw || "understood" in raw)) {
        say("この教材の記録の形ではない（solved と understood がない）。", true);
        return null;
      }
      return normalize(raw);
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
      var st = merge(load(), inc);
      var ok = save(st);
      changed(st);
      var c = counts(st);
      say("合わせた。解いた " + c.solved + " 問・理解した " + c.understood + " 件になった。" + (ok ? "" : "（このブラウザには保存できない）"), !ok);
    });

    bReplace.addEventListener("click", function () {
      var inc = parseInput();
      if (!inc) { resetConfirm(); return; }
      var now = counts(load());
      if ((now.solved || now.understood) && Date.now() > confirmUntil) {
        confirmUntil = Date.now() + 10000;
        bReplace.textContent = "もう一度押すと置き換える";
        say("置き換えると、今の記録（解いた " + now.solved + " 問・理解した " + now.understood + " 件）は消える。よければ10秒以内にもう一度押す。");
        return;
      }
      resetConfirm();
      var ok = save(inc);
      changed(inc);
      var c = counts(inc);
      say("置き換えた。解いた " + c.solved + " 問・理解した " + c.understood + " 件になった。" + (ok ? "" : "（このブラウザには保存できない）"), !ok);
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
    return {
      levels: byLevel.map(finish),
      fields: Array.from(byField.values()).map(finish).filter(function (r) { return r.items || r.problems; }),
      total: finish(total),
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

  function table(caption, head, rows, total, levelBadges) {
    var scroll = el("div", { class: "md-typeset__scrollwrap" });
    var wrapper = el("div", { class: "md-typeset__table" });
    var t = el("table");
    t.appendChild(el("caption", null, caption));
    var thead = el("thead");
    var tr = el("tr");
    tr.append(el("th", null, head), el("th", { class: "kp-num" }, "理解した"), el("th", { class: "kp-num" }, "解いた問題"));
    thead.appendChild(tr);
    var tbody = el("tbody");
    rows.concat(total ? [total] : []).forEach(function (r) {
      var row = el("tr");
      var th = el("td");
      if (levelBadges && LV_CLASS[r.label]) th.appendChild(el("span", { class: "kp-mini kp-lv-" + LV_CLASS[r.label] }, r.label));
      else th.textContent = r.label;
      row.append(th, cell(r.understood, r.items), cell(r.solved, r.problems));
      tbody.appendChild(row);
    });
    t.append(thead, tbody);
    wrapper.appendChild(t);
    scroll.appendChild(wrapper);
    return scroll;
  }

  var statsData = new WeakMap();

  function renderStats(box, st) {
    var g = statsData.get(box);
    if (!g) return;
    var s = computeStats(g, st || load());
    box.textContent = "";
    var wrap = el("div", { class: "kp-stats" });
    wrap.appendChild(table("レベル別", "レベル", s.levels, s.total, true));
    wrap.appendChild(table("分野別", "分野", s.fields, null, false));
    wrap.appendChild(el("p", { class: "kp-stats__note" },
      "「理解した」はページのレベルと、ページの中の上位の帯の節を1件ずつ数える。解いた問題はページの例題・練習・力試しから数える。"));
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

  // ---------------------------------------------------------------- 取り付け

  function mount(root) {
    mountProblems(root);
    root.querySelectorAll(".kp-progress-io").forEach(mountIO);
    root.querySelectorAll(".kp-roadmap-stats").forEach(mountStats);
    refresh(root);
  }

  window.KPProgress = {
    KEY: KEY,
    LEVELS: LEVELS,
    load: load,
    save: save,
    merge: merge,
    isSolved: isSolved,
    isUnderstood: isUnderstood,
    setSolved: setSolved,
    setUnderstood: setUnderstood,
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

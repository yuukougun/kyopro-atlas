/*
 * kyopro-atlas：語の照合の規則と、語で表の行を絞り込む欄（planning/interfaces.md §7。Issue #59・#60）
 *
 * 照合の規則（window.KPMatch）。知識マップの「ページ」欄（map.js）も同じ規則を使う
 * - norm(s)：NFKC で全角と半角をそろえ、小文字にし、カタカナをひらがなにし、空白と区切りの記号（- _ ・ ‐ − – ' ’）を除く。
 *   「Union Find」「union-find」「ＵＮＩＯＮ－ＦＩＮＤ」は同じになり、「だいくすとら」は「ダイクストラ」に当たる
 * - 言い換え（SYNONYMS）：gcd ⇔ 最大公約数 のような少数の組。語が組のどれかを含めば、それをほかの語に置き換えた形でも探す
 *   （組のどの語で探しても同じものが当たる）。組の語の後ろが語の終わりまでひらがなだけなら（取り除いた・削除する）、
 *   その送り仮名・助詞を落として置き換える
 * - 語は空白で区切り、すべての語を含むものだけを残す（「K 番目」は「k」と「番目」の両方を含む行）
 *
 * 絞り込みの欄：本文に <div class="kp-filter"></div> を置いたページで、ページの題の下（要点の囲みの前）に欄を出す。
 * 要点は本文の最初に置く約束（interfaces.md §4）なので、目印の div は要点の後に置き、ここで前へ移す。
 * - 単位は表の行（tbody の tr。既定）か、data-kp-units="li" のとき本文の箇条書きの項目（article の直下の ul の li）。
 *   data-kp-sections="kana latin" のように ## の id を書くと、その節の中の表・箇条書きだけを単位にする（説明の箇条書きを除く）
 * - 語を入れると、語を含む単位と、それを含む表・箇条書き・見出し（## と ###）だけを残し、ほかの本文（説明・図・確認問題）は
 *   隠す（残すものに kp-filter-keep を付け、ほかは CSS で隠す）。件数を出す。語を消すと元に戻る。語はアドレスの ?filter= に
 *   入れる（戻る・ブックマークで同じ絞り込みになる）
 * - 隠れた見出しへのリンク（目次など）を押したら、絞り込みを解いてから移る
 * - JS が動かない環境では目印の div は空のままで、表はそのまま見える
 * すべての JS と同じく、Material の document$ を購読して instant navigation のたびに取り付け直す。
 */
(function () {
  "use strict";

  // ---------------------------------------------------------------- 照合の規則

  // 言い換えの組（表記が違うだけで同じものを指す語）。語が組の語を含めば、それを組のほかの語に置き換えた形でも探すので、
  // 組のどの語で探しても同じものが当たる。活用する語は、件数の行に出す形（取り除く）と、送り仮名を落とした形（取り除）の
  // 両方を書く（「取り除いて」も「取り除」を含むので当たる）。足すときは、語を含む行が増えすぎないか確かめる
  var SYNONYMS = [
    ["gcd", "最大公約数"],
    ["lcm", "最小公倍数"],
    ["xor", "排他的論理和"],
    ["swap", "スワップ", "入れ替える", "入れ替え", "交換"],
    ["mod", "余り", "剰余"],
    ["dp", "動的計画法"],
    ["bfs", "幅優先探索"],
    ["dfs", "深さ優先探索"],
    ["最短路", "最短経路"],
    ["削除", "取り除く", "取り除"],
    ["セグ木", "セグメント木"],
  ];
  var DROP = /[\s\-_・‐−–'’]+/g;
  var KANA_TAIL = /^[\u3041-\u3096]+$/; // ひらがなだけ（語の後ろの送り仮名・助詞）

  // NFKC で全角と半角をそろえ、小文字にし、区切りの記号を除く。kana が真ならカタカナをひらがなにする（カタカナとひらがなは
  // 1 字ずつ対応し、区切りの記号でもないので、kana の真偽で文字の位置は変わらない）
  function fold(s, kana) {
    var t = String(s == null ? "" : s).normalize("NFKC").toLowerCase();
    if (kana) {
      var out = "";
      for (var i = 0; i < t.length; i++) {
        var c = t.charCodeAt(i);
        out += c >= 0x30a1 && c <= 0x30f6 ? String.fromCharCode(c - 0x60) : t[i]; // カタカナ → ひらがな
      }
      t = out;
    }
    return t.replace(DROP, "");
  }

  function norm(s) { return fold(s, true); }

  var GROUPS = SYNONYMS.map(function (g) {
    return g.map(function (w) { return { raw: w, n: norm(w) }; });
  });

  // 組の語 a が、組の語 b の一部か（「取り除」は「取り除く」の一部）
  function partOf(a, b) { return b.n.length > a.n.length && b.n.indexOf(a.n) >= 0; }

  // 語 s（空白で区切った 1 語。正規化の前でも後でもよい）の言い換え：[{n: 探す形, from: 元の語, to: 言い換えの語}]。
  // 正規化した s そのものは含めない。to が "" の形は探すだけで、件数の行には出さない
  // - 語が同じ組の語を重ねて含むとき（「取り除く」は「取り除」も含む）は、長い方だけを置き換える
  // - 組の語の後ろが語の終わりまでひらがなだけなら（送り仮名・助詞）、そのひらがなごと置き換え（「取り除いた」→「削除」）、
  //   ひらがなを落としただけの形（「削除する」→「削除」）も探す。カタカナはひらがなにする前の形で見る（「削除クエリ」の
  //   「クエリ」は落とさない）
  // - 件数の行には、元の語と同じ語の別の形（「取り除く」に対する「取り除」）と、組のほかの語の一部の形（「取り除」）を出さない
  function synonyms(s) {
    var q = norm(s);
    var k = fold(s, false); // q と同じ位置で、カタカナを残した形
    var out = [];
    function add(n, from, to) {
      if (!n || n === q) return;
      var o = out.filter(function (x) { return x.n === n; })[0];
      if (!o) out.push({ n: n, from: from, to: to });
      else if (to && !o.to) { o.from = from; o.to = to; }
    }
    GROUPS.forEach(function (g) {
      var found = g.filter(function (a) { return a.n && q.indexOf(a.n) >= 0; });
      found.forEach(function (a) {
        if (found.some(function (b) { return partOf(a, b); })) return;
        var at = q.lastIndexOf(a.n);
        var end = at + a.n.length;
        var tail = end < q.length && KANA_TAIL.test(k.slice(end)) ? k.slice(end) : "";
        var from = a.raw + tail;
        var put = function (w) { return tail ? q.slice(0, at).split(a.n).join(w) + w : q.split(a.n).join(w); };
        if (tail) add(put(a.n), from, "");
        g.forEach(function (b) {
          if (b === a) return;
          var hide = partOf(a, b) || g.some(function (c) { return partOf(b, c); });
          add(put(b.n), from, hide ? "" : b.raw);
        });
      });
    });
    return out;
  }

  // 語を空白（全角の空白も）で区切る。正規化すると空になる語（記号だけ）は除く
  function words(query) {
    return String(query || "").normalize("NFKC").split(/\s+/).filter(function (t) { return norm(t); });
  }

  // 空白で区切った語ごとに、[正規化した形, ...言い換え] の列
  function terms(query) {
    return words(query).map(function (t) {
      return [norm(t)].concat(synonyms(t).map(function (s) { return s.n; }));
    });
  }

  // 正規化した文字 text が、すべての語（のどれかの形）を含むか
  function test(text, ts) {
    return ts.every(function (vs) {
      return vs.some(function (v) { return text.indexOf(v) >= 0; });
    });
  }

  window.KPMatch = { norm: norm, synonyms: synonyms, words: words, terms: terms, test: test, SYNONYMS: SYNONYMS };

  // ---------------------------------------------------------------- 絞り込みの欄

  var PARAM = "filter";
  var DELAY = 150; // 打つたびに絞らず、少し待つ（ms）
  var SKIP = ".kp-links, .kp-page-info, .md-source-file, .md-content__button";
  var cache = new WeakMap(); // 単位の要素 → 正規化した文字（セルの境目をまたいで当たらないよう \u0001 でつなぐ）
  var current = null; // このページの欄

  function el(tag, attrs, text) {
    var e = document.createElement(tag);
    if (attrs) Object.keys(attrs).forEach(function (k) { e.setAttribute(k, attrs[k]); });
    if (text != null) e.textContent = text;
    return e;
  }

  function unitText(u) {
    var t = cache.get(u);
    if (t == null) {
      var parts = u.tagName === "TR" ? Array.prototype.map.call(u.cells, function (c) { return c.textContent; }) : [u.textContent];
      t = parts.map(norm).join("\u0001");
      cache.set(u, t);
    }
    return t;
  }

  function fmt(n) { return n.toLocaleString("ja-JP"); }

  function mount(box) {
    if (box.dataset.kpMounted) return;
    var article = box.closest("article") || box.parentElement;
    if (!article) return;
    box.dataset.kpMounted = "1";
    var mode = box.dataset.kpUnits === "li" ? "li" : "tr";
    var unitName = mode === "li" ? "語" : "行";

    // 要点の囲みの前（ページの題の下）へ移す。狭い画面でも開いてすぐ見える位置にするため
    var abstract = article.querySelector(":scope > .admonition.abstract");
    if (abstract && abstract.compareDocumentPosition(box) & Node.DOCUMENT_POSITION_FOLLOWING) article.insertBefore(box, abstract);

    box.textContent = "";
    box.setAttribute("role", "search");
    var id = "kp-filter-" + Math.random().toString(36).slice(2, 8);
    var row = el("div", { class: "kp-filter__box" });
    var input = el("input", {
      class: "kp-filter__input", type: "search", id: id, autocomplete: "off", spellcheck: "false", enterkeyhint: "search",
      placeholder: "語で" + unitName + "を絞り込む（例：" + (mode === "li" ? "セグ木・dsu" : "最大公約数・K 番目") + "）",
      "aria-label": "語で" + (mode === "li" ? "索引の語" : "表の行") + "を絞り込む",
      "aria-describedby": id + "-status",
    });
    var clear = el("button", { class: "kp-filter__clear", type: "button", "aria-label": "絞り込みを消す", title: "絞り込みを消す" }, "×");
    clear.hidden = true;
    row.append(input, clear);
    var status = el("p", { class: "kp-filter__status", id: id + "-status", role: "status", "aria-live": "polite" });
    box.append(row, status);

    // 欄の後ろにある本文の要素（article の直下）。表は Material の JS が後から div で包むので、絞るたびに数え直す
    function blocks() {
      var out = [];
      var after = false;
      Array.prototype.forEach.call(article.children, function (b) {
        if (b === box) { after = true; return; }
        if (after && !b.matches(SKIP)) out.push(b);
      });
      return out;
    }

    // 絞り込む単位を持つ節（## の id。data-kp-sections に空白で区切って書く）。書かなければすべての節
    var sections = (box.dataset.kpSections || "").split(/\s+/).filter(Boolean);
    function units(b, h2) {
      if (sections.length && !(h2 && sections.indexOf(h2.id) >= 0)) return [];
      if (mode === "li") return b.tagName === "UL" ? Array.prototype.slice.call(b.children).filter(function (x) { return x.tagName === "LI"; }) : [];
      return Array.prototype.slice.call(b.querySelectorAll("tbody tr"));
    }

    var total = 0;
    var h2now = null;
    blocks().forEach(function (b) {
      if (b.tagName === "H2") h2now = b;
      else total += units(b, h2now).length;
    });
    var hint = fmt(total) + " " + unitName + "。語を入れると、その語を含む" + unitName + "だけを残す（空白で区切ると、すべての語を含む" +
      unitName + "）。全角と半角・カタカナとひらがなの違いは問わない。";

    // 絞っている間は、欄の後ろの本文のうち kp-filter-keep の付いた要素だけを見せる（CSS。後から差し替わる図などの要素も
    // 印がないので隠れる）。残す表・箇条書きの中の当たらない行には kp-filter-off を付ける
    function reset() {
      Array.prototype.forEach.call(article.querySelectorAll(".kp-filter-off, .kp-filter-keep"), function (e) {
        e.classList.remove("kp-filter-off", "kp-filter-keep");
      });
      article.classList.remove("kp-filtering");
    }

    function apply() {
      var q = input.value;
      var ts = terms(q);
      clear.hidden = !q;
      writeQuery(q.trim());
      if (!ts.length) {
        reset();
        status.textContent = hint;
        return;
      }
      article.classList.add("kp-filtering");
      var shown = 0;
      var h2 = null;
      var h3 = null;
      var heads = [];
      blocks().forEach(function (b) {
        var tag = b.tagName;
        if (tag === "H2") { h2 = { el: b, on: false }; h3 = null; heads.push(h2); return; }
        if (tag === "H3" || tag === "H4") { h3 = { el: b, on: false }; heads.push(h3); return; }
        var us = units(b, h2 && h2.el);
        var any = false;
        us.forEach(function (u) {
          var on = test(unitText(u), ts);
          u.classList.toggle("kp-filter-off", !on);
          if (on) { any = true; shown++; }
        });
        b.classList.toggle("kp-filter-keep", any);
        if (any) {
          if (h2) h2.on = true;
          if (h3) h3.on = true;
        }
      });
      heads.forEach(function (h) { h.el.classList.toggle("kp-filter-keep", h.on); });

      // 件数の行に出す言い換え：元の語ごとに、言い換えの語をまとめる
      var used = [];
      words(q).forEach(function (t) {
        synonyms(t).forEach(function (s) {
          if (!s.to) return;
          var u = used.filter(function (x) { return x.from === s.from; })[0];
          if (!u) used.push(u = { from: s.from, to: [] });
          if (u.to.indexOf(s.to) < 0) u.to.push(s.to);
        });
      });
      var msg = shown ? fmt(shown) + " " + unitName + "が当たった（全 " + fmt(total) + " " + unitName + "）。"
        : "当たる" + unitName + "がない。語を短くするか、別の言い方で探す。";
      if (used.length) {
        msg += "言い換え：" + used.map(function (u) { return "「" + u.from + "」を「" + u.to.join("」・「") + "」"; }).join("、") +
          "に置き換えた形でも探した。";
      }
      status.textContent = msg;
    }

    var timer = 0;
    function schedule() {
      clearTimeout(timer);
      timer = setTimeout(apply, DELAY);
    }
    input.addEventListener("input", schedule);
    input.addEventListener("search", function () { clearTimeout(timer); apply(); }); // Enter と、欄の × で消したとき
    input.addEventListener("keydown", function (e) {
      if (e.key === "Escape" && input.value) {
        e.preventDefault();
        input.value = "";
        apply();
      }
    });
    clear.addEventListener("click", function () {
      input.value = "";
      apply();
      input.focus();
    });

    // Material が後から本文の要素を差し替える（表を div で包む・図を描く）ので、絞っている間は差し替えのたびに絞り直す
    if (window.MutationObserver) {
      new MutationObserver(function () {
        if (article.classList.contains("kp-filtering")) schedule();
      }).observe(article, { childList: true });
    }

    var api = {
      article: article,
      // 隠れた要素へ移るリンクを押したら、絞り込みを解く
      reveal: function (target) {
        if (!input.value || !target || !article.contains(target) || !article.classList.contains("kp-filtering")) return;
        if (target.closest(".kp-filter-off") || !target.getClientRects().length) {
          input.value = "";
          apply();
        }
      },
    };
    current = api;

    var initial = new URLSearchParams(location.search).get(PARAM);
    if (initial) input.value = initial;
    apply();
  }

  function writeQuery(q) {
    try {
      var params = new URLSearchParams(location.search);
      if ((params.get(PARAM) || "") === q) return;
      if (q) params.set(PARAM, q);
      else params.delete(PARAM);
      var qs = params.toString();
      history.replaceState(history.state, "", location.pathname + (qs ? "?" + qs : "") + location.hash);
    } catch (e) { /* 書き換えられなくても絞り込みは続ける */ }
  }

  // 同じページの見出しへのリンク（目次・本文）：行き先が隠れていれば、移る前に絞り込みを解く。Material の instant navigation は
  // ページを読み込んだときのアドレス（?filter= を含む）でリンクを絶対の URL に書き換えるので、押したときの絞り込みに合わせて
  // から移す（同じ pathname のリンクは読み込み直さず、そのアドレスへ移るだけなので、合わせないとアドレスと表示がずれる）
  document.addEventListener("click", function (e) {
    if (!current || !current.article.isConnected) return;
    var a = e.target instanceof Element ? e.target.closest("a[href]") : null;
    if (!a || !a.hash || a.origin !== location.origin || a.pathname !== location.pathname) return;
    var id = "";
    try { id = decodeURIComponent(a.hash.slice(1)); } catch (err) { return; }
    if (id) current.reveal(document.getElementById(id));
    if (a.search !== location.search) a.href = location.pathname + location.search + a.hash;
  }, true);

  function onDocument(doc) {
    var root = doc.body || document.body;
    Array.prototype.forEach.call(root.querySelectorAll(".kp-filter"), mount);
  }

  if (window.document$) {
    window.document$.subscribe(onDocument);
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function () { onDocument(document); });
  } else {
    onDocument(document);
  }
})();

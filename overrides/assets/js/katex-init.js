/*
 * kyopro-atlas：数式の描画（planning/interfaces.md §7）
 * pymdownx.arithmatex（generic: true）が出す要素だけを KaTeX 0.16.47（同梱）で描く。
 *   インライン：<span class="arithmatex">\( … \)</span>
 *   ブロック  ：<div class="arithmatex">\[ … \]</div>（\begin{align} などの環境も \[ \] で包まれて来る）
 * 本文の中の $ を数式と誤認しないよう、ページ全体は走査しない。
 * instant navigation でページが替わるたびに document$ が通知されるので、そのたびに描く（描いた要素には印を付ける）。
 */
(function () {
  "use strict";

  // 教材全体で使うマクロを足すときはここに書く（例：{"\\floor": "\\left\\lfloor #1 \\right\\rfloor"}）
  var MACROS = {};

  function strip(tex, open, close) {
    tex = tex.trim();
    if (tex.slice(0, open.length) === open && tex.slice(-close.length) === close) {
      return tex.slice(open.length, tex.length - close.length);
    }
    return tex;
  }

  function render(root) {
    if (!window.katex) return;
    root.querySelectorAll(".arithmatex").forEach(function (el) {
      if (el.dataset.kpRendered) return;
      var display = el.tagName !== "SPAN";
      var tex = display ? strip(el.textContent, "\\[", "\\]") : strip(el.textContent, "\\(", "\\)");
      try {
        window.katex.render(tex, el, {
          displayMode: display,
          throwOnError: false, // 書き誤りは赤字で出し、ページは止めない
          macros: Object.assign({}, MACROS),
        });
        el.dataset.kpRendered = "1";
      } catch (e) {
        console.error("kyopro-atlas: 数式を描けない", tex, e);
      }
    });
  }

  if (window.document$) {
    window.document$.subscribe(function (doc) { render(doc.body || document.body); });
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function () { render(document.body); });
  } else {
    render(document.body);
  }
})();

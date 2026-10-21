/*
 * kyopro-atlas：動く図の共通部品（planning/interfaces.md §7、design.md §8.5）
 *
 * 本文に次のように書くと、assets/js/viz/<名前>.js を読み込み、登録された図をステップ送りの操作付きで描く。
 *   <div class="kp-viz" data-viz="<名前>" data-config='{"array": [1, 3, 5]}'></div>
 * JS が動かない環境（GitHub の表示や Claude が Markdown を読む場合）のために、図の前後に文章で要点を書いておく。
 *
 * 図のファイル（見本は viz/binary-search.js）は次の形で登録する。
 *   window.KPViz.register("<名前>", {
 *     title: "図の短い説明",                       // 読み上げに使う
 *     states: function (config) { … },          // 状態の配列。アルゴリズムを最後まで実行して各ステップを記録する。
 *                                                //   各状態は caption（そのステップの説明文）を持つ。DOM を使わない純粋な関数にし、
 *                                                //   Node で単体試験する（tests/viz/）。入力が正しくなければ Error を投げる
 *     render: function (svg, state, config, h) { … },  // その状態を svg に描く（svg は毎回空にして渡す）。
 *                                                //   h(tag, attrs, text) は SVG の要素を作る道具
 *     viewBox: function (config, states) { … }  // 省略可。"x y 幅 高さ"。全ステップで同じ大きさにする
 *   });
 * 色は kp.css の .kp-v-* の class（Material の CSS 変数）で付けると、ライトとダークに追従する。
 * 操作：最初・前・次・最後・自動再生・速度・スライダー。キーボード（← → Home End Space）。横のスワイプ。
 * 取り付けは Material の document$ で instant navigation のたびに行い、同じ要素には1回だけ取り付ける。
 */
(function () {
  "use strict";

  var NS = "http://www.w3.org/2000/svg";
  var SRC = document.currentScript ? document.currentScript.src : "";
  var STEP_MS = 1200; // 自動再生の1ステップ（速度 1× のとき）
  var SPEEDS = [0.5, 1, 2, 4];
  var NAME = /^[a-z0-9][a-z0-9-]*$/;

  // 記号の文字はフォントにないと豆腐になるので、ボタンの絵は SVG の図形で描く（24×24）
  var ICONS = {
    first: "M5 5h2.5v14H5z M19 5v14l-9.5-7z",
    prev: "M15.5 4.5l2 2L12 12l5.5 5.5-2 2L8 12z",
    play: "M8 5v14l11-7z",
    pause: "M6.5 5h4v14h-4z M13.5 5h4v14h-4z",
    next: "M8.5 4.5l-2 2L12 12l-5.5 5.5 2 2L16 12z",
    last: "M16.5 5H19v14h-2.5z M5 5v14l9.5-7z",
  };

  var registry = Object.create(null);
  var pending = Object.create(null);
  var waiters = Object.create(null);

  function register(name, def) {
    if (!def || typeof def.states !== "function" || typeof def.render !== "function") {
      console.error("kyopro-atlas: 図の登録の形が違う（states と render が要る）：" + name);
      return;
    }
    registry[name] = def;
    (waiters[name] || []).forEach(function (fn) { fn(def); });
    delete waiters[name];
  }

  function load(name) {
    if (registry[name]) return Promise.resolve(registry[name]);
    if (!NAME.test(name)) return Promise.reject(new Error("data-viz の名前が正しくない：" + name));
    if (!pending[name]) {
      pending[name] = new Promise(function (resolve, reject) {
        (waiters[name] = waiters[name] || []).push(resolve);
        var s = document.createElement("script");
        s.src = new URL("viz/" + name + ".js", SRC || location.href).href;
        s.onload = function () {
          if (!registry[name]) {
            delete pending[name];
            delete waiters[name];
            reject(new Error("図が登録されなかった：" + name));
          }
        };
        s.onerror = function () {
          delete pending[name];
          delete waiters[name];
          reject(new Error("図のスクリプトを読み込めない：" + name));
        };
        document.head.appendChild(s);
      });
    }
    return pending[name];
  }

  // SVG の要素を作る
  function h(tag, attrs, text) {
    var e = document.createElementNS(NS, tag);
    if (attrs) {
      Object.keys(attrs).forEach(function (k) {
        if (attrs[k] != null && attrs[k] !== false) e.setAttribute(k, attrs[k]);
      });
    }
    if (text != null) e.textContent = String(text);
    return e;
  }

  function html(tag, cls, text) {
    var e = document.createElement(tag);
    if (cls) e.className = cls;
    if (text != null) e.textContent = text;
    return e;
  }

  function fail(root, msg) {
    root.textContent = "";
    root.appendChild(html("p", "kp-viz__error", "図を表示できなかった：" + msg));
    console.error("kyopro-atlas: 図を表示できなかった（" + (root.dataset.viz || "?") + "）：" + msg);
  }

  function iconButton(icon, label) {
    var b = html("button", "kp-viz__btn");
    b.type = "button";
    b.setAttribute("aria-label", label);
    b.title = label;
    var svg = h("svg", { viewBox: "0 0 24 24", "aria-hidden": "true", focusable: "false" });
    svg.appendChild(h("path", { d: ICONS[icon] }));
    b.appendChild(svg);
    return b;
  }

  function setIcon(b, icon, label) {
    b.querySelector("path").setAttribute("d", ICONS[icon]);
    b.setAttribute("aria-label", label);
    b.title = label;
  }

  function build(root, def, config) {
    var states;
    try {
      states = def.states(config);
    } catch (e) {
      fail(root, e.message);
      return;
    }
    if (!Array.isArray(states) || states.length === 0) {
      fail(root, "状態の列が空である");
      return;
    }

    var n = states.length;
    var i = 0;
    var timer = null;
    var speed = 1;
    var title = def.title || "動く図";

    root.textContent = "";
    root.tabIndex = 0;
    root.setAttribute("role", "group");
    root.setAttribute("aria-roledescription", "ステップ送りの図");
    root.setAttribute("aria-label", title + "（← → で1ステップずつ、Space で自動再生）");

    var svg = h("svg", { class: "kp-viz__svg", role: "img", "aria-label": title });
    var vb = def.viewBox ? def.viewBox(config, states) : null;
    if (vb) svg.setAttribute("viewBox", vb);
    var caption = html("p", "kp-viz__caption");
    caption.setAttribute("aria-live", "polite");

    var controls = html("div", "kp-viz__controls");
    var bFirst = iconButton("first", "最初へ");
    var bPrev = iconButton("prev", "前へ");
    var bPlay = iconButton("play", "自動再生");
    var bNext = iconButton("next", "次へ");
    var bLast = iconButton("last", "最後へ");
    var range = document.createElement("input");
    range.type = "range";
    range.className = "kp-viz__range";
    range.min = "0";
    range.max = String(n - 1);
    range.step = "1";
    range.value = "0";
    range.setAttribute("aria-label", "ステップ");
    var speedLabel = html("label", "kp-viz__speed", "速度");
    var speedSel = document.createElement("select");
    SPEEDS.forEach(function (s) {
      var o = new Option(s + "×", String(s));
      if (s === 1) o.selected = true;
      speedSel.add(o);
    });
    speedLabel.appendChild(speedSel);
    var counter = html("span", "kp-viz__counter");
    counter.setAttribute("aria-hidden", "true");
    controls.append(bFirst, bPrev, bPlay, bNext, bLast, range, speedLabel, counter);
    root.append(svg, caption, controls);

    function draw() {
      var s = states[i];
      svg.replaceChildren();
      try {
        def.render(svg, s, config, h);
      } catch (e) {
        console.error("kyopro-atlas: 図を描けない", e);
        caption.textContent = "図を描けなかった：" + e.message;
        return;
      }
      caption.textContent = s.caption || "";
      counter.textContent = i + 1 + " / " + n;
      range.value = String(i);
      range.setAttribute("aria-valuetext", i + 1 + " / " + n + "：" + (s.caption || ""));
      bFirst.disabled = bPrev.disabled = i === 0;
      bNext.disabled = bLast.disabled = i === n - 1;
    }

    function go(j) {
      i = Math.max(0, Math.min(n - 1, j));
      draw();
    }

    function stop() {
      if (timer) clearTimeout(timer);
      timer = null;
      setIcon(bPlay, "play", "自動再生");
      bPlay.setAttribute("aria-pressed", "false");
    }

    function tick() {
      timer = null;
      if (!root.isConnected) return; // instant navigation でページが替わった
      go(i + 1);
      if (i >= n - 1) stop();
      else timer = setTimeout(tick, STEP_MS / speed);
    }

    function play() {
      if (i >= n - 1) go(0);
      setIcon(bPlay, "pause", "一時停止");
      bPlay.setAttribute("aria-pressed", "true");
      timer = setTimeout(tick, STEP_MS / speed);
    }

    function togglePlay() {
      if (timer) stop();
      else play();
    }

    function step(fn) {
      return function () {
        stop();
        fn();
      };
    }

    bFirst.addEventListener("click", step(function () { go(0); }));
    bPrev.addEventListener("click", step(function () { go(i - 1); }));
    bNext.addEventListener("click", step(function () { go(i + 1); }));
    bLast.addEventListener("click", step(function () { go(n - 1); }));
    bPlay.addEventListener("click", togglePlay);
    range.addEventListener("input", step(function () { go(Number(range.value)); }));
    speedSel.addEventListener("change", function () {
      speed = Number(speedSel.value) || 1;
      if (timer) {
        clearTimeout(timer);
        timer = setTimeout(tick, STEP_MS / speed);
      }
    });

    root.addEventListener("keydown", function (e) {
      if (e.altKey || e.ctrlKey || e.metaKey || e.shiftKey) return;
      var t = e.target;
      if (t === range || t === speedSel) return; // スライダーと選択欄は自分でキーを扱う
      switch (e.key) {
        case "ArrowRight": stop(); go(i + 1); break;
        case "ArrowLeft": stop(); go(i - 1); break;
        case "Home": stop(); go(0); break;
        case "End": stop(); go(n - 1); break;
        case " ":
          if (t.tagName === "BUTTON") return; // ボタンの上の Space はそのボタンを押す
          togglePlay();
          break;
        default:
          return;
      }
      e.preventDefault();
    });

    // 横のスワイプで送る（縦の動きはページのスクロールに任せる。CSS の touch-action: pan-y）
    var sx = null, sy = 0, st = 0, pid = null;
    svg.addEventListener("pointerdown", function (e) {
      if (e.pointerType === "mouse") return;
      sx = e.clientX;
      sy = e.clientY;
      st = Date.now();
      pid = e.pointerId;
    });
    svg.addEventListener("pointerup", function (e) {
      if (sx === null || e.pointerId !== pid) return;
      var dx = e.clientX - sx, dy = e.clientY - sy;
      sx = null;
      if (Math.abs(dx) >= 40 && Math.abs(dx) > 1.5 * Math.abs(dy) && Date.now() - st < 1000) {
        stop();
        go(dx < 0 ? i + 1 : i - 1);
      }
    });
    svg.addEventListener("pointercancel", function () { sx = null; });

    root.kpViz = {
      states: states,
      go: go,
      index: function () { return i; },
      playing: function () { return !!timer; },
    };
    go(0);
  }

  function mount(root) {
    if (root.dataset.kpMounted) return;
    root.dataset.kpMounted = "1";
    var config;
    try {
      config = root.dataset.config ? JSON.parse(root.dataset.config) : {};
    } catch (e) {
      fail(root, "data-config を JSON として読めない（" + e.message + "）");
      return;
    }
    load(root.dataset.viz || "").then(
      function (def) { build(root, def, config); },
      function (e) { fail(root, e.message); }
    );
  }

  window.KPViz = { register: register, load: load, h: h };

  function mountAll(doc) {
    (doc.body || document.body).querySelectorAll(".kp-viz[data-viz]").forEach(mount);
  }
  if (window.document$) {
    window.document$.subscribe(mountAll);
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function () { mountAll(document); });
  } else {
    mountAll(document);
  }
})();

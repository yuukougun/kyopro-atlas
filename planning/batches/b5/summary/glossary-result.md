# 用語集への反映の結果（prop45）

用語集 docs/guide/glossary.md：新しい語 21、既存の項への追記・直し 15。定義はすべて自分で書き直した（提案の文はそのまま使っていない）。
prh.yml は変更なし（揺れの規則が要る語がなかった。「多重テストケース」は本文に出ない）。
python3 tools/check_pages.py はエラー 0・警告 0。npm run lint:text はエラー 0。glossary.md の警告は 12 → 13（部分文字列の項の `$S[l, r)$` に「[ の対がない」が付く。既存の半開区間の項と同じ種類）。

§1（b5 glossary の執筆者が置いた 30 語）はすでに用語集にあるので、読み直して残した。直したのは §3 の指摘の分（パフォーマンス・ペナルティ・色・difficulty・レーティング・反例・愚直解）だけ。

採った基準：競技プログラミングで広く使う語で、生成ページ（lists・index・llms.txt・term-index）を除いた本文の 3 ページ以上に出る語か、ページのない基本の語。その語を題にしたページや節がある語は、リンクで足りるので採らない。

## 採った新しい語（21）

| 語 | anchor | 置いた節 | 用語へのリンクを張ったページ |
| --- | --- | --- | --- |
| チェッカー | checker | judge | stress-testing |
| 完答数 | solves | atcoder | contest-strategy |
| バーチャル参加 | virtual-participation | atcoder（anchor は practice-method 案に統一） | problem-sets |
| 色変記事 | color-change-article | slang | practice-method・roadmap |
| 支配（点の） | dominance-point | techniques（状態の支配 #dominance の後） | cdq-divide-and-conquer |
| 補助頂点 | auxiliary-vertex | techniques（超頂点の後） | segment-tree-graph |
| 整数の分割 | integer-partition | domains（集合の分割の後） | なし（twelvefold-way の本文に「整数の分割」の語がない） |
| 恒等置換 | identity-permutation | domains | permutation |
| 逆置換 | inverse-permutation | domains | permutation |
| 上昇階乗・下降階乗 | rising-factorial | domains | generating-function-counting・stirling-first |
| 母関数（指数型母関数も 1 項に含めた） | generating-function | domains | fps-basics（generating-function-counting は母関数が題のページなので張らない） |
| 線形漸化式 | linear-recurrence | domains | なし（linear-recurrence-fast が語を題にしたページで、項からそこへつなぐ） |
| 連分数 | continued-fraction | domains | なし（stern-brocot が題に持つページ。本文 5 ページで使うので採った） |
| 区分線形 | piecewise-linear | domains（凸関数の後） | slope-trick |
| 推移閉包 | transitive-closure | domains（DAG の後） | dilworth-path-cover |
| 交互路 | alternating-path | domains（増加路の後） | general-matching |
| 有向全域木 | arborescence | domains（全域木の後） | matrix-tree-theorem・spanning-tree-advanced |
| 部分文字列 | substring | domains（部分列の後） | interval・subsequence-and-substring |
| 4 近傍・8 近傍 | neighborhood | domains（外積の後） | grid |
| 市松模様 | checkerboard | domains | grid |
| スタック（関数呼び出しの） | call-stack | domains（未定義動作の後） | なし（cpp-environment#stack-depth が持ち主で、項からそこへつなぐ。本文 10 ページが「スタックの上限」を使う） |

節の前置きの並びの説明（domains）を「グラフ（次数〜有向全域木）」「幾何とグリッド（内積〜市松模様）」に直した。

## 既存の項への追記・直し（15）

| anchor | 追記・直し | 用語へのリンクを張ったページ |
| --- | --- | --- |
| counterexample | 「素朴な解」を愚直解へのリンクに、リンク先を stress-testing#procedure に | — |
| naive-solution | リンク先を stress-testing#procedure に | — |
| penalty | リンク先を atcoder-system#ranking に（定義は atcoder-system と一致していることを確かめた） | — |
| rating | atcoder-system#rating へのリンクを足した | — |
| performance | 「参加回数の補正をかける前の」レート、「成績」→「順位」で atcoder-system#rating とそろえた | — |
| color | atcoder-system#colors へのリンク | — |
| difficulty | atcoder-system#difficulty へのリンク（定義は今のままで一致） | — |
| necessary-condition | 必要十分条件の 1 文 | なし（thinking-checklist は #necessary-condition に既にリンク済み） |
| invariant | 不変量（操作で変わらない量）を 1 文で区別した。別の anchor は作らない（thinking/invariant が不変量のページ） | thinking-checklist（「不変量」を #invariant に） |
| indicator | 指示関数の 1 文 | hadamard-transform（「指示関数」を #indicator に） |
| convex-function | 上に凸（凹関数）の 1 文。別の anchor は作らない | なし（monge・alien-dp は #convex-function に既にリンク済み） |
| squarefree | 核（平方因子を除いた核）の 1 文と prime-exponent-vector#squarefree-kernel へのリンク | divisors-and-multiples（「核」を #squarefree に） |
| graph-isomorphism | 根付き木の同型の 1 文 | — |
| contraction | まとめた頂点どうしの辺は「ふつう」消し、自己ループとして残すこともある、とゆるめた | — |
| subsequence | 部分文字列を #substring へのリンクに | — |

注意（メインへ）：graph-modeling の本文の「用語集の定義と違って消さない」は、contraction をゆるめたので言い方が合わなくなった（本文は直していない）。

## 採らなかった語と理由

| 語 | 理由 |
| --- | --- |
| ARC の区分 | atcoder-system#contests が持ち主で 2 ページだけ。年で変わる事実なので 1 か所に置く |
| パフォーマンスの上限 | atcoder-system だけ |
| 解説 AC | 本文 2 ページだけ |
| コーナーケース | 用語集の外では本文 1 ページ（debugging-checklist）だけ |
| 全数テスト | stress-testing だけ |
| バンドル | cpp-macros-template-file#bundling の節があり、リンクで足りる |
| FMA | 2 ページだけ（cpp-environment が定義） |
| プリコンパイル済みヘッダ | C++ の環境の話で cpp-environment・cpp-macros-template-file が扱う。一般の競プロの語ではない |
| localStorage・準備中（stub）・サイン・次の候補 | この教材のサイトの仕組みの語。how-to-use・reverse-index-signs・knowledge-map が定義する |
| ニュートン法（冪級数）・標本点・組立除法・特性多項式・1 の原始 N 乗根・バタフライ・ビット反転の順・relaxed convolution | どれも 1〜2 ページ（fps-basics・lagrange-interpolation・linear-recurrence-fast・fft-ntt・online-convolution）だけ |
| 軌道 | burnside-lemma だけ |
| 左から見える位置 | stirling-first・generating-function-counting の 2 ページで、手法に固有の語 |
| 写像 12 相・行列式・アダマール変換・Monge・乗法的関数・彩色数・mex・パス被覆・下限付きの辺・ミンコフスキー和・併合可能なヒープ・時間軸のセグメント木・部分永続 | その語を題にしたページか節があり、リンクで足りる |
| 置換の符号 | permutation-parity#sign で足りる（提案者自身） |
| 互いに素な経路 | lgv-lemma だけ |
| 順序統計量 | 本文 2 ページ（continuous-probability・kth-element） |
| モンテカルロ法 | randomized のページが扱う |
| ディリクレ積 | multiplicative-function だけ |
| ラプラシアン行列 | matrix-tree-theorem#laplacian の節がある |
| (min,+) 畳み込み | monge だけ |
| 上に凸（別の anchor） | convex-function の項に 1 文を足した |
| Lagrange 緩和 | alien-dp の別名 |
| 中間数・カーマイケル数・証拠（witness）・Montgomery 乗算 | stern-brocot・miller-rabin（Montgomery は fft-ntt も）だけ |
| 非不偏ゲーム・超現実数 | partizan-games が題にするページ。impartial-game の項がすでに非不偏ゲームに触れている |
| Young 図形・標準タブロー・フック長 | young-tableaux だけ |
| 鎖・反鎖 | dilworth-path-cover だけ |
| 花（blossom） | general-matching だけ |
| 循環流 | flow-lower-bounds だけ |
| 指定頂点（ターミナル） | 一般の言い回しで定義が要らない |
| 誘導部分グラフ | auxiliary-tree だけ |
| 優先パス・通りがけ順・期待計算量・連続段・簡潔ビットベクトル | 1〜2 ページだけ |
| 下側の包絡線 | cht が扱う |
| 対蹠点 | advanced-geometry だけ |
| 木の高さ | 一般の語で、使い方がページごとに違う（tree-isomorphism だけが定義を要する） |
| リテラル・節・含意グラフ | two-sat だけ |
| 核（別の anchor） | squarefree の項に 1 文を足した（持ち主は prime-exponent-vector#squarefree-kernel） |
| 不変量（別の anchor） | invariant の項に 1 文を足した（thinking/invariant がページ） |
| 指示関数（別の anchor） | indicator の項に 1 文を足した |
| 必要十分条件（別の anchor） | necessary-condition の項に 1 文を足した |

## 用語へのリンクを張らなかった所

- practice-method の「バーチャル参加」：その行が用語集の項のリンク先（practice-method#speed）そのもの
- cpp-environment の「スタック」：同じく項のリンク先（#stack-depth）がこのページ
- roadmap の「バーチャル参加」：すでに practice-method#speed へのリンクになっている
- generating-function-counting の「母関数」・linear-recurrence-fast・stern-brocot：その語が題のページ
- twelvefold-way：本文に「整数の分割」の語がない
- monge・alien-dp・thinking-checklist（必要十分条件）：同じ anchor へのリンクがページにすでにある

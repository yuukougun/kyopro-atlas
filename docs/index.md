# kyopro-atlas

AtCoder で黄色（レーティング 2000）を目指す人のための、辞書として引く競技プログラミングの教材である。解けなかった問題の言い回しや制約から手法を引き、前提をたどって読み、色ごとの順に学べるようにする。

想定する読者は、ABC の D までは安定して解け、E は時々解ける人である（[この教材の目的と範囲](start/how-to-use.md#purpose)）。どのページも、冒頭の要点の 4 項目（できること・使う場面・計算量・前提）で問題に使えるかを判断し、分からない前提のページを先に読んでから本文と例題に進めるように書いてある（[ページの構成と読み方](start/how-to-use.md#page-anatomy)）。

!!! info "制作中"
    このサイトは制作中である。全ページに本文があり、Issue の対応を進めている。執筆・別の担当の検証・Issue の対応が一通り終わったら、全ページを完成にする（段階の意味は[この教材の使い方](start/how-to-use.md#stub)）。

本文は AI（Claude）で書いている。書き方と確かめ方、出典の扱いは[出典と AI 利用の方針](start/ai-and-sources.md)にある。

## 目的別の入口 {#entrances}

目的に合う見出しを選び、その最初の行のページから読む。

<!-- gen:begin home-links -->
<!-- textlint-disable -->

### 解けなかった問題から引く {#from-problem}

- [辞書としての引き方](start/how-to-use.md#lookup)：言い回し・制約・手法の名前・問題番号などの手がかりごとに、入口を選ぶ表
- 逆引き辞典：[言い回しから](guide/reverse-index-signs.md)・[制約と計算量から](guide/reverse-index-constraints.md)
- [用語の索引](guide/term-index.md)：手法の名前・別名・英語名から引く
- [問題番号の索引](guide/problem-index.md)：本文に載せた問題の番号から、その問題を載せたページを引く

### 色ごとに順に学ぶ {#by-color}

- [色別ロードマップ](guide/roadmap.md)：色ごとに読むページの順と、最近の ABC の位置ごとの頻出手法（進め方は[色ごとに学ぶとき](start/how-to-use.md#by-color)）
- レベル別の一覧：[基礎](lists/level-basic.md)・[水](lists/level-cyan.md)・[青](lists/level-blue.md)・[黄](lists/level-yellow.md)・[発展](lists/level-advanced.md)（[すべての一覧](lists/index.md)）
- [知識マップ](guide/knowledge-map.md)：ページの前提関係をたどる

### 初めて使う {#first-time}

- [この教材の使い方](start/how-to-use.md)：辞書として引く・色ごとに学ぶ・記録を残す・claude.ai に解説を頼む、の 4 つの使い方
- [記法と用語の約束](start/notation.md)：計算量・半開区間・添字・数学の記号など、全ページで使う記法と用語の表記

<!-- textlint-enable -->
<!-- gen:end home-links -->

## 記録について

「解いた」「理解した」の記録は、このブラウザの中だけに保存する。端末の間では同期しない。

ソースは [GitHub のリポジトリ](https://github.com/yuukougun/kyopro-atlas) にある。

# cdq-divide-and-conquer の検証（b4）

対象：docs/ds/cdq-divide-and-conquer.md、snippets/cdq-divide-and-conquer/（dominance.cpp・dominance.yaml）、docs/img/cdq-divide-and-conquer/split.svg。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page cdq-divide-and-conquer`：エラー 0・警告 0（リンク先の anchor `fenwick-tree#variants`・`divide-and-conquer#crossing`・`#pitfalls`・`sweep-line-2d#rectangle-count`・用語集の `offline`・`forced-online` はどれも実在する）
- `python3 tools/check_snippets.py snippets/cdq-divide-and-conquer`：期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- dominance.cpp を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、警告なし。cases の入力（N=0 と 4 点の例）で異常なし
- 作業用の場所で確かめた（リポジトリには置かない）：
    - `count_dominated` を、N ≤ 200・値の幅 1〜50（a は負の値を含む）の乱択 2000 件で愚直な $O(N^2)$ と照らし、すべて一致
    - N = 2×10^5、座標 10^9 までの乱数で 0.23 秒。$O(N \log^2 N)$ の見積もりと合う
    - 本文の長方形クエリの帰着（最初の点を最も前の追加とし、長方形を「$x < X$ かつ $y < Y$」の 4 つの質問に符号付きで分け、同じ $x$ では質問を先にする CDQ）を自分で書き、座標 0〜5・操作 30 個までの乱択 3000 件で愚直と一致
- yaml の cases を手で確かめた：4 点の例 (1,2,3)・(2,3,4)・(2,1,5)・(3,3,5) の答え `0 1 0 3`、同じ点 2 つで `1 1`、互いに比べられない 3 点で `0 0 0`
- `npx textlint`：エラー 0・警告 13（半開区間の `[` の対応・数式を含む文の長さ・読点の数）。97 行の文の長さ 178・読点の数は誤検出だけとは言えない（指摘 4）
- front matter：git diff で、執筆者が変えたのは complexity・stage・updated と sections への library の追加だけ（§2.1 の範囲）。要点の計算量と complexity が一致し、要点の「何ができるか」は summary と同じ文。別名の行に aliases の 4 つがすべてある
- 事実の主張：
    - 漸化式 $T(n) = 2T(n/2) + O(n \log N)$ から $O(N \log^2 N)$、マージソートに替えても BIT の分で log の次数が変わらないこと、段ごとに BIT を初期化すると区間が約 $2N$ 個で $O(N^2)$ になること、メモリ $O(N)$：正しい
    - 「どの組も初めて別の半分に分かれる段で 1 回だけ数える」、同じ $b$ で更新を先にする理由（等号を含むため。狭義なら質問を先）：正しい
    - 辞書順に並べれば支配される異なる点は自分より前に来ること、$a$ だけでソートすると「前の点が後ろの点を支配する組」を数え落とすこと（右から左への寄与を数えないため）：向きを含めて正しい。同じ点を重み付きの 1 点にまとめ、最後に重み − 1 を足す扱いも正しい（上の乱択で確認）
    - 中間順（`cdq(l, m)` → 左から右 → `cdq(m, r)`）の説明：OI Wiki の記述と一致
    - 使い分けの表：2 次元 BIT の 1 回 $O(\log H \log W)$、先読みして各ノードに圧縮した BIT を持たせる方法の 1 回 $O(\log^2 N)$・メモリ $O(N \log N)$：正しい
- 出典：
    - OI Wiki「CDQ 分治」（付録 B のドメイン）：「CDQ 分治的思想最早由 IOI2008 金牌得主陈丹琦在高中时整理并总结，它也因此得名」とあり、本文の名前の由来（高校生のときにまとめた）と一致。3 つの型（点の組の問題・1D/1D の DP の最適化・動的な問題を静的にする）も一致。同じ点をまとめる処理は本文ではなく例のコードにある（本文の「同じ点をまとめる実装もここで確かめられる」は正しい）
    - robert1003 の記事：h1 は「A Simple Introduction to CDQ Divide and Conquer」。枠組みの 4 段（分ける・2 つを解く・左が右へ与える影響・マージ）、漸化式 $T(N) = 2T(N/2) + O(N \log N)$、例（3 次元の半順序・Mokia の長方形和・削除つきの転倒数ほか）。本文の要約と一致
    - Library Checker（GitHub の task.md・info.toml）：point_add_rectangle_sum は $N, Q \le 10^5$、座標・重み $\le 10^9$、同じ座標の点は別の点。重みの和は最大 $2 \times 10^{14}$ ほどで `long long` が要る（本文どおり）。rectangle_add_point_get は長方形 $[l, r) \times [d, u)$ への重みの追加と、点を含む長方形の重みの和。本文の説明と帰着（4 点への $\pm w$ の差分で、1 点の値が原点を角とする長方形の和になる）は正しい
    - F8：本文の文と例は資料と別で、図も独自。問題はない
- 図：`python3 tools/render_svg.py cdq-divide-and-conquer --scale 2` で 360px・720px の PNG を目で確かめた。左の追加 3 個（t=0・2・3）から右の質問 3 個（t=4・6・7）への矢印 9 本が過不足なく、左の質問 t=1 と右の追加 t=5 には矢印がない（本文の 3 種類の組の分け方と一致）。白背景・viewBox と同じ比の width・height（400×230）・sans-serif のテキスト・追加は実線と質問は破線の枠で、色だけに頼らない。360px で t= の文字は約 9px で読める。catalog の visual（static・priority 2）の text を満たす。代替テキストと前後の文で要点が通じる

### 執筆者の未解決の点について

- mlystdcall 氏の記事を外したこと：読んでいない資料を参考に入れないのは正しい。OI Wiki と robert1003 で本文の主張はすべて裏付けられたので、足す必要はない
- `related` に advanced-ds-catalog・inversion-number を足す案：本文の使い分けの表が advanced-ds-catalog へ、仕組みの説明が divide-and-conquer#crossing（転倒数）へリンクしているので、妥当な提案である。メインの判断に任せる
- 用語集の「支配点」の提案：sweep-line-2d#rectangle-count も同じ向き（「$j$ が $i$ に支配される」＝ $j$ の座標がすべて $i$ 以下）で定義しているので、用語集に足すなら両ページの定義と向きを合わせる（本ページの定義と食い違いはない）

## 指摘

1. **直すとよい**｜F2・U3｜#what-it-does の 1 段落目の末尾「3 つになると BIT をもう 1 段重ねたくなるが、座標が大きいと 2 次元 BIT は置けない」｜#alternatives の表では「座標は大きいが先読みできる」なら各ノードに圧縮した BIT を持つ 2 次元 BIT で解けるとしており、「置けない」と言い切ると表と食い違って読める。3 次元の支配点の数え上げは静的なので、圧縮した 2 次元 BIT でも $O(N \log^2 N)$ で解ける｜表の行と照らした｜「座標が大きいと配列の 2 次元 BIT はそのままでは置けない（先読みして圧縮する方法は[代わりの手](#alternatives)）」とする
2. **直すとよい**｜U3・U6｜#what-it-does の 2 段落目「そこで点を $a$ の順に並べ、並びの位置を「時刻」とみなす」｜$a$ が等しい点どうしでは「前にあれば $a_j \le a_i$」は成り立つが、後ろの点が前の点に支配される組（$a$ が同じで $b, c$ が小さい点が後ろにある組）を数え落とす。手順の節で「辞書順」に変わり、理由は #library まで出てこないので、この段落だけを読むと $a$ だけでソートしてよいと受け取れる｜本文の #library の 1 つ目の箇条と照らした｜「点を $(a, b, c)$ の辞書順に並べ（$a$ が等しい点の扱いは[自作するときの要点](#library)）」とする
3. **直すとよい**｜C3・F7｜#procedure の擬似コードの `m = (l + r) / 2` と、取り込んだ core の `int mid = (l + r) / 2;`。また #what-it-does・#library の長方形 $[l, r) \times [d, u)$｜擬似コードの `m` はコードでは `mid` で、コードの `m` は異なる点の個数（`int m = u.size();`）である。長方形の $l, r$ は CDQ の区間 $[l, r)$ と同じ文字で、#library の「長方形は 4 つの質問に分ける」の箇条は CDQ の手順と同じ節にあるので取り違えやすい｜dominance.cpp の 19 行・41 行と本文を照らした｜擬似コードを `mid` にそろえる（または本文の説明で「中央 $m$」を `mid` と言い換える）。長方形は $[x_1, x_2) \times [y_1, y_2)$ のように別の文字にするか、少なくとも #library の箇条で「長方形 $[l, r) \times [d, u)$（CDQ の区間とは別の文字）」と断る
4. **直すとよい**｜U9｜#library の 1 つ目の箇条（97 行。textlint の文の長さ 178・読点の数の警告）｜「$a$ だけでソートすると、$a$ が等しい点どうしでは、前の点が後ろの点を支配する組を数え落とす（右から左への寄与は数えないため）」は条件が重なり、支配の向きを読み違えやすい。数式による誤検出ではなく実際に長い｜textlint の結果｜文を分け、小さな例を添える。例：「$a$ だけでソートすると、$a$ が等しい点の並びが任意になる。たとえば $(1, 2, 2)$ が $(1, 1, 1)$ より前に来ると、後ろの $(1, 1, 1)$ は前の点に支配されるのに数えられない。CDQ は前から後ろへの寄与しか数えないからである。」
5. **直すとよい**｜U6・F3｜#library の Library Checker の 2 行｜手引き §15-5 の形（judge.yosupo.jp へのリンク）がなく、制約も座標だけである。見本の hld もリンクなしなので規則違反ではないが、Point Add Rectangle Sum の $N, Q \le 10^5$ と重み $\le 10^9$ を書けば、`long long` が要る理由（和が $2 \times 10^{14}$ ほど）が本文だけで分かる｜info.toml の N_MAX・Q_MAX・WEIGHT_MAX｜「座標・重みは $10^9$ まで、$N, Q \le 10^5$ なので、重みの和は $2 \times 10^{14}$ ほどになり `long long` で持つ」とし、題名を https://judge.yosupo.jp/problem/point_add_rectangle_sum ・ https://judge.yosupo.jp/problem/rectangle_add_point_get へのリンクにする

## 総合の判定

小さな直しで可。直すべき指摘 0 件、直すとよい指摘 5 件。事実・計算量・コード片（愚直との乱択照合・サニタイザ・2×10^5 の速さ）・図・出典はどれも確かめられた。直すとよい指摘のうち 1・2 は、断片で読んだときの誤解を防ぐもので、優先して直すとよい。

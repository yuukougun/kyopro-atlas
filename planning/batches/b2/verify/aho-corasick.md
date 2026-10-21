# aho-corasick の検証（b2）

対象：docs/string/aho-corasick.md、snippets/aho-corasick/（count・avoid-dp・taboo-greedy）、docs/img/aho-corasick/（failure-links.svg・fail-tree.svg）。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page aho-corasick`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/aho-corasick`：3 本・19 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 3 本を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、cases の入力で警告・実行時エラーなし
- ランダムな突き合わせ（作業用の場所の stress.py、リポジトリには置かない）：
    - count：英字 1〜3 種・|S| ≤ 12・パターン 5 個以下を 300 回。コード内の assert（素朴な数え上げ）がすべて通った
    - taboo-greedy：同じ 300 回で、書き換える位置の集合を全探索した最小値と一致
    - avoid-dp：パターン 3 個以下（a・b、長さ 3 以下）・L ≤ 3 を 60 回、26^L 通りの全列挙と一致
- 本文の具体例を手で確かめた：he/she/his/hers の失敗リンク（sh→h、she→he、his→s、hers→s、ほかは根）、ushers の状態の列（根→s→sh→she→her→hers）と出現（4 文字目 she・he、6 文字目 hers）、失敗リンクの木の止まった回数と部分木の和（he 1・she 1・his 0・hers 1、s 2、根 6）、bc/abcd と abcx の状態の列と link(abc) = bc、確認問題 1（abab の失敗リンクは bab、KMP の π なら ab）
- 主張の裏付け：KMP の π との対応（kmp.md の流儀は π[i] = S[0, i+1) の最長の border の長さなので、長さ j の節点 ↔ π[j−1] で合う）、遷移の式の正しさの議論、BFS 順の必要性（DFS で h の枝を先に潜ると his・hers の処理時に s の行が未処理）、串刺しの貪欲と根に戻す理由。いずれも正しい
- 数値：k = √(2M) = 1000（M = 5×10^5）で N·k ≈ 5×10^8（位置ごとの和を正確に取っても約 4.995×10^8）。表のメモリ 26 × 10^6 × 4 B ≈ 104 MB（約 100 MB で可）。長さの種類 O(√M)
- 本文のリンク先の anchor：kmp#border-chain・kmp#automaton・suffix-array#pattern-count・matrix-power#dp-transition・interval-scheduling#stabbing・glossary#state はすべて実在
- 問題：ap.py で 4 問の実在・タイトル・diff（1625・1726・1744・2560）を確認。要約は台帳と一致し、手法名を含まない
- 図：`python3 tools/render_svg.py aho-corasick` で 360px・720px の PNG を目で確かめた。白背景・viewBox・sans-serif のテキスト・破線と色の併用はよい。720px の PNG は下端の凡例が切れて写ったが、SVG の viewBox（640×510）には凡例が収まっており、360px の画像では全体が出るので、道具の撮り方によるもので図の誤りではない
- 参考の URL：5 件とも check_noai.py で noai の指定なし。題名は下の指摘 1 を除き合う

### 執筆者の未解決の点について

- abc362_g の制約：本文は上限の数値を書かず計算量の式だけにしており、それで問題ない（kmjp の解答コードの配列の大きさ 505050 から、各上限は 5×10^5 程度と推せる）。直しは不要
- abc458_f の「状態は 100 程度」：gdst.dev の記事（https://gdst.dev/posts/abc458_f/ 、noai の指定なし）で制約 1 ≤ N ≤ 10^9・1 ≤ K ≤ 10・1 ≤ |S_i| ≤ 10 を確かめた。状態は 101 個以下で、主張は正しい（指摘 6 で言い方の精度だけ提案）
- 「N = M = 5×10^5 なら約 5×10^8 回」：自作の見積もりとして計算は正しい。特定の問題の制約と読めない書き方になっている
- ikatakos.com は 2026-10-21 の検証時も HTTP 503 で読めなかった

## 指摘

1. **直すべき**｜F9 参考の URL｜参考の 5 行目（274 行）｜`[anoconne「ABC268」（note）]` の題名が記事と違う。記事の h1・title は「AtCoder Beginner Contest反省会 ~入緑編~」で、ABC266 以降の複数のコンテストの記録である（ABC268 Ex - Taboo はその中の 1 節）｜curl で取得した記事の `<title>`・`<h1>`（「AtCoder Beginner Contest反省会 ~入緑編~｜あのこね anoconne」）。手引き §14-24「ブログの題名は記事の h1 を使う」｜`[anoconne「AtCoder Beginner Contest反省会 ~入緑編~」（note）](https://note.com/anoconne/n/n26b5912e1e9c)：力試し abc268_h（Ex - Taboo の節）の、…` のように直す。内容（一致したら数えて根に戻す貪欲・is_word を失敗リンク先から受け継ぐ実装）は記事の解答コードで確かめた

2. **直すとよい**｜G5・F7 図の内容と用語｜fail-tree.svg の題「本文 ushers」と凡例「止：本文を流して止まった回数」｜このサイトで「本文」はページの本文を指し、ページの文章はずっと「テキスト ushers」と書いている。図だけ「本文」で、読者が「ページの本文？」と迷う｜SVG の text 要素 2 か所と本文 73・116 行の表記を比べた｜「テキスト ushers」「止：テキストを流して止まった回数」に直す

3. **直すとよい**｜G3 スマホで読めるか｜failure-links.svg・fail-tree.svg｜幅 360px では viewBox 640・680 が約 0.5 倍に縮み、辺の文字（h・e・s…、15px）が約 8px、凡例・注記（13px）と fail-tree の「止 1／計 1」が約 7px になり、読みにくい｜render_svg.py の 360px の PNG を目で確かめた｜文字を 17〜18px に上げるか、fail-tree は「止・計」の注記を節点の下に回して viewBox の幅を詰める（例えば 520 程度）。failure-links は凡例を 2 段にして幅を詰める

4. **直すとよい**｜U4・C3 本文との一致｜count-occurrences の手順 2（109 行）｜「節点を BFS の逆順に見て cnt[link(v)] += cnt[v]」とあるが、根にも当てはめると link(根) = 根 で cnt[根] が 2 倍になる。コードは `i >= 1` で根を飛ばしている。本文だけを見て実装すると迷う（実害は根の値だけだが、本文とコードがずれる）｜count.cpp 73 行の `i >= 1`｜「根以外の節点を BFS の逆順に見て」とする

5. **直すとよい**｜U3・F2｜build の節の最後の段落（100 行）｜「メモリの制限が厳しいときは、表の型を `int` にそろえ」とあるが、コード片の表はもともと `int` で、何をそろえるのか分からない（long long にしない、の意味なら言い方が逆）。また vector の push_back で節点を増やすと再確保のときに一時的に約 2 倍のメモリを使う点が、約 100 MB の見積もりに効く｜count.cpp 10 行は `vector<array<int, 26>>`｜「表は `long long` でなく `int` で持つ」と書くか、その句を消す。必要なら「節点の数の上限 M + 1 が分かっていれば `reserve` しておく」を足す

6. **直すとよい**｜F5・F3 問題の内容｜練習の方針 ABC458 F（232 行）｜「状態は 100 程度なので」は正しいが、根拠（制約）がない。string-automaton-dp の例題では「長さの総和が 100 以下なので状態は 101 個以下」と書いており、そろえると確かになる｜gdst.dev の記事の制約（K ≤ 10、|S_i| ≤ 10）｜「禁止文字列は 10 個以下・各 10 文字以下なので状態は 101 個以下で、行列累乗が間に合う」とする。台帳 abc458_f の evidence に https://gdst.dev/posts/abc458_f/ を足す提案（string-automaton-dp で既に参考にしている記事）

7. **直すとよい**｜C4 取り込みの範囲｜count.cpp の `core`（本文 93 行で取り込み）｜core が構造体の全体（add_node・insert を含む 54 行）で、要件の「要点の数行と処理の流れ」より大きい。insert は Trie のページの内容の繰り返しである｜snippets/aho-corasick/count.cpp 6〜61 行｜範囲をメンバの宣言（nxt・link・term・order とそのコメント）と `build` だけにする（insert・add_node を範囲の外に出すか、範囲を 2 つに分けて `core` を build にする）。本文 96 行の説明は build だけを指しているので変えなくてよい

8. **直すとよい**｜U8 確認問題｜確認問題 2（250 行）｜「止まった回数を足し上げると出現回数に等しいのはなぜか」は、count-occurrences の「なぜ重複も漏れもなく数えられるか」の段落をそのまま問うていて、答えも同じ文の言い換えになっている｜本文 114 行と答えの文を並べて読んだ｜具体例で手を動かす小問に替える。例：「パターン a・ab・b、テキスト abab で、止まった回数と失敗リンクの木の部分木の和を求め、各パターンの出現回数を答えよ」（答え：a 2・ab 2・b 2。状態は a, ab, a, ab で、b は ab の失敗リンク先なので ab に止まった回数を受け取る）

## 図・動く図について（指摘ではない）

- `<div class="kp-viz" data-viz="aho-corasick" …>` は指示どおり JS をまだ作っていない（catalog の visual は priority 1）。直前の文「次の動く図は…」と直後の段落（ushers の状態の列）は文章だけで通じるので、JS ができるまでの間も読める。JS を作るときは報告の仕様（BFS の前半・走査の後半）で足りる
- 試験（tests/viz/）は存在しないので G1・G2 は未確認

## 台帳への提案（検証で確かめたもの）

- abc268_h：note の記事の Ex - Taboo の節と解答コードで、「一致したら数えて根に戻す」貪欲と、is_word を失敗リンク先から受け継ぐ実装を確かめた。執筆者の提案どおり approach の注記を外し、checked を 2026-10-21 にしてよい
- abc458_f：evidence に https://gdst.dev/posts/abc458_f/ を足す（制約 1 ≤ N ≤ 10^9、1 ≤ K ≤ 10、1 ≤ |S_i| ≤ 10 を確かめた）

## 総合の判定

**小さな直しで可**。事実・計算量・コード（ランダムな突き合わせを含む）・図の値はすべて正しく、説明も「なぜ」まで書けている。直すべきは参考の題名 1 件（指摘 1）だけで、ほかは表記・読みやすさ・取り込みの範囲の改善（直すとよい 7 件）。

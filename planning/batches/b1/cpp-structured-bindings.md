# cpp-structured-bindings の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-structured-bindings.md、snippets/cpp-structured-bindings/ の 20 本（pair-tuple・bindings・hidden-variable・count-ng・map-loop・map-key-ng・if-init・cond-binding-ng・pq-top・pq-top-ok・enumerate-ref・capture・capture-17・placeholder-twice・placeholder-twice-13-ng・tie・tie-swap・exchange・optional・apply の .cpp と .yaml）、docs/img/cpp-structured-bindings/hidden-variable.svg
- 取り込まないコード片（§13.9）：cond-binding-ng・capture-17・placeholder-twice-13-ng（版の注記の裏付けだけ）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections・cpp_std（17）・gcc_min（null）・atcoder（true）は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 20 本・38 回のコンパイルとも期待どおり（g++-13・g++-15）／textlint エラー 0・警告 9（長い見出しを含む文の長さ、コードを含む文の読点・助詞の重複。§13.8 の範囲）
- 図：静的な SVG 1 枚（catalog の visual は static・priority 2）。描画して目で見る道具が手元になく、XML の妥当性と座標だけを確かめた。pq.top() の図は catalog のとおり cpp-undefined-behavior の図に任せた
- 使った出典：参考の節の 10 件（cpprefjp 9・cppreference 1）。どれも付録 B のドメイン。新しく noai を確かめたドメインはない
- 問題：catalog のとおり置いていない（problems: []、problems_note のとおり）

## 台帳への提案

なし（C++ のページは問題を置かない方針）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| ダングリング | dangling | 寿命の切れたもの（消えた要素・一時オブジェクト）を指したままの参照・ポインタ・イテレータ。使うと未定義動作になる。本文では cpp-undefined-behavior へのリンクで済ませたので、用語集へのリンクは張っていない |

## 手引きへの提案

- 骨格の節の題名「pq-top-reference」の末尾「理由は cpp-undefined-behavior のダングリング」は、実際には要素が 2 個以上なら未定義動作ではなく「同じ場所に別の値が入る」だけである（ダングリングになるのは要素が 1 個のとき）。本文はこの区別を書いた。cpp-undefined-behavior#dangling-pq-top を書く執筆者にも同じ区別を伝えるとよい（題名は変えていない）
- research 09 §4.13 の「C++26 の構造化束縛を条件にする書き方は gnu++23 で使えない」は、g++-15 では実は警告つきで受け付ける（`structured bindings in conditions only available with -std=c++2c`）。ただし条件は組全体を bool に変えた値なので、`set::insert` の pair では C++26 でもエラーになる。from_chars の例（C++26 で from_chars_result が bool に変わる）を cpp-string-api などで扱うなら、同じ区別に注意

## front matter・catalog への提案

- 前提のリンク：cpp-range-for・cpp-undefined-behavior・cpp-views-cpp23・cpp-lambda・cpp-comparators・cpp-initialization・cpp-container-idioms・dijkstra は stub なので、節（#dangling-pq-top・#ctad・#references など）ではなくページへリンクした。これらが draft になったら節へのリンクに直すとよい（cpp-structured-bindings#pq-top-reference → cpp-undefined-behavior#dangling-pq-top、#pair-tuple の CTAD → cpp-initialization#ctad）
- related に cpp-container-idioms を足す案（map のキーを変えるときの erase と入れ直しへのリンクを本文に置いた）

## 問題の補充の候補

なし（catalog の方針で C++ のページは問題を置かない）。

## 未解決の点

- AtCoder の GCC 15.2 での挙動（`_` を 2 回使うと警告つきで通る）は、手元の g++-15 での確認と research の記述からの推定で、AtCoder の上では試していない
- 空の optional の `*o` が `-O2` で 0 を返したのは手元の g++-15 の一例で、決まった挙動ではない（本文にもそう読めるように「何事もなく 0 を返した」と書いた）
- 使用量の目安：道具の呼び出し約 25 回、Web 取得は curl で cpprefjp・cppreference の存在確認 10 件と本文の確認 2 件

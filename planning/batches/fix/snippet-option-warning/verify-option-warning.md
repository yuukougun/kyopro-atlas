# verify-option-warning の報告（工程11 グループ snippet-option-warning・Issue #95）

option-warning の担当が直したもの（`tools/check_snippets.py`・`tests/tools/test_check_snippets.py`（新しいファイル）・`tools/README.md` の 22 行・担当の報告 [option-warning.md](option-warning.md)）を、書いた担当とは別に確かめた。作業ツリーは `kyopro-atlas-wt/snippet-option-warning`（ブランチ fix/snippet-option-warning。HEAD 97e3542 に未 commit の変更）。ファイルは直していない（この報告だけを書いた）。git は status・diff・show・log だけを使い、Issue にはコメントしていない。Web は GitHub（`gh issue view 95`・`gh run view 40823490357 --log-failed`）だけで、atcoder.jp・codeforces.com は開いていない。日付：2026-10-29。

- 作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/snippet-option-warning/verify-option-warning`（以下 `<V>`）。直す前の道具は `<V>/old/check_snippets.py`（`git show HEAD:tools/check_snippets.py`）、試したコード片の写しは `<V>/snip/`・`<V>/snip2/`、壊した道具で試験を流すスクリプトは `<V>/harness/mutate.py`
- 手元：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0。Python は 3.10.12（`python3`）と 3.12.15（`.venv/bin/python`。CI と同じ uv の環境）。CPU は 13th Gen Intel(R) Core(TM) i7-13700 で、AVX10.1 はない

## まとめ

| Issue | 判定 | 一言 |
| --- | --- | --- |
| #95 | 直しが要る（1 点。担当の報告の文だけ） | 道具・試験・README は「直したあとの状態」を満たし、直さなくてよい。CI の失敗を手元で再現すると、直す前の道具は NG 2・終了コード 1、直したあとの道具は OK 2・終了コード 0 になった。C のロケール（引用符 '）でも C.UTF-8（‘ ’）でも同じである。すべてのコード片は 1049 片・1371 回のコンパイルで期待と違う 0 だった。注記は 1 つも出ないので、手元の判定は直す前と同じになる。ただし担当の報告は、外す範囲を実際より狭く書いている。flags に直接書いた -m のオプションへの警告でも、cc1plus だけが出すものは外れる（`-mtune=x86-64` で確かめた） |

## 直しが要る点

### 1. 担当の報告が、CPU によらない -m の警告も「今でも NG になる」と書いている（事実と違う）

- **ファイル・行**：`planning/batches/fix/snippet-option-warning/option-warning.md` 67 行（「CPU によって出たり出なかったりするのは -march=native が広げた分だけで、それだけが外れる」）と 101 行（「-mavx10.1 などを直接書いたときはドライバの警告が数えられるので、CPU によらない -m の警告は今でも run で NG になる。そのため今回は足していない」）
- **理由**：ドライバも同じ文を出すのは、`-mavx10.1`・`-mevex512` など一部の -m のオプションだけである。cc1plus だけが出す -m の警告もある。それを flags に直接書くと、警告は CPU によらず出るのに、今回の正規表現で外れる。g++-15 で確かめた例を次に示す
  - `-mtune=x86-64` では、`cc1plus: warning: ‘-mtune=x86-64’ is deprecated; use ‘-mtune=k8’ or ‘-mtune=generic’ instead as appropriate [-Wdeprecated]` の 1 行だけが出る。ドライバの行は出ない。`strings` で見ても、この文は cc1plus（`/usr/libexec/gcc/x86_64-linux-gnu/15/cc1plus`）にだけあり、ドライバ（g++-15）にはない。-mavx10.1・-mevex512 の文は両方にある
  - これを flags に持つ run のコード片（`<V>/snip2/x/tune.*`）は、直す前の道具では「NG 警告が出た」・終了コード 1 だった。直したあとの道具では「OK 1 case 一致」と注記・終了コード 0 になる
  - 今はそういうコード片がない（-m のオプションを flags に持つのは fma-native・fma-off の 2 つだけで、どちらも `-march=native`）。そのため今の判定は変わらず、道具は Issue の定義（「コードの位置を持たない、-m のオプションへの cc1plus の警告」）どおりである。誤っているのは報告の文だけだが、101 行はこの誤りを、案 2（`-march=native` を持つコード片に限る）を採らない理由にしている。メインが案 2 を判断する前提が違ってしまう
- **直し方の案**：
  - 67 行の最後の文を「外すのは、cc1plus の、位置のない、引用符の直後が -m の警告のすべてで、-march=native が広げた分に限らない。`-mavx10.1`・`-mevex512` を flags に直接書けばドライバも同じ文を出すので、今までどおり NG になる。ただし `-mtune=x86-64`（非推奨の警告）のように cc1plus だけが出す警告は、直接書いても外れる。今はそういうコード片はない」の趣旨に直す
  - 101 行の「また、…NG になる。」を「`-mtune=x86-64` のように cc1plus だけが出す -m の警告は、CPU によらなくても外れる。限る案ならこれも数えられるが、今のコード片では結果は同じである」の趣旨に直す。案 2 を採るかはメインの判断に残す
  - コード（`tools/check_snippets.py` 64 行の正規表現）は、Issue の定義どおりなので直さなくてよい

## Issue の「直したあとの状態」との照合

| 直したあとの状態 | 結果 | 確かめたこと |
| --- | --- | --- |
| コードの位置を持たない、-m のオプションへの cc1plus の警告は、`expect: run` の判定で警告に数えない | 満たす | 正規表現 `cc1plus: warning: [‘']-m` を `match` で行の頭に当てる（64・169 行）。CI のログの 4 行（‘ は U+2018。バイト列 e2 80 98 が正規表現と同じ）はどれも当たった。本物の g++-15 の文で、C・POSIX・`env -i`（引用符 '）と C.UTF-8（‘ ’）の両方が当たった |
| 報告には出す | 満たす | 「注記（判定に数えない警告）: …」として、OK でも `-v` なしで出す（347 行）。同じ行は 1 行にまとめる。まとめの下に、回数と CPU の名前の 1 行を出す |
| fma-native・fma-off は AVX10.1 を持つ計算機でも持たない計算機でも OK | 満たす（持つ計算機は近似で確かめた。最後の確認は push のとき） | 持たない計算機（手元）：OK（下の 3）。持つ計算機は、警告を `-Wp,-mavx10.1 -Wp,-mno-avx10.1` で再現して OK（下の 4）。さらに `-march=graniterapids -Wp,-mavx10.1`（`__AVX10_1__`・`__AVX512F__` が立つ）で 2 片をコンパイルした。`cross` は fma-native が `vmulsd`＋`vfmsub132sd`、fma-off が `vmulsd`×2＋`vsubsd` で、手元で実行した出力は yaml の 4 つの case（`+ 1.66533e-18`・`- -1.33227e-17`・`+ 1`・`0 0`）と一致した。警告を数えなくなった後に出力の違いで落ちることも、まずない |
| ほかのコード片の判定は変わらない | 満たす | すべてのコード片で期待と違う 0、注記 0（下の 3）。新しい判定は、外す行がなければ直す前と同じ式になる（`warnings` は「`warning:` を含む行」、`notes` は空）ので、注記が 0 なら判定と出力は直す前と同じである |

## 特に見ること

### 1. 外す範囲は狭いか

- **位置つきの警告は数える**：`x/b.cpp:2:16: warning: unused variable ‘x’ …` も、仮の形 `x/b.cpp:1:9: warning: ‘-mavx10.1’ …` も数える。行の頭が `cc1plus:` でないためである。`<command-line>: warning: ‘FOO’ redefined` も数える（g++-15 の本物の形で、引用符は ‘ ’）
- **-m 以外のオプションの警告は数える**：g++-15 の本物の文で確かめた。`cc1plus: warning: command-line option ‘-std=gnu11’ …`、`… ‘-Wstrict-prototypes’ …`、`cc1plus: warning: ‘-fstack-check=’ and ‘-fstack-clash-protection’ are mutually exclusive; …`、`cc1plus: warning: SSE instruction set disabled, using 387 arithmetics`（`-mfpmath=sse -mno-sse`。-m の話だが文の頭が引用符でない）のどれも数える
- **ドライバの警告は数える**：`g++-15: warning: ‘-mavx10.1’ …`・`g++-15: warning: ‘-mevex512’ …`。CI のコンテナの呼び名 `g++: warning:` も数える
- **ほかの形**：行の頭に空白がある形、`` `-m…' `` の引用符の形、`cc1:`・`lto1:` の形は数える。どれも今のコード片では出ない
- **外れるもの**：cc1plus の、位置のない、引用符の直後が `-m` の警告のすべて。`-march=native` が広げた分に限らない（上の「直しが要る点」1）。Issue の定義どおりなので、コードは直さなくてよい

### 2. 試験は 3 つの場合を確かめているか

- (1) run で -m の警告だけ → OK と注記：`test_run_ok_with_only_m_option_warning`（両方の引用符。2 回出ても注記は 1 行）と、本物のコンパイラの `test_tool` の clean-run
- (2) run で位置つきの警告がある → NG と注記：`test_run_ng_with_code_warning` と `test_tool` の unused-run（`x/unused-run.cpp:1:18: warning: unused variable`）
- (3) warning の期待で -m の警告だけ → NG「警告が出ない」と注記：`test_warning_ng_with_only_m_option_warning` と `test_tool` の clean-warning
- 試験が誤りを捕まえるかを、道具を 12 通りに壊して流して確かめた（`<V>/harness/mutate.py`）。11 通りで落ちた（落ちた件数を括弧に書く）
  - 正規表現の誤り：頭を `\S+:` に広げる（4）。`-m` の条件を落とす（2）。‘ だけにする（3）。' だけにする（10）
  - 判定の誤り：run で -m の警告を数える（5）。warning の期待で -m の警告を数える（2）
  - 注記の誤り：OK に注記を付けない（5）。同じ行をまとめない（5）。「警告が出た」の NG に注記を付けない（2）。注記のある OK を `-v` なしで出さない（2）。まとめの下の行を出さない（1）
  - 落ちなかったのは、`match` を `search` に替えたときだけである。`cc1plus: warning: ‘-m` が行の途中に出る形はないので、実害はない
- 動かす環境による違い
  - g++ がない：本物のコンパイラの 2 件を飛ばし、12 件が OK
  - `g++` が g++-13 だけ（CI のページのジョブの ubuntu-latest のように、g++-15 も版が 15 の g++ もない形）：2 件を飛ばし、12 件が OK
  - `g++` が g++-15 で `g++-15` という名前がない（CI のコンテナと同じ形）：14 件が OK。道具の行は `（g++-15→g++・run）` になり、`result_blocks` が読める

### 3. 警告を期待するコード片と cpp-environment は手元で OK のままか

- `expect: warning` の 21 片（`grep -rl "expect: warning" snippets`。yaml の `expect:` は run 921・compile-error 97・warning 21・crash 1）を `-v` で流した。直す前の道具と直したあとの道具の出力は、秒の数の行のほかは同じだった（並べ替えて diff）。コンパイル 38 回・期待と違う 0
- `snippets/cpp-environment -v`：同じく、直す前と後の出力は秒の数の行のほかは同じだった。コード片 25・コンパイル 33 回・期待と違う 0
- すべてのコード片（直したあとの道具、`-v` なし）：コード片 1049・コンパイル 1371 回・期待と違う 0（283.0 秒、並列 8）・終了コード 0。注記の行は 0
- -m のオプションを flags に持つコード片は fma-native・fma-off だけである（`grep`）。`#pragma GCC target("avx2")` を書いたコード片は 2 つ（cpp-macros-template-file の pragma-after-include・pragma-before-include-ng）ある。どちらも -march=native を持たないので、検査を動かす計算機の CPU では警告が変わらない

### 4. CI のコンテナのロケールでも正規表現が当たるか

- 本物の g++-15（`-march=native -Wp,-mavx10.1 -Wp,-mno-avx10.1`）で、`LC_ALL=C`・`LC_ALL=POSIX`・`env -i`（ロケールの変数なし）は `'-mavx10.1'`、`LC_ALL=C.UTF-8` は `‘-mavx10.1’` になった。手元には en_US.UTF-8・ja_JP.UTF-8 がないので、それらは C に落ちて ' になった。どの形も正規表現に当たる
- CI の失敗を再現した（`<V>/snip/`：fma-native・fma-off の写しの flags に `-Wp,-mavx10.1 -Wp,-mno-avx10.1` を足し、`--compiler g++-15` で流す）
  - `env -i PATH=/usr/bin:/bin python3 …`：コンテナと同じく C のロケールで、PEP 538 で引用符は ‘ ’ になる。直す前の道具は NG 2・終了コード 1、直したあとの道具は OK 2・終了コード 0 で、注記とまとめの下の行が出た
  - `LC_ALL=C` で Python を起動：引用符は '。直す前の道具は NG 2・終了コード 1、直したあとの道具は OK 2・終了コード 0
  - `g++` が g++-15 の別名のとき（`g++-15→g++`）も OK 2・終了コード 0
- 担当の報告にある事実も確かめた。`g++-15 -march=native -###` は `-march=alderlake … -mno-avx10.2 … -mtune=alderlake` に広がる。`-Wp,-mavx10.1` だけでは `__AVX10_1__`・`__AVX512F__` が立つが、`-Wp,-mno-avx10.1` を足すと消える。g++-13 は `unrecognized command-line option ‘-mavx10.1’` のエラーになる。`#pragma GCC target("avx10.1")` では警告が出ない。flags に `-mavx10.1`・`-mevex512` を直接書くと、ドライバと cc1plus の両方が同じ文を出す

## そのほかの検査（書き換えない）

- `python3 -m unittest tests.tools.test_check_snippets -v`：14 件 OK（本物のコンパイラの 2 件も走った）。`.venv/bin/python` でも 14 件 OK
- `python3 -m unittest discover -s tests/tools`：125 件 OK（飛ばした 3 件は Python-Markdown がないための別の試験）。`.venv/bin/python` では 125 件 OK・飛ばしなし
- `python3 tools/check_pages.py`：エラー 0・警告 0（ページは変わっていない）
- `npx textlint tools/README.md`：エラー 2・警告 11 で、行は 31・86・117・130・133・148・152・155・156・157。どれも前からあるもので、直した 22 行への指摘はない。README は lint:text の対象外で、サイトにも出ない
- `git diff --check -- tools/`：空白の誤りなし。新しい試験のファイルも、行末の空白はなく、最後は改行で終わる
- `python3 tools/check_snippets.py -h`：冒頭の説明に足した 31〜34 行が出る。書いてあることは上で確かめた動きと合う
- 生成物・リンク・表・図への影響はない。直したのは tools/ と tests/ と planning/ だけで、`tools/gen_site.py` の対象でもない

## 参考（直さなくてよい点・メインの判断）

1. **外すのを -march=native に限るか**（担当の報告の案 2）：限れば、`-mtune=x86-64` のような、CPU によらず cc1plus だけが出す -m の警告も run で数えられる。今のコード片では結果は同じである。Issue の定義は限っていないので、今のままでも完了の条件は満たす
2. **文の頭が ‘-m でない AVX10 の文**：GCC 15.2 の cc1plus には `Vector size conflicts between AVX10.1 and AVX512, using 512 as max vector size` という文もある（`strings` で確かめた。どの条件で出るかは確かめていない）。これが -march=native で出る計算機があれば、数えられて NG になる。今のところ CI のログにも手元にも出ていないので、今回は扱わなくてよい
3. **最後の確認**：AVX10.1 を持つ計算機での本物の確認は、push の検査が AVX10.1 を持つ計算機に当たったときになる（担当の報告の 1 と同じ）。新しいブランチとして push すれば全数を流す

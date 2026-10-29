# option-warning の報告（バッチ snippet-option-warning）

- 担当の Issue：#95（コード片の検査が、CI の計算機の CPU しだいで -march=native の警告で落ちる）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/snippet-option-warning（ブランチ fix/snippet-option-warning）。git は読むだけで、commit などはしていない
- 直したファイル：`tools/check_snippets.py`・`tests/tools/test_check_snippets.py`（新しく作った）・`tools/README.md`（一覧の表の check_snippets の行だけ）
- コード片（snippets/）・CI の設定（.github/workflows/）・共有のファイル・生成物は変えていない。`tools/gen_site.py` は動かしていない

## #95 -march=native の CPU しだいの警告で落ちる（完了。AVX10.1 を持つ CI の計算機での最終の確認は push のとき）

### 原因（確かめたこと）

1. **CI のログ**（`gh run view 40823490357 --log-failed`）：1371 回のコンパイルのうち落ちたのは `NG cpp-environment/fma-native.cpp（g++-15→g++・run）` と `fma-off.cpp（g++-15→g++・run）` の 2 回だけである。どちらも 1 回のコンパイルで、次の行が 2 回ずつ出ていた。g++-13 では出ていない
   `cc1plus: warning: ‘-mavx10.1’ is aliased to 512 bit since GCC14.3 and GCC15.1 while ‘-mavx10.1-256’ and ‘-mavx10.1-512’ will be deprecated in GCC 16 due to all machines 512 bit vector size supported`
2. **仕組み**：`-march=native` は、ドライバが計算機の CPU を調べて `-march=<名前> -m<機能> -mno-<機能> …` に広げてから cc1plus に渡す（`g++-15 -march=native -###` で見える。手元では `-march=alderlake … -mno-avx10.2 … -mtune=alderlake`）。AVX10.1 を持つ CPU では -mavx10.1 系のオプションが入るので、GCC 15 の cc1plus が上の警告を出す。ドライバは広げたオプションを自分では処理しないので、ドライバの警告（`g++: warning:`）は出ず、cc1plus の行だけが出る
   - flags に `-mavx10.1` を直接書くと、ドライバ（`g++-15: warning: ‘-mavx10.1’ …`）と cc1plus の両方が同じ文を出す
   - `-Wp,-mavx10.1` と書くと、ドライバを通さずに cc1plus にだけ渡る。AVX10.1 を持たない手元の CPU でも、CI と同じ形（cc1plus の行だけ）の警告が出る。後ろに `-Wp,-mno-avx10.1` を足すと、警告は出たまま AVX10.1 が外れる（`-dM -E` で `__AVX10_1__`・`__AVX512F__` が消える）ので、できたプログラムは手元の CPU で動く
   - g++-13 は -mavx10.1 を知らない（`unrecognized command-line option ‘-mavx10.1’` のエラー）
   - `#pragma GCC target("avx10.1")` では、この警告は出なかった
3. **手元**：CPU は 13th Gen Intel(R) Core(TM) i7-13700。/proc/cpuinfo に avx512・avx10 の印はなく、fma はある。g++-13 は 13.4.0、g++-15 は 15.2.0（どちらも Ubuntu の PPA）。手元ではこの警告は出ない
4. **直す前の道具で CI の失敗を手元で再現した**：fma-native・fma-off の写し（作業用フォルダ）の flags に `-Wp,-mavx10.1 -Wp,-mno-avx10.1` を足し、`--compiler g++-15` で流すと、CI と同じ「警告が出た（run は警告なし…）」の NG が 2 件になった

### ロケールと引用符（CI のコンテナ）

- GCC は、ロケールの文字コードが UTF-8 なら引用符に ‘ ’ を、そうでなければ ' を使う。手元で `LC_ALL=C`・`LC_ALL=POSIX`・ロケールの変数なし（`env -i`）では '、`LC_ALL=C.UTF-8` では ‘ ’ になることを確かめた
- CI のコンテナ（gcc:15.2.0。Debian trixie）は LANG などを設定しないので C のロケールだが、CI のログの引用符は ‘ ’ だった。Python 3.7 以降は、C のロケールで起動すると環境変数 LC_CTYPE を C.UTF-8 にし（PEP 538 のロケールの強制）、それが子のプロセスに渡るためである
  - 手元で `env -i PATH=/usr/bin:/bin python3` から g++-15 を動かすと、Python の環境に `LC_CTYPE=C.UTF-8` が入り、引用符は ‘ ’ になった（ログと同じ）
  - `LC_ALL=C` を付けて Python を起動すると強制は働かず、引用符は ' になる
- 直したあとの判定は、どちらの引用符でも同じである。正規表現 `cc1plus: warning: [‘']-m` を行の頭に当てる。試験は両方の形を使い、本物の g++-15 では `LC_ALL=C` と `LC_ALL=C.UTF-8` の両方で確かめる
- docker は使えなかった（WSL の docker は「The command 'docker' could not be found in this WSL 2 distro」）ので、コンテナの中では動かしていない。CI のログの形と、上の Python の仕組みの確認で代えた

### 直したもの

1. `tools/check_snippets.py`
   - L31〜34（冒頭の説明。`-h` でも出る）：run・warning の判定で数えない警告と、今までどおり数える警告を書いた
   - L60〜65：`M_OPTION_WARNING_RE = re.compile(r"cc1plus: warning: [‘']-m")`（`match` で行の頭に当てる）と、注記の頭の文字 `NOTE = "注記（判定に数えない警告）: "`。理由（-march=native の広がり方・引用符）のコメント付き
   - L164〜173 `split_warnings(diag)`：コンパイラの出力の行を（判定に数える警告, 数えない -m のオプションへの警告）に分ける。数える警告は今までどおり「`warning:` を含む行」で、そこから上の正規表現に当たる行だけを外した
   - L176〜186 `cpu_name()`：/proc/cpuinfo の model name（読めなければ空）。最後の注記の行に「この計算機の CPU」として出す
   - L206〜240 `run_one`：`has_warning` を `split_warnings` に替えた。expect が run・warning のときは、外した警告を詳しい行の最後に注記として足す（重ねて出た同じ行は 1 行にまとめ、10 行まで）
     - OK のとき：注記を足す（今までは詳しい行が空）
     - warning の期待で -m の警告しかないとき：「警告が出ない（warning のはず）」の NG にし、注記を足す
     - run で数える警告があるとき：「警告が出た」の NG。数える警告（10 行まで）の後ろに注記を足す
     - 数えない警告のあとで出力の違い・0 以外の終了コード・時間切れの NG になったときも注記を足す（どの計算機で何が出たかが分かるように）
     - crash（警告を問わない）・compile-error・コンパイルエラーは今までどおりで、注記を足さない
   - L334〜360 `main`：注記のある OK の行は -v なしでも出す。最後のまとめの行の下に、注記のあったコンパイルの回数と CPU の名前の 1 行を出す
2. `tests/tools/test_check_snippets.py`（新しく作った。14 件）
   - SplitWarningsTest（3 件）：数えない形（CI の形・C のロケールの形・`‘-mevex512’`）と、数える形（下の表）と、警告でない行（`In function`・`note:`・ソースの行）
   - RunOneTest（8 件）：subprocess.run をまねて、コンパイルの出力を決めて run_one を動かす
     - (1) run で cc1plus の -m の警告だけ（2 回、両方の引用符）→ OK「1 case 一致」、注記は 1 行
     - (2) run で位置つきの警告がある → NG「警告が出た」、詳しい行は位置つきの警告と注記
     - (3) warning の期待で -m の警告だけ → NG「警告が出ない（warning のはず）」と注記
     - そのほか：下の表の数える警告は run でどれも NG、warning の期待で位置つきの警告と -m の警告 → OK と注記、出力が違う NG にも注記、-m の警告がなければ今までどおり、crash・compile-error は今までどおり
   - MainOutputTest（1 件）：一時フォルダの 2 つのコード片を main で検査し、注記のある OK だけが -v なしで出て、最後の行が「注記: … コンパイル 1 回 …」になる
   - RealCompilerTest（2 件。g++-15 か版が 15 の g++ があり、`-Wp,-mavx10.1` に警告を出すときだけ走る）：本物の警告が `LC_ALL=C` でも `C.UTF-8` でも数えない側に入ること。道具の全体（一時フォルダの 3 つのコード片を子のプロセスで検査）で (1)〜(3) を確かめる
3. `tools/README.md` L22（一覧の表の check_snippets の行）：「コードの位置のない -m のオプションへの cc1plus の警告（`-march=native` では計算機の CPU しだいで出る）は、run・warning の判定に数えず注記として出す（#95）。試験は test_check_snippets.py」を足した

### 外す範囲（狭くしたところ）

| 行の形 | 例（g++-15 の本物の文） | 判定 |
| --- | --- | --- |
| cc1plus・位置なし・引用符の直後が `-m` | `cc1plus: warning: ‘-mavx10.1’ is aliased to 512 bit …`、`cc1plus: warning: ‘-mevex512’ will be deprecated in GCC 16 …` | 数えない（注記） |
| 位置（ファイル:行:列）がある | `x/b.cpp:2:16: warning: unused variable ‘x’ [-Wunused-variable]` | 数える |
| cc1plus・-m 以外のオプション | `cc1plus: warning: command-line option ‘-std=gnu11’ is valid for C/ObjC but not for C++`、`cc1plus: warning: ‘-fstack-check=’ and ‘-fstack-clash-protection’ are mutually exclusive; …` | 数える |
| `<command-line>`（-D の再定義） | `<command-line>: warning: ‘_FORTIFY_SOURCE’ redefined` | 数える |
| ドライバ | `g++-15: warning: ‘-mavx10.1’ is aliased …`（flags に -mavx10.1 を直接書いたとき。CPU によらず出る） | 数える |

- 位置のある行は、文が -m のオプションで始まっても数える（試験では仮の形 `x/b.cpp:1:9: warning: ‘-mavx10.1’ …` で確かめた）
- flags に `-mavx10.1`・`-mevex512` を直接書いたコード片は、ドライバも同じ文を出してその行が数えられるので、今までどおり run で NG になる（cc1plus の同じ文は注記になる）。ただし外れるのは、位置のない cc1plus の警告のうち引用符の直後が -m のものすべてで、-march=native が広げた分に限らない。ドライバも同じ文を出すのは、一部の -m のオプションだけである。`-mtune=x86-64`（非推奨の警告）のように cc1plus だけが出す警告は、flags に直接書いて CPU によらず出るときも外れる（直す前の道具で NG、直したあとの道具で OK と注記になる）。そういうコード片は今のところない（下の「検証の指摘への対応」）

### 出力の例（CI と同じ条件の再現。fma-native・fma-off の写しに `-Wp,-mavx10.1 -Wp,-mno-avx10.1`）

```text
OK  cpp-environment/fma-native.cpp（g++-15・run）: 3 case 一致
      注記（判定に数えない警告）: cc1plus: warning: ‘-mavx10.1’ is aliased to 512 bit since GCC14.3 and GCC15.1 while ‘-mavx10.1-256’ and ‘-mavx10.1-512’ will be deprecated in GCC 16 due to all machines 512 bit vector size supported
OK  cpp-environment/fma-off.cpp（g++-15・run）: 1 case 一致
      注記（判定に数えない警告）: cc1plus: warning: ‘-mavx10.1’ is aliased to 512 bit since GCC14.3 and GCC15.1 while ‘-mavx10.1-256’ and ‘-mavx10.1-512’ will be deprecated in GCC 16 due to all machines 512 bit vector size supported

コード片 2・コンパイル 2 回・期待と違う 0（1.2 秒、並列 8、ACL …/third_party/ac-library）
注記: コードの位置のない -m のオプションへの cc1plus の警告を、run・warning の判定に数えなかった：コンパイル 2 回（-march=native では、検査を動かす計算機の CPU しだいで出る。この計算機の CPU は 13th Gen Intel(R) Core(TM) i7-13700）
```

- 直す前の道具では、同じ写しが NG 2・終了コード 1 だった。直したあとは OK 2・終了コード 0。`LC_ALL=C` でも同じで、注記の引用符が ' になる
- CI のように同じ行が 2 回出ても、注記は 1 行にまとめる

### 確かめたこと（書き換えない検査）

- `python3 -m unittest tests.tools.test_check_snippets -v`：14 件 OK（手元は g++-15 があるので、本物のコンパイラの 2 件も走った）
- `python3 -m unittest discover -s tests/tools`：125 件 OK（飛ばした 3 件は、Python-Markdown がないためのほかの試験）。`.venv/bin/python`（3.12.15。CI と同じ uv の環境）でも 125 件 OK（飛ばしなし）
- g++ を PATH から外したとき（CI の pages のジョブに g++-15 がない場合）：本物のコンパイラの 2 件を飛ばし、12 件 OK
- 試験が誤りを捕まえるか（作業用フォルダの写しで正規表現を壊した）：決して当たらない正規表現 → 13 件が落ちる。広すぎる `\S+: warning: [‘']` → 6 件が落ちる（位置・ドライバ・`<command-line>` の例）。-m の条件を落とした `cc1plus: warning: [‘']` → 2 件が落ちる（-fstack-check の例）
- `python3 tools/check_snippets.py snippets/cpp-environment -v`（設定どおり g++-13・g++-15）：コード片 25・コンパイル 33 回・期待と違う 0
- 警告を期待するコード片（`grep -l "expect: warning" -r snippets` の 21 片）を -v で：コンパイル 38 回・期待と違う 0
- どちらも、直す前の道具の出力と、秒の数の行のほかは同じだった（並べ替えて diff）。-v なしの出力も直す前と同じ（手元では注記が出ないので、OK の行は出ない）
- すべてのコード片 `python3 tools/check_snippets.py`（直したあと）：コード片 1049・コンパイル 1371 回・期待と違う 0（280.4 秒、並列 8）・終了コード 0。手元の CPU では -m の警告が出ないので、注記の行も出なかった
- `-m` のオプションを flags に持つコード片は fma-native・fma-off の 2 つだけ（`grep` で確かめた）。`#pragma GCC target("avx2")` を書いたコード片が 2 つあるが、出るとしても位置のある警告なので判定は変わらない
- `npx textlint tools/README.md`：エラー 2・警告 11 で、直す前と同じ（31・86・117・130・133・148・152・155・156・157 行の既存のもの。足した 22 行目への指摘はない）。README は lint:text の対象外
- Web：GitHub（`gh issue view 95`・`gh run view 40823490357 --log-failed`）だけを使った。atcoder.jp・codeforces.com は開いていない

### 残った点・提案

1. **CI での最終の確認**：CI の計算機が AVX10.1 を持つかは割り当てしだいである（run 40823490357 では持っていた）。push の検査で、持つ計算機なら fma-native・fma-off が「OK …」と「注記（判定に数えない警告）: cc1plus: warning: ‘-mavx10.1’ …」の行で出て、まとめの下に CPU の名前が出る。持たない計算機なら今までどおり何も出ずに通る。新しいブランチとして push すれば全数を検査する
2. **さらに狭くする案（していない。採るかはメインの判断）**：外すのを flags に `-march=native`（`=native` の -m のオプション）を持つコード片に限る。今の道具では、`-mtune=x86-64` のように cc1plus だけが出す -m の警告は、flags に直接書いて CPU によらず出るときも外れる。`-mavx10.1`・`-mevex512` なら、ドライバも同じ文を出し、その行が数えられて NG になる。限る案なら、`=native` の -m のオプションを持たないコード片では、cc1plus だけが出す -m の警告も直す前と同じく数えられる。ただし今は -m のオプションを flags に持つコード片が fma-native・fma-off だけ（どちらも `-march=native`）なので、結果は同じである。Issue の「直したあとの状態」も外す範囲を -march=native に限っていないので、今回は足していない
3. **翻訳されたメッセージ（今回の前からの制限）**：gcc の翻訳を入れた環境で LANG=ja_JP.UTF-8 などにすると、「warning:」が訳されて、道具はどの警告も数えなくなる（warning の期待のコード片が NG になる）。手元（LANG=C.UTF-8）と CI では起きない。コンパイラを `LC_ALL=C` で動かせば、文と引用符がどの環境でもそろう。判定は変わらないが NG の行の引用符の見た目が変わるので、今回はしていない
4. **GitHub の注釈（していない）**：最後の注記の行を `::notice::` でも出せば、実行の要約のページに載る。今はログに出すだけである
5. 共有のファイルへの提案はない。手引き §9 と interfaces.md §9 の設定の見本は「run（実行して出力が一致）」とだけ書いていて、今回の変更と食い違わない。fma-native.yaml の注記（FMA を持つ CPU が前提）も直さなくてよい

## 検証の指摘への対応

検証の報告 [verify-option-warning.md](verify-option-warning.md) の「直しが要る点」1 に対応した。この報告の 67 行と 101 行が、外す範囲を実際より狭く書いていたという指摘である。指摘は正しいと判断し、この報告の文だけを直した。道具・試験・README は直していない。作業用フォルダ（以下 `<W>`）は次のとおりである。

```text
/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/snippet-option-warning/fixup-option-warning
```

### 確かめたこと（指摘の事実）

- g++-15（15.2.0）で flags に `-mtune=x86-64` を書くと、次の 1 行だけが出て、ドライバの行は出ない。g++-13（13.4.0）も同じ 1 行を出す。引用符は `LC_ALL=C.UTF-8` で ‘ ’、`LC_ALL=C` で ' になる（下は C.UTF-8 のとき）

  ```text
  cc1plus: warning: ‘-mtune=x86-64’ is deprecated; use ‘-mtune=k8’ or ‘-mtune=generic’ instead as appropriate [-Wdeprecated]
  ```

- `-mavx10.1`・`-mevex512` を直接書くと、ドライバ（`g++-15: warning: …`）と cc1plus の両方が同じ文を出す
- `strings` で探すと、`%<-mtune=x86-64%> is deprecated; …` の文は cc1plus だけにあって、ドライバに見つからない。探したファイルは、cc1plus が `/usr/libexec/gcc/x86_64-linux-gnu/15/cc1plus`、ドライバが `/usr/bin/x86_64-linux-gnu-g++-15` である
- 写しのコード片（`<W>/snip/x/tune`・`<W>/snip/x/avx`・`<W>/snip13/x/tune`・`<W>/snipevex/x/evex`）を、直す前の道具と直したあとの道具で流した。どれも `expect: run` で、出力 `ok` の case が 1 つある。直す前の道具は `git show HEAD:tools/check_snippets.py` の写し `<W>/old/check_snippets.py` である。C.UTF-8 と C のどちらでも結果は同じだった

| flags に足したもの | 直す前の道具 | 直したあとの道具 |
| --- | --- | --- |
| `-mtune=x86-64`（g++-15・g++-13） | NG「警告が出た」・終了コード 1 | OK「1 case 一致」と注記・終了コード 0 |
| `-mavx10.1 -mno-avx10.1`（g++-15） | NG「警告が出た」（ドライバと cc1plus の 2 行） | NG「警告が出た」（ドライバの行は数え、cc1plus の行は注記） |
| `-mevex512`（g++-15） | NG「警告が出た」（ドライバと cc1plus の 2 行） | NG「警告が出た」（ドライバの行は数え、cc1plus の行は注記） |

- 今のコード片の 1049 の yaml の flags を読み、-m のオプションを持つのは fma-native・fma-off だけ（どちらも `-march=native` だけ）と確かめた。既定の flags（`-std=gnu++23 -O2 -Wall -Wextra`）にも -m はない。そのため今の判定は変わらない

### 直したもの

1. 67 行（「外す範囲」の 2 つめの箇条）：最後の文「CPU によって出たり出なかったりするのは -march=native が広げた分だけで、それだけが外れる」を消し、次の趣旨に替えた
   - 外れるのは、位置のない cc1plus の警告のうち引用符の直後が -m のものすべてで、-march=native が広げた分に限らない
   - ドライバも同じ文を出すのは一部の -m のオプションだけである。`-mtune=x86-64` のように cc1plus だけが出す警告は、直接書いても外れる。そういうコード片は今のところない
   - 最初の文の「-mavx10.1 など」は、ドライバも同じ文を出すと確かめた「`-mavx10.1`・`-mevex512`」に狭めた
2. 101 行（残った点・提案の 2「さらに狭くする案」）：「また、…今でも run で NG になる。そのため今回は足していない」を消し、次の趣旨に替えた
   - 今の道具では、cc1plus だけが出す -m の警告は CPU によらなくても外れる。限る案ならこれも数えられるが、今のコード片では結果は同じである
   - 足していない理由は、Issue の「直したあとの状態」が -march=native に限っていないことと、今は結果が同じことにした。採るかはメインの判断に残す（見出しにも書いた）

### 直さなかったもの

- `tools/check_snippets.py` の 64 行の正規表現 `cc1plus: warning: [‘']-m`：直さない。Issue の定義（コードの位置を持たない、-m のオプションへの cc1plus の警告）どおりだからである
- 道具と README の説明の文：冒頭の説明（31〜34 行）、64 行の上のコメント、まとめの下の注記の行（359・360 行）、`tools/README.md` の 22 行を読み直した。どれも外す範囲を「コードの位置のない -m のオプションへの cc1plus の警告」と書く。-march=native は、CPU しだいで出る場合として挙げているだけである。-march=native に限るとは書いていないので、直さない
- この報告のほかの行：外す範囲を書いた 15 行と 60〜64 行の表は、上で確かめた事実と合うので直さない

### 確かめたこと（書き換えない検査。コードは変えていない）

- `python3 -m unittest tests.tools.test_check_snippets -v`：14 件 OK（本物のコンパイラの 2 件も走った）
- `python3 tools/check_snippets.py snippets/cpp-environment`（設定どおり g++-13・g++-15）：コード片 25・コンパイル 33 回・期待と違う 0
- 警告を期待するコード片（`grep -l "expect: warning" -r snippets` の 21 片）：コンパイル 38 回・期待と違う 0
- `npx textlint` でこの報告を見た：エラー 0・警告 5 で、直す前と同じである。警告は 12・14・20・51・54 行の文の長さで、前からある。直した 67・101 行と、足したこの節への指摘はない
- Web は使っていない。atcoder.jp・codeforces.com は開いていない

### 残った点

- 案 2（外すのを `=native` の -m のオプションを持つコード片に限る）を採るかは、メインの判断に残す。今のコード片では結果は同じである

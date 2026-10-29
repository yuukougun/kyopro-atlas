# snippet-ci の報告（バッチ snippet-ci）

- 担当の Issue：#85（コード片 cpp-io/scanf-warning が CI の環境で警告を出さず、全数の検査が落ちる）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/snippet-ci（ブランチ fix/snippet-ci）。git は読むだけで、commit などはしていない
- 直したファイル：`snippets/cpp-io/scanf-warning.yaml`・`snippets/cpp-io/scanf-warning.cpp`・`docs/cpp/cpp-io.md`（L137 の落とし穴 2 だけ）。`tools/check_snippets.py` は変えていない（設定の flags で足りた）
- front matter：cpp-io の `updated` はもとから 2026-10-29（L33）なので変えていない。stage ほかも変えていない
- 共有のファイル・生成物・CI の設定（.github/workflows/）は変えていない。`tools/gen_site.py` は動かしていない

## #85 scanf-warning の検査が CI で落ちる（完了。CI のコンテナでの最終の確認は push のとき）

### 原因

警告が出るかは、コンパイラが `_FORTIFY_SOURCE` を自動で定義するかで決まる。CI のコンテナのコンパイラは定義せず、手元の Ubuntu の g++ は定義する。

1. **glibc の仕組み**：glibc の `<stdio.h>` は `scanf` を `__wur` 付きで宣言する。`<sys/cdefs.h>` の `__wur` は、`__USE_FORTIFY_LEVEL > 0` のときだけ `__attribute__((__warn_unused_result__))` になり、それ以外は空になる。`<features.h>` は、`_FORTIFY_SOURCE > 0` かつ `__OPTIMIZE__`（`-O0` 以外）のときだけ `__USE_FORTIFY_LEVEL` を 1 以上にする
   - 手元（Ubuntu 22.04、GLIBC 2.35-0ubuntu3.15）：cdefs.h L406〜416、features.h L410〜429、stdio.h L421・L437〜445
   - CI のコンテナと同じ Debian trixie の glibc（libc6-dev 2.41-12+deb13u4 を取り出して読んだ）：cdefs.h L577〜587、features.h L433〜452、stdio.h L428・L445〜475（`scanf`・`__isoc23_scanf`・`__isoc99_scanf` のどれも `__wur`）。仕組みは同じ
2. **手元の Ubuntu の g++**：g++-13（Ubuntu 13.4.0-6ubuntu1~22~ppa2）・g++-15（Ubuntu 15.2.0-15ubuntu1~22~ppa2）の `g++ -dumpspecs` に `%{!O0:%{O*:%{!D_FORTIFY_SOURCE=*:%{!U_FORTIFY_SOURCE:-D_FORTIFY_SOURCE=2}}}}` がある。`-O0` 以外の最適化を付けると、自分で `-D_FORTIFY_SOURCE=…` か `-U_FORTIFY_SOURCE` を付けていなければ、ドライバが `-D_FORTIFY_SOURCE=2` を足す。`echo | g++-15 -O2 -dM -E -x c++ -` で `#define _FORTIFY_SOURCE 2` が出て、`-O0` では出ない（g++-13 も同じ）
3. **CI のコンテナ**：ログの版は `g++ (GCC) 15.2.0`（distro の印がない）と `g++-13 (Debian 13.3.0-16) 13.3.0`
   - gcc のイメージは、docker-library/gcc の `15/Dockerfile`（GitHub の API で読んだ）のとおり `buildpack-deps:trixie` の上で GCC をリリースの tarball からビルドしている（`configure --build=… --disable-multilib --enable-languages=c,c++,fortran,go`。distro のパッチなし）。今の master は GCC_VERSION 15.3.0 だが、CI のログの環境変数は `GCC_VERSION=15.2.0` で、同じテンプレートから作られたものである
   - Debian の g++-13（trixie の g++-13-x86-64-linux-gnu 13.3.0-16 を取り出した）のドライバ `x86_64-linux-gnu-g++-13` には、`strings` で FORTIFY の文字列が 1 つもない。手元の Ubuntu の g++-13 のドライバには上の spec がある
4. **CI の失敗**：週ごとの検査（run 40131318108、2026-10-24）も、新しいブランチの push で全数を検査した check.yml（run 40787874252 fix/cross-links、40762530377 feat/page-template）も、1371 回のコンパイルのうち落ちたのは `NG cpp-io/scanf-warning.cpp（g++-13・warning）` と `（g++-15→g++・warning）` の 2 回だけだった

### docker で確かめられなかった理由と、代わりに確かめたこと

- docker は使えなかった。WSL の `docker` は「The command 'docker' could not be found in this WSL 2 distro」（Docker Desktop の WSL 連携が無効）で、Windows の docker.exe は「failed to connect to the docker API at npipe:////./pipe/dockerDesktopLinuxEngine」（エンジンが動いていない）だった。Docker Desktop は起動していない
- 代わりに、手元の g++-13・g++-15 の前処理とコンパイルを、Debian trixie の glibc 2.41 のヘッダで行った（`-nostdinc` の後に libstdc++・GCC のヘッダ、trixie の `usr/include` を `-isystem` で並べ、カーネルのヘッダだけ手元を `-idirafter` で足す。リンクはせず `-c -o /dev/null`）。CI の「自動で足さない」状態は、Ubuntu の spec を止める `-U_FORTIFY_SOURCE` で再現した

| flags（`-std=gnu++23 -Wall -Wextra` に足すもの） | g++-13 | g++-15 | 意味 |
| --- | --- | --- | --- |
| `-O2 -U_FORTIFY_SOURCE` | 警告 0 | 警告 0 | 直す前の CI と同じ（ログと一致） |
| `-O2 -D_FORTIFY_SOURCE=2` | 警告 1 | 警告 1 | 直した後の設定。`__USE_FORTIFY_LEVEL 2`・`__GLIBC_MINOR__ 41` |
| `-O0 -D_FORTIFY_SOURCE=2` | 警告 0 | 警告 0 | 最適化なしでは出ない（glibc 2.41 は `#warning` も出さない） |

- 出た警告はどれも `ignoring return value of 'int scanf(const char*, ...)' declared with attribute 'warn_unused_result' [-Wunused-result]` の 1 つだけである
- 注意：`-fsyntax-only` ではこの警告が出ない（手元のヘッダでも 0 件、`-c` なら 1 件）。GCC はこの警告を構文解析の後の段階で出すためである。最初の再現は `-fsyntax-only` で行って 0 件になり、取り違えかけた

### 直したもの

1. `snippets/cpp-io/scanf-warning.yaml`
   - L5：`flags: "-std=gnu++23 -O2 -Wall -Wextra -D_FORTIFY_SOURCE=2"` を足した（既定の flags に `-D_FORTIFY_SOURCE=2` を足しただけ。`-ftrivial-auto-var-init=zero`・`-march=native` を足したほかのコード片と同じ書き方）。`compilers: [g++-13, g++-15]`・`expect: warning`・cases は変えていない
   - L1〜3：理由のコメント（警告の条件、Ubuntu は自動で足し CI のコンテナと Debian の g++-13 は足さないこと、#85）
   - 手元の Ubuntu の g++ では、`-D_FORTIFY_SOURCE=2` を自分で付けると spec が足さなくなるので、「redefined」の警告は出ない（`-D_FORTIFY_SOURCE=3` を付けても出なかった）
2. `snippets/cpp-io/scanf-warning.cpp` L7：コメントを「`-O2` と `-D_FORTIFY_SOURCE=2` で「戻り値を無視した」警告が出る（Ubuntu の g++ は自動で足す）」にした。コードは変えていない。このコード片は確認用で、本文には取り込まれていない（範囲 core はどのページも使っていない）
3. `docs/cpp/cpp-io.md` L137（printf・scanf の節の落とし穴 2）：「手元の Ubuntu では `-O2` で警告が出た」だけだったのを、どの環境で出るかが分かる形にした。前の文は 137 字で textlint の文の長さの警告が出ていたので、文を分けた
   - 環境によっては、戻り値を使わないと `-O2` で警告（文面はもとのまま）が出る
   - glibc（Ubuntu・Debian の C の標準ライブラリ）の `_FORTIFY_SOURCE` は関数に安全のための検査を足すマクロで、これを有効にして最適化したときだけ `scanf` に印（`warn_unused_result`）が付く
   - 手元の Ubuntu の g++-13・g++-15 は `-O0` 以外の最適化で `-D_FORTIFY_SOURCE=2` を自動で足すので `-O2` だけで出た（`-O0` では出ない）。Debian の g++-13 と Docker のイメージ `gcc:15.2.0` の g++ は自動で足さないので、`-D_FORTIFY_SOURCE=2` を付けたときだけ出る
   - 「動作には影響しない」を「警告が出ても `scanf` の動作は変わらない」にした（間に `_FORTIFY_SOURCE` の説明が入り、「動作」が FORTIFY の検査を指すと読めるため）。glibc は `scanf` を fortify しない（2.35・2.41 の bits/stdio2.h に scanf がない）ので、FORTIFY の有無で `scanf` の動作は同じである
   - AtCoder については書いていない。cpp-environment のオプションの一覧に `-D_FORTIFY_SOURCE` はないが、AtCoder の GCC が自動で足すかは分からないためである

### 確かめたこと（書き換えない検査）

- `python3 tools/check_snippets.py snippets/cpp-io --compiler g++-15`：コード片 19・コンパイル 19 回・期待と違う 0
- `python3 tools/check_snippets.py snippets/cpp-io --compiler g++-13`：コード片 16・コンパイル 16 回・期待と違う 0
- `python3 tools/check_snippets.py snippets/cpp-io`（両方）：コード片 21・コンパイル 35 回・期待と違う 0。scanf-warning は g++-13・g++-15 とも「警告あり（期待どおり）・1 case 一致」
- 直す前の設定でも手元では通っていた（Ubuntu の spec のため）。CI で落ちる状態の再現は上の表の 1 行目
- `python3 tools/check_pages.py --page cpp-io`：エラー 0・警告 0
- `npx textlint docs/cpp/cpp-io.md`：エラー 0・警告 6。どれも直す前からあるもの（L41・L302 の文の長さ、L64・L190 の「に」、L131 の「が」、L290 の「で」）。直す前は 7 で、L137 の文の長さの警告は文を分けて消えた
- Web：GitHub の API（docker-library/gcc の Dockerfile）と deb.debian.org（`python3 tools/check_noai.py --robots` で noai の指定なし・robots.txt なし）だけを使った。.deb の 2 つ（libc6-dev 2.41-12+deb13u4、g++-13-x86-64-linux-gnu 13.3.0-16）は作業用フォルダに取り出して読んだだけで、中のものは実行していない。atcoder.jp・codeforces.com は開いていない

### 残った点・提案

1. **CI のコンテナでの最終の確認**：手元ではコンテナを動かせなかったので、`-D_FORTIFY_SOURCE=2` で CI でも警告が出ることは、trixie のヘッダでの再現までしか確かめていない。push すると check.yml の「コード片（変わったもの）」が scanf-warning（.cpp・.yaml が変わった）を検査するので、そこで通るかを見てほしい。新しいブランチとして push すれば全数（1049 片）を検査し、これまでの 2 件の NG が消えるはずである。万一落ちたら、本文 L137 の「Debian の g++-13 と … `-D_FORTIFY_SOURCE=2` を付けたときだけ出る」の文も見直す
2. **手引き §9 への提案**（メインが反映）：「警告や動作が `_FORTIFY_SOURCE` に左右されるコード片（glibc の関数の戻り値を使わない警告、FORTIFY の実行時の検査など）は、flags に `-D_FORTIFY_SOURCE=2` を明示する。手元の Ubuntu の g++ は `-O0` 以外で自動で足すが、CI のコンテナ（gcc:15.2.0）と Debian の g++-13 は足さない（#85）。逆に `expect: run` のコード片は手元の方が警告が増えるだけなので、手元で通れば CI でも通る」
3. **check_snippets.py で環境をそろえる案（していない）**：既定の flags で FORTIFY を固定すれば（`-U_FORTIFY_SOURCE` を足して CI に合わせる、など）、どのコード片も手元と CI で同じ条件になる。ただし 1049 片すべての条件が変わり、AtCoder の GCC が FORTIFY を自動で足すかも分からないので、今回は個別の設定で直した。そろえるかはメインの判断
4. **本文に書かなかった事実**：`(void)scanf("%d", &n);` と書いても、g++-13・g++-15（手元、`-O2`）では警告が消えなかった（GCC の `warn_unused_result` は void へのキャストで消えない）。読者が試しがちなので本文に足す価値はあるが、確かめるコード片を別に作る必要があり（担当のファイルの外）、足していない
5. **付録 B（確かめたドメイン）**：deb.debian.org を使った（本文の資料ではなく、検証のためのパッケージの取得だけ）。記録に足すかはメインの判断

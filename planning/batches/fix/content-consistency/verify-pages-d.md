# 検証：content-consistency の pages-d（math のページ）

- 検証した Issue：#68・#69・#77（math の手で書いたページ 30 個）。2026-10-29
- 作業ツリー：kyopro-atlas-wt/content-consistency（ブランチ fix/content-consistency）。ファイルは直していない

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #68 平文のまま出る数式・法の文字 | 合格 | 0 |
| #69 節の並び | 合格 | 0 |
| #77 1 次関数の表記 | 合格 | 0 |

## 流した検査

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --field math -v` | エラー 0・警告 0（書き方の 7 種を含む） |
| `python3 tools/fix_problems.py --check` | 直すべき行 0（問題の行の要約は台帳と同じ） |
| `npx textlint docs/math/*.md`（index.md を除く） | エラー 0・警告 633 |
| `mkdocs build -d <作業用>/site` → `render_pages.py --field math` | エラー 0・警告 1（miller-rabin#deterministic-bases の幅を超える表。前からあり、範囲外） |

## 確かめたこと

### #69 節の並び

- 30 ファイルそれぞれで、直す前と後の行を並べ替えて突き合わせた（`diff <(git show HEAD:f | sort) <(sort f)`）。並べ替えだけのページ（divisor-count-bound・divisor-enum・ext-gcd・mod-pow・modint・segmented-sieve・sieve-eratosthenes・spf-sieve など）は updated の行のほかに違いがなく、節の中身は落ちていない。ほかのページも違いは報告に書かれた文の書き換えだけだった
- front matter の sections の anchor の順が本文の h2 の順と同じことを、フェンスの中を除いて全 41 ページで確かめた（食い違いなし）。modint の sections の並べ替え（… acl-internals → connections）も本文と同じ
- 動かした節をまたぐ位置の参照：ext-gcd・floor-sum・mod-pow の #acl、floor-quotient-enum の #vs-others、modint の 3 節、ほかの使い分け・確認問題を動かした 16 ページで「次の節」「前の節」「上の」「下の」「後で」などを拾って読んだ。ext-gcd:158「前の節の $b$」（linear-congruence → min-solution）、gcd-properties:90「次の節の Sparse Table」、exponent-mod:81、segmented-sieve:54・67・95、multiplicative-order:178、floor-sum:87、floor-quotient-enum:59 は、どれも動かしていない節どうしで意味が変わらない
- 方針の折りたたみの題：convolution-ntt・floor-sum・gaussian-elimination・gcd-properties・linear-recurrence-fast・matrix-power・xor-basis で、「練習の方針」は練習問題の節、「力試しの方針」は力試しの節の中にあり、取り違えはない

### #68 平文の欄・本文の数式・法の文字

- summary・signs・complexity の書き換えはどれも元の式と同じ意味（和の範囲 i + j = k、i XOR j = k、i = 1..N、i = 0..n−1、d = 1..M と k = 1..⌊M/d⌋、j < i、K = 1..N、i = 1..N と j = i..N など）。linear-recurrence-fast の signs は Σ を c_1 a_(n−1) + … + c_K a_(n−K) に展開したもので同じ。上付き・下付きのかっこは手引き §6 のとおり
- 題・要点の KaTeX（exponent-mod の $3^{10^{18}} \bmod 7$、fft-ntt の $469762049 = 7 \times 2^{26} + 1$、floor-sum の証明の題 $\lfloor (y_{\max} - jm)/a \rfloor$ など）は元の文と同じ式で、render_pages で KaTeX のエラー 0
- 問題の行（10 行）は `fix_problems.py --check` が 0 で、台帳の summary と同じ
- 法の文字：mod-arithmetic:94 は問題文の法 998244353 にした（同じ折りたたみの問題文が 998244353 と書いている）、mod-inverse:114 は同じ囲みの inv_mod の $m$ にそろえた、geometric-series-mod:175 は「法を $m$ として」を足した。どれも start/notation#numbers の m に合う
- euler-phi の `$$`：前後を空行にし、前の文を「次の式になる。」で閉じた。文の意味は同じで、描画のエラーもない

### #77 表記

- math（index.md を除く）に残る漢数字の「一次」は、一次合同式・一次不定方程式・一次漸化式・連立一次方程式・一次独立・一次従属（gaussian-elimination:269）の用語と、floor-sum の aliases と別名の行（方針どおり変えない）だけ。prh.yml の規則（連立一次方程式・Vandermonde の行列式）とも合う
- floor-sum の見出し「応用の型：bit ごとの popcount・1 次式の mod の積」は anchor（applications）を変えておらず、sections の title も同じ文字

## 残った点（直しは要らない）

- `gen_site.py --check` は生成物が古い（summary・signs・sections を変えたため）。メインが作り直す。作り直したあとに docs/math/index.md の textlint を見る（担当の提案のとおり）

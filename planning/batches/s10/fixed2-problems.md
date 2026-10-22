# 工程10 2巡目：問題の補充（complement-graph-bfs・floor-sum・steiner-subtree）

decisions.md「練習の節がない complement-graph-bfs・floor-sum・steiner-subtree」に従った。台帳 data/problems.yaml は変えていない（練習に置ける AtCoder の問題を確かめられなかったため）。commit・gen_site.py の書き込みはしていない。図・コード片は変えていない。

## 直したもの

- **graph/complement-graph-bfs**：`## 練習問題 {#practice}` の 1 文を「例題以外で練習に置ける AtCoder の問題は確認できなかった。」に改め、§15-5 の `### Library Checker` に Connected Components of Complement Graph を置いた（問題文は library-checker-problems の task.md で確かめた。front matter の verify にもある）
- **math/floor-sum**：練習の節がなかったので、例題と力試しの間に `## 練習問題 {#practice}` を足した。同じ 1 文と、`### Library Checker` に Sum of Floor of Linear・Min of Mod of Linear（どちらも task.md で確かめた。verify にある）。Min of Mod of Linear には、[x mod m < c] の式（#mod-to-floor）で「余りが X 未満の個数 = f(N,M,A,B) − f(N,M,A,B−X)」を判定にして X を二分探索する方針（1 ケース O(log² M)、B−X が負になる点の注意）を添えた。根拠として参考に sounansya「floor sum アルゴリズムとその一般化」（Qiita。check_noai で指定なし）を足した
- **tree/steiner-subtree**：前の担当（fixed2-graph）が置いた §16-5 型の 1 文「例題のほかに練習に置ける問題は確認できなかった。」をそのまま残した（Library Checker にも対応する問題がない）

## 探して使わなかった候補

- floor-sum：ABC193 E（diff 1948）は opt-cp.com/abc193e/ が二分探索と floor sum で解くと検索結果にあるが、opt-cp.com が名前解決できず（check_noai・WebFetch とも ENOTFOUND）noai も中身も確かめられない。ABC372 G（2925）・ABC402 G（3381、一般化 floor sum）・ARC123 E（2828）・ARC182 E（3098）は黄の練習には難しく、力試しはすでに 3 問ある。AOJ 3217（drken の floor_sum カテゴリ）は Pick の定理が主で floor sum は別解の部品なので外した。PAST202209（第12回）の floor_sum の問題は第三者の解説で問題を特定できなかった
- complement-graph-bfs：補グラフの BFS を使う AtCoder の問題は ABC319 G（例題）以外を第三者の解説で見つけられなかった（sotanishy のライブラリの verify も ABC319 G だけ）
- steiner-subtree：ABC368 D（例題）の類題を探したが、木の上の指定頂点の最小部分木を使う問題を第三者の解説で確かめられなかった。ABC364 G は一般のグラフのシュタイナー木（graph の章）で別物

## 提案

- 台帳の担当（またはメイン）が opt-cp.com 以外の第三者の解説で ABC193 E の floor sum 解を確かめられれば、floor-sum の practice に `{id: floor-sum, role: practice}` を足せる（台帳には crt の practice として既にある）

## 検査

- check_pages.py：エラー 0・警告 0
- fix_problems.py --check --page（3 ページ）：直すべき行 0
- textlint（3 ページ）：エラー 0（足した行に max-comma の警告が 2 件残る。§14-25 で警告は残してよい）

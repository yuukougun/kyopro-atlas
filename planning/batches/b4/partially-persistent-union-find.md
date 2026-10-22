# partially-persistent-union-find の報告（b4）

- 書いたファイル：docs/ds/partially-persistent-union-find.md、snippets/partially-persistent-union-find/usage.{cpp,yaml}、docs/img/partially-persistent-union-find/find-at-time.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（コード片の中で素朴な方法との突き合わせを 300 回 assert）、textlint エラー 0・警告 2（33 行は骨格の summary の文の長さ、105 行は骨格の見出しの二重かっこ。どちらも front matter 由来なので残した）
- 図：find-at-time.svg を render_svg.py で 360px・720px の PNG にして目で確かめた。visual は priority 2 の static なので動く図の置き場は置いていない
- 使った出典：drken1215（Union Sets・Stamp Rally の解説）、noshi91.hatenablog.com/entry/2018/05/30/191943、judge.yosupo.jp/problem/persistent_unionfind（問題文は GitHub の library-checker-problems の task.md で確かめた）。新しいドメインはない

## 台帳への提案

- code_thanks_festival_2017_h｜evidence｜noshi91 などの 2 つ目の裏付けを足したい（今は drken の 1 件だけ。§15-6 の目標に届かない）。今回は 2 つ目を見つけられなかった
- 変更なし：agc002_d・code_thanks_festival_2017_h の summary はそのまま使った

## 用語集への提案

- 部分永続｜partial-persistence｜過去のどの版も読めるが、更新は最新の版にだけ行う永続データ構造の性質。版が一直線に並ぶので、版を時刻と言い換えられる（persistent-data-structures#partial-vs-full が持ち主。用語集に入れるかはメインの判断）

## 手引きへの提案

- Library Checker に直接の問題がない発展の概要では、近い問題が解けない理由（今回は完全永続の Persistent UnionFind）を一言書く、と §13-10 に添えると迷わない

## 問題の補充の候補

- なし。ap.py と第三者の解説で ABC の候補を探したが、部分永続 Union-Find が想定の ABC の問題は見つからなかった（catalog の problems_note のとおり）。Library Checker では persistent_unionfind（https://judge.yosupo.jp/problem/persistent_unionfind）が近いが完全永続で、本文では代わりの手の節で触れるだけにした

## 未解決の点

- 例題の出力（最後まで別の集合のとき）は drken の記事で -1 と確かめたが、本文では「問題の指定」とだけ書いた（問題文を転載しないため）
- 「2 頂点から tm の小さい側を登る」方法の正しさは、本文の論法（道の上で時刻が真に増える）と、コード片での二分探索版との突き合わせ（n ≤ 7、m ≤ 9、300 回）で確かめた。第三者の資料では確かめていない
- 関連の rollback-union-find・merge-process-tree は stub なのでページへのリンクにした。draft になったら節へ張り替える

## 検証の指摘への対応

- 指摘 1・2・3・5：直した（確認問題 2 のずれ方を 2 つに分けた、経路圧縮の例と確認問題 1 に図の要点を括弧で補い #what-it-does へリンク、登る方法の tm に一言添えた、ng = −1 の理由を足した、凡例を「時刻 2 以下のほかの辺」にした。赤の凡例を長くすると赤い辺と重なるので灰色の側を直した）
- 指摘 4（draft のページへのリンクを節へのリンクに）：採らなかった。指摘どおり、メインがバッチの終わりに張り替える作業に任せる

## 台帳への提案（検証の後）

- code_thanks_festival_2017_h・agc002_d の checked に 2026-10-22 を入れる（検証役の提案と同じ）

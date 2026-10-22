# 工程10 直し：ds・cpp で残したもの（s10）

直し担当（ds・cpp）が直さずに残した項目。ほかの分野・共有ファイルに要る直しと、メインの判断が要るもの。

## ほかの分野・共有ファイルに要る直し

- **basics/divide-and-conquer.md の related**（audit-relations ## ds の最後の行）：sparse-table の related には divide-and-conquer を足した。逆向き（divide-and-conquer の related に sparse-table を足す）は basics の分野なので残した
- **tree/root-path-dfs.md L151〜161**（audit-relations：rollback-union-find との重なり）：持ち主を rollback-union-find#no-path-compression にし、root-path-dfs 側を 2〜3 文とリンクに縮める直しは tree の分野。記録する 2 つの値の言い方（root-path-dfs「par[s] と r の大きさ」、rollback-union-find「根 2 つの par」）は、root-path-dfs 側を縮めるときにそろえるとよい。rollback-union-find 側は今のまま
- **summary の「上位ビット」（提案）**：docs/ds/binary-trie.md L13 と docs/ds/wavelet-matrix.md L13 の summary を「上位 bit」に直す提案（付録 A。summary は生成物の索引・ds/index.md にも載るので、メインが直して gen_site.py で作り直す）。本文・要点・見出し・sections の title は直した
- **union-find の frequency_evidence**（audit-facts）：「前提として 17 ページに届く（直接 9）」は今は 18（直接 9）。audit-facts ## shared の frequency_evidence の作り直しで一緒に直す（値 A は変わらない）
- **trap.jp**（audit-shared ## cpp）：2026-10-22 に `python3 tools/check_noai.py https://trap.jp/post/2589/ https://trap.jp/post/1224/` をやり直したが、今回は SSL の証明書の検証に失敗して取得できなかった（self-signed certificate。手元の環境のプロキシの影響の可能性がある）。付録 B の「確かめられなかった」のままにし、別の環境でやり直す。使っているのは cpp-environment L304、cpp-macros-template-file L315・L316（ほかに string/hashing-for-sets・tree/static-top-tree）
- **wavelet-matrix の参考の miti-7.hatenablog.com**：付録 B のはてなブログの一覧にない（今回の監査の対象外。気づいたので記録）。check_noai で確かめて付録 B に足すか確かめる

## メインの判断が要るもの

- **advanced-ds-catalog L155「HLD・重軽分解」**（audit-facts）：名前から引く一覧の表なので別名を置くのは意図どおりとも読める。直すなら「HL 分解（HLD）」
- **mo-algorithm の別名「クエリ平方分割」**（audit-relations）：aliases と別名の行から外す案だが、guide/term-index.md L2719 の手書きの項「『クエリの平方分割』と『クエリ平方分割』」が、この 2 語を別のページに振り分ける説明として使っている。外すなら term-index のこの項も直す（guide の分野）。残すなら今のままでよい。直していない
- **rollback-union-find L102 と graph/offline-dynamic-connectivity の重なり**（audit-relations）：持ち主が未決（handoff-b4b5 §2）。offline-dynamic-connectivity を持ち主に決めたら、rollback-union-find の #offline-dynamic-connectivity の節を要点 3 行とリンクに縮める（anchor は残す。Library Checker の練習の文もこの節を指している）
- **cpp-undefined-behavior の prerequisites の cpp-environment**（audit-relations ## cpp の後半）：level が null のページを前提にしてよいかの判断。cpp-environment の related への cpp-views-cpp23 の追加は済ませた
- **wavelet-matrix の anchor `usage` → `library`**（audit-structure）：§16-2 に合わせるには anchor を変える必要があるが、今回の直しの決まり（anchor を変えない）に従い変えていない。変えるなら、sections の anchor・見出しの `{#usage}`、ds/persistent-data-structures.md L171 の `wavelet-matrix.md#usage`（本文のリンクはこの 1 か所。ほかは生成物の docs/index/ds.md）を一緒に直し、localStorage の鍵の読み替えが要るかを確かめる。資料の節 `{#resources}` は足した
- **global-offset の next-steps**（audit-structure）：中身の節 #to-lazy-segment-tree が同じ役をしているので現状でよいか、定型の節を足すか
- **lazy-segment-tree の `## 落とし穴 {#pitfalls}`**（audit-structure）：見本のページなので、境界の節（L170）で足りるかをメインが決める
- **cpp の 60 字を超える見出し 23 か所**（audit-structure ## cpp の最後）：目安なので直していない。直すなら anchor を残して見出しと sections の title を同時に短くする
- **台帳の summary と本文の要約の言い回し**（audit-shared ## ds、abc206_d・abc157_d・abc278_d）：## shared (3) の要約の規則が決まってから。今回 union-find-applications に足した abc206_d の要約は台帳の本体の summary をそのまま使った

## 提案

- **weighted-union-find の FM の acl**：「ACL では」の囲みは本文の 1 文に直した（§14-4）。ACL の `dsu` で頂点を 2 倍にする使い方を囲みで載せたいなら、FM の acl に `dsu` を足す

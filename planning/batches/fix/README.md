# 工程11：Issue の対応（2026-10-29〜）

GitHub の Issue（#4〜#77。調査は 2026-10-29）を、バッチに分けて直す。メインのセッションが順序と一貫性を決め、直す・検証するはサブエージェントが行う（CLAUDE.md）。

## 進め方

1. メインが、バッチの担当ごとに直す範囲（Issue とファイル）を決めて頼む。担当どうしで同じファイルを触らない
2. 担当は、自分のファイルだけを直し、書き換えない検査で確かめ、報告を `planning/batches/fix/<バッチ>/<担当>.md` に書く
3. 別の担当が検証する（書いた本人は検証しない）。検証の報告は `verify-<担当>.md`
4. 指摘を直す（直すのは書いた担当でよい）
5. メインが front matter・台帳・手引き・用語集など共有のものを反映し、`tools/gen_site.py` を流し、検査をすべて通してから、グループのブランチに commit・push して pull request を作り、マージする。完了の条件を満たした Issue は pull request の本文の `Closes #N` で閉じる（#3 は閉じない）。一部だけ直したものは `Refs #N`

## 担当への共通の指示

- 直す担当：[brief-fix.md](brief-fix.md)
- 検証する担当：[brief-verify.md](brief-verify.md)

## グループ（ブランチ）

グループごとに作業ツリーを分ける。f1 だけはメインの作業ツリーで直した。Issue の列は当初の割り振りで、作業がグループの間で移ったもの（#57 は lookup、#66 は patterns、#70 は cross-links、#75 は entry-points の pull request で閉じた）がある。実際に閉じた pull request は GitHub の記録による。

| グループ（ブランチ） | Issue | 状態 |
| --- | --- | --- |
| f1（fix/broken-display） | #50 図 28 枚・#51 動く図 4 つ・#31〜#33 表示の崩れ、#61 のうち静的な検査 | 完了（#80） |
| minor-content（fix/minor-content） | 軽微な修正の本文：#4・#11〜#24・#26〜#30・#34〜#41・#43・#44・#47・#48 | 完了（#78） |
| generated-pages（fix/generated-pages） | 生成ページの軽微な修正：#25・#42・#45・#46・#49 | 完了（#81） |
| page-template（feat/page-template） | ページの部品：#9 段階と更新日・#10 報告の入口・#54 上の帯の節の印・#56 関連の表示・#73 404 | 完了（#82） |
| problem-display（fix/problem-display） | 問題の行の表示：#5 diff —・#76 参考値 | 完了（#86） |
| code-and-library（feat/code-and-library） | コードと自作ライブラリ：#8・#72 完全なプログラムへのリンク・#53 確認用の問題・#62 mint・#63 グラフのコードの約束・#64 自作の示し方 | 完了（#90） |
| lookup（feat/lookup） | 引く仕組み：#52 検索・#59 知識マップ・#60 絞り込み | 完了（#93） |
| mobile-layout（fix/mobile-layout） | #55 スマホの表と数式 | 完了（#94） |
| entry-points（feat/entry-points） | 入口：#6 問題番号の一覧・#7 トップページ・#58 分野の入口・#57 使い分けへの戻り道・#65 考察と発想リスト | 完了（#88） |
| content-consistency（fix/content-consistency） | 多ページの書き方：#68 平文の数式・#69 節の並び・#70 重なりの持ち主・#77 表記・#91 見出しの題名 | 完了（#97） |
| cross-links（fix/cross-links） | ページ間のつながり：#66 題材別の行・#67 DP の高速化のハブ・#71 学ぶための資料 | 完了（#83） |
| progress（feat/progress） | #74 進捗の拡張・#1 お気に入り | 完了（#89） |
| circle-page（feat/patterns） | #75 円環のページ | 完了（#84） |
| render-check（feat/render-check） | #61 描画の崩れの検査（ヘッドレスの Chrome） | 完了（#92） |
| policy-draft（docs/policy-draft） | #2 出典と AI 利用の方針 | 完了（#79） |
| snippet-ci（fix/snippet-ci） | #85 コード片 scanf-warning を CI の環境で通す | 完了（#87） |
| snippet-option-warning（fix/snippet-option-warning） | #95 -march=native が広げた -m のオプションの警告 | 完了（#96） |
| drop-copies-rule（fix/drop-copies-rule） | #2 の続き：問題文の写し・訳と引用を読まない約束を外す | 完了（#98） |
| wrap-up（fix/wrap-up） | 全ページの段階を完成にする・トップページの「制作中」を外す・frequency の付け直し | 完了 |

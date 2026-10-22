# cayley-pruefer（ラベル付き木の数え上げ・黄）の問題の補充

- 現状：例題 1（abc290_f）・練習 0・力試し 2（abc303_h・arc106_f）
- 目標：練習 2〜4 問

## 確かめた候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付けの URL |
| --- | --- | --- | --- | --- | --- | --- |
| nyc2015_5 | E. ひも | なし（ap.py、2015-01-04） | practice（anchor: degree-sequence） | 完全グラフの全域木のうち、各頂点 v の次数がちょうど a_v（1〜3）であるものの数を 10^9+7 で割った余りで求める問題である（N ≤ 10^5）。 | 次数の和が 2N−2 でなければ 0、そうでなければ Prüfer 列での出現回数が a_v − 1 になる列の数 (N−2)!/Π(a_v − 1)! を階乗の前計算で O(N) で求める。 | https://drken1215.hatenablog.com/entry/2020/10/25/132900 ・ https://drken1215.hatenablog.com/entry/2023/09/07/000919 |

- nyc2015_5 は data/problems.yaml に既にあり、pages に `{id: cayley-pruefer, role: practice}` を持つが、本文の練習の節にはまだない（探す順の (2) に当たる）。台帳の checked は null なので、上の 2 つの記事で問いと方針を確かめた日（2026-10-22）を入れるよう提案する
- difficulty がないので帯は判断できない。式をそのまま使う問題なので、黄の帯より易しい練習として置くのがよい

## 探したが見つからなかったもの

- (1) b1・b3・b5 の candidates.md と b3/cayley-pruefer.md の補充の候補：nyc2015_5 だけ（上）。abc303_h はすでに力試し、abc290_f は例題
- (2) data/problems.yaml で cayley-pruefer を pages に持つのは abc290_f・abc303_h・arc106_f・nyc2015_5 の 4 問で、本文にないのは nyc2015_5 だけ
- (3) 第三者の解説：drken のカテゴリ「プリューファー(Prüfer)コード」「全域木の数え上げ」はどちらも 5 記事で、AtCoder の問題は nyc2015_5・abc303_h・arc106_f だけ（残りは Codeforces の問題と一般の記事）。Web 検索（日本語・中国語）でも、このページの手法を主に使うほかの AtCoder の問題を第三者の解説で確かめられなかった。検索結果に atcoder.jp の公式解説（arc167・arc171・agc070 など）が出たが、noai のため開いておらず、第三者の解説もないので候補にしない
- b3 の報告どおり、ap.py の題名検索（Tree・Degree・Spanning など）からも見つかっていない

## 結論

- 確かめた候補は 1 問（nyc2015_5、practice）。練習は合わせて 1 問にとどまり、目標の 2〜4 問に届かない。無理に足さない
- 新しく使ったドメインはない（drken1215.hatenablog.com は付録 B にある）

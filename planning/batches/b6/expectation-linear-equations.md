# expectation-linear-equations（閉路のある期待値）の問題の補充

- ページ：docs/comb/expectation-linear-equations.md（レベル 青）
- 今の問題：例題 arc174_c・abc333_f、練習 abc189_f、力試し abc224_g（これらは候補から除いた）
- 結果：確かめた候補は 1 問（力試し）。青の帯（1600〜1999）の練習の候補は見つからなかったので、練習は abc189_f の 1 問のままである

## 候補

| 問題 ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付け |
| --- | --- | --- | --- | --- | --- | --- |
| abc271_g | G. Access Counter | 2323（黄） | challenge | 1 日の 24 個の時刻ごとに担当が決まり、各時刻に担当が決まった確率でアクセスするとき、N 回目のアクセスが青木君である確率を求める。 | 次のアクセスの時刻への遷移確率では「丸 1 日アクセスがない」ことが何度でも繰り返すので、その分を公比 P（1 日アクセスがない確率）の等比級数 1/(1 − P) で閉じ（または 24 状態の連立方程式を掃き出し法で解き）、得た 24×24 の遷移行列を行列累乗で N 乗する | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/1001_abc271 （等比級数で閉じる）・https://kmjp.hatenablog.jp/entry/2022/10/04/1000 （24 時刻の循環する系を行列にして mod 998244353 で掃き出す） |

- abc271_g は台帳 data/problems.yaml に既にある（pages は probability-dp のみ）。このページの pages に `{id: expectation-linear-equations, role: challenge}` を足す提案である。本文では [等比級数で閉じる](#geometric-series) と [一般の連立方程式](#linear-system) の両方の適用例になる
- 黄の帯なので練習ではなく力試しとした。主役は行列累乗で、閉路を閉じるのは遷移確率を作る前段である点を本文の方針に書くとよい
- ikatakos の記事は 1 − P が mod で 0 にならないかの注意にも触れている（[b = 1 のとき](#infinite) と対応する）

## 調べたが候補にしなかった問題

| 問題 ID | difficulty | 外した理由 |
| --- | --- | --- |
| arc016_4（軍艦ゲーム） | 2683（参考値） | スタートに戻る選択があり答えを仮定して二分探索する型（kmjp https://kmjp.hatenablog.jp/entry/2013/11/06/0900 ）。帯から遠く、同じ型の abc224_g が力試しにある |
| abc263_e・abc350_e・abc314_e・abc300_e・dp_j・tdpc_ball | 1354〜1722 ほか | 閉路は自己ループだけで、移項で済む（expected-value-dp の担当） |
| dwango2015_prelims_3・m_solutions2019_c | 1953・2038 | atcoder-tags の Expected-Value の一覧から拾ったが、引き分けで同じ状態にとどまる自己ループ（幾何分布）だけで閉路が長くない。第三者の解説は開いていない |
| abc360_e | 1249 | 状態は前に進むだけで閉路がない |

## 探した範囲

- (1) b1・b3・b5 の candidates.md と各バッチの報告：b2 の報告は「見つからなかった」、b3 の candidates.md は「次の調査で探す」とあるだけで、具体的な候補はなかった
- (2) data/problems.yaml：このページを pages に持つのは abc189_f・abc224_g・abc333_f・arc174_c の 4 問で、すべて本文にある。期待値・確率で「未知数・方程式・等比・繰り返し」を含む問題を台帳から拾い、abc271_g を見つけた
- (3) 第三者の解説：drken の「期待値」「回数の期待値」「連立一次方程式」の分類、paruma184 の「期待値DPと確率DPの例」（新しいドメイン。check_noai で noai・noimageai の指定なしを確かめた。挙げている閉路の問題は abc333_f・arc174_c で、どちらも本文にある）、atcoder-tags の Expected-Value-DP・Expected-Value のタグ、ap.py の題名の検索
- 途中で WebSearch の回数の上限に達したため、検索での追加の調査はできていない。ABC の 400 番台以降（2025〜2026 年）は題名からしか探せておらず、取りこぼしがありうる

## 新しく確かめたドメイン

- paruma184.hatenablog.com：check_noai の結果は HTTP 200、X-Robots-Tag なし、meta robots="max-image-preview:large"、noai・noimageai の指定なし（2026-10-22）

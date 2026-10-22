"""tools/frequency.py の小さな試験。python3 -m unittest discover -s tests/tools"""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools"))
import frequency as fq  # noqa: E402


def C(recent=(), reach=0, direct=0, old=0):
    return fq.Counts(recent=list(recent), reach=reach, direct=direct, old=old)


class ClassifyTest(unittest.TestCase):
    def test_thresholds(self):
        self.assertEqual(fq.classify(C(recent=["abc451_d", "abc452_e"])), "A")
        self.assertEqual(fq.classify(C(reach=13, direct=1)), "A")
        self.assertEqual(fq.classify(C(reach=12, direct=4, old=2)), "C")
        self.assertEqual(fq.classify(C(reach=6, direct=5)), "A")
        self.assertEqual(fq.classify(C(recent=["abc451_d"])), "B")
        self.assertEqual(fq.classify(C(old=3)), "B")
        self.assertEqual(fq.classify(C(old=2)), "C")

    def test_manual_only_raises(self):
        self.assertEqual(fq.decide("modint", C())[0], "A")
        self.assertEqual(fq.decide("modint", C(recent=["abc451_d", "abc452_e"]))[1],
                         "recent 2（abc451_d・abc452_e）・前提として届くページなし・古い ABC 0 問")


class EvidenceTest(unittest.TestCase):
    def test_forms(self):
        self.assertEqual(fq.evidence(C(old=2)), "recent 0・前提として届くページなし・古い ABC 2 問")
        self.assertEqual(fq.evidence(C(recent=["abc473_e", "abc455_e"], reach=7, direct=3, old=3)),
                         "recent 2（abc455_e・abc473_e）・前提として 7 ページに届く（直接 3）・古い ABC 3 問")
        ids = [f"abc4{50 + i}_d" for i in range(1, 8)]
        self.assertTrue(fq.evidence(C(recent=ids)).startswith("recent 7（abc451_d・abc452_d・abc453_d・abc454_d・abc455_d・abc456_dほか）"))


class CountTest(unittest.TestCase):
    def test_old_counts_skip_recent_unconfirmed_and_other_contests(self):
        ledger = {
            "abc100_d": {"contest": "abc100", "status": "確認済み", "pages": [{"id": "x", "role": "practice"}]},
            "abc460_d": {"contest": "abc460", "status": "確認済み", "pages": [{"id": "x", "role": "example"}]},
            "abc101_d": {"contest": "abc101", "status": "未確認", "pages": [{"id": "x", "role": "practice"}]},
            "arc100_d": {"contest": "arc100", "status": "確認済み", "pages": [{"id": "x", "role": "practice"}]},
        }
        self.assertEqual(fq.old_counts(ledger)["x"], {"abc100_d"})

    def test_recent_counts_once_per_problem(self):
        rc = fq.recent_counts([{"id": "abc451_e", "pages": ["union-find", "union-find#weighted", "mst"]}])
        self.assertEqual(rc["union-find"], {"abc451_e"})

    def test_reach(self):
        rev = fq.prereq_graph({"b": ["a"], "c": ["b#sec"], "d": ["a", "c"]})
        self.assertEqual(fq.reach_of(rev, "a"), {"b", "c", "d"})
        self.assertEqual(len(rev["a"]), 2)


class RewriteTest(unittest.TestCase):
    def test_only_two_lines_change(self):
        src = "---\nid: x\nfrequency: C\nfrequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問\nstage: draft\n---\nfrequency: C\n"
        out = fq.rewrite(src, "B", "recent 0・前提として届くページなし・古い ABC 3 問")
        self.assertEqual(out, "---\nid: x\nfrequency: B\nfrequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問\nstage: draft\n---\nfrequency: C\n")

    def test_missing_line(self):
        self.assertIsNone(fq.rewrite("---\nid: x\nfrequency: C\n---\n", "B", "e"))

    def test_quotes_when_needed(self):
        self.assertEqual(fq.yaml_scalar("a: b"), '"a: b"')
        self.assertEqual(fq.yaml_scalar("recent 0・古い ABC 1 問"), "recent 0・古い ABC 1 問")


if __name__ == "__main__":
    unittest.main()

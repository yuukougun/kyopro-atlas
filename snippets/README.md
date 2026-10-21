# コード片

本文に取り込むコード片の完全なプログラムを、ページの id ごとのフォルダに置く（planning/interfaces.md §9）。

- `snippets/<page-id>/<name>.cpp`：完全なプログラム。本文に取り込む範囲を `// --8<-- [start:名前]` 〜 `// --8<-- [end:名前]` で囲む
- `snippets/<page-id>/<name>.yaml`：設定（compilers・flags・expect・cases）
- 検査：`python3 tools/check_snippets.py`
- `_ci-smoke/` は CI のコンテナ（gcc:15.2.0）と同梱の ACL v1.6 で通ることを確かめるための1本で、ページからは取り込まない

#!/usr/bin/env python3
import shutil
import subprocess
import sys
from pathlib import Path

def main() -> int:
    if len(sys.argv) not in (2, 3):
        print("usage: package_addon.py <addon-folder> [output-zip]")
        return 1

    root = Path(sys.argv[1]).resolve()
    out = Path(sys.argv[2]).resolve() if len(sys.argv) == 3 else root.with_suffix(".zip")

    validator = Path(__file__).resolve().parent / "validate_addon.py"
    result = subprocess.run([sys.executable, str(validator), str(root)])
    if result.returncode != 0:
        print("error: validation failed; refusing to package")
        return result.returncode

    if out.exists():
        out.unlink()

    archive_base = str(out.with_suffix(""))
    shutil.make_archive(archive_base, "zip", root.parent, root.name)
    print(f"created: {archive_base}.zip")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())

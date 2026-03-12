#!/usr/bin/env python3
import json
import sys
from pathlib import Path

REQUIRED = ["addon.json", "panel.json", "layout.json"]
OPTIONAL = ["presets.json"]

def load_json(path: Path):
    with path.open("r", encoding="utf-8") as handle:
        return json.load(handle)

def main() -> int:
    if len(sys.argv) != 2:
        print("usage: validate_addon.py <addon-folder>")
        return 1

    root = Path(sys.argv[1]).resolve()
    if not root.exists() or not root.is_dir():
        print(f"error: addon folder not found: {root}")
        return 1

    missing = [name for name in REQUIRED if not (root / name).exists()]
    if missing:
        print("error: missing required files:", ", ".join(missing))
        return 1

    addon = load_json(root / "addon.json")
    panel = load_json(root / "panel.json")
    layout = load_json(root / "layout.json")
    presets = load_json(root / "presets.json") if (root / "presets.json").exists() else None

    warnings = []
    errors = []

    if not addon.get("id"):
        errors.append("addon.json must contain a non-empty id")
    if not addon.get("name"):
        errors.append("addon.json must contain a non-empty name")
    if int(addon.get("schemaVersion", 0)) != 1:
        warnings.append("schemaVersion is not 1; runtime compatibility may fail")

    accent = panel.get("accentPalette", {})
    for k in ("primary", "secondary"):
        if k not in accent:
            warnings.append(f"panel accentPalette missing {k}")

    known = {
        "param_chant", "param_temple", "param_halo", "param_drone",
        "param_motion", "param_lightdark", "param_mix", "param_output", "param_freeze"
    }

    controls = layout.get("controls", [])
    if not controls:
        errors.append("layout.json must contain at least one control")
    for idx, control in enumerate(controls):
        param = control.get("param")
        if param not in known:
            errors.append(f"layout control {idx} references unknown param: {param}")
        if "x" not in control or "y" not in control:
            errors.append(f"layout control {idx} is missing x/y")

    if presets:
        names = set()
        for idx, preset in enumerate(presets.get("presets", [])):
            name = preset.get("name", "").strip()
            if not name:
                errors.append(f"preset {idx} missing name")
                continue
            if name in names:
                warnings.append(f"duplicate preset name: {name}")
            names.add(name)

    print(f"validated: {root.name}")
    if warnings:
        print("\nWarnings:")
        for w in warnings:
            print(" -", w)
    if errors:
        print("\nErrors:")
        for e in errors:
            print(" -", e)
        return 2

    print("\nOK: addon package passed structural validation.")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())

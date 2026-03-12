# Seller Checklist

Use this before selling a community AETHER add-on.

## Required

- unique addon id
- clear addon name
- valid `addon.json`
- valid `panel.json`
- valid `layout.json`
- optional but recommended `presets.json`
- original art assets
- passes `python scripts/validate_addon.py <folder>`

## Strongly recommended

- include at least 3 presets
- provide 1 square preview image
- explain whether the theme is celestial / subterranean / haunted / etc.
- test fallback behavior by removing one asset temporarily
- zip package with `scripts/package_addon.py`

## Not allowed

- fake "official" branding
- changing core parameter IDs
- shipping modified core binaries as official AETHER
- malicious scripts or executables

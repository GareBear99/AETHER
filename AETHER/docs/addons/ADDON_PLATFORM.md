# AETHER Add-on Platform

AETHER supports panel-theme add-ons that can safely restyle the plugin and ship preset bundles without altering the canonical DSP contract.

## Allowed

- panel artwork
- orb / glyph visuals
- control layout
- palette changes
- preset banks
- copy / title variants

## Not allowed

- changing canonical parameter IDs
- changing automation meaning
- replacing the core DSP chain inside official core binaries
- impersonating the official AETHER core release

## Required files

- `addon.json`
- `panel.json`
- `ui/layout.json`
- optional `presets/presets.json`

## Validation rules

- schemaVersion must equal 1
- addon type must equal `panel-theme`
- every control must map to a known parameter id
- missing art should fall back safely to default core visuals
- invalid add-ons must fail closed and revert to Default theme

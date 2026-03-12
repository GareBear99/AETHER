# Schema Reference

This folder pairs with `Schemas/*.schema.json`.

## Files
- `addon.json`: identity and compatibility contract
- `panel.json`: palette/art/animation profile
- `ui/layout.json`: positions and styles for controls
- `presets/presets.json`: optional addon-local preset bank

## Fallback behavior
- Missing background -> Default panel background
- Missing orb art -> core orb renderer
- Missing knob ring -> stock ring
- Missing presets -> addon loads without preset bank
- Bad control param -> ignored + warning

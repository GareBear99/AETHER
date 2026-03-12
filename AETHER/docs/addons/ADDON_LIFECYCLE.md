# Addon Lifecycle

1. Creator copies `AddonSDK/Template`
2. Creator edits `addon.json`, `panel.json`, `ui/layout.json`, optional `presets/presets.json`
3. Creator runs `scripts/validate_addon.py <path>`
4. Creator packages addon into a zip
5. User installs into `Themes/<AddonName>`
6. AETHER validates on boot
7. If valid, addon becomes available in registry
8. If partially invalid, AETHER logs warnings and falls back safely

## Non-negotiables

- Canonical parameter IDs cannot be changed
- Engine DSP cannot be overridden by addons
- Addons cannot claim official status without approval

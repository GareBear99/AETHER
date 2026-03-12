# AETHER — Ethereal Choir Atmosphere Designer

AETHER is the missing aura layer in the suite.

- **FreeEQ8** sculpts
- **BassMaid** anchors
- **GlueMaid** binds
- **SpaceMaid** expands
- **WaveForm** visualizes
- **RiftSynth** generates
- **AETHER** enchants

AETHER is designed to turn ordinary audio into sacred, haunted, heavenly atmosphere through a focused macro workflow and a mystical UI that feels like an instrument instead of a utility panel.

## Core identity

AETHER is not another generic reverb.

It is a **choir atmosphere designer** built around four internal behaviors:

1. **Formant Choir Bloom** — pseudo-vocal resonance and spectral chant lift
2. **Halo Overtone Layer** — upper harmonic bloom and shimmer air
3. **Invocation Engine** — hold/freeze capture for evolving choir beds
4. **Temple Space** — dark cathedral depth and sacred tail shaping

## Macro controls

- **Chant** — vocal/choir presence
- **Temple** — chamber size and reverb scale
- **Halo** — overtone bloom and upper sheen
- **Drone** — sustain and undercurrent
- **Motion** — slow life and movement
- **Light / Dark** — emotional voicing tilt
- **Mix** — dry/wet balance
- **Output** — final level trim
- **Invocation Freeze** — signature capture/hold mode

## Mystical GUI direction

This package includes the upgraded mystical GUI pass:

- center **Aether Orb** visual focus
- rune ring / sacred halo treatment
- dark-violet + gold colour language
- ritual panel framing instead of generic boxes
- bloom meters named for musical feel instead of raw engineering only

See `docs/GUI_DIRECTION.md` and `assets/AETHER_GUI_PREVIEW.png`.

## Addon platform

AETHER is also prepared as a **panel/addon platform**.

Official and community-made add-ons can safely override visual presentation and ship preset banks without breaking the core DSP or automation contract.

### What add-ons may change

- panel art
- orb art
- knob/trim skinning
- glyph sets
- colour palette
- control placement
- preset banks
- panel copy / titles

### What add-ons may **not** change

- canonical parameter IDs
- core DSP routing
- automation/state compatibility
- protected AETHER trademarked core identity

### Included in this package

- **Agartha** sample add-on theme
- **Addon SDK template** for creators
- schema files for manifests and layouts
- loader / validator / fallback scaffolding in `Source/Addons/`
- validation script for JSON package checks

See `docs/addons/` for the full creator model.

## Pricing / release model

AETHER core is intended as a **$3 flat-rate plugin**.

Add-ons can be sold separately, such as:

- **Agartha** — $1
- future community panel themes — creator priced
- free community skins / banks — allowed

No DRM.
No activation.
No nonsense.

<details>
<summary>Can I pirate AETHER?</summary>

Yeah.

If you found AETHER on GitHub, a forum, or a weird zip that appeared from the mist, that's fine.

It costs **$3** if you want to support development.
If you do not have the $3, just use it.
If you like it later, come back and buy it.

Make music.

</details>

## Build

```bash
cmake -B build -S .
cmake --build build --config Release
```

## Add-on validation

```bash
python scripts/validate_addon.py Themes/Agartha
python scripts/validate_addon.py AddonSDK/Template
```

## Honest status

This package is **repo-complete and product-structured**, but it is **not honestly release-certified until you compile and test it locally**.

Still required in the real world:

- compile against JUCE
- test AU / VST3 / Standalone
- tune presets by ear
- confirm automation/state restore
- verify CPU and gain behavior in real hosts
- export screenshots and demos for release

## Target release feel

AETHER should feel like:

- ghost choir
- sacred bloom
- black cathedral air
- living invocation hold
- cinematic, mystical, immediate inspiration


## Addon Platform Status

The addon platform is complete at the **repo/spec architecture** level:

- core/addon boundary defined
- schemas locked
- validation script included
- packaging script included
- template SDK included
- fallback model documented

Final commercial completion still requires local JUCE compile integration and DAW testing.

## Runtime integration pass

This v5 package adds the pieces that were still missing from the addon platform:

- `layout.json` and `presets.json` included for **Default**, **Agartha**, and the **AddonSDK template**
- editable SVG placeholder assets for orb/background replacement
- `RuntimeThemeState` and `ThemeBridge` scaffolding to connect the addon host to the editor/UI state
- stronger packaging/validation scripts so community sellers can make clean $1 panel packs without breaking the core contract

See:

- `docs/RUNTIME_INTEGRATION_AUDIT.md`
- `docs/addons/EDITOR_THEME_FLOW.md`
- `docs/addons/SELLER_CHECKLIST.md`

## Still not honest to call release-finished

This package is now **complete at the repo / architecture / platform-contract level**.

It is **still not truthfully binary-finished** until you do these on your machine:

- compile the JUCE targets
- connect the runtime theme bridge into the real editor paint/layout flow
- test theme switching and preset-bank loading in host
- run AU/VST3/Standalone QA
- tune sound and presets by ear
- export final screenshots / demos / release assets

That is the final gap between **platform-complete** and **commercially shipped**.

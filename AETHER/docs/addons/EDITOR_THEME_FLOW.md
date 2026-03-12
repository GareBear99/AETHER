# Editor Theme Flow

Recommended safe flow:

1. Editor constructs `AddonHost`
2. Host scans `Themes/`
3. Host activates `Default` or last-safe theme
4. `RuntimeThemeState` mirrors the active host state
5. `ThemeBridge` converts runtime state into editor colours/copy
6. Editor paints using bridged colours and flavor text
7. If the user switches themes:
   - validate target package
   - load target package
   - rebuild runtime state
   - repaint editor
   - preserve parameter IDs and automation contract
8. If anything fails:
   - log warning
   - revert to `Default`
   - keep DSP and session state intact

## Important

Theme switching must never mutate:
- parameter IDs
- APVTS layout
- preset value ownership
- DSP routing

# Release Checklist

## Build
- [ ] Configure with JUCE present
- [ ] Build Standalone
- [ ] Build VST3
- [ ] Build AU

## Smoke tests
- [ ] Launch standalone
- [ ] Verify stereo I/O
- [ ] Verify parameter changes affect audio
- [ ] Verify preset switching
- [ ] Verify freeze engages without runaway output

## DAW tests
- [ ] Reaper
- [ ] Ableton Live
- [ ] Logic Pro
- [ ] FL Studio / equivalent

## Quality tests
- [ ] Automation recall
- [ ] Session reopen restore
- [ ] CPU sanity at 44.1 / 48 / 96 kHz
- [ ] No denormal spikes on silence
- [ ] Output protected from clipping on extreme settings

## Release assets
- [ ] Screenshots
- [ ] Demo audio
- [ ] GitHub release notes
- [ ] README pricing + pirate-friendly dropdowns checked

# Fallback Matrix

| Failure | Response |
|---|---|
| Missing `backgroundImage` | Use Default background |
| Missing `orbImage` | Use core procedural orb |
| Missing `knobRingImage` | Use stock ritual ring |
| Missing `glyphAtlas` | Use text labels only |
| Invalid preset value | Skip that preset entry |
| Unknown parameter ID | Reject add-on load |
| Unsupported schemaVersion | Reject add-on load |
| Missing add-on manifest fields | Reject add-on load |

#include "AetherThemeValidator.h"

namespace aether::addons
{
    namespace
    {
        AddonLoadReport merge(const AddonLoadReport& a, const AddonLoadReport& b)
        {
            AddonLoadReport out;
            out.success = a.success && b.success;
            out.warnings.addArray(a.warnings);
            out.warnings.addArray(b.warnings);
            out.errors.addArray(a.errors);
            out.errors.addArray(b.errors);
            return out;
        }

        bool existsIfSet(const juce::File& root, const juce::String& relative)
        {
            return relative.isEmpty() || root.getChildFile(relative).existsAsFile();
        }
    }

    bool ThemeValidator::isKnownParameter(const juce::String& paramId)
    {
        static const juce::StringArray known {
            "param_chant", "param_halo", "param_temple", "param_drone", "param_motion",
            "param_lightdark", "param_mix", "param_output", "param_freeze", "param_formant",
            "param_spread", "param_predelay"
        };
        return known.contains(paramId);
    }

    AddonLoadReport ThemeValidator::validateManifest(const AddonManifest& manifest)
    {
        AddonLoadReport r;
        r.success = true;
        if (manifest.schemaVersion != 1) { r.success = false; r.errors.add("Unsupported schemaVersion."); }
        if (manifest.id.isEmpty()) { r.success = false; r.errors.add("Missing addon id."); }
        if (manifest.name.isEmpty()) { r.success = false; r.errors.add("Missing addon name."); }
        if (manifest.type != "panel-theme") { r.success = false; r.errors.add("Addon type must be 'panel-theme'."); }
        if (manifest.fallbackTheme.isEmpty()) r.warnings.add("No fallbackTheme supplied; Default will be used.");
        return r;
    }

    AddonLoadReport ThemeValidator::validatePanel(const PanelTheme& panel, const juce::File& rootFolder)
    {
        AddonLoadReport r; r.success = true;
        if (!existsIfSet(rootFolder, panel.backgroundImage)) r.errors.add("Missing background image."), r.success = false;
        if (!existsIfSet(rootFolder, panel.orbImage)) r.warnings.add("Missing orb image; core orb renderer will be used.");
        if (!existsIfSet(rootFolder, panel.knobRingImage)) r.warnings.add("Missing knob ring; stock control ring will be used.");
        if (!existsIfSet(rootFolder, panel.glyphAtlas)) r.warnings.add("Missing glyph atlas; labels fallback to text only.");
        return r;
    }

    AddonLoadReport ThemeValidator::validateLayout(const LayoutDefinition& layout)
    {
        AddonLoadReport r; r.success = true;
        if (layout.width < 640 || layout.height < 360) { r.success = false; r.errors.add("Layout canvas too small."); }
        for (const auto& c : layout.controls)
        {
            if (!isKnownParameter(c.param)) { r.success = false; r.errors.add("Unknown parameter id in layout: " + c.param); }
            if (c.x < 0 || c.y < 0 || c.x > layout.width || c.y > layout.height)
                r.warnings.add("Control outside canvas bounds: " + c.param);
        }
        return r;
    }

    AddonLoadReport ThemeValidator::validateAll(const LoadedAddon& addon)
    {
        auto m = validateManifest(addon.manifest);
        auto p = validatePanel(addon.panel, addon.rootFolder);
        auto l = validateLayout(addon.layout);
        auto mp = merge(m, p);
        return merge(mp, l);
    }
}

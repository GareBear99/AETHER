#include "AetherThemeFallbackManager.h"

namespace aether::addons
{
    void ThemeFallbackManager::applyFallbacks(LoadedAddon& addon)
    {
        if (addon.manifest.fallbackTheme.isEmpty())
            addon.manifest.fallbackTheme = "Default";

        if (addon.panel.panelStyle.isEmpty())
            addon.panel.panelStyle = "ritual-stone";

        if (addon.panel.animationProfile.isEmpty())
            addon.panel.animationProfile = "deep-breath";

        if (addon.layout.width <= 0) addon.layout.width = 1280;
        if (addon.layout.height <= 0) addon.layout.height = 720;
        if (addon.layout.orbRadius <= 0) addon.layout.orbRadius = 128;

        if (addon.panel.palette.primary.isEmpty()) addon.panel.palette.primary = "#6d4cff";
        if (addon.panel.palette.secondary.isEmpty()) addon.panel.palette.secondary = "#d7b46a";
        if (addon.panel.palette.shadow.isEmpty()) addon.panel.palette.shadow = "#120d1d";
        if (addon.panel.palette.highlight.isEmpty()) addon.panel.palette.highlight = "#f3e6b2";
    }
}

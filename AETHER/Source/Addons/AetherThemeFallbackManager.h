#pragma once
#include "AetherAddonTypes.h"

namespace aether::addons
{
    class ThemeFallbackManager
    {
    public:
        static void applyFallbacks(LoadedAddon& addon);
    };
}

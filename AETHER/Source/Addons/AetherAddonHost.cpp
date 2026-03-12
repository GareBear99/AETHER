#include "AetherAddonHost.h"

namespace aether::addons
{
    bool AddonHost::initialise(const juce::File& themesFolder)
    {
        registry.scanDirectory(themesFolder);
        if (registry.getAddons().isEmpty())
        {
            bootWarnings.add("No addons discovered; Default theme only.");
            activeTheme = nullptr;
            return false;
        }

        for (const auto& addon : registry.getAddons())
        {
            if (addon.manifest.name == "Default" || addon.manifest.id.containsIgnoreCase("default"))
            {
                activeTheme = &addon;
                activePresetBank = PresetBankLoader::loadFromFolder(addon.rootFolder);
                return true;
            }
        }

        activeTheme = &registry.getAddons().getReference(0);
        activePresetBank = PresetBankLoader::loadFromFolder(activeTheme->rootFolder);
        bootWarnings.add("Default theme not found; first valid addon activated.");
        return true;
    }

    bool AddonHost::activateTheme(const juce::String& addonId)
    {
        for (const auto& addon : registry.getAddons())
        {
            if (addon.manifest.id == addonId)
            {
                activeTheme = &addon;
                activePresetBank = PresetBankLoader::loadFromFolder(addon.rootFolder);
                return true;
            }
        }
        bootWarnings.add("Requested addon not found: " + addonId);
        return false;
    }
}

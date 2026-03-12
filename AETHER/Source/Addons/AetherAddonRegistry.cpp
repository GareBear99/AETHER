#include "AetherAddonRegistry.h"
#include "AetherThemeLoader.h"

namespace aether::addons
{
    void AddonRegistry::scanDirectory(const juce::File& themesFolder)
    {
        addons.clear();
        if (!themesFolder.isDirectory())
            return;

        for (const auto& child : themesFolder.findChildFiles(juce::File::findDirectories, false))
        {
            if (child.getChildFile("addon.json").existsAsFile())
                addons.add(ThemeLoader::loadFromFolder(child));
        }
    }
}

#include "AetherThemeLoader.h"
#include "AetherThemeValidator.h"
#include "AetherThemeFallbackManager.h"

namespace aether::addons
{
    namespace
    {
        juce::String getString(const juce::var& object, const juce::Identifier& key)
        {
            if (auto* props = object.getDynamicObject())
                return props->getProperty(key).toString();
            return {};
        }

        int getInt(const juce::var& object, const juce::Identifier& key, int fallback)
        {
            if (auto* props = object.getDynamicObject())
                return static_cast<int>(props->getProperty(key));
            return fallback;
        }
    }

    juce::var ThemeLoader::readJson(const juce::File& file, juce::String& error)
    {
        if (!file.existsAsFile())
        {
            error = "Missing file: " + file.getFullPathName();
            return {};
        }
        auto text = file.loadFileAsString();
        auto parsed = juce::JSON::parse(text);
        if (parsed.isVoid())
            error = "Invalid JSON in: " + file.getFileName();
        return parsed;
    }

    AddonManifest ThemeLoader::parseManifest(const juce::var& value)
    {
        AddonManifest m;
        if (auto* obj = value.getDynamicObject())
        {
            m.schemaVersion = static_cast<int>(obj->getProperty("schemaVersion"));
            m.id = obj->getProperty("id").toString();
            m.name = obj->getProperty("name").toString();
            m.author = obj->getProperty("author").toString();
            m.version = obj->getProperty("version").toString();
            m.aetherMinVersion = obj->getProperty("aetherMinVersion").toString();
            m.type = obj->getProperty("type").toString();
            m.priceHint = obj->getProperty("priceHint").toString();
            m.description = obj->getProperty("description").toString();
            m.fallbackTheme = obj->getProperty("fallbackTheme").toString();
        }
        return m;
    }

    PanelTheme ThemeLoader::parsePanel(const juce::var& value)
    {
        PanelTheme p;
        if (auto* obj = value.getDynamicObject())
        {
            p.panelStyle = obj->getProperty("panelStyle").toString();
            p.backgroundImage = obj->getProperty("backgroundImage").toString();
            p.orbImage = obj->getProperty("orbImage").toString();
            p.knobRingImage = obj->getProperty("knobRingImage").toString();
            p.glyphAtlas = obj->getProperty("glyphAtlas").toString();
            p.animationProfile = obj->getProperty("animationProfile").toString();
            auto palette = obj->getProperty("accentPalette");
            if (auto* pal = palette.getDynamicObject())
            {
                p.palette.primary = pal->getProperty("primary").toString();
                p.palette.secondary = pal->getProperty("secondary").toString();
                p.palette.shadow = pal->getProperty("shadow").toString();
                p.palette.highlight = pal->getProperty("highlight").toString();
            }
        }
        return p;
    }

    LayoutDefinition ThemeLoader::parseLayout(const juce::var& value)
    {
        LayoutDefinition layout;
        if (auto* obj = value.getDynamicObject())
        {
            auto canvas = obj->getProperty("canvas");
            if (auto* c = canvas.getDynamicObject())
            {
                layout.width = static_cast<int>(c->getProperty("width"));
                layout.height = static_cast<int>(c->getProperty("height"));
            }

            auto orb = obj->getProperty("orb");
            if (auto* o = orb.getDynamicObject())
            {
                layout.orb = { static_cast<int>(o->getProperty("x")), static_cast<int>(o->getProperty("y")) };
                layout.orbRadius = static_cast<int>(o->getProperty("radius"));
            }

            if (auto* arr = obj->getProperty("controls").getArray())
            {
                for (const auto& item : *arr)
                {
                    if (auto* control = item.getDynamicObject())
                    {
                        ControlPlacement placement;
                        placement.param = control->getProperty("param").toString();
                        placement.x = static_cast<int>(control->getProperty("x"));
                        placement.y = static_cast<int>(control->getProperty("y"));
                        placement.style = control->getProperty("style").toString();
                        layout.controls.add(placement);
                    }
                }
            }
        }
        return layout;
    }

    LoadedAddon ThemeLoader::loadFromFolder(const juce::File& addonFolder)
    {
        LoadedAddon addon;
        addon.rootFolder = addonFolder;

        juce::String error;
        auto manifest = readJson(addonFolder.getChildFile("addon.json"), error);
        if (error.isNotEmpty()) addon.report.errors.add(error);
        auto panel = readJson(addonFolder.getChildFile("panel.json"), error);
        if (error.isNotEmpty()) addon.report.errors.add(error);
        auto layout = readJson(addonFolder.getChildFile("ui").getChildFile("layout.json"), error);
        if (error.isNotEmpty()) addon.report.errors.add(error);

        addon.manifest = parseManifest(manifest);
        addon.panel = parsePanel(panel);
        addon.layout = parseLayout(layout);

        ThemeFallbackManager::applyFallbacks(addon);
        addon.report = ThemeValidator::validateAll(addon);
        return addon;
    }
}

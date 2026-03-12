#include "AetherPresetBankLoader.h"
#include "AetherThemeContract.h"

namespace aether::addons
{
    ExternalPresetBank PresetBankLoader::loadFromFolder(const juce::File& addonFolder)
    {
        ExternalPresetBank bank;
        auto file = addonFolder.getChildFile("presets/presets.json");
        if (!file.existsAsFile())
        {
            bank.report.success = true;
            bank.report.warnings.add("No external preset bank present.");
            return bank;
        }

        auto parsed = juce::JSON::parse(file);
        if (parsed.isVoid())
        {
            bank.report.success = false;
            bank.report.errors.add("Invalid presets JSON.");
            return bank;
        }

        if (auto* obj = parsed.getDynamicObject())
        {
            bank.bankName = obj->getProperty("bankName").toString();
            if (auto* arr = obj->getProperty("presets").getArray())
            {
                for (const auto& entry : *arr)
                {
                    if (auto* presetObj = entry.getDynamicObject())
                    {
                        ExternalPreset preset;
                        preset.name = presetObj->getProperty("name").toString();
                        if (auto* valuesObj = presetObj->getProperty("values").getDynamicObject())
                        {
                            for (const auto& k : valuesObj->getProperties().getAllKeys())
                            {
                                auto key = k.toString();
                                if (Contract::isCanonicalParameter(key))
                                    preset.values.set(k, valuesObj->getProperty(k));
                            }
                        }
                        bank.presets.add(std::move(preset));
                    }
                }
            }
        }

        bank.report.success = true;
        return bank;
    }
}

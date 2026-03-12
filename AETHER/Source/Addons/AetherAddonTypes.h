#pragma once
#include <juce_core/juce_core.h>

namespace aether::addons
{
    struct AddonManifest
    {
        int schemaVersion = 1;
        juce::String id;
        juce::String name;
        juce::String author;
        juce::String version;
        juce::String aetherMinVersion;
        juce::String type;
        juce::String priceHint;
        juce::String description;
        juce::String fallbackTheme = "Default";
    };

    struct Palette
    {
        juce::String primary = "#6d4cff";
        juce::String secondary = "#d7b46a";
        juce::String shadow = "#120d1d";
        juce::String highlight = "#f3e6b2";
    };

    struct PanelTheme
    {
        juce::String panelStyle = "ritual-stone";
        juce::String backgroundImage;
        juce::String orbImage;
        juce::String knobRingImage;
        juce::String glyphAtlas;
        juce::String animationProfile = "deep-breath";
        Palette palette;
    };

    struct ControlPlacement
    {
        juce::String param;
        int x = 0;
        int y = 0;
        juce::String style = "large-rune-knob";
    };

    struct LayoutDefinition
    {
        int width = 1280;
        int height = 720;
        juce::Array<ControlPlacement> controls;
        juce::Point<int> orb { 640, 280 };
        int orbRadius = 128;
    };

    struct AddonLoadReport
    {
        bool success = false;
        juce::StringArray warnings;
        juce::StringArray errors;
    };

    struct LoadedAddon
    {
        AddonManifest manifest;
        PanelTheme panel;
        LayoutDefinition layout;
        juce::File rootFolder;
        AddonLoadReport report;
    };
}

cmake_minimum_required(VERSION 3.22)
project(Aether VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AETHER_EDITION "PRO" CACHE STRING "AETHER edition: LITE or PRO")
set_property(CACHE AETHER_EDITION PROPERTY STRINGS LITE PRO)

if(DEFINED JUCE_DIR)
    add_subdirectory(${JUCE_DIR} JUCE)
elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt)
    add_subdirectory(JUCE)
else()
    message(FATAL_ERROR "JUCE not found. Set -DJUCE_DIR=/path/to/JUCE or add JUCE submodule.")
endif()

if(AETHER_EDITION STREQUAL "LITE")
    set(AETHER_PRODUCT_NAME "Aether Lite")
    set(AETHER_IS_LITE 1)
    set(AETHER_IS_PRO 0)
else()
    set(AETHER_PRODUCT_NAME "Aether")
    set(AETHER_IS_LITE 0)
    set(AETHER_IS_PRO 1)
endif()

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "Gary Doman"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE GDom
    PLUGIN_CODE Aeth
    FORMATS AU VST3 Standalone
    PRODUCT_NAME ${AETHER_PRODUCT_NAME}
)

target_sources(${PROJECT_NAME} PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/Core/AetherParameters.h
    Source/Core/AetherMeterState.h
    Source/DSP/AetherDSPChain.h
    Source/DSP/AetherDSPChain.cpp
    Source/DSP/FormantChoirEngine.h
    Source/DSP/FormantChoirEngine.cpp
    Source/DSP/HaloEngine.h
    Source/DSP/HaloEngine.cpp
    Source/DSP/InvocationEngine.h
    Source/DSP/InvocationEngine.cpp
    Source/DSP/TempleSpace.h
    Source/DSP/TempleSpace.cpp
    Source/Presets/AetherPresetBank.h
    Source/Presets/AetherPresetManager.h
    Source/Presets/AetherPresetManager.cpp
    Source/UI/AetherLookAndFeel.h
    Source/UI/MysticBackground.h
    Source/Addons/AetherAddonTypes.h
    Source/Addons/AetherThemeValidator.h
    Source/Addons/AetherThemeValidator.cpp
    Source/Addons/AetherThemeFallbackManager.h
    Source/Addons/AetherThemeFallbackManager.cpp
    Source/Addons/AetherThemeLoader.h
    Source/Addons/AetherThemeLoader.cpp
    Source/Addons/AetherAddonRegistry.h
    Source/Addons/AetherAddonRegistry.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        AETHER_LITE=${AETHER_IS_LITE}
        AETHER_PRO=${AETHER_IS_PRO}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

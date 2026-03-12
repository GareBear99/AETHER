#pragma once
#include <JuceHeader.h>

namespace aether::ui
{
static inline void drawMysticPanel(juce::Graphics& g, juce::Rectangle<float> area, float radius = 18.0f)
{
    juce::ColourGradient fill(juce::Colour::fromRGBA(14, 16, 26, 212), area.getX(), area.getY(),
                              juce::Colour::fromRGBA(25, 18, 42, 196), area.getRight(), area.getBottom(), false);
    g.setGradientFill(fill);
    g.fillRoundedRectangle(area, radius);
    g.setColour(juce::Colour::fromRGBA(255, 255, 255, 16));
    g.drawRoundedRectangle(area, radius, 1.15f);
}

static inline void drawOrbAndRunes(juce::Graphics& g, juce::Rectangle<float> orb, float motionNorm, float wetNorm)
{
    const auto centre = orb.getCentre();
    const auto ring1 = orb.expanded(26.0f + 12.0f * motionNorm);
    const auto ring2 = orb.expanded(52.0f + 18.0f * wetNorm);

    juce::ColourGradient aura1(juce::Colour::fromRGBA(177, 126, 255, 90), centre.x, centre.y,
                               juce::Colour::fromRGBA(177, 126, 255, 0), ring2.getRight(), ring2.getBottom(), true);
    g.setGradientFill(aura1);
    g.fillEllipse(ring2);

    juce::ColourGradient aura2(juce::Colour::fromRGBA(255, 229, 170, 40), centre.x, orb.getY(),
                               juce::Colour::fromRGBA(255, 229, 170, 0), centre.x, orb.getBottom(), false);
    g.setGradientFill(aura2);
    g.fillEllipse(ring1);

    juce::ColourGradient core(juce::Colour::fromRGB(71, 56, 128), centre.x, orb.getY(),
                              juce::Colour::fromRGB(16, 14, 25), centre.x, orb.getBottom(), false);
    g.setGradientFill(core);
    g.fillEllipse(orb);
    g.setColour(juce::Colour::fromRGBA(255, 233, 179, 115));
    g.drawEllipse(orb, 2.0f);

    g.setColour(juce::Colour::fromRGBA(255, 255, 255, 18));
    for (int i = 0; i < 6; ++i)
        g.drawEllipse(orb.reduced((float) (8 + i * 12)), 1.0f);

    juce::Font runeFont(juce::FontOptions(12.0f, juce::Font::plain));
    g.setFont(runeFont);
    const juce::StringArray runes { "✶", "✧", "✦", "☽", "✴", "✷", "✹", "✺" };
    for (int i = 0; i < runes.size(); ++i)
    {
        auto angle = juce::MathConstants<float>::twoPi * (float) i / (float) runes.size() + motionNorm * 0.35f;
        auto p = centre + juce::Point<float>(std::cos(angle), std::sin(angle)) * (orb.getWidth() * 0.68f);
        g.setColour(i % 2 == 0 ? juce::Colour::fromRGBA(255, 232, 179, 120)
                               : juce::Colour::fromRGBA(183, 138, 255, 120));
        g.drawText(runes[i], juce::Rectangle<float>(p.x - 10.0f, p.y - 10.0f, 20.0f, 20.0f), juce::Justification::centred);
    }

    g.setColour(juce::Colour::fromRGBA(255, 255, 255, 25 + (int) (70.0f * wetNorm)));
    g.fillEllipse(centre.x - 18.0f, centre.y - 18.0f, 36.0f, 36.0f);
}

static inline void drawMeterBar(juce::Graphics& g, juce::Rectangle<float> area, float norm, juce::String label)
{
    drawMysticPanel(g, area, 12.0f);
    auto inner = area.reduced(10.0f, 8.0f);
    auto bar = inner.removeFromBottom(14.0f);
    g.setColour(juce::Colour::fromRGBA(255, 255, 255, 12));
    g.fillRoundedRectangle(bar, 7.0f);
    auto fill = bar.withWidth(bar.getWidth() * juce::jlimit(0.0f, 1.0f, norm));
    juce::ColourGradient fg(juce::Colour::fromRGB(255, 225, 157), fill.getX(), fill.getCentreY(),
                            juce::Colour::fromRGB(183, 138, 255), fill.getRight(), fill.getCentreY(), false);
    g.setGradientFill(fg);
    g.fillRoundedRectangle(fill, 7.0f);
    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(13.0f, juce::Font::plain));
    g.drawText(label, inner, juce::Justification::centredLeft);
}
}

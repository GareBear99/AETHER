#pragma once
#include <JuceHeader.h>

class AetherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AetherLookAndFeel()
    {
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB(187, 146, 255));
        setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(255, 226, 167));
        setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGBA(255, 255, 255, 28));
        setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour::fromRGBA(8, 8, 14, 180));
        setColour(juce::Label::textColourId, juce::Colours::white);
        setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGBA(9, 11, 18, 210));
        setColour(juce::ComboBox::outlineColourId, juce::Colour::fromRGBA(225, 210, 255, 30));
        setColour(juce::ComboBox::textColourId, juce::Colours::white);
        setColour(juce::PopupMenu::backgroundColourId, juce::Colour::fromRGB(11, 10, 20));
        setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(35, 22, 50));
        setColour(juce::TextButton::textColourOffId, juce::Colours::white);
        setColour(juce::ToggleButton::textColourId, juce::Colours::white);
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider&) override
    {
        auto bounds = juce::Rectangle<float>(x, y, width, height).reduced(10.0f);
        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.5f;
        auto centre = bounds.getCentre();
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        juce::ColourGradient outer(juce::Colour::fromRGBA(167, 127, 255, 42), centre.x, bounds.getY(),
                                   juce::Colour::fromRGBA(167, 127, 255, 0), centre.x, bounds.getBottom(), false);
        g.setGradientFill(outer);
        g.fillEllipse(bounds.expanded(9.0f));

        juce::ColourGradient face(juce::Colour::fromRGB(32, 24, 55), centre.x, bounds.getY(),
                                  juce::Colour::fromRGB(10, 9, 18), centre.x, bounds.getBottom(), false);
        g.setGradientFill(face);
        g.fillEllipse(bounds);

        g.setColour(juce::Colour::fromRGBA(255, 228, 166, 70));
        g.drawEllipse(bounds, 1.6f);
        g.setColour(juce::Colour::fromRGBA(250, 245, 255, 12));
        g.drawEllipse(bounds.reduced(6.0f), 1.0f);

        juce::Path valueArc;
        valueArc.addCentredArc(centre.x, centre.y, radius - 6.0f, radius - 6.0f, 0.0f,
                               rotaryStartAngle, angle, true);
        juce::ColourGradient arc(juce::Colour::fromRGB(255, 222, 152), centre.x, centre.y - radius,
                                 juce::Colour::fromRGB(183, 138, 255), centre.x, centre.y + radius, false);
        g.setGradientFill(arc);
        g.strokePath(valueArc, juce::PathStrokeType(4.25f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        juce::Path pointer;
        auto pointerLength = radius * 0.58f;
        pointer.addRoundedRectangle(-2.5f, -pointerLength, 5.0f, pointerLength, 2.2f);
        g.setColour(juce::Colour::fromRGB(255, 233, 179));
        g.fillPath(pointer, juce::AffineTransform::rotation(angle).translated(centre.x, centre.y));

        g.setColour(juce::Colour::fromRGBA(255, 255, 255, 22));
        g.fillEllipse(centre.x - radius * 0.20f, centre.y - radius * 0.52f, radius * 0.40f, radius * 0.22f);
    }

    void drawComboBox(juce::Graphics& g, int width, int height, bool,
                      int, int, int, int, juce::ComboBox& box) override
    {
        auto area = juce::Rectangle<float>(0, 0, (float) width, (float) height).reduced(1.5f);
        juce::ColourGradient bg(juce::Colour::fromRGB(20, 18, 33), 0, 0,
                                juce::Colour::fromRGB(10, 10, 17), 0, (float) height, false);
        g.setGradientFill(bg);
        g.fillRoundedRectangle(area, 10.0f);
        g.setColour(findColour(juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle(area, 10.0f, 1.2f);

        juce::Path p;
        auto cx = (float) width - 18.0f;
        auto cy = (float) height * 0.5f;
        p.startNewSubPath(cx - 5.0f, cy - 2.0f);
        p.lineTo(cx, cy + 3.0f);
        p.lineTo(cx + 5.0f, cy - 2.0f);
        g.setColour(juce::Colour::fromRGB(255, 226, 167));
        g.strokePath(p, juce::PathStrokeType(2.0f));
    }

    juce::Font getComboBoxFont(juce::ComboBox&) override { return juce::FontOptions(14.0f, juce::Font::plain); }
};

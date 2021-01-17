#pragma once

#include <JuceHeader.h>

class MyListener : public juce::Component {
public:
    MyListener();
    bool keyPressed(const juce::KeyPress &key) override;
    bool keyEvent(const juce::KeyEvent &keyEvent) override;
};

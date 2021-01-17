#include "MyListener.h"

MyListener::MyListener()
{
    
}

bool MyListener::keyPressed(const juce::KeyPress &key) {
//    DBG("MyListener::keyPressed");
    return true;
}

bool MyListener::keyEvent(const juce::KeyEvent &keyEvent) {
    DBG("MyListener::keyEvent rawKeyCode " << keyEvent.rawKeyCode << (keyEvent.keyDown ? " down" : " up"));
    return false;
}

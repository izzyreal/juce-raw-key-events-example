#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    saveButton.setButtonText("Save");
    saveButton.onClick = [this] { saveButtonClicked(); };
    addAndMakeVisible(saveButton);

    setSize (800, 600);

    deviceManager.initialise(0, 2, nullptr, false, {}, nullptr);
//    deviceManager.setCurrentAudioDeviceType("DirectSound", true);
    auto* deviceType = deviceManager.getCurrentDeviceTypeObject();

    auto inputDeviceList = deviceType->getDeviceNames(true);
    juce::String inputDevice;
    for (auto dev : inputDeviceList)
    {
        auto check = dev.contains("MYDEVICE");
        if (check == true)
            inputDevice = dev;
    }

    auto outputDeviceList = deviceType->getDeviceNames();
    juce::String outputDevice = "";
    for (auto dev : outputDeviceList)
    {
        auto check = dev.contains("MacBook Air Speakers");
        if (check == true) {
            outputDevice = dev;
            printf("Yay\n");
        }
    }
    
    if (outputDevice != "") {
        printf("Outputdevice: %s\n", outputDevice.toStdString().c_str());
    }

    auto newSetup = deviceManager.getAudioDeviceSetup();
    newSetup.outputDeviceName = outputDevice;
//    newSetup.inputDeviceName = inputDevice;
    juce::String msg = deviceManager.setAudioDeviceSetup(newSetup, true);
    printf("Device manager audio device: %s\n", deviceManager.getCurrentAudioDevice()->getName().toStdString().c_str());
    DBG(msg);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    // bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::saveButtonClicked()
{
    juce::File xmlfile("/Users/izmar/device_data.txt");

    auto* device = deviceManager.getCurrentAudioDevice();
    xmlfile.replaceWithText(device->getName());
    xmlfile.appendText("\n");
    xmlfile.appendText(device->getTypeName());
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    saveButton.setBounds(10, 10, getWidth() - 20, 20);
}

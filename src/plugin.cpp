#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

// Minimal JUCE VST3 plugin implementation

class ReaperLLMAudioProcessor  : public juce::AudioProcessor
{
public:
    ReaperLLMAudioProcessor() {}
    ~ReaperLLMAudioProcessor() override {}

    const juce::String getName() const override { return "Reaper-LLM"; }
    void prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/) override {}
    void releaseResources() override {}

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override
    {
        // Accept any layout
        return true;
    }

    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override
    {
        // No audio processing – placeholder
        buffer.clear();
    }

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override
    {
        // Placeholder editor – will be replaced with Qt UI later
        return new juce::GenericAudioProcessorEditor (*this);
    }

    bool hasEditor() const override { return true; }

    //==============================================================================
    const juce::String getIdentifier() const override { return "ReaperLLM"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0; }

    //==============================================================================
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    //==============================================================================
    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}
};

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReaperLLMAudioProcessor();
}

[Overview]
Create **Reaper-LLM**, a cross‑platform VST3 plugin written in C++ that runs on Linux and Windows (built with GCC). The plugin will host a locally‑run LLM (or connect to remote LLM APIs) and expose a simple Qt‑based GUI for configuring API keys (OpenAI, OpenAI‑compatible services, Ollama) and sending prompts. Initial integration and testing target **Reaper** running under **WINE**; the codebase will be open‑source to allow community extensions for other DAWs.

[Types]
```cpp
struct ApiCredentials {
    std::string serviceName;   // "OpenAI", "Ollama", etc.
    std::string apiKey;
};

struct PluginConfig {
    std::vector<ApiCredentials> credentials;
    bool useLocalLLM;                // true = launch local binary, false = remote API
    std::string localModelPath;      // path to local model binary (if any)
};

enum class LlmBackend { Local, OpenAI, OpenAICompatible, Ollama };

struct LlmRequest {
    LlmBackend backend;
    std::string prompt;
    std::map<std::string, std::string> options; // e.g. temperature, max_tokens
};
```

[Files]
- **/src/**
  - `plugin.cpp` – VST3 entry point, JUCE factory registration.
  - `gui.cpp` / `gui.h` – Qt widgets for the simple UI (API key fields, prompt box, status display).
  - `llm_manager.cpp` / `llm_manager.h` – abstraction over local LLM process and remote HTTP APIs.
  - `config.cpp` / `config.h` – load/save `PluginConfig` via JSON (nlohmann/json).
- **/CMakeLists.txt** – CMake build script (generates Linux `.so` and Windows `.dll` via MinGW).
- **/README.md** – build instructions, runtime requirements, usage notes.
- **/docs/** – optional design documentation.
- **/tests/** – Catch2 unit tests (config handling, backend routing).

[Functions]
- `bool initPlugin(VST3::HostContext*);`
- `void shutdownPlugin();`
- `void onParameterChanged(int32 paramID, float value);`
- `std::string sendPrompt(const LlmRequest&);`
- `bool loadConfig(const std::string& path, PluginConfig& out);`
- `bool saveConfig(const std::string& path, const PluginConfig&);`

[Classes]
- `class ReaperBridge` – thin wrapper for Reaper‑specific callbacks (transport state, MIDI I/O) when running under WINE.
- `class QtPluginEditor : public juce::AudioProcessorEditor` – hosts the Qt UI inside the JUCE editor window.
- `class LlmBackendBase` (abstract) with concrete subclasses:
  - `LocalLlmBackend` – launches a local LLM binary (e.g., Ollama) and communicates via stdio or HTTP.
  - `OpenAiBackend`, `OpenAiCompatibleBackend`, `OllamaBackend` – perform HTTP POST requests using stored API keys.

[Dependencies]
- **JUCE** (v7.x) – VST3 SDK and audio‑plugin framework.
- **Qt5/Qt6** – UI toolkit (compiled with GCC).
- **CMake** ≥ 3.15 – build system.
- **nlohmann/json** – JSON parsing.
- **cURL** – HTTP client for remote APIs.
- **Catch2** – unit‑testing framework.
- Optional: **spdlog** – logging.

[Testing]
- Unit tests for `PluginConfig` (load/save, validation of API keys).
- Mocked `LlmBackendBase` implementations to verify request routing.
- Integration test: build the plugin and load it in Reaper (via WINE) with a minimal test project.

[Implementation Order]
1. Scaffold repository with directory layout and `CMakeLists.txt`; add a minimal JUCE/VST3 stub.
2. Add Qt integration and a placeholder UI.
3. Implement `PluginConfig` and JSON persistence.
4. Build the LLM abstraction layer (interface + dummy backend).
5. Wire UI controls to configuration and backend selection.
6. Implement concrete backends for OpenAI, OpenAI‑compatible services, and Ollama.
7. Add `ReaperBridge` for transport/MIDI hooks under WINE.
8. Write unit tests for config handling and backend routing.
9. Perform cross‑platform builds (Linux native, Windows target via MinGW).
10. Document build steps, runtime requirements, and usage in `README.md`.

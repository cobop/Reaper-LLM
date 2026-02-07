# Reaper-LLM

A cross‑platform VST3 plugin written in C++ that enables an LLM to control a DAW (Reaper) via a simple Qt GUI. The plugin supports local LLMs and remote APIs (OpenAI, OpenAI‑compatible services, Ollama) and is licensed under GPL‑3.0.

## Features

- VST3 plugin (Linux & Windows via GCC/MinGW)
- Qt‑based UI for API key management and prompt input
- Pluggable LLM back‑ends (local binary, OpenAI, Ollama, etc.)
- Configuration stored in JSON
- Unit tests with Catch2

## Build Instructions

```bash
# Clone the repository
git clone https://github.com/your-username/Reaper-LLM.git
cd Reaper-LLM

# Install dependencies (Ubuntu example)
sudo apt-get install libjuce-dev libqt5widgets5 libqt5core5a libcurl4-openssl-dev nlohmann-json3-dev cmake make

# Build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

The resulting plugin library will be located in `build/`.

## License

This project is licensed under the GNU General Public License v3.0 – see the `LICENSE` file for details.

## Contributing

Feel free to open issues or pull requests. The project is open‑source and welcomes extensions for other DAWs.

## Repository Structure

- `src/` – source files (`plugin.cpp`, `gui.*`, `config.*`, `llm_manager.*`)
- `tests/` – unit tests
- `CMakeLists.txt` – build configuration
- `implementation_plan.md` – detailed implementation plan
- `LICENSE` – GPL‑3.0 license

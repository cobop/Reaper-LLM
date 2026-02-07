cmake_minimum_required(VERSION 3.15)
project(Reaper-LLM LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find JUCE (assumes JUCE is available as a submodule or installed package)
find_package(JUCE CONFIG REQUIRED)

# Find Qt (using Qt5 or Qt6)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Source files
set(SRC_FILES
    src/plugin.cpp
    src/gui.cpp
    src/llm_manager.cpp
    src/config.cpp
)

# Create shared library for VST3 plugin
juce_add_plugin(Reaper-LLM
    COMPANY_NAME "YourCompany"
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE RLLM
    FORMATS VST3
    PRODUCT_NAME "Reaper-LLM"
    VERSION 0.1.0
    # VST3 specific settings
    VST3_CATEGORY "Fx"
    VST3_SUBCATEGORY "Utility"
)

target_sources(Reaper-LLM PRIVATE ${SRC_FILES})

# Link Qt
target_link_libraries(Reaper-LLM PRIVATE Qt5::Widgets)

# Add include directories if needed
target_include_directories(Reaper-LLM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# JSON handling (nlohmann/json)
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(Reaper-LLM PRIVATE nlohmann_json::nlohmann_json)

# cURL for HTTP requests
find_package(CURL REQUIRED)
target_link_libraries(Reaper-LLM PRIVATE CURL::libcurl)

# Enable testing
enable_testing()
add_subdirectory(tests)

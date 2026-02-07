#include "config.h"
#include "json.hpp" // nlohmann::json
#include <fstream>

using json = nlohmann::json;

bool ConfigManager::load(const std::string& path, PluginConfig& out)
{
    std::ifstream infile(path);
    if (!infile.is_open())
        return false;

    json j;
    try {
        infile >> j;
    } catch (...) {
        return false;
    }

    // Parse credentials
    if (j.contains("credentials") && j["credentials"].is_array()) {
        out.credentials.clear();
        for (const auto& cred : j["credentials"]) {
            ApiCredentials ac;
            ac.serviceName = cred.value("serviceName", "");
            ac.apiKey      = cred.value("apiKey", "");
            out.credentials.push_back(ac);
        }
    }

    out.useLocalLLM   = j.value("useLocalLLM", true);
    out.localModelPath = j.value("localModelPath", "");

    return true;
}

bool ConfigManager::save(const std::string& path, const PluginConfig& config)
{
    std::ofstream outfile(path);
    if (!outfile.is_open())
        return false;

    json j;
    j["credentials"] = json::array();
    for (const auto& cred : config.credentials) {
        json c;
        c["serviceName"] = cred.serviceName;
        c["apiKey"]      = cred.apiKey;
        j["credentials"].push_back(c);
    }

    j["useLocalLLM"]    = config.useLocalLLM;
    j["localModelPath"] = config.localModelPath;

    try {
        outfile << j.dump(4);
    } catch (...) {
        return false;
    }

    return true;
}

#include "Logger.hpp"
std::mutex Logger::mutex_;

void Logger::logInfo(const std::string &message)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[INFO]: " << message << std::endl;
}

void Logger::logDebug(const std::string &message)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[DEBUG]: " << message << std::endl;
}

void Logger::logWarn(const std::string &message)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cerr << "[WARN]: " << message << std::endl;
}

void Logger::logError(const std::string &message)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cerr << "[ERROR]: " << message << std::endl;
}

void Logger::logResult(const nlohmann::json &message){
    std::lock_guard<std::mutex> lock(mutex_);
    nlohmann::json output;
    if (message.contains("result")) {
        output["result"] = message["result"];
    }
    if (message.contains("usDiff")) {
        output["usDiff"] = message["usDiff"];
    }
    std::cout << "Message Recieved" << output.dump(4) << std::endl;

}
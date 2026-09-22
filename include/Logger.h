#pragma once

#include <iostream>
#include <fstream> 
#include <string>
#include <ctime>

enum class LogLevel { INFO, WARNING, ERROR, TEST }; 

class Logger {
private: 
    inline static std::ofstream logFile; 
    inline static bool toFile; 

public:    
    // init logger with optional file output
    inline static void init( const std::string& fileName = "" ) {
        if ( !fileName.empty() ) {
            logFile.open( fileName, std::ios::out | std::ios::app ); 
            toFile = logFile.is_open(); 
        }
    }

    // cleanup 
    inline static void shutdown() {
        if ( logFile.is_open() ) {
            logFile.close(); 
        }
        toFile = false; 
    } 

    // logs a message with specific level 
    inline static void log( LogLevel level, const std::string& message ) {
        const char* levelStr = ""; 
        switch ( level ) {
            case LogLevel::INFO:    levelStr = "INFO"; break;
            case LogLevel::WARNING: levelStr = "WARNING"; break;
            case LogLevel::ERROR:   levelStr = "ERROR"; break;
            case LogLevel::TEST:   levelStr = "TEST"; break;
        }
        
        std::time_t now = std::time(nullptr); 
        char buf[20]; 
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now)); 

        // Final log message
        std::string output = "[" + std::string(buf) + "] [" + levelStr + "] " + message;

        // print to console 
        std::cout << output << std::endl; 

        // print to file if enabled
        if ( toFile && logFile.is_open() ) {
            logFile << output << std::endl; 
        }
    }

    // Convenience shortcuts
    inline static void info(const std::string& message) {
        log(LogLevel::INFO, message);
    }

    inline static void warn(const std::string& message) {
        log(LogLevel::WARNING, message);
    }

    inline static void error(const std::string& message) {
        log(LogLevel::ERROR, message);
    }

    inline static void test(const std::string& message) {
        log(LogLevel::TEST, message);
    }};


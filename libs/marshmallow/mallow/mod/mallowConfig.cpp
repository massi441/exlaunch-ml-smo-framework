#include <mallow/mallow.hpp>

#include <nn/fs/fs_directories.h>
#include <nn/fs/fs_types.h>

#include "ModOptions.h"

namespace mallow::config {
    const char* path = "sd:/atmosphere/contents/0100000000010000/mallow.json";
    const char* pathEmu = "sd:/mallow.json";
    const char* defaultConfig = R"(
{
    "myModOption": true,
    "logger": {
        "enable": false,
        "reconnect": true,
        "ip": "127.0.0.1",
        "port": 3080
    }
}
    )";

    extern const LogLevel DefaultLogLevel = LogLevel::Trace; // change the log level through here till its read from the JSON file

    Allocator* getAllocator() {
        static DefaultAllocator allocator = {};
        return &allocator;
    }
    ConfigBase* getConfig() {
        static ModOptions modConfig = { };
        return &modConfig;
    }
    bool isEmu(){
        nn::fs::DirectoryEntryType type;
        nn::fs::GetEntryType(&type, "sd:/atmosphere/package3");
        return type != nn::fs::DirectoryEntryType_File;
    }
}

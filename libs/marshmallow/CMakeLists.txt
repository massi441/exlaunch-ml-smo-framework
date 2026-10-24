add_library(marshmallow STATIC)

target_include_directories(marshmallow
    SYSTEM
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../smo/NintendoSDK
        ../custom/NintendoSDK/
)

target_sources(marshmallow
    PRIVATE
        mallow/alloc.hpp
        mallow/config.cpp
        mallow/exception/abort.cpp
        mallow/init/initLogging.cpp
        mallow/logging/debug.hpp
        mallow/logging/logger.cpp
        mallow/logging/logger.hpp
        mallow/logging/logSinks.cpp
        mallow/logging/logSinks.hpp
        mallow/mod/mallowConfig.cpp
        mallow/net/socket.cpp
)

target_link_libraries(marshmallow PUBLIC exlaunch ArduinoJson)

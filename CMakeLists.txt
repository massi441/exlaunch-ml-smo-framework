include(cmake/deploy-util.cmake)

# Libs --> Exclude from all ensures mallow and exlaunch don't get compiled in INTERFACE build mode
add_subdirectory(libs/ArduinoJson)
add_subdirectory(libs/marshmallow EXCLUDE_FROM_ALL)
add_subdirectory(libs/exlaunch EXCLUDE_FROM_ALL)

# Custom
add_subdirectory(src)

include(cmake/deploy-util.cmake)

# Libs
add_subdirectory(libs/exlaunch)
add_subdirectory(libs/ArduinoJson)
add_subdirectory(libs/marshmallow)

# Custom
add_subdirectory(src)

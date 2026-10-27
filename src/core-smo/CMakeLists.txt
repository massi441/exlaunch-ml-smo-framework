 add_library(ml_core_smo)

 target_include_directories(ml_core_smo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/detail)
 target_include_directories(ml_core_smo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

 target_link_libraries(ml_core_smo PUBLIC
    ml_runtime
    ml_core_cpp
    ArduinoJson
 )

 file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
 )

 target_sources(ml_core_smo PRIVATE ${SOURCES})

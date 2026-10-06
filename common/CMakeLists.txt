
file(GLOB_RECURSE ISKRA_COMMON_SOURCES "src/*.cpp")

add_library(iskra-common STATIC ${ISKRA_COMMON_SOURCES})

target_include_directories(iskra-common PUBLIC "include")


file(GLOB_RECURSE ISKRA_COMPILER_SOURCES "src/*.cpp")

add_executable(iskrac ${ISKRA_COMPILER_SOURCES})

target_include_directories(iskrac PRIVATE "include")
target_link_libraries(iskrac PRIVATE iskra-common)

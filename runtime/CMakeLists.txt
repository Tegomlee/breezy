add_library(zephyr SHARED
    src/breezy_runtime_interface.cpp
    src/runtime_instance.cpp

    src/frontend/lexer.cpp
)

target_include_directories(zephyr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(zephyr PUBLIC BREEZY_BUILD)

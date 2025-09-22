add_executable(
    breezy

    src/main.cpp

    src/commands/version_command.cpp

    src/services/command_table.cpp
)

target_include_directories(breezy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
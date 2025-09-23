add_executable(
    breezy

    src/main.cpp

    src/commands/version_command.cpp
    src/commands/help_command.cpp
    src/commands/run_command.cpp

    src/services/command_table.cpp
    src/services/argument_parser.cpp
)

target_include_directories(breezy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(breezy PRIVATE zephyr)

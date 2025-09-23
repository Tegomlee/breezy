/*
    =============================================================================================
    Copyright 2025 Bryan Sanchez

    Redistribution and use in source and binary forms, with or without modification, 
    are permitted provided that the following conditions are met:

    1.  Redistributions of source code must retain the above copyright notice, this list of 
        conditions and the following disclaimer.

    2.  Redistributions in binary form must reproduce the above copyright notice, this list of 
        conditions and the following disclaimer in the documentation and/or other materials 
        provided with the distribution.

    3.  Neither the name of the copyright holder nor the names of its contributors may be used to 
        endorse or promote products derived from this software without specific prior written 
        permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
    AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
    IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    ============================================================================================
*/

#include "breezy/runtime_instance.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "breezy/frontend/lexer.hpp"

namespace breezy::runtime {
    RuntimeInstance::RuntimeInstance() {
        // TODO: Initialize future components
    }

    RuntimeInstance::~RuntimeInstance() {
        // TODO: Cleanup future components
    }

    void RuntimeInstance::run_file(const std::string& filepath) {
        std::filesystem::path path(filepath);

        if (!std::filesystem::exists(path)) {
            std::cerr << "File does not exist: " << path << std::endl;
            return;
        }

        if (!std::filesystem::is_regular_file(path)) {
            std::cerr << "Not a regular file: " << path << std::endl;
            return;
        }

        std::ifstream file(path, std::ios::in);
        if (!file) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        execute(buffer.str());
    }

    void RuntimeInstance::run_string(const std::string& code) {
        execute(code);
    }

    void RuntimeInstance::execute(const std::string& code) {
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        // For now, just print the tokens
        for (const auto& t : tokens) {
            std::cout << static_cast<int>(t.type) << ": " << t.lexeme << "\n";
        }
    }
}

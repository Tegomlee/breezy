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

#include "services/argument_parser.hpp"

namespace breezy::cli {
    ArgumentParser::ArgumentParser() {
        aliases_["--version"] = "version";
        aliases_["-v"] = "version";
        aliases_["--help"] = "help";
        aliases_["-h"] = "help";
    }

    const std::pair<std::string, std::vector<std::string>> 
    ArgumentParser::parse(int argc, char* argv[]) const {
        if (argc < 2) {
            return { "help", {} }; // default command if none are passed.
        }

        // TODO: Support multiple commands
        std::string cmd = argv[1];

        // Resolve the command alias
        auto it = aliases_.find(cmd);
        std::string alias;
        if (it != aliases_.end()) {
            alias = it->second;
        }
        else {
            alias = cmd;
        }

        // Collect remaining arguments
        std::vector<std::string> args(argv + 2, argv + argc);

        return { alias, args };
    }
}
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

#ifndef BREEZY_RUNTIME_PARSER_HPP
#define BREEZY_RUNTIME_PARSER_HPP

#include <string_view>
#include <vector>

#include "breezy/frontend/ast.hpp"
#include "breezy/frontend/token.hpp"

namespace breezy::runtime {
    class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);

        std::vector<Stmt> parse();

    private:
        const std::vector<Token>& tokens_;
        size_t current_ = 0;

        /*
        ============================
        Statements
        ============================
        */

        Stmt statement();
        Stmt var_declaration();
        Stmt expr_statement();

        /*
        ============================
        Expressions
        ============================
        */

        Expr expression();
        Expr primary();

        /*
        ============================
        Util
        ============================
        */

        bool match(TokenType type, const std::string_view lexeme = {});
        bool check(TokenType type, const std::string_view lexeme = {}) const;
        Token advance();
        bool is_at_end() const;
        Token peek() const;
        Token previous() const;
        Token consume(TokenType type, const std::string& message);
    };
}

#endif // !BREEZY_RUNTIME_PARSER_HPP

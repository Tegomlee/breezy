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

#include "breezy/frontend/parser.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "breezy/frontend/ast.hpp"
#include "breezy/frontend/token.hpp"

namespace breezy::runtime {
    Parser::Parser(const std::vector<Token>& tokens)
        : tokens_(tokens) {}

    std::vector<Stmt> Parser::parse() {
        std::vector<Stmt> statements;
        while (!is_at_end()) {
            statements.push_back(statement());
        }
        return statements;
    }

    Stmt Parser::statement() {
        if (match(TokenType::Keyword, "var")) {
            return var_declaration();
        }
        return expr_statement();
    }

    Stmt Parser::var_declaration() {
        Token name = consume(TokenType::Identifier, "Expected variable name after 'var'.");

        std::unique_ptr<Expr> initializer = nullptr;

        if (match(TokenType::Symbol, "=")) {
            initializer = std::make_unique<Expr>(expression());
        }

        match(TokenType::Symbol, ";");

        return VarDeclStmt{ name.lexeme, std::move(initializer) };
    }

    Stmt Parser::expr_statement() {
        Expr expr = expression();
        match(TokenType::Symbol, ";");
        return ExprStmt{ std::move(expr) };
    }

    Expr Parser::expression() {
        return primary();
    }

    Expr Parser::primary() {
        if (check(TokenType::Number)) {
            Token num = advance();
            double value = std::stod(std::string(num.lexeme));
            return LiteralExpr{ value };
        }

        // Identifiers or keywords (for function calls like print)
        if (check(TokenType::Identifier) || check(TokenType::Keyword)) {
            Token id = advance();

            // Only handle call expressions if next token is '('
            if (check(TokenType::Symbol, "(")) {
                advance(); // Consume '('

                Expr arg;
                if (check(TokenType::Number)) {
                    Token num = advance();
                    arg = LiteralExpr{ std::stod(std::string(num.lexeme)) };
                } 
                else if (check(TokenType::Identifier) || check(TokenType::Keyword)) {
                    Token var = advance();
                    arg = VariableExpr{ var.lexeme };
                }
                else {
                    throw std::runtime_error("Expected expression as print argument");
                }

                // Expect closing ')'
                if (!check(TokenType::Symbol) || peek().lexeme != ")") {
                    throw std::runtime_error("Expected ')' after argument.");
                }
                advance(); // Consume ')'

                return CallExpr{ id. lexeme, {arg} }; // Wrap the vector
            }

            // Otherwise, treat as variable
            return VariableExpr{ id.lexeme };
        }

        throw std::runtime_error("Expected expression at token: " + std::string(peek().lexeme));
    }

    bool Parser::match(TokenType type, const std::string_view lexeme) {
        if (check(type, lexeme)) {
            advance();
            return true;
        }
        return false;
    }

    bool Parser::check(TokenType type, const std::string_view lexeme) const {
        if (is_at_end()) return false;
        const Token& t = peek();
        if (t.type != type) return false;
        if (!lexeme.empty() && t.lexeme != lexeme) return false;
        return true;
    }

    Token Parser::advance() {
        if (!is_at_end()) current_++;
        return previous();
    }

    bool Parser::is_at_end() const {
        return peek().type == TokenType::EndOfFile;
    }

    Token Parser::peek() const {
        return tokens_[current_];
    }

    Token Parser::previous() const {
        return tokens_[current_ - 1];
    }

    Token Parser::consume(TokenType type, const std::string& message) {
        if (check(type)) return advance();
        throw std::runtime_error(message);
    }
}
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

#include "breezy/frontend/lexer.hpp"

#include <cctype>
#include <string>
#include <string_view>
#include <vector>

#include "breezy/frontend/token.hpp"

namespace breezy::runtime {
    Lexer::Lexer(std::string_view source) 
        : source_(source) {}
    
    std::vector<Token> Lexer::tokenize() {
        std::vector<Token> tokens;

        while (!is_at_end()) {
            skip_white_space();
            if (is_at_end()) break;

            std::size_t token_start = position_;
            std::uint32_t token_line = line_;
            std::uint32_t token_column = column_;

            char c = peek();

            // Identifiers / Keywords
            if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
                // Use peek() and guard with is_at_end()
                while (!is_at_end() && (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_')) {
                    advance();
                }
                std::string_view lex = source_.substr(token_start, position_ - token_start);

                TokenType type = TokenType::Identifier;
                if (is_keyword(lex)) {
                    type = TokenType::Keyword;
                }

                tokens.push_back({type, lex, token_line, token_column});
                continue;
            }

            // Numbers (integers only for now)
            if (std::isdigit(static_cast<unsigned char>(c))) {
                while (!is_at_end() && std::isdigit(static_cast<unsigned char>(peek()))) {
                    advance();
                }
                std::string_view lex = source_.substr(token_start, position_ - token_start);
                tokens.push_back({TokenType::Number, lex, token_line, token_column});
                continue;
            }

            // Strings (include quotes in lexeme for now)
            if (c == '"') {
                // consume opening quote
                advance();
                while (!is_at_end() && peek() != '"') {
                    // simple escape handling could be added later
                    advance();
                }
                // consume closing quote if present
                if (!is_at_end() && peek() == '"') advance();
                std::string_view lex = source_.substr(token_start, position_ - token_start);
                tokens.push_back({TokenType::String, lex, token_line, token_column});
                continue;
            }

            // Symbols (single-char for now)
            const std::string symbols = "+-*/=;(){}[],.";
            if (symbols.find(c) != std::string::npos) {
                advance();
                std::string_view lex = source_.substr(token_start, 1);
                tokens.push_back({TokenType::Symbol, lex, token_line, token_column});
                continue;
            }

            // Unknown / skip character
            advance();
        }

        tokens.push_back({TokenType::EndOfFile, std::string_view(), line_, column_});
        return tokens;
    }

    char Lexer::peek() const {
        return is_at_end() ? '\0' : source_[position_];
    }

    char Lexer::advance() {
        if (is_at_end()) return '\0';
        char c = source_[position_++];
        if (c == '\n') {
            ++line_;
            column_ = 1;
        } else {
            ++column_;
        }
        return c;
    }

    bool Lexer::is_at_end() const {
        return position_ >= source_.size();
    }

    void Lexer::skip_white_space() {
        while (!is_at_end() && std::isspace(static_cast<unsigned char>(peek()))) advance();
    }

    bool Lexer::is_keyword(std::string_view lexeme) {
        for (auto kw : keywords_) {
            if (lexeme == kw) return true;
        }
        return false;
    }
}

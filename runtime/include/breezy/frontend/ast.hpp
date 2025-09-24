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

#ifndef BREEZY_RUNTIME_AST_HPP
#define BREEZY_RUNTIME_AST_HPP

#include <memory>
#include <string_view>
#include <variant>
#include <vector>

namespace breezy::runtime {

    // Forward declarations
    struct LiteralExpr;
    struct VariableExpr;
    struct CallExpr;

    struct VarDeclStmt;
    struct ExprStmt;

    // Expression variant
    using Expr = std::variant<
        LiteralExpr,
        VariableExpr,
        CallExpr
    >;

    // Statment variant
    using Stmt = std::variant<
        VarDeclStmt,
        ExprStmt
    >;

    /*
    =======================
    Expression node definitions
    =======================
    */

    struct LiteralExpr {
        std::variant<double, std::string_view> value;
    };

    struct VariableExpr {
        std::string_view name;
    };

    struct CallExpr {
        std::string_view callee;
        std::vector<Expr> arguments;
    };

    /*
    =======================
    Statement node definitions
    =======================
    */

    struct VarDeclStmt {
        std::string_view name;
        std::unique_ptr<Expr> initializer;
    };

    struct ExprStmt {
        Expr expression;
    };
}

#endif // !BREEZY_RUNTIME_AST_HPP

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

#include "breezy/frontend/interpreter.hpp"

#include <iostream>
#include <variant>

namespace breezy::runtime {
    void Interpreter::execute(const Stmt& stmt) {
        std::visit([this](auto&& node) { exec_node(node); }, stmt);
    }

    void Interpreter::exec_node(const VarDeclStmt& stmt) {
        double value = 0;
        if (stmt.initializer) {
            value = eval(*stmt.initializer);
        }
        environment_[stmt.name] = value;
    }

    void Interpreter::exec_node(const ExprStmt& stmt) {
        eval(stmt.expression);
    }

    double Interpreter::eval(const Expr& expr) {
        return std::visit([this](auto&& node) -> double { return eval_node(node); }, expr);
    }

    double Interpreter::eval_node(const LiteralExpr& expr) {
        if (std::holds_alternative<double>(expr.value)) {
            return std::get<double>(expr.value);
        }
        // Strings not yet evaluated to numbers
        return 0;
    }

    double Interpreter::eval_node(const VariableExpr& expr) {
        auto it = environment_.find(expr.name);
        if (it != environment_.end()) return it->second;
        std::cerr << "Undefined variable: " << expr.name << "\n";
        return 0;
    }

    double Interpreter::eval_node(const CallExpr& expr) {
        if (expr.callee == "print") {
            for (auto& arg : expr.arguments) {
                double val = eval(arg);
                std::cout << val << " ";
            }
            std::cout << "\n";
        }
        return 0;
    }
}

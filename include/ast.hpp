#pragma once
#include <cstddef>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <memory>
#include "expr.hpp"
#include "ast_helper.hpp"

// Forward declarations
namespace ast {
    class top_level {
        public:
        top_level() : exprs() {}
        
        std::vector<std::shared_ptr<ast::expr>> exprs;

        auto eval() noexcept -> void;
    };
}

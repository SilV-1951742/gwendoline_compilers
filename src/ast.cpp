#include "ast.hpp"

namespace ast {
    auto top_level::eval(interpret::context& ctx) noexcept -> void {
        for(auto e: exprs) {
            e->eval();
        }
    };
}

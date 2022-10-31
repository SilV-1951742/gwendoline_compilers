#pragma once
#include <memory>
#include <vector>
#include "ast_helper.hpp"
#include "type.hpp"
#include <iostream>


namespace ast {
    class expr : public std::enable_shared_from_this<expr> {
        public:
        expr()                                           : kind(expr_kind::NOP) {}
        expr(const char32_t c,
             const base_type t)                          : kind(expr_kind::LITERAL), expr_type(t), cval(std::move(c)) {}
        template<Integral T>
        expr(const T v,
             const base_type t)                          : kind(expr_kind::LITERAL), expr_type(t) {fill_int(v, t);}
        expr(const double v,
             const base_type t)                          : kind(expr_kind::LITERAL), expr_type(t), fval(v) {}
        expr(const mul_op op,
             std::shared_ptr<expr> l,
             std::shared_ptr<expr> r)                    : kind(expr_kind::MUL), left(l), right(r), mul(op) {}
        expr(const add_op op,
             std::shared_ptr<expr> l,
             std::shared_ptr<expr> r)                    : kind(expr_kind::ADD), left(l), right(r), add(op) {}
        expr(const comp_op op,
             std::shared_ptr<expr> l,
             std::shared_ptr<expr> r)                    : kind(expr_kind::COMP), left(l), right(r), comp(op) {}
        expr(const unary_op op,
             std::shared_ptr<expr> l)                    : kind(expr_kind::UNARY), left(l), unary(op) {}

        auto eval() noexcept -> std::vector<std::shared_ptr<expr>>;
        
        expr_kind kind;
        type_info expr_type;
    
        std::string str; // For string
        char32_t cval;
        std::int64_t ival = 0;    // For int
        std::int8_t  i8val = 0;   // For int8
        std::int16_t i16val = 0;  // For int16
        std::int32_t i32val = 0;  // For int32
        std::int64_t i64val = 0;  // For int64
        std::uint64_t uval = 0;   // For uint
        std::uint8_t  u8val = 0;  // For uint8
        std::uint16_t u16val = 0; // For uint16
        std::uint32_t u32val = 0; // For uint32
        std::uint64_t u64val = 0; // For uint64
        double fval = 0;
        std::shared_ptr<expr>  left = nullptr;
        std::shared_ptr<expr>  middle = nullptr;
        std::shared_ptr<expr>  right = nullptr;
        
        unary_op unary;
        mul_op mul;
        add_op add;
        comp_op comp;

        [[nodiscard]] auto is_literal() const noexcept -> bool {return (kind == expr_kind::LITERAL);}
        [[nodiscard]] auto get_int() const noexcept -> int64_t;
        template<typename T>
            auto fill_int(const T inval) noexcept -> void {
            switch(expr_type.btype) {
            case base_type::INT:
                ival = static_cast<int64_t>(inval);
                break;
            case base_type::INT8:
                i8val = static_cast<int8_t>(inval);
                break;
            case base_type::INT16:
                i16val = static_cast<int16_t>(inval);
                break;
            case base_type::INT32:
                i32val = static_cast<int32_t>(inval);
                break;
            case base_type::INT64:
                i64val = static_cast<int64_t>(inval);
                break;
            case base_type::UINT:
                uval = static_cast<uint64_t>(inval);
                break;
            case base_type::UINT8:
                u8val = static_cast<uint8_t>(inval);
                break;
            case base_type::UINT16:
                u16val = static_cast<uint16_t>(inval);
                break;
            case base_type::UINT32:
                u32val = static_cast<uint32_t>(inval);
                break;
            case base_type::UINT64:
                u64val = static_cast<uint64_t>(inval);
                break;
            default:
                std::cout << "[EXPR] -- invalid int type {}."
                          << base_print.at(expr_type.btype);
                break;
            }
        }
        template<typename T>
            auto fill_int(const T inval, const base_type t) noexcept -> void {
            switch(t) {
            case base_type::INT:
                ival = static_cast<int64_t>(inval);
                break;
            case base_type::INT8:
                i8val = static_cast<int8_t>(inval);
                break;
            case base_type::INT16:
                i16val = static_cast<int16_t>(inval);
                break;
            case base_type::INT32:
                i32val = static_cast<int32_t>(inval);
                break;
            case base_type::INT64:
                i64val = static_cast<int64_t>(inval);
                break;
            case base_type::UINT:
                uval = static_cast<uint64_t>(inval);
                break;
            case base_type::UINT8:
                u8val = static_cast<uint8_t>(inval);
                break;
            case base_type::UINT16:
                u16val = static_cast<uint16_t>(inval);
                break;
            case base_type::UINT32:
                u32val = static_cast<uint32_t>(inval);
                break;
            case base_type::UINT64:
                u64val = static_cast<uint64_t>(inval);
                break;
            default:
                std::cout << "[EXPR] -- invalid int type {}."
                          << base_print.at(t);
                break;
            }
        }
        private:
        [[nodiscard]] auto mul_eval() noexcept -> std::shared_ptr<expr>;
        [[nodiscard]] auto add_eval() noexcept -> std::shared_ptr<expr>;
        [[nodiscard]] auto unary_eval() noexcept -> std::shared_ptr<expr>;
    };
}

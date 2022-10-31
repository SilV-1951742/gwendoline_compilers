#include "expr.hpp"
#include "ast.hpp"
#include "ast_helper.hpp"
#include <limits>

namespace ast {
    auto expr::eval() noexcept -> std::vector<std::shared_ptr<expr>> {
        std::vector<std::shared_ptr<expr>> ret;
        switch(kind) {
        case expr_kind::NOP:
            break;
        case expr_kind::LITERAL:
            ret.push_back(shared_from_this());
            break;
        case expr_kind::ADD:
            ret.push_back(add_eval());
            break;
        case expr_kind::MUL:
            ret.push_back(mul_eval());
            break;
        case expr_kind::UNARY:
            ret.push_back(unary_eval());
            break;
        default:
            std::cout << "[EVAL_EXPR] -- Unknown expression type.\r\n";
        break;
        }
        return ret;
    }
    
    auto expr::unary_eval() noexcept -> std::shared_ptr<expr> {
        auto newl = left->eval()[0];
        base_type btype = newl->expr_type.btype;

        if(ints.count(newl->expr_type.btype)) {
            std::int64_t new_val = 0;
            switch(unary) {
            case unary_op::PLUS:
                new_val = newl->get_int();
                break;
            case unary_op::MIN:
                new_val = -newl->get_int();
                break;
            case unary_op::XOR:
                new_val = ~newl->get_int();
                break;
            default:
                std::cout << "[UNARY] -- Unary operation {} not supported on type int." << unary_print.at(unary) << "\r\n";
                exit(1);
                break;
            }
            return std::make_shared<expr>(new_val, btype);
        }
        
        switch(newl->expr_type.btype) {
        case base_type::FLOAT32: [[fallthrough]];
        case base_type::FLOAT64:
            {
                double new_val = 0.0;
                switch(unary) {
                case unary_op::PLUS:
                    new_val = newl->fval;
                    break;
                case unary_op::MIN:
                    new_val = -newl->fval;
                    break;
                default:
                    std::cout <<"[UNARY] -- Unary operation {} not supported on type float." << unary_print.at(unary) << "\r\n";
                    exit(1);
                    break;
                }
                return std::make_shared<expr>(new_val, btype); // not a literal
            }
            break;
        case base_type::BOOL:
            {
                bool new_val = false;
                switch(unary) {
                case unary_op::NOT:
                    new_val = !newl->bval;
                    break;
                default:
                    std::cout <<"[UNARY] -- Unary operation {} not supported on type bool" << unary_print.at(unary) << "\r\n";
                    exit(1);
                    break;
                }
                return std::make_shared<expr>(new_val, btype); // not a literal
            }
            break;    
        default:
            std::cout <<"[UNARY] -- Unary operation {} not supported on type {}." << unary_print.at(unary), base_print.at(btype);
            exit(1);
            break;
        }
    }
    
    auto expr::mul_eval() noexcept -> std::shared_ptr<expr> {
        auto newl = left->eval()[0];
        auto newr = right->eval()[0];
        base_type btype = base_type::NONE;

        if(newl->is_literal() || newr->is_literal()) {
            if((newl->expr_type.btype != newr->expr_type.btype) &&
               (numerics.count(newl->expr_type.btype) > 0) &&
               (numerics.count(newr->expr_type.btype) > 0)) {
                cast_literal(newl, newr, btype);
            }
            if(newl->expr_type.btype != newr->expr_type.btype) {
                std::cout <<"[MUL] -- Type mismatch between {} and {}" << base_print.at(newl->expr_type.btype), base_print.at(newr->expr_type.btype);
                exit(1);
            }

            if(newl->is_literal()) {
                btype = newr->expr_type.btype;
            } else {
                btype = newl->expr_type.btype;
            }
        } else {
            if(newl->expr_type.btype != newr->expr_type.btype) {
                std::cout <<"[MUL] -- Type mismatch between {} and {}" << base_print.at(newl->expr_type.btype), base_print.at(newr->expr_type.btype);
                exit(1);
            }
            btype = newl->expr_type.btype;
        }
        
        if(ints.count(newl->expr_type.btype) > 0) {
            auto l_val = newl->get_int();
            auto r_val = newr->get_int();
            std::int64_t new_val = 0;
            switch(mul) {
            case mul_op::MUL:
                new_val = l_val * r_val;
                break;
            case mul_op::DIV:
                new_val = l_val / r_val;
                break;
            case mul_op::MOD:
                new_val = l_val % r_val;
                break;
            case mul_op::LSHIFT:
                if(newr->ival < 0) {
                    std::cout <<"[MUL] -- Can't lshift with value less than 0 -- {}" << newr->ival;
                    exit(1);
                }
                new_val = l_val << r_val;
                break;
            case mul_op::RSHIFT:
                if(newr->ival < 0) {
                    std::cout <<"[MUL] -- Can't rshift with value less than 0 -- {}" << newr->ival;
                    exit(1);
                }
                new_val = l_val >> r_val;
                break;
            case mul_op::AND:
                new_val = l_val & r_val;
                break;
            case mul_op::AND_XOR:
                new_val = l_val & !r_val;
                break;
            }
            return std::make_shared<expr>(new_val, btype);
        } else {
                switch(btype) {
                case base_type::FLOAT32: [[fallthrough]];
                case base_type::FLOAT64:
                    {
                        double new_val = 0.0;
                        switch(mul) {
                        case mul_op::MUL:
                            new_val = newl->fval * newr->fval;
                            break;
                        case mul_op::DIV:
                            new_val = newl->fval / newr->fval;
                            break;
                        case mul_op::MOD:
                            std::cout <<"[MUL] -- Can't mod floats.";
                            exit(1);
                            break;
                        case mul_op::LSHIFT:
                            std::cout <<"[MUL] -- Can't lshift floats.";
                            exit(1);
                            break;
                        case mul_op::RSHIFT:
                            std::cout <<"[MUL] -- Can't rshift floats.";
                            exit(1);
                            break;
                        case mul_op::AND:
                            std::cout <<"[MUL] -- Can't and floats.";
                            exit(1);
                            break;
                        case mul_op::AND_XOR:
                            std::cout <<"[MUL] -- Can't and_xor floats.";
                            exit(1);
                            break;
                        }
                        return std::make_shared<expr>(new_val, btype); // not a literal
                    }
                    break;
                default:
                    std::cout <<"[MUL] -- Can't perform multiplication on {} types" << base_print.at(newl->expr_type.btype);
                    exit(1);
                    break;
                }
        }
    }

    auto expr::add_eval() noexcept -> std::shared_ptr<expr> {
        
        auto newl = left->eval()[0];
        auto newr = right->eval()[0];
        base_type btype = base_type::NONE;
        
        if(newl->is_literal() || newr->is_literal()) {
            if((newl->expr_type.btype != newr->expr_type.btype) &&
               (numerics.count(newl->expr_type.btype) > 0) &&
               (numerics.count(newr->expr_type.btype) > 0)) {
                cast_literal(newl, newr, btype);
            }
            if(newl->expr_type.btype != newr->expr_type.btype) {
                std::cout <<"[ADD] -- Type mismatch between {} and {}"
                          << base_print.at(newl->expr_type.btype)
                          << base_print.at(newr->expr_type.btype);
                exit(1);
            }
            
            if(newl->is_literal()) {
                btype = newr->expr_type.btype;
            } else {
                btype = newl->expr_type.btype;
            }
        } else {
            if(newl->expr_type.btype != newr->expr_type.btype) {
                std::cout <<"[ADD] -- Type mismatch between {} and {}"
                          << base_print.at(newl->expr_type.btype)
                          << base_print.at(newr->expr_type.btype);
                exit(1);
            }
            btype = newl->expr_type.btype;
        }

        
        if(ints.count(newl->expr_type.btype) > 0) {
            auto l_val = newl->get_int();
            auto r_val = newr->get_int();
            std::int64_t new_val = 0;
            switch(add) {
            case add_op::PLUS:
                new_val = l_val + r_val;
                break;
            case add_op::MIN:
                new_val = l_val - r_val;
                break;
            case add_op::OR:
                new_val = l_val | r_val;
                break;
            case add_op::XOR:
                new_val = l_val ^ r_val;
                break;
            }
            return std::make_shared<expr>(new_val, btype);
        } else {
            switch(btype) {
            case base_type::FLOAT32: [[fallthrough]];
            case base_type::FLOAT64:
                {
                    double new_val = 0.0;
                    switch(add) {
                    case add_op::PLUS:
                        new_val = newl->fval + newr->fval;
                        break;
                    case add_op::MIN:
                        new_val = newl->fval + newr->fval;
                        break;
                    case add_op::OR:
                        std::cout <<"[ADD] -- Can't bitwise OR on {} types" << base_print.at(newl->expr_type.btype);
                        exit(1);
                        break;
                    case add_op::XOR:
                        std::cout <<"[ADD] -- Can't bitwise XOR on {} types" << base_print.at(newl->expr_type.btype);
                        exit(1);
                        break;
                    }
                    return std::make_shared<expr>(new_val, btype); // not a literal
                }
            break;
            case base_type::STRING:
                {
                    std::string new_val;
                    switch(add) {
                    case add_op::PLUS:
                        new_val = newl->str;
                
                        new_val = new_val.append(newr->str);
                        break;
                    case add_op::MIN:
                        std::cout <<"[ADD] -- Can't subtract on {} types" << base_print.at(newl->expr_type.btype);
                        exit(1);
                        break;
                    case add_op::OR:
                        std::cout <<"[ADD] -- Can't bitwise OR on {} types" << base_print.at(newl->expr_type.btype);
                        exit(1);
                        break;
                    case add_op::XOR:
                        std::cout <<"[ADD] -- Can't bitwise XOR on {} types" << base_print.at(newl->expr_type.btype);
                        exit(1);
                        break;
                    }
                    return std::make_shared<expr>(std::move(new_val), btype); // not a literal
                }
                break;
            default:
                std::cout <<"[ADD] -- Can't perform addition on {} types" << base_print.at(newl->expr_type.btype);
                exit(1);
                break;
            }
        }
    }

    [[nodiscard]] auto expr::get_int() const noexcept -> int64_t {
        switch(expr_type.btype) {
        case base_type::INT:
            return static_cast<int64_t>(ival);
            break;
        case base_type::INT8:
            return static_cast<int64_t>(i8val);
            break;
        case base_type::INT16:
            return static_cast<int64_t>(i16val);
            break;
        case base_type::INT32:
            return static_cast<int64_t>(i32val);
            break;
        case base_type::INT64:
            return static_cast<int64_t>(i64val);
            break;
        case base_type::UINT:
            return static_cast<int64_t>(uval);
            break;
        case base_type::UINT8:
            return static_cast<int64_t>(u8val);
            break;
        case base_type::UINT16:
            return static_cast<int64_t>(u16val);
            break;
        case base_type::UINT32:
            return static_cast<int64_t>(u32val);
            break;
        case base_type::UINT64:
            return static_cast<int64_t>(u64val);
            break;
        default:
            std::cout <<"[EXPR] -- get_int: invalid int type {}."
                      << base_print.at(expr_type.btype);
            exit(1);
            break;
        }
        return 0;
    }
}

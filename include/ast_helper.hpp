#pragma once
#include <cstdint>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <set>

namespace ast {
    enum class id_kind {
        UNDEFINED,
        IMPORT,
        FUNCTION,
        PARAMETER,
        VARIABLE,
        TYPE,
        INTERFACE,
        SELECTOR
    };
    
    const static std::map<id_kind, std::string> id_print {{id_kind::UNDEFINED, "undefined"},
                                                          {id_kind::IMPORT, "import"},
                                                          {id_kind::FUNCTION, "function"},
                                                          {id_kind::PARAMETER, "parameter"},
                                                          {id_kind::VARIABLE, "variable"},
                                                          {id_kind::TYPE, "type"},
                                                          {id_kind::INTERFACE, "interface"}};

    enum class type_kind {
        BASE,
        COMP,
        FUNC,
        STRUCT,
        ARRAY
    };

    const static std::map<type_kind, std::string> type_print {{type_kind::BASE, "base"},
                                                              {type_kind::COMP, "comp"},
                                                              {type_kind::FUNC, "func"},
                                                              {type_kind::STRUCT, "struct"},
                                                              {type_kind::ARRAY, "array"}};

    enum class base_type {
        NONE,
        BOOL,
        STRING,
        INT,
        INT8,
        INT16,
        INT32,
        INT64,
        UINT,
        UINT8,
        UINT16,
        UINT32,
        UINT64,
        UINTPTR,
        BYTE,
        RUNE,
        FLOAT32,
        FLOAT64,
        COMPLEX64,
        COMPLEX128
    };

    template<class T>
        concept Integral = std::is_integral<T>::value;
    
    const static std::set<base_type> numerics{base_type::INT, base_type::INT8, base_type::INT16, base_type::INT32, base_type::INT64,
                                             base_type::UINT, base_type::UINT8, base_type::UINT16, base_type::UINT32, base_type::UINT64,
                                             base_type::FLOAT32, base_type::FLOAT64};
    const static std::set<base_type> ints{base_type::INT, base_type::INT8, base_type::INT16, base_type::INT32, base_type::INT64,
                                          base_type::UINT, base_type::UINT8, base_type::UINT16, base_type::UINT32, base_type::UINT64};
    const static std::set<base_type> signed_ints{base_type::INT, base_type::INT8, base_type::INT16, base_type::INT32, base_type::INT64};
    const static std::set<base_type> unsigned_ints{base_type::UINT, base_type::UINT8, base_type::UINT16, base_type::UINT32, base_type::UINT64};
    const static std::set<base_type> floats{base_type::FLOAT32, base_type::FLOAT64};

    const static std::map<base_type, std::pair<std::int64_t, std::int64_t>> int_limits {{base_type::INT,
                                                                                          {std::numeric_limits<std::int32_t>::min(),
                                                                                           std::numeric_limits<std::int32_t>::max()}},
                                                                                         {base_type::INT8,
                                                                                          {std::numeric_limits<std::int8_t>::min(),
                                                                                           std::numeric_limits<std::int8_t>::max()}},
                                                                                         {base_type::INT16,
                                                                                          {std::numeric_limits<std::int16_t>::min(),
                                                                                           std::numeric_limits<std::int16_t>::max()}},
                                                                                         {base_type::INT32,
                                                                                          {std::numeric_limits<std::int32_t>::min(),
                                                                                           std::numeric_limits<std::int32_t>::max()}},
                                                                                         {base_type::INT64,
                                                                                          {std::numeric_limits<std::int64_t>::min(),
                                                                                           std::numeric_limits<std::int64_t>::max()}},
                                                                                         {base_type::UINT,
                                                                                          {std::numeric_limits<std::uint32_t>::min(),
                                                                                           std::numeric_limits<std::uint32_t>::max()}},
                                                                                         {base_type::UINT8,
                                                                                          {std::numeric_limits<std::uint8_t>::min(),
                                                                                           std::numeric_limits<std::uint8_t>::max()}},
                                                                                         {base_type::UINT16,
                                                                                          {std::numeric_limits<std::uint16_t>::min(),
                                                                                           std::numeric_limits<std::uint16_t>::max()}},
                                                                                         {base_type::UINT32,
                                                                                          {std::numeric_limits<std::uint32_t>::min(),
                                                                                           std::numeric_limits<std::uint32_t>::max()}},
                                                                                         {base_type::UINT64,
                                                                                          {std::numeric_limits<std::uint64_t>::min(),
                                                                                           std::numeric_limits<std::uint64_t>::max()}}};

    const static std::map<base_type, std::pair<std::int64_t, std::int64_t>> sint_limits {{base_type::INT,
                                                                                         {std::numeric_limits<std::int32_t>::min(),
                                                                                          std::numeric_limits<std::int32_t>::max()}},
                                                                                        {base_type::INT8,
                                                                                         {std::numeric_limits<std::int8_t>::min(),
                                                                                          std::numeric_limits<std::int8_t>::max()}},
                                                                                        {base_type::INT16,
                                                                                         {std::numeric_limits<std::int16_t>::min(),
                                                                                          std::numeric_limits<std::int16_t>::max()}},
                                                                                        {base_type::INT32,
                                                                                         {std::numeric_limits<std::int32_t>::min(),
                                                                                          std::numeric_limits<std::int32_t>::max()}},
                                                                                        {base_type::INT64,
                                                                                         {std::numeric_limits<std::int64_t>::min(),
                                                                                          std::numeric_limits<std::int64_t>::max()}}};

    const static std::map<base_type, std::pair<std::int64_t, std::uint64_t>> uint_limits {{base_type::UINT,
                                                                                           {std::numeric_limits<std::uint32_t>::min(),
                                                                                            std::numeric_limits<std::uint32_t>::max()}},
                                                                                          {base_type::UINT8,
                                                                                           {std::numeric_limits<std::uint8_t>::min(),
                                                                                            std::numeric_limits<std::uint8_t>::max()}},
                                                                                          {base_type::UINT16,
                                                                                           {std::numeric_limits<std::uint16_t>::min(),
                                                                                            std::numeric_limits<std::uint16_t>::max()}},
                                                                                          {base_type::UINT32,
                                                                                           {std::numeric_limits<std::uint32_t>::min(),
                                                                                            std::numeric_limits<std::uint32_t>::max()}},
                                                                                          {base_type::UINT64,
                                                                                           {std::numeric_limits<std::uint64_t>::min(),
                                                                                            std::numeric_limits<std::uint64_t>::max()}}};
    
    const static std::map<base_type, std::string> base_print {{base_type::NONE, "none"},
                                                              {base_type::BOOL, "bool"},
                                                              {base_type::STRING, "string"},
                                                              {base_type::INT, "int"},
                                                              {base_type::INT8, "int8"},
                                                              {base_type::INT16, "int16"},
                                                              {base_type::INT32, "int32"},
                                                              {base_type::INT64, "int64"},
                                                              {base_type::UINT, "uint"},
                                                              {base_type::UINT8, "uint8"},
                                                              {base_type::UINT16, "uint16"},
                                                              {base_type::UINT32, "uint32"},
                                                              {base_type::UINT64, "uint64"},
                                                              {base_type::UINTPTR, "uintptr"},
                                                              {base_type::BYTE, "byte"},
                                                              {base_type::RUNE, "rune"},
                                                              {base_type::FLOAT32, "float32"},
                                                              {base_type::FLOAT64, "float64"},
                                                              {base_type::COMPLEX64, "complex64"},
                                                              {base_type::COMPLEX128, "complex128"}};

    const static std::map<std::string, base_type> str_to_base {{"none", base_type::NONE},
                                                               {"bool", base_type::BOOL},
                                                               {"string", base_type::STRING},
                                                               {"int", base_type::INT},
                                                               {"int8", base_type::INT8},
                                                               {"int16", base_type::INT16},
                                                               {"int32", base_type::INT32},
                                                               {"int64", base_type::INT64},
                                                               {"uint", base_type::UINT},
                                                               {"uint8", base_type::UINT8},
                                                               {"uint16", base_type::UINT16},
                                                               {"uint32", base_type::UINT32},
                                                               {"uint64", base_type::UINT64},
                                                               {"uintptr", base_type::UINTPTR},
                                                               {"byte", base_type::BYTE},
                                                               {"rune", base_type::RUNE},
                                                               {"float32", base_type::FLOAT32},
                                                               {"float64", base_type::FLOAT64},
                                                               {"complex64", base_type::COMPLEX64},
                                                               {"complex128", base_type::COMPLEX128}};
    
    enum class binary_kind {
        COMPARISON,
        ADD,
        MUL
    };

    const static std::map<binary_kind, std::string> binary_print {{binary_kind::COMPARISON, "comparison"},
                                                                  {binary_kind::ADD, "add"},
                                                                  {binary_kind::MUL, "mul"}};

    enum class mul_op {
        MUL, DIV, MOD, LSHIFT, RSHIFT, AND, AND_XOR
    };

    const static std::map<mul_op, std::string> mul_print {{mul_op::MUL, "mul"},
                                                          {mul_op::DIV, "div"},
                                                          {mul_op::MOD, "mod"},
                                                          {mul_op::LSHIFT, "lshift"},
                                                          {mul_op::RSHIFT, "rshift"},
                                                          {mul_op::AND, "and"},
                                                          {mul_op::AND_XOR, "and-xor"}};
        
    enum class add_op {
        PLUS, MIN, OR, XOR
    };

    const static std::map<add_op, std::string> add_print {{add_op::PLUS, "plus"},
                                                          {add_op::MIN, "min"},
                                                          {add_op::OR, "or"},
                                                          {add_op::XOR, "xor"}};

    enum class comp_op {
        EQEQ, NEQ, LT, LE, GT, GE, LOGICAL_AND, LOGICAL_OR
    };

    const static std::map<comp_op, std::string> comp_print {{comp_op::EQEQ, "eqeq"},
                                                            {comp_op::NEQ, "neq"},
                                                            {comp_op::LT, "lt"},
                                                            {comp_op::LE, "le"},
                                                            {comp_op::GT, "gt"},
                                                            {comp_op::GE, "ge"},
                                                            {comp_op::LOGICAL_AND, "logical_and"},
                                                            {comp_op::LOGICAL_OR, "logical_or"}};

    enum class unary_op {
        PLUS, MIN, NOT, XOR, MUL, AND, OPCHAN
    };

    const static std::map<unary_op, std::string> unary_print {{unary_op::PLUS, "plus"},
                                                              {unary_op::MIN, "min"},
                                                              {unary_op::NOT, "not"},
                                                              {unary_op::XOR, "complement"},
                                                              {unary_op::MUL, "mul"},
                                                              {unary_op::AND, "and"},
                                                              {unary_op::OPCHAN, "opchan"}};

    enum class assign_op {
        EQ, MIN_EQ, PLUS_EQ, MUL_EQ, DIV_EQ, MOD_EQ, AND_EQ, OR_EQ, XOR_EQ, LSHIFT_EQ, RSHIFT_EQ
    };

    const static std::map<assign_op, std::string> assign_print {{assign_op::EQ, "eq"},
                                                                {assign_op::MIN_EQ, "min_eq"},
                                                                {assign_op::PLUS_EQ, "plus_eq"}};
        
    // enum class expr_kind {
    //     NOP,
    //     OPERAND, FUNC_CALL, ARRAY,           //
    //     STRING, INT, UINT, FLOAT,  BOOL,     // 
    //     CHARACTER,  IDENTIFIER, LITERAL,     // PRIMARY EXPR -> OPERAND
    //     CONVERSION, SELECTOR, INDEX, SLICE,  // PRIMARY EXPR
    //     ADD, MUL, COMP, UNARY                // OPERATION
    // };

    // const static std::map<expr_kind, std::string> expr_print{{expr_kind::NOP, "nop"},
    //                                                          {expr_kind::OPERAND, "operand"},   {expr_kind::FUNC_CALL, "func_call"},
    //                                                          {expr_kind::ARRAY, "array"},
    //                                                          {expr_kind::INT, "int"},           {expr_kind::FLOAT, "float"},
    //                                                          {expr_kind::BOOL, "bool"},         {expr_kind::CHARACTER, "char"},
    //                                                          {expr_kind::IDENTIFIER, "id"},     {expr_kind::LITERAL, "literal"},
    //                                                          {expr_kind::CONVERSION, "conv"},   {expr_kind::SELECTOR, "selector"},
    //                                                          {expr_kind::INDEX, "index"},       {expr_kind::SLICE, "slice"},
    //                                                          {expr_kind::ADD, "add"},           {expr_kind::MUL, "mul"},
    //                                                          {expr_kind::COMP, "comp"},         {expr_kind::UNARY, "unary"}};

    enum class expr_kind {
        NOP,
        VAR_VAL,
        LITERAL, IDENTIFIER,                 // PRIMARY
        CONVERSION, SELECTOR,                // PRIMARY
        INDEX, SLICE, FUNC_CALL,             // PRIMARY
        BUILTIN,                             // PRIMARY
        ADD, MUL, COMP, UNARY                // OPERATION
    };

    enum class builtins {
        NONE, PRINT, LEN
    };

    const static std::map<expr_kind, std::string> expr_print{{expr_kind::NOP, "nop"},
                                                             {expr_kind::LITERAL, "literal"},
                                                             {expr_kind::IDENTIFIER, "identifier"},
                                                             {expr_kind::CONVERSION, "conv"},
                                                             {expr_kind::SELECTOR, "selector"},
                                                             {expr_kind::INDEX, "index"},
                                                             {expr_kind::SLICE, "slice"},
                                                             {expr_kind::ADD, "add"},
                                                             {expr_kind::MUL, "mul"},
                                                             {expr_kind::COMP, "comp"},
                                                             {expr_kind::UNARY, "unary"}};

    enum class literal_kind {
        BASIC, FUNC, COMP
    };

    const static std::map<literal_kind, std::string> literal_print{{literal_kind::BASIC, "basic_lit"},
                                                                   {literal_kind::FUNC, "func_lit"},
                                                                   {literal_kind::COMP, "comp_lit"}};

    enum class operand_kind {
        LITERAL, ID, EXPR
    };

    const static std::map<operand_kind, std::string> operand_print{{operand_kind::LITERAL, "literal"},
                                                                   {operand_kind::ID, "id"},
                                                                   {operand_kind::EXPR, "expr"}};

    enum class stmt_kind {
        STMTS, STMT, PRINT, BLOCK, SIMPLE, LABELED, INCDEC, ASSIGN, RETURN, IF, ELSE, INIT, POST, FOR, COND, FOR_CLAUSE, BREAK, CONTINUE, LEN,
        VARDCL, VARSPEC, SHORTVARDCL, FNDCL, SIGNATURE, PARAM_LIST, PARAM_DECL, FCALL, ARGS, EXPR_SWITCH, SWITCH
    };

    enum class block_kind {
        NONE, FUNCTION, FOR, IF, CASE
    };

    enum class simple_stmt_kind {
        EXPR_LIST, LABELED, INCDEC, ASSIGN, SHORTVARDCL, LEN
    };

    enum class for_kind {
        WHILE, COND, CLAUSE, RANGE
    };

    enum class incdec_kind {
        INC, DEC
    };

    class expr;

    enum class stop_condition {
        NONE, RETURN, BREAK, CONTINUE
    };
}

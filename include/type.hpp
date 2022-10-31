#pragma once
#include "ast_helper.hpp"


namespace ast{
    class type_info {
        public:
        type_info(const bool a = false,
                  const std::shared_ptr<expr>& al = nullptr) :
            kind(type_kind::BASE),
            name(),
            btype(base_type::NONE),
            array(a),
            array_len(al) {}
        type_info(base_type b,
                  const bool a = false,
                  const std::shared_ptr<expr>& al = nullptr) :
            kind(type_kind::BASE),
            name(),
            btype(b),
            array(a),
            array_len(al) {}
        type_info(type_kind t,
                  std::string s,
                  base_type b,
                  const bool a = false,
                  const std::shared_ptr<expr>& al = nullptr) :
            kind(t),
            name(s),
            btype(b),
            array(a),
            array_len(al) {}
        type_kind kind;
        std::string name;
        base_type btype;
        bool array = false;
        std::shared_ptr<expr> array_len;
    };
}

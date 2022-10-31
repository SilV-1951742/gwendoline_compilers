#pragma once
#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer goFlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL go::parser::symbol_type go::scanner::get_next_token()

#include "bison-parser.hpp"

namespace go {
  class driver;

  class scanner : public yyFlexLexer {
  public:

    scanner(driver &driver, std::istream *in) : yyFlexLexer(in), drv(driver) {}

    virtual go::parser::symbol_type get_next_token();
    virtual ~scanner() { }

  private:

    driver &drv;
  };

}

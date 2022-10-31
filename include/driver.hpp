#pragma once
#include <memory>
#include "ast.hpp"
#include "bison-parser.hpp"
// #include "lex_context.hpp"
#include "scanner.hpp"
#include "location.hh"
// #include "symbols.hpp"
#include <iostream>
#include <sstream>
#include <fstream>


namespace go {
  class driver {
  public:
      driver() : loc(0),
                 root(new ast::top_level()) {}

      std::string file;

      void error(const std::string& m) {
          std::cout << "Error at " << m;
      }
      void error(const location& l, const std::string& m) {
          std::cout << "Error at " << l.begin.line << ":" << l.begin.column << " -- " << m  << "\r\n";
      }

      [[nodiscard]] auto parse_file(const std::string& filename) noexcept -> std::shared_ptr<ast::top_level> {
          std::ifstream f(filename);
          std::stringstream buffer;
        
          if(f) {
              buffer << f.rdbuf();
          }
          f.close();
          loc.initialize(&filename, 1, 0);
          auto lexer = go::scanner(*this, &buffer);
          // go::parser parser(lexer, *this, root);
          go::parser parser(lexer, *this);
          parser.set_debug_level(false);
          if(parser.parse() == 0) {
              std::cout << "Parsing succeeded!\r\n";
          } else {
              std::cout << "Parsing failed!\r\n";
              exit(1);
          }
        
          return root;
      }

      [[nodiscard]] auto get_root() const noexcept -> std::shared_ptr<ast::top_level> { return root; }
      auto increase_loc(int iloc) -> void {
          loc += iloc;
          // spdlog::info("Increase loc {} -- current line {}", iloc, loc.end.line);
      }

      go::location loc;

      auto line() noexcept ->  int {return loc.end.line;}
      auto column() noexcept -> int {return loc.end.column;}
      
      private:
      std::shared_ptr<ast::top_level> root;
  };
}

#include <cstdlib>
#include <vector>
#include <string>
#include <filesystem>
// #include "ast.hpp"
// #include "interpreter.hpp"
#include "scanner.hpp"
#include "driver.hpp"

namespace argp {
    class args_parser {
        public:
        args_parser(int& argc, char** argv) {
            if(argc > 2 || argc < 2) {
                std::cout << "[ARG_PARSER] -- incorrect amount of arguments, need 1.\r\n";
                exit(1);
            }
            
            for (int64_t i = 1; i < argc; i++) {
                tokens.push_back(std::string(argv[i]));
            }
        }
        
        [[nodiscard]] auto input_file() const noexcept -> std::string {
            return tokens.at(0);
        }

        private:
        std::vector<std::string> tokens;
    };
}

auto main(int32_t argc, char** argv) -> int {
    std::cout << "Starting compilers project!\r\n";
    auto parser = argp::args_parser(argc, argv);
    auto fname = parser.input_file();

    const std::filesystem::path fpath(fname);
    // && fpath.extension() == std::filesystem::path(".go"))
    
    if(!(std::filesystem::exists(fpath) &&
         std::filesystem::is_regular_file(fpath))) {
        std::cout << "[MAIN] -- input file doesn't exist or isn't a golang file.\r\n";
        exit(1);
    }
    
    go::driver driver;
    auto root = driver.parse_file(fname);
    
    // auto interpreter = interpret::interpreter(root);
    // interpreter.interpret();
    
    return EXIT_SUCCESS;
}

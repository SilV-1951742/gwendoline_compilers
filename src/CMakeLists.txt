set(INCLUDE_DIR "${compilers_SOURCE_DIR}/include")

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${compilers_SOURCE_DIR}/include/*.hpp")

add_subdirectory(flex-bison)

add_executable(compilers
  main.cpp
  # ast.cpp
  # expr.cpp
  # ${FLEX_flex-scanner_OUTPUTS}
  # ${BISON_bison-parser_OUTPUTS}
  )

add_dependencies(compilers copy_assets)

set_target_properties(compilers PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(compilers PUBLIC cxx_std_20)

target_compile_options(compilers PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wshadow -Wold-style-cast -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Werror)

# target_compile_options(compilers PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wshadow -Wold-style-cast -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2 -Werror)


target_link_libraries(compilers PRIVATE
  # spdlog::spdlog
  # fmt::fmt
  # Threads::Threads
  # ${FLEX_LIBRARIES}
  flex-bison
  # ${FLEX_flex-scanner_OUTPUTS}
  # ${BISON_bison-parser_OUTPUTS}
  )

target_include_directories(compilers PUBLIC
  # ${SPDLOG_INCLUDE_DIRS}
  # ${FMT_INCLUDE_DIRS}
  ${INCLUDE_DIR}
  # ${FLEX_BISON_DIR}
)

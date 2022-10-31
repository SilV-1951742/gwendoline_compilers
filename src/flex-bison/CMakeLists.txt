bison_target(bison-parser bison-parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/bison-parser.cpp
  # COMPILE_FLAGS "-Wcounterexamples"
  VERBOSE output)
flex_target(flex-scanner flex-scanner.lpp ${CMAKE_CURRENT_BINARY_DIR}/flex-scanner.cpp
  DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/flex-scanner.hpp"
)

ADD_FLEX_BISON_DEPENDENCY(flex-scanner bison-parser)

set_source_files_properties(
  ${BISON_bison-parser_OUTPUTS}
  PROPERTIES
  COMPILE_FLAGS "-w"
)

set_source_files_properties(
  ${FLEX_flex-scanner_OUTPUTS}
  PROPERTIES
  COMPILE_FLAGS "-w"
)


add_library(flex-bison STATIC
    ${SRC}
    ${BISON_bison-parser_OUTPUTS}
    ${FLEX_flex-scanner_OUTPUTS})

target_link_libraries(flex-bison
  # PUBLIC ${FLEX_LIBRARIES}
)

target_include_directories(flex-bison
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

file(GLOB HEADER_LIST CONFIGURE_DEPENDS ${BISON_bison-parser_OUTPUTS} ${FLEX_flex-scanner_OUTPUTS})
  
  # IDEs should put the headers in a nice place
source_group(
  TREE "${CMAKE_CURRENT_BINARY_DIR}"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

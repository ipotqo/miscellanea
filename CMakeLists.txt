cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

project (
    miscellanea
    VERSION
        0.0.0
    DESCRIPTION
        "Various Tidbits and Trivia of the Useful and/or Useless Kind"
    LANGUAGES
        C CXX
)

set (
    SOURCE_DIR
    src
)

add_executable (
    erasure
    ${SOURCE_DIR}/erasure.cpp
)

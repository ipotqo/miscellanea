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

file( GLOB SOURCE_FILES src/*.cpp )

foreach(SOURCE_PATH ${SOURCE_FILES})

    get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})

endforeach(SOURCE_PATH ${SOURCE_FILES})

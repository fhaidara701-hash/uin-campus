cmake_minimum_required(VERSION 3.20)
project(uin-campus CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(UIN_ACTIVER_SANITIZERS "Activer AddressSanitizer et UndefinedBehaviorSanitizer" OFF)

add_library(uincampus_core
    src/version.cpp
    src/regles.cpp
    src/saisie.cpp
    src/calculs.cpp
)

target_include_directories(uincampus_core PUBLIC include)
target_compile_definitions(uincampus_core PRIVATE UIN_VERSION="0.1.0")
target_compile_options(uincampus_core PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
)

if(UIN_ACTIVER_SANITIZERS)
    target_compile_options(uincampus_core PRIVATE -fsanitize=address,undefined)
    target_link_options(uincampus_core PUBLIC -fsanitize=address,undefined)
endif()

add_executable(uin-campus app/main.cpp)
target_link_libraries(uin-campus PRIVATE uincampus_core)
target_compile_options(uin-campus PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
)
if(UIN_ACTIVER_SANITIZERS)
    target_compile_options(uin-campus PRIVATE -fsanitize=address,undefined)
endif()

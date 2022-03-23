cmake_minimum_required(VERSION 3.2)

project(ludo2p)
cmake_policy(SET CMP0076 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan_cmake)

#set( testd off)
if (${testd})
message(WARNING ${testd})
endif()
enable_testing()


find_package(OpenSSL REQUIRED)
find_package(asio REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

set(OPENSSL_USE_STATIC_LIBS TRUE)

set(Core core)

set(CommonFlg -Wall --std=c++20 -fPIC -g3)

set(CommonLib fmt::fmt OpenSSL::SSL OpenSSL::Crypto asio::asio SQLite::SQLite3)

set(CommonSrc src/helper.cpp)


# ------------C${Core}
add_library(${Core} SHARED)
# add_executable(${Core} )

set(SOURCES src/core.cpp src/piece.cpp src/global.cpp src/square.cpp ${CommonSrc})

# target_precompile_headers(${Core} PUBLIC includes/defs.h)
target_include_directories(${Core} PUBLIC includes)
target_sources(${Core} PRIVATE ${SOURCES})
target_link_libraries(${Core} PRIVATE ${CommonLib} )
target_compile_features(${Core} PRIVATE cxx_std_23)
target_compile_options(${Core} PRIVATE ${CommonFlg}) # -fno-exceptions

if (${Godot})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/godot/src_godot)
endif()
if (${TargetApp})
    message(WARNING "hi")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/consoleapp)
endif()
if (${EnableTest})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

#pragma once
#if __clang__ || __GNUC__
    #define where __FILE__ , __PRETTY_FUNCTION__ , __LINE__
#else
    #define where __FILE__, __function__, __LINE__
#endif
//#define ASIO_ENABLE_HANDLER_TRACKING


#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/format.h>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <istream>
#include <memory>
#include <streambuf>
#include <system_error>
#include <thread>
#include <vector>
#include <functional>
#include <asio.hpp>

//#include "style.h"



using namespace std::placeholders;


//using fmt::print;
extern bool once;


using std::string;



string checkec( std::error_code ec, string file, string func, int line, string msg="" );
string checkec( string file, string func, int line, string msg ="");
string showSock(asio::ip::tcp::socket&);





extern fmt::text_style eStyle ;
extern fmt::text_style wStyle ;
extern fmt::text_style okStyle ;
extern fmt::text_style liStyle;
extern fmt::text_style orStyle;
extern fmt::text_style grStyle;
extern fmt::text_style yeStyle;
extern fmt::text_style fwStyle;
extern fmt::text_style bvStyle;
extern void printallstyle();


//!wow
//@ano
//#asdf
//$omg
//%nopo
//^crra
//&io
//* asdf
//(asd

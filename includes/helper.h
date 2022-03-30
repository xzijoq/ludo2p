#pragma once

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include <cstdint>
#include <iostream>

#include "u64def.h"
//#include "style.h"

#if __clang__ || __GNUC__
    #define where __FILE__, __PRETTY_FUNCTION__, __LINE__
#else
    #define where __FILE__, __function__, __LINE__
#endif
//#define ASIO_ENABLE_HANDLER_TRACKING
//#define CompileDebug
#ifdef CompileDebug
    #define check_p( condition, message )                                      \
        do {                                                                   \
            if ( !( condition ) )                                              \
            {                                                                  \
                fmt::print( orStyle, "\n{} FAILED ", #condition );             \
                std::cout << message;                                          \
                fmt::print( " {} {} {} ", __FILE__, __PRETTY_FUNCTION__,       \
                            __LINE__ );                                        \
                std::cout.flush();                                             \
            }                                                                  \
        } while ( false )

    #define check_f( condition )                                               \
        do {                                                                   \
            if ( !( condition ) )                                              \
            {                                                                  \
                fmt::print( orStyle, "\n{} FAILED ", #condition );             \
                fmt::print( " {} {} {} ", __FILE__, __PRETTY_FUNCTION__,       \
                            __LINE__ );                                        \
                std::cout.flush();                                             \
                std::terminate();                                              \
            }                                                                  \
        } while ( false )

    #define check_fp( condition, message )                                     \
        do {                                                                   \
            if ( !( condition ) )                                              \
            {                                                                  \
                fmt::print( orStyle, "\n{} FAILED ", #condition );             \
                std::cout << message;                                          \
                fmt::print( " {} {} {} ", __FILE__, __PRETTY_FUNCTION__,       \
                            __LINE__ );                                        \
                std::cout.flush();                                             \
                std::terminate();                                              \
            }                                                                  \
        } while ( false )

    #define check_d( message )                                                 \
        fmt::print( grStyle, " {} {} {} ", __FILE__, __PRETTY_FUNCTION__,      \
                    __LINE__ );                                                \
        std::cout << message;                                                  \
        std::cout.flush();
#else

    #define check_p( condition, message )                                      \
        {                                                                      \
        }
    #define check_f( condition )                                               \
        {                                                                      \
        }
    #define check_fp( condition, message )                                     \
        {                                                                      \
        }
    #define check_d( message )                                                 \
        {                                                                      \
        }

#endif

// using fmt::print;
extern bool once;

using std::string;

// void DisplayBits( u64 num, int sp = 8, bool val = false );
inline void DisplayBits( u64 num, int sp = 8, bool val = false )
{
    using std::cout;
    cout << "\n";
    for ( auto i = 63; i >= 0; i-- )
    {
        if ( ( num & (u64)1 << i ) )
        {
            if ( val ) { cout << "(" << ( num & (u64)1 << i ) << ")"; }
            else { cout << 1; }
        }
        else { cout << 0; }
        if ( ( i ) % sp == 0 ) { cout << " "; }
        if ( ( i ) % 4 == 0 && sp == 8 ) { cout << " "; }
    }
    cout << "\n";
}

constexpr inline fmt::text_style eStyle =
    ( fg( fmt::color::navy ) ) | ( fmt::emphasis::bold ) |
    ( bg( fmt::color::blanched_almond ) | ( fmt::emphasis::underline ) );

constexpr inline fmt::text_style wStyle =
    ( fg( fmt::color::yellow ) ) | ( fmt::emphasis::bold ) |
    ( bg( fmt::color::black ) | ( fmt::emphasis::underline ) );
constexpr inline fmt::text_style okStyle =
    fg( fmt::color::steel_blue ) | fmt::emphasis::bold;

constexpr inline fmt::text_style fwStyle = fg( fmt::color::floral_white );

constexpr inline fmt::text_style orStyle = fg( fmt::color::dark_orange );

constexpr inline fmt::text_style grStyle = fg( fmt::color::green_yellow );
constexpr inline fmt::text_style yeStyle = fg( fmt::color::yellow );
constexpr inline fmt::text_style liStyle = fg( fmt::color::lime );
constexpr inline fmt::text_style bvStyle = fg( fmt::color::blue_violet );

//! wow
//@ano
//#asdf
//$omg
//%nopo
//^crra
//&io
//* asdf
//(asd
//)
//?
// todo

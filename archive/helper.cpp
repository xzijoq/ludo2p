#include "helper.h"

#include <fmt/color.h>

#include <cstdio>
#include <string>
#include <system_error>

using std::cout;
using std::endl;
using std::error_code;
bool once = false;

void DisplayBits( u64 num, int sp, bool val )
{
    cout << "\n";
    for ( auto i = 63; i >= 0; i-- )
    {
        if ( ( num & (u64)1 << i ) )
        {
            if ( val ) { cout << "(" << ( num & (u64)1 << i ) << ")"; }
            else{cout<<1;}
        }
        else {  cout << 0; }
        if ( ( i ) % sp == 0 ) { cout << " "; }
        if ( ( i ) % 4 == 0 && sp == 8 ) { cout << " "; }
    }
    cout << "\n";
}

string checkec( error_code ec, string file, string func, int line, string msg )
{
    //@Took 2 hours to figureout !!!
    if ( (int)msg[msg.size() - 1] == 13 ) { msg.resize( msg.size() - 1 ); }

    string errr = std::to_string( ec.value() ) + " : " + ec.message();
    string out;
    if ( ec.value() != 0 )
    {
        out = fmt::format(
            "\nError   :{:^52} \nFunction:{:^52} \nOn Line :{:^52} \nIn File "
            ":{:^52} ",
            errr, func, line, file );
        //  p_err(out);
        fmt::print( eStyle, "{}", out );

        cout << endl;
        return out;
    }
    else
    {
        if ( msg != "" )
        {
            out = fmt::format( "\nCode -> {:<} || Msg -> {:<} || Line: -> {:<}",
                               errr, msg, line );
            fmt::print( okStyle, "{}", out );
            cout << endl;
        }
        else { out = ""; }
    }
    return out;
}
string checkec( string file, string func, int line, string msg )
{
    string out = "\n";

    //@Took 2 hours to figureout !!!
    if ( (int)msg[msg.size() - 1] == 13 ) { msg.resize( msg.size() - 1 ); }
    if ( msg != "" ) { out += fmt::format( "Msg -> {:<}  || ", msg ); }
    out += fmt::format( "Check: Line :{:<} || Func:{:<} || File :{:<}", line,
                        func, file );

    if ( msg != "" ) { fmt::print( grStyle, "{}", out ); }
    else { fmt::print( okStyle, "{}", out ); }

    cout << endl;

    return out;
}
string checkec( bool wh, string file, string func, int line, string msg )
{
    if ( wh == true ) { return ""; }
    string out = "\n";

    //@Took 2 hours to figureout !!!
    if ( (int)msg[msg.size() - 1] == 13 ) { msg.resize( msg.size() - 1 ); }
    if ( msg != "" ) { out += fmt::format( "Failed -> {:<}  || ", msg ); }
    out += fmt::format( "Check: Line :{:<} || Func:{:<} || File :{:<}", line,
                        func, file );

    fmt::print( eStyle, "{}", out );

    cout << endl;

    return out;
}

string showSock( asio::ip::tcp::socket& sock )
{
    string out;
    if ( sock.is_open() )
    {
        out = fmt::format( "LocalEp: {} <=> RmoteEp: {}", sock.local_endpoint(),
                           sock.remote_endpoint() );
    }
    else { out = "SOcket It not open"; }

    return out;
}

fmt::text_style eStyle =
    ( fg( fmt::color::navy ) ) | ( fmt::emphasis::bold ) |
    ( bg( fmt::color::blanched_almond ) | ( fmt::emphasis::underline ) );

fmt::text_style wStyle =
    ( fg( fmt::color::yellow ) ) | ( fmt::emphasis::bold ) |
    ( bg( fmt::color::black ) | ( fmt::emphasis::underline ) );
fmt::text_style okStyle = fg( fmt::color::steel_blue ) | fmt::emphasis::bold;

fmt::text_style fwStyle = fg( fmt::color::floral_white );

fmt::text_style orStyle = fg( fmt::color::dark_orange );

fmt::text_style grStyle = fg( fmt::color::green_yellow );
fmt::text_style yeStyle = fg( fmt::color::yellow );
fmt::text_style liStyle = fg( fmt::color::lime );
fmt::text_style bvStyle = fg( fmt::color::blue_violet );

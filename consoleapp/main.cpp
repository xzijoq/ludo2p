#include <fmt/color.h>
#include <math.h>

#include <ostream>
#include <streambuf>
#include <utility>

#include "Game.h"
#include "core.h"
#include "game2p.h"
#include "gamestate.h"
#include "global.h"
#include "helper.h"
#include "math.h"
#include "piece.h"
#include "square.h"
#include "visualtest.h"
using fmt::print;
using Global::GetEce;
using std::cout;
using std::endl;
void DebugSTest();
#ifdef NDEBUG
    #undef NDEBUG
#endif

void pm( bool fuck )
{
    if ( fuck ) { print( "\nFuck me" ); }
}

int main()
{
    cout << "\nMAIN STARTS HERE" << endl;
    //Game2p<> game;
    //game.InitGame();
    //print( "\ngs: {}", game.mGState.DebugString() );
    //Piece& p00 = game.Ece[GetEce( 0, 0 )];
    //Piece& p10 = game.Ece[GetEce( 1, 0 )];
    //gMove( p00, 0, game.Ece, game.Sq, game.mGState );
    //gMove( p10, 12, game.Ece, game.Sq, game.mGState );
    //    gMove( p10, 1, game.Ece, game.Sq, game.mGState );
    //print( "\np00: {}", p00.DebugString() );
    //print( "\np10: {}", p10.DebugString() );
    //gMove( p00, 1, game.Ece, game.Sq, game.mGState );
    //gMove( p10, 1, game.Ece, game.Sq, game.mGState );
    //print( "\np00: {}", p00.DebugString() );
    //print( "\np10: {}", p10.DebugString() );
    // Piece& p00 = game.Ece[GetEce( 1, 0 )];
    //// gMove( p00, 1, game.Ece, game.Sq, game.mGState );
    // MoveRaw( p00, 12, game.Sq );
    // print( "\np00: {}", p00.DebugString() );
    // gMove( p00, 3, game.Ece, game.Sq, game.mGState );
    // print( "\np00: {}", p00.DebugString() );
    //  Piece& p00 = game.Ece[GetEce( 0, 0 )];
    //  Piece& p01 = game.Ece[GetEce( 0, 1 )];
    //  Piece& p02 = game.Ece[GetEce( 0, 2 )];
    //  Piece& p10 = game.Ece[GetEce( 1, 2 )];
    //  gMove( p00, 3, game.Ece, game.Sq, game.mGState );
    //  gMove( p01, 3, game.Ece, game.Sq, game.mGState );
    //  gMove( p02, 3, game.Ece, game.Sq, game.mGState );
    //
    //  gMove( p10, 13 + 2, game.Ece, game.Sq, game.mGState );
    //
    //  print( "\np00: {}", p00.DebugString() );
    //  print( "\np00: {}", p01.DebugString() );
    //  print( "\np00: {}", p00.DebugString() );
    //  print( "\nsq5: {}", game.Sq[5].DebugString() );
    //
    //  print( "\np01: {}", p10.DebugString() );
    //  cout << endl;
    //  gMove( p10, 1, game.Ece, game.Sq, game.mGState );
    //  print( "\np00: {}", p00.DebugString() );
    //  print( "\np00: {}", p01.DebugString() );
    //  print( "\np00: {}", p02.DebugString() );
    //  print( "\np01: {}", p10.DebugString() );
    //
    //     print( "\nsq5: {}", game.Sq[5].DebugString() );

    cout << endl << "MAIN ENDS HERE" << endl;
}

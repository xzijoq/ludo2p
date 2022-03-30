#pragma once
#include <fmt/core.h>

#include <array>
#include <vector>

#include "core.h"
#include "gamestate.h"
#include "global.h"
#include "RegularMaps.h"
#include "piece.h"
#include "square.h"
#include <iostream>

using namespace Global;

using std::cout;
using std::endl;

// $SPECIFIC TO THIS GAME
static constexpr u64 MaxPlayers2p = 2;
// static constexpr u64 MaxEce2p     = 24;  // can be calculated

//%in game state
static constexpr u64 OuterSqCnt2p = DistancePlayer * MaxPlayers2p;
static constexpr u64 InnerSqCnt2p = GetInnerSquareCount( MaxPlayers2p );

//%gamestate.getWin/Home?Count etc
static constexpr u64 WinSquare2p  = GetWinSquare( OuterSqCnt2p, InnerSqCnt2p );
static constexpr u64 HomeSquare2p = GetHomeSquare( OuterSqCnt2p, InnerSqCnt2p );
static constexpr u64 SquaresCount2p =
    GetSquareCount( OuterSqCnt2p, InnerSqCnt2p );

//^ can be calulated for regular games
//%Stored in respective piece

//%Stored in respective piece
static constexpr std::array<u64, MaxPlayers2p> EntrySq2p =
    initEntrySq<MaxPlayers2p>();

// static constexpr std::array<u64, 4> SwitchSqt=initSwitch<4>();
//%Stored in respective piece
static constexpr std::array<u64, MaxPlayers2p> SwitchSq2p =
    initSwitchSquare<MaxPlayers2p>();

// static constexpr std::array<u64, 4> SplS=initSpecialSafeSquare<4>();
//%stored in respective squares via safe square
static constexpr std::array<u64, MaxPlayers2p> SplSafe2p =
    initSpecialSafeSquare<MaxPlayers2p>();


//%stored in respective squares

static constexpr std::array<u64, GetSafeSquareCount<MaxPlayers2p>()>
    SafeSquare = initSafeSquares<MaxPlayers2p>();

    

class Game2p
{
   public:
    GameState            mGState;

    Piece  Ece[MaxPlayers2p*MAX_PAWNS];
    Square Sq[SquaresCount2p];
    inline void   InitGame( u64 numPlr = 2, u64 numAwn = 6);
    consteval void fuck();
};


using enum b_SquareFlags;

static constexpr u64 active = 1;
[[maybe_unused]] static constexpr u64 in_active = 0;



 inline void Game2p::InitGame( u64 numPlr, u64 numAwn )
{
   // check_f( numPlr * numAwn == (u64)EceSz );
    mGState.InitGameState( MaxPlayers2p, numPlr, numAwn, OuterSqCnt2p,
                           InnerSqCnt2p );
 
    //$todo initialize flags
    for ( u64 pl = 0; pl < (int)MaxPlayers2p; pl++ )
    {
        mGState.setPlrState( pl, active );

        for ( u64 awn = 0; awn < numAwn; awn++ )
        {
            u64 ThisEce = Global::GetEce( pl, awn );
            Ece[ThisEce].InitPiece( ThisEce, HomeSquare2p, EntrySq2p[pl],
                                    SwitchSq2p[pl] );
            Sq[HomeSquare2p].putEce( ThisEce );
        }
    }
    for ( u64 sq : SafeSquare ) { Sq[sq].setFlag( b_sq_safe, true ); }
    // for ( auto i : Ece ) { print( "\n: {}", i.DebugString() ); }
}

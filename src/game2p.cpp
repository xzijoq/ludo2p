#include "game2p.h"

#include <type_traits>

#include "core.h"
#include "gamestate.h"
#include "global.h"
#include "helper.h"
#include "square.h"
/*
using enum b_SquareFlags;

static constexpr u64 active = 1;
[[maybe_unused]] static constexpr u64 in_active = 0;


template <int sz>
void Game2p<sz>::InitGame( u64 numPlr, u64 numAwn )
{
   // check_f( numPlr * numAwn == (u64)EceSz );
    mGState.InitGameState( MaxPlayers2p, numPlr, numAwn, OuterSqCnt2p,
                           InnerSqCnt2p );
    CURRENT_PLAYERS = MaxPlayers2p;
    CURRENT_AWNS    = numAwn;
    CURRENT_SQUARES = SquaresCount2p;
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



*/
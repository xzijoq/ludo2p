#pragma once
#include <array>
#include <vector>

#include "core.h"
#include "gamestate.h"
#include "global.h"
#include "piece.h"
#include "square.h"

using namespace Global;

static constexpr u64 DistancePlayer   = 13;
static constexpr u64 InnerSquareCount = 5;

template <int sz>
static consteval std::array<u64, sz> initEntrySq()
{
    std::array<u64, sz> result{};
    for ( u64 i = 0; i < sz; ++i )
    {
        result[i] = ( ( i * DistancePlayer ) + 2 ) % ( DistancePlayer * sz );
    }
    return result;
};

template <int sz>
static consteval std::array<u64, sz> initSwitchSquare()
{
    std::array<u64, sz> result{};
    for ( u64 i = 0; i < sz; ++i )
    {
        result[i] = ( i * DistancePlayer );  //%(DistancePlayer*sz);
    }
    return result;
};

template <int sz>
static consteval std::array<u64, sz> initSpecialSafeSquare()
{
    std::array<u64, sz> result{};
    for ( u64 i = 0; i < sz; ++i )
    {
        result[i] = ( ( i * DistancePlayer ) + 10 );  //%(DistancePlayer*sz);
    }
    return result;
};



// $SPECIFIC TO THIS GAME
static constexpr u64 MaxPlayers2p = 2;
// static constexpr u64 MaxEce2p     = 24;  // can be calculated

//%in game state
static constexpr u64 OuterSqCnt2p = DistancePlayer * MaxPlayers2p;
static constexpr u64 InnerSqCnt2p = InnerSquareCount;

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

//% expensively calculable via iterating over squares
//( feed it in game state if queried)
static constexpr u64 SafeSqCnt2p = 2  //* WinSquare and HomeSquare
                                   + EntrySq2p.size() + SplSafe2p.size() +
                                   InnerSqCnt2p + 1;

/*
template<int sz>
consteval std::array<u64, sz> initSafeSquare1()
{
    //EntrySq2p1[2];
    //SwitchSqt[0];
    //SplS[1];
    std::array<u64, SafeSqCnt2p> SfSq{};
    SfSq[0]    = WinSquare2p;
    SfSq[1]    = HomeSquare2p;
    u64 nindex = 2;

    for ( auto i : EntrySq2p )
    {
        SfSq[nindex] = i;
        nindex++;
    }

    nindex = 2 + EntrySq2p.size();

    for ( auto i : SplSafe2p )
    {
        SfSq[nindex] = i;
        nindex++;
    }
    nindex = 2 + EntrySq2p.size() + SplSafe2p.size();
    for ( auto i = OuterSqCnt2p; i <= OuterSqCnt2p + InnerSqCnt2p; i++ )
    {
        SfSq[nindex] = i;
        nindex++;
    }

    return SfSq;
}*/

template <int sz>
consteval std::array<u64, sz> initSafeSquare()
{
    // EntrySq2p1[2];
    // SwitchSqt[0];
    // SplS[1];
    std::array<u64, SafeSqCnt2p> SfSq{};
    SfSq[0]    = WinSquare2p;
    SfSq[1]    = HomeSquare2p;
    u64 nindex = 2;

    for ( auto i : EntrySq2p )
    {
        SfSq[nindex] = i;
        nindex++;
    }

    nindex = 2 + EntrySq2p.size();

    for ( auto i : SplSafe2p )
    {
        SfSq[nindex] = i;
        nindex++;
    }
    nindex = 2 + EntrySq2p.size() + SplSafe2p.size();
    for ( auto i = OuterSqCnt2p; i <= OuterSqCnt2p + InnerSqCnt2p; i++ )
    {
        SfSq[nindex] = i;
        nindex++;
    }

    return SfSq;
}

//%stored in respective squares
static constexpr std::array<u64, SafeSqCnt2p> SafeSquare = initSafeSquare<SafeSqCnt2p>();

template <int EceCount = 8>
class Game2p
{
   public:
    GameState            mGState;
    static constexpr int lol1 = 2;
    int EceSz=EceCount;
    //std::array<Piece, EceCount> Ece;
    // std::array<Square, SquaresCount2p> Sq;
    Piece Ece[EceCount];
    Square Sq[SquaresCount2p];
    void   InitGame( u64 numPlr = 2, u64 numAwn = 4 );
};

static constexpr std::array<u64, SafeSqCnt2p>  // hello
    SafeSquare1{
        HomeSquare2p,
        WinSquare2p,
        EntrySq2p[0],
        EntrySq2p[1],  // ob
        7,
        17,  // special
        20,
        21,
        22,
        23,  // how  to fill calculated
        24,
        25  // all the inner swuares;
    };
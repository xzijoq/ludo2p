#pragma once
#include <array>

#include "u64def.h"

static constexpr u64 DistancePlayer   = 13;
static constexpr u64 InnerSquareCount = 5;

consteval u64 GetOuterSquareCount( u64 sz ) { return DistancePlayer * sz; }
consteval u64 GetInnerSquareCount( [[maybe_unused]] u64 sz )
{
    return InnerSquareCount;
}
inline constexpr u64 GetWinSquare( u64 otrSqCnt, u64 inrSqCnt )
{
    return otrSqCnt + inrSqCnt;
}
inline constexpr u64 GetHomeSquare( u64 otrSqCnt, u64 inrSqCnt )
{
    return GetWinSquare( otrSqCnt, inrSqCnt ) + 1;
}
inline constexpr u64 GetSquareCount( u64 otrSqCnt, u64 inrSqCnt )
{
    return GetHomeSquare( otrSqCnt, inrSqCnt ) + 1;
}

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

template <int sz>
consteval u64 GetSafeSquareCount()
{
    std::array<u64, sz> EntrySq = initEntrySq<sz>();
    std::array<u64, sz> SplSafe = initSpecialSafeSquare<sz>();

    u64 inrSqCount = GetInnerSquareCount( sz );

    u64 SafeSqCnt = EntrySq.size() + SplSafe.size() + inrSqCount +
                    2;  //* WinSquare and HomeSquare
    return SafeSqCnt;
}

template <int sz>
consteval std::array<u64, GetSafeSquareCount<sz>()> initSafeSquares()
{
    std::array<u64, sz> EntrySq = initEntrySq<sz>();
    std::array<u64, sz> SplSafe = initSpecialSafeSquare<sz>();

    u64 otrSqCount = GetOuterSquareCount( sz );
    u64 inrSqCount = GetInnerSquareCount( sz );

    std::array<u64, GetSafeSquareCount<sz>()> SfSq{};
    // SfSq[0] = GetWinSquare( otrSqCount, inrSqCount );

    u64 nindex = 0;
    for ( auto i : EntrySq )
    {
        SfSq[nindex] = i;
        nindex++;
    }
    nindex = 0 + EntrySq.size();

    for ( auto i : SplSafe )
    {
        SfSq[nindex] = i;
        nindex++;
    }
    nindex = 0 + EntrySq.size() + SplSafe.size();
    for ( auto i = otrSqCount; i < otrSqCount + inrSqCount; i++ )
    {
        SfSq[nindex] = i;
        nindex++;
    }
    SfSq[nindex]     = GetWinSquare( otrSqCount, inrSqCount );
    SfSq[nindex + 1] = GetHomeSquare( otrSqCount, inrSqCount );
    return SfSq;
}

/*
static constexpr u64 SafeSqCnt2p = 2  // WinSquare and HomeSquare
                                   + EntrySq2p.size() + SplSafe2p.size() +
                                   InnerSqCnt2p + 1;

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
*/
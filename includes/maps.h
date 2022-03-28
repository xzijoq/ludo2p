#include <array>
#include <vector>

#include "global.h"
#include "helper.h"

static constexpr u64 MaxPlayers2p = 2;
static constexpr u64 MaxEce2p     = 24;  // can be calculated

static constexpr u64 OuterSqCnt2p = 20;
static constexpr u64 InnerSqCnt2p  = 5;

static constexpr u64 WinSquare2p  = OuterSqCnt2p + InnerSqCnt2p + 1;
static constexpr u64 HomeSquare2p = WinSquare2p + 1;

static constexpr u64 SquaresCount2p = HomeSquare2p + 1;


static constexpr std::array<u64, MaxPlayers2p> EntrySq2p{ 3, 13 };

static constexpr std::array<u64, MaxPlayers2p> SwitchSq2p{ 0, 10 };


static constexpr std::array<u64, MaxPlayers2p> SplSafe2p{ 7, 17 };



static constexpr u64 SafeSqCnt2p =
    2 + EntrySq2p.size() + SplSafe2p.size() + InnerSqCnt2p + 1;




consteval std::array<u64, SafeSqCnt2p> initSafeSquare()
{
    std::array<u64, SafeSqCnt2p> SfSq{};
    SfSq[0]    = HomeSquare2p;
    SfSq[1]    = WinSquare2p;
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

static constexpr std::array<u64, 12> SafeSquare = initSafeSquare();

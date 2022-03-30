#include <array>

#include "u64def.h"

using std::array;
namespace TestRegularMap
{

//^2Player START================

static constexpr u64 t_MaxPlayers2p = 2;

static constexpr u64 t_OuterSqCnt2p = 26;
static constexpr u64 t_InnerSqCnt2p = 5;

static constexpr u64 t_WinSquare2p    = 31;
static constexpr u64 t_HomeSquare2p   = 32;
static constexpr u64 t_SquaresCount2p = 33;

inline constexpr array<u64, 2> t_EntrySq2p{ 2, 15 };

static constexpr std::array<u64, 2> t_SwitchSq2p{ 0, 13 };

static constexpr std::array<u64, 2> t_SplSafe2p{ 10, 23 };

static constexpr std::array<u64, 11> t_SafeSquare2p{
    2,  15,              //* entry
    10, 23,              //* spl
    26, 27, 28, 29, 30,  //* innter
    31,                  //* win
    32                   //* home
};
//^2Player END==================

//^3Player START=============
inline constexpr array<u64, 3> t_3pEntrySq{ 2, 15, 28 };

//^4Player
inline constexpr array<u64, 4> t_4pEntrySq{ 2, 15, 28, 41 };

}  // namespace TestRegularMap
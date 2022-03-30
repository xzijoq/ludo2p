//! Intentionally in comle
//$Intentioanlly Postponed
#include <gtest/gtest.h>

#include "RegularMaps.h"
#include "TestRegularMap.h"
#include "helper.h"
using namespace TestRegularMap;

//^Very important test
TEST( RegularMapstest, map2p )
{
    auto constexpr en2 = initEntrySq<2>();
    static_assert( en2 == t_EntrySq2p, "wtf" );

    auto constexpr oteSqCnt2 = t_OuterSqCnt2p;
    static_assert( oteSqCnt2 == GetOuterSquareCount( 2 ), "wtf" );

    auto constexpr inrSqCnt2 = t_InnerSqCnt2p;
    static_assert( t_InnerSqCnt2p == GetInnerSquareCount( 2 ), "wtf" );

    static_assert( t_WinSquare2p == GetWinSquare( oteSqCnt2, inrSqCnt2 ),
                   "wtf" );

    static_assert( t_HomeSquare2p == GetHomeSquare( oteSqCnt2, inrSqCnt2 ),
                   "wtf" );

    static_assert( t_SquaresCount2p == GetSquareCount( oteSqCnt2, inrSqCnt2 ),
                   "wtf" );

    //% Arrays
    static_assert( t_EntrySq2p == initEntrySq<2>() );

    static_assert( t_SwitchSq2p == initSwitchSquare<2>() );

    static_assert( t_SplSafe2p == initSpecialSafeSquare<2>() );
    static_assert( t_SafeSquare2p == initSafeSquares<2>() );
}
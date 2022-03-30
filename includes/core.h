#pragma once
#include <cassert>

#include "helper.h"
#include "u64def.h"
using fmt::format;
// Todo make them defines or somethig remove error checking to allow true
// inlining %and complile time computation? witch static assert may be
//! if bits in '<<' opertor are not u64 anything aboove 31 will be set to 1
[[__nodiscard__("ERROR: Set 1 Bit DOESNOT modify argumet")]]
inline constexpr u64 SetBit( u64 numVal, u64 bit )
{
    u64 num=numVal;
    check_fp( ( bit >= 0 && bit < 64 ), format( "bit: {} ", bit ) );
    num |= (u64)1 << bit;
    return num;
}

[[__nodiscard__("ERROR: UnSet 1 Bits DOESNOT modify argumet")]]
inline constexpr u64 UnSetBit( u64 numVal, u64 bit )
{
    u64 num=numVal;
    check_fp( ( bit >= 0 && bit < 64 ), format( "bit: {} ", bit ) );
    //%set it to 1 then negate it = ~(SetBit)
    num &= ~( (u64)1 << bit );
    return num;
}

inline constexpr u64 GetBit( u64 num, u64 bit )
{  //$may not be trivial to inline

    check_fp( ( bit >= 0 && bit < 64 ), format( "bit: {} ", bit ) );
    return ( ( num >> bit ) & (u64)1 );
}



[[__nodiscard__("ERROR: SetBits DOESNOT modify argumet")]]
inline constexpr u64 SetBits( u64 numVal, u64 bits, u64 posi, u64 count )
{
    //%pow(2,n) is ( (u64)1 << count )
    u64 num=numVal;

    check_fp( ( count > 0 && count < 64 && posi >= 0 && posi < 64 ),
              format( "count: {} Posi: {}", count, posi ) );

    check_fp( ( posi + count <= 64 ),
              format( "count: {} Posi: {}", count, posi ) );

    check_fp( ( bits <= ( ( (u64)1 << count ) - 1 ) ),
              format( "bits: {} count {}", bits, count ) );
    //%clear those bits to zero and set new
    num &= ~( ( ( (u64)1 << count ) - 1 ) << posi );
    num |= (u64)bits << posi;
    return num;
}

inline constexpr u64 GetBits( u64 num, u64 posi, u64 count )
{
    check_fp( count > 0 && count < 64 && posi >= 0 && posi < 64,
              format( "count: {} Posi: {}", count, posi ) );

    check_fp( ( posi + count <= 64 ),
              format( "count: {} Posi: {}", count, posi ) );
    //% shift and clear else the rest bits, will go 1 all ovver 32
    return ( num >> (u64)posi ) & ( ( (u64)1 << count ) - 1 );
}

//OLD

/*

inline constexpr void SetBits1( u64& num, u64 bits, u64 posi, u64 count )
{
    //%pow(2,n) is ( (u64)1 << count )

    check_fp( ( count > 0 && count < 64 && posi >= 0 && posi < 64 ),
              format( "count: {} Posi: {}", count, posi ) );

    check_fp( ( posi + count <= 64 ),
              format( "count: {} Posi: {}", count, posi ) );

    check_fp( ( bits <= ( ( (u64)1 << count ) - 1 ) ),
              format( "bits: {} count {}", bits, count ) );
    //%clear those bits to zero and set new
    num &= ~( ( ( (u64)1 << count ) - 1 ) << posi );
    num |= (u64)bits << posi;
}*/
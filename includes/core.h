#pragma once


#include "global.h"
#include "helper.h"

//$ To do make them defines or somethig 
//$ remove error checking to allow true inlining

void SetBit( u64& num, int bit );
void UnSetBit( u64& num, int bit );
u64 GetBit(u64 num, int bit);

void SetBits( u64& num, u64 bits, int posi, int count );
u64 GetBits( u64 num, int posi, int count );

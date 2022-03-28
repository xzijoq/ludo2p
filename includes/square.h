#pragma once
#include "global.h"
#include <string>
using namespace Global;

enum struct b_SquareFlags:u64
{
    b_sq_valid,
    b_sq_safe,
    b_sq_empty,
    b_sq_start,
    b_sq_end,
    zSqSz
};
//0-48 ece 
class Square{
    public:
    u64 mSquare=0;

    void putEce(u64 ece);
    void popEce(u64 ece);
    
    u64 hasEce(u64 ece);
    u64 hasPlr(u64 plr)const;

    void setFlag(b_SquareFlags flg,bool what);

    u64 getFlag(b_SquareFlags flg) const;

    void CheckSquare();
    std::string DebugString ()const;




};

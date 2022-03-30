#pragma once
#include "square.h"
#include "u64def.h"
enum b_GMoveFlags
{
    nope,
    zfg_size
};

struct GraphicsMove
{
    u64 mGMoveData;
    //* Semantic problem, square is a holder of all piece
    Square mGMoveCaptured;

    void setMEce( u64 ece );
    u64  getMEce() const;

    void setFrom( u64 sq );
    u64  getFrom() const;

    void setTo( u64 sq );
    u64  getTo() const;

    void setRoll( u64 ece );
    u64  getRoll() const;
};
/*
enum struct b_GMoveDataLayout : u64
{
    bd_ece,
    bd_frm_sq,
    bd_to_sq,
    bd_roll,
    zdly_size

};
*/
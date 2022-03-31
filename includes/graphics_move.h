#pragma once

#include "u64def.h"
enum struct b_GMove : u64
{
    b_mece,
    b_frm_sq,
    b_to_sq,
    b_roll,
    zb_gmv_size

};

enum b_GMoveFlags
{
    nope,
    zb_gmv_fg_size
};

struct GraphicsMove
{
    u64 mGMove;


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
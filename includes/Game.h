#pragma once
#include "gamestate.h"
#include "global.h"
#include "helper.h"
#include "piece.h"
#include "square.h"

using enum b_SquareFlags;
using enum b_PieceFlags;

//*Most called functions (by Ai mainly) Must be optimised
inline void MoveRaw( Piece eceVal, u64 to, Piece piece[], Square sq[] )
{
    Piece& ece = piece[eceVal.getEce()];
    u64    frm = ece.getSq();  // inline when optimize

    ece.setSq( to );
    sq[frm].popEce( ece.getEce() );
    sq[to].putEce( ece.getEce() );
}

//^ MAX DIE ROLL IS 13*(mapsize-1) DISTANCE
inline void GameMove( Piece eceVal, u64 count, Piece piece[], Square sq[],
                      GameState gs )
{
    Piece& ece = piece[eceVal.getEce()];
    check_fp( count < 13, "Roll: " << count << " MAX DIE ROLL IS 13" );
    u64 frmSq   = ece.getSq();
    u64 toSqRaw = frmSq + count;
    u64 toSq    = toSqRaw % gs.getOtrSqCnt();

    if ( false ) {}
    //%StartMove
    else if ( frmSq == gs.getHomeSq() )
    {
        if ( count == 6 ) { toSq = ece.getEntrySq(); }
        else
        {
            toSq = frmSq;
            check_d( "\nInvaldStartMove" );
        }
        // toSq = ( ece.getEntrySq() + count ) % gs.getOtrSqCnt();
    }
    //%Switch into inner square
    //^following sets the max die roll to 13 in 2p games 13*(n-1)
    else if ( ( frmSq < ece.getSwitchSq() and toSq > ece.getSwitchSq() ) )
    {
        check_d( "\nInnter" );

        toSq = ( toSq - ece.getSwitchSq() ) + ( gs.getOtrSqCnt() - 1 );
        check_fp( toSq <= gs.getWinSq(), " toSq: " << toSqRaw );
    }
    else if ( ( toSqRaw > gs.getOtrSqCnt() and ece.getSwitchSq() == 0 ) )
    {
        check_d( "\nInnter PLAYER 0" );
        check_fp( toSqRaw <= gs.getWinSq(), " toSqRaw: " << toSqRaw );
        toSq = toSqRaw;
    }
    //%End Swithc into inner square
    //%Target sq not empty nor safe
    else if ( /*not sq[toSq].getFlag( b_sq_empty) and*/ not sq[toSq].getFlag(
        b_sq_safe ) )
    {
        check_d( "\nUnSafe" );
        for ( u64 this_plr = 0; this_plr < gs.getMaxPlrCnt(); this_plr++ )
        {  // todo write code for team
            //%Capture
            if ( sq[toSq].hasPlr( this_plr ) and this_plr != ece.getPlr() )
            {
                check_d( "\nCapture" );
                for ( u64 this_awn = 0; this_awn < gs.getCrntAwnCnt();
                      this_awn++ )
                {
                    check_d( "\nWHo:" << this_plr << " " << this_awn );
                    u64 this_ece = Global::GetEce( this_plr, this_awn );
                    u64 Capture  = sq[toSq].hasEce( this_ece );
                    if ( Capture )
                    {
                        check_d( "\nCapture This:" << this_plr << " "
                                                   << this_awn << " "
                                                   << this_ece );
                        //%Send Em home
                        MoveRaw( piece[this_ece], gs.getHomeSq(), piece,sq );
                    }
                    // todo push to move array
                }
            }
        }
    }
    //%Move from innter square
    else if ( frmSq >= gs.getOtrSqCnt() )
    {
        check_fp( toSqRaw <= gs.getWinSq(), " toSqRaw: " << toSqRaw );
        toSq = toSqRaw;
    }
    // todo push to move array

    MoveRaw( ece, toSq,piece, sq );

    // u64 toSq=
}
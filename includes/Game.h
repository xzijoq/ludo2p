#pragma once
#include "gamestate.h"
#include "global.h"
#include "graphics_move.h"
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

    //%untested yet
    bool         isCapture = false;
    GraphicsMove gMv;
    gMv.setMEce( ece.getEce() );
    gMv.setFrom( frmSq );
    gMv.setRoll( count );
    //*Before Capture
    Square toSqBC;
    //%untested yet---END

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
    else if ( ( frmSq <= ece.getSwitchSq() and toSq > ece.getSwitchSq() ) )
    {
        // check_d( "\nInnter" );

        toSq = ( toSq - ece.getSwitchSq() ) + ( gs.getOtrSqCnt() - 1 );
        check_fp( toSq <= gs.getWinSq(), " toSq: " << toSqRaw );
    }
    //(for player0 will work for regulat maps only)
    else if ( ( ( toSqRaw > gs.getOtrSqCnt() or frmSq == 0 ) and
                ece.getSwitchSq() == 0 ) )
    {
        //  check_d( "\nInnter PLAYER 0" );
        if ( frmSq == 0 ) { toSq = gs.getOtrSqCnt() - 1 + count; }
        else { toSq = ( toSq - ece.getSwitchSq() ) + ( gs.getOtrSqCnt() - 1 ); }
        check_fp( toSqRaw <= gs.getWinSq(), " toSqRaw: " << toSqRaw );
    }
    //%End Swithc into inner square

    //%Target sq not empty nor safe
    else if ( /*not sq[toSq].getFlag( b_sq_empty) and*/ not sq[toSq].getFlag(
        b_sq_safe ) )
    {
        isCapture = true;
        toSqBC    = sq[toSq];

        // check_d( "\nUnSafe" );
        for ( u64 this_plr = 0; this_plr < gs.getMaxPlrCnt(); this_plr++ )
        {  // todo write code for team
            //%Capture

            if ( sq[toSq].hasPlr( this_plr ) and this_plr != ece.getPlr() )
            {
                // check_d( "\nCapture" );
                for ( u64 this_awn = 0; this_awn < gs.getCrntAwnCnt();
                      this_awn++ )
                {
                    // check_d( "\nWHo:" << this_plr << " " << this_awn );
                    u64 this_ece = Global::GetEce( this_plr, this_awn );
                    //%if not on same team
                    if ( ece.getTeam() != piece[this_ece].getTeam() )
                    {
                        u64 Capture = sq[toSq].hasEce( this_ece );
                        if ( Capture )
                        {
                            // check_d( "\nCapture This:" << this_plr << " "
                            //                            << this_awn << " "
                            //                            << this_ece );
                            //%Send Em home
                            //$call to raw move
                            MoveRaw( piece[this_ece], gs.getHomeSq(), piece,
                                     sq );
                        }
                    }
                    // todo push to move array
                }
            }
        }
    }
    //%Move from innter square only works cur they are all safe once
    else if ( frmSq >= gs.getOtrSqCnt() )
    {
        check_fp( toSqRaw <= gs.getWinSq(), " toSqRaw: " << toSqRaw );
        toSq = toSqRaw;
    }
    // todo push to move array

    if ( not isCapture ) { toSqBC = sq[toSq]; }

    gMv.setTo( toSq );
    //$call to raw move
    MoveRaw( ece, toSq, piece, sq );
    //* Async_Graphics_Move(gMv,toSqBc)
    //* or  maybe set a last move varaible and notify ppl
    // u64 toSq=
}
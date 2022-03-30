
#include "gamestate.h"

#include <array>
#include <cassert>

#include "RegularMaps.h"
#include "core.h"
#include "global.h"
#include "helper.h"
using namespace Global;
//*ceil( (log2)(8) )
static constexpr u64 MaxPlayers_b = ceillog2( MAX_PLAYERS ) + 1;

//*ceil( (log2)(24) )
static constexpr u64 MaxPawns_b = ceillog2( MAX_PAWNS ) + 1;

enum struct b_GameStateLayout : u64
{
    b_max_plr_cnt,
    b_crnt_plr_cnt,
    b_crnt_awn_cnt,
    b_player_state,
    b_otr_sq_cnt,
    b_inr_sq_cnt,
    zly_size

};

enum struct b_GameStateFlags : u64
{
    wwo,
    zfg_sz

};
using enum b_GameStateLayout;
using enum b_GameStateFlags;

static constexpr std::array<u64, (u64)zly_size> b_SzOf  // %order matters
    {
        //% MUST MATCH b_PieceLayout Enum ABOVE
        MaxPlayers_b,  //*    b_max_plr_cnt
        MaxPlayers_b,  //*    b_crnt_plr_cnt
        MaxPawns_b,    //*   b_crnt_awn_cnt,
        MAX_PLAYERS,   //*  b_player_state,
        SQ_SZb + 1,    //*  b_otr_sq_state,
        SQ_SZb + 1     //*  b_inr_Sq_state,

    };

static consteval u64 b_frm( const b_GameStateLayout inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_SzOf[(u64)i]; }
    return result;
}

void GameState::setMaxPlrCnt( u64 cp )
{
    assert( cp <= MAX_PLAYERS );
    mGameState = SetBits( mGameState, cp, b_frm( b_max_plr_cnt ),
                          b_SzOf[(u64)b_max_plr_cnt] );
}
u64 GameState::getMaxPlrCnt() const
{
    auto result = GetBits( mGameState, b_frm( b_max_plr_cnt ),
                           b_SzOf[(u64)b_max_plr_cnt] );
    assert( result <= MAX_PLAYERS );
    return result;
}

void GameState::setCrntPlrCnt( u64 cp )
{
    assert( cp <= MAX_PLAYERS );
    mGameState = SetBits( mGameState, cp, b_frm( b_crnt_plr_cnt ),
                          b_SzOf[(u64)b_crnt_plr_cnt] );
}
u64 GameState::getCrntPlrCnt() const
{
    auto result = GetBits( mGameState, b_frm( b_crnt_plr_cnt ),
                           b_SzOf[(u64)b_crnt_plr_cnt] );
    assert( result <= MAX_PLAYERS );
    return result;
}
void GameState::setCrntAwnCnt( u64 awn )
{
    assert( awn <= MAX_PAWNS );
    mGameState = SetBits( mGameState, awn, b_frm( b_crnt_awn_cnt ),
                          b_SzOf[(u64)b_crnt_awn_cnt] );
}
u64 GameState::getCrntAwnCnt() const
{
    auto result = GetBits( mGameState, b_frm( b_crnt_awn_cnt ),
                           b_SzOf[(u64)b_crnt_awn_cnt] );
    assert( result <= MAX_PAWNS );
    return result;
}

void GameState::setPlrState( u64 plr, bool what )
{
    check_fp( plr < MAX_PLAYERS, " plr:" << plr );
    if ( what )
    {
        check_p( not getPlrState( plr ), "Player Was Already Active" );
        mGameState=SetBit( mGameState, b_frm( b_player_state ) + plr );
    }
    else
    {
        check_p( getPlrState( plr ), "Player Was Already InActive" );
        mGameState=UnSetBit( mGameState, b_frm( b_player_state ) + plr );
    }
}
u64 GameState::getPlrState( u64 plr ) const
{
    check_fp( plr < MAX_PLAYERS, " plr:" << plr );
    return GetBit( mGameState, b_frm( b_player_state ) + plr );
}

void GameState::setOtrSqCnt( u64 sqc )
{
    assert( sqc <= MAX_SQUARES );
    mGameState = SetBits( mGameState, sqc, b_frm( b_otr_sq_cnt ),
                          b_SzOf[(u64)b_otr_sq_cnt] );
}
u64 GameState::getOtrSqCnt() const
{
    auto result =
        GetBits( mGameState, b_frm( b_otr_sq_cnt ), b_SzOf[(u64)b_otr_sq_cnt] );
    assert( result <= MAX_SQUARES );
    return result;
}
void GameState::setInrSqCnt( u64 sqc )
{
    assert( sqc <= MAX_SQUARES );
    mGameState = SetBits( mGameState, sqc, b_frm( b_inr_sq_cnt ),
                          b_SzOf[(u64)b_inr_sq_cnt] );
}
u64 GameState::getInrSqCnt() const
{
    auto result =
        GetBits( mGameState, b_frm( b_inr_sq_cnt ), b_SzOf[(u64)b_inr_sq_cnt] );
    assert( result <= MAX_SQUARES );
    return result;
}

//^ Change if formula changes
u64 GameState::getWinSq() const
{
    u64 result = GetWinSquare( getOtrSqCnt(), getInrSqCnt() );
    check_fp( result <= MAX_SQUARES,
              " res:" << result << " max:" << MAX_SQUARES );
    return result;
}
u64 GameState::getHomeSq() const
{
    u64 result = GetHomeSquare( getOtrSqCnt(), getInrSqCnt() );
    check_fp( result <= MAX_SQUARES,
              " res:" << result << " max:" << MAX_SQUARES );
    return result;
}
u64 GameState::getSqCnt() const
{
    u64 result = GetSquareCount( getOtrSqCnt(), getInrSqCnt() );
    check_fp( result <= MAX_SQUARES,
              " res:" << result << " max:" << MAX_SQUARES );
    return result;
}
//^ Change if formula changes ---end

void GameState::InitGameState( u64 maxPlrCnt, u64 crntPlrCnt, u64 crntAwnCnt,
                               u64 otrSqCnt, u64 inrSqCnt )
{
    setMaxPlrCnt( maxPlrCnt );
    setCrntPlrCnt( crntPlrCnt );
    setCrntAwnCnt( crntAwnCnt );
    setOtrSqCnt( otrSqCnt );
    setInrSqCnt( inrSqCnt );
}

//& debug ahead

static u64 b_frm_copy( const b_GameStateLayout inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (int)inx; i++ ) { result += b_SzOf[(u64)i]; }
    return result;
}

std::string GameState::DebugString() const
{
    std::string res    = "";
    u64         dState = mGameState;
    u64         i      = 0;

    for ( auto k = 63; k >= 0; k-- )
    {
        i = (u64)k;
        if ( ( dState & (u64)1 << i ) ) { res += format( grStyle, "1" ); }
        else { res += format( grStyle, "0" ); }

        if ( b_frm_copy( b_max_plr_cnt ) == i )
        {
            res += fmt::format( fwStyle, " End" );
        }
        else if ( b_frm_copy( b_crnt_plr_cnt ) == i )
        {
            res += fmt::format( fwStyle, " MaxPlrCnt({}):", getMaxPlrCnt() );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }
        else if ( b_frm_copy( b_crnt_awn_cnt ) == i )
        {
            res += fmt::format( fwStyle, " CrntPlrCnt({}):", getCrntPlrCnt() );
            // res += fmt::format( fwStyle, " CrntAwnCnt({}):", getCrntAwnCnt()
            // );
        }
        else if ( b_frm_copy( b_player_state ) == i )
        {
            res += fmt::format( fwStyle, " CrntAwnCnt({}):", getCrntAwnCnt() );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }
        else if ( b_frm_copy( b_otr_sq_cnt ) == i )
        {
            res += fmt::format( fwStyle, " PlrState({}):", -1 );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }
        else if ( b_frm_copy( b_inr_sq_cnt ) == i )
        {
            res += fmt::format( fwStyle, " OtrSqCnt({}):", getOtrSqCnt() );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }

        else if ( b_frm_copy( zly_size ) == i )
        {
            res += fmt::format( fwStyle, " InrSqCnt({}):", getInrSqCnt() );
            // res += fmt::format( fwStyle, " noop{}):", -1 );
        }
    }
    res += fmt::format( " WinSq:{} HomeSq:{} SqCnt:{} ", getWinSq(),
                        getHomeSq(), getSqCnt() );

    return res;
}
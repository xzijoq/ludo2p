
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

using enum b_GameState;
using enum b_GameStateFlags;

static constexpr std::array<u64, (u64)zb_gamse_state_size>
    b_GsSz  // %order matters
    {
        //% MUST MATCH b_PieceLayout Enum ABOVE
        MaxPlayers_b,  //*  b_max_plr_cnt
        MaxPlayers_b,  //*  b_crnt_plr_cnt
        MaxPawns_b,    //*  b_crnt_awn_cnt,
        MAX_PLAYERS,   //*  b_player_state,
        TEAM_SZb + 1,  //*  b_crmt_team_cnt
        SQ_SZb + 1,    //*  b_otr_sq_state,
        SQ_SZb + 1     //*  b_inr_Sq_state,

    };

consteval u64 b_GsFrm( const b_GameState inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_GsSz[(u64)i]; }
    return result;
}
static consteval u64 b_GsFrm_nc( const b_GameState inx )
{
    u64 result = 0;
    for ( auto i = 0; i < (u64)inx; i++ ) { result += b_GsSz[(u64)i]; }
    return result;
}

void GameState::setMaxPlrCnt( u64 cp )
{
    assert( cp <= MAX_PLAYERS );
    mGameState = SetBits( mGameState, cp, b_GsFrm( b_max_plr_cnt ),
                          b_GsSz[(u64)b_max_plr_cnt] );
}
u64 GameState::getMaxPlrCnt() const
{
    auto result = GetBits( mGameState, b_GsFrm( b_max_plr_cnt ),
                           b_GsSz[(u64)b_max_plr_cnt] );
    assert( result <= MAX_PLAYERS );
    return result;
}

void GameState::setCrntPlrCnt( u64 cp )
{
    assert( cp <= MAX_PLAYERS );
    mGameState = SetBits( mGameState, cp, b_GsFrm( b_crnt_plr_cnt ),
                          b_GsSz[(u64)b_crnt_plr_cnt] );
}
u64 GameState::getCrntPlrCnt() const
{
    auto result = GetBits( mGameState, b_GsFrm( b_crnt_plr_cnt ),
                           b_GsSz[(u64)b_crnt_plr_cnt] );
    assert( result <= MAX_PLAYERS );
    return result;
}
void GameState::setCrntAwnCnt( u64 awn )
{
    assert( awn <= MAX_PAWNS );
    mGameState = SetBits( mGameState, awn, b_GsFrm( b_crnt_awn_cnt ),
                          b_GsSz[(u64)b_crnt_awn_cnt] );
}
u64 GameState::getCrntAwnCnt() const
{
    auto result = GetBits( mGameState, b_GsFrm( b_crnt_awn_cnt ),
                           b_GsSz[(u64)b_crnt_awn_cnt] );
    assert( result <= MAX_PAWNS );
    return result;
}

void GameState::setPlrState( u64 plr, bool what )
{
    check_fp( plr < MAX_PLAYERS, " plr:" << plr );
    if ( what )
    {
        check_p( not getPlrState( plr ), "Player Was Already Active" );
        mGameState = SetBit( mGameState, b_GsFrm( b_player_state ) + plr );
    }
    else
    {
        check_p( getPlrState( plr ), "Player Was Already InActive" );
        mGameState = UnSetBit( mGameState, b_GsFrm( b_player_state ) + plr );
    }
}
u64 GameState::getPlrState( u64 plr ) const
{
    check_fp( plr < MAX_PLAYERS, " plr:" << plr );
    return GetBit( mGameState, b_GsFrm( b_player_state ) + plr );
}

void GameState::setCrntTeamCnt( u64 TeamCount ){
       check_fp( TeamCount <= MAX_TEAMS ," TeamCount:" << TeamCount );
       mGameState = SetBits( mGameState, TeamCount, b_GsFrm( b_crnt_team_cnt ),
                          b_GsSz[(u64)b_crnt_team_cnt] );
}
u64  GameState::getCrntTeamCnt() const{

    return GetBits( mGameState, b_GsFrm( b_crnt_team_cnt ),
                          b_GsSz[(u64)b_crnt_team_cnt] );
}

void GameState::setOtrSqCnt( u64 sqc )
{
    assert( sqc <= MAX_SQUARES );
    mGameState = SetBits( mGameState, sqc, b_GsFrm( b_otr_sq_cnt ),
                          b_GsSz[(u64)b_otr_sq_cnt] );
}
u64 GameState::getOtrSqCnt() const
{
    auto result = GetBits( mGameState, b_GsFrm( b_otr_sq_cnt ),
                           b_GsSz[(u64)b_otr_sq_cnt] );
    assert( result <= MAX_SQUARES );
    return result;
}
void GameState::setInrSqCnt( u64 sqc )
{
    assert( sqc <= MAX_SQUARES );
    mGameState = SetBits( mGameState, sqc, b_GsFrm( b_inr_sq_cnt ),
                          b_GsSz[(u64)b_inr_sq_cnt] );
}
u64 GameState::getInrSqCnt() const
{
    auto result = GetBits( mGameState, b_GsFrm( b_inr_sq_cnt ),
                           b_GsSz[(u64)b_inr_sq_cnt] );
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

void GameState::setFlag( b_GameStateFlags flg, bool what )
{
    check_f( ( 63 - (u64)flg ) > b_GsFrm( b_GameState::zb_gamse_state_size ) );
    ( what ) ? mGameState = SetBit( mGameState, 63 - (u64)flg )
             : mGameState = UnSetBit( mGameState, 63 - (u64)flg );
}

u64 GameState::getFlag( b_GameStateFlags flg )
{
    return GetBit( mGameState, 63 - (u64)flg );
}

void GameState::InitGameState( u64 maxPlrCnt, u64 crntPlrCnt, u64 crntAwnCnt, u64 crntTeamCnt,
                               u64 otrSqCnt, u64 inrSqCnt )
{
    setMaxPlrCnt( maxPlrCnt );
    setCrntPlrCnt( crntPlrCnt );
    setCrntAwnCnt( crntAwnCnt );
    setCrntTeamCnt(crntTeamCnt);
    setOtrSqCnt( otrSqCnt );
    setInrSqCnt( inrSqCnt );
}

//& debug ahead

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

        if ( b_GsFrm_nc( b_max_plr_cnt ) == i )
        {
            res += fmt::format( fwStyle, " End" );
        }
        else if ( b_GsFrm_nc( b_crnt_plr_cnt ) == i )
        {
            res += fmt::format( fwStyle, " MaxPlrCnt({}):", getMaxPlrCnt() );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }
        else if ( b_GsFrm_nc( b_crnt_awn_cnt ) == i )
        {
            res += fmt::format( fwStyle, " CrntPlrCnt({}):", getCrntPlrCnt() );
            // res += fmt::format( fwStyle, " CrntAwnCnt({}):", getCrntAwnCnt()
            // );
        }
        else if ( b_GsFrm_nc( b_player_state ) == i )
        {
            res += fmt::format( fwStyle, " CrntAwnCnt({}):", getCrntAwnCnt() );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }
        else if ( b_GsFrm_nc( b_otr_sq_cnt ) == i )
        {
            res += fmt::format( fwStyle, " PlrState({}):", -1 );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }
        else if ( b_GsFrm_nc( b_inr_sq_cnt ) == i )
        {
            res += fmt::format( fwStyle, " OtrSqCnt({}):", getOtrSqCnt() );
            // res += fmt::format( fwStyle, " PlrState({}):", -1 );
        }

        else if ( b_GsFrm_nc( zb_gamse_state_size ) == i )
        {
            res += fmt::format( fwStyle, " InrSqCnt({}):", getInrSqCnt() );
            // res += fmt::format( fwStyle, " noop{}):", -1 );
        }
    }
    res += fmt::format( " WinSq:{} HomeSq:{} SqCnt:{} ", getWinSq(),
                        getHomeSq(), getSqCnt() );

    return res;
}
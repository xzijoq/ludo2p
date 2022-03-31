#pragma once
#include <string>

#include "u64def.h"
enum struct b_GameState : u64
{
    b_max_plr_cnt,
    b_crnt_plr_cnt,
    b_crnt_awn_cnt,
    b_player_state,
    b_crnt_team_cnt,
    b_otr_sq_cnt,
    b_inr_sq_cnt,
    zb_gamse_state_size

};

enum struct b_GameStateFlags : u64
{
    wwo,
    zfg_sz

};
class GameState
{
   public:
    u64 mGameState = 0;

    void setMaxPlrCnt( u64 cp );
    u64  getMaxPlrCnt() const;

    void setCrntPlrCnt( u64 cp );
    u64  getCrntPlrCnt() const;

    void setCrntAwnCnt( u64 awn );
    u64  getCrntAwnCnt() const;

    void setPlrState( u64 plr, bool what = true );
    u64  getPlrState( u64 plr ) const;

    void setCrntTeamCnt( u64 TeamCount );
    u64  getCrntTeamCnt() const;

    void setOtrSqCnt( u64 osc );
    u64  getOtrSqCnt() const;

    void setInrSqCnt( u64 osc );
    u64  getInrSqCnt() const;

    u64 getWinSq() const;
    u64 getHomeSq() const;
    u64 getSqCnt() const;

    void setFlag( b_GameStateFlags flg, bool what );
    u64  getFlag( b_GameStateFlags flg );

    void InitGameState( u64 maxPlrCnt, u64 crntPlrCnt, u64 crntAwnCnt, u64 crntTeamCnt,
                        u64 otrSqCnt, u64 inrSqCnt );

    std::string DebugString() const;
    // void setBrdSz( u64 awn );
    // u64  getBrdSz();
};

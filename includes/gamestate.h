#pragma once
#include <global.h>

#include <string>
using namespace Global;

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

    void setOtrSqCnt( u64 osc );
    u64  getOtrSqCnt() const;

    void setInrSqCnt( u64 osc );
    u64  getInrSqCnt() const;

    u64 getWinSq() const;
    u64 getHomeSq() const;
    u64 getSqCnt() const;

    void InitGameState( u64 maxPlrCnt, u64 crntPlrCnt, u64 crntAwnCnt,
                        u64 otrSqCnt ,u64 inrSqCnt);

    std::string DebugString() const;
    // void setBrdSz( u64 awn );
    // u64  getBrdSz();
};

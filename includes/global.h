
#pragma once
//$short is-- player:plr || pawn:awn || piece:ece --for better readability
#include <sys/types.h>

#include <cstdint>

// 32 bit may not provide it may need to switch to fast uint_fast64_t
// https://en.cppreference.com/w/cpp/types/integer
using u64 = std::uint_fast64_t;

static constexpr int MAX_SQUARES     = 128;
static constexpr int SQ_SZb=7;
static constexpr int MAX_PIECE_COUNT = 48;

extern int CURRENT_PLAYERS;
extern int CURRENT_PAWNS;

static constexpr int MAX_PLAYERS2     = 24;
static constexpr int MAX_PAWN2        = 24;
static constexpr int OUTER_RING2     = 28;

//$ storage size in bits



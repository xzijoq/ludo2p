#include <fmt/color.h>
#include <math.h>

#include <cstdint>
#include <ostream>
#include <streambuf>
#include <utility>

#include "Game.h"
#include "RegularMaps.h"
#include "core.h"
#include "game2p.h"
#include "gamestate.h"
#include "global.h"
#include "helper.h"
#include "math.h"
#include "piece.h"
#include "square.h"
#include "vector"
#include "visualtest.h"
using fmt::print;
using Global::GetEce;
using std::cout;
using std::endl;
void DebugSTest();
#ifdef NDEBUG
    #undef NDEBUG
#endif

int main()
{
    cout << "\nMAIN STARTS HERE" << endl;

 

  
    //print( "\n{}", sq.DebugString() );

    cout << endl << "MAIN ENDS HERE" << endl;
}

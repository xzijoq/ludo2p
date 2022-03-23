#include <fmt/color.h>

#include "core.h"
#include "helper.h"
#include "math.h"
#include "piece.h"

using fmt::print;
using std::cout;
using std::endl;
int main()
{
    Piece p1;
    p1.mEce=0;

    DisplayBits(p1.getEce());

    return 0;
}
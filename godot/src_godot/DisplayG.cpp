#include "DisplayG.h"


#include <math.h>
// 
#include <Color.hpp>
#include <OS.hpp>
#include <ResourceLoader.hpp>
#include <RichTextLabel.hpp>
#include <String.hpp>
#include <Viewport.hpp>
#include <array>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <system_error>
#include <thread>
//scons -j8 platform=linux generate_bindings=yes use_llvm=yes use_lld=yes target=debug

#include "Godot.hpp"
#include "Node.hpp"
#include "OS.hpp"
#include "Object.hpp"
#include "PackedScene.hpp"

#include "Vector2.hpp"
using namespace godot;
using namespace std::placeholders;

using namespace std::chrono_literals;

using namespace std::chrono;

void DisplayG::_ready()
{
  Godot::print("Ok this ran");
}




void DisplayG::_draw() {}

void DisplayG::OnSzChange() {}

void DisplayG::_init() {}



void DisplayG::_register_methods()
{
    register_method( "_ready", &DisplayG::_ready );
    register_method( "_draw", &DisplayG::_draw );
    register_method( "OnSzChange", &DisplayG::OnSzChange );


}
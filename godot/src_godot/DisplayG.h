#pragma once

#include <Control.hpp>
#include <Godot.hpp>
#include <PackedScene.hpp>

#include "Button.hpp"


#include "Ref.hpp"
#include "RichTextLabel.hpp"
#include <Timer.hpp>

namespace godot
{
class DisplayG : public godot::Control
{
    GODOT_CLASS( DisplayG, Control );

   public:
    //$ Registered
    static void _register_methods();
    void        _init();
    void        OnSzChange();
    void        _draw();
    void        _ready();

    //$ not registered

 

};
}  // namespace godot
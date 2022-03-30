# :red_book: Global COmments
- has plr depends on knowledge of current awns (In Square)


# :blue_book: Things logged
- [git hub emojes](https://gist.github.com/rxaviers/7360908)
- godot 4 gdextention not used yet

# :smoking: Compiling / Cross Compling
- GodotCpp for version [3.4](https://github.com/godotengine/godot-cpp/tree/3.4) was compiled as 
  - ```ini
    scons -j8 platform=linux generate_bindings=yes use_llvm=yes use_lld=yes target=debug
    ```
  - Details for Compiling for and android are on the repo page, works, tested
- conan profiles need to be swapped in run.py for cross compiling
  - :telescope: look into c++_static vs c++_shared vs libc++
- :hammer: in cmake lists the android version of godot-cpp must be linked (automate)
- :hammer: for godot compile multiple libraries for each platform :pill: will do after upgrading to godot4 gd extentions, or will have to redo for no reason 
- :beetle: fmt dosent compile well with libc++, which may be used for xcompiling on android (to check switch to libc++ in conan profile)


# :beetle: called a STATIC FUNCTION via MEMBER in [piecetest](./tests/piecetest.cpp) on line 109
- on march 24 commit globalPiece
  
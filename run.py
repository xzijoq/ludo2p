# -================GOD ENDS HERE===============================
# --TODO ENABLE EAST CROSS SCRIPTING

import os
import subprocess
import sys
import argparse
import shutil

from os.path import join
from os.path import isdir
from os.path import isfile
import inspect
from inspect import currentframe, getframeinfo

conan = True
TargetApp = True
EnableTest = True
godot = False
# ---------DEFS DONT ALTER-------------
cwd = os.getcwd()
Fatal = True
# --------------END DEFS----------------------


# -------------------CONAN DATA---------------------------

if conan:
    conan_dir = "conan"
    conan_dir_path = join(cwd, conan_dir)
    conan_build_dir = "conan_cmake"
    conan_build_dir_path = join(cwd, conan_build_dir)

    # 'clang' | ''/'default'
    conan_profile_host = "default"
    conan_profile_host = "clang"

    conan_profile_build = "default"
    conan_profile_build = "clang"
    conan_profile_host_path = join(conan_dir_path, conan_profile_host)
    conan_profile_build_path = join(conan_dir_path, conan_profile_build)

    if conan_profile_host == "default" or conan_profile_host == "":
        conan_profile_host_path = "default"
    if conan_profile_build == "default" or conan_profile_build == "":
        conan_profile_build_path = "default"

# -------------------CONAN DATA ENDS----------------------

# ---------------- CMAKE DATA START ---------------
# -- Required vaiables-- set to "" if not in use
if Fatal == True:
    build_dir = "build"
    build_dir_path = join(cwd, build_dir)

    cmake_compiler = ""
    cmake_compiler = "clang++"

    cmake_build_type = "Relese"
    cmake_build_type = "Debug"

    cmake_generator = "Ninja"
    #"\"Ninja Multi-Config\""
    # leave empty if using conan
    cmake_toolchain_path = ""

# ----------------CMAKE DATA ENDS HERE-------------------

# ---------------------------TARGET

if TargetApp:
    target_src_dir = "consoleapp"
    target = "corex"
# -- ------------------------END TARGET

# --------Test---

if EnableTest == True:
    TestSourceDir = "tests/"
    Tests = ['ggtest']

# ----EndTest------

# -------------------GODOT DATA STARTS----------------------

if godot:
    godot_scene = "Display.tscn"
    godot_executable = f"/home/babayaga/godot/godotb"
    godot_project_path = f"/home/babayaga/godot/projects/ludo2p/godot/gludo2p"
    godot_relative_src_path = f"godot/src_godot"
    godot_lib = ["libgui.so"]
    godot_dir = join(godot_project_path, "bin")
    godot_scene_dir = join(godot_project_path, "scenes")
# -------------------Godot DATA ENDS----------------------


# ---------------MAIN STARTS HERE----------------------


def MainFunc():
    p_fnc("executing")
    goRun_check()
    if 'clean' in args.goRun:
        clean()
        return
    if 'c' in args.goRun:
        conan_run()
    if 'r' in args.goRun:
        cmake_run()
    if 'b' in args.goRun:
        cmake_build()
    if 'x' in args.goRun:
        run_target()
    if 't' in args.goRun:
        run_test()
    if 'gc' in args.goRun:
        godot_copy()
    if 'gx' in args.goRun:
        godot_run()
    goRun_check()
    p_mwg("Script END")
    return 0



def goRun_check():
    p_fnc("executing")
    validLis = ['c', 'r', 'b', 'x', 't', 'gc', 'gx', 'clean']
    isValid = False
    # isValid = goRun_has('clean') or goRun_has('c') or goRun_has(
    #    'r') or goRun_has('b') or goRun_has('x') or goRun_has('gc') or goRun_has('gx')
    for i in args.goRun:
        if i in validLis:
            isValid = True
        else:
            p_wrn(f"Unused argument: {i}")
        pass
    if not isValid:
        p_msg(f"Valid Arguments to Run:\n\
            c:     conan_run()\n\
            r:     cmake_run()\n\
            b:     cmake_build()\n\
            x:     run_target()\n\
            t:     run_tests()\n\
            gc:    godot_copy()\n\
            gx:    godot_run()\n\
            clean: clean() and return\n\
            --help: for help\n\
        ")

        p_err("Please Enter a Valid Command", Fatal)
    if(('c' in args.goRun) and conan == False):
        p_wrn(f"Coan is set to false, yet coanan_run() was requested via arg 'c'\n")

    if(('gc' in args.goRun) and godot == False):
        p_wrn("Godot is set to false, yet godot_copy() was requested via arg 'gc' \n")
    if(('gx' in args.goRun) and godot == False):
        p_wrn("Godot is set to false, yet  godot_run() was requested via arg 'gx'\n")

    if(('gx' in args.goRun) and not goRun_has('gc')):
        p_err("Will Try To Run Godot Scene Without Copying THe LIBRARY !!!! \n")

    if(('x' in args.goRun) and TargetApp == False):
        p_wrn("TargetApp is set to false, yet run_target() was requested via arg 'x'\n")
    if(('t' in args.goRun) and EnableTest == False):
        p_wrn("EnableTest is set to false, yet run_test) was requested via arg 't'\n")


def cmake_run():
    p_fnc("Executing")
    global cmake_toolchain_path
    if not isfile(join(cwd, "CMakeLists.txt")):
        p_err("CMakeLists.txt not found", Fatal)
    if (build_dir == ""):
        p_err("CmakeBuildDir cant be null specified", Fatal)
    if isdir(build_dir_path):
        p_msg(f"Deleting:  {build_dir_path}")
        shutil.rmtree(build_dir_path)

    # @ todo: currently specifying source directory is not supported
    cmake_command = f"cmake -S./ -B {build_dir}"

    if(not cmake_build_type == ""):
        cmake_command += f" -D CMAKE_BUILD_TYPE={cmake_build_type}"

    if(not cmake_compiler == ""):
        cmake_command += f" -D CMAKE_CXX_COMPILER={cmake_compiler}"

    if(not cmake_generator == ""):
        cmake_command += f" -G {cmake_generator}"

    if conan and cmake_toolchain_path == "":
        cmake_toolchain_file = "conan_toolchain.cmake"
        cmake_toolchain_dir = conan_build_dir_path
        cmake_toolchain_path = join(cmake_toolchain_dir, cmake_toolchain_file)

    if(not cmake_toolchain_path == ""):
        cmake_command += f" -D CMAKE_TOOLCHAIN_FILE={cmake_toolchain_path}"

    if(TargetApp == True):
        cmake_command += f" -D TargetApp=True"
    if (godot == True):
        cmake_command += f" -D Godot=True"
    if (EnableTest == True):
        cmake_command += f" -D EnableTest=True"

    if(not {args.cma} == ""):
        cmake_command += f" {args.cma}"

    result = subprocess.run([cmake_command], shell=True)
    p_nfy(f"{result}")

    if not result.returncode == 0:
        p_err(f"Failed : {result.returncode}", Fatal)

    pass


def cmake_build():
    p_fnc("executing")
    if not os.path.isdir(build_dir):
        p_nfy("Try calling the script with f/r or full/run")
        p_err("Build Directory not found", Fatal)

    cmake_build_command = f"cmake --build {build_dir} -j8 "

    if not(args.cba == ""):
        cmake_build_command += f"{args.cba}"

    result = subprocess.run(
        [cmake_build_command], shell=True)
    p_nfy(f"{result}")

    if not result.returncode == 0:
        p_err(f"Failed : {result.returncode}", Fatal)

    if isfile(join(build_dir_path, "compile_commands.json")):
        if isfile(join(cwd, "compile_commands.json")):
            os.remove(join(cwd, "compile_commands.json"))
        else:
            p_wrn(f"can'nt find compile_commands.json in cwd: {cwd}")
        p_msg("Copyting compile_commands.json")
        shutil.copy(
            join(build_dir, "compile_commands.json"),
            join(cwd, "compile_commands.json"),
        )

    else:
        p_wrn(
            f"can'nt find compile_commands.json in build dir: {build_dir_path}")


def run_target():
    p_fnc("Executing")
    if TargetApp == False:
        p_wrn("TargetApp is DEFINED FALSE")
        return
    global target

    if args.target != "":
        target = args.target

    if target == "":
        p_wrn("NO TARGET TO RUN")
        return False

    target_path = join(build_dir_path, target_src_dir, target)

    if not isfile(target_path):
        p_err(f"NotFound {target_path}")
        return

    result = subprocess.run(
        [f"{target_path} {args.exa}"], shell=True
    )
    p_nfy(f"{result}")


def run_test():
    p_fnc("executing")
    if EnableTest == False:
        p_wrn("EnableTest is FALSE")
        return
    # $CAN USE CTEST FOR ITS FEATURES
    #test=f"ctest  --output-on-failure --verbose --gtest_color=yes"
    test_dir = join(build_dir_path, TestSourceDir)
    for i in Tests:
        test_path = join(test_dir, i)
        test_command = test_path
        if args.tea != "":
            test_command += args.tea
        result = subprocess.run([test_command], shell=True)
        p_nfy(f"{result}")


def conan_run():
    p_fnc("executing")
    if not conan:
        p_wrn("Conan is DEFINED FALSE")
        return False

    if not isdir(conan_dir_path):
        p_err(f"Conan Directory Not Found: {conan_dir_path}", Fatal)

    if conan_profile_host_path != "default" and not isfile(conan_profile_host_path):
        p_err(f"NOT FOUND {conan_profile_host_path}", Fatal)

    if conan_profile_build_path != "default" and not isfile(conan_profile_build_path):
        p_err(f"NOT FOUND {conan_profile_build_path}", Fatal)

    if isdir(conan_build_dir_path):
        p_msg(f"Deleting ConanBuildDir:\n   {conan_build_dir_path}")
        shutil.rmtree(conan_build_dir_path)
    conan_r = f"conan install {conan_dir_path}\
             -if={conan_build_dir_path} \
             --build=missing \
             --profile:build={conan_profile_build_path} \
             --profile:host={conan_profile_host_path}"
    if(not {args.coa} == ""):
        conan_r += f" {args.coa}"
    result = subprocess.run([conan_r], shell=True)
    p_nfy(f"{result}")
    if not result.returncode == 0:
        p_err("Failed", Fatal)


def clean():
    p_fnc("Executing")
    shutil.rmtree(join(cwd, ".vscode"), ignore_errors=True)
    shutil.rmtree(join(cwd, ".cache"), ignore_errors=True)
    shutil.rmtree(build_dir_path, ignore_errors=True)
    shutil.rmtree(conan_build_dir_path, ignore_errors=True)
    if godot:
        for i in godot_lib:
            target_lib = join(godot_dir, i)
            if isfile(target_lib):
                os.remove(target_lib)


def godot_copy():
    p_fnc("executing")
    if godot == False:
       # p_wrn("Godot is set to False")
        return False

    if not isdir(godot_project_path):
        p_err("Godot ProjectDir NOT FOUND:\n{godot_project_path} ", Fatal)

    if not isfile(join(godot_project_path, "project.godot")):
        p_err(
            "MostLikely Invalid godot project Directoey:\n{godot_project_path}")
    if not isdir(godot_dir):
        p_err("Godot Library folder  not found:\n{godot_dir}", Fatal)

    if not isdir(godot_dir):
        p_err(f"{godot_dir} Not FOund", Fatal)

    for i in godot_lib:
        target_lib = join(godot_dir, i)
        src_lib = join(build_dir_path, godot_relative_src_path, i)

        if not isfile(src_lib):
            p_err(f"Godot Built Library Not FOund:\n{src_lib} ", Fatal)
        if isfile(target_lib):
            p_msg(f"removing {target_lib}:")
            os.remove(target_lib)
        else:
            p_wrn(f"{target_lib} not fouind")
        p_msg(f"copying {src_lib} --> {target_lib}")
        ts = shutil.copy(src_lib, target_lib)


def godot_run():
    p_fnc("executing")
    if godot == False:
        #p_wrn("Godot is set to False")
        return False

    global godot_scene
    if not args.scene == "":
        godot_scene = args.scene
    if not str(godot_scene).endswith(".tscn"):
        godot_scene = godot_scene + ".tscn"

    os.chdir(godot_project_path)
    scene_path = join(godot_scene_dir, godot_scene)
    if not isfile(godot_executable):
        p_err("Godot Executable not found at {godot_executable}")
        return False
    if not isdir(godot_scene_dir):
        p_err(f"Does Not Exist {godot_scene_dir}  ")
        return False
    if not isfile(scene_path):
        p_err(f"Does Not Exist:--- {godot_scene} --AT \n {scene_path} ")
        return False
    runs = f"{godot_executable} -d {scene_path}"
    result = subprocess.run([runs], shell=True)
    p_nfy(f"{result}")
    pass


# -------------------PARSER STARTS HERE----------------------
parser = argparse.ArgumentParser()
parser.add_argument("goRun", help="Get Some Help", nargs='+', default="b")
parser.add_argument("-t", "--target", help="target to run", default="")
parser.add_argument("-exa", help="executable args ", default="")
parser.add_argument("-cma", help="cmake args ENTER IN QUOTES", default="")
parser.add_argument(
    "-cba", help="cmake build args ENTER IN QUOTES", default="")
parser.add_argument("-coa", help="conan args ENTER IN QUOTES", default="")
parser.add_argument("-tea", help="TEST args ENTER IN QUOTES", default="")
parser.add_argument("-sc", "--scene", help="GodotScene", default="")
args = parser.parse_args()


# -------------------PARSER ENDS HERE----------------------

# ---------------- PRINT FUNCS ---------------


def p_msg(what):
    callerframerecord = inspect.stack()[1]
    frame = callerframerecord[0]
    info = inspect.getframeinfo(frame)
    print(f"\033[30;102mMsg:\033[00m {what}\
        func:{info.function}\
        line:{info.lineno}\
        ")


def p_wrn(what):
    callerframerecord = inspect.stack()[1]
    frame = callerframerecord[0]
    info = inspect.getframeinfo(frame)
    print(f"\033[30;103;3;4mWarn: {what}\
        func:{info.function}\
        line:{info.lineno}\
        \033[00m")


def p_mwg(what):
    callerframerecord = inspect.stack()[1]
    frame = callerframerecord[0]
    info = inspect.getframeinfo(frame)
    print(f"\033[30;106;3;4m {what}\
        func:{info.function}\
        line:{info.lineno}\
        \033[00m")


def p_nfy(what):
    callerframerecord = inspect.stack()[1]
    frame = callerframerecord[0]
    info = inspect.getframeinfo(frame)
    print(f"\033[30;44mNotice:\033[00m {what}\
        func:{info.function}\
        line:{info.lineno}")


def p_fnc(what):
    callerframerecord = inspect.stack()[1]
    frame = callerframerecord[0]
    info = inspect.getframeinfo(frame)
    print(f"\033[30;45m{what}\033[00m\
        func:{info.function}\
        line:{info.lineno}")


def p_err(what, isFatal=False):
    callerframerecord = inspect.stack()[1]
    frame = callerframerecord[0]
    info = inspect.getframeinfo(frame)
    print(f"\033[30;101;3;4mErr: {what}\
        line:{info.lineno}\
        func:{info.function}\
        \033[00m")
    if isFatal:
        quit()

# ---------------- PRINT FUNCS END---------------


MainFunc()
# scons platform=android android_arch=arm64v8 generate_bindings=yes -j8

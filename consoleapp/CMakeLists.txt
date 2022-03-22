cmake_minimum_required(VERSION 3.2)


set(CoreX corex)
add_executable(${CoreX} main.cpp  )
target_link_libraries(${CoreX} PRIVATE ${Core} ${CommonLib} )
target_compile_options(${CoreX} PRIVATE ${CommonFlg})

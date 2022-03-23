
cmake_minimum_required(VERSION 3.2)



set(ggtests ggtest)
add_executable(${ggtests} coretest.cpp  piecetest.cpp)
target_link_libraries(${ggtests} PRIVATE ${Core} ${CommonLib} GTest::GTest)
target_compile_options(${ggtests} PRIVATE ${CommonFlg})

add_test(coreTest ${ggtests})
#add_exec(${tests} coretest.cpp  )

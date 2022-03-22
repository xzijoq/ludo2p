cmake_minimum_required(VERSION 3.2)





set(gSOURCES ${CMAKE_CURRENT_SOURCE_DIR})
set(gcp /home/babayaga/godot/projects/godot-cpp/)
set(GodotUI gui)

add_library(${GodotUI} SHARED)
target_include_directories(
  ${GodotUI} PUBLIC includes ${gcp}/include ${gcp}/include/core
                    ${gcp}/include/gen ${gcp}/godot-headers)

target_link_directories(${GodotUI} PRIVATE ${gcp}/bin)
target_compile_options(${GodotUI} PRIVATE ${CommonFlg})

# target_compile_features(${GodotUI} PUBLIC cxx_std_20)
target_sources(${GodotUI} PRIVATE ${gSOURCES}/GdRegClass.cpp
                                  ${gSOURCES}/DisplayG.cpp
                                  )
target_link_libraries(${GodotUI} PRIVATE galx asio::asio ${Core})
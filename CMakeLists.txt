cmake_minimum_required(VERSION 3.10.0)
project(visibility_graph)
aux_source_directory(. src_list)

add_executable(main ${src_list})

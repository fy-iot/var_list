cmake_minimum_required(VERSION 3.10)

project(demo)
aux_source_directory(. src_list)
message(${src_list})
add_executable(demo ${src_list})

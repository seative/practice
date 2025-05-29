cmake_minimum_required(VERSION 3.22)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 80)

project(hellocuda LANGUAGES CXX CUDA)

add_executable(main arraySum.cu)

target_compile_options(main PUBLIC $<$<COMPILE_LANGUAGE:CUDA>:--extended-lambda>)


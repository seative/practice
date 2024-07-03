cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 17)

project(main LANGUAGES CXX)


find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC benchmark::benchmark)
target_link_libraries(main PUBLIC benchmark::benchmark_main)
target_compile_definitions(main PUBLIC -DBENCHMARK_DISPATCHED_KERNELS)
target_compile_options(main PUBLIC $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mavx2$<SEMICOLON>-mfma>$<SEMICOLON>-g)

add_executable(saxpy saxpy.cpp)

target_compile_options(saxpy PUBLIC $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mavx2$<SEMICOLON>-mfma$<SEMICOLON>-g> $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/arch:AVX2>) 
# 如果你的电脑不支持 AVX2，请删除本行
add_custom_command(
    OUTPUT saxpy.s
    COMMAND ${CMAKE_CXX_COMPILER} -S -o saxpy.s ${CMAKE_CURRENT_SOURCE_DIR}/saxpy.cpp
    DEPENDS saxpy.cpp
)

# Add a custom target to run the custom command
add_custom_target(saxpy_assembly ALL DEPENDS saxpy.s)

target_link_libraries(saxpy PUBLIC benchmark::benchmark)
target_link_libraries(saxpy PUBLIC benchmark::benchmark_main)  # 测试性能时使用此行

target_link_libraries(saxpy PUBLIC GTest::gtest)
 target_link_libraries(saxpy PUBLIC GTest::gtest_main)  # 测试正确性时使用此行

find_package(OpenMP REQUIRED)
target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)


add_executable(sum sum.cpp)

target_compile_options(sum PUBLIC $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mavx2$<SEMICOLON>-g> $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/arch:AVX2>) 
# add_custom_command(
#     OUTPUT sum.s
#     COMMAND ${CMAKE_CXX_COMPILER} -S -o sum.s ${CMAKE_CURRENT_SOURCE_DIR}/sum.cpp
#     DEPENDS sum.cpp
# )

# # Add a custom target to run the custom command
# add_custom_target(sum_assembly ALL DEPENDS sum.s)

target_link_libraries(sum PUBLIC benchmark::benchmark)
target_link_libraries(sum PUBLIC benchmark::benchmark_main)  # 测试性能时使用此行

target_link_libraries(sum PUBLIC GTest::gtest)
target_link_libraries(sum PUBLIC GTest::gtest_main)  # 测试正确性时使用此行

target_link_libraries(sum PUBLIC OpenMP::OpenMP_CXX)


add_executable(countp countp.cpp)
target_compile_options(countp PUBLIC $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mavx2$<SEMICOLON>-g> $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/arch:AVX2>) 
add_custom_command(
    OUTPUT countp.s
    COMMAND ${CMAKE_CXX_COMPILER} -S -o countp.s ${CMAKE_CURRENT_SOURCE_DIR}/countp.cpp
    DEPENDS countp.cpp
)

# Add a custom target to run the custom command
add_custom_target(countp_assembly ALL DEPENDS countp.s)

target_link_libraries(countp PUBLIC benchmark::benchmark)
target_link_libraries(countp PUBLIC benchmark::benchmark_main)  # 测试性能时使用此行

target_link_libraries(countp PUBLIC GTest::gtest)
target_link_libraries(countp PUBLIC GTest::gtest_main)  # 测试正确性时使用此行

target_link_libraries(countp PUBLIC OpenMP::OpenMP_CXX)
cmake_minimum_required(VERSION 3.0.0)
project(CompilationPrinciple)

# 设置语言版本
set(CMAKE_CXX_STANDARD 11)

# 查找当前目录下的所有源文件,并将名称保存到 DIR_SRCS 变量
# aux_source_directory(. DIR_SRCS)
set(DIR_SRCS compiler.h compiler.cpp
    my_structs.h
    lexical.h lexical.cpp
    grammar.h grammar.cpp
    parser.h parser.cpp
    operation.h operation.cpp
    conditional.h conditional.cpp
    combuilder.h combuilder.cpp
)

# 指定生成目标
add_executable(CompilationPrinciple ${DIR_SRCS})

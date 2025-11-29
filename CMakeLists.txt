cmake_minimum_required(VERSION 4.0)
project(AlgebraLinear C)

set(CMAKE_C_STANDARD 17)

add_executable(AlgebraLinear
        Primeiro/main.c
        Primeiro/matrizes.h
        Primeiro/lib_matriz.c
        Primeiro/funcoes_mat.c
        Primeiro/utils.c
        Primeiro/utils.h)

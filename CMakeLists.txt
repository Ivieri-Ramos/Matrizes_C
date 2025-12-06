cmake_minimum_required(VERSION 3.20)
project(AlgebraLinear)

set(CMAKE_C_STANDARD 17)

add_executable(AlgebraLinear
        Primeiro/main.c
        Primeiro/matrizes.h
        Primeiro/lib_matriz.c
        Primeiro/funcoes_mat.c
        Primeiro/utils.c
        Primeiro/utils.h
        Primeiro/funcoes_mat.h
        Primeiro/calcular_diferenca.c
        Primeiro/calcular_diferenca.h)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Detectado GCC/Clang no Linux/WSL. Ativando Sanitizers...")

        target_compile_options(AlgebraLinear PRIVATE
                -fsanitize=address,undefined
                -g
                -fno-omit-frame-pointer
                -O1
        )
        target_link_options(AlgebraLinear PRIVATE
                -fsanitize=address,undefined
                -static-libasan
        )
    elseif(MSVC)
        message(STATUS "Compilador MSVC detectado. AddressSanitizer nao sera ativado automaticamente.")
    endif()

endif()
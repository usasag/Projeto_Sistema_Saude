cmake_minimum_required(VERSION 3.26)
project(Projeto_Sistema_Saude_TRABALHO C)

set(CMAKE_C_STANDARD 99)

add_library(Projeto_Sistema_Saude_TRABALHO
        utilidades.h
        "projeto base.c"
        pacientes.h
        atendimento.h
        atendimento.c
        paciente.c
)

#include "crud.h"

int main() {
    iniciar_livres();

    inserir("Vitor Bispo");
    inserir("Ajalmar Rego");
    inserir("Mariana Clea");
    listar();

    inserir("Vitor Bispo");
    remover("Ajalmar Rego");
    listar();

    alterar("Mariana Clea", "Mariana Clea Abreu da Silva");
    listar();

    return 0;
}

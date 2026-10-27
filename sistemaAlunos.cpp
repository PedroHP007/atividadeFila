
#include <iostream>
#include <string>
using namespace std;

struct Conteudo {
    string nome;
    Conteudo* prox;
};

struct Disciplina {
    string nome;
    int creditos;
    Conteudo* inicioConteudos;
    Disciplina* prox;
};

struct Aluno {
    string nome;
    string cpf;
    int idade;
    string matricula;
    Disciplina* inicioDisciplinas;
    Aluno* prox;
};

struct Fila {
    Aluno* inicio;
    Aluno* fim;
};

void inicializarFila(Fila &fila) {
    fila.inicio = nullptr;
    fila.fim = nullptr;
}

Aluno* buscarAluno(Fila &fila, string matricula) {
    Aluno* atual = fila.inicio;

    while (atual != nullptr) {
        if (atual->matricula == matricula)
            return atual;

        atual = atual->prox;
    }

    return nullptr;
}

void enfileirar(Fila &fila) {
    Aluno* novo = new Aluno;

    cout << "Nome: ";
    getline(cin >> ws, novo->nome);

    cout << "CPF: ";
    getline(cin, novo->cpf);

    cout << "Idade: ";
    cin >> novo->idade;

    cout << "Matricula: ";
    cin >> novo->matricula;

    if (buscarAluno(fila, novo->matricula) != nullptr) {
        cout << "Matricula ja cadastrada!\n";
        delete novo;
        return;
    }

    novo->inicioDisciplinas = nullptr;
    novo->prox = nullptr;

    if (fila.inicio == nullptr) {
        fila.inicio = novo;
        fila.fim = novo;
    } else {
        fila.fim->prox = novo;
        fila.fim = novo;
    }

    cout << "Aluno enfileirado!\n";
}

void desenfileirar(Fila &fila) {
    if (fila.inicio == nullptr) {
        cout << "Fila vazia!\n";
        return;
    }

    Aluno* removido = fila.inicio;
    fila.inicio = fila.inicio->prox;

    if (fila.inicio == nullptr)
        fila.fim = nullptr;

    cout << "Aluno removido: " << removido->nome << "\n";

    Disciplina* d = removido->inicioDisciplinas;

    while (d != nullptr) {
        Conteudo* c = d->inicioConteudos;

        while (c != nullptr) {
            Conteudo* tempC = c;
            c = c->prox;
            delete tempC;
        }

        Disciplina* tempD = d;
        d = d->prox;
        delete tempD;
    }

    delete removido;
}

void consultarPrimeiro(Fila &fila) {
    if (fila.inicio == nullptr) {
        cout << "Fila vazia!\n";
        return;
    }

    cout << "Nome: " << fila.inicio->nome << "\n";
    cout << "CPF: " << fila.inicio->cpf << "\n";
    cout << "Idade: " << fila.inicio->idade << "\n";
    cout << "Matricula: " << fila.inicio->matricula << "\n";
}

void adicionarDisciplina(Fila &fila) {
    string matricula;

    cout << "Matricula do aluno: ";
    cin >> matricula;

    Aluno* aluno = buscarAluno(fila, matricula);

    if (aluno == nullptr) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    Disciplina* nova = new Disciplina;

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nova->nome);

    Disciplina* atual = aluno->inicioDisciplinas;

    while (atual != nullptr) {
        if (atual->nome == nova->nome) {
            cout << "Disciplina ja cadastrada!\n";
            delete nova;
            return;
        }

        atual = atual->prox;
    }

    cout << "Quantidade de creditos: ";
    cin >> nova->creditos;

    nova->inicioConteudos = nullptr;
    nova->prox = aluno->inicioDisciplinas;
    aluno->inicioDisciplinas = nova;

    cout << "Disciplina adicionada!\n";
}

void removerDisciplina(Fila &fila) {
    string matricula, nome;

    cout << "Matricula do aluno: ";
    cin >> matricula;

    Aluno* aluno = buscarAluno(fila, matricula);

    if (aluno == nullptr) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nome);

    Disciplina* atual = aluno->inicioDisciplinas;
    Disciplina* anterior = nullptr;

    while (atual != nullptr && atual->nome != nome) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == nullptr) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    if (anterior == nullptr)
        aluno->inicioDisciplinas = atual->prox;
    else
        anterior->prox = atual->prox;

    Conteudo* c = atual->inicioConteudos;

    while (c != nullptr) {
        Conteudo* temp = c;
        c = c->prox;
        delete temp;
    }

    delete atual;
    cout << "Disciplina removida!\n";
}

void listarDisciplinas(Fila &fila) {
    string matricula;

    cout << "Matricula do aluno: ";
    cin >> matricula;

    Aluno* aluno = buscarAluno(fila, matricula);

    if (aluno == nullptr) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    Disciplina* d = aluno->inicioDisciplinas;

    if (d == nullptr) {
        cout << "Aluno sem disciplinas.\n";
        return;
    }

    while (d != nullptr) {
        cout << "Disciplina: " << d->nome
             << " | Creditos: " << d->creditos << "\n";

        d = d->prox;
    }
}

void adicionarConteudo(Fila &fila) {
    string matricula, nomeDisciplina;

    cout << "Matricula do aluno: ";
    cin >> matricula;

    Aluno* aluno = buscarAluno(fila, matricula);

    if (aluno == nullptr) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nomeDisciplina);

    Disciplina* d = aluno->inicioDisciplinas;

    while (d != nullptr && d->nome != nomeDisciplina)
        d = d->prox;

    if (d == nullptr) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    Conteudo* novo = new Conteudo;

    cout << "Descricao do conteudo: ";
    getline(cin >> ws, novo->nome);

    novo->prox = d->inicioConteudos;
    d->inicioConteudos = novo;

    cout << "Conteudo adicionado!\n";
}

void removerConteudo(Fila &fila) {
    string matricula, nomeDisciplina, nomeConteudo;

    cout << "Matricula do aluno: ";
    cin >> matricula;

    Aluno* aluno = buscarAluno(fila, matricula);

    if (aluno == nullptr) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nomeDisciplina);

    Disciplina* d = aluno->inicioDisciplinas;

    while (d != nullptr && d->nome != nomeDisciplina)
        d = d->prox;

    if (d == nullptr) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    cout << "Conteudo a remover: ";
    getline(cin >> ws, nomeConteudo);

    Conteudo* atual = d->inicioConteudos;
    Conteudo* anterior = nullptr;

    while (atual != nullptr && atual->nome != nomeConteudo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == nullptr) {
        cout << "Conteudo nao encontrado!\n";
        return;
    }

    if (anterior == nullptr)
        d->inicioConteudos = atual->prox;
    else
        anterior->prox = atual->prox;

    delete atual;
    cout << "Conteudo removido!\n";
}

void listarConteudos(Fila &fila) {
    string matricula, nomeDisciplina;

    cout << "Matricula do aluno: ";
    cin >> matricula;

    Aluno* aluno = buscarAluno(fila, matricula);

    if (aluno == nullptr) {
        cout << "Aluno nao encontrado!\n";
        return;
    }

    cout << "Nome da disciplina: ";
    getline(cin >> ws, nomeDisciplina);

    Disciplina* d = aluno->inicioDisciplinas;

    while (d != nullptr && d->nome != nomeDisciplina)
        d = d->prox;

    if (d == nullptr) {
        cout << "Disciplina nao encontrada!\n";
        return;
    }

    Conteudo* c = d->inicioConteudos;

    if (c == nullptr) {
        cout << "Disciplina sem conteudos.\n";
        return;
    }

    while (c != nullptr) {
        cout << "- " << c->nome << "\n";
        c = c->prox;
    }
}

void listarTodos(Fila &fila) {
    Aluno* a = fila.inicio;

    if (a == nullptr) {
        cout << "Fila vazia!\n";
        return;
    }

    while (a != nullptr) {
        cout << "\n========================\n";
        cout << "Nome: " << a->nome << "\n";
        cout << "CPF: " << a->cpf << "\n";
        cout << "Idade: " << a->idade << "\n";
        cout << "Matricula: " << a->matricula << "\n";

        Disciplina* d = a->inicioDisciplinas;

        while (d != nullptr) {
            cout << "  Disciplina: " << d->nome
                 << " | Creditos: " << d->creditos << "\n";

            Conteudo* c = d->inicioConteudos;

            while (c != nullptr) {
                cout << "    Conteudo: " << c->nome << "\n";
                c = c->prox;
            }

            d = d->prox;
        }

        a = a->prox;
    }
}

bool filaVazia(Fila &fila) {
    return fila.inicio == nullptr;
}

int main() {
    Fila fila;
    inicializarFila(fila);

    int opcao;

    do {
        cout << "\n===== FILA DE ALUNOS =====\n";
        cout << "1 - Enfileirar aluno\n";
        cout << "2 - Desenfileirar aluno\n";
        cout << "3 - Consultar primeiro aluno\n";
        cout << "4 - Adicionar disciplina\n";
        cout << "5 - Remover disciplina\n";
        cout << "6 - Listar disciplinas de um aluno\n";
        cout << "7 - Adicionar conteudo\n";
        cout << "8 - Remover conteudo\n";
        cout << "9 - Listar conteudos de uma disciplina\n";
        cout << "10 - Listar todos os alunos\n";
        cout << "11 - Verificar se fila esta vazia\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                enfileirar(fila);
                break;
            case 2:
                desenfileirar(fila);
                break;
            case 3:
                consultarPrimeiro(fila);
                break;
            case 4:
                adicionarDisciplina(fila);
                break;
            case 5:
                removerDisciplina(fila);
                break;
            case 6:
                listarDisciplinas(fila);
                break;
            case 7:
                adicionarConteudo(fila);
                break;
            case 8:
                removerConteudo(fila);
                break;
            case 9:
                listarConteudos(fila);
                break;
            case 10:
                listarTodos(fila);
                break;
            case 11:
                cout << (filaVazia(fila)
                    ? "Fila vazia!\n"
                    : "Fila possui alunos.\n");
                break;
            case 0:
                cout << "Encerrando...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    while (!filaVazia(fila))
        desenfileirar(fila);

    return 0;
}

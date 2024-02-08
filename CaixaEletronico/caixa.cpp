#include <iostream>
#include <stdlib.h>
#include <climits>
#include <locale.h>
using namespace std;

const int n = 7;
const int notas_tipo[n] = {100, 50, 20, 10, 5, 2, 1};

struct Notas {
    int notas[n] = {0, 0, 0, 0, 0, 0, 0};
};

// Declaração de funções
void menu_cliente();
void conf_notas(Notas &estq);
void nova_opr();
void Ent_depst(Notas &estq, int &balanco);
void conf_saque(Notas &estq, int balanco, int saque);
void Ent_saque(Notas &estq, int saque);
void Saida_balanco(int balanco);
void cadastrar_admin(Notas &estq);
void menu_admin(Notas &estq);
void bal_caixa(Notas &estq);
void depst_caixa(Notas &estq);
void saida_depst_caixa(Notas &estq);
void validacao_entr_dados(int &var, string str, string invalid);

int main() {
    setlocale(LC_ALL, "Portuguese");

    Notas estq;
    int op, saque;
    int balanco = 0;

    do {
        cout << "Bem vindo!" << endl;
        conf_notas(estq);
        menu_cliente();
        validacao_entr_dados(op, "\nPor favor, escolha uma opção: ", "Opção inválida, tente novamente");

        switch (op) {
            case 1:
                Saida_balanco(balanco);
                nova_opr();
                break;
            case 2:
                Ent_depst(estq, balanco);
                Saida_balanco(balanco);
                nova_opr();
                break;
            case 3:
                do {
                    validacao_entr_dados(saque, "\nDigite o valor que você deseja sacar: ", "Opção inválida, tente novamente");
                    conf_saque(estq, balanco, saque);
                } while (saque < 0 || saque > balanco);
                balanco -= saque;
                Saida_balanco(balanco);
                nova_opr();
                break;
            case 4:
                cadastrar_admin(estq);
                nova_opr();
                break;
            default:
                if (op < 1 || op > 5) {
                    cout << "Opção inválida. Por favor digite novamente." << endl;
                    break;
                }
        }

    } while (op != 5);
}

void menu_cliente() {
    cout << "\n----------MENU----------";
    cout << "\n|1.Checar balanço      |";
    cout << "\n|2.Depósito            |";
    cout << "\n|3.Saque               |";
    cout << "\n|4.Login Admin         |";
    cout << "\n|5.Sair                |";
    cout << "\n------------------------";
}

void conf_notas(Notas &estq) {
    for (int i = 0; i < n; i++) {
        if (estq.notas[i] == 0)
            cout << "\nPeça para um administrador inserir mais notas de $" << notas_tipo[i];
    }
}

void nova_opr() {
    char opcao;
    cout << "\nDigite S se quiser fazer mais uma operação? ";
    cin >> opcao;

    if (opcao == 'S' || opcao == 's') {
        system("CLS");
    } else {
        cout << "Obrigado por utilizar nossos serviços. Até logo!" << endl;
        exit(0);
    }

    cin.ignore(); // Limpar o buffer de entrada
}

void Ent_depst(Notas &estq, int &balanco) {
    int aux;
    for (int i = 0; i < n; i++) {
        do {
            cout << "Você quer depositar quantas notas de $" << notas_tipo[i] << ": ";
            cin >> aux;

            if (aux < 0) {
                cout << "Valor inválido. Digite novamente.\n" << endl;
            }
        } while (aux < 0);
        estq.notas[i] += aux;
        balanco += (aux * notas_tipo[i]);
    }
    for (int i = 0; i < n; i++) {
        cout << "\nNotas total de " << notas_tipo[i] << ": " << estq.notas[i];
    }
}

void conf_saque(Notas &estq, int balanco, int saque) {
    if (saque <= 0) {
        cout << "Valor inválido. Digite novamente." << endl;
    } else if (saque > balanco) {
        cout << "Você não possui saldo suficiente. O máximo que você pode retirar é $" << balanco << endl;
    } else if (balanco < 100) {
        cout << "Você tem menos de R$100, por favor deposite mais" << endl;
    } else {
        Ent_saque(estq, saque);
    }
}

void Ent_saque(Notas &estq, int saque) {
    int aux;
    for (int i = 0; i < n; i++) {
        if (estq.notas[i] > 0) {
            aux = saque / notas_tipo[i];
            saque = saque % notas_tipo[i];
            estq.notas[i] -= aux;

            for (int e = 0; e < aux; e++) {
                if (estq.notas[i] < 0) {
                    estq.notas[i]++;
                    saque += notas_tipo[i];
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "\nNotas total de " << notas_tipo[i] << ": " << estq.notas[i];
    }
}

void Saida_balanco(int balanco) {
    cout << "\nSeu balanço atual é: $" << balanco;
}

void cadastrar_admin(Notas &estq) {
    string login, senha;

    do {
        cout << "\nCADASTRO: \nLOGIN: ";
        cin >> login;
        cout << "SENHA: ";
        cin >> senha;

        if (login == "AdminSovietico" && senha == "******") {
            menu_admin(estq);
            break;
        }
        cout << "Login ou senha incorreta. Digite novamente." << endl;
    } while (login != "AdminSovietico" && senha != "******");
}

void menu_admin(Notas &estq) {
    int op;

    do {
        cout << "Bem vindo!" << endl;
        cout << "\n---------------MENU---------------";
        cout << "\n|1.Checar balanço do caixa       |";
        cout << "\n|2.Depositar mais notas no caixa |";
        cout << "\n|3.Sair                          |";
        cout << "\n----------------------------------";
        cout << "\nPor favor, escolha uma opção: ";
        cin >> op;

        switch (op) {
            case 1:
                bal_caixa(estq);
                nova_opr();
                break;
            case 2:
                depst_caixa(estq);
                nova_opr();
                break;
            default:
                if (op < 1 || op > 3) {
                    cout << "Opção inválida. Por favor digite novamente." << endl;
                    break;
                }
        }
    } while (op != 3);
}

void bal_caixa(Notas &estq) {
    int balanco = 0;
    for (int i = 0; i < n; i++) {
        balanco += (estq.notas[i] * notas_tipo[i]);
    }
    cout << "\nO balanço atual do caixa é: " << balanco << endl;

    for (int i = 0; i < n; i++) {
        cout << "\nNotas total de " << notas_tipo[i] << ": " << estq.notas[i];
    }
}

void depst_caixa(Notas &estq) {
    int aux;
    for (int i = 0; i < n; i++) {
        do {
            cout << "Você quer depositar quantas notas de $" << notas_tipo[i] << ": ";
            cin >> aux;

            if (aux < 0) {
                cout << "Valor inválido. Digite novamente." << endl;
            }
        } while (aux < 0);
        estq.notas[i] += aux;
    }
    cout << "\n\n";
    saida_depst_caixa(estq);
}

void saida_depst_caixa(Notas &estq) {
    for (int i = 0; i < n; i++) {
        cout << "TOTAL DE NOTAS DISPONÍVEIS DE R$" << notas_tipo[i] << ": " << estq.notas[i] << endl;
    }
}

void validacao_entr_dados(int &var, string str, string invalid) {
    bool valid = false;
    while (!valid) {
        cout << str;
        cin >> var;
        if (cin.fail()) {
            cout << invalid;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } else
            valid = true;
    }
}

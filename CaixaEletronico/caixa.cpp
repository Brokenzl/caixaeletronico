#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

class CaixaEletronico {
private:
    double saldo;

public:
    // Construtor da classe, inicializa o saldo como zero.
    CaixaEletronico() {
        saldo = 0.0;
    }

    // Retorna o saldo atual da conta.
    double getSaldo() const {
        return saldo;
    }

    // Exibe o saldo atual da conta na tela.
    void exibirSaldo() const {
        cout << "Saldo atual: R$" << fixed << setprecision(2) << saldo << endl;
    }

    // Permite depositar um valor na conta.
    void depositar(double valor) {
        if (valor > 0) {
            saldo += valor;
            cout << "Depósito de R$" << fixed << setprecision(2) << valor << " realizado com sucesso." << endl;
        } else {
            cout << "Valor inválido para depósito." << endl;
        }
    }

    // Permite sacar um valor da conta, desde que seja válido.
    bool sacar(double valor) {
        if (valor > 0 && saldo >= valor) {
            saldo -= valor;
            cout << "Saque de R$" << fixed << setprecision(2) << valor << " realizado com sucesso." << endl;
            return true;
        } else if (valor <= 0) {
            cout << "Valor de saque inválido. Digite um valor positivo." << endl;
        } else {
            cout << "Saldo insuficiente. Saldo atual: R$" << fixed << setprecision(2) << saldo << endl;
        }
        return false;
    }
};

int main() {
    CaixaEletronico caixa;

    int opcao;
    double valor;

    cout << "Bem-vindo ao Simulador de Caixa Eletrônico!" << endl;

    do {
        cout << "\nEscolha uma opção:" << endl;
        cout << "1. Exibir saldo" << endl;
        cout << "2. Depositar" << endl;
        cout << "3. Sacar" << endl;
        cout << "4. Sair" << endl;
        cout << "Opção: ";

        // Lê a opção escolhida pelo usuário e verifica se é um número válido.
        while (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Digite um número válido: ";
        }

        switch (opcao) {
            case 1:
                // Exibe o saldo da conta.
                caixa.exibirSaldo();
                break;

            case 2:
                cout << "Digite o valor a ser depositado: R$";
                // Lê o valor do depósito e verifica se é válido.
                while (!(cin >> valor) || valor <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Valor inválido. Digite um valor positivo: R$";
                }
                // Realiza o depósito.
                caixa.depositar(valor);
                break;

            case 3:
                cout << "Digite o valor a ser sacado: R$";
                // Lê o valor do saque e verifica se é válido.
                while (!(cin >> valor) || valor <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Valor inválido. Digite um valor positivo: R$";
                }
                // Tenta realizar o saque e exibe uma mensagem de sucesso ou erro.
                if (caixa.sacar(valor)) {
                    cout << "Saque realizado com sucesso." << endl;
                }
                break;

            case 4:
                cout << "Saindo do programa." << endl;
                break;

            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 4);

    return 0;
}

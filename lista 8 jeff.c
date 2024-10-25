#include <stdio.h>
#include <time.h>

// Estrutura para representar uma data
struct Data {
    int dia;
    int mes;
    int ano;
};

// Função que verifica se um ano é bissexto
int is_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Função que retorna o número de dias em um mês
int dias_no_mes(int mes, int ano) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return is_bissexto(ano) ? 29 : 28;
        default:
            return 0; // Mês inválido
    }
}

// Função que calcula os dias de vida
int dias_de_vida(struct Data nasc) {
    time_t now = time(NULL);
    struct tm *data_atual = localtime(&now);

    int dias_vividos = 0;

    // Adiciona os dias do ano de nascimento
    if (nasc.ano == data_atual->tm_year + 1900) {
        dias_vividos += data_atual->tm_mday - nasc.dia; // se for o mesmo ano
        for (int m = nasc.mes + 1; m <= 12; m++) {
            dias_vividos += dias_no_mes(m, nasc.ano);
        }
    } else {
        for (int m = nasc.mes; m <= 12; m++) {
            if (m == nasc.mes) {
                dias_vividos += dias_no_mes(m, nasc.ano) - nasc.dia; // dias restantes no mês
            } else {
                dias_vividos += dias_no_mes(m, nasc.ano);
            }
        }

        // Adiciona os dias dos anos completos
        for (int a = nasc.ano + 1; a < data_atual->tm_year + 1900; a++) {
            dias_vividos += is_bissexto(a) ? 366 : 365;
        }

        // Adiciona os dias do ano atual
        for (int m = 1; m <= data_atual->tm_mon + 1; m++) {
            if (m == data_atual->tm_mon + 1) {
                dias_vividos += data_atual->tm_mday; // dias até hoje no mês atual
            } else {
                dias_vividos += dias_no_mes(m, data_atual->tm_year + 1900);
            }
        }
    }

    return dias_vividos;
}

// Função principal para testes
int main() {
    struct Data nascimento;

    printf("Digite sua data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &nascimento.dia, &nascimento.mes, &nascimento.ano);

    // Verifica se a data de nascimento é válida
    if (nascimento.mes < 1 || nascimento.mes > 12 || 
        nascimento.dia < 1 || nascimento.dia > dias_no_mes(nascimento.mes, nascimento.ano)) {
        printf("Data de nascimento inválida.\n");
        return 1;
    }

    int dias = dias_de_vida(nascimento);
    printf("Você viveu %d dias.\n", dias);

    return 0;
}

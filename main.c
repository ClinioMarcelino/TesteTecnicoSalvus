#include <stdio.h>
#include <stdlib.h>
#define VERMELHO     "\x1b[31m"
#define RESET       "\x1b[0m"

/*
============================================================
    ESTRUTURAS
============================================================
*/
typedef struct CLt{
    float salario;
}Clt;

typedef struct Terceirizado{
    float salarioPorHora;
    unsigned short nHorastrabalhadas;
}Terceirizado;

// Union para utliziar a estrutura Clt ou a Terceirizada
typedef union {
    Clt clt;
    Terceirizado terceirizado;
}TipoFuncionario;

typedef struct{
    char nome[30];
    _Bool isCLT; // se true/1 o funcionario é CLT, caso false/0 é Terceirizado
    TipoFuncionario tipoFuncionario;
    float comissaoPorContrato;
    unsigned short nContratosAssinados;
}Funcionario;

/*
============================================================
    PROTOTIPOS DAS FUNCOES
============================================================
*/
float (*CalcularPgmt)(Funcionario *funcionario);
void CadastrarInformacoesFuncionario(Funcionario *funcionario);
float CalcularPagamentoFuncionario(Funcionario *funcionario);
float CalcularFolhadePagamento(Funcionario funcionarios[],unsigned short nFuncionarios, float (*CalcularPgmt)(Funcionario*));

/*
============================================================
    MAIN
============================================================
*/

int main(){
    unsigned short nFuncionarios = 1;
    printf("Digite para quantos funcionarios deseja realizar os calculos:");
    scanf("%hu",&nFuncionarios);

    Funcionario funcionarios[nFuncionarios];

    CalcularPgmt = CalcularPagamentoFuncionario;
    
    unsigned short contador = 0;
    // Cadastro dos funcionarios
    do{
        CadastrarInformacoesFuncionario(&funcionarios[contador]);
    }while(++contador<nFuncionarios);

    // Calculo e impressao dos totais individuais
    for(int i=0;i<nFuncionarios;i++){
        printf("Nome: %s.",funcionarios[i].nome);
        printf("\tTotal a receber = R$ %.2f\n", CalcularPgmt(&funcionarios[i]));
    }

    // Calculo de impressao do total da folha de pagamento
    printf("Total folha: R$ %.2f\n",CalcularFolhadePagamento(funcionarios, nFuncionarios, CalcularPgmt));

return 0;
}

/*
============================================================
    IMPLEMENTACAO DAS FUNCOES
============================================================
*/

// Cadastro de informacoes de Funcionarios, recebe o ponteiro da array de funcionarios e a posicao da array
void CadastrarInformacoesFuncionario(Funcionario *funcionario){
    printf("Cadastro funcionario:\n");
    printf("\tNome: ");
    scanf("%s",funcionario->nome);
    getchar();

    // Variavel auxiliar para verificar o input do usuario e posteriormente passar valor a variavel do funcionario
    short aux;
    // Loop so sera quebrado caso o usuario responda corretamente.
    while(1){
        printf("\tTipo de contrato:\n\t\t0 - Terceirizado\n\t\t1 - CLT:\n\t");
        scanf("%hu", &aux);
        if (aux == 0 || aux == 1)
           break;
        else
            printf("%sError: input invalido.%s\n",VERMELHO,RESET);;
    }
    funcionario->isCLT = aux;

    if(funcionario->isCLT){
        printf("\tQual o salario do funcionario: ");
        scanf("%f",&funcionario->tipoFuncionario.clt.salario);
    }
    else{
        printf("\tQual o salario por hora do funcionario: ");
        scanf("%f",&funcionario->tipoFuncionario.terceirizado.salarioPorHora);
        printf("\tQuantas horas o funcionario trabalhou: ");
        scanf("%hu",&funcionario->tipoFuncionario.terceirizado.nHorastrabalhadas);
    }

    printf("\tQual o valor da comissao por contrato do funcionario: ");
    scanf("%f",&funcionario->comissaoPorContrato);

    printf("\tQuantos contratos o funcionario assinou no mes: ");
    scanf("%hu",&funcionario->nContratosAssinados);

    printf("\n");

}

// Calcula e retorna o Total a receber do funcionario seja CLT ou Terceirizado. 
float CalcularPagamentoFuncionario(Funcionario *funcionario){
    // operacao ternaria para verificar se e Clt ou Tercerizado e calcular de acordo
    float aux = funcionario->isCLT ? funcionario->tipoFuncionario.clt.salario : 
        funcionario->tipoFuncionario.terceirizado.nHorastrabalhadas * funcionario->tipoFuncionario.terceirizado.salarioPorHora;
    return aux + (funcionario->comissaoPorContrato*funcionario->nContratosAssinados);
}

// Variavel totalFolha vai somando o pagamento de cada funcionario utilizando o function pointer de Calcular Pgmt e retorna o total da folha.
float CalcularFolhadePagamento(Funcionario funcionarios[], unsigned short nFuncionarios, float (*CalcularPgmt)(Funcionario*)){
    float totalFolha = 0;
    for(int i=0;i<nFuncionarios;i++){
        totalFolha += CalcularPgmt(&funcionarios[i]);
    }

    return totalFolha;
}

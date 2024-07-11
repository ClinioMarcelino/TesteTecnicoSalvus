#include <stdio.h>
#include <stdlib.h>
#define VERMELHO     "\x1b[31m"
#define RESET       "\x1b[0m"

/*
    Estruturas
*/
typedef struct Mes{
    unsigned short nContratosAssinados;
    unsigned short horasTrabalhadas;
}Mes;

typedef struct Funcionario{
    char nome[30];
    _Bool isCLT; // se true/1 o funcionario é CLT, caso false/0 é Terceirizado
    float salarioBase;
    float comissaoPorContrato;
    Mes mes; // Possibilidade de implementacao de array de Mes para sistema com arquivo para acompanhamento dos meses
}Funcionario;

/*
    Prototipos das funcoes
*/
void CadastrarInformacoesFuncionario(Funcionario *funcionario);
float CalcularPagamentoFuncionario(Funcionario funcionario);
float CalcularFolhadePagamento(Funcionario funcionarios[],unsigned short nFuncionarios);

int main(){
    unsigned short nFuncionarios = 1;
    printf("Digite para quantos funcionarios deseja realizar os calculos:");
    scanf("%hu",&nFuncionarios);

    Funcionario funcionarios[nFuncionarios];
    
    unsigned short contador = 0;
    do{
        CadastrarInformacoesFuncionario(&funcionarios[contador]);
    }while(++contador<nFuncionarios);

    for(int i=0;i<nFuncionarios;i++){
        printf("Nome: %s.",funcionarios[i].nome);
        printf("\tTotal a receber = R$ %.2f\n", CalcularPagamentoFuncionario(funcionarios[i]));
    }

    printf("Total folha: R$ %.2f\n",CalcularFolhadePagamento(funcionarios,nFuncionarios));

return 0;
}

/*
    Implementacao das Funcoes
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


    printf("\tQual o salario do funcionario: ");
    scanf("%f",&funcionario->salarioBase);

    printf("\tQual o valor da comissao por contrato do funcionario: ");
    scanf("%f",&funcionario->comissaoPorContrato);

    printf("\tQuantos contratos o funcionario assinou no mes: ");
    scanf("%hu",&funcionario->mes.nContratosAssinados);

    // Caso o funcionario nao seja CLT pergnta e cadastra o numero de horas trabalhadas no mes
    if (!funcionario->isCLT){
        printf("\tQuantas horas o funcionario trabalhou: ");
        scanf("%hu",&funcionario->mes.horasTrabalhadas);

    }
    // Se o funcioanrio for CLT o "numero de horas trabalhadas": 1. Nao interfere na base de calculo do salario mensal  
    else
        funcionario->mes.horasTrabalhadas = 1;

    printf("\n");

}

// Calcula e retorna o Total a receber do funcionario seja CLT ou Terceirizado. 
// Comissao por contrato e nContratos assinados funciona igual para ambos.
// SalarioBase do CLT: valor total mensal que multiplica por 1. 
// Terceirizados tem o SalarioBase como o valor por hora e multiplica pela quantidade de horas trabalhadas no mes.
float CalcularPagamentoFuncionario(Funcionario funcionario){
    return(funcionario.salarioBase*funcionario.mes.horasTrabalhadas) + 
    (funcionario.comissaoPorContrato*funcionario.mes.nContratosAssinados);
}

// Variavel totalFolha vai somando o pagamento de cada funcionario utilizando CalcularPagamentoFuncionario() e retorna o total da folha.
float CalcularFolhadePagamento(Funcionario funcionarios[],unsigned short nFuncionarios){
    float totalFolha = 0;
    for(int i=0;i<nFuncionarios;i++){
        totalFolha += CalcularPagamentoFuncionario(funcionarios[i]);
    }

    return totalFolha;
}

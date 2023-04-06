#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//-------------------------------------------------------ESTRUTURAS-----------------------------------------------------------//
struct clientes{
    char nomeCompleto[100];
    char cpf[100];
    char telefone[100];
};

struct produto{
    int numero_quarto;
    double preco;
    int reservado;
};

struct reserva{
    struct clientes cliente;
    struct produto quarto;
    double valor;
};

struct repositorio_quartos{
    struct produto dormitorio[100];
    int proximoQuarto;
};

struct repositorio_clientes{
    struct clientes lista_clientes[100];
    int prox_cliente_disponivel;

};

struct repositorio_clientes repo_clientes;

struct repositorio_quartos repo_quartos;

struct reserva repo_reserva[100];
int proxima_reserva;

//-------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------VOIDS----------------------------------------------------------------//
void criar_cliente(char *nome, char *cpf, char *telefone){
    struct clientes cliente;



    strcpy(cliente.nomeCompleto, nome);
    strcpy(cliente.cpf, cpf);                                               //incrementando cliente para salvar na proxima posicao de repo_clientes.
    strcpy(cliente.telefone, telefone);
    repo_clientes.lista_clientes[repo_clientes.prox_cliente_disponivel] = cliente;
    repo_clientes.prox_cliente_disponivel++;
}

void criar_quarto(){
    int i;

    for(i=0; i<100; i++){

    if(repo_quartos.proximoQuarto == 0){
        repo_quartos.dormitorio[repo_quartos.proximoQuarto].numero_quarto = 1;
     }
     if(repo_quartos.proximoQuarto != 0){
        repo_quartos.dormitorio[repo_quartos.proximoQuarto].numero_quarto = repo_quartos.dormitorio[repo_quartos.proximoQuarto - 1].numero_quarto + 1;
     }


     repo_quartos.dormitorio[repo_quartos.proximoQuarto].preco = 250.0;
     repo_quartos.dormitorio[repo_quartos.proximoQuarto].reservado = 0;
     repo_quartos.proximoQuarto++;
    }


}

void visualizar_quartos_disponiveis(){
    int i;

    for(i=0; i<100; i++){

        if(repo_quartos.dormitorio[i].reservado == 0){
            printf("Numero do quarto: %d, preco: %.2lf\n",repo_quartos.dormitorio[i].numero_quarto, repo_quartos.dormitorio[i].preco );
        }

    }

}

void criar_reserva(char* cpf, int numeroQuarto ){

    int i;
    int j;
   for(j=0; j<100; j++){

        if(strcmp(repo_clientes.lista_clientes[j].cpf, cpf) == 0){
            for(i=0; i<100; i++){

                if(repo_quartos.dormitorio[i].numero_quarto == numeroQuarto){

                       repo_reserva[proxima_reserva].cliente = repo_clientes.lista_clientes[j];
                       repo_reserva[proxima_reserva].quarto = repo_quartos.dormitorio[i];
                       repo_reserva[proxima_reserva].valor = repo_quartos.dormitorio[i].preco;
                       repo_quartos.dormitorio[i].reservado = 1;
                       proxima_reserva++;
                }
            }
        }
   }

}


void visualizar_reserva(){
    int i;

    for(i=0; i<100; i++){

        if(repo_quartos.dormitorio[i].reservado >= 1){
            printf("Numero do quarto: %d, preco %.2lf\n",repo_quartos.dormitorio[i].numero_quarto, repo_quartos.dormitorio[i].preco );
        }
   }

}


void visualizar_reserva_cliente(char* cpf){

    int i;

    for(i=0; i<100; i++){

        if(strcmp(repo_reserva[i].cliente.cpf, cpf)==0){
            printf("Numero do quarto: %d, preco %.2lf\n",repo_reserva[i].quarto.numero_quarto, repo_reserva[i].quarto.preco );

        }
   }

}



int procurarcliente(char* cpf, int proxima_posicao){
    int i;

    for(i=0; i<proxima_posicao; i++){

        if(strcmp(cpf,repo_clientes.lista_clientes[i].cpf)==0){

        return 1;
        }

    }


    return 0;
}



void remover_Reserva(){

    int i, k,y,continuar=1, quarto;
    char cpfApagavel[100];



        printf("\n\nPor meios de seguranca, por favor, digite novamente o seu CPF: \n");
        scanf("%s", cpfApagavel);
        system("cls");

    for(y =0; y < proxima_reserva; y++)
    {
        if(strcmp(repo_reserva[y].cliente.cpf, cpfApagavel) == 0){  //encontra a reserva que tem o mesmo cpf que deseja apagar

                printf("Este Cliente tem uma reserva ativa!\n");
                printf("\n<<<------------------------------------------>>>\n");
                printf("Caso deseje continuar, sua reserva sera apagada!\n");
                printf("\n1 - Continuar\n");
                printf("2 - Cancelar\n");
                scanf("%d", &continuar);
                printf("\n<<<------------------------------------------>>>\n");

            if(continuar == 1){ //caso opte por coninuar e apagar a reserva

                    quarto = repo_reserva[y].quarto.numero_quarto;
                    for(i=0; i < 100;i++){

                        if(quarto == repo_quartos.dormitorio[i].numero_quarto){ //verifica quarto por quarto ate achar o quarto com o numero do quarto o qual deseja remover a reserva
                                repo_quartos.dormitorio[i].reservado = 0;       //o quarto selecionado recebe 0 na variavel reservado, isto Ã©, ele agora esta disponivel e a reserva foi cancelada
                                printf("Reserva Apagada!\n");
                        }

                    }
                    proxima_reserva--; //diminui uma reserva pois uma foi apagada
            }

            else{
                printf("Retornando para a tela inicial\n");

            }

        }
    }

}

void editar_reserva(char* cpf, int numeroQuarto ){
    int i, k,y,j, continuar=1, quarto;
    char cpfApagavel[100];
    printf("CPF's cadastrados ate agora:\n\n");

    for(i=0; i < repo_clientes.prox_cliente_disponivel; i++){

        printf("Sr/Sra: %s de cpf:  %s.", repo_clientes.lista_clientes[i].nomeCompleto, repo_clientes.lista_clientes[i].cpf);
      }
        printf("\n\nPor meios de seguranca, por favor, digite novamente o seu CPF: \n");
        scanf("%s", cpfApagavel);
        system("cls");

    for(y =0; y < proxima_reserva; y++)
    {
        if(strcmp(repo_reserva[y].cliente.cpf, cpfApagavel) == 0){

                printf("\n<<<------------------------------------------>>>\n");
                printf("Deseja continuar?\n");
                printf("\n1 - Continuar\n");
                printf("2 - Cancelar\n");
                scanf("%d", &continuar);
                printf("\n<<<------------------------------------------>>>\n\n");

            if(continuar == 1){

                    quarto = repo_reserva[y].quarto.numero_quarto;
                    for(i=0; i < 100;i++){

                        if(quarto == repo_quartos.dormitorio[i].numero_quarto){
                                repo_quartos.dormitorio[i].reservado = 0;
                        }

                    }
                    proxima_reserva--;
            }
            else{
                printf("Retornando para a tela inicial\n");

            }

        }
    }
    for(j=0; j<100; j++){

        if(strcmp(repo_clientes.lista_clientes[j].cpf, cpf) == 0){
            for(i=0; i<100; i++){

                if(repo_quartos.dormitorio[i].numero_quarto == numeroQuarto){

                       repo_reserva[proxima_reserva].cliente = repo_clientes.lista_clientes[j];
                       repo_reserva[proxima_reserva].quarto = repo_quartos.dormitorio[i];
                       repo_reserva[proxima_reserva].valor = repo_quartos.dormitorio[i].preco;
                       repo_quartos.dormitorio[i].reservado = 1;
                       printf("\tRESERVA TROCADA COM SUCESSO!\n");
                       proxima_reserva++;
                }
            }
        }
   }
}



struct produto quartos;
//--------------------------------------------------------------------------------------------------------------------------//

int main()
{

    proxima_reserva = 0;
    criar_quarto();
    repo_clientes.prox_cliente_disponivel = 0;
    repo_quartos.proximoQuarto = 0;
    int entrada;
    struct produto quartos;
    quartos.preco = 250.0;
    quartos.reservado = 0;                             //Nenhum quarto reservado ainda
    struct repositorio_quartos repositorio;
    int i;
    char nome[100];
    char cpf[100];
    char telefone[100];
    int Nquarto;

    for(i = 0; i < 100; i++){
        quartos.numero_quarto = i + 1;              //quarto tem que comecar do 1, nao faz sentido quarto 0
        repositorio.dormitorio[i] = quartos;        // mandar os quartos pra dentro do repositorio
    }

    int opcao, opcao2,editar_ordem_reserva, criar_ordem_reserva, remover_ordem;
    char continuar[10];

    do{


        printf("<<<--------------Bem vindo ao Hotel Hirata!-------------->>>\n\n");
        printf("1- ---------- Visualizar quartos disponiveis.\n");
        printf("2- ---------- Visualizar reservas.\n");
        printf("3- ---------- Reservar quarto.\n");
        printf("4- ---------- Editar pedido.\n");
        printf("5- ---------- Remover pedido.\n");
        printf("6- ---------- extras(Desenvolvedores)\n");
        printf("7- ---------- Sair\n");
        printf("<<<------------------------------------------------------>>>\n");

        printf("\nEscolha uma opcao:\n");
        scanf("%d", &opcao);

        if(opcao == 1){
            system("cls");
            printf("\n<<<------------------------------------------>>>\n");
            visualizar_quartos_disponiveis();
            printf("\n<<<------------------------------------------>>>\n");


        }
        if(opcao == 2){
            system("cls");
            printf("Todos os quartos reservados: ");
            printf("\n<<<------------------------------------------>>>\n\n");
            visualizar_reserva();
            printf("\n<<<------------------------------------------>>>\n");
            system("pause");
            system("cls");

        }

        if(opcao == 3){

            printf("Voce ja tem cadastro? [0 - Nao/ 1 - Sim]\n");
            scanf("%d", &entrada);

            if (entrada == 1)
            {
                printf("\n<<<------------------------------------------>>>\n");
                printf("Digite seu CPF para verificarmos seu cadastro: \n");
                getchar();
                scanf("%[^\n]", cpf);

                if(procurarcliente(cpf, repo_clientes.prox_cliente_disponivel)==0){

                    printf("CPF invalido\n");
                    printf("\n<<<------------------------------------------>>>\n");
                    system("pause");
                    system("cls");
                }

                else{
                printf("INFORMACOES VALIDADAS COM SUCESSO!");
                printf("\n<<<------------------------------------------>>>\n");

                printf("Digite o numero do quarto: ");
                scanf("%d", &Nquarto);
               criar_reserva(cpf, Nquarto);
                printf("\n<<<------------------------------------------>>>\n");
                printf("\tQUARTO RESERVADO COM SUCESSO!\n");
                printf("\n<<<------------------------------------------>>>\n");
                system("pause");
                system("cls");
                }

            }
            else{
                system("cls");
                printf("\n<<<------------------------------------------>>>\n");
                printf("\nVamos lhe cadastrar agora!\n");
                printf("Digite o seu nome: ");
                getchar();
                scanf(" %[^\n]", nome);
                printf("Digite o seu cpf: ");
                getchar();
                scanf(" %[^\n]", cpf);
                printf("Digite o seu telefone: ");
                getchar();
                scanf(" %[^\n]", telefone);
                criar_cliente(nome, cpf, telefone);

                printf("\n<<<------------------------------------------>>>\n");
                printf("\t  CADASTRO REALIZADO!\n");
                printf("\n<<<------------------------------------------>>>\n");

                printf("\nAgora podemos ir para a reserva.\n");
                printf("Digite o numero do quarto: ");
                scanf("%d", &Nquarto);
               criar_reserva(cpf, Nquarto);
                printf("\n<<<------------------------------------------>>>\n");
                printf("\tQUARTO RESERVADO COM SUCESSO!\n");
                printf("\n<<<------------------------------------------>>>\n");
                system("pause");
                system("cls");

            }

        }
        if(opcao == 4){
            system("cls");
            printf("Todos os quartos reservados: ");
            printf("\n<<<------------------------------------------>>>\n");
            visualizar_reserva();
            printf("\n<<<------------------------------------------>>>\n");
            printf("Digite seu CPF para verificarmos seu cadastro: \n");
                getchar();
                scanf("%[^\n]", cpf);

                if(procurarcliente(cpf, repo_clientes.prox_cliente_disponivel)==0){

                    printf("CPF invalido\n");
                    printf("<<<------------------------------------------>>>\n");
                    system("pause");
                    system("cls");
                    
                }



                else{
                printf("\n<<<------------------------------------------>>>\n");
                printf("\tINFORMACOES VALIDADAS COM SUCESSO!");
                printf("\n<<<------------------------------------------>>>\n");



                printf("Digite o numero do quarto que voce deseja agora para trocarmos: ");
                scanf("%d", &Nquarto);
                editar_reserva(cpf, Nquarto);

                printf("\n<<<------------------------------------------>>>\n");
                system("pause");
                system("cls");
                }

        }
         if(opcao == 5){
            system("cls");
            printf("Todos os quartos reservados: ");
            printf("\n<<<------------------------------------------>>>\n");
            visualizar_reserva();
            printf("\n<<<------------------------------------------>>>\n");

            printf("Digite seu CPF:\n");
            getchar();
            scanf("%[^\n]", cpf);

            if(procurarcliente(cpf, repo_clientes.prox_cliente_disponivel)==0){

                printf("CPF invalido\n");
                printf("<<<------------------------------------------>>>\n");
                system("pause");
                
            }
            remover_Reserva();
            printf("<<<------------------------------------------>>>\n");
            system("cls");

        }
        if(opcao == 6){
            system("cls");
            printf("\n");
            printf("  ______________________________________________ \n");
            printf(" |                                              |\n");
            printf(" | Primeiro Mini-Projeto em C                   |\n");
            printf(" | Prof. Dr. Luis Filipe Alves Pereira          |\n");
            printf(" |----------------------------------------------|\n");
            printf(" |                                              |\n");
            printf(" |  Aluno1: Claudierio Baltazar Barra Nova      |\n");
            printf(" |  Aluno2: Filipe Alencar Andrade Amorim Gomes |\n");
            printf(" |______________________________________________|\n\n");
            system("pause");
            system("cls");
        }

    }while(opcao != 7);

    printf("Esperamos que nossos servicos tenham lhe atendido. Ate mais!\n");
    printf("\n<<<--------------------------------------------------------->>>\n");

    system("pause");

    return 0;
}
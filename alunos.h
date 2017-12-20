#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>

int mat = 100;
//Estrutura para o cadastro de alunos
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[11];
} CAD_ALUNOS;
//Fun��o para gravar registro de funcion�rios.

void verificadorArquivo(FILE* arquivo);

void cadastrar() {
    system("cls");
    FILE* arquivo; //FILE (sempre maiuscula), vari�vel do tipo file (arquivo � o nome do ponteiro), nesta linha est� sendo criado o ponteiro
    CAD_ALUNOS al;
    arquivo = fopen ("cad_alunos.txt", "ab");// "ab" acrescenta dados bin�rios no fim do arquivo e se o arquivo n�o existir ele ser� criado e
    //e fopen � respons�vel fazer com que o ponteiro aponte para um arquivo no programa
    verificadorArquivo(arquivo);
    char op;

    do {
        system("cls");
        fflush(stdin);
        menuCIMA(strlen("Matricula do Aluno: ")+10);
        menuOPCAO("Matricula do Aluno: ", strlen("Matricula do Aluno: ")+10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Matricula do Aluno: ")+10);
        gotoXY(22, 1);
        scanf("%d", &al.matricula);
        system("cls");
        fflush(stdin);
        menuCIMA(strlen("Digite o Nome do Aluno: ")+50);
        menuOPCAO("Digite o Nome do Aluno: ", strlen("Digite o Nome do Aluno: ")+50);
        gotoXY(0, 2);
        menuBAIXO(strlen("Digite o Nome do Aluno: ")+50);
        gotoXY(26, 1);
        gets(al.nome);
        strupr(al.nome); //Converte o conte�do digitado em mai�sculo.
        fflush(stdin);
        system("cls");
        menuCIMA(strlen("Digite o CPF do Aluno: ")+15);
        menuOPCAO("Digite o CPF do Aluno: ", strlen("Digite o CPF do Aluno: ")+15);
        gotoXY(0, 2);
        menuBAIXO(strlen("Digite o CPF do Aluno: ")+15);
        gotoXY(25, 1);
        gets(al.cpf);
        strupr(al.cpf);//Converte o conte�do digitado em mai�sculo.
        fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
        //SIZEOF passa para a fun��o o tamanho em bytes da struct
        system("cls");
        menuCIMA(strlen("Registro gravado com sucesso!"));
        menuOPCAO("\nRegistro gravado com sucesso!\n", strlen("Registro gravado com sucesso!"));
        gotoXY(0, 2);
        menuBAIXO(strlen("Registro gravado com sucesso!"));
        gotoXY(22, 1);
        system("cls");
        menuCIMA(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
        menuOPCAO("Deseja Continuar e Inserir um Novo Registro (S/N)?  ", strlen("Deseja Continuar e Inserir um Novo Registro (S/N)? "));
        gotoXY(0, 2);
        menuBAIXO(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 4);
        setbuf(stdin, NULL);
        op = getchar();
        op = toupper(op);
        system("cls");
        while(op != 'S' && op != 'N') {
            system("cls");
            menuCIMA(strlen("Opcao invalida, digite novamente!"));
            menuOPCAO("Opcao invalida, digite novamente!", strlen("Opcao invalida, digite novamente!"));
            gotoXY(0, 2);
            menuBAIXO(strlen("Opcao invalida, digite novamente!"));
            gotoXY(22, 1);
            printf("\n\n");
            system("pause");
            system("cls");
            menuCIMA(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
            menuOPCAO("Deseja Continuar e Inserir um Novo Registro (S/N)?  ", strlen("Deseja Continuar e Inserir um Novo Registro (S/N)? "));
            gotoXY(0, 2);
            menuBAIXO(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
            menuCIMA(10);
            menuOPCAO(" OPCAO: ", 10);
            menuBAIXO(10);
            gotoXY(10, 4);
            setbuf(stdin, NULL);
            op = getchar();
            op = toupper(op);
            system("cls");
        }
    } while(op == 'S');

    fclose(arquivo); //Fecha o arquivo que foi aberto.
    system("cls");
}

void listarAlunos() {

    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    verificadorArquivo(arquivo);
    printf("\n---------------LISTAGEM DE ALUNOS-------------\n\n");
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        printf("\nMatricula: %d\n", al.matricula);
        printf("\nNome: %s\n", al.nome);
        printf("\nCPF: %s\n\n", al.cpf);
        system("pause");

    }

    printf("\n--------------- FIM DA LISTAGEM DE ALUNOS-------------\n\n");
    system("pause");
    system("cls");
}
void editar () {
    int op=0;

    printf("---------PROCURAR ALUNO PARA EDITAR-----------");
    do {
        printf("\n1 - Procurar Por CPF ");
        printf("\n2 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            pnome();
            break;
        case 2:
            printf("Saindo...\n");
            Sleep(1000);
            break;
        default:
            printf("\nOpcao invalida\n");
            break;
        }
    } while(op != 2);
}
pnome() {
    CAD_ALUNOS al;
    char aux[255];
    printf("\n---------------PROCURAR ALUNOS POR NOME-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo;
    //Abrindo o arquivo criado e dando o nome cad_alunos para o arquivo
    //O "a+" �  para abrir salvar no final, e ler os dados do arquivo
    arquivo = fopen("cad_alunos.txt", "rb");
    //verificando se o arquivo foi aberto com exito
    if(arquivo == NULL) {
        printf("Impossivel Abrir Aquivo!");
    }
    else {
        fflush(stdin);
        printf("\nDigite o nome que deseja procurar: ");
        gets(aux);

        while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo) == 1) {
            if(strstr(aux, al.nome)) {
                printf("editar nome: ");
            }
        }
    }
    printf("\n\n***************Fim da Edi��o.***************\n\n");
    system("pause");
    system("cls");
}

//Fun��o para verificar que op��o vai ser usada no menu aluno
void op_alunos () {
    int o = menuAluno();
    struct alunos al;
    while(o != 5) {
        system("cls");
        switch(o) {
        case 1:
            cadastrar();
            Sleep(1000);
        case 2:
            break;
        case 3:
            editar();
            Sleep(1000);
            break;
        case 4:
            listarAlunos(al);
            Sleep(1000);
            break;
        case 5:
            Sleep(1000);
            return;
        default:
            printf("Op��o invalida\n");
            break;
        }
        fflush(stdin);
    }
}
void verificadorArquivo(FILE *arquivo) {
    if(arquivo == NULL) {
        system("cls");
        printf("Ocorreu um erro no sistema. Por favor contate o fabricante! \n\n\n\n");
        printf("Saindo do programa...");
        Sleep(2000);
        exit(1);
    }
}

int menuAluno() {
    int o;
    menuCIMA(40);
    printf(" %c                 ALUNOS                 %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - Cadastrar Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - Remover Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - Editar Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Listar Alunos Cadastrados", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 5 - Ir para menu anterior", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 15);
    scanf("%d", &o);
    return o;
}

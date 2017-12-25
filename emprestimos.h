#ifndef EMPRESTIMOS_H_INCLUDED
#define EMPRESTIMOS_H_INCLUDED
#endif // EMPRESTIMOS_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>
int codEmprestimo = 100;

//Estrutura para o cadastro de alunos
typedef struct emprestimos {
    int cod_livro;
    int cod_emprestimo;
    int matricula_aluno;
    char nome_livro[50];
    char nome_aluno[50];
    int dia_em;
    int mes_em;
    int ano_em;
    int diadev;
    int mesdev;
    int anodev;
}CAD_EMP;

typedef struct {
	int dia;
	int mes;
	int ano;
}DAT;

void p_data(char str[9], DAT *Alvo){
	char _dia[3] = {
		str[3],
		str[4],
		0
	};
	char _mes[3] = {
		str[0],
		str[1],
		0
	};
	char _ano[3] = {
		str[6],
		str[7],
		0
	};
	Alvo->dia = atoi(_dia);
	Alvo->mes = atoi(_mes);
	Alvo->ano = atoi(_ano);
}

int contadorCodEm() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    if(arquivo == NULL) {
        printf("\nProblemas na abertura do arquivo!\n");
    } else
        while(fread(&em, sizeof(CAD_EMP), 1,arquivo) == 1){
            if(&(em.cod_emprestimo) != NULL){
                aux++;
            }
        }
    fclose(arquivo);
    return aux;
}

int veri_cpf(int cod){
    int i=0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    CAD_ALUNOS al;

    while(fread(&al,sizeof(CAD_ALUNOS), 1, arquivo)==1){
        if(cod == al.matricula){
            break;
            return 1;
        }
    }
}

void cadastrarEmprestimos() {
    system("cls");
    char dataatual[9];
    // pega a data atual
	_strdate( dataatual);
	DAT atual;
	p_data(dataatual, &atual);
	int ano = atual.ano;
	int dia = atual.dia;
	int mes = atual.mes;
    int cod=0, aux=0, x=0, i=0;
    FILE *arquivo;
    FILE *livro;
    FILE *aluno; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
    CAD_EMP em;
    CAD_LIVROS li;
    CAD_ALUNOS al;
    arquivo = fopen ("emprestimos", "a+b");// "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
    livro = fopen("cad_livros.txt", "r+b");
    aluno = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    verificadorArquivo(livro);
    verificadorArquivo(aluno);
    menuCIMA(40);
    menuOPCAO("     REALIZANDO EMPRESTIMO      ", 40);
    menuBAIXO(40);
    char op;
        printf("\nDigite o codigo do livro que deseja realizar o emprestimo!\n");
        scanf("%d", &cod);
        while(fread(&li, sizeof(CAD_LIVROS), 1, livro)==1){
            aux++;
            if(cod == li.codigo){
                li.quantidade = li.quantidade - 1;
                if(li.quantidade < 0){
                    printf("Sem livro para emprestimo.\n");
                    system("pause");
                    return;
                }else{
                    fseek(livro,(aux-1)*sizeof(CAD_LIVROS),SEEK_SET);
                    fwrite(&li,sizeof(CAD_LIVROS), 1,livro);
                    }break;
                }
            }
        printf("\nDigite a Matricula do Aluno que deseja realizar o emprestimo!\n");
        scanf("%d", &cod);
        //continuar a fazer a busca para saber se os alunos tem o mesmo CPF
        x = veri_cpf(cod);
        if(x == 1){
            printf("\nMatricula Nao Existe\n");
            return;
        }else{
        while(fread(&al, sizeof(CAD_ALUNOS), 1, aluno)==1){
                x = al.matricula;
                if(cod == al.matricula){
                    em.matricula_aluno = al.matricula;
                    strcpy(em.nome_aluno, al.nome);
                    break;
                }
            }
        //Verificando se o aluno ja tem mais de 2 emprestimos
        while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1){
            if(cod == em.matricula_aluno){
                    i++;
                }
        }
        if(i >= 2){
            system("cls");
            printf("\nNao Foi Possivel Realizar o Emprestimo Aluno com Quantidade Maxima de Emprestimos\n");
            system("pause");
            return;
        }else{
            aux = contadorCodEm();
            system("cls");
            menuCIMA(40);
            printf(" %c                 DADOS DO EMPRESTIMO                 %c\n", 186, 186);
            menuOPCAO("", 40);
            menuOPCAO(" Codigo do Emprestimo", 40);
            codEmprestimo = codEmprestimo + aux;
            printf("%d", codEmprestimo);
            menuOPCAO("", 40);
            menuOPCAO(" Codigo do Livro", 40);
            printf("%d", li.codigo);
            menuOPCAO("", 40);
            menuOPCAO(" Nome do Livro", 40);
            printf("%s", strupr(li.nome_livro));
            menuOPCAO("", 40);
            menuOPCAO(" Matricula do Aluno", 40);
            printf("%d", em.matricula_aluno);
            menuOPCAO("", 40);
            menuOPCAO(" Nome do Aluno", 40);
            printf("%s", strupr(em.nome_aluno));
            menuOPCAO("", 40);
            menuOPCAO(" Data do Emprestimo", 40);
            printf("%d/%d/%d\n", dia, mes, ano);
                em.dia_em = dia;
                em.mes_em = mes;
                em.ano_em = ano;
            menuOPCAO("", 40);
            menuOPCAO(" Data da Devolucao do Emprestimo\n\n", 40);
            dia = dia+10;
            if(dia > 30){
                dia = dia%30;
                mes = mes + 1;
                if(mes > 12){
                    mes = 1;
                    ano = ano + 1;
                }
            }
            printf("%d/%d/%d\n\n\n", dia, mes, ano);
            menuOPCAO("", 40);
            menuBAIXO(40);
            gotoXY(10, 15);
            menuCIMA(40);
            menuOPCAO(" Emprestimo Salvo com Sucesso! ", 40);
            menuBAIXO(40);
            gotoXY(10, 15);

                em.cod_livro = li.codigo;
                strcpy(em.nome_livro, li.nome_livro);
                //em.matricula_aluno = al.matricula;
                //strcpy(em.nome_aluno, al.nome);
                em.diadev = dia;
                em.mesdev = mes;
                em.anodev = ano;
                em.cod_emprestimo = codEmprestimo;
                fwrite(&em, sizeof(CAD_EMP), 1, arquivo);
                }
    }

    fclose(arquivo); //Fecha o arquivo que foi aberto.
    fclose(livro);
    fclose(aluno);
    system("pause");
    system("cls");
}

void listartodos(){
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    verificadorArquivo(arquivo);
    menuCIMA(29);
    menuOPCAO("     LISTAGEM DE EMPRESTIMOS", 29);
    menuBAIXO(29);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        printf("\nCodigo do Emprestimo: %d\n", em.cod_emprestimo);
        printf("\nMatricula do Aluno: %d\n", em.matricula_aluno);
        printf("\nNome do Aluno: %s\n", em.nome_aluno);
        printf("\nCodigo do Livro: %d\n", em.cod_livro);
        printf("\nNome do Livro: %s\n", em.nome_livro);
        printf("\nData do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
        printf("\nData da Devolucao do Livro: %d/%d/%d\n", em.diadev, em.mesdev, em.anodev);
        printf("---------------------------------------------\n");
    }

    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DO EMPRESTIMOS    ", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
}

void listar_por_Alunos(){
    int aux;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    verificadorArquivo(arquivo);
    menuCIMA(40);
    menuOPCAO("     LISTAGEM DE EMPRESTIMOS POR ALUNO   ", 40);
    menuBAIXO(40);
    printf("\nDigite a Matricula do Aluno: ");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        if(aux == em.matricula_aluno){
            printf("\nMatricula do Aluno: %d\n", em.matricula_aluno);
            printf("\nNome do Aluno: %s\n", em.nome_aluno);
            printf("\nCodigo do Livro: %d\n", em.cod_livro);
            printf("\nNome do Livro: %s\n", em.nome_livro);
            printf("\nData do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
            printf("\nData da Devolucao do Livro: %d/%d/%d\n", em.diadev, em.mesdev, em.anodev);
            printf("---------------------------------------------\n");
        }
    }

    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE EMPRESTIMOS    ", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
}

void listar_por_livros(){
    int aux;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    verificadorArquivo(arquivo);
    menuCIMA(40);
    menuOPCAO("     LISTAGEM DE EMPRESTIMOS POR LIVRO   ", 40);
    menuBAIXO(40);
    printf("\nDigite o Codigo do Livro: ");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        if(aux == em.cod_livro){
            printf("\nMatricula do Aluno: %d\n", em.matricula_aluno);
            printf("\nNome do Aluno: %s\n", em.nome_aluno);
            printf("\nCodigo do Livro: %d\n", em.cod_livro);
            printf("\nNome do Livro: %s\n", em.nome_livro);
            printf("\nData do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
            printf("\nData da Devolucao do Livro: %d/%d/%d\n", em.diadev, em.mesdev, em.anodev);
            printf("---------------------------------------------\n");
        }
    }

    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE EMPRESTIMOS    ", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
}

void listar_emprestimos(){
    int op = 0;
    do {
        menuCIMA(29);
        menuOPCAO("     LISTAGEM DE EMPRESTIMOS     ", 29);
        menuOPCAO("", 29);
        menuOPCAO(" 1 - Listar Todos Emprestimos ", 29);
        menuOPCAO("", 29);
        menuOPCAO(" 2 - Listar Por Livro Especifico", 29);
        menuBAIXO(29);
        menuOPCAO(" 3 - Listar Por Aluno Especifico", 29);
        menuBAIXO(29);
        menuOPCAO(" 4 - Sair", 29);
        menuBAIXO(29);
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 8);
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            listartodos();
            break;
        case 2:
            listar_por_livros();
            break;
        case 3:
            listar_por_Alunos();
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("\nOpcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 4);
}

void devolucao(){
    int aux=0,j =0 ,i=0;
    char auxlivro[50];
    FILE *arquivo;
    FILE *livro;
    CAD_EMP em;
    CAD_LIVROS li;
    arquivo = fopen("emprestimos", "rb");
    livro = fopen("cad_livros.txt", "r+b");
    verificadorArquivo(arquivo);
    verificadorArquivo(livro);

    printf("Qual Codigo do Emprestimo que Deseja fazer a Devolucao\n");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1, arquivo)==1){
        if(aux == em.cod_emprestimo){
            j = em.cod_livro;
            break;
        }
    }
    while(fread(&li, sizeof(CAD_LIVROS), 1, livro)==1){
        i++;
        if(em.cod_livro == li.codigo){
            li.quantidade++;
            li.nome_autor[strlen(li.nome_autor) - 1] = '\0';
            li.nome_livro[strlen(li.nome_livro) - 1] = '\0';
            li.area[strlen(li.area) - 1] = '\0';
            fseek(livro,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
            if(fwrite(&li, sizeof(CAD_LIVROS), 1, livro) != 1){
                printf("\nFalha ao fazer devolucao!\n");
                system("pause");
                printf("\n\n%s\n\n", strerror(errno));

            }else{
                printf("\nDevolucao Feita com Sucesso!\n");
                system("pause");

            }
            break;
        }
    }



}

void excluirEmprestimo(){
    CAD_EMP em;
    int i = 0;
    int auxiliar;
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("emprestimos", "a+b");
    FILE *arq_auxiliar = fopen("auxiliar", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    }
    else {
        fflush(stdin);
        printf("\nDigite o Codigo do Emprestimo que deseja excluir: ");
        scanf("%d", &auxiliar);

        while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1) {
            i++;
            if(auxiliar == em.cod_emprestimo){
                fseek(arquivo,(i - 1) * sizeof(CAD_EMP),SEEK_SET);
            } else {
                fwrite(&em,sizeof(CAD_EMP), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        if(remove("emprestimos") == 0){
            rename("auxiliar", "emprestimos");
            printf("\n\n--------------- Emprestimo excluido com sucesso ---------------\n");
            system("pause");
        }else{
            printf("Nao foi Possivel Excluir o Emprestimo!\n");
            printf("\n\n%s\n\n", strerror(errno));
            system("pause");
        }
        system("cls");
    }
}

//Função para verificar que opção vai ser usada no menu aluno
void op_emprestimos () {
    int o=0;
    struct emprestimos em;
    do{
                printf("\n---------------EMPRESTIMOS-------------\n\n");
                printf("-\t 1 Novo Emprestimo\t\t\t-\n");
                printf("-\t 2 Confirma Devolucao\t\t\t-\n");
                printf("-\t 3 Cancelar Emprestimo\t\t\t-\n");
                printf("-\t 4 Listar Emprestimos\t\t\t-\n");
                printf("-\t 5 Ir para menu anterior\t\t\t-\n\n");
                scanf("%d", &o);
        system("cls");
        switch(o){
            case 1:
                cadastrarEmprestimos();
                Sleep(1000);
                break;
            case 2:
                devolucao();
                Sleep(1000);
                break;
            case 3:
                Sleep(1000);
                break;
            case 4:
                listar_emprestimos();
                Sleep(1000);
                break;
            case 5:
                return;
                Sleep(1000);
                break;
            default:
                printf("Opção invalida\n");break;
        }
        fflush(stdin);
    }
    while(o >= 5);
}


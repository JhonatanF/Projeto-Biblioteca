#include <stdio.h>
#include <windows.h>
#include <dos.h>

int mat = 100;
//Estrutura para o cadastro de alunos
void pnome();
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[11];
}CAD_ALUNOS;
//Fun��o para gravar registro de funcion�rios.
void cadastrar(){
	limpartela();
	FILE* arquivo; //FILE (sempre maiuscula), vari�vel do tipo file (arquivo � o nome do ponteiro), nesta linha est� sendo criado o ponteiro
	CAD_ALUNOS al;
	arquivo = fopen ("cad_alunos.txt", "ab");// "ab" acrescenta dados bin�rios no fim do arquivo e se o arquivo n�o existir ele ser� criado e
	                                     //e fopen � respons�vel fazer com que o ponteiro aponte para um arquivo no programa

	if (arquivo == NULL){
		printf("\nProblemas na abertura do arquivo!\n");
	}
	else{
		do{
            system("cls");
            fflush(stdin);
            printf("\nMatricula do Aluno: \n");
            scanf("%d", &al.matricula);
			fflush(stdin);
			printf("\nDigite o Nome do Aluno: \n");
			gets(al.nome);
			strupr(al.nome); //Converte o conte�do digitado em mai�sculo.
			fflush(stdin);
			printf("\nDigite o CPF do Aluno: \n");
			gets(al.cpf);
			strupr(al.cpf);//Converte o conte�do digitado em mai�sculo.
			fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
															//SIZEOF passa para a fun��o o tamanho em bytes da struct
			printf("\n\nRegistro gravado com sucesso!\n\n");
			printf("\nDeseja Continuar e Inserir um Novo Registro (S/N)?\n");
		}
		while(getche() == 's');
		fclose(arquivo); //Fecha o arquivo que foi aberto.
		}
    }
void listaralunos(){
    CAD_ALUNOS al;
    printf("\n---------------LISTAGEM DE ALUNOS-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo;
    //Abrindo o arquivo criado e dando o nome cad_alunos para o arquivo
    //O "a+" �  para abrir salvar no final, e ler os dados do arquivo
    arquivo = fopen("cad_alunos.txt", "rb");
    //verificando se o arquivo foi aberto com exito
    if(arquivo == NULL){
        printf("Impossivel Abrir Aquivo!");
    }
    else{
            while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1){
                printf("\nMatricula: %d", al.matricula);
                printf("\nNome: %s", al.nome);
                printf("\nCPF: %s", al.cpf);
                printf("\n-----------------------------------------------------------\n");
                system("pause");
                }
    }
    printf("\n\n***************Fim do relat�rio.***************\n\n");
	system("pause");
}
void editar (){
    int op=0;

    printf("---------PROCURAR ALUNO PARA EDITAR-----------");
    do{
        printf("\n1 - Procurar Por Nome ");
        printf("\n2 - Procurar Por Matricula ");
        printf("\n3 - Procurar Por CPF ");
        printf("\n4 - Sair");
        scanf("%d", &op);
        system("cls");
        switch(op){
            case 1:
                pnome();
                break;
            case 2:
                //pmatricula();
                break;
            case 3:
               // pcpf();
                break;
            case 4:
                printf("Saindo...\n");
                Sleep(1000);
                break;
            default:
                printf("\nOpcao invalida\n");
                break;
        }
    }while(op != 4);
}
void pnome(){
    CAD_ALUNOS al;
    char aux[255];
    printf("\n---------------PROCURAR ALUNOS POR NOME-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo;
    //Abrindo o arquivo criado e dando o nome cad_alunos para o arquivo
    //O "a+" �  para abrir salvar no final, e ler os dados do arquivo
    arquivo = fopen("cad_alunos.txt", "rb");
    //verificando se o arquivo foi aberto com exito
    if(arquivo == NULL){
        printf("Impossivel Abrir Aquivo!");
    }
    else{
            fflush(stdin);
            printf("\nDigite o nome que deseja procurar: ");
            gets(aux);

            while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1){
                 if(strstr(aux, al.nome)){
                        printf("editar nome: ");
                    }
                }
    }
    printf("\n\n***************Fim da Edi��o.***************\n\n");
	system("pause");


}
void pmatricula(){
}
void pcpf(){
}
//Fun��o para verificar que op��o vai ser usada no menu aluno
void op_alunos () {
    int o=0;
    struct alunos al;
    do{
                printf("\n---------------ALUNOS-------------\n\n");
                printf("-\t 1 Cadastrar Aluno\t\t\t-\n");
                printf("-\t 2 Remover Aluno\t\t\t-\n");
                printf("-\t 3 Editar Aluno\t\t\t-\n");
                printf("-\t 4 Listar Alunos Cadastrados\t\t\t-\n");
                printf("-\t 5 Ir para menu anterior\t\t\t-\n\n");
                scanf("%d", &o);
        switch(o){
            case 1:
                cadastrar();
                Sleep(1000);
            case 2:
                Sleep(1000);
                break;
            case 3:
                editar();
                Sleep(1000);
                break;
            case 4:
                listaralunos(al);
                Sleep(1000);
                break;
            case 5:
                Sleep(1000);
                menu_principal();
            default:
                printf("Op��o invalida\n");break;
        }
        fflush(stdin);
    }
    while(o >= 5);
}


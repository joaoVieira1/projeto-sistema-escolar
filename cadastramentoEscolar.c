//importações de bibliotecas 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//declarações de estruturas

typedef struct{
    char nome[40];
    char prontuario[20];
    int idade;
    float notas[4];
} Aluno;

//declaração de funções

void logar(char *senha[], char *login[]);
void confirmaAdm();
void entrarSistema(char *senha[], char *login[]);
int adminOuUser(char *login[]);
void menuAdmin(Aluno *alunos, int *ptr, int quant, char *senha[]);
void menuUser(Aluno *alunos, int *ptr, int quant);
void limparTela();
void timeout(int tempoMs);
void matricularAluno(Aluno *alunos, int *ptr);
void consultarAluno(Aluno *alunos, int quant);
void inserirNotas(Aluno *alunos, int quant);
void exibirAlunos(Aluno *alunos, int quant);
void desmatricularAluno(Aluno *alunos, int quant, char *senha[]);

//main 

int main(){
    char senha[20], login[20];
    int quantidadeAlunos, cont = 0;

    printf("##################################\n");
    printf("|                                |\n");
    printf("| SISTEMA DE CADASTROS ESCOLARES |\n");
    printf("|                                |\n");
    printf("##################################\n\n");

    logar(&senha, &login);

    printf("\n=-=-=-=-= BEM VINDO -=-=-=-=-=\n");
    
    printf("Quantidade maxima de matriculas: ");
    scanf("%d", &quantidadeAlunos);

    Aluno *alunos = (Aluno *)malloc(quantidadeAlunos * sizeof(Aluno));
    if (alunos == NULL) {
        fprintf(stderr, "Erro na alocacao de memoria.\n");
        return 1;
    }

    if(adminOuUser(login) == 1){
        menuAdmin(alunos, &cont, quantidadeAlunos, &senha);
    }else{
        menuUser(alunos, &cont, quantidadeAlunos);
    }

    free(alunos);

    printf("\n=-=-=-=-= SISTEMA ENCERRADO -=-=-=-=-=\n");

    return 0;
}

//implementação de funções

void logar(char *senha[], char *login[]){
    char confirmaSenha[20];
    char palavraChave[] = {"admin"};
    char *ponteiro;

    printf("#######################\n");
    printf("|     CADASTRE-SE     |\n");
    printf("#######################\n\n");

    printf("OBS: Para o registro de um administrador e necessario inserir 'admin' no login do usuario\n\n");
    printf("!Nao utilizar espacos!\n\n");

    printf("Login: ");
    scanf("%s", &*login);

    printf("Senha: ");
    scanf("%s", &*senha);

    printf("Confirme sua senha: ");
    scanf("%s", &confirmaSenha);
    
    limparTela();

    while(strcmp(senha, confirmaSenha) != 0){
        printf("Confirmacao de senha invalida, por favor, insira seus dados novamente!\n\n");

        printf("Login: ");
        scanf("%s", &*login);

        printf("Senha: ");
        scanf("%s", &*senha);

        printf("Confirme sua senha: ");
        scanf("%s", &confirmaSenha);

        limparTela();
    }

    ponteiro = strstr(login, palavraChave);

    if(ponteiro > 0){
        confirmaAdm();
        entrarSistema(senha, login);
    }else{
        entrarSistema(senha, login);
    }
    
}

void confirmaAdm(){
    int senhaConfirmaAdm;
    printf("Senha de confirmacao para registros de administradores: ");
    scanf("%d", &senhaConfirmaAdm);

    while(senhaConfirmaAdm != 123){
        printf("Senha invalida, tente novamente: ");
        scanf("%d", &senhaConfirmaAdm);

        limparTela();
    }

}

void entrarSistema(char *senha[], char *login[]){
    char senhaCopia[20], loginCopia[20];

    printf("\n#################\n");
    printf("|     LOGAR     |\n");
    printf("#################\n\n");

    printf("Login: ");
    scanf("%s", &loginCopia);

    printf("Senha: ");
    scanf("%s", &senhaCopia);

    limparTela();

    while(strcmp(senha, senhaCopia) != 0 || strcmp(login, loginCopia) != 0){
        printf("Login ou senha invalidos, tente novamente!\n");

        printf("Login: ");
        scanf("%s", &loginCopia);

        printf("Senha: ");
        scanf("%s", &senhaCopia);      

        limparTela();  
    }
}

int adminOuUser(char *login[]){
    char palavraChave[] = {"admin"};
    char *ponteiro;
    int retorno;

    ponteiro = strstr(login, palavraChave);

    if(ponteiro > 0){
        retorno = 1;
    }else{
        retorno = 2;
    }

    return retorno;
}

void menuAdmin(Aluno *alunos, int *ptr, int quant, char *senha[]){
    int funcionalidade;

    while(funcionalidade != 0){
        printf("\n##############################\n");
        printf("|    MENU - ADMINISTRADOR    |\n");
        printf("| [1] Matricular aluno       |\n");
        printf("| [2] Consultar aluno        |\n");
        printf("| [3] Inserir notas          |\n");
        printf("| [4] Exibir alunos          |\n");
        printf("| [5] Desmatricular aluno    |\n");
        printf("| [6] Maior nota             |\n");
        printf("| [7] Menor nota             |\n");
        printf("| [0] Sair do sistema        |\n");
        printf("##############################\n");

        printf("\nFuncionalidade: ");
        scanf("%d", &funcionalidade);
        switch (funcionalidade){
        case 1:
            matricularAluno(alunos, ptr);
            break;
        case 2:
            consultarAluno(alunos, quant);
            break;
        case 3:
            inserirNotas(alunos, quant);
            break;
        case 4:
            exibirAlunos(alunos, quant);
            break;
        case 5:
            desmatricularAluno(alunos, quant, senha);
            break;
        case 6:
            break;   
        case 7:
            break;
        default:
            break;
        }
    }
}

void menuUser(Aluno *alunos, int *ptr, int quant){
    int funcionalidade;

    while(funcionalidade != 0){
        printf("\n##############################\n");
        printf("|       MENU - USUARIO       |\n");
        printf("| [1] Matricular aluno       |\n");
        printf("| [2] Consultar aluno        |\n");
        printf("| [3] Inserir notas          |\n");
        printf("| [4] Exibir alunos          |\n");
        printf("| [5] Maior nota             |\n");
        printf("| [6] Menor nota             |\n");
        printf("| [0] Sair do sistema        |\n");
        printf("##############################\n");

        printf("\nFuncionalidade: ");
        scanf("%d", &funcionalidade);
        switch (funcionalidade){
        case 1:
            matricularAluno(alunos, ptr);
            break;
        case 2:
            consultarAluno(alunos, quant);
            break;
        case 3:
            inserirNotas(alunos, quant);
            break;
        case 4:
            exibirAlunos(alunos, quant);
            break;  
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
    }
}

void limparTela() {
    #ifdef _WIN64
        system("cls");
    #elif __linux
        system("clear");
    #endif
}

void timeout(int tempoMs) {
    #ifdef _WIN64
        Sleep(tempoMs);
    #elif __linux
        usleep(tempoMs * 1000);
    #endif
}

void matricularAluno(Aluno *alunos, int *ptr){
    printf("\n=-=-=-=-= MATRICULAR ALUNO -=-=-=-=-=\n");

    printf("\nProntuario do aluno: ");
    scanf("%s", &alunos[*ptr].prontuario);
    
    getchar();

    printf("Nome do aluno: ");
    gets(alunos[*ptr].nome);

    printf("Idade do aluno: ");
    scanf("%d", &alunos[*ptr].idade);

    printf("\nALUNO MATRICULADO!\n");

    *ptr += 1;
}

void consultarAluno(Aluno *alunos, int quant){
    char prontuarioCopia[20];
    int flag = 0;

    printf("\n=-=-=-=-= CONSULTAR ALUNO -=-=-=-=-=\n");

    printf("\nProntuario: ");
    scanf("%s", &prontuarioCopia);

    for(int i = 0; i < quant; i++){
        if(strcmp(alunos[i].prontuario, prontuarioCopia) == 0){
            printf("\n=-=-=-=-= DADOS -=-=-=-=-=\n");

            printf("Nome: %s\n", alunos[i].nome);
            printf("Prontuario: %s\n", alunos[i].prontuario);
            printf("Idade: %d\n", alunos[i].idade);
            for(int j = 0; j < 4; j++){
                printf("Nota %d: %.2f\n", j+1, alunos[i].notas[j]);
            }
            break;
        }else{
            flag += 1;
        }
    }

    if(flag == quant){
        printf("\nProntuario nao encontrado!\n");
    }
}

void inserirNotas(Aluno *alunos, int quant){
    char prontuarioCopia[20];
    int flag = 0;

    printf("\n=-=-=-=-= INSERIR NOTAS -=-=-=-=-=\n");

    printf("\nProntuario: ");
    scanf("%s", &prontuarioCopia);

    for(int i = 0; i < quant; i++){
        if(strcmp(alunos[i].prontuario, prontuarioCopia) == 0){
            for(int j = 0; j < 4; j++){
                printf("Nota %d: ", j+1);
                scanf("%f", &alunos[i].notas[j]);
            }
            break;
        }else{
            flag += 1;
        }
    }

    if(flag == quant){
        printf("\nProntuario nao encontrado!\n");
    }else{
        printf("\nNOTAS INSERIDAS!\n");
    }
}

void exibirAlunos(Aluno *alunos, int quant){
    printf("\n=-=-=-=-= ALUNOS MATRICULADOS -=-=-=-=-=\n");

    for(int i = 0; i < quant; i++){
        if(alunos[i].idade > 0 && alunos[i].idade < 100){
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("ALUNO %d!\n", i+1);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Prontuario: %s\n", alunos[i].prontuario);
            printf("Idade: %d\n", alunos[i].idade);
            for(int j = 0; j < 4; j++){
                printf("Nota %d: %.2f\n", j+1, alunos[i].notas[j]);
            }
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        }
    }
}

void desmatricularAluno(Aluno *alunos, int quant, char *senha[]){
    char prontuarioCopia[20], senhaCopia[20];
    int flag = 0;

    printf("\n=-=-=-=-= DESMATRICULAR ALUNO -=-=-=-=-=\n");

    printf("\nProntuario: ");
    scanf("%s", &prontuarioCopia);
    
    printf("Confirme sua senha para desmatricular o aluno solicitado: ");
    scanf("%s", &senhaCopia);
    while(strcmp(senha, senhaCopia) != 0){
        printf("Senha incorreta, tente novamento: ");
        scanf("%s", &senhaCopia);
    }

    for(int i = 0; i < quant; i++){
        if(strcmp(alunos[i].prontuario, prontuarioCopia) == 0){
            alunos[i].idade = 0;
            for(int j = 0; j < quant; j++){
                alunos[i].notas[j] = 0;
            }
            strcpy(alunos[i].nome, " ");
            strcpy(alunos[i].prontuario, " ");
            
            break;
        }else{
            flag += 1;
        }
    }

    if(flag == quant){
        printf("\nProntuario nao encontrado!\n");
    }else{
        printf("\nALUNO DESMATRICULADO!\n");
    }
    
}
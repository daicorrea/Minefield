/*
Unirio
Trabalho de TP1
Prof. Geiza Hamazaki
Daiane Correa e Leonardo Santos*/


#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <string.h>

void preenche_pos (int mat[12][12]);
short escolhe_posicao (short pos);
int conta_minas (int pos[12][12],int minas);
void mostra (int mat[12][12],int pos[12][12]);
void mostra_aberto (int mat[12][12]);
void posicao (int cm[12][12], int minas,int res);
void calcula (int mat[12][12]);
void gerador (int mat[12][12],int minas);
void preenche (int mat[12][12]);
void exemplo(int mat[12][12]);
void apresentacao();
void escreve_arquivo(int res);
int altera_valor(int res, int minas);
void manual();
int main(){
   int cm[12][12],minas,res;
   short l,c;
   res=0;
   apresentacao();
       do{
          printf ("Digite a quantidade de bombas desejada (No minimo 1, no maximo 70 bombas): \n");
          scanf ("%d",&minas);//pede o numero de minas
          fflush (stdin);
          if (minas < 1 || minas > 70)
             printf ("\nValor invalido!\n\n");
       }while(minas < 1 || minas > 70);

       preenche(cm);
       gerador(cm,minas);
       calcula(cm);
       posicao(cm,minas,res);

   system("pause");
}

void apresentacao(){
    int cm[12][12], aux,operacao;
    printf("\n\n\n      ===========================================\n");
   printf("      == Bem vindo ao jogo de Campo Minado! 8D ==\n ");
   printf("     ===========================================\n\n\n\n");
   printf("O que deseja fazer?\n\n1 - Jogar\n2 - Sair\n3 - Ler manual do jogo\n\n");
   scanf("%d", &operacao);

   if(operacao == 2){
		exit(1);
	}
   else{
        if(operacao==1){
            system("cls"); // Limpa a tela
            exemplo(cm);
        }
        else{
            if(operacao==3){
                system("cls"); // Limpa a tela
                manual();
                printf("\nDigite 1 para voltar ou outra tecla para sair.\n");
                scanf("%d",&aux);
                if (aux==1){
                    system("cls"); // Limpa a tela
                    apresentacao();
                }else{
                    exit(1);
                }
            }
            else{
                system("cls");
                apresentacao();
            }
        }
    }
}

void exemplo(int mat[12][12]){  //imprime a matriz de exemplo para o jogador
 short l,c;
    printf("\n\n - Campo minado - \n\n");
    printf ("\n     1 2 3 4 5 6 7 8 9 10");
     for(l=0; l<12; l++){
         if (l > 0 && l < 11){
                if(l==10){
                    printf ("\n%hd ",l); //imprime um short int
                }
                else{
                    printf ("\n %hd ",l);
                }
         }
         else{
             printf ("  \n");
        }
    for(c=0; c<12; c++){
            if(l == 0 && c == 0 || l == 11 && c == 0){
                printf("   = ");
            }
            else{
                if(l == 0 || l == 11 || c == 0 || c == 11){
                    printf("= ");
                }
                else{
                     printf("? ");
                }
            }
        }

    }
    printf("\n\n");
}


void preenche (int mat[12][12]){//zerando a matriz do jogo
   short l,c;

   for(l=0; l<12; l++){
      for(c=0; c<12; c++){
            if (l == 0 || l == 11 || c == 0 || c == 11){
                mat[l][c] = '='; //ladinhos bonitinhos pra fazer a borda
            }
            else{
                mat[l][c] = 0;
            }

        }
    }
}

void gerador (int mat[12][12],int minas){//gerando minas em posiçoes aleatorias atraves da hora do sistema
   short l,c,cont=0;
   int gerado;
   srand(time(NULL)); //retira informações da hora do sistema pra criar numeros randomicos.
    do{
      gerado = rand() % 10 + 1;
      l = gerado;
      gerado = rand() % 10 + 1;
      c = gerado;
      if (mat[l][c] != 9){ //numero randomico
         mat[l][c] = 9;
         cont++; //contando a qtd de minas
      }
   }while (cont < minas); //até a qtd ser igual a entrada pelo usuario
}

void calcula (int mat[12][12]){ //calcula ao redor da posiçao que foi escolhida se tem ou nao bomba

   short l,c,x,y;
    for(l=0; l<12; l++){
      for(c=0; c<12; c++){
        if (mat[l][c] == 9){//se for bomba
          for (x = l - 1; x <= l + 1; x++){//linha ao redor
            for (y = c - 1; y <= c + 1; y++){//coluna ao redor
              if (mat[x][y] != 9){//se ao redor nao for bomba
                 mat[x][y] += 1;//avisa que tem mais uma bomba ao redor desse numero
              }
            }
          }
        }
      }
    }
}

void posicao (int cm[12][12], int minas,int res)
{
   int pos[12][12],sem_minas=100-minas,aux1,aux2,salvar;
   short l=0,c=0;

   preenche_pos(pos);

   do{
      printf ("\nUtilize posicao 0,0 para sair do jogo.\n");
      printf ("\nLinha: ");
      l = escolhe_posicao(l);//pede a posiçao da linha
      printf ("\nColuna: ");
      c = escolhe_posicao(c);//pede a posiçao da coluna
      if (l == 0 && c == 0){//caso ocorra sai do jogo
         exit(0);
      }
      else{
            if(pos[l][c] == 1 && l != 0 && c != 0){//so ocorre se posiçao jah tiver sido aberta e nao tiver pedido pra sair
                printf ("\nEsta posicao ja foi escolhida!\n");
            }
            else{//se posiçao nao tiver sido aberta
                 if(cm[l][c] == 9){//se for bomba
                    pos[l][c] = 0;
                    aux1=res;
                    aux2=altera_valor(aux1,minas);
                    res=aux2;
                    printf ("\nQue pena, voce atingiu uma bomba!\n");
                    printf("\nSua pontuacao final foi: %d\n",res);
                    mostra_aberto(cm);//mostra matriz inclusive as bombas
                    printf("\nDeseja salvar seu recorde no arquivo?\n1-Sim\n2-Nao\n\n");
                    scanf("%d",&salvar);
                    if(salvar==1){
                        escreve_arquivo(res);
                        printf("O arquivo com os recordes esta localizado na pasta do jogo\n");
                    }else{
                        break;
                    }
                    break;
                }
                else{//se nao for bomba
                    if(cm[l][c] == 0){//se nao tiver bomba por perto
                        pos[l][c] = 1;
                        mostra(cm,pos);//mostra a matriz mas apenas com as posiçoes que foram abertas
                        sem_minas = conta_minas(pos,minas);//calcula quantos espaços em branco ainda existem
                        res++;
                        printf ("\nRestam %d espacos sem bomba.\n",sem_minas);
                    }
                    else{//se tiver bomba por perto ira imprimir o numero que foi calculado anteriormente pela funçao calcula na main
                        pos[l][c] = 1;
                        mostra(cm,pos);
                        sem_minas = conta_minas(pos,minas);
                        res++;
                        printf ("\nRestam %d espacos sem bomba.\n",sem_minas);
                    }
                }
            }
      }
   }while(sem_minas != 0);//enquanto tiver espaços em branco que nao foram abertos ele repete
       if (sem_minas == 0){
              aux1=res;
              aux2=altera_valor(aux1,minas);
              res=aux2;
              printf ("\nParabens! Voce ganhou!\n");
              printf("\nSua pontuacao final foi: %d\n",res);
              printf("\nDeseja salvar seu recorde no arquivo?\n1-Sim\n2-Nao\n\n");
              scanf("%d",&salvar);
              if(salvar==1){
                  escreve_arquivo(res);
                  printf("O arquivo com os recordes esta localizado na pasta do jogo\n");
              }
              
        }

}


void preenche_pos (int pos[12][12]){ //inicializa a matriz pos com 5
   short l,c;

   for(l=0; l<12; l++){
      for(c=0; c<12; c++){
         pos[l][c] = 5; //numero randomico
        }
    }
}

short escolhe_posicao (short pos){ // pedir e armazenar posiçao da linha e coluna que o usuario quer
   do{
      printf ("Digite a posicao desejada: ");
      scanf ("%hd",&pos);
      fflush (stdin);
      if (pos < 0 || pos > 10)
         printf ("\nValor invalido!\n");
   }while(pos < 0 || pos > 10);

   return pos;
}
int conta_minas (int pos[12][12],int minas){//verifica quantos espaços em branco nao abertos ainda resta na matriz
   int espacos=0;
   short l,c;
    for(l=1; l<11; l++){
      for(c=1; c<11; c++){
         if(pos[l][c] != 1){
             espacos++;
          }
       }
    }
   return (espacos-minas);
}

void mostra (int mat[12][12],int pos[12][12]){// imprime a matriz a cada jogada que o jogador nao acerta mina
   short l,c;
     printf ("\n     1 2 3 4 5 6 7 8 9 10");
     for(l=0; l<12; l++){
         if (l > 0 && l < 11){
             if(l==10){
                    printf ("\n%hd ",l); //hd é pra printar um short int
                }
                else{
                    printf ("\n %hd ",l);
                }
            }
         else{
             printf ("  \n");
        }
    for(c=0; c<12; c++){
            if(l == 0 && c == 0 || l == 11 && c == 0){
                printf("   = ");
            }
            else{
                if(l == 0 || l == 11 || c == 0 || c == 11){
                    printf("= ");
                }
                else{
                    if(pos[l][c] == 0 || pos[l][c] == 1){
                        printf("%d ",mat[l][c]);
                    }
                    else{
                        printf("? ");
                    }
                }
            }
      }
    }
    printf("\n");
}


void mostra_aberto (int mat[12][12]){//imprime a matriz com todas as posiçoes abertas caso tenha acertado uma mina
    short l,c;
     printf ("\n     1 2 3 4 5 6 7 8 9 10");
     for(l=0; l<12; l++){
         if (l > 0 && l < 11){
            if(l==10){
                    printf ("\n%hd ",l);
                }
                else{
                    printf ("\n %hd ",l);
                }
         }
         else{
             printf ("  \n");
        }
    for(c=0; c<12; c++){
            if(l == 0 && c == 0 || l == 11 && c == 0){
                printf("   = ");
            }
            else{
                if(l == 0 || l == 11 || c == 0 || c == 11){
                    printf("= ");
                }
                else{
                    if(mat[l][c] == 9){
                        printf("* ");
                    }
                    else{
                        printf("%d ",mat[l][c]);
                    }
                }
            }
      }
    }
    printf("\n");
}


void escreve_arquivo(int res){
   int r,q,n,resarq,cont,pontresultado;
   char nome[21], nomearq[21];//levando em conta que o nome da pessoa seja de ate 20 letras
   FILE *arq;
   printf("\nDigite seu nome\n");
   scanf(" %20[^\n]",nome);//pede o nome do usuario
   
   arq=fopen("resultado.txt","rt");
        if(arq==NULL){
             printf("Ocorreu um erro ao abrir o arquivo\n");
             exit(1);
         }
   fscanf(arq,"%d",&n);//le quantos recordes estao salvos no arquivo
   fclose(arq);
        if(n==0){//se nao houver recorde nenhum ele imprime o recorde
            arq=fopen("resultado.txt","wt");
                if(arq==NULL){
                     printf("Ocorreu um erro ao abrir o arquivo\n");
                     exit(1);
                }
            n=1;
            cont=2;
            fprintf(arq,"%d\n%s\n  %d\n",n,nome,res);
            fclose(arq);
         }
         else{//se houver recordes
         cont=0;
            arq=fopen("resultado.txt","rt");
                if(arq==NULL){
                    printf("Ocorreu um erro ao abrir o arquivo\n");
                    exit(1);
                }
                fscanf(arq,"%n",&n);
                r=fscanf(arq,"%s",nomearq);
                while(r==1){//varre o arquivo em busca de todos os recordes existentes
                    if((strcmp(nome,nomearq))==0){//se nome for igual
                    cont=1;
                }
                    r=fscanf(arq,"%s",nomearq);
                }
                fclose(arq);
            }
            if(cont==0){//se houver recorde salvo e nenhum nome repetido
            arq=fopen("resultado.txt","r+");
                if(arq==NULL){
                    printf("Ocorreu um erro ao abrir o arquivo\n");
                    exit(1);
                }
                fscanf(arq,"%d",&n);
                r=fscanf(arq,"%s %d",nomearq,&resarq);
                while(r==2){//varre o arquivo recorde por recorde
                    r=fscanf(arq,"%s %d",nomearq,&resarq);//imprime os recordes ja existentes
                }
                fprintf(arq,"%s\n  %d\n",nome,res);//imprime o nome e pontuaçao do jogo atual
                n++;
                rewind(arq);//volta ao inicio do arquivo
                fprintf(arq,"%d",n);//atualiza o n
                fclose(arq);
            }
            else{//se contador nao for 0
                if(cont==1){//se houver recorde salvo mas o nome ja existir
                    arq=fopen("resultado.txt","r+");
                        if(arq==NULL){
                            printf("Ocorreu um erro ao abrir o arquivo\n");
                            exit(1);
                        }
                        fscanf(arq,"%d",&n);
                    r=fscanf(arq,"%s %d",nomearq,&resarq);
                        while(r==2){//varre o arquivo recorde por recorde
                            if((strcmp(nome,nomearq))==0){//se nome for igual
                                pontresultado=resarq;
                            }
                            r=fscanf(arq,"%s %d",nomearq,&resarq);
                        }
                        rewind(arq);
                        r=fscanf(arq,"%s",nomearq);
                            while(r==1){//varre o arquivo nome por nome
                                if((strcmp(nomearq,nome))==0){//se nome for igual
                                    if(res>pontresultado){//e se pontuaçao atual for maior que pontuaçao salva anteriormente
                                        fseek(arq,0,SEEK_CUR);
                                            if(res>=10 && res < 100){
                                                fprintf(arq,"\n %d\n",res);
                                                break;
                                            }
                                            else{
                                                if(res>=100){
                                                    fprintf(arq,"\n%d\n",res);
                                                    break;
                                                }
                                            }
                                    }
                                    else{//se pontuaçao atual for menor do que a arquivada nao altera
                                        break;
                                    }
                                }
                            r=fscanf(arq,"%s",nomearq);
                            }
                        fclose(arq);
                        }
        }
}
    
int altera_valor(int aux, int minas){
        int total, sem_minas;
        float div;
        sem_minas = 100 - minas; //espaços vazios da matriz
        div = (minas/10);
        total = int((minas+div)+aux);
        
        return total;
}

void manual(){
    int r,pular;
    FILE* manual;
    char frase[101];
    pular=0;
    manual=fopen("cmmanual.txt","rt");
    if(manual==NULL){
        printf("Ocorreu um erro ao abrir o arquivo\n");
        exit(1);
    }
    r=fscanf(manual,"%100[^\n]\n",frase);
    while(r!=EOF){
        pular++;
        if(pular==1 || pular==2 || pular==3 || pular==14 || pular==15){
            printf("\n");
        }
        printf("%s\n",frase);
        r=fscanf(manual,"%100[^\n]\n",frase);
    }
    fclose(manual);
}
    


#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h> //biblioteca pra funcionar o sleep
#include <ctype.h>
#include "tamanhoArq.h"
#include "token.h"
// ------------- declarações
#define nomeArquivo "linguagem.c"
#define TRUE 1
#define FALSE 0
struct thread{
    int idThread;
    pthread_t thread;
    char buffer[100];
    int statusBuf;
};
typedef struct thread thread;
thread *teste;
int lock = 0;
#define Buffer_Limit 100
char *Buffer_Queue;
// ------------- fim declarações



void *lerArquivo(void *arg){
    long vezes = (long)arg;
    	//printf("Lock = %d e Vezes %ld \n", lock, vezes);
    int controle=0;
    int quantVezRodada = 0;
    while(controle==0){
        if (lock==1){
        	quantVezRodada++;
        	//printf("Tentou entrar na região critica, vezes = %ld \n", vezes);
        	sleep(1);
        }else if(lock==0){
        	controle=1;
        	lock=1;
        	//printf("Entrou na região critica, vezes = %ld \n", vezes);
    	FILE *arq;
    	char ch;
    	int quantidadeCaracter = 0;
    	int quantAux = 100*(vezes);
    	arq = fopen(nomeArquivo, "r");
    	if(arq == NULL){
    	}else{
    	    int e = 0;
    		while( (ch=fgetc(arq))!= EOF ){

    		    if (ch!=' ' || ch!='\n'){
    		        quantidadeCaracter++;

    		    }
    			if (quantidadeCaracter > quantAux && quantidadeCaracter <= quantAux + 100){

    			    //printf("Caractere no vetor: %c \n", v[e]);

    			    //threads[vezes].buffer[e] = ch;
    			    teste[vezes].buffer[e] = ch;
    			    //printf("Caracter numero-> %d ",quantidadeCaracter);
    			    //printf("Caracter -> %c \n", teste[vezes].buffer[e]);

    			    e++;
                    teste[vezes].statusBuf=1;
    			}
    			}
    	}
    	fclose(arq);
    	lock=0;
    	//printf("Saiu da região critica, vezes = %ld \n", vezes);
        }
    }
}
void *reconhecerToken(void *arg){
    long vezes = (long)arg;
    int controle=0;
    int quantVezRodada = 0;
    while(controle==0){
        if (lock==1){
        	quantVezRodada++;
        	//printf("CONSUMIDOR. Tentou entrar na região critica, vezes = %ld \n", vezes);
        	sleep(1);
        }else if(lock==0){
            if (teste[vezes].statusBuf==1){
            //printf("CONSUMIDOR. Entrou na região critica, vezes = %ld \n", vezes);
            lock=1;
            controle=1;
            int i=0;

            //printf("---------- VEZES -> %ld \n", vezes);
            for (i=0;i<Buffer_Limit;i++){
                if ( isdigit(teste[vezes].buffer[i]) ){
                    printf("<NUMBER,");

                    printf("%c", teste[vezes].buffer[i]);

                    i++;
                    while(isdigit(teste[vezes].buffer[i]) || (teste[vezes].buffer[i] == '.' && isdigit(teste[vezes].buffer[i+1]))){
                        if (isdigit(teste[vezes].buffer[i])){
                            printf("%c", teste[vezes].buffer[i]);
                        }
                        else {
                            printf("%c", teste[vezes].buffer[i]);

                            i++;

                            printf("%c", teste[vezes].buffer[i]);

                        }
                        i++;
                    }

                    printf(">");

                }
                //printf("%c", teste[vezes].buffer[i]);
                if (teste[vezes].buffer[i]=='\n'){
                    printf("<ENDL> \n");
                }
                if (teste[vezes].buffer[i]=='['){
                    printf("\n<OC>");
                }
                if (teste[vezes].buffer[i]==']'){
                    printf("<CC>");
                }
                if (teste[vezes].buffer[i]=='('){
                    printf("\n<OP>");
                }
                if (teste[vezes].buffer[i]==')'){
                    printf("<CP>");
                }
                if (teste[vezes].buffer[i]=='-'){
                    printf("<MENOS>");
                }
                if (teste[vezes].buffer[i]=='+'){
                    printf("<SOMA>");
                }
                if (teste[vezes].buffer[i]=='%'){
                    printf("<POR>");
                }
                if (teste[vezes].buffer[i]=='/'){
                    printf("<DIV>");
                }
                if (teste[vezes].buffer[i]=='*'){
                    printf("<MULT>");
                }
                if (teste[vezes].buffer[i]==','){
                    printf("\n<VIR>");
                }
                if (teste[vezes].buffer[i]=='>'){
                    if (teste[vezes].buffer[i+1]=='>'){
                        printf("\n<IN>");
                        i++;
                    }else if (teste[vezes].buffer[i+1]=='='){
                        printf("<MAI>");
                         i++;
                    }else{
                        printf("<MAIOR>");
                    }
                }
                if (teste[vezes].buffer[i]=='<'){
                    if (teste[vezes].buffer[i+1]=='<'){
                        printf("\n<OUT>");
                        i++;
                    }else if (teste[vezes].buffer[i+1]=='='){
                        printf("<MEI>");
                         i++;
                    }else{
                        printf("<MENOR>");
                    }
                }
                if (teste[vezes].buffer[i]=='!'){
                    if(teste[vezes].buffer[i+1]=='='){
                    printf("<DIF>");
                     i++;
                   }else{
                     printf("<EXC>");
                   }
                }

                if (teste[vezes].buffer[i]=='=' && teste[vezes].buffer[i+1]=='='){
                    printf("<II>");
                     i++;
                }
                if (teste[vezes].buffer[i]=='.'){
                    printf("<CON>");
                }
                if (teste[vezes].buffer[i]=='"'){
                    printf("<STRING,");
                    int q=0;
                    for(q=i;q<Buffer_Limit;q++){

                        printf("%c",teste[vezes].buffer[q]);
                        i++;
                        if(teste[vezes].buffer[i]=='"'){
                            goto sai;
                        }
                    }
                    sai:
                    printf("\">");
                }
                if (teste[vezes].buffer[i]=='@'){
                    printf("<VAR,");
                    int q=0;
                    for(q=i;q<Buffer_Limit;q++){

                        printf("%c",teste[vezes].buffer[q]);
                        i++;
                        if(teste[vezes].buffer[i]==' ' ||
                        teste[vezes].buffer[i]==']' ||
                        teste[vezes].buffer[i]=='[' ||
                        teste[vezes].buffer[i]=='\n'||
                        teste[vezes].buffer[i]=='.'||
                        teste[vezes].buffer[i]=='+'||
                        teste[vezes].buffer[i]==')'||
                        teste[vezes].buffer[i]=='('||
                        teste[vezes].buffer[i]=='>'||
                        teste[vezes].buffer[i]=='<'||
                        teste[vezes].buffer[i]=='!'||
                        teste[vezes].buffer[i]=='='||
                        teste[vezes].buffer[i]=='*'||
                        teste[vezes].buffer[i]=='/'){
                            i--;
                            goto saiv;
                        }
                    }
                    saiv:
                    printf(">");
                }
            }
            lock=0;
            }
        }
    }
}
int main(){
    int tamanho = tamanhoArq();
    teste = (thread *) malloc(sizeof(thread) * tamanho);
    //printf("Quantidade de linha do arquivo -> %d \n", tamanho);
    int rc;
    long i;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (i=0;i<tamanho;i++){
        teste[i].statusBuf=0;
        rc = pthread_create(&(teste[i]).thread, &attr, &lerArquivo, (void *)i);
        pthread_create(&(teste[i]).thread, &attr, &reconhecerToken, (void *)i);
        if (rc) {
          //printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
          }
    }
    pthread_attr_destroy(&attr);
	for (i=0;i<tamanho;i++){
        pthread_join((teste[i]).thread, NULL);
        if (rc) {
          //printf("ERROR; return code from pthread_join() is %d\n", rc);
          exit(-1);
          }
    }

}

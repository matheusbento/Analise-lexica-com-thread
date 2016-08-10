#define nomeArquivo "linguagem.c"
int tamanhoArq(){
    FILE *arq;
    int quantidadeCaracter =0;
	arq = fopen(nomeArquivo, "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fgetc(arq))!= EOF ){
			quantidadeCaracter++;
			}
	fclose(arq);
	return (quantidadeCaracter/100)+1;
    
}
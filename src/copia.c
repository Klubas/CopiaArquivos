#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Linux
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>

/*inicio coisas que deveriam ser um header*/
struct MeuArquivo{
    int tam;
    const char* id;
    const char* output_id;
    FILE *in;
    FILE *out;
} typedef MeuArquivo;

void criarArquivo();
void criarArquivosResult();
void calculaTempoCriar(MeuArquivo file);
void calculaTempoCopiar(MeuArquivo);
double encheArquivoFunc(MeuArquivo, char);
double encheArquivoSys(MeuArquivo, char);
void salvaResultados(MeuArquivo, MeuArquivo, float);
double copiaFunc(MeuArquivo);
double copiaSys(MeuArquivo);
const char* agora();
/*fim coisas que deveriam ser um header*/

MeuArquivo file1;
MeuArquivo file2;
MeuArquivo file3;
MeuArquivo file4;
MeuArquivo resultFunc;
MeuArquivo resultSys;
MeuArquivo resultCriarSys;
MeuArquivo resultCriarFunc;

FILE* output = NULL;

int remover_out = 1;
int manter_log = 0;
struct timeval t_inicio, t_fim;
struct timezone tzp;

char data[80];

int main(){
    int i;
    char c = 'n';

    printf("\n%s Manter arquivos copiados em disco (S/n)\n > ", agora());
    scanf("%c", &c);
    
    if(c == 'n' || c == 'N'){
        printf("%s Arquivos serao removidos.\n", agora());
        remover_out = 1;
    } else {
        printf("%s Arquivos serao mantidos.\n", agora());
        remover_out = 0;
    }

    if(manter_log) output = fopen("logfile.log", "a");
    else output = stdout;

    c = 'n';
    printf("\n%s Manter Log?(s/N)\n > ", agora());
    scanf("%c", &c);

    if(c == 'n' || c == 'N'){
        manter_log = 0;
    } else {
	manter_log = 1;
	printf("Executando...\n");
    }

    criarArquivo();
    criarArquivosResult();

    calculaTempoCriar(file1);
    calculaTempoCriar(file2);
    calculaTempoCriar(file3);
    calculaTempoCriar(file4);
    
    calculaTempoCopiar(file1);
    calculaTempoCopiar(file2);
    calculaTempoCopiar(file3);
    calculaTempoCopiar(file4);

    if(manter_log) {
        fclose(output);
        printf("Execucao completa, verifique o arquivo de log\n");
    }

    exit(0);
}

const char* agora(){
   time_t rawtime;
   struct tm *info;

   time( &rawtime );

   info = localtime( &rawtime );

   strftime(data,80,"\%d/%m/%Y - %H:%M:\%S>", info);
   return data;
}

void criarArquivosResult(){
    resultFunc.id = "ResultFunc.csv";
    resultSys.id = "ResultSys.csv";
    resultCriarFunc.id = "ResultCriarFunc.csv";
    resultCriarSys.id = "ResultCriarSys.csv";
        
    resultFunc.in = fopen(resultFunc.id, "w");
    resultSys.in = fopen(resultSys.id, "w");
    resultCriarFunc.in = fopen(resultCriarFunc.id, "w");
    resultCriarSys.in = fopen(resultCriarSys.id, "w");

    fprintf(resultFunc.in, "Arquivo, tamanho, tempo\n");
    fprintf(resultSys.in, "Arquivo, tamanho, tempo\n");
    fprintf(resultCriarFunc.in, "Arquivo, tamanho, tempo\n");
    fprintf(resultCriarSys.in, "Arquivo, tamanho, tempo\n"); 
    
    fclose(resultFunc.in);
    fclose(resultSys.in);
    fclose(resultCriarFunc.in); 
    fclose(resultCriarSys.in);
}

void criarArquivo(){
    //Inicializa os 4 arquivos
    file1.id = "File1.in"; 
    file2.id = "File2.in"; 
    file3.id = "File3.in"; 
    file4.id = "File4.in";

    file1.output_id = "File1.out"; 
    file2.output_id = "File2.out"; 
    file3.output_id = "File3.out"; 
    file4.output_id = "File4.out";

    file1.tam = 1;
    file2.tam = 1024;
    file3.tam = 1024 * 1024;
    file4.tam = 1024 * 1024 * 1024;
}

void calculaTempoCopiar(MeuArquivo file){
    int i = 0;
    for (i = 0; i < 5; i++){
        fprintf(output, "%s [%d] Copiando arquivo %s.\n",agora(), i, file.id);
        salvaResultados(resultFunc, file, copiaFunc(file));
        salvaResultados(resultSys, file, copiaSys(file));
    }
    fprintf(output, "%s Resultados (funcoes) gravados em %s\n", agora(),resultFunc.id);
    fprintf(output, "%s Resultados (syscalls) gravados em %s\n", agora(),resultSys.id);
}

void calculaTempoCriar(MeuArquivo file){
    int i;
    for (i = 0; i < 5; i++){
        fprintf(output, "%s [%d] Criando arquivo %s.\n",agora(), i, file.id);
        salvaResultados(resultCriarFunc, file, encheArquivoFunc(file, 'A'));
        salvaResultados(resultCriarSys, file, encheArquivoSys(file, 'A'));
        
    }
    fprintf(output, "%s Resultados (criacao Funcoes) gravados em %s\n", agora(),resultCriarFunc.id);
    fprintf(output, "%s Resultados (criacao Syscalls) gravados em %s\n", agora(),resultCriarSys.id);    
}

double encheArquivoFunc(MeuArquivo file, char c){
    int i;
    file.in = fopen(file.id, "w");    

     fprintf(output, "%s Criando arquivo %s usando funcoes\n",agora() , file.id);
    
    gettimeofday(&t_inicio, &tzp);
    for(i=0; i < file.tam; i++) fputc(c, file.in);
    gettimeofday(&t_fim, &tzp);
    
    fclose(file.in);
    fprintf(output, "%s Criado arquivo %s. - Tamanho: %d Bytes\n",agora() ,file.id, file.tam);
    
    return (double)   (t_fim.tv_sec - t_inicio.tv_sec) + 
            (((double) (t_fim.tv_usec - t_inicio.tv_usec))/1000000);
}

double encheArquivoSys(MeuArquivo file, char c){
    int in, i;

    in = open(file.id, O_WRONLY| O_CREAT,S_IRUSR|S_IWUSR); //linux

   fprintf(output, "%s Criando arquivo %s usando syscalls\n",agora() , file.id);

    gettimeofday(&t_inicio, &tzp);
    for(i = 0;i < file.tam; i++) write(in,&c,1);
    gettimeofday(&t_fim, &tzp);
    
    close(in);
    fprintf(output, "%s Criado arquivo %s. - Tamanho: %d Bytes\n",agora() , file.id, file.tam);

    
    return (double)   (t_fim.tv_sec - t_inicio.tv_sec) + 
            (((double) (t_fim.tv_usec - t_inicio.tv_usec))/1000000);
}

//gravar bytes em arquivo file usando funcao
double copiaFunc(MeuArquivo file){
    char c;
   
    file.in = fopen(file.id,"r");
    file.out = fopen(file.output_id,"w");

    fprintf(output, "%s Copiando arquivo %s usando funcoes\n",agora() , file.id);

    gettimeofday(&t_inicio, &tzp);
    while((c = fgetc(file.in)) != EOF) fputc(c, file.out);
    gettimeofday(&t_fim, &tzp);

    fclose(file.in);
    fclose(file.out);
    
    fprintf(output, "%s Arquivo %s copiado utilizando Funcoes\n",agora() ,file.id);
    
    if(remover_out){
        remove(file.output_id);
        fprintf(output, "%s %s foi removido.\n",agora(), file.output_id);
    }
    
    return (double)   (t_fim.tv_sec - t_inicio.tv_sec) + 
            (((double) (t_fim.tv_usec - t_inicio.tv_usec))/1000000);
}

//grava bytes em arquivo file usando syscall
double copiaSys(MeuArquivo file){
    char c;
    int in, out;

    in = open(file.id, O_RDONLY);
    out = open(file.output_id, O_WRONLY| O_CREAT,S_IRUSR|S_IWUSR); //linux
    //out = open(file.output_id, O_WRONLY | O_CREAT);

    fprintf(output, "%s Copiando arquivo %s usando syscalls\n",agora() , file.id);
    
    gettimeofday(&t_inicio, &tzp);
    while(read(in,&c,1) == 1) write(out,&c,1);
    gettimeofday(&t_fim, &tzp);
    
    close(in);
    close(out);

    fprintf(output, "%s Arquivo %s copiado utilizando Syscalls\n",agora() ,file.id);
    
    if(remover_out){
        remove(file.output_id);
        fprintf(output, "%s %s foi removido.\n",agora() , file.output_id);
    }

    return (double)   (t_fim.tv_sec - t_inicio.tv_sec) + 
            (((double) (t_fim.tv_usec - t_inicio.tv_usec))/1000000);
}

//grava resultados do tempo de execução em um arquivo de texto
void salvaResultados(MeuArquivo resultados, MeuArquivo file, float result) {
    resultados.in = fopen(resultados.id, "a");
    fprintf(resultados.in, "%s, %d, %f\n", file.id, file.tam, result);
    fclose(resultados.in);
}

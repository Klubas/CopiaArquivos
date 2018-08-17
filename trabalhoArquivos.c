#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Linux
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>

/*inicio coisas que deveriam ser um header*/
struct MeuArquivo{
    int tam;
    const char* id;
    const char* output_id;
    FILE *in;
    FILE *out;
} typedef MeuArquivo;

void criarArquivos();
void calculaTempo(MeuArquivo);
double encheArquivo(MeuArquivo, char);
void calculaTempo(MeuArquivo);
void salvaResultados(MeuArquivo, MeuArquivo, float);
double copiaFunc(MeuArquivo);
double copiaSys(MeuArquivo);
/*fim coisas que deveriam ser um header*/

MeuArquivo file1;
MeuArquivo file2;
MeuArquivo file3;
MeuArquivo file4;
MeuArquivo resultFunc;
MeuArquivo resultSys;
MeuArquivo resultCriar;

int remover_out = 1;

struct timeval t_inicio, t_fim;
struct timezone tzp;

int main(){
    int i;
    char c = 'n';
    criarArquivos();
    
    printf("Manter arquivos copiados em disco (s/n)\n > ");
    scanf("%c", &c);
    
    if(c == 'n'){
        printf("Arquivos serao mantidos.\n");
        remover_out = 1;
    } else {
        printf("Arquivos serao removidos.\n");
        remover_out = 0;
    }
    
    calculaTempo(file1);
    calculaTempo(file2);
    calculaTempo(file3);
    calculaTempo(file4);
    exit(0);
}

void criarArquivos(){
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

    encheArquivo(file1, '1');
    encheArquivo(file2, '2');
    encheArquivo(file3, '3');
    encheArquivo(file4, '4');
    
    //arquivos de resultados
    resultFunc.id = "ResultFunc.csv";
    resultSys.id = "ResultSys.csv";
    resultCriar.id = "ResultCriar.csv";
        
    resultFunc.in = fopen(resultFunc.id, "w");
    resultSys.in = fopen(resultSys.id, "w");
    resultCriar.in = fopen(resultCriar.id, "w");
    
    fprintf(resultFunc.in, "Arquivo, tamanho, tempo\n");
    fprintf(resultSys.in, "Arquivo, tamanho, tempo\n");
    fprintf(resultCriar.in, "Arquivo, tamanho, tempo\n");
    
    fclose(resultFunc.in);
    fclose(resultSys.in);
    fclose(resultCriar.in);
}

double encheArquivo(MeuArquivo file, char c){
    int i;
    file.in = fopen(file.id, "w");
    printf("Criando arquivo %s\n", file.id);
    
    gettimeofday(&t_inicio, &tzp);
    for(i=0; i < file.tam; i++) fputc(c, file.in);
    gettimeofday(&t_fim, &tzp);
    
    fclose(file.in);
    printf("Criado arquivo %s. Tamanho: %d Bytes\n", file.id, file.tam);
    
    return (double)   (t_fim.tv_sec - t_inicio.tv_sec) + 
            (((double) (t_fim.tv_usec - t_inicio.tv_usec))/1000000);
}

void calculaTempo(MeuArquivo file){
    int i;
    for (i = 0; i < 5; i++){
        printf("[%d] Copiando arquivo %s.\n", i, file.id);
        salvaResultados(resultFunc, file, copiaFunc(file));
        salvaResultados(resultSys, file, copiaSys(file));
    }
    printf("Resultados (funcoes) gravados em %s\n", resultFunc.id);
    printf("Resultados (syscalls) gravados em %s\n", resultSys.id);
}

//gravar bytes em arquivo file usando funcao
double copiaFunc(MeuArquivo file){
    char c;
   
    file.in = fopen(file.id,"r");
    file.out = fopen(file.output_id,"w");

    gettimeofday(&t_inicio, &tzp);
    while((c = fgetc(file.in)) != EOF) fputc(c, file.out);
    gettimeofday(&t_fim, &tzp);

    fclose(file.in);
    fclose(file.out);
    
    printf("Arquivo %s copiado utilizando Funcoes\n", file.id);
    
    if(remover_out){
        remove(file.output_id);
        printf("%s foi removido.\n", file.output_id);
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
    
    gettimeofday(&t_inicio, &tzp);
    while(read(in,&c,1) == 1) write(out,&c,1);
    gettimeofday(&t_fim, &tzp);
    
    close(in);
    close(out);

    printf("Arquivo %s copiado utilizando Syscalls\n", file.id);
    
    if(remover_out){
        remove(file.output_id);
        printf("%s foi removido.\n", file.output_id);
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

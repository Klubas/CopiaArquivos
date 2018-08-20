#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    int p, i, f;
    char c;
    FILE *file;
    
    file = fopen("demo_fputc", "w");

    p = fork();
    if(p) c = 'a';
    else c = 'b';

    for (i=0; i<100;i++)
        fputc(c, file);
    fclose(file);

    if(p) return 0;

    f = open("demo_write", O_WRONLY| O_CREAT,S_IRUSR|S_IWUSR);

    p = fork();  
    if(p) c = 'a';
    else c = 'b';

    for(i=0; i<100; i++)
        write(f, &c, 1);
    close(f);

    return 0;
}
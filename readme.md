# Avaliação de desempenho em termo de speedup

Comparar as duas estratégias:
 - Syscalls: `write()`, `read()`
 - Funções: `fputc()`, `fgetc()`

Método de cópia e gravação: 1 caractere por vez

## 1. Métodos utilizados para análise
### Criação de arquivos

Foram primeiro criados 4 arquivos, de acordo com a tabela:

| Arquivo  	| Tamanho (bytes)| 
|----------	|----------------|
| File1.in 	| 1          	 |
| File2.in 	| 1024       	 |
| File3.in 	| 1048576    	 |
| File4.in 	| 1073741824 	 |

Esse procedimento foi repetido 10 vezes para cada arquivo:
- 5 utilizando funções de manipulação de arquivo 
- 5 utilizando syscalls para gravaçãO em arquivo

Pseudocódigo para gravação em arquivo:

    Enquanto (cont < tamanho_arquivo)
        escreva('A', file); cont++;
        
Utilizando a função `gettimeofday()` foram obtidos os tempos de execução para que fosse tirada uma média das 5 execuções.

### Copia de arquivos:

Utilizando os arquivos anteriores foi feito o processo de cópia, também 10 vezes para cada arquivos:
- 5 utilizando funções de manipulação de arquivo
- 5 utilizando syscalls para cópia do arquivo

Psudocódigo para cópia de arquivo
    
    Enquanto (c = leia(input) != EOF)
        escreva(c, output);
       
Utilizando a função `gettimeofday()` foram obtidos os tempos de execução para que fosse tirada uma média das 5 execuções.       


## 2. Resultados
### Configuração da máquina
    Linux Manjaro
    Intel Core i3 3310m 2.4GHz
    6GB RAM DDR3 1600MHz
    HDD 320GB 5400 RPM
    
Todos os tempos estão em segundos.
    
### Criação dos arquivos usando funções

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in   |
|-------------|-----------|-----------|-----------|------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824 |
| Tempo Médio | 0.0000028 | 0.0000084 | 0.0066086 | 16.3184658 |


### Criação dos arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in | File4.in    |
|-------------|-----------|-----------|----------|-------------|
| Tamanho     | 1         | 1024      | 1048576  | 1073741824  |
| Tempo Médio | 0.0000036 | 0.0010324 | 1.077748 | 1134.490509 |


### Cópia de arquivos usando funções

| Arquivo     | File1.in  | File2.in | File3.in  | File4.in   |
|-------------|-----------|----------|-----------|------------|
| Tamanho     | 1         | 1024     | 1048576   | 1073741824 |
| Tempo Médio | 0.0032038 | 0.000058 | 0.0233158 | 15.2322186 |


### Cópia de arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in    |
|-------------|-----------|-----------|-----------|-------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824  |
| Tempo Médio | 0.0000062 | 0.0016586 | 1.7209822 | 1868.473657 |



 ## 4. Análise dos resultados
 
 Analisando os resultados podemos chegar a algumas conclusões\*

- Gravar um arquivo utilizando as funções é mais rápido
- Copiar um arquivo utilizando as funções também é mais rápido
- Não existe grande diferença entre gravar ou copiar um arquivo utilizando funções
- Utilizando as syscalls, copiar um arquivo é perceptívelmente mais lento do que apenas gravar
- Copiar e criar arquivos utilizando funções é cerca de 100 vezes mais rápido do que utilizando syscalls\**

\*Os tempos dos arquivos 1 e 2 possuem mais variações, por serem menores qualquer variação no uso do processador pode afetar o desempenho de forma inesperada.

\*\*Levando em conta principalmente os tempos dos arquivos 3 e 4, que são maiores.

Técnicamente, a gravação em arquivo utilizando a syscall `write()` é mais rápido. Isso por que a syscall escreve o argumento recebido diretamente no arquivo, de forma praticamente instantânea.

Na prática, o uso da função `fputc` (ou outras como `fprintf` ou `fwrite`) tem um desempenho muito melhor, pelo fato de que na sua implementação é criado um buffer com os caracteres que serão gravados, antes de eles serem efetivamente gravados.

Na pasta `demo` está incluso um pequeno programa e os arquivos resultantes de sua execução para demonstrar a diferença entre esses dois métodos. Esse progrma utiliza a função fork() para ter dois processos escrevendo em um mesmo arquivo de forma simultânea

O arquivo `demo_fputc` foi criado utilizando a função fputc, nele podemos ver o seguinte conteúdo:

`aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb`
    
Já o arquivo `demo_write` foi criado utilizando a syscall write, e nele podemos ver o seguinte:

`aaaaaaaaaaaaaaaaaaaaabababababababababababababababababbabababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababbbbbbbbbbbbbbbbbbbb`

A diferença é clara, no primeiro arquivo a gravação ocorreu de forma mais ordenada, pois todos os caracteres do loop foram gravados em um `buffer` antes de serem efetivamente gravados no arquivo.

No segundo arquivo os caracteres foram gravados de forma desorganizada, praticamente alternada, a cada iteração do `for`. Essa segunda forma é mais lenta pois a cada iteração o processo precisa aguardar que o SO confirme a gravação, nesse momento ocorre uma mudança de contexto e o fork filho pode fazer sua gravação, logo após o caractere inserido pelo processo pai.


#### Implementação da função fputc()

    int fputc (int c, FILE *fp) 
    {
      int result;
      CHECK_FILE (fp, EOF);
      if (!_IO_need_lock (fp))
        return _IO_putc_unlocked (c, fp);
      _IO_acquire_lock (fp);
      result = _IO_putc_unlocked (c, fp);
      _IO_release_lock (fp);
      return result;
    }
    
#### Implementação da syscall write() 

    ssize_t __libc_write (int fd, const void *buf, size_t nbytes) 
    {
      return SYSCALL_CANCEL (write, fd, buf, nbytes);
    }    
 
## Referências
    
    http://pubs.opengroup.org/
    https://code.woboq.org/
    tldp.org


### Desktop
    Windows 10 Pro
    AMD Ryzen 3 1300x 3.5GHz
    12GB RAM DDR4 2400MHz
    SSD 480GB 6Gb/s
    HDD 750GB 5400 RPM


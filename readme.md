# Avaliação de desempenho na cópia de arquivos em termo de speedup

Comparar as duas estratégias:
 - Syscalls: `write()`, `read()`
 - Funções: `fputc()`, `fgetc()`

Método de cópia e gravação: 1 caractere por vez

## 1. Métodos utilizados para análise
### Criação de arquivos

Foram primeiro criados 4 arquivos, de acordo com a tabela:

| Arquivo  	| Tamanho (bytes)| 
|----------	|----------------|
| File1.in 	| 1          	   |
| File2.in 	| 1024       	   |
| File3.in 	| 1048576    	   |
| File4.in 	| 1073741824 	   |

Esse procedimento foi repetido 10 vezes para cada arquivo:
- 5 utilizando funções de manipulação de arquivo 
- 5 utilizando syscalls para gravaçãO em arquivo

Pseudocódigo para gravação em arquivo:

    Enquanto (cont < tamanho_arquivo)
        escreva('A', file); cont++;
        
Utilizando a função `gettimeofday()` foram obtidos os tempos de execução para que fosse tirada uma média das 5 execuções.

### Cópia de arquivos

Utilizando os arquivos anteriores foi feito o processo de cópia, também 10 vezes para cada arquivos:
- 5 utilizando funções de manipulação de arquivo
- 5 utilizando syscalls para cópia do arquivo

Pseudocódigo para cópia de arquivo
    
    Enquanto (c = leia(input) != EOF)
        escreva(c, output);
       
Utilizando a função `gettimeofday()` foram obtidos os tempos de execução para que fosse tirada uma média das 5 execuções.       


## 2. Resultados

O programa foi executado em duas máquinas com distintas configurações de hardware. 

Em relação ao software as duas configurações são bem similares.

### Configuração da Máquina 1
    Linux Manjaro
    Intel Core i3 3310m 2.4GHz (2 Cores 4 Threads)
    6GB RAM DDR3 1600MHz
    HDD 320GB 5400 RPM
    
Resultados completos salvos na pasta `manjaro-lucas`    

### Configuração da Máquina 2
    Linux Manjaro
    AMD Ryzen 3 1300x 3.5GHz (4 Cores 4 Threads)
    12GB RAM DDR4 2400MHz
    SSD 480GB 6Gb/s
    
Resultados completos salvos na pasta `manjaro-pc`
    
### Resultados Máquina 1

Todos os tempos estão em segundos.

#### Criação dos arquivos usando funções

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in   |
|-------------|-----------|-----------|-----------|------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824 |
| Tempo Médio | 0.0000028 | 0.0000084 | 0.0066086 | 16.3184658 |

#### Criação dos arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in | File4.in    |
|-------------|-----------|-----------|----------|-------------|
| Tamanho     | 1         | 1024      | 1048576  | 1073741824  |
| Tempo Médio | 0.0000036 | 0.0010324 | 1.077748 | 1134.490509 |


#### Cópia de arquivos usando funções

| Arquivo     | File1.in  | File2.in | File3.in  | File4.in    |
|-------------|-----------|----------|-----------|-------------|
| Tamanho     | 1         | 1024     | 1048576   | 1073741824  |
| Tempo Médio | 0.0032038 | 0.000058 | 0.0233158 | 15.2322186  |


#### Cópia de arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in    |
|-------------|-----------|-----------|-----------|-------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824  |
| Tempo Médio | 0.0000062 | 0.0016586 | 1.7209822 | 1868.473657 |

### Resultados Máquina 2

Todos os tempos estão em segundos.
    
#### Criação dos arquivos usando funções

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in    |
|-------------|-----------|-----------|-----------|-------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824  |
| Tempo Médio | 0.0000018 | 0.0000074 | 0.0041192 | 3.1261698   |

#### Criação dos arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in | File4.in     |
|-------------|-----------|-----------|----------|--------------|
| Tamanho     | 1         | 1024      | 1048576  | 1073741824   |
| Tempo Médio | 0.0000036 | 0.0017828 | 0.697322 | 496.1882996  |

#### Cópia de arquivos usando funções

| Arquivo     | File1.in  | File2.in | File3.in | File4.in      |
|-------------|-----------|----------|----------|---------------|
| Tamanho     | 1         | 1024     | 1048576  | 1073741824    |
| Tempo Médio | 0.0000026 | 0.000007 | 0.005848 | 5.4580522     |

#### Cópia de arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in    |
|-------------|-----------|-----------|-----------|-------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824  |
| Tempo Médio | 0.0000018 | 0.0006704 | 0.6590028 | 681.0315432 |


 ## 3. Comparação dos resultados
 
Não convém fazer uma comparação direta entre os resultados dos dois computadores utilizados por estarem equipados com processadores de gerações muitos distantes e com propósitos distintos. Sem dúvidas o processador mais novo (Ryzen 3) se sairá muito melhor em todos os testes que possam vir a ser feitos.

O Processador Intel pertence a 3ª Geração de processadores Intel Core i3 e foi lançado em 2012. É um processador voltado para computadores mobile, tanto que a máquina utilizada é um notebook.

Já o processador AMD foi lançado no ano de 2017 e é um produto voltado para Desktops, sendo assim sem as limitações de um processador mobile.

O que será analisado é se as conclusões a serem tiradas se mantém constantes, independente do hardware utilizado.

 ## 4. Análise dos resultados

De acordo com resultados obtidos, podemos chegar a algumas conclusões quanto ao desempenho de cada um dos métodos utilizados:

- Gravar e Copiar um arquivo utilizando as funções é mais rápido
- Não existe grande diferença entre gravar ou copiar um arquivo utilizando funções
- Utilizando as syscalls, copiar um arquivo é perceptivelmente mais lento do que apenas gravar
- Copiar e criar arquivos utilizando funções é cerca de 100 a 120 vezes mais rápido do que utilizando syscalls\**

\*Os tempos dos arquivos 1 e 2 possuem mais variações, por serem menores qualquer variação no uso do processador pode afetar o desempenho de forma inesperada.

\*\*Levando em conta principalmente os tempos dos arquivos 3 e 4, que são maiores.

Técnicamente, a gravação em arquivo utilizando a syscall `write()` é mais rápido. Isso por que a syscall escreve o argumento recebido diretamente no arquivo, de forma praticamente instantânea.

Na prática, o uso da função `fputc` (ou outras como `fprintf` ou `fwrite`) tem um desempenho muito melhor, pelo fato de que na sua implementação é criado um buffer com os caracteres que serão gravados, antes de eles serem efetivamente gravados.

## 5. Demonstração

Na pasta `demo` está incluso um pequeno programa e os arquivos resultantes de sua execução para demonstrar a diferença entre esses dois métodos. Esse programa utiliza a função fork() para ter dois processos escrevendo em um mesmo arquivo de forma simultânea

O arquivo `demo_fputc` foi criado utilizando a função fputc, nele podemos ver o seguinte conteúdo:

`aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb`
    
Já o arquivo `demo_write` foi criado utilizando a syscall write, e nele podemos ver o seguinte:

`aaaaaaaaaaaaaaaaaaaaabababababababababababababababababbabababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababbbbbbbbbbbbbbbbbbbb`

A diferença é clara, no primeiro arquivo a gravação ocorreu de forma mais ordenada, pois todos os caracteres do loop foram colocados em uma `stream`. Essa `stream` que é o que será gravado no arquivo, utilizando apenas uma chamada de sistema para todos os caracteres.

No segundo arquivo os caracteres foram gravados de forma desorganizada, praticamente alternada, a cada iteração do `for`. Essa segunda forma é mais lenta pois a cada iteração o processo precisa aguardar que o SO confirme a gravação. Nesse momento pode ocorrer uma mudança de contexto e o fork filho faz sua gravação, logo após o caractere inserido pelo processo pai.

## 6. Implementações

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
 
## 7. Referências
    
    https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_72/rtref/fputc.htm
    https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_72/apis/write.htm
    http://www.gnu.org/software/libc/manual/html_node/Stream-Buffering.html
    https://code.woboq.org/userspace/glibc/sysdeps/unix/sysv/linux/write.c.html
    https://code.woboq.org/userspace/glibc/libio/fputc.c.html
    https://ark.intel.com/PT-BR/products/65700/Intel-Core-i3-3110M-Processor-3M-Cache-2_40-GHz
    https://www.amd.com/pt/products/cpu/amd-ryzen-3-1300x

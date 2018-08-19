# Avaliação de desempenho em termo de speedup

Comparar as Duas estratégias (syscalls e funções).

Método de cópia: 1 bloco de cada vez


## 1. Métodos utilizados para análise
### a. Criação de arquivos

Foram primeiro criados 4 arquivos, de acordo com a tabela:

| Arquivo  	| Tamanho (bytes)| 
|----------	|------------	|
| File1.in 	| 1          	|
| File2.in 	| 1024       	|
| File3.in 	| 1048576    	|
| File4.in 	| 1073741824 	|

Esse procedimento foi repetido 10 vezes para cada arquivo:
- 5 utilizando funções de manipulação de arquivo 
- 5 utilizando syscalls para gravaçãO em arquivo

Pseudocódigo da gravação em arquivo:

    Enquanto (cont < tamanho_arquivo)
        escreva('A', file); cont++;
        
Utilizando a função gettimeofday() foram obtidos os tempos de execução para que fosse tirada uma média das 5 execuções.

### b. Copia de arquivos:

Utilizando os arrquivos anteriores foi feito o processo de cópia, também 10 vezes para cada arquivos:
- 5 utilizando funções de manipulação de arquivo
- 5 utilizando syscalls para cópia do arquivo

Psudocódigo cópia de arquivo
    
    Enquanto (c = leia(input) != EOF)
        escreva(c, output);
       
Utilizando a função gettimeofday() foram obtidos os tempos de execução para que fosse tirada uma média das 5 execuções.       


## 2. Resultados
### a. Configuração
    Linux Manjaro
    Intel Core i3 3310m 2.4GHz
    6GB RAM DDR3 1600MHz
    HDD 320GB 5400 RPM
    
#### Criação dos arquivos usando funções

| Arquivo  	| tamanho    	| Tempo Médio |
|----------	|------------	|------------	|
| File1.in 	| 1          	| 0,0000032  	|
| File2.in 	| 1024       	| 0,0000102  	|
| File3.in 	| 1048576    	| 0,0084248  	|
| File4.in 	| 1073741824 	| 11,3113002 	|

#### Criação dos arquivos usando syscalls

| Arquivo  	| tamanho    	| Tempo Médio |
|----------	|------------	|------------	|
| File1.in 	| 1          	| 0,  	|
| File2.in 	| 1024       	| 0,  	|
| File3.in 	| 1048576    	| 0,  	|
| File4.in 	| 1073741824 	| 0   	|

### Cópia de arquivos usando funções

| Arquivo  	| tamanho    	| Tempo Médio|
|----------	|------------	|-----------	|
| File1.in 	| 1          	| 0,0000098 	|
| File2.in 	| 1024       	| 0,0000214 	|
| File3.in 	| 1048576    	| 0,0110352 	|
| File4.in 	| 1073741824 	| 14,375128 	|

#### Cópia de arquivos usando syscalls

| Arquivo  	| tamanho    	| Tempo Médio  |
|----------	|------------	|-------------	|
| File1.in 	| 1          	| 0,000016    	|
| File2.in 	| 1024       	| 0,0035406   	|
| File3.in 	| 1048576    	| 2,1966092   	|
| File4.in 	| 1073741824 	| 2651,520801 	|


 ## 4. Explicação do resultados (por que o desempenho varia)
 - Referências pesquisa

       thelinuxdocumentationproject
       tldp.org


### Desktop
    Windows 10 Pro
    AMD Ryzen 3 1300x 3.5GHz
    12GB RAM DDR4 2400MHz
    SSD 480GB 6Gb/s
    HDD 750GB 5400 RPM


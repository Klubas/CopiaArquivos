# Avaliação de desempenho em termo de speedup

Comparar as Duas estratégias (syscalls e funções).

Método de cópia: 1 bloco de cada vez


## 1. Métodos utilizados para análise
### a. Criação de arquivos

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

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in   |
|-------------|-----------|-----------|-----------|------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824 |
| Tempo Médio | 0.0000028 | 0.0000084 | 0.0066086 | 16.3184658 |

#### Criação dos arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in | File4.in    |
|-------------|-----------|-----------|----------|-------------|
| Tamanho     | 1         | 1024      | 1048576  | 1073741824  |
| Tempo Médio | 0.0000036 | 0.0010324 | 1.077748 | 1134.490509 |

### Cópia de arquivos usando funções

| Arquivo     | File1.in  | File2.in | File3.in  | File4.in   |
|-------------|-----------|----------|-----------|------------|
| Tamanho     | 1         | 1024     | 1048576   | 1073741824 |
| Tempo Médio | 0.0032038 | 0.000058 | 0.0233158 | 15.2322186 |

#### Cópia de arquivos usando syscalls

| Arquivo     | File1.in  | File2.in  | File3.in  | File4.in    |
|-------------|-----------|-----------|-----------|-------------|
| Tamanho     | 1         | 1024      | 1048576   | 1073741824  |
| Tempo Médio | 0.0000062 | 0.0016586 | 1.7209822 | 1868.473657 |

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


# Avaliação de desempenho em termo de speedup

Comparar as Duas estratégias (syscalls e funções).

Método de cópia: 1 bloco de cada vez

### 1. Criar arquivos:

Repetir 5x o procedimento de criar arquivo e anotar os resultados (tempos) e fazer média

4 Arquivos:

 >   1 Byte
 >
 >   1024 Bytes
 >
 >   1024 * 1024
 >
 >   1024 * 1024  * 1024

    Enquanto (cont < tamanho_arquivo)
        fputc("A")

### 2. Copiar 4 arquivos:

Repetir 5x o procedimento de cópia e anotar os resultados (tempos) e fazer média
    
    file.in -> file.out

### 3. Resultados
- Conf Máquina (Hardware/Software)
- Média de tempos (5x) p/ 4 tamanhos de arquivos
    - Criar arquivos
    - Copiar arquivos
 
 ### 4. Explicação do resultados (por que o desempenho varia)
 - Referências pesquisa

       thelinuxdocumentationproject
       tldp.org
 
## Configuração
### Notebook 
    Linux Manjaro
    Intel Core i3 3310m 2.4GHz
    6GB RAM DDR3 1600MHz
    HDD 320GB 5400 RPM


### Desktop
    Windows 10 Pro
    AMD Ryzen 3 1300x 3.5GHz
    12GB RAM DDR4 2400MHz
    SSD 480GB 6Gb/s
    HDD 750GB 5400 RPM


#### TODO
criarArquivo(); //todos os parametros de MeuArquivo

calculaTempoCopiar(); //so renomear calculaTempo

calculaTempoCriar(); //calcular tempo médio de criação de arquivos e gravar em .csv

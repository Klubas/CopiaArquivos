# Avaliação de desempenho em termo de speedup

Comparar as Duas estratégias (syscalls e funções).
Método de cópia: 1 bloco de cada vez

### 1. Criar arquivos:
4 Arquivos:
    1 Byte
    1024 Bytes 1k
    1024 * 1024 Bytes 1mb
    1024 * 1024  * 1024 Bytes 1gb

Repetir 5x e anotar os resultados (tempos) e fazer média

    Enquanto (cont < tamanho_arquivo)
        fputc("A")

### 2. Copiar 4 arquivos:
    file.in -> file.out
Repetir 5X e anotar os resultados (tempo) e fazer média

-> Conf Máquina (Hardware/Software)
-> Média de tempos (5x) p/ 4 tamanhos de arquivos
1 Criar arquivos
2 Copiar arquivos

### 3. Explicação do resultados (por que o desempenho varia)
-> Referências pesquisa

thelinuxdocumentationproject
tldp.org

## Resultados

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



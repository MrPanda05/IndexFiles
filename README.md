# Trabalho indice invertido

Feito por: Gabriel Alexsander da Costa Pereira

[github](https://github.com/MrPanda05/IndexFiles)

## Como Compilar

### Opção 1:

rode o makefile com o comando

#### Make
```
make
```
ou

#### Mingw32-make
```
mingw32-make
```

O executavel dese se chamar main

### Opção 2(windows only):

1. Abra a solução do visual studio
2. Compile com Control + shift + b

O executavel deve se chamar IndexFiles

## Como executar

### No console, siga as instruções abaixo
#### Indexação

1. ./NomeDoExecutavel indice construir <caminho>

O caminho pode ser global ou relativo, é recomendavel usar o caminho global.

A indexeção não é destrutiva, ou seja, os arquivos originais não sao re-escritos, mas os arquivos processados podem ser vistos em "bin/ProcessedFiles"

#### Busca

1. ./NomeDoExecutavel busca <lista_de_palavras>
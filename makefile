# o arquivo makefile serve para automatizar o processo de compilação do programa, evitando a necessidade de digitar comandos longos no terminal toda vez que quisermos compilar o código
# declaração das variáveis para o compilador, flags de compilação, arquivos fonte e teste
CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude 
SRC     = src/story.c src/character.c src/stack.c src/queue.c src/fsm.c src/enemies.c src/ui.c src/combat.c
MAIN    = src/main.c
TEST    = src/test.c
 # Makefile é usado para compilar o programa de teste(alvo "test") e para limpar os arquivos compilados(alvo "clean")
 #com o comando "make test" no terminal, e o comando "make clean" para remover o executável gerado, deixando o diretório limpo
 # make all, pra rodar o teste, e make clean, pra limpar os arquivos compilados
all: $(SRC) $(MAIN)
	$(CC) $(CFLAGS) $(SRC) $(MAIN) $(LIBS) -o RPG
clean:# comando puro do terminal para remover o arquivo executável gerado
	rm -f RPG
 
# ./main

CC = clang # Compilador
CFLAGS = -g -Wall -Wextra -pedantic # Flags de compilação: -g (debug), -Wall (todos os warnings), -Wextra (warnings extras), -pedantic (conformidade com o padrão C).
LDFLAGS = -pthread -lm # Flags para o linker (bibliotecas).

# Encontra todos os arquivos .c (exclui diretórios .ccls-cache)
SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
# Substitui a extensão .c por .o para obter os nomes dos arquivos objeto
OBJS = $(SRCS:.c=.o)

TARGET = main # Nome do executável principal

# Objetivo padrão: compilar o executável
all: $(TARGET)

# Regra para construir o executável a partir dos arquivos objeto
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Regra para compilar cada arquivo .c em um arquivo .o
# $<: nome do primeiro pré-requisito (o arquivo .c)
# $@: nome do objetivo (o arquivo .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Objetivo para compilação de depuração (mantém a otimização em 0 para melhor depuração)
main-debug: CFLAGS += -O0 # Adiciona -O0 às flags apenas para este objetivo
main-debug: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Limpeza: remove todos os arquivos objeto e os executáveis
clean:
	rm -f $(OBJS) $(TARGET) main-debug
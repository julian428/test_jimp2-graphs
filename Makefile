CC = gcc
CFLAGS = -Wextra -g
LDFLAGS = -lcurl -lcjson

SRC = main.c lib/file-check.c lib/utils.c lib/config.c
OBJ = $(SRC:.c=.o)
EXEC = graph_test

all: $(EXEC)

$(EXEC): $(OBJ)
	nix-shell --run "$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)"

%.o: %.c
	nix-shell --run "$(CC) $(CFLAGS) -c $< -o $@"

clean:
	rm -rf test_inputs/* *.png *.txt $(EXEC) $(OBJ) $(EXEC)

CC = gcc
CFLAGS = -Wextra -g
LDFLAGS = -lcurl -lcjson -lm

SRC = main.c lib/file-check.c lib/utils.c lib/config.c lib/log.c
OBJ = $(patsubst %.c,bin/%.o,$(SRC))
EXEC = bin/graph_test
SUBMODULE = jimp2-graphs

all: $(EXEC)

$(EXEC): $(OBJ) | bin
	nix-shell --run "$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)"

# Ensure object files go to bin/, creating necessary subdirectories
bin/%.o: %.c | bin_dirs
	nix-shell --run "$(CC) $(CFLAGS) -c $< -o $@"

# Create bin and bin/lib directories as needed
bin_dirs:
	mkdir -p bin bin/lib

clean:
	rm -rf test_inputs bin logs

sub:
	nix-shell --run "make -C $(SUBMODULE)"

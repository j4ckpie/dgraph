dgraph: $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
	gcc -Wall -Wextra -O2 -o dgraph $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))

src/%.o: src/%.c
	gcc -Wall -Wextra -O2 -c $< -o $@

clean:
	rm -f src/*.o dgraph
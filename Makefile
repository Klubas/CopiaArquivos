default: ./src/copia.c
	mkdir bin
	gcc -o ./bin/copia ./src/copia.c
run:
	./bin/copia && ./src/clean.sh `hostname`
clean:
	rm -rf ./bin/copia && ./src/clean.sh

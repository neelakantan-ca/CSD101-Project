
COMPILER = gcc
CFLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code

final: main.o
	@$(COMPILER) $(CFLAGS) ./output/objects/main.o -o ./output/main
	@chmod +x ./output/main

main.o: ./src/main.c 
	@mkdir -p ./output/objects/
	@$(COMPILER) $(CFLAGS) -c ./src/main.c -o ./output/objects/main.o

clean:
	@echo "Removing all temporary files"
	rm -f ./output/objects/*
	rm -f ./output/project.zip

zip:
	zip ./output/project.zip ./src/*.c

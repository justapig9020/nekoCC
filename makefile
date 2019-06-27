main: main.c scanner.c struct.c alert.c parser.c
	gcc -o nekoCC main.c scanner.c struct.c alert.c parser.c
test: main1.c scanner.c 
	gcc -o main1 main1.c scanner.c 

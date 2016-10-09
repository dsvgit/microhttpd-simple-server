all: ./src/main.c
	gcc ./src/main.c ./src/router.c -o ./dist/main -I/usr/local/lib -L/usr/local/lib -lmicrohttpd
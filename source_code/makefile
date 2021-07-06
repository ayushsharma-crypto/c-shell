# main:
# 	gcc -g main.c ./cmds/prompt.c ./cmds/execution.c ./cmds/setup.c ./cmds/builtin.c  ./cmds/cd.c  ./cmds/pwd.c  ./cmds/pinfo.c  ./cmds/echo.c  ./cmds/history.c -o run_shell


CFLAGS = -g

run_shell: main.o prompt.o pwd.o cd.o echo.o pinfo.o history.o builtin.o setup.o execution.o
	gcc -o run_shell $(CFLAGS) main.o prompt.o pwd.o cd.o echo.o pinfo.o history.o  builtin.o setup.o execution.o

clean:
	rm -f *.o run_shell

main.o: main.c  ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c main.c

builtin.o: ./cmds/builtin.c ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/builtin.c

cd.o: ./cmds/cd.c  ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/cd.c

echo.o: ./cmds/echo.c  ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/echo.c

execution.o: ./cmds/execution.c ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/execution.c

history.o: ./cmds/history.c  ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/history.c

pinfo.o: ./cmds/pinfo.c  ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/pinfo.c

prompt.o: ./cmds/prompt.c ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/prompt.c

pwd.o: ./cmds/pwd.c  ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/pwd.c

setup.o: ./cmds/setup.c ./headers/header.h ./headers/execution.h ./headers/prompt.h
	gcc $(CFLAGS) -c ./cmds/setup.c

#OBJS = main.o salida.o calculadora.o 

OBJS = ./cmd_utils.o ./sig_handlers.o ./redirectIO.o
BINARY  = myshell 

CFLAGS = -g -Wall -Werror -pedantic
#La opcion -g hace que el compilador le agregue al binario informacion\
#extra que se va a utilizar para debugger, por ejemplo con GDB

#all: programa

#Esta regla compila el programa principal
myshell: $(OBJS) 
	gcc $(CFLAGS) myshell.c -o myshell ./cmd_utils.o ./exec.o ./sig_handlers.o redirectIO.o
	./myshell
	
cmd_utils.o:  ./cmd_utils.h ./cmd_utils.c ./exec.o
	gcc $(CFLAGS) -c ./cmd_utils.c 

exec.o: ./exec.c ./exec.h
	gcc $(CFLAGS) -c ./exec.c

sig_handlers.o: ./sig_handlers.c ./sig_handlers.h
	gcc $(CFLAGS) -c ./sig_handlers.c 

redirectIO.o: ./redirectIO.c ./redirectIO.h ./cmd_utils.o
	gcc $(CFLAGS) -c ./redirectIO.c 
	
clean: 
	rm -f $(BINARY) $(OBJS)
	rm -f *.o
#	ls | grep -v "\." | xargs rm #to remove all executables
# 	WARNING: The last command also removes the Makefile

celan: 
	rm -f $(BINARY) $(OBJS)
	rm -f *.o
#	ls | grep -v "\." | xargs rm #to remove all executables
# 	WARNING: The last command also removes the Makefile
a : main.o func.o 
	gcc -o a main.o func.o 
main.o : main.c list.h
	gcc -c main.c
func.o : func.c list.h
	gcc -c func.c
clean :
	del a.exe main.o func.o 

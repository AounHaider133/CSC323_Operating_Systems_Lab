FA21_BSE_133.exe: q1.o libmystaticlib.a
	gcc -o FA21_BSE_133.exe q1.o -L. -lmystaticlib

q1.o: q1.c
	gcc -c q1.c 

handler.o: handler.c
	gcc -c handler.c

libmystaticlib.a: handler.o
	ar cr libmystaticlib.a handler.o

clean:
	rm *.o libmystaticlib.a

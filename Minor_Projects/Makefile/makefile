CC = gcc
OBJECTS = mystrings.o Person.o NameAge.o


final: $(OBJECTS)
	$(CC) $(OBJECTS) -o final

mystrings.o: mystrings.c mystrings.h boolean.h
	$(CC) -c mystrings.c

Person.o: Person.c Person.h
	$(CC) -c Person.c

NameAge.o: NameAge.c Person.h
	$(CC) -c NameAge.c

run: 
	./final

edit:
	>makefile ; vim makefile

clean:
	rm -f final $(OBJECTS) *.bak *~



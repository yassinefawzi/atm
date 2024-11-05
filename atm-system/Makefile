objects = src/main.o src/system.o src/auth.o

atm : $(objects)
	gcc -o atm $(objects)

clean :
	rm -f $(objects)
fclean :
	rm -f $(objects) atm
re :	fclean atm
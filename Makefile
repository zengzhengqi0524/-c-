CC = cc
objects = test.o menu.o  

test : $(objects) test.o 
	$(CC) -o test $(objects)

$(objects): menu.h

.PHONY : clean
clean :
	rm main $(objects)




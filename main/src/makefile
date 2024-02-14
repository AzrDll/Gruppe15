CC=gcc
CFLAGS=-I.
DEPS = stb_image.h	stb_image_write.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean	

clean:
	rm -f *.o main
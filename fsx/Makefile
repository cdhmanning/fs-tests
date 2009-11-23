
CFLAGS =    -Wall -g 
CFLAGS +=    -O0


ALLOBJS = fsx-linux.o

all: fsx

$(ALLOBJS): %.o: %.c
	gcc -c $(CFLAGS) -o $@ $<


fsx: $(ALLOBJS)
	gcc -o $@ $(ALLOBJS)


clean:
	rm fsx $(ALLOBJS)

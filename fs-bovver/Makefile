CFLAGS =    -Wall -g 
CFLAGS +=    -O0

#CFLAGS+=   -Wshadow -Wpointer-arith -Wwrite-strings -Wstrict-prototypes -Wmissing-declarations
#CFLAGS+=   -Wmissing-prototypes -Wredundant-decls -Wnested-externs -Winline


ALLOBJS = fs-bovver.o bovver.o

all: fs-bovver

$(ALLOBJS): %.o: %.c
	gcc -c $(CFLAGS) -o $@ $<


fs-bovver: $(ALLOBJS)
	gcc -o $@ $(ALLOBJS) -lpthread


clean:
	rm fs-bovver $(ALLOBJS)

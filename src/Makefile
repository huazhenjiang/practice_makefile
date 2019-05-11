
objects := $(patsubst %.c,%.o,$(wildcard *.c))
foo : $(objects)
	cc -o foo $(objects)

.PHONY: clean

clean:
	rm -rf *.o foo


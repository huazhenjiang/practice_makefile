
objects := $(patsubst %.c,%.o,$(wildcard *.c))
$(FINAL_TARGET) : $(objects)
	cc -o $(FINAL_TARGET) $(objects)

main.o: include/base64.h include/str_reverse.h include/strcat_imp.h
.PHONY: clean

clean:
	rm -rf *.o $(FINAL_TARGET)



objects := $(patsubst %.c,%.o,$(wildcard *.c))
$(FINAL_TARGET) : $(objects)
	cc $(CFLAGS) $^ -o $@
	strip $(FINAL_TARGET)
	cp $(FINAL_TARGET) ../bin
	#cc -c need to match with dependency *.c, not *.o
	#cc -c $(CFLAGS) -o $@ $^
	#all of dependency file here are *.o

main.o: ../include/base64.h ../include/str_reverse.h ../include/strcat_imp.h
.PHONY: clean

clean:
	rm -rf *.o $(FINAL_TARGET)


PROJ_ROOT        := $(shell pwd)
APP_SOURCES = src/main.c
LIBS_SOURCES = src/base64.c src/strcat_imp.c src/str_reverse.c
SOURCE_DIR = src/$(wildcard *.o)

CFLAG = -Wall -Wextra
HEADERS = $(PROJ_ROOT)/include/$(wildcard *.h)
OBJECTS = $(APP_SOURCES:.c=.o) $(LIBS_SOURCES:.c=.o)
#OBJECTS = $(SOURCE_DIR:.c=.o)

FINAL_TARGET=all

all: $(OBJECTS)
	gcc -I $(HEADERS) -o $(FINAL_TARGET) $(OBJECTS)


#OBJECTS = ./$(wildcard *.o)
#objects=main.o base64.o strcat_imp.o str_reverse.o

#all: $(APP_SOURCES)/%.o
#	gcc -o $@ $(APP_SOURCES)/%.o
#main.o: maic.c base64.o strcat_imp.o str_reverse.o base64.h strcat_imp.h str_reverse.h

#main.o: main.c
#	gcc -c main.c
#base64.o: base64.c
#strcat_imp: strcat_imp.c
#str_reverse.o: str_reverse.c

#*.o : $(APP_SOURCES)/*.c

#$(APP_SOURCES)/%.o: $(APP_SOURCES)/%.c
#	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -f src/*.o $(FINAL_TARGET) 

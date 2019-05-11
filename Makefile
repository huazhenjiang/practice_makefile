PROJ_ROOT        := $(shell pwd)
INC = -I $(PROJ_ROOT)/include
LIB = -L $(PROJ_ROOT)/lib
CFLAG += -Wall -Wextra
FINAL_TARGET=all

COMP_TYPE = 0

ifeq ($(COMP_TYPE),1)
APP_SOURCES = src/main.c
LIBS_SOURCES = src/base64.c src/strcat_imp.c src/str_reverse.c
HEADERS := $(PROJ_ROOT)/include
OBJECTS = $(APP_SOURCES:.c=.o) $(LIBS_SOURCES:.c=.o)

$(FINAL_TARGET): $(OBJECTS)
	echo "$(HEADERS)\n"
	echo "$(OBJECTS)\n"
	gcc -I $(HEADERS) $(CFLAG) -o $(FINAL_TARGET) $(OBJECTS)
else

SOURCE_C = src
objects := $(patsubst $(SOURCE_C)/%.c, $(SOURCE_C)/%.o,$(wildcard $(SOURCE_C)/*.c))

$(FINAL_TARGET): $(objects)
	cc $(INC) $(CFLAG) -o $(FINAL_TARGET) $(objects)
endif

main.o: include/base64.h include/str_reverse.h include/strcat_imp.h



.PHONY: clean
clean:
	rm -f src/*.o $(FINAL_TARGET) 

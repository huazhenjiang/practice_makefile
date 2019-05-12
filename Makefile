PROJ_ROOT        := $(shell pwd)
INC = -I $(PROJ_ROOT)/include
LIB = -L $(PROJ_ROOT)/lib
CFLAGS += -Wall -Wextra
BUILD_DIR = $(PROJ_ROOT)/out
FINAL_TARGET=$(BUILD_DIR)/all

COMP_TYPE = 3
export PROJ_ROOT INC LIB CFLAGS BUILD_DIR FINAL_TARGET

ifeq ($(COMP_TYPE),1)
APP_SOURCES = src/main.c
LIBS_SOURCES = src/base64.c src/strcat_imp.c src/str_reverse.c
HEADERS := $(PROJ_ROOT)/include
OBJECTS = $(APP_SOURCES:.c=.o) $(LIBS_SOURCES:.c=.o)

$(FINAL_TARGET): $(OBJECTS)
	echo "$(HEADERS)\n"
	echo "$(OBJECTS)\n"
	gcc -I $(HEADERS) $(CFLAGS) -o $(FINAL_TARGET) $(OBJECTS)

else ifeq ($(COMP_TYPE), 2)


SOURCE_C = src
objects := $(patsubst $(SOURCE_C)/%.c, $(SOURCE_C)/%.o,$(wildcard $(SOURCE_C)/*.c))

$(FINAL_TARGET): $(objects)
	cc $(INC) $(CFLAGS) -o $(FINAL_TARGET) $(objects)
else

$(FINAL_TARGET): init  opsrc
	echo "$(opsrc)"

init:
	mkdir -p $(PROJ_ROOT)/out
opsrc:
	#make -C src -f Makefile
	make -C src
clean_opsrc:
	make -C src -f Makefile clean 

endif


.PHONY: clean
clean:
	rm -rf src/*.o $(BUILD_DIR) 

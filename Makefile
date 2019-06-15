PROJ_ROOT        := $(shell pwd)
INC = -I $(PROJ_ROOT)/include
LIB = -L $(PROJ_ROOT)/lib
CFLAGS += -Wall -Wextra
BUILD_DIR = $(PROJ_ROOT)/out
FINAL_TARGET=$(BUILD_DIR)/all

COMP_TYPE = 3
i=0
FUN_file= file 
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

filtersources := foo.c bar.c baz.s ugh.h
filterout = foo.c bar.c
wordpool = aa.c bb.c dd.o ee.o ff.c vv.k

obj1=111 222 333
obj2=aaa bbb ccc ddd

$(FINAL_TARGET): init  opsrc
	echo "$(opsrc)"

init:
	mkdir -p $(PROJ_ROOT)/bin
	mkdir -p $(PROJ_ROOT)/out
opsrc:
	#make -C src -f Makefile
	make -C src
test_make_function:
	#----------word-------------------
	echo "$i.subst $(subst ee,EE,feet on the street)"
	echo "$i.sort $(sort aa zz bb)"
	echo "$i.strip $(strip a b c )"
	echo "patsubst $(patsubst %.c,%.op,x.c.c bar.c)"
	echo "findstring $(findstring a,a b c)"
	echo "findstring none $(findstring a,b c)"
	echo "filter $(filter %.c %.s,$(filtersources))"
	echo "filter-out $(filter-out $(filterout),$(filtersources))"
	echo "word $(word 1, foo bar baz)"
	echo "word $(word 2, $(filtersources))"
	echo "wordlist $(wordlist 2, 9,$(wordpool))"
	echo "words $(words $(wordpool))"
	echo "firstword $(firstword $(wordpool))"
	#---------dir--------------------
	echo "dir $(dir src/foo.c hacks)"
	echo "notdir $(notdir src/foo.c hacks)"
	echo "suffix $(suffix $(wordpool))"
	echo "basename $(basename $(wordpool))"
	echo "addsuffix $(addsuffix .pp, $(wordpool))"
	echo "addprefix $(addprefix test_,$(wordpool))"
	echo "join $(join $(obj1),$(obj2))"
clean_opsrc:
	make -C src -f Makefile clean 

endif


.PHONY: clean
clean:
	rm -rf src/*.o $(BUILD_DIR)/ 

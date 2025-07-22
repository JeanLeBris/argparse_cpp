export OS
export CC=g++
export CFLAGS=
export LDFLAGS=
export EXEC=argparse
SRCNAMES= argparse.cpp
export SRCDIR=src
SRC= $(foreach srcname, $(SRCNAMES), $(SRCDIR)/$(srcname))
OBJNAMES= $(SRCNAMES:.cpp=.o)
export OBJDIR=obj
OBJ= $(foreach objname, $(OBJNAMES), $(OBJDIR)/$(objname))
export BINDIR=bin
export DEPENDENCIES= deallocator

EXAMPLESDIR=examples
# EXAMPLENAMES= example_1.cpp example_2.cpp example_3.cpp
# EXAMPLES= $(foreach examplename, $(EXAMPLENAMES), $(EXAMPLESDIR)/$(examplename))
# EXAMPLESEXE= $(EXAMPLES:.cpp=.exe)

ifeq ($(OS), Windows_NT)
	RMDIR= rmdir
	RMFILE= del /s /q
	COPYFILE= copy
	SHARED_LIBRARY_EXT= dll
	FILE_SLASH=\\

else
ifeq ($(OS), Linux)
	RMDIR= rmdir
	RMFILE= rm
	COPYFILE= cp
	SHARED_LIBRARY_EXT= so
	FILE_SLASH=/
endif
endif

export RMDIR
export RMFILE
export COPYFILE
export SHARED_LIBRARY_EXT
export FILE_SLASH

ifeq ($(LIBRARY_TYPE), shared)
else
	ifeq ($(LIBRARY_TYPE), static)
	else
		LIBRARY_TYPE=shared
	endif
endif
export LIBRARY_TYPE

compile:bin obj update $(OBJNAMES)
ifeq ($(LIBRARY_TYPE), shared)
	$(CC) -fpic -shared $(OBJ) -L $(BINDIR) -l deallocator -o $(BINDIR)/lib$(EXEC).$(SHARED_LIBRARY_EXT)
endif
ifeq ($(LIBRARY_TYPE), static)
	ar rcs $(BINDIR)/lib$(EXEC).a $(OBJ)
endif

examples:compile
	@(cd $(EXAMPLESDIR) && $(MAKE) $@)
# 	cp $(BINDIR)/libargparse.dll $(EXAMPLESDIR)/$(BINDIR)/libargparse.dll

update:
	git submodule update --recursive --remote
# 	$(CC) -c ./lib/deallocator/src/deallocator.cpp -o ./obj/deallocator.o
# # 	ar rcs ./bin/libdeallocator.a ./obj/deallocator.o
# 	$(CC) -fpic -shared ./obj/deallocator.o -o ./bin/libdeallocator.dll
	@(cd ./lib/deallocator && $(MAKE) compile)
	$(COPYFILE) .$(FILE_SLASH)lib$(FILE_SLASH)deallocator$(FILE_SLASH)bin$(FILE_SLASH)* bin

%.o:
	$(CC) -c $(SRCDIR)/$(@:.o=.cpp) -o $(OBJDIR)/$@

.PHONY: compile examples clean

# examples:example_1 example_2 example_3

# example_1:update argparse.o
# 	g++ -c ./examples/example_1.cpp -o ./obj/example_1.o
# # 	g++ ./obj/example_1.o -L ./bin -l argparse -l deallocator -o ./bin/example_1
# 	g++ ./obj/example_1.o -L ./bin -l argparse -o ./bin/example_1

# example_2:update argparse.o
# 	g++ -c ./examples/example_2.cpp -o ./obj/example_2.o
# # 	g++ ./obj/example_2.o -L ./bin -l argparse -l deallocator -o ./bin/example_2
# 	g++ ./obj/example_2.o -L ./bin -l argparse -o ./bin/example_2

# example_3:update argparse.o
# 	g++ -c ./examples/example_3.cpp -o ./obj/example_3.o
# # 	g++ ./obj/example_3.o -L ./bin -l argparse -l deallocator -o ./bin/example_3
# 	g++ ./obj/example_3.o -L ./bin -l argparse -o ./bin/example_3

# argparse.o:
# 	g++ -c ./src/argparse.cpp -o ./obj/argparse.o
# # 	ar rcs ./bin/libargparse.a ./obj/argparse.o
# 	g++ -fpic -shared ./obj/argparse.o -L ./bin -l deallocator -o ./bin/libargparse.dll

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	$(RMFILE) $(OBJDIR)$(FILE_SLASH)*
	$(RMDIR) $(OBJDIR)
	$(RMFILE) $(BINDIR)$(FILE_SLASH)*
	$(RMDIR) $(BINDIR)
	@(cd $(EXAMPLESDIR) && $(MAKE) $@)
	@(cd ./lib/deallocator && $(MAKE) $@)

all:
	echo $(SRC)
	echo $(OBJ)

SRCNAMES= example_1.cpp example_2.cpp example_3.cpp
SRC= $(foreach srcname, $(SRCNAMES), $(SRCDIR)/$(srcname))
OBJNAMES= $(SRCNAMES:.cpp=.o)
OBJ= $(foreach objname, $(OBJNAMES), $(OBJDIR)/$(objname))

examples: obj bin $(OBJNAMES)
	$(COPYFILE) ..\$(BINDIR)\* .\$(BINDIR)

%.o:
	$(CC) -c $(SRCDIR)/$(@:.o=.cpp) -o $(OBJDIR)/$@
	$(CC) $(OBJDIR)/$@ -L  ../$(BINDIR) -l $(EXEC) -o $(BINDIR)/$(@:.o=.exe)
# 	g++ ./obj/example_1.o -L ./bin -l argparse -o ./bin/example_1

.PHONY: examples

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	$(RMFILE) $(OBJDIR)
	$(RMDIR) $(OBJDIR)
	$(RMFILE) $(BINDIR)
	$(RMDIR) $(BINDIR)
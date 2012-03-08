#Makefile to build the parser
CXXFLAGS += -Wno-write-strings


$(BINDIR)/parser: $(addprefix $(OBJDIR)/, parser.o ast.o environment.o y.tab.o lex.yy.o)
	$(CXX)  $^ -o $@

$(OBJDIR)/parser.o: $(addprefix $(PARSERDIR)/, parser.cc parser.hh lexer.hh) \
                    $(addprefix $(GENDIR)/, y.tab.h)
	$(CXX) -c $< $(CXXFLAGS) -o $@ -I$(GENDIR) -I$(PARSERDIR)

$(OBJDIR)/ast.o: $(addprefix $(PARSERDIR)/, ast.cc ast.hh)
	$(CXX) -c $< $(CXXFLAGS) -o $@ -I$(PARSERDIR)

$(OBJDIR)/environment.o: $(addprefix $(PARSERDIR)/, environment.cc environment.hh)
	$(CXX) -c $< $(CXXFLAGS) -o $@ 

$(OBJDIR)/y.tab.o: $(GENDIR)/y.tab.c
	$(CXX) -c $< -o $@ -I$(PARSERDIR)

$(addprefix $(GENDIR)/, y.tab.h y.tab.c): $(PARSERDIR)/parser.y
	$(YACC) -d $<
	mv y.tab.c Gen
	mv y.tab.h Gen

$(OBJDIR)/lex.yy.o: $(GENDIR)/lex.yy.c
	$(CXX) -c $< -o $@ -I$(PARSERDIR)

$(GENDIR)/lex.yy.c: $(PARSERDIR)/lexer.l
	$(LEX) -o $@ $<


.PHONY: clean-parser
clean-parser:
	rm $(GENDIR)/y.tab.h $(GENDIR)/y.tab.c $(GENDIR)/lex.yy.c $(OBJDIR)/parser.o \
           $(BINDIR)/parser $(OBJDIR)/y.tab.o $(OBJDIR)/lex.yy.o $(OBJDIR)/ast.o
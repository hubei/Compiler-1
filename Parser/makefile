#Makefile to build the parser
CXXFLAGS += -Wno-write-strings


$(BINDIR)/parser: $(OBJDIR)/parser.o
	$(CXX) -o $@ $^

$(OBJDIR)/parser.o: $(addprefix $(PARSERDIR)/, parser.cc parser.h) \
                    $(addprefix $(GENDIR)/,  lex.yy.c y.tab.c y.tab.h)
	$(CXX) -c $< $(CXXFLAGS) -o $@ -I$(GENDIR)

$(GENDIR)/y.tab.h: $(PARSERDIR)/parser.y
	$(YACC) -d -o $@ $<

$(GENDIR)/y.tab.c: $(PARSERDIR)/parser.y
	$(YACC) -o $@ $<

$(GENDIR)/lex.yy.c: $(PARSERDIR)/lexer.l
	$(LEX) -o $@ $<


.PHONY: clean-parser
clean-parser:
	rm $(GENDIR)/y.tab.h $(GENDIR)/y.tab.c $(GENDIR)/lex.yy.c $(OBJDIR)/parser.o \
           $(BINDIR)/parser

#Primary makefile for Ryan's compiler
TOPLEVEL = 1

#Global variables
CXX = g++
CXXFLAGS = -Wall -Wextra
#Directory Structure
ROOTDIR = $(realpath .)
PARSERDIR = $(ROOTDIR)/Parser
BINDIR = $(ROOTDIR)/Bin
OBJDIR = $(ROOTDIR)/Obj
GENDIR = $(ROOTDIR)/Gen
#Output
targets = $(addprefix $(BINDIR)/, parser)
directories = $(BINDIR) $(OBJDIR) $(GENDIR)


.PHONY: all
all: $(directories) $(targets)

include $(PARSERDIR)/makefile

$(BINDIR):
	mkdir Bin
$(OBJDIR):
	mkdir Obj
$(GENDIR):
	mkdir Gen


.PHONY: clean
clean: clean-parser
	rm -r $(BINDIR) $(OBJDIR) $(GENDIR)
PNAME=noentities
VERSION=1
MINOR_NUMBER=1

PNAMESTATIC=$(PNAME)s
PNAMEDYNAMIC=$(PNAME)
PNAMEDYNAMICLIB=$(PNAME)dl
LINKERNAME=lib$(PNAME).so
SONAME=$(LINKERNAME).$(VERSION)
REALNAME=$(SONAME).$(MINOR_NUMBER)


SRCDIR     = .
LETTERFUNCSDIR    = ../src
INCLUDEDIR = -I$(SRCDIR) -I$(LETTERFUNCSDIR)

CC=g++ $(INCLUDEDIR) -O3 -Wall -pedantic -DNDEBUG 

# -fPIC or -fpic: enable 'position independent code' generation. Necessary for shared libs
# -fpic may generate smaller and faster code, but will have platform-dependent limitations
PIC=-fPIC
#PIC=

CCLINKSTATIC=g++ -static
CCLINKDYNAMIC=g++ 
CCCREATELIB=g++ -shared -Wl,-soname,$(SONAME)

#DEBUG=-g
DEBUG=

GCCLINK=-L/usr/local/lib -lstdc++
RM=rm -f

PROJECTSRC=main.cpp $(LETTERFUNCSDIR)/entities.cpp $(LETTERFUNCSDIR)/letter.cpp $(LETTERFUNCSDIR)/letterfunc.cpp $(LETTERFUNCSDIR)/utf8func.cpp

PROJECTOBJS=main.o entities.o letter.o letterfunc.o utf8func.o

#                               #
#   Dependencies start here.    #
#                               #


$(PNAMEDYNAMIC): $(PROJECTOBJS)
	$(CCLINKDYNAMIC) $(PROJECTOBJS) -o $@ $(GCCLINK)

$(PNAMESTATIC): $(PROJECTOBJS)
	$(CCLINKSTATIC) $(PROJECTOBJS) -o $@ $(GCCLINK)

$(REALNAME) : $(PROJECTOBJS)
	$(CCCREATELIB) -o $@ $(PROJECTOBJS)
	ln -sf $(REALNAME) $(SONAME)
	ln -sf $(SONAME) $(LINKERNAME)

$(PNAMEDYNAMICLIB): $(REALNAME) $(PROJECTOBJS)
	$(CCLINKDYNAMIC) $(PROJECTOBJS) -L. -l $(PNAME) -o $@ $(GCCLINK)


all: $(PNAMESTATIC) $(PNAMEDYNAMIC) $(REALNAME) $(PNAMEDYNAMICLIB)

.cpp.o:
	$(CC) $(PIC) $(DEBUG) $(GCCINC) -c $(PROJECTSRC)

#.cpp.o:
#	$(CC) $(PIC) $(DEBUG) $(GCCINC) -c $?

clean:
	$(RM) *.o
	$(RM) $(LINKERNAME)
	$(RM) $(SONAME)
	$(RM) $(REALNAME)

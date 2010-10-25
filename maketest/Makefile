include Makefile.inc

DIRS	= subdir subdira
EXE	= mainx
OBJS	= main.o
OBJLIBS	= libsub.a libsuba.a libsubsub.a
LIBS	= -L. -lsub -lsuba -lsubsub

all : $(EXE)

$(EXE) : main.o $(OBJLIBS)
	$(ECHO) $(LD) -o $(EXE) $(OBJS) $(LIBS)
	$(LD) -o $(EXE) $(OBJS) $(LIBS)

libsub.a libsubsub.a : force_look
	$(ECHO) looking into subdir : $(MAKE) $(MFLAGS)
	cd subdir; $(MAKE) $(MFLAGS)

libsuba.a : force_look
	$(ECHO) looking into subdira : $(MAKE) $(MFLAGS)
	cd subdira; $(MAKE) $(MFLAGS)

clean :
	$(ECHO) cleaning up in .
	-$(RM) -f $(EXE) $(OBJS) $(OBJLIBS)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look :
	true
include ../Makefile.inc

CFLAGS	= $(PRJCFLAGS) -I..
OBJLIBS	= ../libsub.a ../libsubsub.a
OBJS	= sub1.o sub2.o sub3.o

all : $(OBJLIBS)

../libsub.a : $(OBJS)
	$(ECHO) $(AR) $(ARFLAGS) rv ../libsub.a $?
	$(AR) $(ARFLAGS) rv ../libsub.a $?
	$(ECHO) $(RANLIB) ../libsub.a
	$(RANLIB) ../libsub.a

../libsubsub.a : force_look
	$(ECHO) looking into subsubdir : $(MAKE) $(MFLAGS)
	cd subsubdir; $(MAKE) $(MFLAGS)

clean :
	$(ECHO) cleaning up in subdir
	-$(RM) -f $(OBJS)
	cd subsubdir; $(MAKE) $(MFLAGS) clean

force_look :
	true
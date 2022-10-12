
CC = CC -O

CFLAGS		= -I. -I.. -I$(DANCE_DIR)/libinclude

LDFLAGS		= -L. -L..

.SUFFIXES: .C

SRCS		= RAPID.C build.cxx collide.cxx overlap.cxx lmderBound.c

OBJECTS		= RAPID.o build.o collide.o overlap.o lmderBound.o

CLEAN		= sample_client $(OBJECTS) *.a *.o *~

TARGET = libRAPID.a



irix:
	@make -s 'CC=CC' 'OS=Irix' libRAPID 

Irix:
	@make -s 'CC=CC' 'OS=Irix' libRAPID 

linux:
	@make -s 'CC=g++' 'OS=Linux' libRAPID

Linux:
	@make -s 'CC=g++' 'OS=Linux' libRAPID

libRAPID: $(DANCE_DIR)/lib/$(OS)/$(TARGET)

$(DANCE_DIR)/lib/$(OS)/$(TARGET): $(OBJECTS)
	@ ar ruv libRAPID.a $(OBJECTS)
	@ mv libRAPID.a $(DANCE_DIR)/lib/$(OS)/$(TARGET)

.cxx.o:
	@ $(CC) ${CFLAGS} -c $<

.c.o:
	@ $(CC) ${CFLAGS} -c $<

%.o:%.cxx
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $<

test:
	$(CC) -o sample_client sample_client.cxx -L. -lRAPID -lm

clean:
	touch clean.a
	/bin/rm -f $(CLEAN)

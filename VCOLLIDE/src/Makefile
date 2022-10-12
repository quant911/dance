CFLAGS = -O

CC = CC

VC_TOP     = ..

INCLUDES = -I. -I$(VC_TOP)/RAPID

OBJS = NBody.o PairData.o VInternal.o VCollide.o AABB.o

TARGET = libVCollide.a

irix:
	@make -s 'CC=CC' 'OS=Irix' libVCollide

linux:
	@make -s 'CC=g++' 'OS=Linux' libVCollide

libVCollide: $(DANCE_DIR)/lib/$(OS)/$(TARGET)
$(DANCE_DIR)/lib/$(OS)/$(TARGET) : $(OBJS) 
	@ ar ruv $(TARGET) $(OBJS)
	@ mv $(TARGET)  $(DANCE_DIR)/lib/$(OS)/$(TARGET)

.cxx.o :
	echo $<
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $<

%.o:%.cxx
	echo $<
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $<


clean: 
	rm -f *.o $(TARGET)



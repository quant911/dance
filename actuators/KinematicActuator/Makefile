ACTUATOR = KinematicActuator
PLUGINS_DIR = ../../plugins

INCLUDES = -I$(DANCE_DIR)/src  -I/usr/local/include

OBJS = AnimationSequence.o KeyFrame.o

irix:
	@echo "Creating	Irix version KinematicActuator"
	@make 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(ACTUATOR).so

linux:
	@echo "Creating	Linux version KinematicActuator"
	@make 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(ACTUATOR).so


$(PLUGINS_OS_DIR)/$(ACTUATOR).so: $(OBJS) $(ACTUATOR).h	$(ACTUATOR).cxx	../../src/DActuator.h
	$(CC) $(CFLAGS)	$(LFLAGS) $(OBJS) $(ACTUATOR).cxx -o $(PLUGINS_OS_DIR)/$(ACTUATOR).so

%.o:%.cxx 
	$(CC) $(CFLAGS) -c $<
.cxx.o:
	$(CC) $(CFLAGS) -c $<

clean:
	\rm -f *.o *.so	*.a



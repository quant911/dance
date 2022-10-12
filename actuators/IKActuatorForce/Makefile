ACTUATOR = IKActuatorForce
PLUGINS_DIR = ../../plugins

INCLUDES = -I$(DANCE_DIR)/src -I$(DANCE_DIR)/libinclude  -I/usr/local/include \
	-I$(DANCE_DIR)/systems/ArticulatedObject

OBJS = list.o DOFrecord.o IK_Joint.o IKconstraint.o \
       IKdata.o  IKassembler.o IPose.o IPoseGraph.o \
       posConstraint.o orientConstraint.o

.cxx.o:
	$(CC) -c $(CFLAGS)	$(DEFINES) $<

%.o:%.cxx
	$(CC) -c $(CFLAGS)	$(DEFINES) $<
     
irix:
	@echo "Creating	Irix version of IKActuatorForce."
	@make 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(ACTUATOR).so

linux:
	@echo "Creating	Linux version of IKActuatorForce."
	@make 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(ACTUATOR).so


$(PLUGINS_OS_DIR)/$(ACTUATOR).so: $(OBJS) $(ACTUATOR).h	$(ACTUATOR).cxx	../../src/DActuator.h
	$(CC) $(CFLAGS)	$(LFLAGS) $(OBJS) $(ACTUATOR).cxx -o $(PLUGINS_OS_DIR)/$(ACTUATOR).so


clean:
	\rm -f *.o *.so *.a








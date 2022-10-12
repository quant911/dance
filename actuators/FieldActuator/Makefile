ACTUATOR = FieldActuator
PLUGINS_DIR = ../../plugins

INCLUDES = -I$(DANCE_DIR)/src -I$(DANCE_DIR)/libinclude  -I/usr/local/include

irix:
	@echo "Creating	Irix version of FieldActuator"
	@make 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(ACTUATOR).so

linux:
	@echo "Creating	Linux version of FieldActuator"
	@make 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(ACTUATOR).so


$(PLUGINS_OS_DIR)/$(ACTUATOR).so: $(ACTUATOR).h	$(ACTUATOR).cxx	../../src/DActuator.h
	$(CC) $(CFLAGS)	$(LFLAGS) $(ACTUATOR).cxx -o $(PLUGINS_OS_DIR)/$(ACTUATOR).so


clean:
	\rm -f *.o *.so *.a



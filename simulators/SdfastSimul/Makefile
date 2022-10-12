PLUGIN = SdfastSimul
PLUGINS_DIR = ../../plugins

INCLUDES = -I$(DANCE_DIR)/src -I$(DANCE_DIR)/libinclude  -I/usr/local/include

irix:
	@echo "Creating	Irix version of SdfastSimul"
	@make -s 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(PLUGIN).so

linux:
	@echo "Creating	Linux version of SdfastSimul"
	@make -s 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(PLUGIN).so


$(PLUGINS_OS_DIR)/$(PLUGIN).so: $(PLUGIN).h	$(PLUGIN).cxx	../../src/DSimulator.h
	$(CC) $(CFLAGS)	$(LFLAGS) $(PLUGIN).cxx -o $(PLUGINS_OS_DIR)/$(PLUGIN).so 


clean:
	\rm -f *.o *.so *.a



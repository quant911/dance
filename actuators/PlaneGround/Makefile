ACTUATOR = PlaneGround
PLUGINS_DIR = ../../plugins

INCLUDES = -I$(DANCE_DIR)/src  -I/usr/local/include -I$(DANCE_DIR)/libinclude

irix:
	@echo "Creating	Irix version of PlaneGround"
	@make 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262 -DIRIX' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(ACTUATOR).so

linux:
	@echo "Creating	Linux version of PlaneGround"
	@make 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(ACTUATOR).so


$(PLUGINS_OS_DIR)/$(ACTUATOR).so: $(ACTUATOR).h	$(ACTUATOR).cxx	../../src/DActuator.h \
	QuadMesh.cxx QuadMesh.h	Texture.cxx Texture.h
	$(CC) $(CFLAGS)	$(LFLAGS) $(ACTUATOR).cxx \
		QuadMesh.cxx Texture.cxx \
		-o $(PLUGINS_OS_DIR)/$(ACTUATOR).so

clean:
	\rm -f *.o *.so	*.a

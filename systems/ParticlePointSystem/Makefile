PLUGIN = ParticlePointSystem
PLUGINS_DIR = ../../plugins

INCLUDES =  \
	-I$(DANCE_DIR)/src  \
	-I$(DANCE_DIR)/libinclude  \
	-I$(DANCE_DIR)/VCOLLIDE/src \
	-I$(DANCE_DIR)/VCOLLIDE/RAPID \
	-I/usr/local/include
LIBS = -lm

OBJS = ParticlePointSystem.o ParticlePoint.o ParticlePointList.o

.cxx.o:
	@echo $<
	$(CC) $(CFLAGS)	-c $(CFLAGS) $<

%.o:%.cxx
	@echo $<
	$(CC) $(CFLAGS)	-c $(CFLAGS) $<

irix:
	@echo "Creating	Irix version of ParticlePointSystem"
	@make 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(PLUGIN).so

linux:
	@echo "Creating	Linux version of ParticlePointSystem"
	@make 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(PLUGIN).so


$(PLUGINS_OS_DIR)/$(PLUGIN).so: $(PLUGIN).h $(OBJS)
	$(CC) $(CFLAGS)	$(OBJS) $(LFLAGS) -o $(PLUGINS_OS_DIR)/$(PLUGIN).so \
	$(LIBS) 

clean:
	\rm -f *.o *.so *.a



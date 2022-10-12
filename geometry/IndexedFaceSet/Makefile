PLUGIN = IndexedFaceSet
OBJS = Material.o Vrml.o WingedEdge.o jacobi.o Obj.o Ply.o 

PLUGINS_DIR = ../../plugins

INCLUDES = -I$(DANCE_DIR)/src  -I$(DANCE_DIR)/VCOLLIDE/RAPID -I/usr/local/include

irix:
	@echo "Creating Irix version of IndexedFaceSet"
	@make -s 'CC=CC' 'OS=Irix'	\
	    'PLUGINS_OS_DIR = $(PLUGINS_DIR)/Irix' \
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-c -woff 3262' \
	    'LFLAGS = -D_cplusplus -shared ' \
	    $(PLUGINS_DIR)/Irix/$(PLUGIN).so

linux:
	@echo "Creating Linux version of IndexedFaceSet"
	@make -s 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -c -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' $(PLUGINS_DIR)/Linux/$(PLUGIN).so

$(PLUGINS_OS_DIR)/$(PLUGIN).so:	$(OBJS) $(PLUGIN).h $(PLUGIN).o ../../src/DGeometry.h librapid 
	$(CC) $(LFLAGS) $(PLUGIN).o	$(OBJS) $(RAPID_LIB) -o $(PLUGINS_OS_DIR)/$(PLUGIN).so 
librapid:
	@ (cd ../../VCOLLIDE/RAPID; make -s $(OS))

.cxx.o:
	@echo $<
	$(CC) $(CFLAGS) $(DEFINES) $<

%.o:%.cxx
	@echo $<
	$(CC) $(CFLAGS) $(DEFINES) $<

clean:
	\rm -f *.o *.so	*.a



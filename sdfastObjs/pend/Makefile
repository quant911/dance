PROG = pend

INCLUDES = -I.

SRC = $(PROG)_dyn.c $(PROG)_sar.c $(PROG)lib.c
HEADERS = $(PROG)_dyn.h $(PROG)_sar.h $(PROG)lib.h sdfast.h

irix:
	@echo "Creating	Irix version."
	@make 'CC=CC' 'OS=Irix'	\
	    'CFLAGS = $(INCLUDES) -DREAL=float -D_cplusplus -g3	-woff 3262' \
	    'LFLAGS = -D_cplusplus -check_registry /usr/lib/so_locations -shared ' \
	    ./$(PROG).so

linux:
	@echo "Creating	Linux version."
	@make 'SHELL = /bin/csh	-f' 'OS=Linux' \
	      'PLUGINS_OS_DIR =	$(PLUGINS_DIR)/Linux' \
	      'CC=g++ '	\
	      'CFLAGS =	$(INCLUDES) -DREAL=float -D_cplusplus -DX86 -shared -rdynamic -g3 ' \
	      'LFLAGS =	-shared	-rdynamic' ./$(PROG).so


$(PROG).so: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS)	$(LFLAGS) $(SRC) -o ./$(PROG).so


clean:
	\rm -f *.o *.so *.a



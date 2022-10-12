############################################################################
#
# Top Level Makefile for V-Collide.
#
#
############################################################################

#Choose the C++ compiler you want
CC = CC

# If you want the demos to be compiled with a graphical display of 
# the simulation, then uncomment the following lines and provide
# the correct locations of the libraries and include files.

GRAPHICS_CFLAGS   = -DOGL_GRAPHICS
GRAPHICS_INCLUDES = -I/usr/include
GRAPHICS_LDFLAGS  = -L/usr/lib
GRAPHICS_LIBS     = -lglut -lGLU -lGL -lX11 -lXmu

irix:
	@echo "Creating Irix version of VCollide"
	@cd RAPID; \
	make -s irix 
	@cd src; \
	make -s irix 


linux:
	@echo "Creating Linux version of VCollide"
	@cd RAPID; \
	make -s linux 
	@cd src; \
	make -s linux

clean : 
	cd RAPID; make -i clean
	cd src; make -i clean


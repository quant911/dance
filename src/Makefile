#########################################################
# Define these environment variables for your own setup	#
#########################################################
PROG_DIR = $(DANCE_DIR)
#########################################################
# SHELL	= /bin/csh -f

PROG=dance
ARCBALL_OBJS = Ball.o BallAux.o	BallMath.o
DANCE_OBJS = DGeometry.o DanceObject.o DanceObjectList.o myMath.o vector.o \
	BoundingBox.o	CoordSystem.o Quaternion.o  Proximity.o \
	PlugInManager.o DActuator.o DLight.o danceTcl.o \
	ViewManager.o DView.o SimulatorEvents.o DSimulatorManager.o \
	DSystem.o DSimulator.o MonitorPoints.o DanceObjectRefList.o

DRIVER_OBJS = main.o APPcommands.o GLutilities.o

SYS = test
SDFAST_HOST = dali.dgp
SD_SCRIPTS = sdfast/scripts
SDFAST_C = $(SYS)/$(SYS)_dyn.c $(SYS)/$(SYS)_sar.c

OBJS = $(PROG).o $(DANCE_OBJS) 	$(ARCBALL_OBJS)	$(DRIVER_OBJS) $(COMMAND_OBJS)

COLLIDEINCS = -I../VCOLLIDE/src -I../VCOLLIDE/RAPID
INCLUDES = -I../libinclude -I/usr/local/include $(COLLIDEINCS)
OPTIMIZE = -Olimit 2187	-O2
CFLAGS = -c -g3	$(INCLUDES) -woff 3262 -D_cplusplus

#TCLLIBS	=  -L/local/lib -ltcl8.0 -ltk8.0 
TCLLIBS	=  -ltcl8.3 -ltk8.3 
COLLIDELIBS = -lVCollide -lRAPID -lminpack
XLIBS  = -L/usr/X11R6/lib -lXmu	-lX11 -lXi
LDFLAGS	= -rdynamic $(COLLIDELIBS) $(GLLIBS) $(XLIBS) $(TCLLIBS)  -ldl -lm
all: irix

.cxx.o:
	@echo $<
	$(CC) $(CFLAGS)	$(DEFINES) $<

%.o:%.cxx
	@echo $<
	$(CC) $(CFLAGS)	$(DEFINES) $<

irix:
	@echo -s "Creating Irix version of src."
	@make 'CC=CC' \
	      'LDFLAGS = -L../lib/Irix $(COLLIDELIBS) $(TCLLIBS) -lglutShared -lGLU -lGL $(XLIBS) -lm' \
	      'OBJS = $(OBJS)' 'OS=irix' \
	      'CFLAGS =	-DSGI -D_cplusplus -c -g3 $(INCLUDES) -woff 3262 ' $(PROG)

linux:
	@echo "Creating Linux version of src."
	@make -s 'SHELL = /bin/csh	-f' \
	      'CC=g++' 'OS=linux' \
	      'GLLIBS =	-L../lib/Linux -lglutShared -lMesaGLU -lMesaGL' \
	      'CFLAGS =	-D_cplusplus -c -g3 $(INCLUDES) -I/usr/local/include ' $(PROG)


$(PROG): $(OBJS) libvcollide IndexedFaceSet 
	$(CC) -o $(PROG)  $(OBJS) $(LDFLAGS)
	\mv dance ../bin/.

clean:
	\rm -f *.o *.so	*.a $(PROG)

libvcollide:
	(cd ../VCOLLIDE; make $(OS))

IndexedFaceSet:
	(cd ../geometry/IndexedFaceSet; make $(OS))

# DO NOT DELETE

APPcommands.o: dance.h defs.h danceTcl.h DanceObjectList.h DanceObject.h
APPcommands.o: Event.h
DActuator.o: defs.h DActuator.h PlugIn.h DanceObject.h Event.h BoundingBox.h
DActuator.o: myMath.h vector.h CoordSystem.h DSystem.h dance.h
DActuator.o: DanceObjectList.h danceTcl.h ViewManager.h
Ball.o: Ball.h BallAux.h BallMath.h
BallAux.o: BallAux.h
BallMath.o: BallMath.h BallAux.h
BoundingBox.o: BoundingBox.h myMath.h vector.h CoordSystem.h
CoordSystem.o: CoordSystem.h vector.h
DSimulator.o: defs.h danceTcl.h DanceObjectList.h DanceObject.h Event.h
DSimulator.o: DSimulator.h vector.h PlugIn.h
DSimulatorManager.o: danceTcl.h DanceObjectList.h DanceObject.h defs.h
DSimulatorManager.o: Event.h DSimulatorManager.h DSimulator.h vector.h
DSimulatorManager.o: PlugIn.h
DSystem.o: defs.h PlugIn.h DanceObject.h Event.h DSystem.h
DanceObject.o: DanceObject.h defs.h Event.h
DanceObjectList.o: defs.h DanceObjectList.h DanceObject.h Event.h
GLutilities.o: defs.h GLutilities.h vector.h
Geometry.o: defs.h Geometry.h vector.h Ball.h BallAux.h CoordSystem.h
Geometry.o: BoundingBox.h myMath.h PlugIn.h DanceObject.h Event.h
Geometry.o: GLutilities.h
DLight.o: DLight.h DanceObject.h defs.h Event.h dance.h ViewManager.h
DLight.o: DanceObjectList.h DView.h Ball.h BallAux.h
Playback.o: defs.h Playback.h
PlugInManager.o: PlugInManager.h DanceObjectList.h DanceObject.h defs.h
PlugInManager.o: Event.h PlugIn.h
Proximity.o: Proximity.h defs.h dance.h danceTcl.h DanceObjectList.h
Proximity.o: DanceObject.h Event.h DActuator.h PlugIn.h BoundingBox.h myMath.h
Proximity.o: vector.h CoordSystem.h DSystem.h
Quaternion.o: Quaternion.h vector.h
SimulatorEvents.o: defs.h danceTcl.h DanceObjectList.h DanceObject.h Event.h
SimulatorEvents.o: SimulatorEvents.h
DView.o: dance.h defs.h danceTcl.h DanceObjectList.h DanceObject.h Event.h
DView.o: DView.h Ball.h BallAux.h ViewManager.h
ViewManager.o: dance.h defs.h ViewManager.h DanceObjectList.h DanceObject.h
ViewManager.o: Event.h DView.h Ball.h BallAux.h
dance.o: dance.h defs.h danceTcl.h DanceObjectList.h DanceObject.h Event.h
dance.o: DActuator.h PlugIn.h BoundingBox.h myMath.h vector.h CoordSystem.h
dance.o: DSystem.h DLight.h DView.h Ball.h BallAux.h ViewManager.h
dance.o: PlugInManager.h DSimulatorManager.h GLutilities.h Proximity.h
danceTcl.o: dance.h defs.h DanceObjectList.h DanceObject.h Event.h
danceTcl.o: PlugInManager.h PlugIn.h DSimulatorManager.h danceTcl.h DSystem.h
danceTcl.o: ViewManager.h Proximity.h
main.o: dance.h defs.h
myMath.o: defs.h myMath.h vector.h CoordSystem.h
vector.o: vector.h
DActuator.o: PlugIn.h DanceObject.h defs.h Event.h BoundingBox.h myMath.h
DActuator.o: vector.h CoordSystem.h DSystem.h
Ball.o: BallAux.h
BallMath.o: BallAux.h
BoundingBox.o: myMath.h vector.h CoordSystem.h
CoordSystem.o: vector.h
DSimulator.o: defs.h vector.h PlugIn.h DanceObject.h Event.h
DSimulatorManager.o: DanceObjectList.h DanceObject.h defs.h Event.h
DanceObject.o: defs.h Event.h
DanceObjectList.o: DanceObject.h defs.h Event.h
Geometry.o: defs.h vector.h Ball.h BallAux.h CoordSystem.h BoundingBox.h
Geometry.o: myMath.h PlugIn.h DanceObject.h Event.h
DLight.o: DanceObject.h defs.h Event.h
PlugIn.o: DanceObject.h defs.h Event.h
PlugInManager.o: DanceObjectList.h DanceObject.h defs.h Event.h PlugIn.h
Proximity.o: defs.h
Quaternion.o: vector.h
SimulatorEvents.o: defs.h
DView.o: DanceObject.h defs.h Event.h Ball.h BallAux.h
ViewManager.o: DanceObjectList.h DanceObject.h defs.h Event.h
dance.o: defs.h
danceTcl.o: DanceObjectList.h DanceObject.h defs.h Event.h
myMath.o: vector.h CoordSystem.h

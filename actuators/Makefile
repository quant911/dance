SHELL =	/bin/tcsh

all: linux

irix:
	(cd PlaneGround	; make -i -s irix)
	(cd FieldActuator ; make -i -s irix)
	(cd KinematicActuator ; make -i -s irix)
	(cd IKActuatorForce ; make -i -s irix)

linux:
	(cd PlaneGround	; make -i -s linux)
	(cd FieldActuator ; make -i -s linux)
	(cd KinematicActuator ; make -i -s linux)
	(cd IKActuatorForce ; make -i -s linux)

clean: 
	(cd FieldActuator ; make -i clean)
	(cd PlaneGround	; make -i clean)
	(cd KinematicActuator ; make -i clean)
	(cd IKActuatorForce ; make -i clean)
	



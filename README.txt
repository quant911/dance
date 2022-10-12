To install dance follow the instructions in doc/Installation.txt.
If everything went well, you should have an executable in bin/dance.
To run dance do:
> dance
and you should see the opening interface of dance. Use:
Tool->Command Console
to bring up the command console of dance. Although you may prefer
to use only the GUI keep in mind that error messages
and warnings appear only at the console window.

Compiling
---------

Under windows: We provide project files for MS visual studio version 6.
Load the work space dance.dsw and make all the projects.

Under UNIX: type "make linux" or "make irix" depending on your operating system
at the root directory $(DANCE_DIR). If you get make errors make sure
that you run redhat 6.xxx

NOTE: In all cases make sure you have properly set DANCE_DIR to 
<pathname>/dance.

Running the demos:
-----------------

Under UNIX: Set LD_LIBRARY_PATH to include ${DANCE_DIR}/lib/${OS} so that the runtime linker
can locate the neccessary libraries. $OS is one of "Linux" or "Irix" depending or your system.
If you run a csh compatible shell you can do this as follows:

> setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${DANCE_DIR}/lib/Linux
or
> setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${DANCE_DIR}/lib/Irix

If you have set the path properly you should be able to start dance by 
typing "dance<Enter>" in any window.

Under windows: Make "dance" the active project and use the execute command of visual studio.
If for some reason it is not allready defined, define bin/dance.exe as the main executable
through Project->Settings.

(a) Pendulum and particle system
--------------------------------

You can run a first example by opening the following session
$(DANCE_DIR)/run/pend/inp.tcl
You can do that in too ways:
GUI: 
     File -> Open Session
command console using the "<" command:
     <prompt> < run/pend/inp.tcl
In the unix version the program will pose while compiling the dynamic simulator
provided by Symbolic Dynamics Inc. The compiled simulator is automatically linked
in and the system and then the program will continue normally.

If everything loads successfully you should see a two link dynamic pendulum swinging
while it emits kinematic particles form its base. Use the left mouse button to rotate
the screen the middle button to move the camera and the right button to zoom in and out.
If you have a two button mouse then the right button moves the camera if you hold down
the <Shift> key.

Check the file run/pend/README.txt for more information on the demo.

(b) Inverse kinematics actuator
-------------------------------

Open session run/skel18/inp.tcl
Unix users: It will take quite some time to compile the dynamic model
the first time you attempt to run the demo. This model is complex and it
is courtesy of Symbolic Dynamics Inc. During the compilation
DANCE will freeze.

Read actuators/IKActuatorForce/userman.txt on how to user this actuator.







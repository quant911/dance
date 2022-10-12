This demo shows the simulation of two link dynamic pendulum (dynamics courtesy
of Symbolic Dynamics Inc) and a kinematic particle system. The first time you run this under
linux, the system will automatically compile the equations of motion into 
a shared library. The system will pause until the library is linked in. 


Camera Motion:
-------------
	Left mouse button motion controls arcbacll rotation
	Right mouse button  motion controls the zoom
	Middle mouse button and alternatively right mouse button + <shift key>
	       moves the camera.

Simulator Panel:
----------------
	use the Start, Stop etc buttons to control the simulation.
	If the simulation finishes set the current time to 0
	by typing 0<Enter> at the appopriate GUI entry.	

To position the pendulum:
-------------------------
	Stop the simulation.
	Bring up the console using Tool->Console.
	In the console window type:
	> system pend transparency 0.5
	That will make the pendulum transparent.
	Move the pointer in the view window and hit the key 'J'
	to enter the joint edit mode.
	You should now see the skeleton of the pendulum. The joints
	are represented by squares. Clicking on the joints (squares)
	results in the degrees of freedom appearing as rotational
	axis. Dragging the mouse after clicking on an axis controls
	the associated angle. Clicking anywhere but the axis and joints
	restores the camera mode. You should press 'J' whenever you want
	to enter the joint edit mode.

View
----
	Click on Main menu: Edit->Views and selected the view by clicking twice on it.
	Then click on the "Edit" button. That brings up a panel that allows you to change
	various parameters such as background color, turn lighing on/off etc.

Note: Do not get confused by the meny provided by the console window. The DANCE main
      menu is separate from the console window. If you do not see it, it is probably
      hidden behind another window.


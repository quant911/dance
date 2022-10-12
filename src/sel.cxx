int dance::handleSelection(int x, int y, int button, int &number, int *item, int type)
{
	int selection_mode = -1;

	// Set up selection buffer.
	static GLuint SelectBuffer[512];
	glSelectBuffer(512,SelectBuffer);

	// Begin picking.
	glRenderMode(GL_SELECT);
	glInitNames();

	View *view = AllViews->getViewFocus();
	view->pickProjection(x,y,7.0,7.0);
	view->positionCamera();

	ArticulatedObject *active =(ArticulatedObject *)AllSystems->getActive();
	switch(type) {
	   case	JOINT_SELECTION:
	    glPushName(JOINT_SELECTION);
	    if (active)	{
	      if (button == GLUT_LEFT_BUTTON)
			active->displayJoints(JDISPLAY_MANIPS);
	      else
			active->displayJoints(JDISPLAY_CENTRES);
	    }
	    glPopName();
	   break;
	   case	ACTUATOR_SELECTION:
	     if (AllActuators)	{
		  glPushName(ACTUATOR_SELECTION);
		  // must LDISPLAY_SELECTION otherwise the
		  // actuator display will produce wrong windw coordinates
		  // for glReadPixels and core dump.
		  // selection changes the projection matrix!!
		  AllActuators->output(LDISPLAY_SOLID |	LDISPLAY_SELECTION);
		  glPopName();
	      }
	   break;
	   case	ARTICOBJ_SELECTION:
	    glPushName(ARTICOBJ_SELECTION);

	    // Must use	output with two	arguments.
	    AllSystems->output(LDISPLAY_SOLID);
	    glPopName();
	    break;
	   case	GEOMETRY_SELECTION:
	    glPushName(GEOMETRY_SELECTION);
	    if (active)
		active->displayLinks(LDISPLAY_SOLID);
	    glPopName();
	   break;
	   case	LIGHT_SELECTION:
	     glPushName(LIGHT_SELECTION);
	     AllLights->output(LDISPLAY_SOLID);
	     glPopName();
	   break;
	}

	// Process hits.
	int hits = glRenderMode(GL_RENDER);

	view->setProjection();

	int hp = 0;

	// Must use unsigned int for distance calculations to be correct.
	unsigned int closest = 0;

	// Loop	through	and pick the front-most	item
	for (int h = 0;	h < hits; h++) {
		int pickThis = 0;
		int numNames = SelectBuffer[hp++];
		unsigned int minz = SelectBuffer[hp++];
		unsigned int maxz = SelectBuffer[hp++];
		if (h==0) {
			closest	= minz;
			pickThis = 1;
		}
		else if	(minz <= closest)
			pickThis = 1;
		
		
		if (pickThis) {
		    number = 0;
		    for	(int ns	= hp; ns < hp+numNames;	ns++) {
		      if (ns ==	hp)
		       switch(SelectBuffer[ns])	{
				case ACTUATOR_SELECTION:
			    selection_mode = ACTUATOR_SELECTION;
				break;
				case JOINT_SELECTION:
			    selection_mode = JOINT_SELECTION;
				break;
				case ARTICOBJ_SELECTION:
			    selection_mode = ARTICOBJ_SELECTION;
				break;
				case GEOMETRY_SELECTION:
			    selection_mode = GEOMETRY_SELECTION;
				break;
				case LIGHT_SELECTION:
			    selection_mode = LIGHT_SELECTION;
				break;
		       }
		      else {
				item[ns-hp-1] =	SelectBuffer[ns];
				number = ns-hp;
		      }
		    }
		    if (number == 0) item[0] = -1;
		}
		hp += numNames;

	}

	return(selection_mode);
}

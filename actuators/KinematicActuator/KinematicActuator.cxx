#include "defs.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GLutilities.h"
#include "dance.h"
#include "danceTcl.h"
#include "DanceObjectList.h"
#include "KeyFrame.h"
#include "AnimationSequence.h"
#include "KinematicActuator.h"
//#include "SdfastSimul.h"

PlugIn *Proxy(void) { return (new KinematicActuator); } ;

KinematicActuator::KinematicActuator() 
{
    danceObj = NULL ;
    m_LocalTime = 0 ;
    m_recordTimeStep = 0.033 ;
    m_playTimeStep = 0.01 ;
    m_recording = FALSE ;
    m_animFileName[0] = '\0' ;
    m_PingPong = 0;
    m_direction = 1;
    m_show_time = FALSE ;
    m_last_record_time = MINFLOAT ;
    m_interpolation = TRUE ;
    m_isPlaying = FALSE ;
    setVector(m_labelPos, 0.0,0.0,0.0) ;
    m_labelCol[0] = 0.0 ;
    m_labelCol[1] = 1.0 ;
    m_labelCol[2] = 0.0 ;
    m_labelSize = 18 ;
    m_objectState = NULL ;

    m_isOffsetted = FALSE ;
    zeroVector(m_offset) ;
    return ;
}

KinematicActuator::~KinematicActuator()
{
    if( m_objectState != NULL )
	delete [] m_objectState ;
    
    if( interpreter != NULL )
	unLinkVariables(interpreter) ;
}

PlugIn *KinematicActuator::create(Tcl_Interp *interp, int argc, char **argv)
{
    KinematicActuator *f = new KinematicActuator ;

    if(	f == NULL )
    {
		danceTcl::OutputMessage( "Cannot allocate memory!") ;
		return NULL ;
    }

    f->interpreter = interp ;

    return f ;
}



void KinematicActuator::print(void)
{
    return ;
}

void KinematicActuator::saveScript(char *fname)
{
    FILE *fp = fopen(fname, "a") ;
    if( fp == NULL )
    {
	danceTcl::OutputMessage("Cannot open %s\n", fname) ;
	return ;
    }
    saveScript(fp) ;
    return ;
}


// saves the animation sequence too
void KinematicActuator::saveScript(FILE *fp)
{
    fprintf(fp, "actuator %s apply %s\n", getName(), danceObj->getName()) ;
    
    if( m_animSeq.GetSize() == 0 ) return ;
    // make a file name for the animation sequence if needed
    if( m_animFileName[0] == '\0' )
    {
	char *fn = tempnam(".", "anim") ;
	if( fn == NULL ) 
	{
	    danceTcl::OutputMessage("Cannot produce a unique filename."
		   "Animation sequence will not be saved.") ;
	    return ;
	}
    	strcpy(m_animFileName, fn) ;
	// according to the linux man pages
	// fn is allocated by malloc and should be deleted with free
	free(fn) ;
    }

    if( m_animSeq.Save(m_animFileName) == -1 )
	danceTcl::OutputMessage("Error saving the animation sequence.") ;
    
    return ;
}

void KinematicActuator::ExertLoad(DSystem *ao, double time, 
				 double dt, double *state, double *dstate)
{
    
    AppliedObject *wao = applyList;
    if( (applyList == NULL) || (applyList->ao == NULL))  return ;

    while (wao) {
	if (wao->ao == (DanceObject *) ao) break;
	wao = wao->next;
    }
 
    int isArtObj = FALSE ;
    // if applied on articulated object wait until the object is being simulated
    if( strcmp(applyList->ao->getType(), "ArticulatedObject") == 0 )
	isArtObj = TRUE ;
    if( (wao == NULL) && (isArtObj == TRUE)  )
	return ;

    // it is applied on a non-articulated object
    // check if the last time we saved a key frame is the same with the 
    // current time.



    danceObj = applyList->ao ;
    if( m_recording == TRUE )
    {
	if( fabs(m_last_record_time - time) < 1e-6)
	    return ;

	if( (m_animSeq.GetSize() == 0) || 
	    (time >= m_animSeq.GetEndTime() + m_recordTimeStep) )
	{
	    m_last_record_time = time ;
	    m_LocalTime = time ;
	    //if( isArtObj == TRUE ) // use sdfast compliant routine
	    //	InsertKeyFrameSdfast(danceObj->GetStateSize(), state) ;
	    //else		// use the normal routine
	    //{
		if( m_objectState == NULL )
		    m_objectState = new double [danceObj->GetStateSize()] ;
		if( m_objectState == NULL )
		{
		    danceTcl::OutputMessage("KinematicActuator::ExertLoad: "
					    "Cannot allocate memory!") ;
		    return ;
		}
		danceObj->GetState(m_objectState) ;
		m_animSeq.InsertKeyFrame(time, danceObj->GetStateSize(), m_objectState) ;
		//}
	}
    }

}


int KinematicActuator::commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char **argv)
{

    if( danceObj == NULL )
    {
	// associate with the last object applied on. There should be only
	// one.
	AppliedObject *wao = applyList;
	
	while (wao) {
	    if( wao->ao != NULL ) break ;
	    wao = wao->next;
	}
	
	if (strcmp(argv[0], "system") == 0) {
		if (wao)
			danceTcl::OutputResult("%s",wao->ao->getName());
		else
			danceTcl::OutputResult("nothing");
		return TCL_OK;
	}

	if (wao == NULL) 
	{
	    danceTcl::OutputMessage("No system associated with this actuator.\n") ;
	    return TCL_ERROR ;
	}
	danceObj = wao->ao ;
    }

    if( strcmp(argv[0], "set") == 0) {
	set(interp, argc-1, &argv[1]) ;
    }
    else if (strcmp(argv[0], "pingpong") == 0) {
	m_PingPong = atoi(argv[1]);
	if (m_PingPong == 0)
	    m_direction = 1;
    }
    else if( strcmp(argv[0], "rewind") == 0 )
    {
	m_LocalTime = m_animSeq.GetStartTime() ;
	ShowKeyFrame() ;
    }
    else if( strcmp(argv[0], "play") == 0 )
    {
	Play(argc-1, &argv[1]) ;
    }
    else if( strcmp(argv[0], "show_next_key_frame") == 0 )
	ShowNextKeyFrame() ;
    else if( strcmp(argv[0], "show_key_frame") == 0 )
	ShowKeyFrame(interp, argc-1, &argv[1]) ;
    else if( strcmp(argv[0], "record") == 0 )
	Record(interp, argc-1, &argv[1]) ;
    else if( strcmp(argv[0], "label_pos") == 0 )
    {
	if( argc == 4 )
	{
	    m_labelPos[0] = atof(argv[1]) ;
	    m_labelPos[1] = atof(argv[2]) ;
	    m_labelPos[2] = atof(argv[3]) ;
	}
	else
	    danceTcl::OutputResult("usage: label_pos x y z") ;
    }
    else if( strcmp(argv[0], "label_col") == 0 )
    {
	if( argc == 4 )
	{
	    m_labelCol[0] = (GLfloat) atof(argv[1]) ;
	    m_labelCol[1] = (GLfloat) atof(argv[2]) ;
	    m_labelCol[2] = (GLfloat) atof(argv[3]) ;
	}
	else
	    danceTcl::OutputResult("usage: label_col r g b") ;
    }
    else if( strcmp(argv[0], "label_size") == 0 )
    {
	if( argc == 2 )
	    m_labelSize = atoi(argv[1]) ;
	else
	    danceTcl::OutputResult("usage: label_size 10|12|18") ;
    }
    else if( strcmp(argv[0], "interpolation") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("usage: interpolation on/off") ;
	    return TCL_OK ;
	}
	if( strcmp(argv[1], "on") == 0 )
	    m_interpolation = TRUE ;
	else if(  strcmp(argv[1], "off") == 0 )
	    m_interpolation = FALSE ;
	else
	{
	    danceTcl::OutputMessage("usage: interpolation on/off") ;
	    return TCL_OK ;
	}
    }
    else if( strcmp(argv[0], "offset") == 0 )
    {
	m_isOffsetted = FALSE ;
	if( argc == 4 )
	{
	    m_offset[0] = atof(argv[1]) ;
	    m_offset[1] = atof(argv[2]) ;
	    m_offset[2] = atof(argv[3]) ;
	    m_isOffsetted = TRUE ;
	}
	else
	    danceTcl::OutputMessage("usage: offset x y z") ;
    }
    else if( strcmp(argv[0], "save_anim") == 0 )
    {
	if( argc != 2) 
	{
	    danceTcl::OutputMessage("ERROR: save <file_name>\n") ;
	    return TCL_ERROR ;
	}
	if( m_animSeq.Save(argv[1]) == -1 )
	    danceTcl::OutputMessage("Problem saving the animation script.\n") ;
	else
	    danceTcl::OutputMessage("Animation script saved in %s\n", argv[1]) ;
    }
    else if( strcmp(argv[0], "load_anim") == 0 )
    {
	if( argc != 2) 
	{
	    danceTcl::OutputMessage("ERROR: load <file_name>\n") ;
	    return TCL_ERROR ;
	}
	if( m_animSeq.Read(argv[1]) == -1 )
	    danceTcl::OutputMessage("Problem loading the animation script.\n") ;
    }
    else if( strcmp(argv[0], "delete") == 0 )
    {
	Delete(interp, argc - 1, &argv[1]) ;
    }
    else if( strcmp(argv[0], "show_time") == 0 )
    {
	if( argc != 2) 
	{
	    danceTcl::OutputMessage("ERROR: show_time [on|off]\n") ;
	    return TCL_ERROR ;
	}
	if( strcmp(argv[1], "on") == 0 )
	    m_show_time = TRUE ;
	else
	    m_show_time = FALSE ;
    }
    else
    {
	danceTcl::OutputMessage("Usage: system|set|show_next_key_frame|rewind|record|delete"
	       "|show_key_frame|load_anim|save_anim|show_time|label_pos|label_col\n") ;
	return TCL_ERROR ;
    }
    
    return TCL_OK ;
}

int KinematicActuator::linkVariables(Tcl_Interp *interp)
{
    char varName[256] ;

    sprintf(varName,"RecordTimeStep%s", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &m_recordTimeStep,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable %s\n", varName) ;
	return TCL_ERROR ;
    }
    // for some reasion this call crashes the program unless the
    // danceTcl::OutputMessage proc uses single quotes. WEIRD.
    //else danceTcl::OutputMessage("Linked variable %s", varName) ;

    sprintf(varName,"PlayTimeStep%s", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &m_playTimeStep,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable %s\n", varName) ;
	return TCL_ERROR ;
    }
    sprintf(varName,"KinematicActuatorTime%s", getName()) ;
    if ( Tcl_LinkVar(interp,varName, (char *) &m_LocalTime,TCL_LINK_DOUBLE)
	 == TCL_ERROR)
    {
	danceTcl::OutputMessage("Cannot link variable %s\n", varName) ;
	return TCL_ERROR ;
    }
    //else danceTcl::OutputMessage("Linked variable %s", varName) ;


    return TCL_OK ;
}

void KinematicActuator::unLinkVariables(Tcl_Interp *interp)
{
    char varName[256] ;

    sprintf(varName,"RecordTimeStep%s", getName()) ;
    Tcl_UnlinkVar(interp, varName) ;
    
    sprintf(varName,"PlayTimeStep%s", getName()) ;
    Tcl_UnlinkVar(interp, varName) ;

    sprintf(varName,"KinematicActuatorTime%s", getName()) ;
    Tcl_UnlinkVar(interp, varName) ;

    return  ;
}

int KinematicActuator::initInterface(Tcl_Interp *interp)
{
    return linkVariables(interp) ;
}
    
// sets	the various parameters of the Kinematic actuator
// expects argv[0] = <param_name>
//	   argv[1] = <value 0> ...
int KinematicActuator::set(Tcl_Interp *interp, int argc, char **argv)
{
    if( argc < 1 )
    {
	danceTcl::OutputMessage("Usage: set play_time_step| record_time_step | time\n") ;
	return TCL_ERROR ;
    }
    if( strcmp(argv[0], "time") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("Usage: set time <time>\n") ;
	    return TCL_ERROR ;
	}
	m_LocalTime = atof(argv[1]) ;
    }
    else if( strcmp(argv[0], "record_time_step") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("Usage: set record_time_step  <dt>\n") ;
	    return TCL_ERROR ;
	}
	m_recordTimeStep = atof(argv[1]) ;
    }
    else if( strcmp(argv[0], "play_time_step") == 0 )
    {
	if( argc != 2 )
	{
	    danceTcl::OutputMessage("Usage: set play_time_step  <dt>\n") ;
	    return TCL_ERROR ;
	}
	m_playTimeStep = atof(argv[1]) ;
    }
    else 
    {
	danceTcl::OutputMessage("Usage: play_time_step| record_time_step | time\n") ;
	return TCL_ERROR ;
    }
    return TCL_OK ;
}

// inserts a key frame GIVEN that the m_LocalTime field
// has allready been set up properly
int KinematicActuator::InsertKeyFrame(void)
{
    int stateSize = danceObj->GetStateSize() ;
    double *state = new double [stateSize] ;

    if( state == NULL ) 
    {
	danceTcl::OutputMessage("ERROR: InsertKeyFrame: no more memory!\n") ;
	return TCL_ERROR ;
    }

    danceObj->GetState(state) ;
    if( m_animSeq.InsertKeyFrame(m_LocalTime, stateSize, state)  == 0 )
    {
	danceTcl::OutputMessage("ERROR: cannot add key frame.\n") ;
	delete [] state ;
	return TCL_ERROR ;
    }
    delete [] state ;
    return TCL_OK ;
}

// PROC: InsertKeyFrameSdfast()
// DOES:
// inserts a key frame GIVEN that the m_LocalTime field
// has allready been set up properly. To be used when the simulation
// is running and we are not sure if the state of the object
// has been updated properly in the ao structure (for example when we
// use variable time step. Again the m_LocalTime field must be set properly
// before the call.
// NOTE: assumes that the first joint is a free joint
int KinematicActuator::InsertKeyFrameSdfast(int stateSize, double *state)
{
    double stateFixed[500] ;

    // stateFixed[6] = state[stateSize-1] ; // move the quaternion parameter forward
    //memcpy(stateFixed, state, 6*sizeof(double)) ;
    //memcpy(&stateFixed[7], &state[6], (stateSize-8)*sizeof(double)) ;
    for( int i = 0 ; i < stateSize  ; i++ )
    {
	if( i == 6 ) stateFixed[i] = state[stateSize-1] ;
	if( i < 6 ) stateFixed[i] = state[i] ;
	if( i > 6 ) stateFixed[i] = state[i-1] ;
    }
    if( m_animSeq.InsertKeyFrame(m_LocalTime, stateSize, stateFixed)  == 0 )
    {
	danceTcl::OutputMessage("ERROR: cannot add key frame.\n") ;
	return TCL_ERROR ;
    }

    return TCL_OK ;
}

// ShowKeyFrame(...)
// sets the time to argv[0] and then shows the keyframe if one exists at that
// time
int KinematicActuator::ShowKeyFrame(Tcl_Interp *interp, int argc, char **argv) 
{
    if( argc < 1 )
    {
	danceTcl::OutputMessage("Usage: show_key_frame <time>\n") ;
	return TCL_ERROR ;
    }
    m_LocalTime = atof(argv[0]) ;
    ShowKeyFrame() ;
    return TCL_OK ;
}

// ShowKeyFrame()
// Shows the key frame at time m_LocalTime if it exists
void KinematicActuator::ShowKeyFrame(void)
{
    if( (m_LocalTime > m_animSeq.GetEndTime()) || (m_LocalTime < m_animSeq.GetStartTime()))
    {
	return ;
    }
    
    int count = 0 ;
    double params[MAX_NUM_PARAM] ;
    int nparam = m_animSeq.GetKeyFrame(m_LocalTime, params, m_interpolation) ;

    if( nparam == 0 )
    {
	return ;
    }

    if( m_isOffsetted == TRUE )
	VecAdd(params,params, m_offset) ;
    danceObj->UpdateState(params) ;
    // Update all actuators
    for ( int i = 0; i < dance::AllActuators->size(); i++) {
	DActuator *act = (DActuator *)dance::AllActuators->get(i);
	act->afterObjectUpdate(danceObj);
    }
    
}

// ShowNextKeyFrame()
// Shows the key frame at the current time and advances the time
// by m_playTimeStep 
void KinematicActuator::ShowNextKeyFrame(void) 
{
    if( danceObj == NULL )
    {
	// associate with the last object applied on. There should be only
	// one
	AppliedObject *wao = applyList;
	
	while (wao) {
	    if( wao->ao != NULL ) break ;
	    wao = wao->next;
	}
	
	if (wao == NULL) 
	{
	    danceTcl::OutputMessage("No object associated with this actuator.\n") ;
	    return ;
	}
	danceObj = wao->ao ;
    }

    if( m_LocalTime > m_animSeq.GetEndTime()) 
		if (m_PingPong == 0)
			m_LocalTime = m_animSeq.GetStartTime();
		else {
			m_direction = -1;
			m_LocalTime = m_animSeq.GetEndTime();
		}
	if ( m_LocalTime < m_animSeq.GetStartTime()) {
		if (m_PingPong)
			m_direction = 1;
		
		m_LocalTime = m_animSeq.GetStartTime();
	}
    int count = 0 ;
    double params[MAX_NUM_PARAM] ;
    int nparam = m_animSeq.GetKeyFrame(m_LocalTime, params, m_interpolation) ;

    if( nparam == 0 )
	return ;
    
    // danceObj->SetLastState(); // Sets the last state vector, can be used to 
    // optimize playback for actuator updates by taking
    // advantage of non-zero deltas only
    
    if( m_isOffsetted == TRUE )
	VecAdd(params,params, m_offset) ;
    danceObj->UpdateState(params) ;
    // Update all actuators
    
    for (int i = 0; i < dance::AllActuators->size(); i++) {
	DActuator *act = (DActuator *)dance::AllActuators->get(i);
	act->afterObjectUpdate(danceObj);
    }
    
    m_LocalTime += m_direction*m_playTimeStep ;
    
}

int KinematicActuator::Record(Tcl_Interp *interp, int argc, char **argv)
{
    if( argc < 1 )
    {
	danceTcl::OutputMessage("Usage: record start|stop|key_frame\n") ;
	return TCL_ERROR ;
    }
    if( strcmp(argv[0], "start") == 0 )
    {
		m_animSeq.Clear() ;
		m_recording = TRUE ;
		danceTcl::OutputMessage("Recording started.\n") ;
    }
    else if( strcmp(argv[0], "stop") == 0 )
    {
		danceTcl::OutputMessage("Recording stop.\n") ;
		m_recording = FALSE ;
    }
    else if( strcmp(argv[0], "key_frame") == 0 )
    {
		if( argc < 2)
		{
			danceTcl::OutputMessage("Usage: record key_frame <time>\n") ;
			return TCL_ERROR ;
		}
		m_LocalTime = atof(argv[1]) ;
        InsertKeyFrame() ;
    }
    	
    return TCL_OK ;
}

					  
int KinematicActuator::Delete(Tcl_Interp *interp, int argc, char **argv)
{
    if( argc < 1 )
    {
	danceTcl::OutputMessage("Usage: delete key_frame|all\n") ;
	return TCL_ERROR ;
    }
    if(strcmp(argv[0], "all") == 0 )
    {
	m_animSeq.Clear() ;
	m_LocalTime = 0 ;
    }
    else if( strcmp(argv[0], "key_frame") == 0 )
    {
	m_animSeq.DeleteKeyFrame(m_LocalTime) ;
    }
    else 
    {
	danceTcl::OutputMessage("Usage: delete key_frame|all\n") ;
	return TCL_ERROR ;
    }
    return TCL_OK ;
}

void KinematicActuator::Play(int argc, char *argv[])
{
    if (argc < 1)
    {
	danceTcl::OutputMessage("usage: play start|stop") ;
	return ;
    }
    if( strcmp(argv[0], "start") == 0) 
    {
	danceTcl::OutputMessage("Starting playback for actuator %s.",
				getName()) ;
	m_isPlaying = TRUE ;
    }
    else  if( strcmp(argv[0], "stop") == 0) 
    {
	danceTcl::OutputMessage("Stopping playback for actuator %s.",
				getName()) ;
	m_isPlaying = FALSE ;
    }
    else
    {
	danceTcl::OutputMessage("usage: play start|stop") ;
	return ;
    }
}

int KinematicActuator::IdleCB(void)
{
    if( m_isPlaying == TRUE )
    {
	ShowNextKeyFrame() ;
	return 1 ;		// shows that something has changed
    }
    return 0 ;
}

void KinematicActuator::output(int mode)
{
    if( m_show_time == FALSE ) return ;

    char label[256] ;
    glPushAttrib(GL_LIGHTING_BIT) ;
    glDisable(GL_LIGHTING) ;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix() ;
    glLoadIdentity() ;
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix() ;
    glLoadIdentity() ;
    gluOrtho2D(0.0, (GLfloat) 1000, 0.0, (GLfloat) 1000) ;

    glColor3f(m_labelCol[0], m_labelCol[1], m_labelCol[2]) ;
    glRasterPos3dv(m_labelPos) ;
    
    sprintf(label, "Time : %lf", m_LocalTime) ; 
    GLlabel(label, m_labelSize) ;
    glMatrixMode(GL_PROJECTION) ;
    glPopMatrix() ;
    glMatrixMode(GL_MODELVIEW) ;
    glPopMatrix() ;
    
    glPopAttrib() ;
    
    return ;
}


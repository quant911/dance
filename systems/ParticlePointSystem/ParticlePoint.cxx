#include "defs.h"
#include "GL/gl.h"
#include "GL/glutShared.h"
#include "danceTcl.h"
#include "ParticlePoint.h"

ParticlePoint::ParticlePoint() { 
      m_mass = 0 ; m_birthTime = 0 ; 
      m_pos[0] = 0 ; m_pos[1] = 0 ; m_pos[2] ;
      m_rotX = 0 ; m_rotZ = 0 ;
      m_vel[0] = 0 ; m_vel[1] = 0 ; m_vel[2] = 0 ;
      m_length2 = 0.5 ;
}

ParticlePoint::ParticlePoint(double mass, double time) { 
    m_rotX = 0 ; m_rotZ = 0 ;
    m_mass = mass ; m_birthTime = time ;
    m_pos[0] = 0 ; m_pos[1] = 0 ; m_pos[2] ;
    m_vel[0] = 0 ; m_vel[1] = 0 ; m_vel[2] = 0 ;
} 

void ParticlePoint::output(int mode)
{
    glPushAttrib(GL_ENABLE_BIT) ;
    glDisable(GL_LIGHTING) ;
    glPushMatrix() ;
    glTranslated(m_pos[0], m_pos[1], m_pos[2]) ;
    //glRotated(m_rotX, 1.0 , 0.0, 0.0) ;
    //glRotated(45.0, 0.0, 0.0, 1.0) ;
	glColor3f(1.0, 1.0, 1.0) ;
	glutSolidSphere(m_length2, 4, 4) ;

    //glBegin(GL_LINES) ;
    //glColor3f(1.0, 1.0, 1.0) ;
    //glVertex3d(m_pos[0], m_pos[1] + m_length2, m_pos[2]) ;
    //glVertex3d(m_pos[0], m_pos[1] - m_length2, m_pos[2]) ;
    //glVertex3d(0, m_length2, 0) ;
    //glVertex3d(0, -m_length2, 0) ;
    //glEnd() ;

    glPopMatrix() ;
    glPopAttrib() ;
}

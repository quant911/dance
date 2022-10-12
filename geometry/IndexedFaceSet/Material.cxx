// Material.cpp: implementation of the Material class.
//
//////////////////////////////////////////////////////////////////////

#include "Material.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Material::Material()
{
	// Some defaults. Same as OpenGL
    mAmbientColor[0] = 0.2f;
	mAmbientColor[1] = 0.2f;
	mAmbientColor[2] = 0.2f;
	mAmbientColor[3] = 1.0f;

	mDiffuseColor[0] = 1.0f;
	mDiffuseColor[1] = 1.0f;
	mDiffuseColor[2] = 1.0f;
	mDiffuseColor[3] = 1.0f;

	mSpecularColor[0] = 0.0f;
	mSpecularColor[1] = 0.0f;
	mSpecularColor[2] = 0.0f;
	mSpecularColor[3] = 1.0f;

	mEmissiveColor[0] = 0.0f;
	mEmissiveColor[1] = 0.0f;
	mEmissiveColor[2] = 0.0f;
	mEmissiveColor[3] = 1.0f;

	mShininess = 0.0f;

}

void Material::setOpenGLMaterial(void)
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,mAmbientColor);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mDiffuseColor);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mSpecularColor);
	glMaterialfv(GL_FRONT,GL_EMISSION,mEmissiveColor);
	glMaterialf(GL_FRONT,GL_SHININESS,mShininess);
}


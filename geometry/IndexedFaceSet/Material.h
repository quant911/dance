// Material.h: interface for the Material class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MATERIAL_H_
#define _MATERIAL_H_ 

class Material  
{
public:
// class Material {
public:
	// Some defaults. Same as OpenGL
    float mAmbientColor[4];
	float mDiffuseColor[4];
	float mSpecularColor[4];
	float mEmissiveColor[4];
	float mShininess;

	Material();
	void setOpenGLMaterial();
};

#endif 

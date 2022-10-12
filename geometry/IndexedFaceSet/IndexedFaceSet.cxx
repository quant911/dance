/**************************************************************************
	----------------------------------------------
	ORIGINAL AUTHORS: Victor Ng,  Petros Faloutsos
	-----------------------------------------------
		{victorng,pfal}@dgp.toronto.edu
	University of Toronto
	Department of Computer Science
	Dynamic	Graphics Project


 ***************************************************************
 ******General License Agreement and Lack of Warranty ***********
 ****************************************************************

 This software is distributed in the hope that it will be useful
 but WITHOUT ANY WARRANTY. The author(s) do not	accept responsibility
 to anyone for the consequences	of using it or for whether it serves
 any particular	purpose	or works at all. No warranty is	made about
 the software or its performance.
***************************************************************************/

#include "defs.h"
#include <GL/gl.h>
#include <ctype.h>

#include <stdio.h>
#include "danceTcl.h"
#include "IndexedFaceSet.h"
#include "RAPID.h"

PlugIn *Proxy(void) { return (new IndexedFaceSet); } ;


static const int VECTOR_CHUNK_SIZE = 1000 ; // this is the size of the vector	chunks
				// that	are allocated every time we need more space
				// when	reading	in a indexed face set file
static const int FACE_CHUNK_SIZE = 1000 ; // similarly for faces

static const int EDGE_CHUNK_SIZE = 1000 ; // similarly for edges


IndexedFaceSet::IndexedFaceSet(): DGeometry()
{
    m_HasColors = FALSE;
    m_AllTriangles = FALSE;
    m_HasNormals = FALSE;
	m_DisplayList = FALSE;

	m_ScaleFactor = 1.0;

    m_MassPropertiesType = 0;
    m_Mass = 1.0;
    m_Moments[0] = m_Moments[1] = m_Moments[2] = 1.0;

    m_Density = 1.0;
    m_MassPt = 1.0;

    m_NumFaces = 0 ;
    m_NumVertices = 0 ;
    m_NumNormals = 0 ;
    m_NumMaterials = 0;

    m_comDiscrete[0] = 0.0; m_comDiscrete[1] = 0.0; m_comDiscrete[2] = 0.0;

    m_Materials = NULL;
	m_EdgeList = NULL;
    m_Faces = NULL;
    m_Vertices = NULL;
	m_VertexEdges = NULL;
    m_Normals = NULL ;
    m_TexCoords = NULL ;

	m_MirrorGeometry *= 0;

    setType("IndexedFaceSet");

    return ;
}

IndexedFaceSet::~IndexedFaceSet()
{
    if(	m_Normals  ) delete [] m_Normals ;
    if(	m_Vertices ) delete [] m_Vertices ;

    // Remove all entries first.
    for (int i = 0; i < m_NumVertices; i++) 
	m_VertexEdges[i].Cleanup();
    if (m_VertexEdges) delete [] m_VertexEdges;
    
    if (m_EdgeList) delete [] m_EdgeList;
    if(	m_TexCoords) delete [] m_TexCoords ;
    if(	m_Faces )	delete [] m_Faces	;
    if (m_Materials) delete [] m_Materials;
    
    if (m_RAPIDmodel) delete m_RAPIDmodel;
}

int IndexedFaceSet::commandPlugIn(ClientData clientData, Tcl_Interp *interp, int argc, char	**argv)
{
	int result = TCL_OK;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i],"filename") == 0) {
			danceTcl::OutputResult("%s",getFileName());
			return TCL_OK;
		}
		if (strcmp(argv[i],"calcMassProperties") == 0) {
			i++;
			if (i < argc) {
				if (strcmp(argv[i],"continuous") == 0) {
					m_MassPropertiesType = 1;
					i++;
					if (i < argc)
						computeContMassProperties(atof(argv[i]),&m_Mass,m_Moments);
					else
						danceTcl::OutputMessage("USAGE: computeMassProperties continuous <density>\n");
				}
				else { // Discrete mass properties
					m_MassPropertiesType = 2;
					i++;
					if (i < argc)
					    computeDiscMassProperties(atof(argv[i]),&m_Mass,m_Moments);
					else
					    danceTcl::OutputMessage("USAGE: computeMassProperties discrete <pointmass>\n");
				}
			}
			else
			    danceTcl::OutputMessage("USAGE: computeMassProperties continous|discrete <density|pointmass>\n");
			return TCL_OK;
			
		}
		if (strcmp(argv[i],"mass") == 0) {
			danceTcl::OutputListElement("%f",m_Mass);
			return TCL_OK;
		}
		if (strcmp(argv[i],"moments") == 0) {
			danceTcl::OutputListElement("%f",m_Moments[0]);
			danceTcl::OutputListElement("%f",m_Moments[1]);
			danceTcl::OutputListElement("%f",m_Moments[2]);
			return TCL_OK;
		}
		if (strcmp(argv[i],"save") == 0) {
		    result = TCL_ERROR;
			if (i+1 < argc) {
				char *extension = strchr(argv[i+1],'.');
				if( extension == NULL )
				{
					danceTcl::OutputMessage("Needs a file name. The extension indicates the type.");
				}
				else if (strcmp(extension,".wrl") == 0) {
				    result = saveVRML(interp,argv[i+1]);
				    danceTcl::OutputMessage("Saved VRML file\n");
				}
				else if (strcmp(extension,".ply") == 0) {
				    result = savePly(interp,argv[i+1]);
				    danceTcl::OutputMessage("Saved ply file\n");
				}
				else if (strcmp(extension,".obj") == 0) {
				    result = saveOBJ(argv[i+1]);
				    danceTcl::OutputMessage("Saved obj file.");
				}
				else
				    danceTcl::OutputMessage("Unknown extension %sfile format.",
							    extension);
			}
			else
				danceTcl::OutputMessage("USAGE: save <filename>\n");
		    return result;
		}
		if (strcmp(argv[i],"setupCollision") == 0) { 
			result = PrepareCollision();
		    return result;
		}
		if( strcmp(argv[i], "flip_normals") == 0 ) {
		    for( int j = 0 ; j < m_NumNormals; j++ )
		    {
			m_Normals[j][0] -= m_Normals[j][0] ;
			m_Normals[j][1] -= m_Normals[j][1] ;
			m_Normals[j][2] -= m_Normals[j][2] ;
		    }
		    UpdateParamsAndDispList() ;
		    return TCL_OK ;
		}
		if( strcmp(argv[i], "reverse_vertex_order") == 0 ) {
		     for( int i = 0 ; i < m_NumFaces ;	i++ )
		     {
			 for( int j = 0 ; j < (m_Faces[i].numVertices / 2) ;	j++ )
			 {
			     int temp_indx ;
			     temp_indx =  m_Faces[i].vertexIndex[j] ;
			     m_Faces[i].vertexIndex[j] =  
			       m_Faces[i].vertexIndex[m_Faces[i].numVertices - j - 1] ;
			      m_Faces[i].vertexIndex[m_Faces[i].numVertices - j - 1] = 
				temp_indx ;
			     
			 }
		     }
		     UpdateParamsAndDispList() ;
		     return TCL_OK ; 
		}
		if (strcmp(argv[i],"testClosed") == 0) {
			if (m_NumEdges + 2 == m_NumVertices + m_NumFaces)
				danceTcl::OutputResult("yes");
			else
				danceTcl::OutputResult("no");
			return TCL_OK;
		}
		if( strcmp(argv[i],"monitor_points") == 0) {
		    assignMonitorPoints(argc -(i+1), &argv[i+1]) ;
		    return TCL_OK ;
		}
	}	
	return TCL_OK;
}

PlugIn *IndexedFaceSet::create(Tcl_Interp *interp, int argc, char **argv)
{
	if (argc < 1) {
		danceTcl::OutputMessage("USAGE: instance IndexedFaceSet <name> "
			      "<filename> [-flip {0|1}|-scalefactor <float>]\n");
		return NULL;
	}

	// Determine valid filename, if any.
	char filename[256];
	
	FILE *fp = NULL;
	fp = fopen(argv[0],"r");
	int len = strlen(argv[0]);
	if (fp == NULL)	
	{
	    
	    sprintf(filename,"%s/data/models/%s",getenv("DANCE_DIR"),argv[0]);
	    fp = fopen(filename,"r");
	    if (fp == NULL)	{
		danceTcl::OutputMessage("ERROR: Could not open file.");
		return(NULL);
	    }
	    fclose(fp);
	}
	else 
	    sprintf(filename,"%s",argv[0]) ;
	
	
	IndexedFaceSet *geo = new IndexedFaceSet;
	if (geo	== NULL) {
		danceTcl::OutputMessage("Cannot allocate memory for geometry plugin.\n");
		return NULL;
	}

	int count = 1;
	while (count < argc) {
		if (strcmp(argv[count],"-flip") == 0) {
			if (++count < argc)
				geo->m_MirrorGeometry *= atoi(argv[count]);
		}
		else if (strcmp(argv[count],"-scalefactor") == 0) {
			if (++count < argc)
				geo->m_ScaleFactor = atof(argv[count]);
		}
		count++;
	}
	// Determine which parser to use, examine the extension.
	char *extension = strrchr(filename,'.');
	if (strcmp(extension,".vrml") == 0 || strcmp(extension,".wrl") == 0
		|| strcmp(extension,".WRL") == 0)
	{		// Parse a VRML file.
			// NOTE: Moved fclose(fp) into parseVRML because Windows
			// did not like to fclose outside of the parseVRML. Perhaps because
			// the end of file condition was encountered in parseVRML.
			//
		    if (geo->ParseVRML(interp, filename) != TCL_OK) 
				return NULL;
	}
	else if (strcmp(extension,".bone") == 0) 
	{
			// Parse modified bone file from Don Henderson
			if (geo->parseBONE(interp,filename) != TCL_OK)
				return NULL;
	}
	else if (strcmp(extension,".ply") == 0)
	{
		    if (geo->parsePly(interp,filename) != TCL_OK)
				return NULL;
	}
	else {
		danceTcl::OutputMessage("ERROR: Cannot recognize object file format.\n");
		delete geo;
		return NULL;
	}

	// Save the filename.
	geo->setFileName(filename);

	// Compute face normals.
	geo->compFaceProperties();

	// Create the monitor points.
	// geo->createMonitorPoints();
	
	return geo;
}

// ***********************************************************
// PROC: display
// DOES:	displays the IndexedFaceSet object.
// CAUTION	The normals used are the face->norm and	not the	ones
//		stored for the vertices.!!
// ***********************************************************
void IndexedFaceSet::display(int style)
{
    
    int shadows = FALSE ;
    int lights = FALSE ;

    if(	(m_NumVertices == 0 ) || (m_NumFaces == 0 ))
		return ;
    	// We build the display list here instead of earlier because we must
	// be sure that an OpenGL context has already been created.
	if (m_DisplayList == FALSE) {
		// Create display list.
		DisplayFaces(1);
		m_DisplayList = TRUE;

		// Assign default color.
		if (m_Faces[0].materialIndex >= 0)
			memcpy(m_Color,m_Materials[m_Faces[0].materialIndex].mDiffuseColor,3*sizeof(float));
	}

   
    if(	style &	LDISPLAY_WIRE) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)  ;
    else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;

    if( glIsEnabled(GL_LIGHTING) == GL_TRUE ) lights = TRUE ;

    if( style & LDISPLAY_SHADOW) 
    {
		if (lights == TRUE) glDisable(GL_LIGHTING);
		shadows = TRUE ;
		glColor4f(0.0,0.0,0.0,0.5) ;
    }

	// Adjust color for transparency effects
    if (lights == TRUE && shadows == FALSE) {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		
	}
	if (shadows == FALSE) {
		m_Color[3] = 1.0f-m_Transparency;
		glColor4fv(m_Color);
	}

	
	glCallList(m_ID);

    // restore lighting if it was shadow drawing
    if( shadows == TRUE && lights == TRUE )
		glEnable(GL_LIGHTING) ;

	if (lights == TRUE && shadows == FALSE)
		glDisable(GL_COLOR_MATERIAL);

    return ;
}

// computeVolume:
//	Solves volume by using quick polygon approximation formula, derived from 
//  Graphics Gems IV. 
//  NOTE: Polygon order should be counterclockwise facing outwards.
//
double IndexedFaceSet::computeVolume(void)
{
    double vol	= 0.0 ;
    for( int i = 0 ; i < m_NumFaces ;	i++ )
    {
		// For each face, solve for the double area vector.
		double A2[3] = {0.0,0.0,0.0};
	    double *p1, *p2;
		Vector c1;
		for( int j = 0 ; j < m_Faces[i].numVertices-1 ;	j++ )
		{
			p1 = m_Vertices[m_Faces[i].vertexIndex[j]];
			p2 = m_Vertices[m_Faces[i].vertexIndex[j+1]];
			VecCrossProd(c1,p1,p2);
			A2[0] += c1[0]; A2[1] += c1[1]; A2[2] += c1[2];
		}
		p1 = m_Vertices[m_Faces[i].vertexIndex[m_Faces[i].numVertices-1]];
		p2 = m_Vertices[m_Faces[i].vertexIndex[0]];
		VecCrossProd(c1,p1,p2);
		A2[0] += c1[0]; A2[1] += c1[1]; A2[2] += c1[2];
	
		vol += 1.0/6.0 * VecDotProd(m_Vertices[m_Faces[i].vertexIndex[0]],A2) ;
    }

    return vol ;
}


// set the center of mass as end effector
// Not the most	accurate choice	of course!
void IndexedFaceSet::getEndEffector(Vector e)
{
    e[0] = 0.0 ;
    e[1] = 0.0 ;
    e[2] = 0.0 ;
}

BoundingBox *IndexedFaceSet::calcBoundingBox(BoundingBox *box)
{
    // run through all the vertices and	calculate
    // a general bounding box
    for( int i = 0 ; i <m_NumVertices ; i++ )
    {
	if (i == 0) {
		m_BoundingBox.xMin = m_BoundingBox.xMax = m_Vertices[i][0];
		m_BoundingBox.yMin = m_BoundingBox.yMax = m_Vertices[i][1];
		m_BoundingBox.zMin = m_BoundingBox.zMax = m_Vertices[i][2];
	}
	else {
	if( m_Vertices[i][0] < m_BoundingBox.xMin )
	    m_BoundingBox.xMin = m_Vertices[i][0] ;
	if( m_Vertices[i][1] < m_BoundingBox.yMin )
	    m_BoundingBox.yMin = m_Vertices[i][1] ;
	if( m_Vertices[i][2] < m_BoundingBox.zMin )
	    m_BoundingBox.zMin = m_Vertices[i][2] ;

	if( m_Vertices[i][0] > m_BoundingBox.xMax )
	    m_BoundingBox.xMax = m_Vertices[i][0] ;
	if( m_Vertices[i][1] > m_BoundingBox.yMax )
	    m_BoundingBox.yMax = m_Vertices[i][1] ;
	if( m_Vertices[i][2] > m_BoundingBox.zMax )
	    m_BoundingBox.zMax = m_Vertices[i][2] ;
		}
	}

	if (box)
		box->copy(&m_BoundingBox);
    return (box) ;
}

// Adds	a vertex in the	list. If it needs more memory it
// increases the size of the vertices arrays by
// VECTOR_CHUNK_SIZE more vectors. Also creates a parallel array
// to store the edges (not more than four edges to a vertex, 
// maximum valence 4).
//
int IndexedFaceSet::addVertex(double x,	double y, double z)
{
    int	numChunks = 0 ;

	// Initialize buffers for vertices and vertex edges.
    if(	m_NumVertices == 0 )
    {
		m_Vertices = new Vector[VECTOR_CHUNK_SIZE] ;
		if( m_Vertices == NULL) {
			fprintf(stderr,"ERR: IndexedFaceSet::addVertex cannot allocate memory for vertices.\n") ;
			return ERR ;
		}
		m_VertexEdges = new EdgeList[VECTOR_CHUNK_SIZE] ;
		if (m_VertexEdges == NULL) {
			fprintf(stderr,"ERR: IndexedFaceSet::addVertex cannot allocate memory for vertex edges.\n");
			return ERR;
		}
    }
    else if(m_NumVertices % VECTOR_CHUNK_SIZE ==	0 )
    {
		numChunks =m_NumVertices	/ VECTOR_CHUNK_SIZE ;
		// time	to allocate another chunk of memory
		numChunks++ ;
		Vector *vertices_tmp = new Vector[numChunks*VECTOR_CHUNK_SIZE] ;
		if( vertices_tmp == NULL )
		{
			fprintf(stderr,"IndexedFaceSet::addVertex Cannot allocate memory!\n") ;
			return ERR;
		}
		EdgeList *vedges = new EdgeList[numChunks*VECTOR_CHUNK_SIZE];
		if (vedges == NULL) {
			fprintf(stderr,"ERR: IndexedFaceSet::addVertex cannot allocate memory for new chunk.\n");
			return ERR;
		}

		
		memcpy(vertices_tmp,m_Vertices,3*sizeof(double)*m_NumVertices);
		memcpy(vedges, m_VertexEdges, m_NumVertices * sizeof (EdgeList));
		
		// WARNING: Make sure m_VertexEdges does not delete the actual integer lists, only
		// the nodes that hold pointers to the lists.
		delete [] m_Vertices ;
		delete [] m_VertexEdges ;
		m_Vertices = vertices_tmp ;
		m_VertexEdges = vedges;
    }
    setVector(m_Vertices[m_NumVertices],x*m_ScaleFactor,y*m_ScaleFactor,z*m_ScaleFactor) ;
    m_NumVertices++ ;

    return OK ;
}

// addMaterial:
//
int IndexedFaceSet::addMaterial(Material material)
{
    int	numChunks = 0 ;

    if(	m_NumMaterials == 0 )
    {
	m_Materials	= new Material[VECTOR_CHUNK_SIZE]	;
	if( m_Materials == NULL )
	{
	    fprintf(stderr,"IndexedFaceSet::addMaterial Cannot allocate memory!\n") ;
	    return ERR ;
	}
    }
    else if( (m_NumMaterials % VECTOR_CHUNK_SIZE) == 0 )
    {
	numChunks = m_NumMaterials / VECTOR_CHUNK_SIZE ;
	// time	to allocate another chunk of memory
	numChunks++ ;
	Material *materials_tmp = new Material[numChunks*VECTOR_CHUNK_SIZE] ;
	if( materials_tmp == NULL)
	{
	    fprintf(stderr,"IndexedFaceSet::addMaterial Cannot allocate memory!\n") ;
	    return ERR ;
	}
	memcpy(materials_tmp, m_Materials,m_NumMaterials*sizeof(Material));
	delete [] m_Materials ;
	m_Materials = materials_tmp ;
    }

    // Copy new material information.
    memcpy(&(m_Materials[m_NumMaterials]),&material,sizeof(Material));
    m_NumMaterials++ ;

    return OK ;
}

// adds	a normal in the	list. If it needs more memory it
// increases the size of the normals arrays by
// VECTOR_CHUNK_SIZE more vectors
int IndexedFaceSet::addNormal(double x,	double y, double z)
{

    int	numChunks = 0 ;

    if(	m_NumNormals == 0	)
    {
	m_Normals	= new Vector[VECTOR_CHUNK_SIZE]	;
	if( m_Normals == NULL )
	{
	    fprintf(stderr,"IndexedFaceSet::addNormal Cannot allocate memory!\n") ;
	    return ERR ;
	}
    }
    else if( (m_NumNormals % VECTOR_CHUNK_SIZE) == 0 )
    {
	numChunks = m_NumNormals / VECTOR_CHUNK_SIZE ;
	// time	to allocate another chunk of memory
	numChunks++ ;
	Vector *normals_tmp = new Vector[numChunks*VECTOR_CHUNK_SIZE] ;
	if( normals_tmp	== NULL	)
	{
	    fprintf(stderr,"IndexedFaceSet::addNormal Cannot allocate memory!\n") ;
	    return ERR ;
	}
	for( int i = 0 ; i < m_NumNormals; i++ )
	{
	    VecCopy(normals_tmp[i], m_Normals[i])	;
	}
	delete [] m_Normals ;
	m_Normals	= normals_tmp ;
    }
    setVector(m_Normals[m_NumNormals],x,y,z) ;
    m_NumNormals++ ;

    return OK ;
}
// addFace:
//
//  index      : Desired index of face. 
//  returns:    Current count of faces stored in this indexed face set,
//				-1 if no new face created.
//
int IndexedFaceSet::addFace(int index)
{

  
	if (index < m_NumFaces) return -1;
  
	int numChunks = 0 ;
	
	// We only want to create new space if the desired face has not been 
	// created yet.

    if(	m_NumFaces == 0 )
    {
		m_Faces =	new IndexedFace[FACE_CHUNK_SIZE] ;
		if( m_Faces == NULL )
		{
			fprintf(stderr,"IndexedFaceSet::addFace Cannot allocate memory!\n")	;
			return ERR ;
		}
    }
    else if( (m_NumFaces % FACE_CHUNK_SIZE) == 0 )
    {
		numChunks = m_NumFaces / FACE_CHUNK_SIZE ;
		// time	to allocate another chunk of memory
		numChunks++ ;
		IndexedFace *faces_tmp = new IndexedFace[numChunks*FACE_CHUNK_SIZE] ;
		if( faces_tmp == NULL )
		{
			fprintf(stderr,"IndexedFaceSet::addFace Cannot allocate memory!\n")	;
			return ERR ;
		}

		memcpy((void *)	faces_tmp, (void *) m_Faces, m_NumFaces*sizeof(IndexedFace)) ;
		delete [] m_Faces	;
		m_Faces =	faces_tmp ;
    }


	// Newly added face. Initialize several entries.

	m_Faces[index].numNormals = 0;
	m_Faces[index].normalIndex = NULL;
	m_Faces[index].numVertices = 0;
	m_Faces[index].vertexIndex = NULL;
	m_Faces[index].texCoordIndex = NULL;
	m_Faces[index].materialIndex = m_NumMaterials-1;

	m_Faces[index].faceNormal[0] = m_Faces[m_NumFaces].centroid[0] = 0.0;
	m_Faces[index].faceNormal[1] = m_Faces[m_NumFaces].centroid[1] = 0.0;
	m_Faces[index].faceNormal[2] = m_Faces[m_NumFaces].centroid[2] = 0.0;
	m_Faces[index].avgSideLength = 0.0;
	
  	m_NumFaces++;
    return m_NumFaces;
}

// scales the vertices and the monitor points of an Indexed face set.
// Normals need	not be scaled unless I change it to
// non-uniform scaling.
void IndexedFaceSet::scaleGeom(double scaleX, double scaleY, double scaleZ)
{
    int	i ;

    for( i = 0 ; i <m_NumVertices ; i++ )
    {
	m_Vertices[i][0] *= scaleX ;
	m_Vertices[i][1] *= scaleY ;
	m_Vertices[i][2] *= scaleZ ;
    }

    // very important: the offset w uses vertex	information
    // so it has to be recalculated
    for	(i = 0;	i < m_NumFaces; i++)
    {
	IndexedFace *f = &m_Faces[i];
	f->w = - f->faceNormal[X] * m_Vertices[f->vertexIndex[0]][X]
	  - f->faceNormal[Y] * m_Vertices[f->vertexIndex[0]][Y]
	  - f->faceNormal[Z] * m_Vertices[f->vertexIndex[0]][Z];
    }

    for( i = 0 ; i < m_MonitorPoints.m_NumPoints ; i++ )
    {
	m_MonitorPoints.m_Point[i][0] *=  scaleX ;
	m_MonitorPoints.m_Point[i][1] *=  scaleY ;
	m_MonitorPoints.m_Point[i][2] *=  scaleZ ;
    }

}


// compFaceProperties:
//
//	Computes the face normals based on the normals stored at the indices.
//
//	WARNING: These values will be invalid if original vertices  transformed.
//
void IndexedFaceSet::compFaceProperties(void)
{
	for (int i = 0; i < m_NumFaces; i++) {
		int *vertIndices = m_Faces[i].vertexIndex;
		int *normIndices = m_Faces[i].normalIndex;
		int numNormals = m_Faces[i].numNormals;
		if (numNormals == 1) 
			memcpy(m_Faces[i].faceNormal, m_Normals[m_Faces[i].normalIndex[0]],3*sizeof(double));
		// NOTE: Do not average the vertex normals as this may not necessarily give the proper
		// normal of the face.
		else { 
				// Calculate normals from cross-product of vectors formed from polygon sides.
			double dx1, dy1, dz1, dx2, dy2, dz2, nx, ny, nz;
			
    			dx1 = m_Vertices[vertIndices[1]][0] - m_Vertices[vertIndices[0]][0];
    			dy1 = m_Vertices[vertIndices[1]][1] - m_Vertices[vertIndices[0]][1];
    			dz1 = m_Vertices[vertIndices[1]][2] - m_Vertices[vertIndices[0]][2];
    			dx2 = m_Vertices[vertIndices[2]][0] - m_Vertices[vertIndices[1]][0];
    			dy2 = m_Vertices[vertIndices[2]][1] - m_Vertices[vertIndices[1]][1];
    			dz2 = m_Vertices[vertIndices[2]][2] - m_Vertices[vertIndices[1]][2];
    			nx = dy1 * dz2 - dy2 * dz1;
    			ny = dz1 * dx2 - dz2 * dx1;
    			nz = dx1 * dy2 - dx2 * dy1;
				
				// Potential danger of collinear polygons. 
    			double len = nx * nx + ny * ny + nz * nz;
				if (len < 0.00001) {
					// Take average of involved normals.
					for (int ii=0; ii < 3; ii++) {
						m_Faces[i].faceNormal[ii] = m_Normals[normIndices[0]][ii];
						m_Faces[i].faceNormal[ii] += m_Normals[normIndices[1]][ii];
						m_Faces[i].faceNormal[ii] += m_Normals[normIndices[2]][ii];
						m_Faces[i].faceNormal[ii] /= 3.0;
					}
					// Normalize it
					double mag = sqrt(m_Faces[i].faceNormal[0]*m_Faces[i].faceNormal[0]
							   + m_Faces[i].faceNormal[1]*m_Faces[i].faceNormal[1]
							   + m_Faces[i].faceNormal[2]*m_Faces[i].faceNormal[2]);
					m_Faces[i].faceNormal[0] /= mag;
					m_Faces[i].faceNormal[1] /= mag;
					m_Faces[i].faceNormal[2] /= mag;
				}
				else {
					len = sqrt(len);
    			m_Faces[i].faceNormal[0] = nx / len;
    			m_Faces[i].faceNormal[1] = ny / len;
    			m_Faces[i].faceNormal[2] = nz / len;
				}
		}

		// Compute offset w: from ax + by +cz + w = 0 for plane equation of the polygon
		// with normal (a,b,c). w solves for the exact plane, which will be used to
		// project to one of the coordinate planes to solve the projection integrals.
		// ref: see page 5 of Brian Mirtich's paper [Fast and Accurate Computation of 
		// Polyhedral Mass Properties.
		//
		m_Faces[i].w = - m_Faces[i].faceNormal[0] * m_Vertices[vertIndices[0]][0]
          			  - m_Faces[i].faceNormal[1] * m_Vertices[vertIndices[0]][1]
           			  - m_Faces[i].faceNormal[2] * m_Vertices[vertIndices[0]][2];

		// Compute centre of mass and avg face length.
		m_Faces[i].centroid[0] = m_Faces[i].centroid[1]  = m_Faces[i].centroid[2] = 0.0;
		m_Faces[i].avgSideLength = 0.0;
		for (int j = 0; j < m_Faces[i].numVertices; j++) {
			// Calculate length of one side.
			int cur = m_Faces[i].vertexIndex[j];
			int adj = m_Faces[i].vertexIndex[(j+1) % m_Faces[i].numVertices];
			double length = pow(m_Vertices[cur][0] - m_Vertices[adj][0],2.0)
				+ pow(m_Vertices[cur][1] - m_Vertices[adj][1],2.0)
				+ pow(m_Vertices[cur][2] - m_Vertices[adj][2],2.0);
			length = sqrt(length);

			m_Faces[i].avgSideLength += length;			  
	    
			m_Faces[i].centroid[0] += m_Vertices[cur][0];
			m_Faces[i].centroid[1] += m_Vertices[cur][1];
			m_Faces[i].centroid[2] += m_Vertices[cur][2];
		}

		m_Faces[i].avgSideLength /= m_Faces[i].numVertices;
		m_Faces[i].centroid[0] /= m_Faces[i].numVertices;
		m_Faces[i].centroid[1] /= m_Faces[i].numVertices;
		m_Faces[i].centroid[2] /= m_Faces[i].numVertices;
		
	}	
}

#define	X 0
#define	Y 1
#define	Z 2

// Macros
#define	SQR(x) ((x)*(x))
#define	CUBE(x)	((x)*(x)*(x))

// Globals
static int A;	// alpha 
static int B;	// beta	
static int C;	// gamma

// projection integrals	
static double P1, Pa, Pb, Paa, Pab, Pbb, Paaa, Paab, Pabb, Pbbb;

// face	integrals 
static double Fa, Fb, Fc, Faa, Fbb, Fcc, Faaa, Fbbb, Fccc, Faab, Fbbc, Fcca;

// volume integrals 
static double T0, T1[3], T2[3],	TP[3];

// compute various integrations	over projection	of face	
//
void IndexedFaceSet::compProjectionIntegrals(IndexedFace *f)
{
  double a0, a1, da;
  double b0, b1, db;
  double a0_2, a0_3, a0_4, b0_2, b0_3, b0_4;
  double a1_2, a1_3, b1_2, b1_3;
  double C1, Ca, Caa, Caaa, Cb,	Cbb, Cbbb;
  double Cab, Kab, Caab, Kaab, Cabb, Kabb;
  int i;

  P1 = Pa = Pb = Paa = Pab = Pbb = Paaa	= Paab = Pabb =	Pbbb = 0.0;

  for (i = 0; i	< f->numVertices; i++) {
    a0 = m_Vertices[f->vertexIndex[i]][A];
    b0 = m_Vertices[f->vertexIndex[i]][B];
    a1 = m_Vertices[f->vertexIndex[(i+1) % f->numVertices]][A];
    b1 = m_Vertices[f->vertexIndex[(i+1) % f->numVertices]][B];
    da = a1 - a0;
    db = b1 - b0;
    a0_2 = a0 *	a0; a0_3 = a0_2	* a0; a0_4 = a0_3 * a0;
    b0_2 = b0 *	b0; b0_3 = b0_2	* b0; b0_4 = b0_3 * b0;
    a1_2 = a1 *	a1; a1_3 = a1_2	* a1;
    b1_2 = b1 *	b1; b1_3 = b1_2	* b1;

    C1 = a1 + a0;
    Ca = a1*C1 + a0_2; Caa = a1*Ca + a0_3; Caaa	= a1*Caa + a0_4;
    Cb = b1*(b1	+ b0) +	b0_2; Cbb = b1*Cb + b0_3; Cbbb = b1*Cbb	+ b0_4;
    Cab	= 3*a1_2 + 2*a1*a0 + a0_2; Kab = a1_2 +	2*a1*a0	+ 3*a0_2;
    Caab = a0*Cab + 4*a1_3; Kaab = a1*Kab + 4*a0_3;
    Cabb = 4*b1_3 + 3*b1_2*b0 +	2*b1*b0_2 + b0_3;
    Kabb = b1_3	+ 2*b1_2*b0 + 3*b1*b0_2	+ 4*b0_3;

    P1 += db*C1;
    Pa += db*Ca;
    Paa	+= db*Caa;
    Paaa += db*Caaa;
    Pb += da*Cb;
    Pbb	+= da*Cbb;
    Pbbb += da*Cbbb;
    Pab	+= db*(b1*Cab +	b0*Kab);
    Paab += db*(b1*Caab	+ b0*Kaab);
    Pabb += da*(a1*Cabb	+ a0*Kabb);
  }

  P1 /=	2.0;
  Pa /=	6.0;
  Paa /= 12.0;
  Paaa /= 20.0;
  Pb /=	-6.0;
  Pbb /= -12.0;
  Pbbb /= -20.0;
  Pab /= 24.0;
  Paab /= 60.0;
  Pabb /= -60.0;
}

void IndexedFaceSet::compFaceIntegrals(IndexedFace *f)
{
  double *n, w;
  double k1, k2, k3, k4;

  compProjectionIntegrals(f);

  w = f->w;
  n = f->faceNormal;
  k1 = 1 / n[C]; k2 = k1 * k1; k3 = k2 * k1; k4	= k3 * k1;

  Fa = k1 * Pa;
  Fb = k1 * Pb;
  Fc = -k2 * (n[A]*Pa +	n[B]*Pb	+ w*P1);

  Faa =	k1 * Paa;
  Fbb =	k1 * Pbb;
  Fcc =	k3 * (SQR(n[A])*Paa + 2*n[A]*n[B]*Pab +	SQR(n[B])*Pbb
	 + w*(2*(n[A]*Pa + n[B]*Pb) + w*P1));

  Faaa = k1 * Paaa;
  Fbbb = k1 * Pbbb;
  Fccc = -k4 * (CUBE(n[A])*Paaa	+ 3*SQR(n[A])*n[B]*Paab
	   + 3*n[A]*SQR(n[B])*Pabb + CUBE(n[B])*Pbbb
	   + 3*w*(SQR(n[A])*Paa	+ 2*n[A]*n[B]*Pab + SQR(n[B])*Pbb)
	   + w*w*(3*(n[A]*Pa + n[B]*Pb)	+ w*P1));

  Faab = k1 * Paab;
  Fbbc = -k2 * (n[A]*Pabb + n[B]*Pbbb +	w*Pbb);
  Fcca = k3 * (SQR(n[A])*Paaa +	2*n[A]*n[B]*Paab + SQR(n[B])*Pabb
	 + w*(2*(n[A]*Paa + n[B]*Pab) +	w*Pa));
}

void IndexedFaceSet::compVolumeIntegrals(void)
{
  IndexedFace *f;
  double nx, ny, nz;
  int i;

  T0 = T1[X] = T1[Y] = T1[Z]
     = T2[X] = T2[Y] = T2[Z]
     = TP[X] = TP[Y] = TP[Z] = 0.0;

  for (i = 0; i	< m_NumFaces; i++) {

    f =	&m_Faces[i];

    nx = fabs(f->faceNormal[X]);
    ny = fabs(f->faceNormal[Y]);
    nz = fabs(f->faceNormal[Z]);

    if (nx > ny	&& nx >	nz) C =	X;
    else C = (ny > nz) ? Y : Z;
    A =	(C + 1)	% 3;
    B =	(A + 1)	% 3;

    compFaceIntegrals(f);

    T0 += f->faceNormal[X] * ((A == X) ? Fa :	((B == X) ? Fb : Fc));

    T1[A] += f->faceNormal[A]	* Faa;
    T1[B] += f->faceNormal[B]	* Fbb;
    T1[C] += f->faceNormal[C]	* Fcc;
    T2[A] += f->faceNormal[A]	* Faaa;
    T2[B] += f->faceNormal[B]	* Fbbb;
    T2[C] += f->faceNormal[C]	* Fccc;
    TP[A] += f->faceNormal[A]	* Faab;
    TP[B] += f->faceNormal[B]	* Fbbc;
    TP[C] += f->faceNormal[C]	* Fcca;

  }

  T1[X]	/= 2; T1[Y] /= 2; T1[Z]	/= 2;
  T2[X]	/= 3; T2[Y] /= 3; T2[Z]	/= 3;
  TP[X]	/= 2; TP[Y] /= 2; TP[Z]	/= 2;
}

void IndexedFaceSet::findAverageVertex(double point[3])
{
	point[0] = point[1] = point[2] = 0.0;
    for (int i = 0; i <m_NumVertices; i++)
	{
	  double x = m_Vertices[i][0];
	  double y = m_Vertices[i][1];
	  double z = m_Vertices[i][2];

	  point[0] += x;
	  point[1] += y;
	  point[2] += z;
	}
 
    point[0] /=m_NumVertices;
    point[1] /=m_NumVertices;
    point[2] /=m_NumVertices;
}

// computeContMassProperties:
//
// Computes accurately the mass,volume and the	moments	of inertia of an object	given its mass density.
// Also returns the centre of mass and the principle axes for the geometry.
//
// Based on code from:
// Brian Mirtich, "Fast	and Accurate Computation of Polyhedral Mass Properties"
//		journal	of graphics tools, volume 1, number 2, 1996.		       
//		mirtich@cs.berkeley.edu, http://www.cs.berkeley.edu/~mirtich		       *
//
// NOTE: inertiaTensor is a diagonal matrix, so it is the inertia tensor of the geometry
//	 when the geometry is aligned with its principle axes. 
// 
void IndexedFaceSet::computeContMassProperties(double density, double *mass, double moments[3])
{
  double volume, inerTensor[3][3], principleAxes[3][3];

  m_Density = density;
  compVolumeIntegrals();

  
  volume = T0;
  *mass	= m_Density * T0;
  
  // compute center of mass 
  m_comContinuous[X] = T1[X] / T0;
  m_comContinuous[Y] = T1[Y] / T0;
  m_comContinuous[Z] = T1[Z] / T0;

  // compute inertia tensor 
  inerTensor[X][X] = density * (T2[Y] +	T2[Z]);
  inerTensor[Y][Y] = density * (T2[Z] +	T2[X]);
  inerTensor[Z][Z] = density * (T2[X] +	T2[Y]);
  inerTensor[X][Y] = inerTensor[Y][X] =	- density * TP[X];
  inerTensor[Y][Z] = inerTensor[Z][Y] =	- density * TP[Y];
  inerTensor[Z][X] = inerTensor[X][Z] =	- density * TP[Z];

  // translate inertia tensor to center	of mass	
  inerTensor[X][X] -= *mass * (m_comContinuous[Y]*m_comContinuous[Y] + m_comContinuous[Z]*m_comContinuous[Z]);
  inerTensor[Y][Y] -= *mass * (m_comContinuous[Z]*m_comContinuous[Z] + m_comContinuous[X]*m_comContinuous[X]);
  inerTensor[Z][Z] -= *mass * (m_comContinuous[X]*m_comContinuous[X] + m_comContinuous[Y]*m_comContinuous[Y]);
  inerTensor[X][Y] = inerTensor[Y][X] += *mass * m_comContinuous[X]*m_comContinuous[Y];
  inerTensor[Y][Z] = inerTensor[Z][Y] += *mass * m_comContinuous[Y]*m_comContinuous[Z];
  inerTensor[Z][X] = inerTensor[X][Z] += *mass * m_comContinuous[Z]*m_comContinuous[X];
 
  // Find principle axes and diagonalize the inertia tensor. Use jacobi transformations to perform
  // a set of planar rotations that will diagonalize the inertia tensor matrix.
  //
  int nrot; // Number of jacobi rotations required.

  extern void jacobi(double **, int , double *, double **, int *); // in jacobi.cxx
  extern double **matrix(int , int , int , int ); // in jacobi.cxx
  extern double *vector(int , int );

  // Must create special matrix structures with indexing starting at 1 for
  // Numerical Recipes code.
  double **wTensor = matrix(1,3,1,3);
  int i,j;
  // Copy inertia tensor to Numerical Recipes matrix format.
  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3; j++)
		  wTensor[i+1][j+1] = inerTensor[i][j];
 
  double **wAxes = matrix(1,3,1,3);
  double *wEigenvals = vector(1,3);
  jacobi(wTensor,3,wEigenvals, wAxes, &nrot);
  for (i = 0; i < 3; i++) {
	  for (j = 0; j < 3; j++)
		  principleAxes[i][j] = wAxes[i+1][j+1];
	  moments[i] = wEigenvals[i+1];
  }
  

  danceTcl::OutputMessage("Jacobi transformations completed with %d rotations.\n",nrot);
  danceTcl::OutputMessage("Moments are: (%f,%f,%f) and\n",m_Moments[0],m_Moments[1],m_Moments[2]);
  danceTcl::OutputMessage("X axis: (%f,%f,%f), Y axis: (%f,%f,%f), Z axis: (%f,%f,%f)\n",
	principleAxes[0][0],principleAxes[1][0],principleAxes[2][0],
	principleAxes[0][1],principleAxes[1][1],principleAxes[2][1],
	principleAxes[0][2],principleAxes[1][2],principleAxes[2][2]);


  transform(m_comContinuous, principleAxes);

  m_comContinuous[0] = m_comContinuous[1] = m_comContinuous[2] = 0.0;
}

void IndexedFaceSet::computeDiscMassProperties(double massPt, double *mass, double moments[3])
{
  double volume, inerTensor[3][3], principleAxes[3][3];

  volume = computeVolume();
  m_MassPt = massPt;
 
  *mass	= massPt *m_NumVertices;

  // compute inertia tensor 
  double Ixx = 0.0, Iyy = 0.0, Izz = 0.0, Ixy = 0.0, Iyz = 0.0, Izx = 0.0;
 
  int i ;
  m_comDiscrete[0] = m_comDiscrete[1] = m_comDiscrete[2] = 0.0;
  for (i = 0; i <m_NumVertices; i++)
  {
	  double x = m_Vertices[i][0];
	  double y = m_Vertices[i][1];
	  double z = m_Vertices[i][2];

	  m_comDiscrete[0] += x;
	  m_comDiscrete[1] += y;
	  m_comDiscrete[2] += z;

	  Ixx += y*y + z*z;
	  Iyy += z*z + x*x;
	  Izz += x*x + y*y;

	  Ixy += x*y;
	  Iyz += y*z;
	  Izx += z*x;
  }

  m_comDiscrete[0] /=m_NumVertices;
  m_comDiscrete[1] /=m_NumVertices;
  m_comDiscrete[2] /=m_NumVertices;

  inerTensor[X][X] = massPt * Ixx;
  inerTensor[Y][Y] = massPt * Iyy;
  inerTensor[Z][Z] = massPt * Izz;
  inerTensor[X][Y] = inerTensor[Y][X] =	- massPt * Ixy;
  inerTensor[Y][Z] = inerTensor[Z][Y] =	- massPt * Iyz;
  inerTensor[Z][X] = inerTensor[X][Z] =	- massPt * Izx;

  // translate inertia tensor to center	of mass	
  inerTensor[X][X] -= *mass * (m_comDiscrete[Y]*m_comDiscrete[Y] + m_comDiscrete[Z]*m_comDiscrete[Z]);
  inerTensor[Y][Y] -= *mass * (m_comDiscrete[Z]*m_comDiscrete[Z] + m_comDiscrete[X]*m_comDiscrete[X]);
  inerTensor[Z][Z] -= *mass * (m_comDiscrete[X]*m_comDiscrete[X] + m_comDiscrete[Y]*m_comDiscrete[Y]);
  inerTensor[X][Y] = inerTensor[Y][X] += *mass * m_comDiscrete[X]*m_comDiscrete[Y];
  inerTensor[Y][Z] = inerTensor[Z][Y] += *mass * m_comDiscrete[Y]*m_comDiscrete[Z];
  inerTensor[Z][X] = inerTensor[X][Z] += *mass * m_comDiscrete[Z]*m_comDiscrete[X];



  // Find principle axes and diagonalize the inertia tensor. Use jacobi transformations to perform
  // a set of planar rotations that will diagonalize the inertia tensor matrix.
  //
  int nrot; // Number of jacobi rotations required.

  extern void jacobi(double **, int , double *, double **, int *); // in jacobi.cxx
  extern double **matrix(int , int , int , int ); // in jacobi.cxx
  extern double *vector(int , int );

  // Must create special matrix structures with indexing starting at 1 for
  // Numerical Recipes code.
  double **wTensor = matrix(1,3,1,3);
  int j;
  // Copy inertia tensor to Numerical Recipes matrix format.
  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3; j++)
		  wTensor[i+1][j+1] = inerTensor[i][j];
 
  double **wAxes = matrix(1,3,1,3);
  double *wEigenvals = vector(1,3);
  jacobi(wTensor,3,wEigenvals, wAxes, &nrot);
  for (i = 0; i < 3; i++) {
	  for (j = 0; j < 3; j++)
		  principleAxes[i][j] = wAxes[i+1][j+1];
	  moments[i] = wEigenvals[i+1];
  }
  
/*
  printf("Jacobi transformations completed with %d rotations.\n",nrot);
  printf("Moments are: (%f,%f,%f) and\n",moments[0],moments[1],moments[2]);
  printf("X axis: (%f,%f,%f), Y axis: (%f,%f,%f), Z axis: (%f,%f,%f)\n",
	principleAxes[0][0],principleAxes[1][0],principleAxes[2][0],
	principleAxes[0][1],principleAxes[1][1],principleAxes[2][1],
	principleAxes[0][2],principleAxes[1][2],principleAxes[2][2]);
*/

  transform(m_comDiscrete, principleAxes);
  m_comDiscrete[0] = m_comDiscrete[1] = m_comDiscrete[2] = 0.0;
}


// the points must be preallocated by geometry
int IndexedFaceSet::createMonitorPoints(int npoints)
{
    
    if( (m_NumVertices == 0) || (npoints <= 0) ) return 0 ;


    if( m_NumVertices < npoints ) m_MonitorPoints.m_NumPoints = m_NumVertices ;
    else m_MonitorPoints.m_NumPoints = npoints ;
   
    int skip = (int) (m_NumVertices / npoints ) ;
	if( skip == 0 ) skip = 1 ;
    int count = 0, numPoints = 0  ;
    for( int i = 0 ; (i < m_NumVertices) && ( numPoints < npoints) ; i++ )
    {
	count++ ;
	if( count == skip )
	{
	    VecCopy(m_MonitorPoints.m_Point[numPoints], m_Vertices[i]) ;
	    count = 0 ;
	    numPoints++ ;
	}
	    
    }
    danceTcl::OutputMessage("Number of vertices %d number of mnts %d\n", m_NumVertices,
	   m_MonitorPoints.m_NumPoints) ;
	
    return m_MonitorPoints.m_NumPoints ;
}


int IndexedFaceSet::addNormalToFace(int index, int numNormals, int * normIndices)
{
	if (index < 0 || index >= m_NumFaces) return -1;

    /**
    // Check if normals are the same for all vertices. If so,
    // optimize so we store only one normal per face, rather than
    // per vertex.
    int faceNormal = 1;

    int testindex;
    for (int i=0; i < numNormals; i++) {
	if (i==0) {
		testindex = normIndices[i];
	}
	else if (testindex != normIndices[i]) {
		faceNormal = 0;
		break;
	}
    }
    if (faceNormal) 
	numNormals = 1;
	**/

    // Allocate memory for normals in IndexedFace class.
    m_Faces[index].numNormals = numNormals;
    if (m_Faces[index].normalIndex) 
		delete [] m_Faces[index].normalIndex;
    m_Faces[index].normalIndex = new int[numNormals];
    memcpy(m_Faces[index].normalIndex,normIndices,numNormals*sizeof(int));

    return OK;
}

// prepareCollision:
// Uses RAPID to build an Oriented Bounding Box for the indexed
// face set.
//
int IndexedFaceSet::PrepareCollision(void)
{
	if (m_AllTriangles == FALSE) {
			danceTcl::OutputMessage("ERROR: RAPID code only works when all"
						" faces are triangles.\n");
			return TCL_ERROR;
	}

	if (m_RAPIDmodel) delete m_RAPIDmodel;
	m_RAPIDmodel = new RAPID_model;
	if (m_RAPIDmodel == NULL) {
		danceTcl::OutputMessage("ERROR: Could not allocate memory for RAPID object.\n");
		return TCL_ERROR;
	}

	m_RAPIDmodel->BeginModel();

	for (int i=0; i < m_NumFaces; i++) {
		int i1 = m_Faces[i].vertexIndex[0];
		int i2 = m_Faces[i].vertexIndex[1];
		int i3 = m_Faces[i].vertexIndex[2];

		m_RAPIDmodel->AddTri(m_Vertices[i1], m_Vertices[i2], m_Vertices[i3], i);
	}

	m_RAPIDmodel->EndModel();
	danceTcl::OutputResult("Successfully created RAPID Oriented Bounding Box (OBB).\n");
	return TCL_OK;
}

// output information for DGeometry
void IndexedFaceSet::printFile(char *filename)
{

	FILE *fptr = fopen(filename,"a");
	print(fptr);
	fclose(fptr);
}

// print save information to reconstruct this geometry
void IndexedFaceSet::print(FILE * fptr)
{
	// Strip out the leading path of the filename. We are assuming geometry
	// is in standard location $(DANCE_DIR)/geometry/models
	char *fname = getFileName();
	
	char *tail = NULL;
	char prefix[256];
	sprintf(prefix,"%s/data/models",getenv("DANCE_DIR"));
	// Strips off the standard path.
	if (strncmp(prefix,fname,strlen(prefix)) == 0) 
		tail = &(fname[strlen(prefix)+1]);
	else
		tail = fname;

	fprintf(fptr,"instance %s %s %s\n",getType(),getName(),tail);

	if (m_MassPropertiesType == 1) 
		fprintf(fptr,"geometry %s calcMassProperties continuous %f\n",getName(),m_Density);
	else if (m_MassPropertiesType == 2)
		fprintf(fptr,"geometry %s calcMassProperties discrete %f\n",getName(),m_MassPt);

	if (m_RAPIDmodel)
		fprintf(fptr,"geometry %s setupCollision\n",getName());
}

void IndexedFaceSet::transform(double com [ 3 ], double refFrame [ 3 ] [ 3 ])
{
	// Translate all points to the new com position.
	int i,j;
	for (i = 0; i <m_NumVertices; i++) {
		for (j = 0; j < 3; j++) 
			m_Vertices[i][j] -= com[j];

		Vector newPt = {0.0,0.0,0.0};
		for (j = 0; j < 3; j++) 
			// Rotate the vertices to align themselves to the principle axes store in refFrame.
			newPt[j] = refFrame[0][j]*m_Vertices[i][0]+refFrame[1][j]*m_Vertices[i][1]+refFrame[2][j]*m_Vertices[i][2];
		memcpy(m_Vertices[i],newPt,3*sizeof(double));
	}

	// Transform the normals to the new reference frame. Since we are only rotating,
	// we do not have to use the inverse-transpose matrix (which would be need if nonuniform
	// scaling is present).
	Vector newNorm = {0.0,0.0,0.0};
	for (i = 0; i < m_NumNormals; i++) { 
		for (j = 0; j < 3; j++)
			newNorm[j] = refFrame[0][j]*m_Normals[i][0]+refFrame[1][j]*m_Normals[i][1]+refFrame[2][j]*m_Normals[i][2];
		memcpy(m_Normals[i],newNorm,3*sizeof(double));
	}
	

	// Recalculate face properties.
	compFaceProperties();

	// Recalculate bounding box.
	calcBoundingBox();
}

void IndexedFaceSet::displayNormals()
{
	// Turn off lighting temporarily if its on.
	int prevL = glIsEnabled(GL_LIGHTING);
	if (prevL == TRUE) glDisable(GL_LIGHTING);


	// Loop through all faces.
	glBegin(GL_LINES);
	for (int i = 0; i < m_NumFaces; i++) {

		double avg_length = m_Faces[i].avgSideLength;

	/*  // Comment out for per-vertex normals
		for (int v = 0; v < m_Faces[i].numVertices; v++)
		{
			double x = m_Vertices[m_Faces[i].vertexIndex[v]][0];
			double y = m_Vertices[m_Faces[i].vertexIndex[v]][1];
			double z = m_Vertices[m_Faces[i].vertexIndex[v]][2];

			// Draw polygons per vertex.
			glColor4f(1.0,1.0,0.0,1.0); // yellow arrow
			if (m_Faces[i].numNormals > 1) {
				glBegin(GL_LINES);
				glVertex3dv(m_Vertices[m_Faces[i].vertexIndex[v]]);
				glVertex3d( 
					       x+avg_length*m_Normals[m_Faces[i].normalIndex[v]][0],
						   y+avg_length*m_Normals[m_Faces[i].normalIndex[v]][1],
						   z+avg_length*m_Normals[m_Faces[i].normalIndex[v]][2]);
				glEnd();
			}
		}
       */
		double *centroid= m_Faces[i].centroid;

		/*
		// Display face normal provided by import.
	    if (m_Faces[i].numNormals == 1) {
		
		    glVertex3dv(centroid);
			glVertex3d(centroid[0] + avg_length*m_Normals[m_Faces[i].normalIndex[0]][0],
					   centroid[1] + avg_length*m_Normals[m_Faces[i].normalIndex[0]][1],
					   centroid[2] + avg_length*m_Normals[m_Faces[i].normalIndex[0]][2]);
		}
		*/

		// Display computed face per normal.
		glColor4f(1.0,0.0,1.0,1.0);
		glVertex3dv(centroid);
		glVertex3d(centroid[0]+avg_length*m_Faces[i].faceNormal[0],
				   centroid[1]+avg_length*m_Faces[i].faceNormal[1],
				   centroid[2]+avg_length*m_Faces[i].faceNormal[2]);
	}
	glEnd();

	if (prevL) glEnable(GL_LIGHTING);
}

// BuildEdges:
//
// Loops through all stored polygons and builds up the edge lists for each vertex.
// Also fills in the WingedEdge data structure via a method call. 
//
// Returns the number of edges created.
int IndexedFaceSet::BuildEdges()
{
	m_NumEdges = 0;

	// Loop through all faces.
	for (int i = 0; i < m_NumFaces; i++) {
		// Loop through all edges of this face.
		for (int j = 0; j < m_Faces[i].numVertices; j++) {
			int v1 = m_Faces[i].vertexIndex[j];
			int v2 = m_Faces[i].vertexIndex[(j+1) % m_Faces[i].numVertices];
			ProcessEdge(v1,v2,i);
		}
	}
	return (m_NumEdges);
}

// ProcessEdge:
//		Adds to the list of WingedEdges if applicable.
//	
// Returns 1 if modified a WingedEdge structure, 0 if WingedEdge already defined.
//
int IndexedFaceSet::ProcessEdge(int v1, int v2, int face)
{
	// Check if v2 is in v1's edgelist.
	WingedEdge *foundedge = NULL;
	int inList = 0;
	for (int i = 0; i < m_VertexEdges[v1].m_numEdges; i++) {
		WingedEdge *edge = &(m_EdgeList[m_VertexEdges[v1].m_Edges[i]]);
		if (edge->v1 == v2) {
			inList = 1; foundedge = edge;
			break;
		}
		if (edge->v2 == v2) {
			inList = 2; foundedge = edge;
			break;
		}		
	}

	if (inList == 1) { // Edge found but traversing in opposite direction.
		// Add face to f2 of WingedEdge
		foundedge->f2 = face;
		return 1;
	}

	if (inList == 2) // Found a duplicate edge, so we just return.
		return 0;
	
    // Create a WingedEdge structure.
    if(m_NumEdges % EDGE_CHUNK_SIZE == 0 )
    {
		int numChunks = m_NumEdges	/ EDGE_CHUNK_SIZE ;
		// time	to allocate a chunk of memory
		numChunks++ ;
		WingedEdge *tmp = new WingedEdge[numChunks*EDGE_CHUNK_SIZE] ;
		if( tmp == NULL )
		{
			fprintf(stderr,"IndexedFaceSet::ProcessEdge Cannot allocate memory!\n") ;
			return ERR;
		}
	
		if (m_EdgeList) {
			memcpy(tmp,m_EdgeList,m_NumEdges*sizeof(WingedEdge));
			delete [] m_EdgeList;
		}
		m_EdgeList = tmp;
    }

	m_EdgeList[m_NumEdges].v1 = v1;
	m_EdgeList[m_NumEdges].v2 = v2;
	m_EdgeList[m_NumEdges].f1 = face;

	// Add this edge to each of the vertices.
	int nEdges = ++m_VertexEdges[v1].m_numEdges;
	int *tmpEdge = m_VertexEdges[v1].m_Edges;
	
	m_VertexEdges[v1].m_Edges = new int[nEdges];
	if (nEdges > 1)
		memcpy(m_VertexEdges[v1].m_Edges,tmpEdge,(nEdges-1)*sizeof(int));
	m_VertexEdges[v1].m_Edges[nEdges-1] = m_NumEdges;
	
	nEdges = ++m_VertexEdges[v2].m_numEdges;
	tmpEdge = m_VertexEdges[v2].m_Edges;
	m_VertexEdges[v2].m_Edges = new int[nEdges];
	if (nEdges > 1)
		memcpy(m_VertexEdges[v2].m_Edges,tmpEdge,(nEdges-1)*sizeof(int));
	m_VertexEdges[v2].m_Edges[nEdges-1] = m_NumEdges;

	m_NumEdges++;

	return(1);
}

void IndexedFaceSet::DisplayFaces(int buildList)
{
    if (buildList)
	glNewList(m_ID,GL_COMPILE);
    
    for( int i = 0 ; i < m_NumFaces ; i++ )
    {
	// We can only set material colors in non-display list mode, otherwise
	// the alpha value is overridden and cannot get transparency.
	if (m_Faces[i].materialIndex >= 0 && buildList == 0)
	    glColor4f(m_Materials[m_Faces[i].materialIndex].mDiffuseColor[0],
				  m_Materials[m_Faces[i].materialIndex].mDiffuseColor[1],
				  m_Materials[m_Faces[i].materialIndex].mDiffuseColor[2],
				  1.0f-m_Transparency);
	
	
	glBegin(GL_POLYGON) ;
	if (m_Faces[i].numNormals == 0) 
		glNormal3dv(m_Faces[i].faceNormal);
	else if (m_Faces[i].numNormals == 1)
	    glNormal3dv(m_Normals[m_Faces[i].normalIndex[0]]);
	
	double avg_length = 0.0;
	for( int j = 0 ; j < m_Faces[i].numVertices ;	j++ )
	{
	    if (m_Faces[i].numNormals > 1)
	    {
		glNormal3dv(m_Normals[m_Faces[i].normalIndex[j]]) ;
	    }
	    glVertex3dv(m_Vertices[m_Faces[i].vertexIndex[j]]) ;
	}
	glEnd() ; // GL_POLYGON
    }

    if (buildList)
	glEndList();

}

// PROC:    SetOrigin()
// DOES: The vertices are substituted with their distance with respect
//       to orgn. In other words the origin of the geometry becomes orgn
void IndexedFaceSet::SetOrigin(Vector orgn)
{
    for( int i = 0 ; i < m_NumVertices ; i++ )
    {
	VecSubtract(m_Vertices[i], m_Vertices[i], orgn) ;
    }
    UpdateParamsAndDispList() ;
}

// PROC:   Center()
// DOES: Centers the geometry around the geometric
//       center of the vertices
void IndexedFaceSet::Center(void)
{
    Vector center ;

    findAverageVertex(center) ;
    SetOrigin(center) ;
}


// if center is 1 then rotation around the center of the bounding box
// else rotate around the origin of the cs of the vertices 
void IndexedFaceSet::Rotate(char *axis, double degrees, int center)
{
    if( m_NumVertices == 0 ) return ;
    
    Vector gcenter ;

    if( center == 1 )
    {
	calcBoundingBox() ;
	gcenter[0] = (m_BoundingBox.xMax + m_BoundingBox.xMin)*0.5 ;
	gcenter[1] = (m_BoundingBox.yMax + m_BoundingBox.yMin)*0.5 ;
	gcenter[2] = (m_BoundingBox.zMax + m_BoundingBox.zMin)*0.5 ;
    
	SetOrigin(gcenter) ;
    }
    
    if( strcmp(axis, "x") == 0 )
    {
	XRotatePoints(m_Vertices, m_NumVertices, degrees) ;
	XRotatePoints(m_Normals, m_NumNormals, degrees) ;
    }
    else if( strcmp(axis, "y") == 0 )
    {
	YRotatePoints(m_Vertices, m_NumVertices, degrees) ;
	YRotatePoints(m_Normals, m_NumNormals, degrees) ;
    }
    else  if( strcmp(axis, "z") == 0 )
    {
	ZRotatePoints(m_Vertices, m_NumVertices, degrees) ;
	ZRotatePoints(m_Normals, m_NumNormals, degrees) ;
    }
    else
	danceTcl::OutputMessage("ERROR: IndexedFaceSet::Rotate: Invalid axis.\n") ;

    if( center == 1 )
    {
	// bring the origin back to its original place
	for( int i = 0 ; i < m_NumVertices ; i++ )
	{
	    VecAdd(m_Vertices[i], m_Vertices[i], gcenter) ;
	}
    }

    UpdateParamsAndDispList() ;
}

// relative translation
void IndexedFaceSet::Translate(double x, double y, double z)
{
    if( m_NumVertices == 0 ) return ;

    Vector t ;
    setVector(t, x, y, z) ;
    for( int i = 0 ; i < m_NumVertices ; i++ )
    {
	VecAdd(m_Vertices[i], m_Vertices[i], t) ;
    }

    UpdateParamsAndDispList() ;
}


// scaling. If center is 1 then rotate around the center 
// of the bounding box of this geometry.
void IndexedFaceSet::Scale(double sx, double sy, double sz, int center = 0)
{
    if( m_NumVertices == 0 ) return ;

    Vector gcenter ;
    
    if( center == 1 )
    {
	calcBoundingBox() ;
	gcenter[0] = (m_BoundingBox.xMax + m_BoundingBox.xMin)*0.5 ;
	gcenter[1] = (m_BoundingBox.yMax + m_BoundingBox.yMin)*0.5 ;
	gcenter[2] = (m_BoundingBox.zMax + m_BoundingBox.zMin)*0.5 ;
	
	SetOrigin(gcenter) ;
    }
    
    int i ;
    for( i = 0 ; i < m_NumVertices ; i++ )
    {
	m_Vertices[i][0] *= sx ;
	m_Vertices[i][1] *= sy ;
	m_Vertices[i][2] *= sz ;
    }

    if( center == 1 )
    {
	// bring the origin back to its original place
	for( i = 0 ; i < m_NumVertices ; i++ )
	{
	    VecAdd(m_Vertices[i], m_Vertices[i], gcenter) ;
	}
    }
    
    UpdateParamsAndDispList() ;
    
}

    
void IndexedFaceSet::UpdateParamsAndDispList(void)
{
    // update parameters that depend on the vertices
    calcBoundingBox() ;
    compFaceProperties() ;
    
    // delete the display list if it exists and 
    // note the deletion
    if( m_DisplayList == TRUE )
	glDeleteLists(m_ID, 1) ;
    m_DisplayList = FALSE ;
}

IndexedFace::IndexedFace()
{
    numVertices = 0 ;
    numNormals = 0 ;
    vertexIndex = NULL ;
    texCoordIndex = NULL ;
    normalIndex = NULL ;
    materialIndex = -1 ;
}

IndexedFace::~IndexedFace()
{
    if( vertexIndex == NULL ) delete [] vertexIndex ;
    if( texCoordIndex == NULL ) delete [] texCoordIndex ;
    if( normalIndex == NULL ) delete [] normalIndex ;
}


void IndexedFaceSet::assignMonitorPoints(int argc, char *argv[])
{
    if( AllocateMonitorPoints(argc) != argc ) return ;
    for( int i = 0 ; i < argc ; i++ )
    {
	int indx = atoi(argv[i]) ;
	if( (indx < 0) || (indx >= m_NumVertices ))
	{
	    danceTcl::OutputMessage("Error: index out of bounds!") ;
	    danceTcl::OutputMessage("MonitorPoints not assigned!\n") ;
	    DeleteMonitorPoints() ;
	    return ;
	}
	VecCopy(m_MonitorPoints.m_Point[i], m_Vertices[indx]) ;
    }
}

int IndexedFaceSet::parseTextureNode(Tcl_Interp *interp, FILE *fp)
{
	char token[MAX_LINE];

	fprintf(stderr,"Parsing texture node.\n");
	fscanf(fp,"%s",token);
	if (strcmp(token,"ImageTexture") == 0) {
		// Parsing image texture
		fscanf(fp,"%s",token);
		if (strcmp(token,"{") != 0) 
			return TCL_ERROR;
		fscanf(fp,"%s",token);
		if (strcmp(token,"url") == 0) {
			char filename[256];
			// Read until encounter first quote.
			while (fgetc(fp) != '\"');
			// Read in characters until next quote.
			char letter = (char)fgetc(fp);
			int count = 0;
			while (letter != '\"') {
				filename[count++] = letter;
				letter = (char)fgetc(fp);
			}
			filename[count] = '\0';
		}

		fscanf(fp,"%s",token);

		// Read until close quote or end of file.
		while (strcmp(token,"}") != 0 && !feof(fp)) 
			fscanf(fp,"%s",token);
		if (strcmp(token,"}") != 0)
			return TCL_ERROR;
			
	}
	return TCL_OK;
}

int IndexedFaceSet::addCoordsToFace(int index, int numCoords, int *coordIndices)
{
	if (index < 0 || index >= m_NumFaces) return 0;
	// Set these face entries.
	m_Faces[index].numVertices = numCoords;
	if (m_Faces[index].vertexIndex != NULL)
		delete [] m_Faces[index].vertexIndex;
	m_Faces[index].vertexIndex = new int[numCoords];
    memcpy(m_Faces[index].vertexIndex,coordIndices,numCoords*sizeof(int));
	return 1;
}

// Fills in the three vertices that correspond to the RAPID triangle
// with id id. Returns -1 on error or the id.
int IndexedFaceSet::GetRapidTriangle(int id, Vector v1, Vector v2, Vector v3 )
{
    if( (id < 0) || ( id > (m_NumFaces - 1) ) )
	return -1 ;
    else
    {
	VecCopy(v1, m_Vertices[m_Faces[id].vertexIndex[0]]) ;
	VecCopy(v2, m_Vertices[m_Faces[id].vertexIndex[1]]) ;
	VecCopy(v3, m_Vertices[m_Faces[id].vertexIndex[2]]) ;
	return id ;
    }
}

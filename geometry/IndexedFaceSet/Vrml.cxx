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

#include "IndexedFaceSet.h"
#include "danceTcl.h"
#include "assert.h"

static int FaceOffset  = 0;
static int NormalOffset = 0;
static int VertexOffset = 0;

static void outputMessage(Tcl_Interp *interp, char *s)
{
    Tcl_AppendResult(interp, s, (char *) NULL) ;
}

void IndexedFaceSet::BuildRotate(double mat[16], double x, double y, double z, double rad)
{
	// Taken from VRML 97 SFRotation Field specification
	double c = cos(rad);
	double s = sin(rad);
	double t = 1 - c;
	mat[0] = t*x*x + c;
	mat[1] = t*x*y + s*z;
	mat[2] = t*x*z - s*y;
	mat[4] = t*x*y - s*z;
	mat[5] = t*y*y + c;
	mat[6] = t*y*z + s*x;
	mat[8] = t*x*z + s*y;
	mat[9] = t*y*z - s*x;
	mat[10] = t*z*z + c;
}

void IndexedFaceSet::BuildTransform(int level, double mat[16])
{
	if (level < 0) {
		danceTcl::OutputMessage("BuildTransform called with negative level.");
		return;
	}

	if (level == 0) {
		memcpy(mat,m_TransformStack[level],16*sizeof(double));
		return;
	}

	double mat1[4][4]; memcpy(mat1,m_TransformStack[0],16*sizeof(double));
	double mat2[4][4];
	for (int k = 1; k <= level; k++) {
		memcpy(mat2,m_TransformStack[k],16*sizeof(double));

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) 
				mat[j*4+i] = mat1[0][i]*mat2[j][0] + mat1[1][i]*mat2[j][1] 
					       + mat1[2][i]*mat2[j][2] + mat1[3][i]*mat2[j][3];;
			
		memcpy(mat1,mat,16*sizeof(double));
	}
}

void IndexedFaceSet::BuildTranslate(double mat[16], double x, double y, double z)
{
	mat[12]  = x;
	mat[13]  = y;
	mat[14]  = z;
}

void IndexedFaceSet::BuildScale(double mat[16], double sx, double sy, double sz)
{
	mat[0] *= sx;
	mat[5] *= sy;
	mat[10] *= sz;
}

// saveMaterial:
//	Saves the material appearance node.
int IndexedFaceSet::saveMaterial(Tcl_Interp *interp, FILE *fptr) 
{
	if (m_Materials == NULL) return TCL_OK;

         fprintf(fptr,"     appearance Appearance {\n");

	 Material wMaterial; wMaterial = m_Materials[0];
	 if (m_NumMaterials > 1) 
	 	danceTcl::OutputMessage("WARNING: Only the first material will be output.\n");

 	 fprintf(fptr,"         material Material {\n");
         fprintf(fptr,"                 diffuseColor %f %f %f\n", 
		wMaterial.mDiffuseColor[0],wMaterial.mDiffuseColor[1],wMaterial.mDiffuseColor[2]);
         fprintf(fptr,"                 ambientIntensity %f\n", wMaterial.mAmbientColor[0]);
         fprintf(fptr,"                 specularColor %f %f %f\n",
	 	wMaterial.mSpecularColor[0],wMaterial.mSpecularColor[1],wMaterial.mSpecularColor[2]);
         fprintf(fptr,"                 emissiveColor %f %f %f\n",
	 	wMaterial.mEmissiveColor[0],wMaterial.mEmissiveColor[1],wMaterial.mEmissiveColor[2]);
	 fprintf(fptr,"                 shininess %f\n", wMaterial.mShininess);
	 fprintf(fptr,"                 transparency %f\n",1.0-wMaterial.mDiffuseColor[3]);
         fprintf(fptr,"         }\n");
         fprintf(fptr,"     }\n");

	 return TCL_OK;
}

// saveVRML: saves the IndexedFaceSet as a VRML 2.0 wrl file.
//	Only saves the Shape node.
//
int IndexedFaceSet::saveVRML(Tcl_Interp *interp, char *filename)
{
	int i,j;

	FILE *fptr = fopen(filename,"w");
	if (fptr == NULL) return  TCL_ERROR;

        // Write proper VRML 2.0 header
	fprintf(fptr,"#VRML V2.0 utf8\n");

	fprintf(fptr,"# Original file: %s\n",getFileName());
	fprintf(fptr,"# Resaved using DANCE, IndexedFaceSet plugin\n");
	fprintf(fptr,"\nShape {\n");

	// Output appearance node
	saveMaterial(interp,fptr);

	// Output IndexedFaceSet
	fprintf(fptr,"     geometry IndexedFaceSet {\n");

	// Output vertices.
	fprintf(fptr,"          coord Coordinate {\n");
	fprintf(fptr,"                point [ # %d vertices\n",m_NumVertices);
	for (i = 0; i < m_NumVertices; i++) {
		fprintf(fptr,"                     %f %f %f",
			m_Vertices[i][0],m_Vertices[i][1],m_Vertices[i][2]);
		if (i == m_NumVertices-1) 
			fprintf(fptr,"\n");
		else
			fprintf(fptr,",\n");
	}
	fprintf(fptr,"	       ]\n");
	fprintf(fptr,"          } # End of Coordinate\n");

	// Output polygons.
	fprintf(fptr,"           # %d polygons\n",m_NumFaces);
	fprintf(fptr,"           coordIndex [\n");
	for (i = 0; i < m_NumFaces;i ++) {
		fprintf(fptr,"                ");
		for (j = 0; j < m_Faces[i].numVertices; j++) 
			fprintf(fptr,"%d,",m_Faces[i].vertexIndex[j]);
		if (i == m_NumFaces-1)
			fprintf(fptr,"-1\n");
                else
			fprintf(fptr,"-1,\n");
	}
	fprintf(fptr,"           ]\n");

	// Output normals.
	fprintf(fptr,"           normal Normal {\n");
	fprintf(fptr,"                  vector [  # %d normals\n",m_NumNormals);
	for (i = 0; i < m_NumNormals; i++) {
		fprintf(fptr,"                       %f %f %f",
			m_Normals[i][0],m_Normals[i][1],m_Normals[i][2]);
		if (i == m_NumNormals-1)
			fprintf(fptr,"\n");
                else
			fprintf(fptr,",\n");	
	}
	fprintf(fptr,"                  ]\n");
	fprintf(fptr,"           } # End of normals\n");

	// Output normalIndices
	fprintf(fptr,"           normalIndex [\n");
	for (i = 0; i < m_NumFaces; i++) {
		fprintf(fptr,"                  ");
		for (j = 0; j < m_Faces[i].numNormals; j++) 
			fprintf(fptr,"%d,",m_Faces[i].normalIndex[j]);
		if (i == m_NumFaces-1)
			fprintf(fptr,"-1\n");
                else
			fprintf(fptr,"-1,\n");

	}
	fprintf(fptr,"           ]\n");
	
	fprintf(fptr,"     } # End of IndexedFaceSet\n");
	fprintf(fptr,"} # End of shape node.\n");
	fflush(fptr);
	fclose(fptr);
	return TCL_OK;
}

// parseBONE: parses the given BONE file and fills in the data structure.
//
int IndexedFaceSet::parseBONE(Tcl_Interp *interp, char *filename)
{
	FILE *fp = fopen(filename,"r");
	if (fp == NULL) return TCL_ERROR;

	char token[MAX_LINE];

	// Parse only geometry nodes until end-of-file
	FaceOffset = 0;
	NormalOffset = 0;
	VertexOffset = 0;

	int result = 0;
	// Read in the vertex list.
	result = fscanf(fp,"%s",token);
	if (result == 1 && strcmp(token,"vertices") == 0) {
		int numVertices = 0;
		fscanf(fp,"%d",&numVertices);
		for (int i = 0; i < numVertices; i++) {
			double x,y,z;
			fscanf(fp,"%lf %lf %lf", &x,&y,&z);

			if (m_MirrorGeometry) x = -1.0*x;
			
			addVertex(x,y,z);
		}
			
	}
	else {
		fclose(fp);
		return TCL_ERROR;
	}

	// Read in polygon list.
	int vertexList[MAX_VERT_FACE];

	result = fscanf(fp,"%s",token);
	if (result == 1 && strcmp(token,"polygons") == 0) {
		int numPolys = 0;
		int numFaces = 0;
		fscanf(fp,"%d",&numPolys);
		for (int i = 0; i < numPolys; i++) {
			int numPoints = 0;
			fscanf(fp,"%d",&numPoints);
			assert(numPoints <= MAX_VERT_FACE);
			for (int j = 0; j < numPoints; j++)
				// Load in vertices backwards to reverse orientation
				// of polygons.
				if (m_MirrorGeometry)
					fscanf(fp,"%d",&(vertexList[j]));
				else
					fscanf(fp,"%d",&(vertexList[numPoints-1-j]));
			if (numPoints > 3) {
					int numTriangles = numPoints - 2;

					// First index is common to all triangles. We must ensure
					// the vertex order is counter-clockwise for front facing.
					int triVertices[3];
					triVertices[0] = vertexList[0];
					for (int i = 1; i <= numTriangles; i++) {
						triVertices[1] = vertexList[i];
						triVertices[2] = vertexList[i+1];
						addFace(FaceOffset+numFaces);
						addCoordsToFace(FaceOffset+numFaces,3,triVertices);
						numFaces++;
					}
			}
			else {
				addFace(FaceOffset+numFaces);
				addCoordsToFace(FaceOffset+numFaces,numPoints,vertexList);
				numFaces++;
			}
		}

	}
	else {
		fclose(fp);
		return TCL_ERROR;
	}

    fclose(fp);

	// Give a default boney-milk color
	m_Color[0] = m_Color[1] = m_Color[2] = 0.8f;

	// A successfully parsed BONE ensures all faces are triangles.
	m_AllTriangles = TRUE;

	danceTcl::OutputResult("Read in %d vertices, %d normals, %d faces\n",m_NumVertices, m_NumNormals, m_NumFaces);

	// Build edge list.
	BuildEdges();
	danceTcl::OutputResult("Number of edges found: %d\n",m_NumEdges);
	
    return(TCL_OK);
  
}

// parseVRML: parses the given VRML file and fills in the data structure.
//	    Allocates the memory necessary.
//	    All	the vertices become monitor points
int IndexedFaceSet::ParseVRML(Tcl_Interp *interp, char *filename)
{

	FILE *fp = fopen(filename,"r");
	if (fp == NULL) return TCL_ERROR;

	danceTcl::OutputMessage("Loading in %s",filename);

    char token[MAX_LINE];	

	// Parse only geometry nodes until end-of-file
	FaceOffset = 0;
	NormalOffset = 0;
	VertexOffset = 0;

	int result = 0;
	
	do {
		result = fscanf(fp,"%s",token);
		if (result > 0)	{
			if (strcmp(token,"#") == 0) 
				ParseComment(interp,fp);
			else if (strcmp(token,"Shape") == 0) {
				if (TCL_ERROR ==  ParseShapeNode(interp,fp,-1)) {
					danceTcl::OutputMessage("Parse Error: in Shape Node.");
					danceTcl::OutputMessage("Make sure brackets are surrounded"
								" by spaces") ;
					fclose(fp);
					return TCL_ERROR;
				}
			}
			else if (strcmp(token,"Transform") == 0) {
				if (TCL_ERROR == ParseTransform(interp,fp,0)) {
					danceTcl::OutputMessage("Parse Error: in Transform Node.");
					fclose(fp);
					return TCL_ERROR;
				}
			}
			else if (strcmp(token,"Separator") == 0) {
				if (TCL_ERROR == ParseShapeNode(interp,fp,-1)) {
					danceTcl::OutputMessage("Parse Error: in Separator Node.");
					danceTcl::OutputMessage("Make sure brackets are surrounded"
								" by spaces") ;
					fclose(fp);
					return TCL_ERROR;
				}
			}
		}
	} while	(!feof(fp));
    fclose(fp);

	// A successfully parsed VRML ensures all faces are triangles.
	m_AllTriangles = TRUE;

	danceTcl::OutputResult("Read in %d vertices, %d normals, %d faces\n",m_NumVertices, m_NumNormals, m_NumFaces);

	// Build edge list.
	BuildEdges();
	danceTcl::OutputResult("Number of edges found: %d\n",m_NumEdges);

    return(TCL_OK);
  
}

// parseAppearanceNode:
int IndexedFaceSet::parseAppearanceNode(Tcl_Interp *interp, FILE *fp)
{
	danceTcl::OutputMessage("Parsing Appearance node.\n");
	char token[MAX_LINE];

        fscanf(fp,"%s",token);
	if (strcmp(token,"{") != 0) {
		danceTcl::OutputMessage("Parse error: expected { for Appearance node.\n");
		return TCL_ERROR;
	}
	fscanf(fp,"%s",token);
	while (strcmp(token,"}") != 0  && !feof(fp)) {
		if (strcmp(token,"#") == 0)
			ParseComment(interp,fp);
        else if (strcmp(token,"material") == 0) {
			danceTcl::OutputMessage("Found material field.\n");
			if (TCL_ERROR == parseMaterialNode(interp,fp)) 
				return TCL_ERROR;
		}
		else if (strcmp(token,"texture") == 0) {
			danceTcl::OutputMessage("Found texture field.\n");
			if (TCL_ERROR == parseTextureNode(interp,fp))
				return TCL_ERROR;
		}
		fscanf(fp,"%s",token);
	}

	if (strcmp(token,"}") != 0) {
		danceTcl::OutputMessage("Error parsing Appearance node. Expect }\n");	
		return TCL_ERROR;
	}
	return TCL_OK;
}

// ParseChildren:
//
int IndexedFaceSet::ParseChildren(Tcl_Interp *interp, FILE *fp, int level)
{
	danceTcl::OutputMessage("Parsing children node.");

	char token[256];
	fscanf(fp,"%s",token);

	if (strcmp(token,"[") != 0) {
		danceTcl::OutputMessage("Parse Error: children node expecting [");
		return TCL_ERROR;
	}
	fscanf(fp,"%s",token);
	while (strcmp(token,"]") != 0) {
		if (strcmp(token,"Shape") == 0) {
			if (TCL_ERROR == ParseShapeNode(interp,fp,level)) {
				danceTcl::OutputMessage("Parse Error: in Shape Node.");
				danceTcl::OutputMessage("Make sure brackets are surrounded"
					" by spaces") ;
			
				return TCL_ERROR;
			}
		}
		else if (strcmp(token,"Transform") == 0) {
			if (TCL_ERROR == ParseTransform(interp,fp,level+1)) {
				danceTcl::OutputMessage("Parse Error: in children's Transform node.");
				return TCL_ERROR;
			}
		}
		else if (strcmp(token,"#") == 0)
			ParseComment(interp,fp);
		fscanf(fp,"%s",token);
	}
	return TCL_OK;

}

// ParseComment:
//
int IndexedFaceSet::ParseComment(Tcl_Interp *interp, FILE *fp)
{
	// Read comment until newline.
	while (fgetc(fp) != (int)'\n');
	return TCL_OK;
}


// parseCoordIndexField:
int IndexedFaceSet::parseCoordIndexField(Tcl_Interp *interp, FILE *fp)
{
	char token[MAX_LINE];

	danceTcl::OutputMessage("Parsing CoordIndex Field.\n");
    fscanf(fp,"%s",token);
	if (strcmp(token,"[") != 0) {
		danceTcl::OutputMessage("Parse error: expected [ for CoordIndex.\n");
		return -1;
	}

	fscanf(fp,"%s",token);

	int index = 0;
	int numVertices = 0;
	int vertIndex[MAX_VERT_FACE];
	int numFacesRead = 0;
	while (strcmp(token,"]") != 0  && !feof(fp)) {
		if (strcmp(token,"#") == 0) {
			ParseComment(interp,fp);
			strcpy(token,",");
		}
        else {
			// There is a chance that a token may contain a list of numbers
			// delimited by commas, but no spaces. We need to break up this
			// token into its individual pieces using strtok
			char *indextoken=strtok(token,", ");
		
			while (indextoken != 0) {
			     sscanf(indextoken,"%d",&index);
			     if (index == -1) {


				 if( numVertices < 3 ) continue ;
				 // get read of triangles with same vertices
				 if( (vertIndex[0] == vertIndex[1]) ||
				     (vertIndex[1] == vertIndex[2]) ||
				     (vertIndex[2] == vertIndex[0]) )
				 {
				     exit(-1) ;
				     continue ;

				 }

				 if (m_MirrorGeometry) {
					 // flip all vertices in vertIndex.
					 int tempVert[MAX_VERT_FACE];
					 for (int i = 0; i < numVertices; i++)
						 tempVert[i] = vertIndex[numVertices-1-i];
					 memcpy(vertIndex,tempVert,numVertices*sizeof(int));
				 }
					// This code guarantees all faces are triangles.
					if (numVertices == 3) {
						addFace(FaceOffset+numFacesRead);
						addCoordsToFace(FaceOffset+numFacesRead,numVertices,vertIndex);
						numFacesRead++;
					}
					else {
						int numTriangles = numVertices - 2;

						// First index is common to all triangles. We must ensure
						// the vertex order is counter-clockwise for front facing.
						int triVertices[3];
						triVertices[0] = vertIndex[0];
						for (int i = 1; i <= numTriangles; i++) {
							triVertices[1] = vertIndex[i];
							triVertices[2] = vertIndex[i+1];
							addFace(FaceOffset+numFacesRead);
							addCoordsToFace(FaceOffset+numFacesRead,3,triVertices);
							numFacesRead++;
						
						
						}
					}
					
				    numVertices = 0;
				 }
                 else if (numVertices < MAX_VERT_FACE) 
				      vertIndex[numVertices++] = VertexOffset+index;
                 else {
                		danceTcl::OutputMessage(
				          "Parse error: Face encountered which exceeds maximum vertices.\n");
                		return TCL_ERROR;
				 }
				 indextoken=strtok(NULL,", ");
			} // end while

			// There is a chance token may contain a ] character. If so,
			// ensure that we exit this loop properly and don't read more.
			if (strchr(token,']')) {
				strcpy(token,"]");
				break;
			}

		    fscanf(fp,"%s",token);

		}
	}

	if (strcmp(token,"]") != 0) {
		danceTcl::OutputMessage("Parse error: expected ] for CoordIndex.\n");
		return TCL_ERROR;
	}
	return numFacesRead;
}

// parseCoordinateNode:
int IndexedFaceSet::ParseCoordinateNode(Tcl_Interp *interp, FILE *fp, int level, double mat[16])
{
	char token[MAX_LINE];

	danceTcl::OutputMessage("Parsing Coordinate node.\n");
	fscanf(fp,"%s",token);

	// Encountered use of DEF for instantiation purposes. We will ignore it
	// for now, as we don't use it.
	if (strcmp(token,"DEF") == 0) {
		// Read in instance label to skip it.
		fscanf(fp,"%s",token);	
		fscanf(fp,"%s",token);
	}

	// Some files use a coordinate node flag to store the vertices.
	int coordinateNodeFlag = 0;
	if (strcmp(token,"Coordinate") == 0) {
		coordinateNodeFlag = 1;
	    fscanf(fp,"%s",token);
	    if (strcmp(token,"{") != 0) {
		   danceTcl::OutputMessage("Parse error: expected { for Coordinate node.\n");
		   return -1;
		}		
	}

	// Read until find first [ for vertices.
	while (strcmp(token,"[") != 0 && !feof(fp)) {
		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
		fscanf(fp,"%s",token);
    }

	if (strcmp(token,"[") != 0) {
		danceTcl::OutputMessage("Parse error: expected [ for coordinate vertex list.\n");
		return -1;
	}

    int numVerticesRead = 0;
	fscanf(fp,"%s",token);
	int count = 0;
	while (strcmp(token,"]") != 0 && !feof(fp)) {
		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
		else if (strcmp(token,",") != 0) {
			 // Read vertex values.
			double point[3];
			point[0] = atof(token);
			if (m_MirrorGeometry) point[0] = -1.0*point[0];

			fscanf(fp,"%s",token);
			point[1] = atof(token);
			fscanf(fp,"%s",token);
			point[2] = atof(token);
			if (level != -1)
				TransformPoint(mat,point,0);
			addVertex(point[0],point[1],point[2]);
			numVerticesRead++;
		}	
		
		// There is a chance token may contain a ] character. If so,
		// ensure that we exit this loop properly and don't read more.
		if (strchr(token,']')) {
			strcpy(token,"]");
			break;
		}

		fscanf(fp,"%s",token);
	} // end of point parsing

	if (strcmp(token,"]") != 0) {
		danceTcl::OutputMessage("Parse Error: Expected ] for coordinate list.\n");
		return -1;
	}

	if (coordinateNodeFlag) {
		fscanf(fp,"%s",token);
		if (strcmp(token,"}") != 0) {
			danceTcl::OutputMessage("Parse Error: Expected } for Coordinate node.\n");
			return -1;
		}
	}

	return numVerticesRead;
}

// parseIndexedFaceSetNode:
int IndexedFaceSet::ParseIndexedFaceSetNode(Tcl_Interp *interp, FILE *fp, int level)
{
	char token[MAX_LINE];
	fscanf(fp,"%s",token);
	
	danceTcl::OutputMessage("Parsing IndexedFaceSet node.\n");
	
	// Build up transformation matrix (if applicable)
	double mat[16];
	if (level != -1) 
		BuildTransform(level,mat);
	

	if (strcmp(token,"{") != 0) {
		danceTcl::OutputMessage("Parse error: expected { for IndexedFaceSet.\n");
		return -1;
	}

	fscanf(fp,"%s",token);

	// Some files store the information within a vertexProperty field.
	int vertexPropertyFlag = 0;
	if (strcmp(token,"vertexProperty") == 0) {
		vertexPropertyFlag = 1;
		fscanf(fp,"%s",token);
		if (strcmp(token,"VertexProperty") != 0) {
			danceTcl::OutputMessage("Parse Error: Expected VertexProperty keyword.\n");
			return -1;
		}
		fscanf(fp,"%s",token);
		if (strcmp(token,"{") != 0) {
			danceTcl::OutputMessage("Parse error: expected { for VertexProperty.\n");
			return -1;
		}
		fscanf(fp,"%s",token);
	}

	if (strcmp(token,"colorPerVertex") == 0) {
		fscanf(fp,"%s",token);
		int colorPerVertex = (strcmp(token,"TRUE") == 0);
		fscanf(fp,"%s",token);
	}

	if (strcmp(token,"normalPerVertex") == 0) {
		fscanf(fp,"%s",token);
		int normalPerVertex = (strcmp(token,"TRUE") == 0);
		fscanf(fp,"%s",token);
	}

  	int numVerticesRead = 0;
	int numFacesRead = 0;
	int numNormalsRead = 0;
	int numNormalFacesRead = 0;

	while (strcmp(token,"}") != 0 && !feof(fp)) {
		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
		else if (strcmp(token,"coord") == 0 || strcmp(token,"vertex") == 0) {
		    if (-1 == (numVerticesRead = ParseCoordinateNode(interp,fp,level,mat))) 
			return TCL_ERROR;
		}
		else if (strcmp(token,"coordIndex") == 0) {
			if (-1 == (numFacesRead = parseCoordIndexField(interp,fp)))
				return TCL_ERROR;
		}
		else if (strcmp(token,"normal") == 0) {
		    danceTcl::OutputMessage("parsing normals") ;
			if (-1 == (numNormalsRead = ParseNormalNode(interp,fp,level,mat)))
				return TCL_ERROR;
		}
		else if (strcmp(token,"normalIndex") == 0) {
			if (-1 == (numNormalFacesRead = parseNormalIndexField(interp,fp)))
				return TCL_ERROR;
		}
		else if (strcmp(token,"texCoordIndex") == 0) 
			skipVrmlNode(fp);		
		else if (strcmp(token,"texCoord") == 0) 
			skipVrmlNode(fp);
		
	    fscanf(fp,"%s",token);
	}

	// Look for delimiter } of VertexProperty node if used.
	if (vertexPropertyFlag) {
		if (strcmp(token,"}") != 0) {
			danceTcl::OutputMessage("Parse error: expected } for VertexProperty node.\n");
			return -1;
		}
		fscanf(fp,"%s",token);
	}

	if (strcmp(token,"}")!=0) {
		danceTcl::OutputMessage("Parse error: expected } for IndexedFaceSet node.\n");
		return TCL_ERROR;
	}

	if (numNormalFacesRead > 0 && numFacesRead > 0) {
		if (numNormalFacesRead != numFacesRead) {
			danceTcl::OutputMessage("VRML error: Number of faces do not match for coordinate index list and normal index list.\n");
			// return TCL_ERROR;
		}
	}

	// Now add normals to face.
	VertexOffset += numVerticesRead;
	FaceOffset += numFacesRead;
	NormalOffset += numNormalsRead ;
	
	danceTcl::OutputMessage("Finished parsing IndexedFaceSet node.\n");
	danceTcl::OutputMessage("%d vertices with %d faces.\n",numVerticesRead,numFacesRead);
	danceTcl::OutputMessage("%d normals with %d faces.\n",numNormalsRead,numNormalFacesRead);

	return TCL_OK;
}

// parseMaterialNode:
int IndexedFaceSet::parseMaterialNode(Tcl_Interp *interp, FILE *fp)
{
	char token[MAX_LINE];

	danceTcl::OutputMessage("Parsing Material node.\n");
	fscanf(fp,"%s",token);
	if (strcmp(token,"DEF") == 0) { // Parse definition label.
		fscanf(fp,"%s",token); // definition name.
		fscanf(fp,"%s",token); // read next token.
	}
	else if (strcmp(token,"USE") == 0) {
		fscanf(fp,"%s",token); // definition name.
		danceTcl::OutputMessage("Warning: ignoring USE instance of material.");
		return(TCL_OK);
	}
	if (strcmp(token,"Material") != 0) {
		danceTcl::OutputMessage("Parse error: expected Material keyword for material node.\n");
		return TCL_ERROR;
	}
	fscanf(fp,"%s",token);
	if (strcmp(token,"{") != 0) {
		danceTcl::OutputMessage("Parse error: expected { for Material\n"); 
		return TCL_ERROR;
	}

	fscanf(fp,"%s",token);

	Material wMaterial;
	// Give some defaults in case nothing provided. Use the OpenGL defaults.
	wMaterial.mDiffuseColor[0] = wMaterial.mDiffuseColor[1] = wMaterial.mDiffuseColor[2] = wMaterial.mDiffuseColor[3] = 1.0;
	wMaterial.mAmbientColor[0] = wMaterial.mAmbientColor[1] = wMaterial.mAmbientColor[2] = 0.0;
	wMaterial.mAmbientColor[3] = 1.0;
	wMaterial.mSpecularColor[0] = wMaterial.mSpecularColor[1] = wMaterial.mSpecularColor[2] = wMaterial.mSpecularColor[3] = 1.0;
	wMaterial.mEmissiveColor[0] = wMaterial.mEmissiveColor[1] = wMaterial.mEmissiveColor[2] = 0.0;
	wMaterial.mEmissiveColor[3] = 1.0;
	wMaterial.mShininess = 0.0;

	while (strcmp(token,"}") != 0 && !feof(fp)) {
		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
		if (strcmp(token,"diffuseColor") == 0) 
			fscanf(fp,"%f %f %f", &(wMaterial.mDiffuseColor[0]),
				&(wMaterial.mDiffuseColor[1]),
				&(wMaterial.mDiffuseColor[2]));
	
		if (strcmp(token,"ambientIntensity") == 0) {
			float ambientIntensity;
			fscanf(fp,"%f", &ambientIntensity);
			wMaterial.mAmbientColor[0] = ambientIntensity;
			wMaterial.mAmbientColor[1] = ambientIntensity;
			wMaterial.mAmbientColor[2] = ambientIntensity;
		}

		if (strcmp(token,"specularColor") == 0)
			fscanf(fp,"%f %f %f", &(wMaterial.mSpecularColor[0]),
				&(wMaterial.mSpecularColor[1]),
				&(wMaterial.mSpecularColor[2]));

		if (strcmp(token,"emissiveColor") == 0)
			fscanf(fp,"%f %f %f", &(wMaterial.mEmissiveColor[0]),
				&(wMaterial.mEmissiveColor[1]),
				&(wMaterial.mEmissiveColor[2]));
			
		if (strcmp(token,"shininess") == 0)
			fscanf(fp,"%f", &wMaterial.mShininess);

		if (strcmp(token,"transparency") == 0) {
			float transparency;
			fscanf(fp,"%f", &transparency);
			wMaterial.mAmbientColor[3] = 1.0f-transparency;
			wMaterial.mDiffuseColor[3] = 1.0f-transparency;
		}

		fscanf(fp,"%s",token);
	}

	if (strcmp(token,"}") != 0) {
		danceTcl::OutputMessage("Error parsing Material.\n");
		return TCL_ERROR;
	}

	addMaterial(wMaterial);

	// Create a default color based on material.
	if (m_NumMaterials == 1)
		memcpy(m_Color,wMaterial.mDiffuseColor,4*sizeof(float));
	return TCL_OK;
}

// parseNormalIndexField:
int IndexedFaceSet::parseNormalIndexField(Tcl_Interp *interp, FILE *fp)
{
	char token[MAX_LINE];
	danceTcl::OutputMessage("Parsing Normal index field.\n");

    fscanf(fp,"%s",token);
	if (strcmp(token,"[") != 0) {
		danceTcl::OutputMessage("Parse error: expected [ for normalIndex.\n");
		return -1;
	}

	fscanf(fp,"%s",token);

	int index = 0;
	int numVertices = 0;
	int vertIndex[MAX_VERT_FACE];
	int faceIndex = 0;
	int numFacesRead = 0;
	while (strcmp(token,"]") != 0  && !feof(fp)) {
		if (strcmp(token,"#") == 0) {
			ParseComment(interp,fp);
			strcpy(token,",");
		}
       	else {
			char *indextoken=strtok(token,", ");
			while (indextoken != 0) {
			    sscanf(indextoken,"%d",&index);
				if (index == -1) {
					
					// This code guarantees all faces are triangles.
					if (numVertices == 3) {
						addFace(FaceOffset+faceIndex);
						addNormalToFace(FaceOffset+faceIndex,numVertices,vertIndex);
						numFacesRead++;
						faceIndex++;
					}
					else {
						int numTriangles = numVertices - 2;

						// First index is common to all triangles. We must ensure
						// the vertex order is counter-clockwise for front facing.
						int triVertices[3];
						triVertices[0] = vertIndex[0];
						for (int i = 1; i <= numTriangles; i++) {
							triVertices[1] = vertIndex[i];
							triVertices[2] = vertIndex[i+1];
							addFace(FaceOffset+faceIndex);
							addNormalToFace(FaceOffset+faceIndex,3,triVertices);
							numFacesRead++;
							faceIndex++;
						}
					}
					numVertices = 0;
				}
            	else if (numVertices < MAX_VERT_FACE) 
					vertIndex[numVertices++] = NormalOffset+index;
            	else {
                	danceTcl::OutputMessage("Parse error: Face encountered which exceeds maximum vertices.\n");
               		return -1;
           		}
				indextoken = strtok(NULL,", ");
			}
			
			// There is a chance token may contain a ] character. If so,
			// ensure that we exit this loop properly and don't read more.
			if (strchr(token,']')) {
				strcpy(token,"]");
				break;
			}
			fscanf(fp,"%s",token);
		}
	}

	if (strcmp(token,"]") != 0) {
		danceTcl::OutputMessage("Parse error: expected ] for normalIndex.\n");
		return -1;
	}
	return numFacesRead;
}


// parseNormalNode:
int IndexedFaceSet::ParseNormalNode(Tcl_Interp *interp, FILE *fp, int level, double mat[16])
{
	char token[MAX_LINE];
	fscanf(fp,"%s",token);

	// Some files use a normal node flag to store the normals
	int normalNodeFlag = 0;
	if (strcmp(token,"Normal") == 0) {
		normalNodeFlag = 1;
	    fscanf(fp,"%s",token);
	    if (strcmp(token,"{") != 0) {
		   danceTcl::OutputMessage("Parse error: expected { for Normal node.\n");
		   return -1;
		}		
	}

	// Read until find first [ for normals.
	while (strcmp(token,"[") != 0 && !feof(fp)) {
		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
		fscanf(fp,"%s",token);
    }

	if (strcmp(token,"[") != 0) {
		danceTcl::OutputMessage("Parse error: expected [ for normal list.\n");
		return -1;
	}

    int numNormalsRead = 0;
	fscanf(fp,"%s",token);
	while (strcmp(token,"]") != 0 && !feof(fp)) {
		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
	    else if (strcmp(token,",") != 0) {
			 // Read normal values.
			double normal[3];
			normal[0] = atof(token);
			fscanf(fp,"%s",token);
			normal[1] = atof(token);
			fscanf(fp,"%s",token);
			normal[2] = atof(token);
			if (level != -1)
				TransformPoint(mat,normal,1);
			addNormal(normal[0],normal[1],normal[2]);
			numNormalsRead++;
		}	
		
		// There is a chance token may contain a ] character. If so,
		// ensure that we exit this loop properly and don't read more.
		if (strchr(token,']')) {
			strcpy(token,"]");
			break;
		}

		fscanf(fp,"%s",token);
	} // end of point parsing

	if (strcmp(token,"]") != 0) {
		danceTcl::OutputMessage("Parse Error: Expected ] for normal list.\n");
		return -1;
	}

	// Looks for delimiter } if a Normal node was encountered.
	if (normalNodeFlag) {
		fscanf(fp,"%s",token);
		if (strcmp(token,"}") != 0) {
			danceTcl::OutputMessage("Parse Error: Expected } for Normal node.\n");
			return -1;
		}
	}

	return numNormalsRead;
}

// parseNode:
int IndexedFaceSet::parseNode(Tcl_Interp *interp, FILE *fp)
{
	char token[256];
	char beginBracket[2];
	char endBracket[2];

	danceTcl::OutputMessage("Parsing node.\n");
	fscanf(fp,"%s",token);

	// Chooses to match brace or square brackets.
	if (strcmp(token,"{") == 0) {
		strcpy(beginBracket,"{");
		strcpy(endBracket,"}");
	}
	else if (strcmp(token,"[") == 0) {
		strcpy(beginBracket,"[");
		strcpy(endBracket,"]");
	}
	else
		return TCL_OK;

	// Ensures brackets match.
	int count = 1;
	while  (count != 0 && !feof(fp)) {
		fscanf(fp,"%s",token);
		if (strcmp(token,"#") == 0)
			ParseComment(interp,fp);
		else if (strcmp(token,endBracket) == 0)
			count--;
		else if (strcmp(token,beginBracket) == 0)
			count++;
        }

	if (count != 0) {
		danceTcl::OutputMessage("Parse error: expected } or ] for node.\n");
		return TCL_ERROR;
	}

	danceTcl::OutputMessage("Finished parsing node.\n");
	return TCL_OK;
}

// parseShapeNode:
int IndexedFaceSet::ParseShapeNode(Tcl_Interp *interp, FILE *fp, int level)
{
	char token[256];
	int result = 0;

	danceTcl::OutputMessage("Parsing Shape node.\n");
	fscanf(fp,"%s",token);
	if (strcmp(token,"{") != 0) {
		danceTcl::OutputMessage("Parse error: expected { for Shape.\n");
		return TCL_ERROR;
	}
	fscanf(fp,"%s",token);
	while (strcmp(token,"}") != 0) { // Loop until end of shape node.

		if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);
		else if (strcmp(token,"geometry") == 0) {
			danceTcl::OutputMessage("Found geometry field.\n");
			fscanf(fp,"%s",token);
			// Handle DEF if present.
			if (strcmp(token,"DEF") == 0) {
				fscanf(fp,"%s",token); // Reads in label.
				fscanf(fp,"%s",token); // Reads next token.
			}
			if (strcmp(token,"IndexedFaceSet") == 0) {
				if (TCL_ERROR == ParseIndexedFaceSetNode(interp,fp,level)) {
					danceTcl::OutputMessage("Parse error: in IndexedFaceSet Node.\n");
					return TCL_ERROR;
				}
			}

		}
		// Some VRML files have an IndexedFaceSet node without the geometry field
		// label. Example, files from Alias PowerAnimator.
		else if (strcmp(token,"IndexedFaceSet") == 0) {
			if (TCL_ERROR == ParseIndexedFaceSetNode(interp,fp,level)) {
				danceTcl::OutputMessage("Parse error: in IndexedFaceSet Node.\n");
				return TCL_ERROR;
			}
		}
		else if (strcmp(token,"appearance") == 0) {
			// Parse until Appearance keyword found, or }
			fscanf(fp,"%s",token);
			while (strcmp(token,"Appearance") != 0 && strcmp(token,"}") != 0)
				fscanf(fp,"%s",token);

			if (strcmp(token,"Appearance") == 0)
				if (TCL_ERROR == parseAppearanceNode(interp,fp)) {
					danceTcl::OutputMessage("Parse error: in Appearance Node.\n");
					return TCL_ERROR;
				}
		}
		else {
			danceTcl::OutputMessage("Found node: %s, doing nothing.\n",token);
			parseNode(interp,fp); // Just verifies node is properly delimited.
		}

		if( feof(fp) ) 
		{
		    danceTcl::OutputMessage("Vrml: Unexpected end of file!") ;
		    return TCL_ERROR ;
		}
		if( fscanf(fp,"%s",token) != 1 )
		{
		   danceTcl::OutputMessage("Vrml: Unexpected end of file!") ;
		    return TCL_ERROR ;
		}  
	}

	if (strcmp(token,"}") != 0) {
		danceTcl::OutputMessage("Parse error: expected } for node.");
		return TCL_ERROR;
	}
	danceTcl::OutputMessage("Finished parsing Shape node.");
	return TCL_OK;
}

int IndexedFaceSet::ParseTransform(Tcl_Interp *interp, FILE *fp, int level)
{
	danceTcl::OutputMessage("Parsing Transform node at level %d.",level);

	char token[256];
	fscanf(fp,"%s",token);
	if (strcmp(token,"{") != 0) {
		danceTcl::OutputMessage("Parse error: expected { for transform.");
		return TCL_ERROR;
	}

	fscanf(fp,"%s",token);
	// Initialize transform matrix to identity.
	for (int i = 0; i < 16; i++) {
		if (i == 0 || i == 5 || i == 10 || i == 15)
			m_TransformStack[level][i] = 1.0;
		else
			m_TransformStack[level][i] = 0.0;
	}
	while (strcmp(token,"}") != 0 && strcmp(token,"},") != 0) { // Loop until end of transform node.
		if (strcmp(token,"translation") == 0) {
			danceTcl::OutputMessage("Parsing translation field.");
			double x,y,z;
			fscanf(fp,"%lf %lf %lf",&x,&y,&z);
			BuildTranslate(m_TransformStack[level],x,y,z);
		}
		else if (strcmp(token,"rotation") == 0) {
			danceTcl::OutputMessage("Parsing rotation field.");
			double x,y,z,rad;
			fscanf(fp,"%lf %lf %lf %lf",&x,&y,&z,&rad);
			BuildRotate(m_TransformStack[level],x,y,z,rad);
		}
		else if (strcmp(token,"scale") == 0) {
			danceTcl::OutputMessage("Parsing scale field.");
			double sx,sy,sz;
			fscanf(fp,"%lf %lf %lf", &sx,&sy,&sz);
			BuildScale(m_TransformStack[level],sx,sy,sz);
		}
		else if (strcmp(token,"children") == 0) {
			if (TCL_ERROR == ParseChildren(interp,fp,level)) {
				danceTcl::OutputMessage("Parse Error: Children field in transform node.");
				return TCL_ERROR;
			}
		}
		else if (strcmp(token,"#") == 0) 
			ParseComment(interp,fp);

		fscanf(fp,"%s",token);
	}
	return TCL_OK;
}

void IndexedFaceSet::skipVrmlNode(FILE *fp)
{
	// Read until encounter { or [ bracket.
	char token[256];
	fscanf(fp,"%s",token);
	while(strcmp(token,"{") != 0 && strcmp(token,"[") != 0)
		fscanf(fp,"%s",token);

	char closetoken[256];
	if (strcmp(token,"{") == 0)
		strcpy(closetoken,"}");
	else if (strcmp(token,"[") == 0)
		strcpy(closetoken,"]");

	// FUTURE: Should add more sophisticated code to handle nested brackets.
	while(strcmp(token,closetoken) != 0)
		fscanf(fp,"%s",token);

}

void IndexedFaceSet::TransformPoint(double mat[16], double point[3], int normal)
{
	
	double newpoint[3];
	newpoint[0] = mat[0]*point[0] + mat[4]*point[1] + mat[8]*point[2];
	newpoint[1] = mat[1]*point[0] + mat[5]*point[1] + mat[9]*point[2];
	newpoint[2] = mat[2]*point[0] + mat[6]*point[1] + mat[10]*point[2];
	if (normal == 0) { // Add translation component.
		newpoint[0] += mat[3];
		newpoint[1] += mat[7];
		newpoint[2] += mat[11];
	}
	memcpy(point,newpoint,3*sizeof(double));
	
}

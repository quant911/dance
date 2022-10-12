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

// Saves a ply file: vertices, faces
int IndexedFaceSet::savePly(Tcl_Interp *interp, char *filename)
{
	int i,j;

	FILE *fptr = fopen(filename,"w");
	if (fptr == NULL) return  TCL_ERROR;

    // Write proper Ply header
	fprintf(fptr,"ply\n");
	fprintf(fptr,"format ascii 1.0\n");
	fprintf(fptr,"comment Created with DANCE's IndexedFaceSet plugin.\n");

	fprintf(fptr,"element vertex %d\n",m_NumVertices);
	fprintf(fptr,"property float x\n");
	fprintf(fptr,"property float y\n");
	fprintf(fptr,"property float z\n");

	fprintf(fptr,"element face %d\n",m_NumFaces);
	fprintf(fptr,"property list uchar int vertex_indices\n");
	fprintf(fptr,"end_header\n");
	// End of header

	// Output vertices.
	for (i = 0; i < m_NumVertices; i++) 
		fprintf(fptr,"%f %f %f\n",
			m_Vertices[i][0],m_Vertices[i][1],m_Vertices[i][2]);

	// Output faces.
	for (i = 0; i < m_NumFaces;i ++) {
		fprintf(fptr,"%d ", m_Faces[i].numVertices);
		for (j = 0; j < m_Faces[i].numVertices; j++) 
			fprintf(fptr,"%d ",m_Faces[i].vertexIndex[j]);
		fprintf(fptr,"\n");
	}

	fflush(fptr);
	fclose(fptr);
	return TCL_OK;
}


// parsePly: parses the given ply file and fills in the data structure.
//	    Allocates the memory necessary.
//	    returns 1 on success, 0 on failure
int IndexedFaceSet::parsePly(Tcl_Interp *interp, char *filename)
{

	FILE *fp = fopen(filename,"r");
	if (fp == NULL) return TCL_ERROR;

    	char token[MAX_LINE];	

	// Parse only geometry nodes until end-of-file
	FaceOffset = 0;
	NormalOffset = 0;
	VertexOffset = 0;

	int result = 0;
	// Parse header first.
	fscanf(fp,"%s",token);
	if (strcmp(token,"ply") != 0) {
		danceTcl::OutputMessage("parsePly: Expected ply keyword.\n");
		return 0;
	}
	fscanf(fp,"%s",token);
	if (strcmp(token,"format") != 0) {
		danceTcl::OutputMessage("parsePly: Expected format keyword.\n");
		return 0;
	}
	float versionID = 0.0;
	fscanf(fp,"%s %f",token,&versionID);
	if (strcmp(token,"ascii") != 0) {
		danceTcl::OutputMessage("parsePly: Only ascii format currently supported.\n");
		return 0;
	}
	danceTcl::OutputMessage("Encountered ply ascii format %f\n",versionID);

	// Load element headers
	int numElements = 0;
	enum elementTypes {
		eVertices,
		eNormals,
		eFaces,
		eEdges,
		eColors
	};
	int elementArray[5] = { 0,0,0,0,0};

	int number = 0;
	int elementType = -1;
	do {
		result = fscanf(fp,"%s",token);
		if (result > 0)	{
			if (strcmp(token,"comment") == 0) 
				parsePlyComment(interp,fp);
			else if (strcmp(token,"element") == 0) {
				fscanf(fp,"%s %d",token,&number);
				if (strcmp(token,"vertex") == 0) 
					elementType = eVertices;
				else if (strcmp(token,"face") == 0) 
					elementType = eFaces;	
				else if (strcmp(token,"edge") == 0) 
					elementType = eEdges;
			}
			else if (strcmp(token,"property") == 0) {
				char typeString[MAX_LINE], label[MAX_LINE];
				fscanf(fp,"%s %s", typeString, label);
				if (strcmp(label,"x") == 0 && elementType == (int)eVertices) 
					elementArray[eVertices]=number;
				if (strcmp(label,"y") == 0 && elementType == (int)eVertices) 
					elementArray[eVertices]=number;
				if (strcmp(label,"z") == 0 && elementType == (int)eVertices) 
					elementArray[eVertices]=number;
				if (strcmp(label,"nx") == 0 && elementType == (int)eVertices) 
					elementArray[eNormals]=number;
				if (strcmp(label,"ny") == 0 && elementType == (int)eVertices) 
					elementArray[eNormals]=number;
				if (strcmp(label,"nz") == 0 && elementType == (int)eVertices) 
					elementArray[eNormals]=number;

				// Currently, do not handle edge lists and face lists per vertex
				if (strcmp(label,"uchar") == 0) {
					unsigned char quantity;
					fscanf(fp,"%c %s %s",&quantity,typeString,label);
					if (elementType == eFaces)
						elementArray[eFaces] = number;
				}
			}
			else if (strcmp(token,"end_header") == 0)
				break;	
		}
	} while	(!feof(fp));

	// Read vertices
	for (int i = 0; i < elementArray[eVertices]; i++) {
		float x,y,z;
		fscanf(fp,"%f %f %f", &x,&y,&z); addVertex(x,y,z);
		if (elementArray[eNormals]) {
			float nx,ny,nz;
			fscanf(fp,"%f %f %f",&nx,&ny,&nz); addNormal(nx,ny,nz);
		}
	}

	// Read faces
	int m_AllTriangles = TRUE;
	for (int f = 0; f < elementArray[eFaces]; f++) {
		int numVerts;
		int vertArray[256];
		fscanf(fp,"%d",&numVerts);
		if (numVerts != 3) 
		    m_AllTriangles = FALSE;
		for (int v = 0; v < numVerts; v++) 
			fscanf(fp,"%d", &(vertArray[v]));
		addFace(FaceOffset+f);
		addCoordsToFace(FaceOffset+f,numVerts,vertArray);
		if (elementArray[eNormals])
			addNormalToFace(FaceOffset+f,numVerts,vertArray);
	}
    	fclose(fp);

	danceTcl::OutputResult("Read in %d vertices, %d normals, %d faces\n",m_NumVertices, m_NumNormals, m_NumFaces);

	// Build edge list.
	// if (elementArray[eEdges] == 0)
	//	BuildEdges();
	// Runs out of memory!
	danceTcl::OutputResult("Number of edges found: %d\n",m_NumEdges);

    return(TCL_OK);
}

// parsePlyComment:
int IndexedFaceSet::parsePlyComment(Tcl_Interp *interp, FILE *fp)
{
	// Read comment until newline.
	while (fgetc(fp) != (int)'\n');
	return TCL_OK;
}

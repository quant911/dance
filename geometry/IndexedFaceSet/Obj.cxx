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

// saveOBJ: saves the IndexedFaceSet as a wavefront object
//	Only saves vertices
//
int IndexedFaceSet::saveOBJ(char *filename)
{
	int i,j;

	FILE *fptr = fopen(filename,"w");
	if (fptr == NULL) return  TCL_ERROR;

	fprintf(fptr,"# Original file: %s\n",getFileName());
	for (i = 0; i < m_NumVertices; i++) 
	    fprintf(fptr,"v %lf %lf %lf\n", m_Vertices[i][0],
		    m_Vertices[i][1], m_Vertices[i][2]);

	// Output faces.
	fprintf(fptr,"# %d faces\n",m_NumFaces);
	for (i = 0; i < m_NumFaces;i ++) 
	{
	    fprintf(fptr, "f") ;
	    for (j = 0; j < m_Faces[i].numVertices; j++) 
		fprintf(fptr," %d", 1 + m_Faces[i].vertexIndex[j]);
	    fprintf(fptr,"\n");
	}
	return TCL_OK;
}


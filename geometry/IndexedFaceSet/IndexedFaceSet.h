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


#ifndef	_IndexedFaceSet_H_
#define	_IndexedFaceSet_H_ 1

#include "DGeometry.h"
#include "Material.h"
#include "WingedEdge.h"

#ifndef WIN32
#define BOOL int
#endif

static const int MAX_VERT_FACE = 16 ;
static const int MAX_TRANSFORM_LEVELS = 10;

class RAPID_model;




class IndexedFace {
    friend class IndexedFaceSet;

public:
    IndexedFace() ;
    ~IndexedFace() ;
    int	numVertices ;
    int	numNormals ;
    int	*vertexIndex;
    int	*texCoordIndex;
    int	*normalIndex;
    int materialIndex;

    double avgSideLength;
    double centroid[3];
    double faceNormal[3];
private:

    double w;		// used	by the computeMoments proc
} ;

class EdgeList {
public:
	int m_numEdges;
	int *m_Edges;
	void Cleanup(void) { if (m_Edges) delete [] m_Edges; };
	EdgeList() { m_numEdges = 0; m_Edges = NULL; };

};

// This class stores a list of triangles. Although the structures can potentially
// store all kinds of polygons, some of the code is optimized and will only work
// with triangles. Examples, are the RAPID collision detection code.
//
class DLLEXPORT IndexedFaceSet : public DGeometry {
public:
    int	m_NumVertices ;
    Vector *m_Vertices;		// List of vertices.

	int addCoordsToFace(int index, int numCoords, int *coordIndices);
	int m_MirrorGeometry ;
	void DisplayFaces(int buildList = 0);
	int BuildEdges(void);
	void displayNormals(void);
	void transform(double com[3], double refFrame[3][3]);
    IndexedFaceSet() ;
    ~IndexedFaceSet() ;

    void print(FILE *fptr);
    void printFile(char *filename);

    int GetRapidTriangle(int id, Vector v1, Vector v2, Vector v3 ) ;
    int PrepareCollision(void);

    void display(int style=0);

    BoundingBox *calcBoundingBox(BoundingBox *box = NULL);
    Vector *getVertices(void) {	return m_Vertices	;} ;
    void getEndEffector(Vector p) ;

    PlugIn *create(Tcl_Interp *interp, int argc, char **argv);
    int commandPlugIn(ClientData clientData, Tcl_Interp	*interp, int argc, char	**argv);

  void UpdateParamsAndDispList() ;
  void scaleGeom(double scaleX, double scaleY, double	scaleZ);
  void calcInerTensor(double inerTensor[3][3], double	mass) {return;};
  void computeContMassProperties(double density,double *mass, double moments[3]);
  void computeDiscMassProperties(double massPt, double *mass, double moments[3]);
  void Center(void) ;
  void SetOrigin(Vector orgn) ;
  void Rotate(char *axis, double degrees, int center) ;
  void Translate(double x, double y, double z) ;
  void Scale(double sx, double sy, double sz, int center) ;

  private:
	double m_ScaleFactor;
    int m_DisplayList;
    double m_Moments[3];
    double m_Mass;
    int ProcessEdge(int v1, int v2, int face);
    int m_NumEdges;

	// Transformation routines
	double m_TransformStack[MAX_TRANSFORM_LEVELS][16];
	void BuildRotate(double mat[16], double x, double y, double z, double rad);
	void BuildTranslate(double mat[16], double x, double y, double z);
	void BuildScale(double mat[16], double sx, double sy, double sz);
	void BuildTransform(int level, double mat[16]);
	void TransformPoint(double mat[16], double point[3], int normal);

    // Characteristics
    BOOL m_HasColors;
    BOOL m_AllTriangles;
    BOOL m_HasNormals;

    // Mass properties
    int m_MassPropertiesType;
    double m_Density;
    double m_MassPt;
    double m_comDiscrete[3];
    double m_comContinuous[3];
    double m_InertiaTensorDiscrete[3];
    double m_InertiaTensorContinuous[3];

    // Construction routines.
    int addMaterial(Material material);
    int addNormalToFace(int index, int numNormals, int *normIndices);
    int	addNormal(double x, double y, double z)	 ;
    int	addVertex(double x, double y, double z)	;
    int addFace(int index) ;

    void assignMonitorPoints(int argc, char *argv[]) ;
    int	createMonitorPoints(int percent) ;

    // Property routines.
    double computeVolume(void) ;
    void compVolumeIntegrals(void) ;
    void compFaceIntegrals(IndexedFace *f) ;
    void compProjectionIntegrals(IndexedFace *f) ;
    void compFaceProperties(void);
    void findAverageVertex(double point[3]);

    // BONE parser commands.
    int parseBONE(Tcl_Interp *interp, char *filename);

    // VRML parser commands.
    int ParseVRML(Tcl_Interp *interp, char *filename);
    int parseAppearanceNode(Tcl_Interp *interp, FILE *fp);
	int ParseChildren(Tcl_Interp *interp, FILE *fp, int level);
    int ParseComment(Tcl_Interp *interp, FILE *fp);
    int parseCoordIndexField(Tcl_Interp *interp, FILE *fp);
    int ParseCoordinateNode(Tcl_Interp *interp, FILE *fp, int level, double mat[16]);
    int	ParseIndexedFaceSetNode(Tcl_Interp *interp, FILE *fp,int level);
    int parseMaterialNode(Tcl_Interp *interp, FILE *fp);
    int parseNormalIndexField(Tcl_Interp *interp, FILE *fp);
    int ParseNormalNode(Tcl_Interp *interp, FILE *fp, int level, double mat[16]);
	int ParseTransform(Tcl_Interp *interp, FILE *fp, int level);
    int ParseShapeNode(Tcl_Interp *interp, FILE *fp, int level);
    int parseTextureNode(Tcl_Interp *interp, FILE *fp);
    int parseNode(Tcl_Interp *interp, FILE *fp);
    void skipVrmlNode(FILE *fp);

    int saveMaterial(Tcl_Interp *interp, FILE *fp);
    int saveVRML(Tcl_Interp *interp, char *filename);
    int saveOBJ(char *filename) ;
    // Ply parser routines
    int savePly(Tcl_Interp *interp, char *filename);
    int parsePly(Tcl_Interp *interp, char *filename);
    int parsePlyComment(Tcl_Interp *interp, FILE *fp);
    int parsePlyColors(Tcl_Interp *interp, FILE *fp, int mode);
    int parsePlyEdges(Tcl_Interp *interp, FILE *fp, int mode);
    int parsePlyFaces(Tcl_Interp *interp, FILE *fp, int mode);
    int parsePlyNormals(Tcl_Interp *interp, FILE *fp, int mode);
    int parsePlyVertices(Tcl_Interp *interp, FILE *fp, int mode);


    Material *m_Materials;

    // DGeometry information.
    WingedEdge *m_EdgeList; // List of edges

    EdgeList *m_VertexEdges;		// Edge list for a vertex.
    Vector *m_Normals ;
    Vector *m_TexCoords;
    IndexedFace	*m_Faces;

    int	m_NumFaces ;
    int	m_NumNormals ;
    int m_NumMaterials;
} ;

#endif






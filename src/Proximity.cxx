#include "Proximity.h"
#include "dance.h"
#include "danceTcl.h"
#include "DanceObject.h"
#include "DanceObjectList.h"
#include "DActuator.h"
#include "DGeometry.h"
#include "RAPID.h"
#include "obb.h"
#include <string.h>
#include <assert.h>

enum VolumeType {
	eOBB,
	eActuator
};

Volume::Volume()
{
	m_LowerBound = -1.0;
	m_UpperBound = -1.0;
	m_Next = NULL;
	m_Object = NULL;
}

Proximity::Proximity() 
{
	m_Volumes = NULL;
	m_SortedVolumes = NULL;
}

// AddItem:
//	Builds candidate of objects to test proximity with.
//
void Proximity::AddItem(DanceObject *obj)
{
	if( obj == NULL )
	{
		danceTcl::OutputMessage("WARNING: null object passed to proximity.") ;
		return ;
	}
	char *typeString = obj->getBaseType();
	int type;
	box *OBB = NULL;
	if (strcmp(typeString,"Link") == 0) {
	
		DGeometry *geom = obj->GetGeometry();
		if (geom == NULL) return;
		
		if (geom->m_RAPIDmodel == NULL)
 			if( geom->PrepareCollision() == TCL_ERROR )
	  		{
  				danceTcl::OutputMessage("ERROR: Cannot prepare for collisions.") ;
  				return ;
  			}
  		
  		if (geom->m_RAPIDmodel) {
  				type = eOBB;
  				OBB = geom->m_RAPIDmodel->GetRootOBB();
  		}
  		else
  			return;
	    
	}
	else if (strcmp(typeString,"actuator") == 0) {
	        type = eActuator;	
	}
	else 
		return;

	Volume *wvolume = new Volume;
	wvolume->m_Type = type;
	wvolume->m_Object = OBB;
	wvolume->m_DanceObject = obj;

	if (m_Volumes == NULL)
		m_Volumes = wvolume;
	else {
		wvolume->m_Next = m_Volumes;
		m_Volumes = wvolume;
	}
}

// FindClosest:
//	point  : Point in world coordinates.
//  closest: Closest point on an object in the list to the world coordinates, point.
//	normal: Normal of tangent plane at the closest point.
//	obj: Stores pointer to DanceObject
//  OBB: Stores pointer to oriented bounding box
//
//  returns:
//		 0, proximity class not set up.
//		 1, successful
//	
int Proximity::FindClosest(double point[], double closest[], double normal[], DanceObject **obj, box **OBB)
{
	*obj = NULL;
	*OBB = NULL;

	// If nothing set up, exit early.
	if (m_Volumes == NULL) {
		memcpy(closest,point,3*sizeof(double));
		return 0;
	}

	memcpy(m_TestPoint,point,3*sizeof(double));

	// Build a sorted list from m_Volumes.
	// Loop through all volumes of m_Volumes and calculate
	// lower and upper bounds.
	//
	Volume *wvolume = m_Volumes;
	Volume *ovolume = NULL;
	Volume *nextVol = NULL;

	while (wvolume) {
		if (wvolume->m_Object == NULL) { // Must be an Actuator
			DActuator *act = (DActuator *)wvolume->m_DanceObject;
			wvolume->m_LowerBound = wvolume->m_UpperBound = act->GetDistance(point,wvolume->m_LocalPoint);
		}
		else { // Must be a Link's OBB
			// Find point in local coords.
			if (wvolume->m_Object->leaf()) { // A triangle.
				double linkCoords[3]; wvolume->m_DanceObject->getLocalCoord(linkCoords,point);
				wvolume->m_LowerBound 
			  = wvolume->m_UpperBound = wvolume->m_Object->GetDistanceToTri(linkCoords,wvolume->m_LocalPoint);
			}
			else { // An OBB
				double linkCoords[3]; wvolume->m_DanceObject->getLocalCoord(linkCoords,point);
				wvolume->m_Object->GetLocalCoords(wvolume->m_LocalPoint,linkCoords);
				wvolume->m_LowerBound = wvolume->m_Object->GetLowerBoundMin(wvolume->m_LocalPoint);
				wvolume->m_UpperBound = wvolume->m_Object->GetUpperBoundMin(linkCoords);
			}
		}
	
		nextVol = wvolume->m_Next;
		if (wvolume->m_LowerBound >= 0 && wvolume->m_UpperBound >= 0)
			AddSortedItem(wvolume);
		else { // Remove this bad volume from the list.
			if (wvolume == m_Volumes) 
				m_Volumes = nextVol;
			else
				ovolume->m_Next = nextVol;
			delete wvolume;
			wvolume = NULL;
		
		}

		if (wvolume) // Test since it may have been deleted.
			ovolume = wvolume;
		wvolume = nextVol;
	
	}

	// Now that m_SortedVolumes has been created on the first pass,
	// we want to continue the pruning process until only one item
	// is left. We first have to remove all list items and break
	// them down further if possible.
	while (Prune() == 0);

	*obj = m_SortedVolumes->m_DanceObject;
	double frame[3][3];
	if (*obj)  {
		if (m_SortedVolumes->m_Type == eOBB) { // Must be a triangle.
			assert(m_SortedVolumes->m_Object->trp);
			*OBB = m_SortedVolumes->m_Object;
			tri *trp = m_SortedVolumes->m_Object->trp;

			// Take normal cross product of edges.
			double e0[3], e1[3];
			for (int i = 0; i < 3; i++) {
				e0[i] = trp->p2[i] - trp->p1[i];
				e1[i] = trp->p3[i] - trp->p1[i];
			}
			double lnormal[3];
			lnormal[0] = e0[1]*e1[2] - e0[2]*e1[1];
			lnormal[1] = e0[2]*e1[0] - e0[0]*e1[2];
			lnormal[2] = e0[0]*e1[1] - e0[1]*e1[0];
			double ldist = lnormal[0]*lnormal[0]+lnormal[1]*lnormal[1]+lnormal[2]*lnormal[2];
			ldist = sqrt(ldist);
			lnormal[0] /= ldist;
			lnormal[1] /= ldist;
			lnormal[2] /= ldist;
			// Multiply the localPoint by the transformation of the link it resides in.

			(*obj)->GetWorldVector(normal,lnormal);
		}
		else {// Get the normal position located at the local position coordinates.
			m_SortedVolumes->m_DanceObject->GetWorldFrame(frame,m_SortedVolumes->m_LocalPoint);
			memcpy(normal,&(frame[2]),3*sizeof(double));
		}

		// Transform closest point in local coordinates to world coordinates.
		memcpy(m_LocalPoint,m_SortedVolumes->m_LocalPoint,3*sizeof(double));
		m_SortedVolumes->m_DanceObject->getWorldCoord(closest,m_SortedVolumes->m_LocalPoint);
	
	}

	/* Not necessary, done in GetWorldFrame()
	// Normalize the normal
	double size = normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2];
	size = sqrt(size);
	normal[0] /= size; normal[1] /= size; normal[2] /= size;
	*/

	// Deallocate the closest value.
	delete m_SortedVolumes; 
	m_SortedVolumes = NULL;

	return(1);
}

// Implicit:
//
// For a given world point, returns normal at that point.
// Returns:
//	< 0 if inside,
//	  0 if on surface,
//	> 0 if outside,
double Proximity::Implicit(double world[3], double normal[3]) {
	
	box *obb;
	DanceObject *obj;
	double closest[3];
	FindClosest(world, closest, normal, &obj, &obb);

	double dotprod = 0.0;
	double diff[3];
	for (int i = 0; i < 3; i++) {
		diff[i] = world[i]-closest[i];
		dotprod += diff[i]*normal[i];
	}
	const double tol = 0.001;
	if (fabs(dotprod) > tol) 
		memcpy(normal,diff,3*sizeof(double));
	return(dotprod);
}

// AddSortedItem:
//		Adds volume to a sorted list in ascending distance
//		May discard items if invalid in list.
//
void Proximity::AddSortedItem(Volume *vol)
{
	
	if (m_SortedVolumes == NULL) {
		Volume *wvol = new Volume;
		*wvol = *vol;
		wvol->m_Next = NULL;
		m_SortedVolumes = wvol;
		return;
	}

	Volume *old = NULL;
	Volume *wvolume = m_SortedVolumes;

	int quit = 0;
	while (wvolume) {

		// If this volume is entirely farther than the
		// current volume, do not add it in the list as
		// it will never be the closest.
		if (vol->m_LowerBound >= wvolume->m_UpperBound) {
			quit = 1;
			break;
		}

		// If this volume is entirely closer than the current
		// volume, throw away the rest of the list.
		if (vol->m_UpperBound < wvolume->m_LowerBound) {
			Volume *wvol = new Volume;
			*wvol = *vol;
			wvol->m_Next = NULL;
			if (old == NULL) 
				m_SortedVolumes = wvol;
			else {
				old->m_Next =wvol;
			}
			Deallocate(wvolume);
			quit = 1;
			break;
		}

		// If lower bound is closer than current, then put
		// this volume in front of it, only if previous two
		// conditions do not hold.
		if (vol->m_LowerBound < wvolume->m_LowerBound) {
			Volume *wvol = new Volume;
			*wvol = *vol;
			wvol->m_Next = wvolume;
			if (old == NULL) 
				m_SortedVolumes = wvol;
			else
				old->m_Next = wvol;
			quit = 1;
			break;
		}

		old = wvolume;
		wvolume = wvolume->m_Next;
	}

	// If we came to the end of the list, and none of the
	// exit conditions occurred, we add this item to the end
	// of the list.
	if (quit == 0) {
		Volume *wvol = new Volume;
		*wvol = *vol;
		wvol->m_Next = NULL;
		old->m_Next = wvol;
	}
}

// Deallocates everything pass this list.
void Proximity::Deallocate(Volume *wvol)
{
	Volume *vol;
	while (wvol) {
		vol = wvol;
		wvol = wvol->m_Next;
		delete vol;
	}
}

// GetClosestN:
//	Finds the N closest DanceObjects's wrt distance to bounding box.
//	Distance is based on lower bound estimates only.
//	Only valid volumes are stored (those with a valid distance method).
//	Looks at the m_Volumes and creates a ascending distance list and
//	stores it in list.
//
//	Returns the actual number of values in the list, and the linked list of volumes in
//	list.
//	Preconditions: Assumes you have initialized a set of candidate volumes to test.
//
int Proximity::GetClosestN(double point[3], int n, Volume **list, DanceObject *exclude)
{
	// Loop through all objects in m_Volumes.
	Volume *wvolume = m_Volumes;

	*list = NULL;

 	double lowerBound = -1.0;	
	while (wvolume) {
		if (exclude != wvolume->m_DanceObject) { // Make sure not to include
												 // excluded object.
		if (wvolume->m_Object == NULL) { // Must be an Actuator
			DActuator *act = (DActuator *)wvolume->m_DanceObject;
			lowerBound = act->GetDistance(point,wvolume->m_LocalPoint);
		}
		else { // Must be a Link's OBB
			// Find point in local coords.
			if (wvolume->m_Object->leaf()) { // A triangle.
				double linkCoords[3]; wvolume->m_DanceObject->getLocalCoord(linkCoords,point);
				lowerBound = wvolume->m_Object->GetDistanceToTri(linkCoords,wvolume->m_LocalPoint);
			}
			else { // An OBB
				double linkCoords[3]; wvolume->m_DanceObject->getLocalCoord(linkCoords,point);
				wvolume->m_Object->GetLocalCoords(wvolume->m_LocalPoint,linkCoords);
				lowerBound = wvolume->m_Object->GetLowerBoundMin(wvolume->m_LocalPoint);
			}
		}

		// Check all entries.
		fprintf(stderr,"Lower bound for %s is: %f\n",
			wvolume->m_DanceObject->getName(),lowerBound);
		if (lowerBound >= 0.0) { // Only do this for valid volumes.
		if (*list == NULL) {
			*list = new Volume;
			*(*list) = *wvolume;
			(*list)->m_LowerBound = lowerBound;
			(*list)->m_Next = NULL;
		}
		else {
			Volume *wvol = *list;
			Volume *prevVol = NULL;
			while (wvol) {
				if (lowerBound < wvol->m_LowerBound) {
					Volume *newVol = new Volume;
					*newVol = *wvolume;
					newVol->m_LowerBound = lowerBound;
					newVol->m_Next = wvol;
					if (wvol == *list) {
						*list = newVol;
						prevVol = *list; // To properly handle append code
								 // outside of while loop. m_Next
								 // field will be non-null
					}
					else	
						prevVol->m_Next = newVol;
					break;
				}
				prevVol = wvol;
				wvol = wvol->m_Next;
			}

			if (prevVol->m_Next == NULL) { // Append to end.
				Volume *newVol = new Volume;
				*newVol = *wvolume;
				newVol->m_LowerBound = lowerBound;
				newVol->m_Next = NULL;
				prevVol->m_Next = newVol;
			}

		}
		}
	
	} // End exclude
		wvolume = wvolume->m_Next;
	}

	int count = 0;
	// Delete all volumes after the first n
	Volume *wvol = *list;
	while (wvol) {
		count++;
		if (count == n) { // Delete everything afterwards.
			Deallocate(wvol->m_Next);
			wvol->m_Next = NULL;
			break;
		}
		wvol = wvol->m_Next;
	}
	return count;

}

// Continue pruning until only one volume left.
int Proximity::Prune()
{
	// Start new sorted list.
	Volume *wvol = m_SortedVolumes;
	m_SortedVolumes = NULL;
	Volume *ovol = NULL;
	while(wvol) {
		switch(wvol->m_Type) {
		case eOBB:
			if (wvol->m_Object->leaf())   
				AddSortedItem(wvol);
			else {
				// Split up box into its two children and add them
				// to the list.
				Volume *leftvol = buildVolumeFromOBB(wvol->m_Object->N, wvol->m_LocalPoint,wvol->m_DanceObject);
				if (leftvol) { AddSortedItem(leftvol); delete leftvol; }

				Volume *rightvol = buildVolumeFromOBB(wvol->m_Object->P, wvol->m_LocalPoint, wvol->m_DanceObject);
				if (rightvol) { AddSortedItem(rightvol); delete rightvol; }
			}
			break;
		case eActuator:
			// Just add item back into sorted list.
			AddSortedItem(wvol);
			break;
		}
		ovol = wvol;
		wvol = wvol->m_Next;
		delete ovol;
	}

	if (m_SortedVolumes->m_Next == NULL) {
		if (m_SortedVolumes->m_Type == eActuator) // Actuator
			return 1;
		else 
			return (m_SortedVolumes->m_Object->leaf()); // Leaf node of an OBB
			
	}
	return 0;
}

Volume * Proximity::buildVolumeFromOBB(box *obb, double *local, DanceObject *danceObj)
{
	if (obb == NULL) 
		return NULL;

	Volume *wvol = new Volume;
	wvol->m_Object = obb;
	wvol->m_DanceObject = danceObj;
	wvol->m_Type = eOBB;
	double linkCoord[3]; danceObj->getLocalCoord(linkCoord,m_TestPoint);
	if (obb->leaf()) {
		wvol->m_LowerBound = wvol->m_UpperBound =
			obb->GetDistanceToTri(linkCoord,wvol->m_LocalPoint);
	}
	else { // Since this obb is a child of its parent, we find the
		   // distance of the obb from the point in its outer frame.
		obb->GetLocalCoords(wvol->m_LocalPoint,local);
		wvol->m_LowerBound = obb->GetLowerBoundMin(wvol->m_LocalPoint);
		wvol->m_UpperBound = obb->GetUpperBoundMin(linkCoord);

		// Subtract a tolerance to handle cases where numbers are very close 
		const double tol = 0.00001;
		assert(wvol->m_LowerBound - tol <= wvol->m_UpperBound); 
	}
	return(wvol);
}

void Proximity::Clear()
{
	Deallocate(m_SortedVolumes);
	m_SortedVolumes = NULL;
}

void Proximity::Reset(Volume *wvol)
{
	Clear();

	// Do not delete old m_Volumes as we are only referring to it.
	// if (m_Volumes) Deallocate(m_Volumes);

	m_Volumes = wvol;
}

// type is 0 for links only, 1 for BsplineActuators only, -1 for all
Volume * Proximity::InitializeAll(DanceObject *skipObj, int type)
{
	Deallocate(m_Volumes);
	m_Volumes = NULL;

	// Add all bones.
	int i;
	DanceObject *obj;
	if (type != 1)
	for (i = 0; i < dance::AllSystems->size(); i++) {
			DSystem *sys = (DSystem *)dance::AllSystems->get(i);
			// Add all links of an object.
		 	for (int l = 0; l < sys->GetNumGroups() ; l++) {
			    DanceObject *g = sys->GetGroup(l) ;
				if (g != skipObj)
					AddItem(g);
			}
	}

	// Add all actuators.
	// Only want to add the BsplineActuators.
	if (type != 0)
	for (i = 0; i < dance::AllActuators->size(); i++) {
			obj = dance::AllActuators->get(i);
			if (strcmp(obj->getType(),"BsplineActuator") == 0) {
				  if (obj != skipObj)
	 				AddItem(obj);
			}
	}
			
		
	return(m_Volumes);
}

// GetClosest:
//		Returns closest point to given point of all objects in proximity class.
//
//		Returns: 1 on success, 0 on failure. 
int Proximity::GetClosest(double point[], double closest[], DanceObject **obj)
{
	// Loop through all objects in m_Volumes.
	Volume *wvolume = m_Volumes;

	*obj = NULL;
 	double lowerBound = -1.0;	
	box *obb;
	double normal[3];
	if (FindClosest(point,closest,normal,obj,&obb)) {
		return 1;
	}
	return(0);
}

// GetLocalPoint:
//		Returns the local point from the last valid query.
//
void Proximity::GetLocalPoint(double localpoint[]) {
	memcpy(localpoint,m_LocalPoint,3*sizeof(double));
}

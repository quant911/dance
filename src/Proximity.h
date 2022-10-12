#ifndef _PROXIMITY_H_
#define _PROXIMITY_H_ 1
#include "defs.h"

class DanceObject;
class box;
class Volume {
	public:
		int m_Type;
		box *m_Object;
		DanceObject *m_DanceObject;
		double m_LowerBound;
		double m_UpperBound;
		double m_LocalPoint[3];
		Volume *m_Next;

		Volume();
};


class DLLENTRY Proximity {
	private:
		Volume * buildVolumeFromOBB(box *obb, double *local, DanceObject *danceObj);
		int Prune(void);
		void AddSortedItem(Volume *vol);
		Volume * m_SortedVolumes;
		double m_LocalPoint[3];
	
	public:
		int GetClosest(double point[3], double closest[3], DanceObject **obj);
		void GetLocalPoint(double localpoint[3]);
		Volume * InitializeAll(DanceObject *skipObj = NULL, int type = -1);
		Volume *m_Volumes;
		double m_TestPoint[3];
		void Clear();
		void Deallocate(Volume *wvol);
		int FindClosest(double point[3], double closest[3], double normal[3], DanceObject **obj, box **OBB);
		int GetClosestN(double point[3], int n, Volume **list, DanceObject *exclude = NULL);
		double Implicit(double world[3], double normal[3]);
		void Reset(Volume *wvol);

		Proximity();
		void AddItem(DanceObject *obj);
};
#endif

/************************************************************************\

  Copyright 1997 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software
  and its documentation for educational, research and non-profit
  purposes, without fee, and without a written agreement is
  hereby granted, provided that the above copyright notice and
  the following three paragraphs appear in all copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL
  HILL BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL,
  INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
  ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
  EVEN IF THE UNIVERSITY OF NORTH CAROLINA HAVE BEEN ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGES.


  Permission to use, copy, modify and distribute this software
  and its documentation for educational, research and non-profit
  purposes, without fee, and without a written agreement is
  hereby granted, provided that the above copyright notice and
  the following three paragraphs appear in all copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
  BASIS, AND THE UNIVERSITY OF NORTH CAROLINA HAS NO OBLIGATION
  TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.


   --------------------------------- 
  |Please send all BUG REPORTS to:  |
  |                                 |
  |   geom@cs.unc.edu               |
  |                                 |
   ---------------------------------
  
     
  The authors may be contacted via:

  US Mail:  A. Pattekar/J. Cohen/T. Hudson/S. Gottschalk/M. Lin/D. Manocha
            Department of Computer Science
            Sitterson Hall, CB #3175
            University of N. Carolina
            Chapel Hill, NC 27599-3175
	    
  Phone:    (919)962-1749
	    
  EMail:    geom@cs.unc.edu

\************************************************************************/

/************************************************************************\
Filename: VCollide.C
--
Description: This file implements the member functions of the class VCollide.
             The class VCollide is simply a user interface and and is
             designed for data hiding. Hence, these member functions
             simply return make calls to the corresponding member
             functions of the class VCInternal.
\************************************************************************/


#include "VCollide.h"
#include "VCol.h"
#include "VInternal.h"

VCollide::VCollide()
{
  vcint = new VCInternal;
}

VCollide::~VCollide()
{
  delete vcint;
}

int VCollide::NewObject(int *id, RAPID_model *RAPIDobject)    //create a new object in the database.
{
  return vcint->NewObject(id, RAPIDobject);
}

int VCollide::AddTri(double v1[], double v2[], double v3[])  //insert
                                                             //the geometry
{
  return vcint->AddTri(v1, v2, v3);
}


int VCollide::EndObject(void) //tell VCollide that inserting the 
                              //geometry is complete.
{
  return vcint->EndObject();
}

int VCollide::UpdateTrans(int id, double t[][4])
  //update the transformation matrix of the object.
{
  return vcint->UpdateTrans(id, t);
}


int VCollide::ActivateObject(int id)          
{
  return vcint->ActivateObject(id);
}

int VCollide::DeactivateObject(int id)        
{
  return vcint->DeactivateObject(id);
}


int VCollide::ActivatePair(int id1, int id2)  //activate the pair.
{
  return vcint->ActivatePair(id1, id2);
}

int VCollide::DeactivatePair(int id1, int id2)//deactivate the pair.
{
  return vcint->DeactivatePair(id1, id2);
}


int VCollide::DeleteObject(int id)  //delete the object from the database.
{
  return vcint->DeleteObject(id);
}


int VCollide::Collide(void)         //perform collision detection.
{
  return vcint->Collide();
}

RAPID_model *VCollide::GetRAPIDModel(int id)
{
  return vcint->GetRAPIDModel(id);
}

int VCollide::Report(int size, VCReportType *vcrep)
{                               //report the results of collision detection.
  return vcint->Report(size, vcrep);
}

void VCollide::Display(int id)
{
  vcint->Display(id);
}

//Plain C wrappers for the C++ routines:

void *vcOpen(void)
{
  return (void *)(new VCollide);
}


void vcClose(void *vc_handle)
{
  delete ( (VCollide *) vc_handle );
}


int vcNewObject(void *vc_handle, int *id)
{
  return ( (VCollide *)vc_handle)->NewObject(id);
}

int vcAddTri(void *vc_handle, double v1[], double v2[], double v3[])
{
  return ( (VCollide *)vc_handle)->AddTri(v1, v2, v3);
}

int vcEndObject(void *vc_handle)
{
  return ( (VCollide *)vc_handle)->EndObject();
}

int vcUpdateTrans(void *vc_handle, int id, double t[][4])
{
  return ( (VCollide *)vc_handle)->UpdateTrans(id, t);
}

int vcActivateObject(void *vc_handle, int id)
{
  return ( (VCollide *)vc_handle)->ActivateObject(id);
}

int vcDeactivateObject(void *vc_handle, int id)
{
  return ( (VCollide *)vc_handle)->DeactivateObject(id);
}


int vcActivatePair(void *vc_handle, int id1, int id2)
{
  return ( (VCollide *)vc_handle)->ActivatePair(id1, id2);
}

int vcDeactivatePair(void *vc_handle, int id1, int id2)
{
  return ( (VCollide *)vc_handle)->DeactivatePair(id1, id2);
}


int vcDeleteObject(void *vc_handle, int id)
{
  return ( (VCollide *)vc_handle)->DeleteObject(id);
}

int vcCollide(void *vc_handle)
{
  return ( (VCollide *)vc_handle)->Collide();
}

int vcReport(void *vc_handle, int size, VCReportType *vcrep)
{
  return ( (VCollide *)vc_handle)->Report(size, vcrep);
}


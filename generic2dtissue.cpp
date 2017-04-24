/*
 *  generic2dtissue.cpp
 *
 *  Created by Alfredo Hernández on Fri Jul 26 2002.
 *  Copyright (c) 2001 INSERM. All rights reserved.
 *
 */


#include "generic2dtissue.h"

Generic2DTissue::Generic2DTissue() : Model(DESS,0,0,0,0,TISSUESIZE*TISSUESIZE)
{
    // creation of the cells composing the tissu model
  for (int i=0;i<getNumComponents();i++) {      
    components->at(i) = new BeelerReuterModel();
    numOutputs += (components->at(i))->getNumOutputs();
  }

  int count = 0;
  for (int i=0;i<TISSUESIZE;i++) {
    for (int j=0;j<TISSUESIZE;j++) {
      tissue[i][j] = components->at(count);
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
  }

//coupling parameters
//cardiac cell (cf yellow book p 254)
/*  d=20.0;
  Rc=150.0;
  Rm=7.0;
  Cm=1.2; */
  Tm=8.4;
//Lm=0.15;
  Lm=4.0; 
  coupParam=Lm*Lm/Tm;


  filter[0][0]=0; filter[0][1]=1; filter[0][2]=0;
  filter[1][0]=1; filter[1][1]=-4;filter[1][2]=1;
  filter[2][0]=0; filter[2][1]=1; filter[2][2]=0;

}

Generic2DTissue::~Generic2DTissue()
{
}


int Generic2DTissue::ModelStart()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelStart();

  return 0;
}


int Generic2DTissue::ModelInitSim()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelInitSim();

  return 1;
}


int Generic2DTissue::NextSampleHit()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->NextSampleHit();

  return 0;
}


int Generic2DTissue::ModelOutputs()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelOutputs();

  return 0;
}


int Generic2DTissue::ModelUpdate(double time)
{
  double tempGrad;

  //updating of all cells
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelUpdate(time);
 
  /*
  //initialisation of the first cell
  if ((time>=50.0) && (time<=60.0)) {
	 ((BeelerReuterModel*)tissue[0][0])->setIN_Z(5.0);
	 
  } else {
    ((BeelerReuterModel*)tissue[0][0])->setIN_Z(0.0);
  }
  
  *gradTissue[0][0] = 0.0; 
  
 */
  
/*Ahmad*/
  //initialisation of the first column
  if ((time>=50.0) && (time<=60.0)) {
		  for (int j=0;j<TISSUESIZE-1;j++) {
		  ((BeelerReuterModel*)tissue[j][0])->setIN_Z(5.0);
	  }
	}

  else {
	   for (int j=0;j<TISSUESIZE-1;j++) {
  ((BeelerReuterModel*)tissue[j][0])->setIN_Z(0.0);
  }
  }
  

    for (int j=0;j<TISSUESIZE-1;j++) {
		  *gradTissue[j][0] = 0.0; 	
	}

/*Ahmad*/


  //first row but first cell (pacemaker cell)
  //middle cells
  for (int j=1;j<TISSUESIZE-1;j++) {
    tempGrad = filter[1][0]*((BeelerReuterModel*)tissue[0][j-1])->getST_X() +
               filter[1][2]*((BeelerReuterModel*)tissue[0][j+1])->getST_X() +
               filter[2][0]*((BeelerReuterModel*)tissue[1][j-1])->getST_X() +
               filter[2][1]*((BeelerReuterModel*)tissue[1][j])->getST_X() +
               filter[2][2]*((BeelerReuterModel*)tissue[1][j+1])->getST_X() -
               (filter[1][0]+filter[1][2]+filter[2][0]+filter[2][1]+filter[2][2])*((BeelerReuterModel*)tissue[0][j])->getST_X();
    ((BeelerReuterModel*)tissue[0][j])->setIN_Z(tempGrad*coupParam);
    *gradTissue[0][j] = tempGrad;
  }

  
  //last cell in first row
  tempGrad = filter[1][0]*((BeelerReuterModel*)tissue[0][TISSUESIZE-2])->getST_X() +
             filter[2][0]*((BeelerReuterModel*)tissue[1][TISSUESIZE-2])->getST_X() +
             filter[2][1]*((BeelerReuterModel*)tissue[1][TISSUESIZE-1])->getST_X() -
             (filter[1][0]+filter[2][0]+filter[2][1])*((BeelerReuterModel*)tissue[0][TISSUESIZE-1])->getST_X();
  ((BeelerReuterModel*)tissue[0][TISSUESIZE-1])->setIN_Z(tempGrad*coupParam);
  *gradTissue[0][TISSUESIZE-1] = tempGrad;

  
  //last row
  //first cell in last row
  tempGrad = filter[0][1]*((BeelerReuterModel*)tissue[TISSUESIZE-2][0])->getST_X() +
             filter[0][2]*((BeelerReuterModel*)tissue[TISSUESIZE-2][1])->getST_X() +
             filter[1][2]*((BeelerReuterModel*)tissue[TISSUESIZE-1][1])->getST_X() -
             (filter[0][1]+filter[0][2]+filter[1][2])*((BeelerReuterModel*)tissue[TISSUESIZE-1][0])->getST_X();
  ((BeelerReuterModel*)tissue[TISSUESIZE-1][0])->setIN_Z(tempGrad*coupParam);
  *gradTissue[TISSUESIZE-1][0] = tempGrad;

   //middle cells
  for (int j=1;j<TISSUESIZE-1;j++) {
    tempGrad = filter[0][0]*((BeelerReuterModel*)tissue[TISSUESIZE-2][j-1])->getST_X() +
               filter[0][1]*((BeelerReuterModel*)tissue[TISSUESIZE-2][j])->getST_X() +
               filter[0][2]*((BeelerReuterModel*)tissue[TISSUESIZE-2][j+1])->getST_X() +
               filter[1][0]*((BeelerReuterModel*)tissue[TISSUESIZE-1][j-1])->getST_X() +
               filter[1][2]*((BeelerReuterModel*)tissue[TISSUESIZE-1][j+1])->getST_X() -
               (filter[0][0]+filter[0][1]+filter[0][2]+filter[1][0]+filter[1][2])*((BeelerReuterModel*)tissue[TISSUESIZE-1][j])->getST_X();
    ((BeelerReuterModel*)tissue[TISSUESIZE-1][j])->setIN_Z(tempGrad*coupParam);
    *gradTissue[TISSUESIZE-1][j] = tempGrad;
  }
    
  //last cell in last row
  tempGrad = filter[0][0]*((BeelerReuterModel*)tissue[TISSUESIZE-2][TISSUESIZE-2])->getST_X() +
             filter[0][1]*((BeelerReuterModel*)tissue[TISSUESIZE-2][TISSUESIZE-1])->getST_X() +
             filter[1][0]*((BeelerReuterModel*)tissue[TISSUESIZE-1][TISSUESIZE-2])->getST_X() -
             (filter[0][0]+filter[0][1]+filter[1][0])*((BeelerReuterModel*)tissue[TISSUESIZE-1][TISSUESIZE-1])->getST_X();
  ((BeelerReuterModel*)tissue[TISSUESIZE-1][TISSUESIZE-1])->setIN_Z(tempGrad*coupParam);
  *gradTissue[TISSUESIZE-1][TISSUESIZE-1] = tempGrad;

  
 /*Ahmad
 
  //first column
  //middle cells
  for (int i=1;i<TISSUESIZE-1;i++) {
    tempGrad = filter[0][1]*((BeelerReuterModel*)tissue[i-1][0])->getST_X() +
               filter[0][2]*((BeelerReuterModel*)tissue[i-1][1])->getST_X() +
               filter[1][2]*((BeelerReuterModel*)tissue[i][1])->getST_X() +
               filter[2][1]*((BeelerReuterModel*)tissue[i+1][0])->getST_X() +
               filter[2][2]*((BeelerReuterModel*)tissue[i+1][1])->getST_X() -
               (filter[0][1]+filter[0][2]+filter[1][2]+filter[2][1]+filter[2][2])*((BeelerReuterModel*)tissue[i][0])->getST_X();
    ((BeelerReuterModel*)tissue[i][0])->setIN_Z(tempGrad*coupParam);
    *gradTissue[i][0] = tempGrad;
  }
 
 */

    
  //last column
  //middle celles
  for (int i=1;i<TISSUESIZE-1;i++) {
    tempGrad = filter[0][0]*((BeelerReuterModel*)tissue[i-1][TISSUESIZE-2])->getST_X() +
               filter[0][1]*((BeelerReuterModel*)tissue[i-1][TISSUESIZE-1])->getST_X() +
               filter[1][0]*((BeelerReuterModel*)tissue[i][TISSUESIZE-2])->getST_X() +
               filter[2][0]*((BeelerReuterModel*)tissue[i+1][TISSUESIZE-2])->getST_X() +
               filter[2][1]*((BeelerReuterModel*)tissue[i+1][TISSUESIZE-1])->getST_X() -
               (filter[0][0]+filter[0][1]+filter[1][0]+filter[2][0]+filter[2][1])*((BeelerReuterModel*)tissue[i][TISSUESIZE-1])->getST_X();
    ((BeelerReuterModel*)tissue[i][TISSUESIZE-1])->setIN_Z(tempGrad*coupParam);
    *gradTissue[i][TISSUESIZE-1] = tempGrad;
  }

 
  //coupling between middle cells
  for (int i=1;i<TISSUESIZE-1;i++) {
    for (int j=1;j<TISSUESIZE-1;j++) {
    //  if ((i!=1)||(j!=1)) {
        tempGrad = filter[0][0]*((BeelerReuterModel*)tissue[i-1][j-1])->getST_X() +
                   filter[0][1]*((BeelerReuterModel*)tissue[i-1][j])->getST_X() +
                   filter[0][2]*((BeelerReuterModel*)tissue[i-1][j+1])->getST_X() +
                   filter[1][0]*((BeelerReuterModel*)tissue[i][j-1])->getST_X() +
                   filter[1][1]*((BeelerReuterModel*)tissue[i][j])->getST_X() +
                   filter[1][2]*((BeelerReuterModel*)tissue[i][j+1])->getST_X() +
                   filter[2][0]*((BeelerReuterModel*)tissue[i+1][j-1])->getST_X() +
                   filter[2][1]*((BeelerReuterModel*)tissue[i+1][j])->getST_X() +
                   filter[2][2]*((BeelerReuterModel*)tissue[i+1][j+1])->getST_X();
        ((BeelerReuterModel*)tissue[i][j])->setIN_Z(tempGrad*coupParam);
        *gradTissue[i][j] = tempGrad;
    //  }
    }
  }


  return 0;
}


int Generic2DTissue::ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas)
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelDerivatives(time,variables,derivadas);

  return 0;
}


int Generic2DTissue::ModelTerminate()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelTerminate();

  return 0;
}

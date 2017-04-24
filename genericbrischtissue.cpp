/***************************************************************************
                          genericbrischtissue.cpp  -  description
                             -------------------
    begin                : mer fév 4 2004
    copyright            : (C) 2004 by Antoine Defontaine
    email                : antoine@univ-rennes1.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "genericbrischtissue.h"

GenericBRIschTissue::GenericBRIschTissue() : Model(DESS,0,0,0,0,TISSUESIZE*TISSUESIZE)
{
// creation of the cells composing the parent model
/*  for (int i=0;i<getNumComponents();i++) {
    components->at(i) = new BeelerReuterModel();
    numOutputs += (components->at(i))->getNumOutputs();
  }
*/
  int count = 0;
  for (int i=0;i<TISSUESIZE/2-ISCHSIZE/2-INTSIZE;i++) {
    for (int j=0;j<TISSUESIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
  }

  
  for (int i=TISSUESIZE/2-ISCHSIZE/2-INTSIZE;i<TISSUESIZE/2-ISCHSIZE/2;i++) {
    for (int j=0;j<TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j<TISSUESIZE/2-ISCHSIZE/2;j++) {
      if (j<i)
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(j+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE)));
      else
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(i+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE)));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2-ISCHSIZE/2;j<TISSUESIZE/2+ISCHSIZE/2;j++) {
      tissue[i][j] = components->at(count) = new IschBR(CalculateCK(i+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE)));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2+ISCHSIZE/2;j<TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j++) {
      if (j>=TISSUESIZE-i)
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(INTSIZE+TISSUESIZE/2+ISCHSIZE/2-j));
      else
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(i+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE)));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j<TISSUESIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
  }


  for (int i=TISSUESIZE/2-ISCHSIZE/2;i<TISSUESIZE/2+ISCHSIZE/2;i++) {
    for (int j=0;j<TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j<TISSUESIZE/2-ISCHSIZE/2;j++) {
      tissue[i][j] = components->at(count) = new IschBR(CalculateCK(j+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE)));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2-ISCHSIZE/2;j<TISSUESIZE/2+ISCHSIZE/2;j++) {
      tissue[i][j] = components->at(count) = new IschBR();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2+ISCHSIZE/2;j<TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j++) {
      tissue[i][j] = components->at(count) = new IschBR(CalculateCK(INTSIZE+TISSUESIZE/2+ISCHSIZE/2-j));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j<TISSUESIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
  }


  for (int i=TISSUESIZE/2+ISCHSIZE/2;i<TISSUESIZE/2+ISCHSIZE/2+INTSIZE;i++) {
    for (int j=0;j<TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j<TISSUESIZE/2-ISCHSIZE/2;j++) {
      if (j<TISSUESIZE-i)
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(j+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE)));
      else
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(INTSIZE+TISSUESIZE/2+ISCHSIZE/2-i));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2-ISCHSIZE/2;j<TISSUESIZE/2+ISCHSIZE/2;j++) {
      tissue[i][j] = components->at(count) = new IschBR(CalculateCK(INTSIZE+TISSUESIZE/2+ISCHSIZE/2-i));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2+ISCHSIZE/2;j<TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j++) {
      if (j>i)
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(INTSIZE+TISSUESIZE/2+ISCHSIZE/2-j));
      else
        tissue[i][j] = components->at(count) = new IschBR(CalculateCK(INTSIZE+TISSUESIZE/2+ISCHSIZE/2-i));
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
    for (int j=TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j<TISSUESIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
  }


  for (int i=TISSUESIZE/2+ISCHSIZE/2+INTSIZE;i<TISSUESIZE;i++) {
    for (int j=0;j<TISSUESIZE;j++) {
      tissue[i][j] = components->at(count) = new BeelerReuterModel();
      gradTissue[i][j] = gradLin[count];
      count += 1;
    }
  }


//components outputs
  for (int i=0;i<getNumComponents();i++) {
    numOutputs += (components->at(i))->getNumOutputs();
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
//  coupParam=Lm*Lm/Tm;
//  K1 = 1.9;
//  K2 = 1.34;


  filter[0][0]=0; filter[0][1]=1; filter[0][2]=0;
  filter[1][0]=1; filter[1][1]=-4;filter[1][2]=1;
  filter[2][0]=0; filter[2][1]=1; filter[2][2]=0;

}

GenericBRIschTissue::~GenericBRIschTissue()
{
}


int GenericBRIschTissue::ModelStart()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelStart();

  return 0;
}


int GenericBRIschTissue::ModelInitSim()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelInitSim();

  return 1;
}


int GenericBRIschTissue::NextSampleHit()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->NextSampleHit();

  return 0;
}


int GenericBRIschTissue::ModelOutputs()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelOutputs();

  return 0;
}


int GenericBRIschTissue::ModelUpdate(double time)
{
  double tempGrad;

  //updating of all cells
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelUpdate(time);


  //init coup param BR cells
  coupParam = K1;
   /* 
  //initialisation of the first cell
  tempGrad = filter[1][2]*((BeelerReuterModel*)tissue[0][1])->getST_X() +
             filter[2][1]*((BeelerReuterModel*)tissue[1][0])->getST_X() +
             filter[2][2]*((BeelerReuterModel*)tissue[1][1])->getST_X() -
             (filter[1][2]+filter[2][1]+filter[2][2])*((BeelerReuterModel*)tissue[0][0])->getST_X();
			 */
  /*
  if ((time>=50.0) && (time<=60.0)) {
    ((BeelerReuterModel*)tissue[0][0])->setIN_Z(5.0);
  } else {
    ((BeelerReuterModel*)tissue[0][0])->setIN_Z(tempGrad*coupParam);
  }
  *gradTissue[0][0] = tempGrad;
  */


  /*Ahmad*/
  //initialisation of the first column
  if ((time>=20.0) && (time<=30.0)) {
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



  

  //i guess there is no need to do the "coupling" sequentially since we just set the external
  //output for all the cells before computing


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


/*
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

  //beeler reuter cells
  for (int i=1;i<TISSUESIZE/2-ISCHSIZE/2-INTSIZE;i++) {
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


  //beeler reuter and ischemic cells
  for (int i=TISSUESIZE/2-ISCHSIZE/2-INTSIZE;i<TISSUESIZE/2+ISCHSIZE/2+INTSIZE;i++) {
    for (int j=1;j<TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j++) {
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

    for (int j=TISSUESIZE/2-ISCHSIZE/2-INTSIZE;j<TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j++) {
    //  if ((i!=1)||(j!=1)) {

    // setting coupParam for ischemic area
      if ((j<i)&&(j<TISSUESIZE-i))
        coupParam = CalculateCoupPar (j+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE));
      else if ((j>=i)&&(j<TISSUESIZE-i))
        coupParam = CalculateCoupPar (i+1-(TISSUESIZE/2-ISCHSIZE/2-INTSIZE));
      else if ((j>=TISSUESIZE-i)&&(j<=i))
        coupParam = CalculateCoupPar (INTSIZE+TISSUESIZE/2+ISCHSIZE/2-i);
      else if ((j>=TISSUESIZE-i)&&(j>i))
        coupParam = CalculateCoupPar (INTSIZE+TISSUESIZE/2+ISCHSIZE/2-j);
      else if ((i>=TISSUESIZE/2-ISCHSIZE/2)&&(i<=TISSUESIZE/2+ISCHSIZE/2)&&
               (j>=TISSUESIZE/2-ISCHSIZE/2)&&(j>=TISSUESIZE/2+ISCHSIZE/2))
        coupParam = K2;
        
        
        tempGrad = filter[0][0]*((IschBR*)tissue[i-1][j-1])->getST_X() +
                   filter[0][1]*((IschBR*)tissue[i-1][j])->getST_X() +
                   filter[0][2]*((IschBR*)tissue[i-1][j+1])->getST_X() +
                   filter[1][0]*((IschBR*)tissue[i][j-1])->getST_X() +
                   filter[1][1]*((IschBR*)tissue[i][j])->getST_X() +
                   filter[1][2]*((IschBR*)tissue[i][j+1])->getST_X() +
                   filter[2][0]*((IschBR*)tissue[i+1][j-1])->getST_X() +
                   filter[2][1]*((IschBR*)tissue[i+1][j])->getST_X() +
                   filter[2][2]*((IschBR*)tissue[i+1][j+1])->getST_X();
        ((IschBR*)tissue[i][j])->setIN_Z(tempGrad*coupParam);
        *gradTissue[i][j] = tempGrad;
    //  }
    }


    // "back" to BR cells
    coupParam = K1;
    for (int j=TISSUESIZE/2+ISCHSIZE/2+INTSIZE;j<TISSUESIZE-1;j++) {
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


  for (int i=TISSUESIZE/2+ISCHSIZE/2+INTSIZE;i<TISSUESIZE-1;i++) {
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

/*  for (int i=0;i<TISSUESIZE*TISSUESIZE;i++) {
      cout << *gradLin[i] << "\t";
  }
  cout << endl;
*/
  return 0;
}


int GenericBRIschTissue::ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas)
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelDerivatives(time,variables,derivadas);

  return 0;
}


int GenericBRIschTissue::ModelTerminate()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelTerminate();

  return 0;
}

double GenericBRIschTissue::CalculateCK (int index) {
  return 7.0+(15.0-7.0)/(INTSIZE+1.0)*index;
}

double GenericBRIschTissue::CalculateCoupPar (int index) {
  return (K1-KSTEP)+(K2-(K1-KSTEP))/(INTSIZE+1.0)*index;
}
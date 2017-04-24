/***************************************************************************
                          genericbrischtissue.h  -  description
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

#ifndef GENERICBRISCHTISSUE_H
#define GENERICBRISCHTISSUE_H

#include "Model.h"
#include "BeelerReuterModel.h"
#include "ischbr.h"
#include <iostream>

#define TISSUESIZE 16
#define INTSIZE 4
#define ISCHSIZE 4
#define FILTERSIZE 3
#define K1 1.9
#define K2 0.4
#define KSTEP 1.0

using namespace std;

typedef vector< vector<Model *> > TwoDTissue;

class GenericBRIschTissue : public Model {
public:

//variables
//double d, Rc, Rm, Cm;
  double Tm, Lm;
  double coupParam;

  int filter[FILTERSIZE][FILTERSIZE];

  Model *tissue[TISSUESIZE][TISSUESIZE];
  double *gradTissue[TISSUESIZE][TISSUESIZE];
  double gradLin[TISSUESIZE*TISSUESIZE][1];

// constructor / destructor
	GenericBRIschTissue();
	~GenericBRIschTissue();

// methods (cf COrgan from Alfredo's AC)
// to be adapted and updated
  virtual int ModelInitSim();
  virtual int NextSampleHit();
  virtual int ModelOutputs();
  virtual int ModelUpdate(double time);
  virtual int ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas);
  virtual int ModelTerminate();
  virtual int ModelStart();

// calculation of CK
  double CalculateCK (int index);
  double CalculateCoupPar (int index);

};


#endif


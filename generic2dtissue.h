/***************************************************************************
                          generic2dtissue.h  -  description
                             -------------------
    begin                : mer jan 28 2004
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

#ifndef GENERIC2DTISSUE_H
#define GENERIC2DTISSUE_H

#include "Model.h"
#include "BeelerReuterModel.h"
#include <iostream>

#define TISSUESIZE 16
#define FILTERSIZE 3

using namespace std;

typedef vector< vector<Model *> > TwoDTissue;

class Generic2DTissue : public Model {
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
	Generic2DTissue();
	~Generic2DTissue();

// methods
  virtual int ModelInitSim();
  virtual int NextSampleHit();
  virtual int ModelOutputs();
  virtual int ModelUpdate(double time);
  virtual int ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas);
  virtual int ModelTerminate();
  virtual int ModelStart();

};


#endif

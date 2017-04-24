/*
 *  BeelerReuterModel.h
 *
 *  Created by Alfredo Hern‡ndez on Fri Jul 26 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __BRMODEL_H
#define __BRMODEL_H

//#include <Carbon/Carbon.h>
#include "Model.h"

class BeelerReuterModel: public Model
{

public :

//inherited methods
    virtual int ModelInitSim();
    virtual int NextSampleHit();
    virtual int ModelOutputs();
    virtual int ModelUpdate(double time/*, ParamVect *inputs*/);
    virtual int ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas);
    virtual int ModelTerminate();
    virtual int ModelStart();
    
    // locals del BR
    double AM,BM,AH,BH,AJ,BJ,AD,BD,AF,BF,AX,BX;
    double IX,INA,ES,IS,IK,IT,IExt;
    
//protected :
BeelerReuterModel();
BeelerReuterModel(double VmRest);
virtual ~BeelerReuterModel();
void RateConstants(ParamVect *variables);

//own methods
  double getST_X();
  double getIN_Z();
  void setIN_Z(double input);
  void setINC(double input);
  void setST_X(double state);

//threshold test variable
  double thresTest;

// init membrane pot
  double VmRestInit;  


//debug methods
  double getINA();

};

#endif

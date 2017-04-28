/*
 *  prostateCell.h
 *
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 * 	03.23.2017
 *
 */

#ifndef __PCELL_H
#define __PCELL_H

//#include <Carbon/Carbon.h>
#include "Model.h"
#include "generic2dtissueProstate.h"

class prostateCell: public Model//, public generic2dtissueProstate
{

  public :

  //inherited methods
  virtual int ModelInitSim();
  virtual int ModelInitSim(double alive,double dead, double tumor, double ves, double state);
  virtual int NextSampleHit();
  virtual int ModelOutputs();
  virtual int ModelUpdate(double time/*, ParamVect *inputs*/);
  virtual int ModelDerivatives(double time/*, ParamVect *variables, ParamVect *derivadas*/);
  virtual int ModelTerminate();
  virtual int ModelStart();
  virtual int ModelRAZ();
  virtual int ModelRAZ(double alive,double dead, double tumor, double ves, double state);
    
  //protected :
  prostateCell();
  prostateCell(double VmRest);
  virtual ~prostateCell();
  void RateConstants(ParamVect *variables);

  //own methods
  double getST_X();
  double getIN_Z();
  double getAlive();
  double getDead();
  double getTumor();
  double getVes();
  
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

/***************************************************************************
                          ischbr.h  -  description
   *                                                                         *
 ***************************************************************************/

#ifndef ISCHBR_H
#define ISCHBR_H


//#include <Carbon/Carbon.h>
#include "Model.h"
#include "math.h"

class IschBR: public Model
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
    double ITO,IP,EK ;

    // resting (init) potential
    double VmRestInit;
    
//protected :
IschBR();
IschBR(double CKInit);
virtual ~IschBR();
void RateConstants(ParamVect *variables);

//own methods
  double getST_X();
  double getIN_Z();
  void setIN_Z(double input);
  void setINC(double input);
  void setST_X(double state);

//threshold test variable
  double thresTest;

// K+ concentration
  double CK;

//debug methods
  double getINA();

};

#endif

/**
 * @(#) SimMeth.cpp
 */

#include "SimMeth.h"
//#include <iostream.h>
#include <stdlib.h>

SimMeth::SimMeth( methName meth, Model* modelo )
{
	causMeth = meth;
	modelSim = modelo;  
}


SimMeth::SimMeth( methName meth )
{
	causMeth = meth;
}


void SimMeth::setModel (Model* modelo)
{
  modelSim = modelo;
}


methName SimMeth::getCausMeth( )
{
	return causMeth;
}


int SimMeth::setCausMeth( methName meth )
{
	causMeth = meth;
	return 0;
}


void SimMeth::initMeth( )
{
	
}


void SimMeth::simulate( double globalTime, double DT )
{
	switch ( causMeth ) {
	  case rk4:
            //simRk4(globalTime, DT);   // We have disabled RK4 for this test. Contact Alfredo or Karim to re-enable it.
            euler(globalTime, DT);
	    break;
    case ac:
      break;
    default:
            euler(globalTime, DT);
      break;
  }
}


void SimMeth::simRk4( double x, double h )
{
  int i;
  double xh,hh,h6;
  ParamVect *dyma,*dyt,*yt;
  int n;
  ParamVect *y,*dydx,*yout;
  

  n = modelSim->getNumStates();
  y = yout = modelSim->getStates();
  dydx = modelSim->getDerivStates();

  dyma = new ParamVect (n,0);
  dyt = new ParamVect (n,0);
  yt = new ParamVect (n,0);

  hh = h*0.5;
  h6 = h/6.0;
  xh = x+hh;
                                                                                                                
  for (i=0;i<n;i++)
    yt->at(i) = y->at(i)+hh*dydx->at(i);

  modelSim->ModelDerivatives (xh,yt,dyt);

  for (i=0;i<n;i++)
    yt->at(i) = y->at(i)+hh*dyt->at(i);

  modelSim->ModelDerivatives(xh,yt,dyma);

  for (i=0;i<n;i++) {
    yt->at(i) = y->at(i)+h*dyma->at(i);
    dyma->at(i) += dyt->at(i);
  }

  modelSim->ModelDerivatives(x+h,yt,dyt);

  for (i=0;i<n;i++)
    yout->at(i) = y->at(i)+h6*(dydx->at(i)+dyt->at(i)+2.0*dyma->at(i));

  delete(yt);
  delete(dyt);
  delete(dyma);
}

void SimMeth::euler(double x, double h)
{
  int i;
  int n;

  ParamVect *y, *dydx, *yout;

  n = modelSim->getNumStates();

  y = yout = modelSim->getStates();
  dydx = modelSim->getDerivStates();

  //Evaluacion de las derivadas en el punto actual AIHR
  modelSim->ModelDerivatives(x, y, dydx);

  for (i=0;i<n;i++) {
    yout->at(i)=y->at(i)+ h*(dydx->at(i));
  }
}




SimMeth::~SimMeth( )
{
  delete modelSim;
}



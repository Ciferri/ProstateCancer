/**
 * @(#) SimMeth.h
 */

#ifndef SimMeth_h_h
#define SimMeth_h_h

#include "Model.h"

enum methName {rk4,euler,ac};

class SimMeth
{
	
public:
	methName causMeth;
	
	Model* modelSim;
  
	void setModel( Model* modelo );
	methName getCausMeth( );
	void initMeth( );
	int setCausMeth( methName meth );
	SimMeth( methName meth, Model* modelo );
    SimMeth( methName meth );
	void simulate( double globalTime, double DT );
	void simRk4( double x, double h );
    void euler(double x, double h);
	~SimMeth( );
	
};

#endif

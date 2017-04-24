/**
 * @(#) Simulator.h
 */

#ifndef Simulator_h_h
#define Simulator_h_h

#include "Model.h"
#include "SimMeth.h"
#include <iostream>
#include <fstream>

typedef vector<double> OutputData;
typedef vector<OutputData *> OutputDataList;

class Simulator
{
	
public:
	OutputDataList* outputList;

  SimMeth* simMeth;

  // output file
  ofstream outfile;
	
	
protected:
	double DT;
	
	double globalTime;
	
	Model* model;
	
	
public:
	void setModel( Model* modelo );
	//void simulate( double globalTime, double DT );
	Simulator( );
  Simulator ( Model* modelo, double x, double h);
	void start( double duration );
	void stop( );
	~Simulator( );

};

#endif

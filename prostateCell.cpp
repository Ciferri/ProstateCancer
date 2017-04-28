/*
 *  prostateCell.cpp
 *
 *  Copyright (c) 2001 INSERM. All rights reserved.
 *	03.23.2017
 */

#include "prostateCell.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


//Internal Parameters
#define PAR_VMREST 		parameters->at(0)
#define PAR_Km 			parameters->at(1)

 
// Inputs
#define IN_PO2 			inputs->at(0)

#define OUT_CONS_O2 	outputs->at(0)


//State variables
#define ST_NUM_ALIVE 	states->at(0)
#define ST_NUM_DEAD 	states->at(1)
#define ST_NUM_TUMOR 	states->at(2)
#define ST_NUM_VES 		states->at(3)
#define ST_PO2_INT 		states->at(4)
#define ST_STATE_1 		states->at(5)


//state variables
#define VAR_NUM_ALIVE	variable->at(0)
#define VAR_NUM_DEAD	variable->at(1)
#define VAR_NUM_TUMOR	variable->at(2)
#define VAR_NUM_VES		variable->at(3)
#define VAR_PO2_INT		variable->at(4)
#define VAR_STATE_1		variable->at(5)


prostateCell::prostateCell() : Model(DESS,1,6,1,2,0)
{
  //Model(int numIn=1,int numSt=1,int numOut =1,int numParam =1, int numComp=0);
}

prostateCell::prostateCell(double VmRest) : Model(DESS,1,6,1,2,0)
{

}

prostateCell::~prostateCell()
{
    
}

int prostateCell::ModelInitSim()
{
	
  ST_NUM_ALIVE 	=0;		
  ST_NUM_DEAD	=0;
  ST_NUM_TUMOR	=0;		
  ST_NUM_VES	=0;
  ST_PO2_INT	=0;
  ST_STATE_1	=0;
	

  return 0;
}

int prostateCell::ModelInitSim(double alive,double dead, double tumor, double ves, double state)
{
	
  ST_NUM_ALIVE 	= alive;
  ST_NUM_DEAD	= dead;
  ST_NUM_TUMOR	= tumor;
  ST_NUM_VES	= ves;
  ST_PO2_INT	= state;
  ST_STATE_1	= 0;
	

  return 0;
}
int prostateCell::ModelRAZ()
{
	ModelInitSim();
}

int prostateCell::ModelRAZ(double alive,double dead, double tumor, double ves, double state)
{
	ModelInitSim(alive, dead, tumor, ves, state);
}

int prostateCell::NextSampleHit()
{
  return 0;
}

int prostateCell::ModelOutputs()
{
  OUT_CONS_O2 = ST_PO2_INT;
  return 0;
}

int prostateCell::ModelUpdate(double time/*, ParamVect *inputs*/)
{
 
  ST_NUM_ALIVE 	= 0;		
  ST_NUM_DEAD	= 0;
  ST_NUM_TUMOR	= 0;		
  ST_NUM_VES	= 0;
  ST_PO2_INT	= IN_PO2;// - OUT_CONS_O2;
  ST_STATE_1	= 0;
 

	
	
  return 0;
}


int prostateCell::ModelDerivatives(double time/*, ParamVect *variables, ParamVect *derivadas*/)
{
  return 0;
}

int prostateCell::ModelTerminate()
{
  return 0;
}

int prostateCell::ModelStart()
{
  return 0;
}

void prostateCell::RateConstants(ParamVect *variables)
{

}


double prostateCell::getST_X()
{
  return OUT_CONS_O2;
}


double prostateCell::getIN_Z()
{
  return IN_PO2;
}

double prostateCell::getAlive()
{
  return ST_NUM_ALIVE;
}

double prostateCell::getDead()
{
  return ST_NUM_DEAD;
}

double prostateCell::getTumor()
{
  return ST_NUM_TUMOR;
}

double prostateCell::getVes()
{
  return ST_NUM_VES;
}


void prostateCell::setINC(double input)
{
	
}


void prostateCell::setIN_Z(double input)
{
  IN_PO2=input;
}



void prostateCell::setST_X(double state)
{
  OUT_CONS_O2 = state;
}


double prostateCell::getINA()
{
  return 0;
}


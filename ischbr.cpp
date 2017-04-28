/***************************************************************************
                          ischbr.cpp  -  description
                             -------------------
    begin                : lun nov 10 2003
    copyright            : (C) 2003 by Antoine Defontaine
    email                : antoine.defontaine@univ-rennes1.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ischbr.h"

#include <iostream>

//#define CK 7


//Internal Parameters
#define PAR_GNA		parameters->at(0)
#define PAR_GNAC	parameters->at(1)
#define PAR_ENA		parameters->at(2)
#define PAR_GS		parameters->at(3)
#define PAR_C		parameters->at(4)

// Inputs
#define IN_ST		inputs->at(0)
#define INC     inputs->at(1)

#define OUT_VM		outputs->at(0)
/*#define OUT_M		outputs->at(1)
#define OUT_H		outputs->at(2)
#define OUT_J		outputs->at(3)
#define OUT_CA		outputs->at(4)
#define OUT_D		outputs->at(5)
#define OUT_F		outputs->at(6)
#define OUT_X1		outputs->at(7)
#define OUT_IX		outputs->at(8)
#define OUT_INA		outputs->at(9)
#define OUT_ES		outputs->at(10)
#define OUT_IS		outputs->at(11)
#define OUT_IK		outputs->at(12)
#define OUT_IT		outputs->at(13)*/

//State variables
#define ST_VM		states->at(0)
#define ST_M		states->at(1)
#define ST_H		states->at(2)
#define ST_J		states->at(3)
#define ST_CA		states->at(4)
#define ST_D		states->at(5)
#define ST_F		states->at(6)
#define ST_X1		states->at(7)


//State variables
#define VAR_VM		variables->at(0)
#define VAR_M		variables->at(1)
#define VAR_H		variables->at(2)
#define VAR_J		variables->at(3)
#define VAR_CA		variables->at(4)
#define VAR_D		variables->at(5)
#define VAR_F		variables->at(6)
#define VAR_X1		variables->at(7)



IschBR::IschBR() : Model(DESS,2,8,1,5,0)
{
//Model(int numIn=1,int numSt=1,int numOut =1,int numParam =1, int numComp=0);
//thresTest = 0;
CK = 15.0;
VmRestInit = 3.0*CK-105.0;
}

IschBR::IschBR(double CKInit) : Model(DESS,2,8,1,5,0)
{
//Model(int numIn=1,int numSt=1,int numOut =1,int numParam =1, int numComp=0);
//thresTest = 0;
CK = CKInit;
VmRestInit = 3.0*CK-105.0;
}

IschBR::~IschBR()
{

}

int IschBR::ModelInitSim()
{


    //Estado estable del modelo

	ST_VM = VmRestInit;
        //ST_VM = -90.0;
	ST_CA = 3e-7;
//	OUT_IT = 0.0;
	IN_ST = 0.0;
  INC = 0.0;

      // PAR_GNA	= 4.0;
        PAR_GNA = 35.0;
        PAR_GNAC =  0.003;
        PAR_ENA	= 50.0;
	      PAR_GS = 0.09;
        PAR_C = 1.2;

        IExt = 0;

        RateConstants(states);

        ST_M = AM / (AM + BM);
	ST_H = AH / (AH + BH);
	ST_J = AJ / (AJ + BJ);
	ST_D = AD / (AD + BD);
	ST_F = AF / (AF + BF);
	ST_X1 = AX / (AX + BX);
;

//        ST_M = 0.01;
//	ST_H = 0.988;
//	ST_J = 0.98;
//	ST_D = 0.003;
//	ST_F = 0.8;
//	ST_X1 = 0.001;



        // I externa de estimulo


        // init currents
        INA = 0;
        IK = 0;
        IX = 0;
        IS = 0;
        IP = 0;
        ITO = 0;
        

        return 0;

}

int IschBR::NextSampleHit()
{
    return 0;
}
int IschBR::ModelOutputs()
{
    double Z1,Z2,Z3;


        //Corriente de sodio
        //INA = ((PAR_GNA * ST_M * ST_M * ST_M * ST_H * ST_J) + PAR_GNAC) * ( ST_VM - PAR_ENA);
        INA = PAR_GNA*ST_M*ST_M*ST_M*ST_H*(ST_VM-34.0);


        //Corriente lenta de entrada :
        ES = -82.3 - 13.0287 * log(ST_CA);
        IS = PAR_GS * ST_D * ST_F * (ST_VM - ES);
        ////IS = PAR_GS * ST_D * ST_F * (ST_VM + 66.18 + 13.0287 * log(ST_CA)); // Segun el libro amarillo
//      IS = (0.1 * derivStates->at(6) + (0.045/(1+exp(-0.15*(ST_VM + 40)))))*(ST_VM - 70);

        
        // Time-dependent outward current
	      //IX = ST_X1 * (0.8 * (exp(0.04 * (ST_VM + 77.0)) -1.0) / exp (0.04 * (ST_VM + 35.0)));
        IX = 0.037 * (150.0 - CK * exp(-ST_VM/25.0))* ST_X1;

        // Time-independent outward current
/*        Z1 = 4.0 * (exp(0.04 * (ST_VM + 85.0)) - 1);
	Z2 = exp(0.08 * (ST_VM + 53.0)) + exp(0.04 * (ST_VM + 53.0));
	Z3 = 0.2 * (ST_VM + 23.0) / (1.0 - exp( -0.04 * (ST_VM + 23.0)));
	IK = 0.35 * ((Z1/Z2) + Z3);
*/        EK = 26.7*log(CK/150.0);     //RT/F cf Nernst
        Z1 = 0.02*(ST_VM  - EK);
        Z2 = 0.02*(ST_VM  - (EK+50.0));
        Z3 = 0.0475*(ST_VM  - (EK+110.0));
        IK = 1.36 * exp ((EK/144.4)+Z1 -3.0*Z2)*sinh(Z1)/cosh(Z2)+0.98*Z3*exp(Z3)/sinh(Z3);


        //ITO
        //r=1 to be checked
        ITO = 0.19 * 1.0 /*r*/ * (CK + 0.2) * (ST_VM + 12.0) * exp ((ST_VM + 72.0)/50.0) / ((CK + 30.0) * (1.0 + 8.0 * 10e-7 / ST_CA) * (1.0 - exp (-( ST_VM + 12.0) / 5.0)));

        //IP
        IP = 0.8 * (1.0 - exp(-CK/2.2));
                                          
        //I total
        IT = IX + INA + IS + IK + ITO  + IP;

 //       cout << ITO << '\t';
/*        cout << EK << '\t';
        cout << IK << '\t';
        cout << IT << '\t';
*/

        OUT_VM	= ST_VM;
/*      OUT_M	= ST_M;
        OUT_H	= ST_H;
        OUT_J	= ST_J;
        OUT_CA	= ST_CA;
        OUT_D	= ST_D;
        OUT_F	= ST_F;
        OUT_X1	= ST_X1;
        OUT_IX	= IX;
        OUT_INA	= INA;
        OUT_ES = ES;
        OUT_IS = IS;
        OUT_IK = IK;
        OUT_IT = IN_ST;*/

return 0;
}

int IschBR::ModelUpdate(double time/*, ParamVect *inputs*/)
{

  //IN_ST = inputs->at(0);


//    if /*(*/((time >= 50.0)&&(time <= 60.0)) /*|| ((time >= 250.0)&&(time <= 255.0)))*/
//       setINC(5.0);
//       else
//       setINC(0);
  //if ((time>=5.0)&&(time<5.2))
  //  setST_X(100.0);


return 0;
}


int IschBR::ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas)
{

    RateConstants(variables);    // may be to be done once for all


    // membrana dv/dt
    derivadas->at(0)=  (-1.0/PAR_C)* IT + IN_ST + INC;
    //derivadas->at(0)=  (-1.0/PAR_C)*(VAR_IX + VAR_INA + VAR_IS + VAR_IK + VAR_IExt);

    // calculo de la puerta m dm/dt
    derivadas->at(1)=  (AM * (1.0 - VAR_M) - BM * VAR_M);

    // calculo de la puerta h dh/dt
    derivadas->at(2)=  (AH * (1.0 - VAR_H) - BH * VAR_H);

    // calculo de la puerta j dj/dt
    derivadas->at(3)=  (AJ * (1.0 - VAR_J) - BJ * VAR_J);

    // calculo de la CA dCa/dt
    derivadas->at(4)=  (-1e-7 * IS + 0.07 * (1e-7 - VAR_CA));
    //derivadas->at(4)=  0.07 * (1 - 1e7 * VAR_CA) - IS; // Segun el libro amarillo

    // calculo de la D dD/dt
    derivadas->at(5)=  (AD * (1.0 - VAR_D) - BD * VAR_D);

    // calculo de la F dF/dt
    derivadas->at(6)=  (AF * (1.0 - VAR_F) - BF * VAR_F);

    // calculo de la F dF/dt
    derivadas->at(7)=  (AX * (1.0 - VAR_X1) - BX * VAR_X1);


return 0;
}

int IschBR::ModelTerminate()
{
return 0;
}

int IschBR::ModelStart()
{
return 0;
}

void IschBR::RateConstants(ParamVect *variables)
{
        double V;

        V = VAR_VM;

        // Sodium current M-gate
	AM = (-1 * (V + 47.0)) / (exp(- 0.1 * (V + 47.0)) - 1.0);
        BM = (40 * exp( -0.056 * (V + 72.0)));

        // Sodium current H-gate
	AH = (0.126 * exp( -0.25 * (V+77.0)));
	BH = 1.7/ (exp ( -0.082 * (V + 22.5)) + 1.0);

        // Sodium current J-gate
	AJ = (0.055 * exp( -0.25 * (V + 78.0))) / (exp (-0.2 * (V + 78.0)) + 1.0);
	BJ = 0.3 / (exp ( -0.1 * (V + 32.0)) + 1.0);

        // Slow inward current d gate
	AD = (0.095 * exp(-(V - 5.0)/100.0)) / (exp(-(V - 5.0)/13.89) + 1.0);
	BD = (0.07 * exp( -(V + 44.0)/59.0)) / (exp((V + 44.0)/20.0) + 1.0);

        // Slow inward current f gate
	AF = (0.012 * exp( -(V + 28.0)/125.0)) / (exp((V + 28.0)/6.67) + 1.0);
	BF = (0.0065 * exp( -(V + 30.0)/50.0)) / (exp(-(V + 30.0)/5.0) + 1.0);


	// Time-dependent outward current x1 gate
	AX = (0.0005 * exp( (V + 50.0)/12.1)) / (exp((V + 50.0)/17.5) + 1.0);
	BX = (0.0013 * exp( -(V + 20.0)/16.67)) / (exp(-(V + 20.0)/25.0) + 1.0);


}


double IschBR::getST_X()
{
  return OUT_VM;
}


double IschBR::getIN_Z()
{
  return IN_ST;
}


void IschBR::setINC(double input)
{
  INC=input;
}


void IschBR::setIN_Z(double input)
{
  IN_ST=input;
}


void IschBR::setST_X(double state)
{
  OUT_VM=state;
}


double IschBR::getINA()
{
  return INA;
}
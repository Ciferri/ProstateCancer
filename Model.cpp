/*
 *  Model.cpp
 *  AlfSimLib
 *
 *  Created by Alfredo Hern‡ndez on Fri Jul 26 2002.
 *  Copyright (c) 2001 INSERM. All rights reserved.
 *
 */

#include "Model.h"
#include <iostream>

Model::Model(modelType type,int numIn,int numSt,int numOut,int numParam,int numComp) {

    typeModel = type;
    numInputs = numIn;
    numStates = numSt;
    numOutputs = numOut;
    numParameters = numParam;
    numComponents = numComp;

    inputs = new ParamVect( numInputs, 0 );
    states = new ParamVect( numStates, 0 );
    derivStates	= new ParamVect( numStates, 0 );
    outputs = new ParamVect( numOutputs, 0 );
    parameters = new ParamVect( numParameters,0 );
    components = new vector<Model *> ( numComponents, 0 );
}

Model::~Model() {
}

int Model::ModelInitSim() {
    int i;

    for(i=0;i<numInputs;i++) {
      inputs->at(i) = i;
      //cout << inputs[i];
    }
    return 1;
}

int Model::NextSampleHit() {

    return 0;
}

int Model::ModelOutputs() {

    return 0;
}

int Model::ModelUpdate(double time) {

    return 0;
}

int Model::ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas) {

    return 0;
}

int Model::ModelTerminate() {

    return 0;
}

int Model::ModelStart() {

    return 0;
}

int Model::ModelRAZ() {

    return 0;
}


int Model::ModelRAZ(double alive,double dead, double tumor, double ves, double state) {

    return 0;
}

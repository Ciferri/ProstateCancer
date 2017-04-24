/*
 *  Model.h
 *  AlfSimLib
 *
 *  Created by Alfredo Hern‡ndez on Fri Jul 26 2002.
 *  Copyright (c) 2001 INSERM. All rights reserved.
 *
 */


#ifndef __MODEL_H
#define __MODEL_H

#include <vector>


// standard classes used
// cf gcc 3
// using std::vector;
using namespace std;

// define paramters storage
typedef vector<double> ParamVect;

// model types
enum	modelType {DEVS,DESS,DTSS};


// instantiation of class Model
class Model {

    public :
        virtual ~Model(); // Destructor

        // methods
        virtual int ModelInitSim();
        virtual int NextSampleHit();
        virtual int ModelOutputs();
        virtual int ModelUpdate(double time);
        virtual int ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas);
        virtual int ModelTerminate();
        virtual int ModelStart();
        virtual int ModelRAZ();
        virtual int ModelRAZ(double alive,double dead, double tumor, double ves, double state);


        // IO methods
        ParamVect *getInputs() {
            return inputs;
        }

        ParamVect *getStates() {
            return states;
        }

        ParamVect *getDerivStates() {
            return derivStates;
        }

        ParamVect *getOutputs() {
            return outputs;
        }

        ParamVect *getParameters() {
            return parameters;
        }

        modelType getModelType() {
            return typeModel;
        }

        int getNumInputs() {
            return numInputs;
        }

        int getNumStates() {
            return numStates;
        }

        int getNumOutputs() {
            return numOutputs;
        }

        int getNumParameters() {
            return numParameters;
        }

        int getNumComponents() {
            return numComponents;
        }

        
    // protected :
    // Protected instance variables

        modelType	typeModel;
        int		numInputs;
        int		numStates;
        int		numOutputs;
        int	 	numParameters;
        unsigned int		numComponents;

        ParamVect *inputs;	//model inputs
        ParamVect *states;	//state variables of the model
        ParamVect *derivStates;	//auxiliary variable to cache the value of state variables during integration
        ParamVect *outputs;	//outputs of the model (usually a function of the state variables)
        ParamVect *parameters;	//parameters of the model that can be modified during the simulation
        vector<Model *>  *components;	//vector containing the sub-models of this model
        Model	*parent;	//parent model, for model components.
     
    //protected :
        Model(modelType type,int numIn,int numSt,int numOut,int numParam, int numComp);// protected, so
                                                                                       // it can only be used by a derived class
    

};

#endif

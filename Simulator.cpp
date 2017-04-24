/**
 * @(#) Simulator.cpp
 */

#include "Simulator.h"
#include <stdlib.h>

void Simulator::setModel( Model* modelo )
{
  model = modelo;
}

Simulator::~Simulator( )
{
  delete model;
  delete outputList;
}


void Simulator::stop( )
{
	
}


void Simulator::start( double duration )
{
  int index = 0;
  int toto =0;
//  int bdn,smb;
  
  simMeth->initMeth();

for (int i=0;i<model->getNumOutputs();++i)    //creation of each element of outputList
    outputList->push_back (new OutputData());   //vector of numberOfOutputs pointers on globalTime/DT samples

  model->ModelInitSim();
  model->ModelStart();
    
    // Simulation loop

    for (int j=0;j<duration/DT;j++) {
      globalTime = j*DT;
      //model->NextSampleHit();
      model->ModelUpdate(globalTime);

      if (model->getNumComponents()==0) {
        simMeth->simulate(globalTime,DT);
      } else {
        for (int k=0;k<model->getNumComponents();++k) {
            
        // TO-DO: distribute each call of the simulate method in a different GPU.
          simMeth->setModel(model->components->at(k));
          simMeth->simulate(globalTime,DT);
        }
      }

      model->ModelOutputs();
        
        
        if ((j%10)==0) {
            cout << "Simulator time = " << globalTime << endl;
        }
        
      
      // add something to check the outputs - cf Al's stuff
      if ((j%10)==0) {      // one output each xxx outputs
        if (model->getNumComponents()==0) {
          for (int i=0;i<model->getNumOutputs();++i) {
            (outputList->at(i))->push_back((model->getOutputs())->at(i));   //copy of the outputs in outputList
            outfile << (*(outputList->at(i))).at(toto) << '\t';
          }           
        } else {
          for (int k=0;k<model->getNumComponents();++k) {
            for (int i=0;i<(model->components->at(k))->getNumOutputs();++i) {
              index = (model->components->at(k))->getNumOutputs()*k+i;
              (outputList->at(index))->push_back((model->components->at(k)->getOutputs())->at(i));   //copy of the outputs in outputList
              outfile << (*(outputList->at(index))).at(toto) << '\t';
            }
          }
        }
        outfile << endl ;
        toto += 1;
      }   
    }
      
 model->ModelTerminate();

  // close file
  outfile.close();
}


Simulator::Simulator( )
{
  globalTime = 0;
  DT = 0.01;
  outputList = new OutputDataList();
  simMeth = new SimMeth (euler); // TO-DO: Create one instance of this class for each GPU

  //output file
  outfile.open ("out.dat");
}


Simulator::Simulator ( Model* modelo, double x, double h)
{
  model = modelo;
  globalTime = x;
  DT = h;
  outputList = new OutputDataList();
  simMeth = new SimMeth (euler);
}



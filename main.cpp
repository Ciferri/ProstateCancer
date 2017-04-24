/*
 *  main.cpp
 *
 *  Created by Alfredo Hernández on Fri Jul 26 2002.
 *  Copyright (c) 2001 INSERM. All rights reserved.
 *
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include "Model.h"
#include "Simulator.h"
#include "generic2dtissueProstate.h"
#include "prostateCell.h"

int main(int argc, char *argv[])
{
 
  Model *modelo;
  Simulator *sim;

  modelo = new generic2dtissueProstate();  
  //modelo = new GenericBRIschTissue();
    
  sim = new Simulator();
  sim->setModel(modelo);

  sim->start(500);

  return EXIT_SUCCESS;
}

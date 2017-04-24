/**
 * 	
 *	\brief Tissue prostatique
 * Tissue contenant plusieurs cellules prostatique (prostateCell)
 * 
 * 
 * 
 *	generic2dtissueProstate.cpp
 *
 *  Copyright (c) 2001 INSERM. All rights reserved.
 */



#include "generic2dtissueProstate.h"


/**
 * Contructeur.
 * Création d'un vecteur de prostateCell
 */
generic2dtissueProstate::generic2dtissueProstate() : Model(DESS,0,0,0,0,TISSUESIZE*TISSUESIZE)
{
  // creation of the cells composing the tissu model
  for (int i=0;i<getNumComponents();i++)
  {      
    components->at(i) = new prostateCell();				/**< Création du vecteur de prostateCell */
    numOutputs += (components->at(i))->getNumOutputs();
  }

  int count = 0;
  for (int i=0;i<TISSUESIZE;i++)
  {
    for (int j=0;j<TISSUESIZE;j++)
    {
      tissue[i][j] = components->at(count);				/**< tableau du tissue */
      count += 1;
    }
  }

  //coupling parameters

  coeff_diff = 2*pow(10,-9);
  size = 20;
  time_step_s = 0.07;
  coupParam = coeff_diff*pow(10,-12)*time_step_s/(size*size);	/**< Paramètre de la diffusion */
  
  Vmax = 15;
  K_conso = 2.5;
  
  //~ filter[0][0]=0.125; filter[0][1]=0.125; filter[0][2]=0.125;
  //~ filter[1][0]=0.125; filter[1][1]=1;filter[1][2]=0.125;
  //~ filter[2][0]=0.125; filter[2][1]=0.125; filter[2][2]=0.125;				
  filter[0][0]=1; filter[0][1]=1; filter[0][2]=1;
  filter[1][0]=1; filter[1][1]=8;filter[1][2]=1;
  filter[2][0]=1; filter[2][1]=1; filter[2][2]=1;				
}

/**
 * 
 * Destructeur
 * 
 */
generic2dtissueProstate::~generic2dtissueProstate()
{
}

int generic2dtissueProstate::ModelStart()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelStart();

  return 0;
}

/**
 * 
 * Initialisation du tissue.
 * 
 * */
int generic2dtissueProstate::ModelInitSim()
{
  for (int i=0;i<getNumComponents();i++)
  {
	(components->at(i))->ModelRAZ();	/**< Fonction qui initialise toute les pO2 à zéro */
  }
  return 1;
}

/**
 * 
 * Surcharge de la classe ModelInitSim
 * 
 * */
int generic2dtissueProstate::ModelInitSim(int x, int y,double pO2)
{
  int indice = Coord_XY_to_K(x,y);		/**< Fonction qui prend en paramètre x et y et renvoie un indice */
  (components->at(indice))->ModelRAZ(0.0, 0.0, 0.0, 1.0, pO2); 	/**< Pour un vaisseau, on met la pO2 à 42mmHg */
  return 1;
}

//Fonction qui initialise la matrice d'entrer en fonction de l'image

int generic2dtissueProstate::ModelInitSim(double *tab,int size_x, int size_y)
{
	int count= 0;
  for (int i=0;i<size_x-1;i++)
  {
	for (int j;j<size_y-1;j++)
	{
		//if(valeur de l'image == rouge) { (components->at(indice))->ModelRAZ(0.0, 0.0, 0.0, 1.0, pO2); }
		//else if(valeur de limage == bleu) { (components->at(indice))->ModelRAZ(0.0, 0.0, 1.0, 0.0, pO2); }
		//etc 
	count += 1;
	}
  }
  return 1;
}

int generic2dtissueProstate::NextSampleHit()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->NextSampleHit();

  return 0;
}

int generic2dtissueProstate::ModelOutputs()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelOutputs();

  return 0;
}

/**
 * 
 * Mise à jour du tissue 
 * 
 * */
int generic2dtissueProstate::ModelUpdate(double time)
{
  double tempGrad;

  //updating of all cells
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelUpdate(time);
  
  ModelInitSim((TISSUESIZE-1)/2,(TISSUESIZE-1)/2,INIT_VASCULAR_PO2); /**< Test pour avoir une impulsion au centre de l'image */
  
  for (int i=0;i<TISSUESIZE;i++)
    for (int j=0;j<TISSUESIZE;j++){
		initImageTissue[i][j] = ((prostateCell*)tissue[i][j])->getST_X();
		Conso_PO2[i][j] = (initImageTissue[i][j]*Vmax*time_step_s)/(K_conso + initImageTissue[i][j]);
	}
  
  /// --Cas particulier--
  
  /**
   * First row / Middle cells
   * */
  for (int j=1;j<TISSUESIZE-1;j++)
  {	
    tempGrad = filter[1][0]*((prostateCell*)tissue[0][j-1])->getST_X() +
      filter[1][2]*((prostateCell*)tissue[0][j])->getST_X() +
      filter[2][0]*((prostateCell*)tissue[1][j+1])->getST_X() +
      filter[2][1]*((prostateCell*)tissue[1][j-1])->getST_X() +
      filter[2][2]*((prostateCell*)tissue[1][j+1])->getST_X() -
      (filter[0][0]+filter[0][1]+filter[0][2]+filter[1][0]+filter[1][2])*((prostateCell*)tissue[0][j])->getST_X();    
    resDiffusion[0][j] = tempGrad*coupParam/5; // Resultat de la diffusion
    
  }
  
  /**
   * First row / First Cell
   * */   
  tempGrad = filter[1][2]*((prostateCell*)tissue[TISSUESIZE-2][0])->getST_X() +
    filter[2][1]*((prostateCell*)tissue[TISSUESIZE-2][1])->getST_X() +
    filter[2][2]*((prostateCell*)tissue[TISSUESIZE-1][1])->getST_X() -
    (filter[1][2]+filter[2][1]+filter[2][2])*((prostateCell*)tissue[0][0])->getST_X();  
  resDiffusion[0][0] = tempGrad*coupParam/3;
    
  /**
   * First row / Last Cell
   * */   
  tempGrad = filter[1][0]*((prostateCell*)tissue[0][TISSUESIZE-2])->getST_X() +
    filter[2][0]*((prostateCell*)tissue[1][TISSUESIZE-2])->getST_X() +
    filter[2][1]*((prostateCell*)tissue[1][TISSUESIZE-1])->getST_X() -
    (filter[1][0]+filter[2][0]+filter[2][1])*((prostateCell*)tissue[0][TISSUESIZE-1])->getST_X();  
  resDiffusion[0][TISSUESIZE-1] = tempGrad*coupParam/3;
  
  /**
   * Last row / First Cell
   * */   
  tempGrad = filter[0][1]*((prostateCell*)tissue[TISSUESIZE-2][0])->getST_X() +
    filter[0][2]*((prostateCell*)tissue[TISSUESIZE-2][1])->getST_X() +
    filter[1][2]*((prostateCell*)tissue[TISSUESIZE-1][1])->getST_X() -
    (filter[0][1]+filter[0][2]+filter[1][2])*((prostateCell*)tissue[TISSUESIZE-1][0])->getST_X();  
  resDiffusion[TISSUESIZE-1][0] = tempGrad*coupParam/3;

  /**
   * Last row / Middle Cells
   * */
  for (int j=1;j<TISSUESIZE-1;j++)
  {	
    tempGrad = filter[0][0]*((prostateCell*)tissue[TISSUESIZE-2][j-1])->getST_X() +
      filter[0][1]*((prostateCell*)tissue[TISSUESIZE-2][j])->getST_X() +
      filter[0][2]*((prostateCell*)tissue[TISSUESIZE-2][j+1])->getST_X() +
      filter[1][0]*((prostateCell*)tissue[TISSUESIZE-1][j-1])->getST_X() +
      filter[1][2]*((prostateCell*)tissue[TISSUESIZE-1][j+1])->getST_X() -
      (filter[0][0]+filter[0][1]+filter[0][2]+filter[1][0]+filter[1][2])*((prostateCell*)tissue[TISSUESIZE-1][j])->getST_X();    
    resDiffusion[TISSUESIZE-1][j] = tempGrad*coupParam/5;
  }
      
  /**
   * Last row / Last Cell
   * */   
  tempGrad = filter[0][0]*((prostateCell*)tissue[TISSUESIZE-2][TISSUESIZE-2])->getST_X() +
    filter[0][1]*((prostateCell*)tissue[TISSUESIZE-2][TISSUESIZE-1])->getST_X() +
    filter[1][0]*((prostateCell*)tissue[TISSUESIZE-1][TISSUESIZE-2])->getST_X() -
    (filter[0][0]+filter[0][1]+filter[1][0])*((prostateCell*)tissue[TISSUESIZE-1][TISSUESIZE-1])->getST_X();
  resDiffusion[TISSUESIZE-1][TISSUESIZE-1] = tempGrad*coupParam/3;

  /**
   * Last column / Middle Cells
   * */
  for (int i=1;i<TISSUESIZE-1;i++)
  {	  
    tempGrad = filter[0][0]*((prostateCell*)tissue[i-1][TISSUESIZE-2])->getST_X() +
      filter[0][1]*((prostateCell*)tissue[i-1][TISSUESIZE-1])->getST_X() +
      filter[1][0]*((prostateCell*)tissue[i][TISSUESIZE-2])->getST_X() +
      filter[2][0]*((prostateCell*)tissue[i+1][TISSUESIZE-2])->getST_X() +
      filter[2][1]*((prostateCell*)tissue[i+1][TISSUESIZE-1])->getST_X() -
      (filter[0][0]+filter[0][1]+filter[1][0]+filter[2][0]+filter[2][1])*((prostateCell*)tissue[i][TISSUESIZE-1])->getST_X();
    resDiffusion[i][TISSUESIZE-1] = tempGrad*coupParam/5;
  }
  
  /**
   * First column / Middle Cells
   * */
  for (int i=1;i<TISSUESIZE-1;i++) 
  {	  
	tempGrad = filter[0][1]*((prostateCell*)tissue[i-1][0])->getST_X() +
      filter[0][2]*((prostateCell*)tissue[i-1][1])->getST_X() +
      filter[1][2]*((prostateCell*)tissue[i][1])->getST_X() +
      filter[2][1]*((prostateCell*)tissue[i+1][0])->getST_X() +
      filter[2][2]*((prostateCell*)tissue[i+1][1])->getST_X() -
      (filter[0][1]+filter[0][2]+filter[1][2]+filter[2][1]+filter[2][2])*((prostateCell*)tissue[i][0])->getST_X();
    resDiffusion[i][0] = tempGrad*coupParam/5;
  }

  /**
   * coupling between middle cells
   * */
  for (int i=1;i<TISSUESIZE-1;i++)
  {
    for (int j=1;j<TISSUESIZE-1;j++)
    {
		tempGrad = filter[0][0]*((prostateCell*)tissue[i-1][j-1])->getST_X() +
			filter[0][1]*((prostateCell*)tissue[i-1][j])->getST_X() +
			filter[0][2]*((prostateCell*)tissue[i-1][j+1])->getST_X() +
			filter[1][0]*((prostateCell*)tissue[i][j-1])->getST_X() -
			filter[1][1]*((prostateCell*)tissue[i][j])->getST_X() +
			filter[1][2]*((prostateCell*)tissue[i][j+1])->getST_X() +
			filter[2][0]*((prostateCell*)tissue[i+1][j-1])->getST_X() +
			filter[2][1]*((prostateCell*)tissue[i+1][j])->getST_X() +
			filter[2][2]*((prostateCell*)tissue[i+1][j+1])->getST_X();
		resDiffusion[i][j] = tempGrad*coupParam/8;
    }
  }
  
  for (int i=0;i<TISSUESIZE;i++)
    for (int j=0;j<TISSUESIZE;j++)
		((prostateCell*)tissue[i][j])->setIN_Z(initImageTissue[i][j] - resDiffusion[i][j] - Conso_PO2[i][j]); /**< set the pO2 of cell */
  
  return 0;
}

int generic2dtissueProstate::ModelDerivatives(double time, ParamVect *variables, ParamVect *derivadas)
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelDerivatives(time,variables,derivadas);

  return 0;
}

int generic2dtissueProstate::ModelTerminate()
{
  for (int i=0;i<getNumComponents();i++)
    (components->at(i))->ModelTerminate();

  return 0;
}

/**
 * Fonction qui prend en paramètre des coordonné x et y et rend une position de vecteur.
 * */
int generic2dtissueProstate::Coord_XY_to_K(int x, int y)
{
	return x*TISSUESIZE + y;
}

/**
 * Fonction qui prend en paramètre une position de vecteur et qui rend un tableau de coordonné x et y.
 * */
int *generic2dtissueProstate::Coord_K_to_XY(int k)
{
	int *tab= new int[2];
	tab[0] = k/TISSUESIZE;
    tab[1] = k%TISSUESIZE;
    
    return tab;
    // dans le main : int *array = CoordVectXY(k);	
}





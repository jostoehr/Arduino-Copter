/*
  ------------------
   Quadcopter Pilot
  ------------------
  author : vincent JAUNET
  mail : vincent.jaunet@hotmail.fr

  Copyright (c) <2014> <Vincent Jaunet>

  Modified 05-2017, johannes stoehr
  mail: post@johannes-stoehr.de
*/


#include "main.h"

//-------------------------------------
//--------- Main-----------------------

int main(int argc, char *argv[])
{
	printf("QuadCopter Pilot v0.1\n");
	printf("----------------------\n");
	printf("\n");

	//initializing Network communication
	remote.create();

	/* Waiting fo Start command */
	while (true) {

		remote.exec_remoteCMD();
		usleep(2000);

	}//end

	return 0;
}


//

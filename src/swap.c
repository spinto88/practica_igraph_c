
#include "swap.h"

void swap(int *px, int *py)
{

	/* Swap function: exchange the value of px with the value 
	of py. It's an auxiliar function for the fragment identifier, 
	for example.*/   

	int temp;
	temp = *px;
	*px = *py;
	*py = temp; 
}


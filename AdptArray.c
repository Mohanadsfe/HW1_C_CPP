#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "AdptArray.h"
#include "Person.h"
#include "book.h"
#include <sys/types.h>



typedef struct AdptArray_
{
	int SIZE;
	PElement* pelement;
	DEL_FUNC delfunc;
	COPY_FUNC copyfunc;
    PRINT_FUNC printfunc;
}AdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyfunc, DEL_FUNC delfunc, PRINT_FUNC printfunc)
{
	PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray));
	if (arr == NULL)
		return NULL;
	arr->SIZE = 0;
	arr->pelement = NULL;
	arr->delfunc = delfunc;
	arr->copyfunc = copyfunc;
    arr->printfunc = printfunc;

	return arr;
}


void DeleteAdptArray(PAdptArray arr)
{
	
	if (arr == NULL)
		return;
        
	for(int i = 0; i < arr->SIZE; ++i)
	{
        if ((arr->pelement)[i]!=NULL)
        {

            arr->delfunc((arr->pelement)[i]);

        }
        
	}
	free(arr->pelement);
	free(arr);
}



Result SetAdptArrayAt(PAdptArray arr, int index, PElement pnew)
{

	PElement* peNEW;
    // Check if success to Allocte memory for the array elements
	if (arr == NULL)
		return FAIL; // if not, then return 0 (it saved in the struct of the AdptArray.h)

    // if we get here , that means it success to allocate memory. 
	if (index >= arr->SIZE) 
	{ 
        //Inside the if, that means' we add a new element ,not replacing with any element. 
		

		if ((peNEW = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
			return FAIL; 

		memcpy(peNEW, arr->pelement, (arr->SIZE) * sizeof(PElement)); // Copy the allocate to org array . 

		free(arr->pelement); // free the memory of the element

		arr->pelement = peNEW; // get new one

	}

    // Here, that's mean ,we should replace with element alleardy in the array. 

	// delete the current element 
    if ((arr->pelement)[index]!=NULL){
    
        	arr->delfunc((arr->pelement)[index]);  

    }
    

    // copy a new element and put it in the same index ,where we deleted.
	(arr->pelement)[index] = arr->copyfunc(pnew);

    // Update the Size of the array elements

    if (index >= arr->SIZE)
    {
        arr->SIZE = index + 1;
    }
    else{
                arr->SIZE = arr->SIZE ; 

    }
    
	return SUCCESS;
}




PElement GetAdptArrayAt(PAdptArray arr, int index){

         if (index>arr->SIZE || index<0)
    {
        return NULL;
    }
    
       

        else{

            if ((arr->pelement)[index]==NULL)
            {
                return NULL;
            }
            else{
            
           return  arr->copyfunc((arr->pelement)[index]);
            
            }
        }
        
}



int GetAdptArraySize(PAdptArray arr){

        if (arr!=NULL)
        {
           return arr->SIZE;
        }
        else{
            return -1;
        }
        
} 




void PrintDB(PAdptArray arr){

    for (int i = 0; i <arr->SIZE; i++)
    {
        if (((arr->pelement)[i] != NULL))
        {
           
            arr->printfunc(((arr->pelement)[i]));
            

        }
        
    }
    
}





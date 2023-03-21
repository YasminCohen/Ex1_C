#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_ 
{
	int SizeOfArr;
	PElement* ArrayOfPElement;
	DEL_FUNC deleteFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC deleteFunc,PRINT_FUNC printFunc) 
{
	 PAdptArray pArray = (PAdptArray)malloc(sizeof(AdptArray));
     if (pArray !=NULL){
        pArray->SizeOfArr = 0;
        pArray->ArrayOfPElement = NULL;
        pArray->deleteFunc = deleteFunc;
        pArray->copyFunc = copyFunc;
        pArray->printFunc = printFunc;
    }
	return pArray;
}


Result SetAdptArrayAt(PAdptArray pArray, int idx, PElement pNew)
{
    PElement* newArrayOfPElement = NULL;
    if (pArray == NULL || pNew == NULL || idx < 0) {
        return FAIL;
    }

    if (pArray->SizeOfArr <= idx) {
  
        newArrayOfPElement = (PElement*)calloc((idx + 1), sizeof(PElement));
        if (newArrayOfPElement == NULL)
            return FAIL;
        memcpy(newArrayOfPElement, pArray->ArrayOfPElement, (pArray->SizeOfArr) * sizeof(PElement));
        free(pArray->ArrayOfPElement);
        pArray->ArrayOfPElement = newArrayOfPElement;
    }

    if (pArray->deleteFunc != NULL && pArray->ArrayOfPElement[idx] != NULL) {
        pArray->deleteFunc(pArray->ArrayOfPElement[idx]);
    }

    (pArray->ArrayOfPElement)[idx] = pArray->copyFunc(pNew);


    if (idx < pArray->SizeOfArr) {
        pArray->SizeOfArr = pArray->SizeOfArr;
    } else {
        pArray->SizeOfArr = idx + 1;
    }

    return SUCCESS;
}



void DeleteAdptArray(PAdptArray pArray)
{
    int size = pArray->SizeOfArr;
	if (pArray != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            if (pArray->ArrayOfPElement[i] != NULL) {
                PElement del = pArray->ArrayOfPElement[i];
                pArray->deleteFunc(del);
            }
        }
        free(pArray->ArrayOfPElement);
        free(pArray);
    }
}



PElement GetAdptArrayAt(PAdptArray pAdptArray, int ID)
{
    if(ID >= 0 && pAdptArray->ArrayOfPElement[ID]!=NULL)
    {
        return  pAdptArray->copyFunc(pAdptArray->ArrayOfPElement[ID]);   
    }return NULL;
}


int GetAdptArraySize(PAdptArray pAdptArray) 
{
    if(pAdptArray!=NULL){
        return pAdptArray->SizeOfArr;
    }
    return -1;
}

void PrintDB(PAdptArray pAdptArray) 
{
    int i;

    for (i = 0; i < pAdptArray->SizeOfArr; i++)
    {
    if (pAdptArray->ArrayOfPElement[i]!=NULL)

        pAdptArray->printFunc(pAdptArray->ArrayOfPElement[i]);
    }
}


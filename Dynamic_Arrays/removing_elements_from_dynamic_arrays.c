/*
 * removing_elements_from_dynamic_arrays.c
 *
 *  Created on: Apr 17, 2015
 *  Author: Nick Pershin
 *
 *  Last edited on: Apr 18, 2015
 *  Editor: Nick Pershin
 *
 * 
 * TO BUILD: gcc -std=c99 -I../.. -o removing_elements_from_dynamic_arrays removing_elements_from_dynamic_arrays.c
 *
 * TO RUN: ./removing_elements_from_dynamic_arrays
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


int remove_element(int** array, unsigned int* sizeOfArray, unsigned int indexToRemove)
{
    if(indexToRemove >= *sizeOfArray) {
        printf("OUT OF BOUNDS? Oh no...\n");
        return -1;
    }

    int* temp = malloc((*sizeOfArray - 1) * sizeof(int));// allocate an array with a size 1 less than the current one

    memmove(
            temp,
            *array,
            (indexToRemove+1) * sizeof(int));// copy everything BEFORE the index

    memmove(
            temp+indexToRemove,
            (*array)+(indexToRemove+1),
            (*sizeOfArray - indexToRemove) * sizeof(int));// copy everything AFTER the index


    free (*array);
    *array = temp;
    *sizeOfArray -= 1;

    return 0;
}


int main()
{
    double start, end;
    unsigned int lenght = 20;
    // allocate an array
    int* test = malloc(lenght * sizeof(int*));
    // fill the array with integers
    for (int i = 0; i < lenght; ++i) {
        (test[i]) = i;
    }

    printf("\ttest[14] = %d, lenght = %d\n", test[14], lenght);
    printf("\tBegin processing. Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\tremoving test[14]...\n");
    
    start = clock();
    remove_element(&test, &lenght, 14);
    end = clock();

    printf("\tProcessing done.  Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");    
    printf("\ttest[14] = %d, lenght = %d\n", test[14], lenght);
    printf("\tOne element was removed from array in %.6lf sec\n\n", (end-start)/CLOCKS_PER_SEC);



    printf("\ttest[0] = %d, lenght = %d\n", test[0], lenght);
    printf("\tBegin processing. Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\tremoving test[0]...\n");
    
    start = clock();
    remove_element(&test, &lenght, 0);
    end = clock();

    printf("\tProcessing done.  Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");    
    printf("\ttest[0] = %d, lenght = %d\n", test[0], lenght);
    printf("\tFIRST element was removed from array in %.6lf sec\n\n", (end-start)/CLOCKS_PER_SEC);



    printf("\ttest[%d] = %d, lenght = %d\n", lenght-1, test[lenght-1], lenght);
    printf("\tBegin processing. Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\tremoving test[%d]...\n", lenght-1);
    
    start = clock();
    remove_element(&test, &lenght, lenght-1);
    end = clock();

    printf("\tProcessing done.  Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");    
    printf("\ttest[%d] = %d, lenght = %d\n", lenght-1, test[lenght-1], lenght);
    printf("\tLAST element was removed from array in %.6lf sec\n\n", (end-start)/CLOCKS_PER_SEC);


// TRY to go out of array bounds (and make Segmentation fault: 11)
    printf("\ttest[17] = %d, lenght = %d\n", test[17], lenght);
    printf("\tBegin processing. Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\tremoving test[17]...\n");
    
    start = clock();
    remove_element(&test, &lenght, 17);
    end = clock();

    printf("\tProcessing done.  Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\ttest[17] = %d, lenght = %d\n", test[17], lenght);
    printf("\ttest[17] element was removed from array in %.6lf sec\n\n", (end-start)/CLOCKS_PER_SEC);



// TRY to go out of array bounds (and make Segmentation fault: 11)
    printf("\ttest[-7] = %d, lenght = %d\n", test[-7], lenght);
    printf("\tBegin processing. Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\tremoving test[-7]...\n");
    
    start = clock();
    remove_element(&test, &lenght, -7);
    end = clock();

    printf("\tProcessing done.  Array is currently: ");
    for (int i = 0; i < lenght; ++i) {
        printf("%d ", test[i]);
    }
    printf("\n");
    printf("\ttest[-7] = %d, lenght = %d\n", test[-7], lenght);
    printf("\ttest[-7] element was removed from array in %.6lf sec\n\n", (end-start)/CLOCKS_PER_SEC);
    

    return 0;
}

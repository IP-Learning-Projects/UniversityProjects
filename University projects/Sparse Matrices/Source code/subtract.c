///\file subtract.c
///\brief Function subtract is used to subtract a matrix form another
///Created by Preda Iulian
#include "functions.h"
///\fn int subtr(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3])
///\brief subtract a matrix form another
///\param len1 the lengths of the first matrix after compression
///\param mat1[1001000][3] represents the first matrix
///\param len2 the lengths of the second matrix after compression
///\param mat2[1001000][3] represents the second matrix


int subtr(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3]){
    ///this is basically multiplying one matrix with -1 and then adding them
    if (subtr1 == 1){
        intMult(len2, mat2, -1);
        isAdded = 1;
        resLen = add(len1, mat1, len2, mat2, resMat);
        intMult(len2, mat2, -1);
    }else{
        intMult(len1, mat1, -1);
        isAdded = 1;
        resLen = add(len1, mat1, len2, mat2, resMat);
        intMult(len1, mat1, -1);
    }
    return resLen;
}

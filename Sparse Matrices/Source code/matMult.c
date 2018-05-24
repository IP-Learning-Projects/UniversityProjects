///\file matMult.c
///\brief Function matMult is used to multiply the 2 matrices
///Created by Preda Iulian
#include "functions.h"
///\fn void matMult(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int &resLen, int resMat[1001000][3])
///\brief  multiply the 2 matrices
///\param len1 the lengths of the first matrix after compression
///\param mat1[1001000][3] represents the first matrix
///\param len2 the lengths of the second matrix after compression
///\param mat2[1001000][3] represents the second matrix
///\param resLen represents the length of the resulting matrix
///\param resMat[1001000][3] represents the resulting matrix
///\param noRows1 represents the number of rows in the first matrix
///\param noRows2 represents the number of rows in the second matrix
///\param noCols1 represents the number of columns in the first matrix
///\param noCols2 represents the number of columns in the second matrix

int matMult(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3]){
    ///the first thing we need to do is to check that the 2 matrices have
    ///sizes that allow multiplication(noCols1 = noRows2)
    int row1,row2,col,it1,it2;
    if( noCols1 != noRows2 ){
        printf("Sorry, but you cannot multiply the matrices as they do not have corresponding sizes");
        isMulted = 0;
        return 0;
    }
    else{
        ///now we need to determine the size of the resulting matrix
        for( row1 = 1; row1 <= noRows1; row1 ++){
            for( row2 = 1; row2 <= noRows2; row2 ++){
                int sum = 0;
                ///we compute the value of the current element
                for( col = 1; col <= noCols1; col ++){
                    for( it1 = 1; it1 <= len1; it1 ++){
                        ///now we need to check if the current element, given by
                        ///row1 and col is in the first matrix
                        if(row1 == mat1[it1][0] && col == mat1[it1][1]){
                            for( it2 = 1; it2 <= len2; it2 ++){
                                ///now we check if it is in the second matrix
                                ///given by row2 and col
                                if(col == mat2[it2][0] && row2 == mat2[it2][1])
                                    ///we add to the current sum the product of
                                    ///the values of the 2 elements
                                    sum += mat1[it1][2] * mat2[it2][2];
                            }
                        }
                    }
                }
                ///we add 1 to the size of the result matrix if the sum is != 0
                if(sum != 0){
                    resLen ++;
                    resMat[resLen][0] = row1;
                    resMat[resLen][1] = row2;
                    resMat[resLen][2] = sum;
                }
            }
        }



        ///finally, we compute the actual multiplication
        return resLen;
    }
}

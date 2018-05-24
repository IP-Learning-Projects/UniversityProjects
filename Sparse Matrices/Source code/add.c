///\file add.c
///\brief Function add is used to sum the 2 matrices
///Created by Preda Iulian

#include "functions.h"
///\fn int add(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3])
///\param it1 and \param it2 are iterators
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

int add(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3]){
    ///the first thing we need to do is to check that the 2 matrices have the
    ///same size, as otherwise we cannot add them
    if( noRows1 != noRows2 || noCols1 != noCols2 ){
        printf("Sorry, but you cannot add the matrices as they do not have the same sizes");
        isAdded = 0;
        return 0;
    }
    ///now we need to calculate the resulting matrix
    ///first we need to know its size, as it is the sum of the sizes of
    ///the other 2 matrices - number of common elements
    else{
        resLen = len1 + len2;
        int it1, it2; //the iterators for the matrices
        it1 = it2 = 1;
        while(it1 <= len1 || it2 <= len2){
            ///first we check if they are on the same row
            if(mat1[it1][0] < mat2[it2][0])
                it1 ++;
            else if(mat1[it1][0] > mat2[it2][0])
                it2 ++;
            else{
                ///now we check if they are on the same column
                if(mat1[it1][1] < mat2[it2][1])
                    it1 ++;
                else if(mat1[it1][1] > mat2[it2][1])
                    it2 ++;
                else{
                    ///we know that we have 2 elements located at the same position
                    ///now we have to check if their sum if 0 in order to decrease
                    ///the number of elements by 2(as we need to exclude this
                    ///element from the new matrix), or not, to decrease it by 1
                    if(mat1[it1][2] + mat2[it2][2] == 0)
                        resLen -= 2;
                    else
                        resLen --;
                    it1 ++;
                    it2 ++;
                }
            }
        }
        ///now we do the addition itself
        it1 = it2 = 1;
        int resIt = 1; //the iterator tfor the resulting matrix
        while(it1 <= len1 || it2 <= len2){
             ///first we check if the elements of the original matrices are on
             ///the same row and if not we just add the current element to the
             ///result matrix
            if(mat1[it1][0] < mat2[it2][0]){
                resMat[resIt][0] = mat1[it1][0];
                resMat[resIt][1] = mat1[it1][1];
                resMat[resIt][2] = mat1[it1][2];
                it1 ++;
                resIt ++;
            }
            else if(mat1[it1][0] > mat2[it2][0]){
                resMat[resIt][0] = mat2[it2][0];
                resMat[resIt][1] = mat2[it2][1];
                resMat[resIt][2] = mat2[it2][2];
                it2 ++;
                resIt ++;
            }
            else{
                ///now we check if they are on the same column
                if(mat1[it1][1] < mat2[it2][1]){
                    resMat[resIt][0] = mat1[it1][0];
                    resMat[resIt][1] = mat1[it1][1];
                    resMat[resIt][2] = mat1[it1][2];
                    it1 ++;
                    resIt ++;
                }
                else if(mat1[it1][1] > mat2[it2][1]){
                    resMat[resIt][0] = mat2[it2][0];
                    resMat[resIt][1] = mat2[it2][1];
                    resMat[resIt][2] = mat2[it2][2];
                    it2 ++;
                    resIt ++;
                }
                else{
                    ///as they are located as the same position, we add to the
                    ///resulting matrix their sum
                    if(mat1[it1][2] + mat2[it2][2] == 0);
                        ///if it is 0 we do not add anything
                    else{
                        resMat[resIt][0] = mat1[it1][0];
                        resMat[resIt][1] = mat1[it1][1];
                        resMat[resIt][2] = mat1[it1][2] + mat2[it2][2];
                        resIt ++;
                    }
                    it1 ++;
                    it2 ++;
                }
            }
        }
        return resLen;
    }
}

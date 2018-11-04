///\file main.c
///\brief Sparse Matrices
///Created by Preda Iulian

#include "functions.h"

int main(){
     int i,it;
    ///\fn int main()
    ///\brief main function
    /// This function reads the input data and calls the functions
    ///readMat, add , matMult, intMult,scalarMult,subtract  from  functions.h
    ///first we need to read the matrices
    ///for this I have chosen to read the whole matrices as input
    ///also, we do not want to store the whole matrices due to memory restraints
    ///therefore, we will only read the current element and compress it at the
    ///same time

    printf("Insert the number of rows and columns for the first matrix:\n");
    scanf("%d%d", &noRows1, &noCols1);

    ///the parameters are the compressed matrix, its length and the number
    ///of rows and columns of the original matrix
    len1 = readMatrix(mat1, noRows1, noCols1);
    printf("Insert the number of rows and columns for the second matrix:\n");
    scanf("%d%d", &noRows2, &noCols2);
    len2 = readMatrix(mat2, noRows2, noCols2);
    printf("\n");

    ///now let us print the compressed matrices to check if the compression
    ///is done correctly
    printf("The compressed matrices are:\n");
    for( i = 1; i <= len1; i ++){
        printf("%d %d %d\n", mat1[i][0], mat1[i][1], mat1[i][2]);
    }
    printf("\n");

    for( i = 1; i <= len2; i ++){
        printf("%d %d %d\n", mat2[i][0], mat2[i][1], mat2[i][2]);
    }
    printf("\n");

    ///now we have to do the addition
    ///\var isAdded has 1 if the addition was completed or 0 otherwise
    isAdded = 1;
    resLen = 0;
    ///the parameters are the 2 compressed matrices, their respective length
    ///and the result matrix with its size
    resLen = add(len1, mat1, len2, mat2, resMat);
    ///now let us print the result of the addition, but as a regular matrix
    ///to make it simpler to look at
    printf("The result of the addition is:\n");
    if(isAdded){
        printMat(resMat);
    }
    printf("\n");

    ///now we have to do the multiplication of 2 sparse matrices
    ///however, before getting to that, we have to reset resMat and resLen
    for( i = 1; i <= resLen; i ++){
        resMat[i][0] = resMat[i][1] = resMat[i][2] = 0;
    }
    resLen = 0;
    ///now that this is done, we can move forward to the multiplication part
    ///\var isMulted is 1 if the multiplication was completed or 0 otherwise
    isMulted = 1;
    ///it has the same parameters as the add function
    resLen = matMult(len1, mat1, len2, mat2, resMat);
    ///now we print the resulting matrix as an actual matrix
    printf("The result of the multiplication of the 2 matrices is:\n");
    if(isMulted){
        printMat(resMat);
    }
    printf("\n");

    ///now we have subtraction
    ///so its parameters are the same as addition
    printf("choose which matrix to be subtracted form which");
    printf("\n1: The second one from the first one");
    printf("\n2: The first one form the second one\n");
    scanf("%d",&subtr1);
    printf("The result of the subtraction is:\n");
    resLen = subtr(len1, mat1, len2, mat2, resMat);
    ///now let us print the result of the addition, but as a regular matrix
    ///to make it simpler to look at
    if(isAdded){
        printMat(resMat);
    }
    printf("\n");

    ///multiplication with an integer \var fact
    ///the parameters are: the compressed matrix, its length and the integer it is
    ///multiplied by
    printf("Insert the integer:\n");
    scanf("%d", &fact);
    printf("Choose which matrix to be multiplied with the integer(1/2?)\n");
    scanf("%d",&it);
    if(it == 1){
        intMult(len1, mat1, fact);
        printMat(mat1); ///now we print the resulting matrix as an actual matrix
    }else{
        intMult(len2, mat2, fact);
        printMat(mat2); ///now we print the resulting matrix as an actual matrix
    }
    printf("\n");
    return 0;
}

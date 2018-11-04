///\file function.h
///\brief The library of functions
///Created by Preda Iulian
#include<stdio.h>


int noRows1,noCols1,noRows2,noCols2; //the sizes of the 2 matrices
int mat1[1001000][3],mat2[1001000][3]; //the 2 matrices after they are
//compressed into the following pattern: row, column, value
int resMat[1001000][3]; //the resulting matrix
int resLen; //the length of the resulting matrix
int len1,len2; //the lengths of the 2 matrices after compression
int isAdded,isMulted; //to check that matrix add or mult has taken place
int fact; //the integer by which a matrix is multiplied
int subtr1;//the integer used for choosing how to subtract matrices

int readMatrix(int mat[1001000][3], int noRows, int noCols);
int add(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3]);
int matMult(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3]);
void intMult(int len, int mat[1001000][3], int fact);
int subtr(int len1, int mat1[1001000][3], int len2, int mat2[1001000][3], int resMat[1001000][3]);
void printMat(int Mat[1001000][3]);

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

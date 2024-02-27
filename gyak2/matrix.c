#include "matrix.h"

#include <stdio.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;
    for (i = 0; i< 3; i++)
    {
        for (j = 0; j < 3; ++j)
        {
            if (i == j) matrix[i][j] = 1.0f;
            else matrix[i][j] = 0.0f;
        }
    }
}

void scalar_product(float scalar, float matrix[3][3])
{
    int i;
    int j;
    for (i = 0; i< 3; i++)
    {
        for (j = 0; j < 3; ++j)
        {
            matrix[i][j] *= scalar;
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;
    for (i = 0; i< 3; i++)
    {
        for (j = 0; j < 3; ++j)
        {
            c[i][j] =(a[0][i]*b[j][0]) + (a[1][i]*b[j][1]) + (a[2][i]*b[j][2]);
        }
    }
}

void transform_point(float matrix[3][3], float point[3]);
{
    int i;
    int j;
    for (i = 0; i< 3; i++)
    {
        point[i] = 0;
        for (j = 0; j < 3; ++j)
        {
            point[i] = point[j]*matrix[j][i];
        }
    }
}
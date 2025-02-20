#ifndef MATRIX_H
#define MATRIX_H

void init_zero_matrix(float matrix[3][3]);

void print_matrix(const float matrix[3][3]);

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void init_identity_matrix(float matrix[3][3]);

void scalar_product(float scalar, float matrix[3][3]);

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void transform_point(float matrix[3][3], float point[3]);

#endif
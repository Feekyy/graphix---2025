#include "matrix.h"

int main(int argc, char* argv[])
{
	float a[3][3] = 
    {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };

	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);
    
    add_matrices(a, b, c);

    print_matrix(c);

    init_identity_matrix(a);
    print_matrix(a);

    scalar_product(3, b);
    print_matrix(b);

    multiply_matrices(a, b, c);
    print_matrix(c);

    float point[3] = {3.0f, 5.0f, 3.0f};
    transform_point(a, point);
    for (int i = 0; i < 3; i++)
    {
        printf("%f ",point[i]);
    }

	return 0;
}
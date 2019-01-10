#include <stdio.h>
#include <assert.h>
#include "libvector.h"

void vector_initialization_test()
{
	vector_t vector = NULL;

	puts("==== create_vector test ====");
	vector = create_vector(4);

	assert(vector != NULL);
	assert(vector->dimension == 4);
	for(unsigned int i = 0; i < vector->dimension; i++)
		assert(vector->components[i] == 0.0);

	puts("create_vector test passed\n\n");

	puts("==== destroy_vector test ====");
	destroy_vector(&vector);
	assert(vector == NULL);
	puts("destroy_vector test passed\n\n");
}

void vector_print_test()
{
	vector_t vector = create_vector(4);

	puts("==== printf_vector test ====");
	printf_vector(vector, "%.1f\t");
	puts("printf_vector test passed\n\n");

	puts("==== print_vector test ====");
	print_vector(vector);
	puts("print_vector test passed\n\n");

	destroy_vector(&vector);
}

void vector_setup_test()
{
	vector_t vector1 = create_vector(4);
	vector_t vector2 = create_vector(4);
	vector_t vector3 = NULL;

	puts("==== fill_vector test ====");
	fill_vector(vector1, 30.0);

	for(unsigned int i = 0; i < vector1->dimension; i++)
		assert(vector1->components[i] == 30.0);

	puts("fill_vector test passed\n\n");

	puts("==== copy_vector test ====");
	fill_vector(vector1, 3.0);
	copy_vector(vector2, vector1);

	for(unsigned int i = 0; i < vector2->dimension; i++)
		assert(vector2->components[i] == 3.0);

	puts("copy_vector test passed\n\n");

	puts("==== string_to_vector test ====");
	vector3 = string_to_vector("30.0,3.5,4.2");

	assert(vector3->components[0] == 30.0 && vector3->components[1] == 3.5 && vector3->components[2] == 4.2);

	puts("string_to_vector test passed\n\n");

	destroy_vector(&vector1);
	destroy_vector(&vector2);
	destroy_vector(&vector3);
}

void vector_operations_test()
{
	vector_t vector1 = create_vector(3);
	vector_t vector2 = create_vector(3);
	vector_t vector3 = NULL, vector4 = NULL;

	puts("==== sum_vector test ====");
	fill_vector(vector1, 1.0);
	fill_vector(vector2, 1.0);
	vector3 = sum_vector(vector1, vector2);

	for(unsigned int i = 0; i < vector3->dimension; i++)
		assert(vector3->components[i] == 2.0);

	puts("sum_vector test passed\n\n");

	puts("==== dot_product test ====");
	fill_vector(vector1, 1.0);
	fill_vector(vector2, 2.0);

	assert(dot_product(vector1, vector2) == 6.0);

	puts("dot_product test passed\n\n");

	puts("==== cross_product test ====");
	fill_vector(vector1, 1.0);
	fill_vector(vector2, 2.0);
	vector4 = cross_product(vector1, vector2);
	for(unsigned int i = 0; i < vector4->dimension; i++)
		assert(vector4->components[i] == 0.0);

	puts("cross_product test passed\n\n");

	puts("==== vector_scalar_multiplication test ====");
	fill_vector(vector1, 3.0);
	vector_scalar_multiplication(vector1, 10.0);

	for(unsigned int i = 0; i < vector1->dimension; i++)
		assert(vector1->components[i] == 30.0);

	puts("vector_scalar_multiplication test passed\n\n");

	puts("==== vector_magnitude test ====");
	fill_vector(vector1, 0.0);
	vector1->components[2] = 1.0;

	assert(vector_magnitude(vector1) == 1.0);

	puts("vector_magnitude test passed\n\n");

	puts("==== vector_normalize test ====");
	fill_vector(vector1, 2.0);
	vector_normalize(vector1);

	assert(vector_magnitude(vector1) == 1.0);

	puts("vector_normalize test passed\n\n");

	destroy_vector(&vector1);
	destroy_vector(&vector2);
	destroy_vector(&vector3);
	destroy_vector(&vector4);
}

int main()
{
	vector_initialization_test();
	vector_print_test();
	vector_setup_test();
	vector_operations_test();

	return 0;
}

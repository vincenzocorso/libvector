#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libvector.h"

/* Create a zero vector and return pointer to it */
vector_t create_vector(const unsigned int dimension)
{
	if(!dimension)
		return NULL;

	vector_t vector = (vector_t)malloc(sizeof(struct Vector));
	vector->dimension = dimension;
	vector->components = (double *)calloc(dimension, sizeof(double));

	return vector;
}

/* Delete a vector and free memory */
void destroy_vector(vector_t *vector)
{
	if(*vector == NULL)
		return;

	free((*vector)->components);
	free(*vector);
	*vector = NULL;
}

/* Print the components of a vector using custom format specifier */
void printf_vector(const vector_t vector, const char *format)
{
	if(vector == NULL)
		return;

	for(unsigned int i = 0; i < vector->dimension; i++)
		printf(format, vector->components[i]);

	puts("");
}

/* Copy a vector */
vector_t copy_vector(const vector_t vector)
{
	if(vector == NULL)
		return NULL;

	vector_t result = create_vector(vector->dimension);

	for(unsigned int i = 0; i < result->dimension; i++)
		result->components[i] = vector->components[i];

	return result;
}

/* Create a new vector using a string */
vector_t string_to_vector(const char string[])
{
	size_t lenght = strlen(string);
	if(!lenght)
		return NULL;

	unsigned int dimension = 0;
	for(unsigned int i = 0; i < lenght; i++)
		if(string[i] == ',')
			dimension++;

	vector_t vector = create_vector(dimension + 1);
	
	char copy[lenght + 1];
	strcpy(copy, string);
	char *token = strtok(copy, ",");
	for(unsigned int i = 0; token != NULL; i++)
	{
		vector->components[i] = atof(token);
		token = strtok(NULL, ",");
	}

	return vector;
}

/* Fill all components of a vector with a new value */
void fill_vector(const vector_t vector, const double new_value)
{
	if(vector == NULL)
		return;

	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] = new_value;
}

/* Increase vector dimension and push a new element in the selected position */
void vector_push(const vector_t vector, const double new_value, const unsigned int position)
{
	if(vector == NULL || position > vector->dimension)
		return;

	vector->components = (double *)realloc(vector->components, (vector->dimension + 1) * sizeof(double));
	memmove(vector->components + position + 1, vector->components + position, (vector->dimension - position) * sizeof(double));
	vector->components[position] = new_value;
	(vector->dimension)++;
}

/* Decrease vector dimension and pop a element from the selected position */
void vector_pop(const vector_t vector, const unsigned int position)
{
	if(vector == NULL || position > vector->dimension - 1)
		return;

	memmove(vector->components + position, vector->components + position + 1, (vector->dimension - position - 1) * sizeof(double));
	vector->components = (double *)realloc(vector->components, (vector->dimension - 1) * sizeof(double));
	(vector->dimension)--;
}

/* Return the sum of two vectors */
vector_t sum_vector(const vector_t vector1, const vector_t vector2)
{
	if(vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension)
		return NULL;

	vector_t vector = create_vector(vector1->dimension);
	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] = vector1->components[i] + vector2->components[i];

	return vector;
}

/* Calculate the dot product between two vectors */
double dot_product(const vector_t vector1, const vector_t vector2)
{
	// Return error ?
	/*if(vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension)
		return;*/

	double sum = 0.0;
	for(unsigned int i = 0; i < vector1->dimension; i++)
		sum += vector1->components[i] * vector2->components[i];

	return sum;
}

/* Calculate the cross product between two vectors */
vector_t cross_product(const vector_t vector1, const vector_t vector2)
{
	if(vector1 == NULL || vector2 == NULL || vector1->dimension != 3 || vector2->dimension != 3) // cross_product is defined in R^3
		return NULL;

	vector_t vector = create_vector(3);
	vector->components[0] = vector1->components[1] * vector2->components[2] - vector1->components[2] * vector2->components[1];
	vector->components[1] = vector1->components[2] * vector2->components[0] - vector1->components[0] * vector2->components[2];
	vector->components[2] = vector1->components[0] * vector2->components[1] - vector1->components[1] * vector2->components[0];

	return vector;
}

/* Calculate the product beetween a vector and a scalar */
void vector_scalar_multiplication(const vector_t vector, const double scalar)
{
	if(vector == NULL)
		return;

	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] *= scalar;
}

/* Add a scalar to vector components */
void vector_add_scalar(const vector_t vector, const double scalar)
{
	if(vector == NULL)
		return;

	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] += scalar;
}

/* Calculate the absolute value of vector components */
void vector_abs(const vector_t vector)
{
	if(vector == NULL)
		return;

	for(unsigned int i = 0; i < vector->dimension; i++)
		if(vector->components[i] < 0)
			vector->components[i] *= -1;
}

/* Calculate the magnitude of a vector */
double vector_magnitude(const vector_t vector)
{
	// return error ?
	/*if(vector == NULL)
		return;*/

	return sqrt(dot_product(vector, vector));
}

/* Calculate the normalized vector */
void vector_normalize(const vector_t vector)
{
	if(vector == NULL)
		return;

	const double magnitude = vector_magnitude(vector);
	
	if(magnitude)
		for(unsigned int i = 0; i < vector->dimension; i++)
			vector->components[i] /= magnitude;
}

/* Calculate the angle in radians between two vectors */
double vector_angle(const vector_t vector1, const vector_t vector2)
{
	// Return error ?
	/*if(vector1 == NULL || vector2 == NULL)
		return;*/

	double dp = fabs(dot_product(vector1, vector2));
	double lenght1 = vector_magnitude(vector1);
	double lenght2 = vector_magnitude(vector2);
	return acos(dp / (lenght1 * lenght2));
}

/* Return the max component index from a vector */
int max_vector_component(const vector_t vector)
{
	if(vector == NULL)
		return -1;

	unsigned int max_index = 0;
	for(unsigned int i = 1; i < vector->dimension; i++)
		if(vector->components[i] > vector->components[max_index])
			max_index = i;

	return max_index;
}

/* Return the min component index from a vector */
int min_vector_component(const vector_t vector)
{
	if(vector == NULL)
		return -1;

	unsigned int min_index = 0;
	for(unsigned int i = 1; i < vector->dimension; i++)
		if(vector->components[i] < vector->components[min_index])
			min_index = i;

	return min_index;
}

/* Check if a vector is a zero vector */
int is_zero_vector(const vector_t vector)
{
	if(vector == NULL)
		return 0;

	for(unsigned int i = 0; i < vector->dimension; i++)
		if(vector->components[i] != 0)
			return 0;

	return 1;
}

/* Check if two vectors are parallel */
int is_parallel_to(const vector_t vector1, const vector_t vector2)
{
	if(vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension)
		return 0;

	vector_t vector = cross_product(vector1, vector2);
	int result = is_zero_vector(vector);
	destroy_vector(&vector);

	return result;
}

/* Check if two vectors are perpendicular */
int is_perpendicular_to(const vector_t vector1, const vector_t vector2)
{
	if(vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension)
		return 0;

	return !dot_product(vector1, vector2);	
}

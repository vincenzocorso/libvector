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
	for(unsigned int i = 0; i < vector->dimension; i++)
		printf(format, vector->components[i]);

	puts("");
}

/* Copy a vector */
void copy_vector(const vector_t vector_dest, const vector_t vector_src)
{
	if(vector_dest == NULL || vector_src == NULL)
		return;

	for(unsigned int i = 0; i < vector_dest->dimension; i++)
		vector_dest->components[i] = vector_src->components[i];
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
	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] = new_value;
}

/* Return the sum of two vectors */
vector_t sum_vector(const vector_t vector1, const vector_t vector2)
{
	if(vector1->dimension != vector2->dimension)
		return NULL;

	vector_t vector = create_vector(vector1->dimension);
	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] = vector1->components[i] + vector2->components[i];

	return vector;
}

/* Calculate the dot product between two vectors */
double dot_product(const vector_t vector1, const vector_t vector2)
{
	// Check vector1 and vector2 dimension?
	double sum = 0.0;
	for(unsigned int i = 0; i < vector1->dimension; i++)
		sum += vector1->components[i] * vector2->components[i];

	return sum;
}

/* Calculate the cross product between two vectors */
vector_t cross_product(const vector_t vector1, const vector_t vector2)
{
	if(vector1->dimension != 3 || vector2->dimension != 3) // cross_product is defined in R^3
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
	for(unsigned int i = 0; i < vector->dimension; i++)
		vector->components[i] *= scalar;
}

/* Calculate the magnitude of a vector */
double vector_magnitude(const vector_t vector)
{
	return sqrt(dot_product(vector, vector));
}

/* Calculate the normalized vector */
void vector_normalize(const vector_t vector)
{
	const double magnitude = vector_magnitude(vector);
	
	if(magnitude)
		for(unsigned int i = 0; i < vector->dimension; i++)
			vector->components[i] /= magnitude;
}

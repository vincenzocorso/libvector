#ifndef LIBVECTOR_H
	#define LIBVECTOR_H

/* Defines */
#define DEFAULT_VECTOR_FORMAT_SPECIFIER		"%.2f "

/* Structures */
struct Vector
{
	unsigned int dimension;
	double *components;
};
typedef struct Vector *vector_t;

/* Macros */
/* Print the components of a vector using default format specifier */
#define print_vector(vector)	printf_vector(vector,DEFAULT_VECTOR_FORMAT_SPECIFIER)

/* Functions */
/* Create a zero vector and return pointer to it */
vector_t create_vector(const unsigned int dimension);

/* Delete a vector and free memory */
void destroy_vector(vector_t *vector);

/* Print the components of a vector using custom format specifier */
void printf_vector(const vector_t vector, const char *format);

/* Copy a vector */
vector_t copy_vector(const vector_t vector);

/* Create a new vector using a string */
vector_t string_to_vector(const char string[]);

/* Fill all components of a vector with a new value */
void fill_vector(const vector_t vector, const double new_value);

/* Return the sum of two vectors */
vector_t sum_vector(const vector_t vector1, const vector_t vector2);

/* Calculate the dot product between two vectors */
double dot_product(const vector_t vector1, const vector_t vector2);

/* Calculate the cross product between two vectors */
vector_t cross_product(const vector_t vector1, const vector_t vector2);

/* Calculate the product beetween a vector and a scalar */
void vector_scalar_multiplication(const vector_t vector, const double scalar);

/* Calculate the magnitude of a vector */
double vector_magnitude(const vector_t vector);

/* Calculate the normalized vector */
void vector_normalize(const vector_t vector);

#endif /* LIBVECTOR_H */
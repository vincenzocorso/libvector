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
vector_t create_zero_vector(const unsigned int dimension);

/* Create a vector and return pointer to it */
vector_t create_vector(const unsigned int dimension, const double components[]);

/* Delete a vector and free memory */
void destroy_vector(vector_t *vector);

/* Delete the vectors passed by argument */
void destroy_vectors(int numargs, ...);

/* Print the components of a vector using custom format specifier */
void printf_vector(const vector_t vector, const char *format);

/* Copy a vector */
vector_t copy_vector(const vector_t vector);

/* Fill all components of a vector with a new value */
void fill_vector(const vector_t vector, const double new_value);

/* Increase vector dimension and push a new element in the selected position */
void vector_push(const vector_t vector, const double new_value, const unsigned int position);

/* Decrease vector dimension and pop a element from the selected position */
void vector_pop(const vector_t vector, const unsigned int position);

/* Return the sum of two vectors */
vector_t sum_vector(const vector_t vector1, const vector_t vector2);

/* Calculate the dot product between two vectors */
double dot_product(const vector_t vector1, const vector_t vector2);

/* Calculate the cross product between two vectors */
vector_t cross_product(const vector_t vector1, const vector_t vector2);

/* Calculate the product beetween a vector and a scalar */
void vector_scalar_multiplication(const vector_t vector, const double scalar);

/* Add a scalar to vector components */
void vector_add_scalar(const vector_t vector, const double scalar);

/* Calculate the absolute value of vector components */
void vector_abs(const vector_t vector);

/* Calculate the magnitude of a vector */
double vector_magnitude(const vector_t vector);

/* Calculate the normalized vector */
void vector_normalize(const vector_t vector);

/* Calculate the angle in radians between two vectors */
double vector_angle(const vector_t vector1, const vector_t vector2);

/* Return the max component index from a vector */
int max_vector_component(const vector_t vector);

/* Return the min component index from a vector */
int min_vector_component(const vector_t vector);

/* Check if a vector is a zero vector */
int is_zero_vector(const vector_t vector);

/* Check if two vectors are parallel */
int is_parallel_to(const vector_t vector1, const vector_t vector2);

/* Check if two vectors are perpendicular */
int is_perpendicular_to(const vector_t vector1, const vector_t vector2);

#endif /* LIBVECTOR_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include "libvector.h"

// Define a struct for vectors
typedef struct {
    unsigned int dimension;
    double *components;
} Vector;

// Define a typedef for the struct
typedef Vector* vector_t;

// Function to create a zero vector
vector_t create_zero_vector(const unsigned int dimension) {
    if (dimension == 0) {
        return NULL;
    }

    vector_t vector = (vector_t)malloc(sizeof(Vector));
    vector->dimension = dimension;
    vector->components = (double *)calloc(dimension, sizeof(double));

    return vector;
}

// Function to create a vector from components
vector_t create_vector(const unsigned int dimension, const double components[]) {
    if (dimension == 0) {
        return NULL;
    }

    vector_t vector = create_zero_vector(dimension);
    memcpy(vector->components, components, dimension * sizeof(double));

    return vector;
}

// Function to destroy a vector
void destroy_vector(vector_t *vector) {
    if (*vector != NULL) {
        free((*vector)->components);
        free(*vector);
        *vector = NULL;
    }
}

// Function to destroy multiple vectors
void destroy_vectors(int numargs, ...) {
    va_list list;
    va_start(list, numargs);
    for (int i = 0; i < numargs; i++) {
        vector_t *arg = va_arg(list, vector_t *);
        destroy_vector(arg);
    }
    va_end(list);
}

// Function to print a vector with a custom format
void printf_vector(const vector_t vector, const char *format) {
    if (vector == NULL) {
        return;
    }

    for (unsigned int i = 0; i < vector->dimension; i++) {
        printf(format, vector->components[i]);
    }
    puts("");
}

// Function to create a copy of a vector
vector_t copy_vector(const vector_t vector) {
    if (vector == NULL) {
        return NULL;
    }

    vector_t result = create_zero_vector(vector->dimension);
    memcpy(result->components, vector->components, vector->dimension * sizeof(double));

    return result;
}

// Function to fill all components of a vector with a new value
void fill_vector(const vector_t vector, const double new_value) {
    if (vector == NULL) {
        return;
    }

    for (unsigned int i = 0; i < vector->dimension; i++) {
        vector->components[i] = new_value;
    }
}

// Function to push a new element at the specified position
void vector_push(vector_t vector, const double new_value, const unsigned int position) {
    if (vector == NULL || position > vector->dimension) {
        return;
    }

    vector->dimension++;
    vector->components = (double *)realloc(vector->components, vector->dimension * sizeof(double));

    memmove(vector->components + position + 1, vector->components + position, (vector->dimension - position - 1) * sizeof(double));
    vector->components[position] = new_value;
}

// Function to pop an element from the specified position
void vector_pop(vector_t vector, const unsigned int position) {
    if (vector == NULL || position >= vector->dimension) {
        return;
    }

    memmove(vector->components + position, vector->components + position + 1, (vector->dimension - position - 1) * sizeof(double));
    vector->dimension--;
    vector->components = (double *)realloc(vector->components, vector->dimension * sizeof(double));
}

// Function to return the sum of two vectors
vector_t sum_vector(const vector_t vector1, const vector_t vector2) {
    if (vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension) {
        return NULL;
    }

    vector_t vector = create_zero_vector(vector1->dimension);
    for (unsigned int i = 0; i < vector->dimension; i++) {
        vector->components[i] = vector1->components[i] + vector2->components[i];
    }

    return vector;
}

// Function to calculate the dot product between two vectors
double dot_product(const vector_t vector1, const vector_t vector2) {
    if (vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension) {
        return 0.0; // Consider returning a default value or indicating an error
    }

    double sum = 0.0;
    for (unsigned int i = 0; i < vector1->dimension; i++) {
        sum += vector1->components[i] * vector2->components[i];
    }

    return sum;
}

// Function to calculate the cross product between two vectors in R^3
vector_t cross_product(const vector_t vector1, const vector_t vector2) {
    if (vector1 == NULL || vector2 == NULL || vector1->dimension != 3 || vector2->dimension != 3) {
        return NULL;
    }

    vector_t vector = create_zero_vector(3);
    vector->components[0] = vector1->components[1] * vector2->components[2] - vector1->components[2] * vector2->components[1];
    vector->components[1] = vector1->components[2] * vector2->components[0] - vector1->components[0] * vector2->components[2];
    vector->components[2] = vector1->components[0] * vector2->components[1] - vector1->components[1] * vector2->components[0];

    return vector;
}

// Function to multiply a vector by a scalar
void vector_scalar_multiplication(vector_t vector, const double scalar) {
    if (vector == NULL) {
        return;
    }

    for (unsigned int i = 0; i < vector->dimension; i++) {
        vector->components[i] *= scalar;
    }
}

// Function to add a scalar to vector components
void vector_add_scalar(vector_t vector, const double scalar) {
    if (vector == NULL) {
        return;
    }

    for (unsigned int i = 0; i < vector->dimension; i++) {
        vector->components[i] += scalar;
    }
}

// Function to calculate the absolute value of vector components
void vector_abs(vector_t vector) {
    if (vector == NULL) {
        return;
    }

    for (unsigned int i = 0; i < vector->dimension; i++) {
        if (vector->components[i] < 0) {
            vector->components[i] *= -1;
        }
    }
}

// Function to calculate the magnitude of a vector
double vector_magnitude(const vector_t vector) {
    if (vector == NULL) {
        return 0.0; // Consider returning a default value or indicating an error
    }

    return sqrt(dot_product(vector, vector));
}

// Function to normalize a vector
void vector_normalize(vector_t vector) {
    if (vector == NULL) {
        return;
    }

    double magnitude = vector_magnitude(vector);
    if (magnitude != 0) {
        for (unsigned int i = 0; i < vector->dimension; i++) {
            vector->components[i] /= magnitude;
        }
    }
}

// Function to calculate the angle in radians between two vectors
double vector_angle(const vector_t vector1, const vector_t vector2) {
    if (vector1 == NULL || vector2 == NULL) {
        return 0.0; // Consider returning a default value or indicating an error
    }

    double dp = fabs(dot_product(vector1, vector2));
    double length1 = vector_magnitude(vector1);
    double length2 = vector_magnitude(vector2);

    return acos(dp / (length1 * length2));
}

// Function to return the index of the maximum component in a vector
int max_vector_component(const vector_t vector) {
    if (vector == NULL) {
        return -1; // Consider returning a default value or indicating an error
    }

    unsigned int max_index = 0;
    for (unsigned int i = 1; i < vector->dimension; i++) {
        if (vector->components[i] > vector->components[max_index]) {
            max_index = i;
        }
    }

    return max_index;
}

// Function to return the index of the minimum component in a vector
int min_vector_component(const vector_t vector) {
    if (vector == NULL) {
        return -1; // Consider returning a default value or indicating an error
    }

    unsigned int min_index = 0;
    for (unsigned int i = 1; i < vector->dimension; i++) {
        if (vector->components[i] < vector->components[min_index]) {
            min_index = i;
        }
    }

    return min_index;
}

// Function to check if a vector is a zero vector
int is_zero_vector(const vector_t vector) {
    if (vector == NULL) {
        return 0;
    }

    for (unsigned int i = 0; i < vector->dimension; i++) {
        if (vector->components[i] != 0) {
            return 0;
        }
    }

    return 1;
}

// Function to check if two vectors are parallel
int is_parallel_to(const vector_t vector1, const vector_t vector2) {
    if (vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension) {
        return 0;
    }

    vector_t cross = cross_product(vector1, vector2);
    int result = is_zero_vector(cross);
    destroy_vector(&cross);

    return result;
}

// Function to check if two vectors are perpendicular
int is_perpendicular_to(const vector_t vector1, const vector_t vector2) {
    if (vector1 == NULL || vector2 == NULL || vector1->dimension != vector2->dimension) {
        return 0;
    }

    return (dot_product(vector1, vector2) == 0);
}

# A simple C math vector library
[![Build Status](https://travis-ci.com/vincenzocorso/libvector.svg?token=gZvgq4ygyQjdGiqvUYN4&branch=master)](https://travis-ci.com/vincenzocorso/libvector) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/2e6db9f3220e4f2db81c25ec806e1f1a)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=vincenzocorso/libvector&amp;utm_campaign=Badge_Grade)

Libvector is a simple library that allows you to work with math vectors in <img src="https://latex.codecogs.com/gif.latex?\dpi{120}&space;\large&space;\mathbb{R}^{n}" /> 

Author: Vincenzo Corso <[vincenzocorso99@gmail.com](mailto:vincenzocorso99@gmail.com)>

License: MIT (see [LICENSE](https://github.com/vincenzocorso/libvector/blob/master/LICENSE)  for details)

## Installation
Download...

To do...

Include `libvector.h` header file at the top of the file:
```c
#include "libvector.h"
```

## Usage
It's very simple and intuitive. These are some examples of usage.

### Creating/Initialising new vectors
This library use a new type called `vector_t`. To create a new vector you can use `create_vector` specifying vector dimension. For example this code will create a vector in <img src="https://latex.codecogs.com/gif.latex?\dpi{120}&space;\large&space;\mathbb{R}^{3}" /> 
```c
vector_t my_vector = create_vector(3); // 3 is vector dimension (R^3)
// By default create_vector creates a null vector. To change components value use:
my_vector->components[0] = 4.4563; // Components goes from 0 to 2
my_vector->components[1] = 1;
my_vector->components[2] = -9.331113;
destroy_vector(&my_vector) // Don't forget to destroy the vector at the end
```
There is also a more compact method to create a vector:
```c
// This will create a vector in R^5. All components are splitted by comma, so don't use any whitespace between them
vector_t vector1 = string_to_vector("1.0031,2134.01,333.333,0.001,3.4");
destroy_vector(&vector1); // Really. Don't forget this!
```
You can fill the components with the same value:
```c
vector_t vector1 = create_vector(3);
fill_vector(vector1, 5.6); // Now vector1 is (5.6, 5.6, 5.6)
destroy_vector(&vector1);
```
To increase/decrease vector dimension use `vector_push` and `vector_pop`:
```c
vector_t vector1 = ("1.1,4.0,3.2,0.0");
// The following line add a new component in position 1
vector_push(vector1, 5.6, 1); // Now vector1 is (1.1, 5.6, 4.0, 3.2, 0.0)
// The following line delete a component in position 3
vector_pop(vector1, 3); // Now vector 1 is (1.1, 5.6, 4.0, 0.0) 
destroy_vector(&vector1);
```

### Printing vectors
You can print a vector using both `print_vector` and `printf_vector`. For example:
```c
vector_t vector = create_vector(4);
vector->components[1] = 1;
vector->components[3] = 1;
// You can use print_vector to use default print format "%.2f "
print_vector(vector); // Print '0.00 1.00 0.00 1.00'
// .. Or you can use printf_vector to use a custom format
printf_vector(vector, "%.0f "); // Print '0 1 0 1'
destroy_vector(&vector);
```

### Vector operations
#### Sum
```c
vector_t vector1 = string_to_vector("1,2,3,1");
vector_t vector2 = string_to_vector("3,4,1,2");
vector_t sum = sum_vector(vector1, vector2);
printf_vector(sum, "%.0f "); // Print '4 6 4 3'

destroy_vector(&vector1);
destroy_vector(&vector2);
destroy_vector(&sum);
```
#### Dot product
```c
vector_t vector1 = string_to_vector("1,4,1,4");
vector_t vector2 = string_to_vector("3,3,1,1");
double result = dot_product(vector1, vector2);
printf("Dot product: %.2f\n", result); // Calculate 1*3 + 4*3 + 1*1 + 4*1. Print 20.00

destroy_vector(&vector1);
destroy_vector(&vector2);
```

#### Cross product
```c
vector_t vector1 = string_to_vector("1,4,1");
vector_t vector2 = string_to_vector("3,3,1");
vector_t result = cross_product(vector1, vector2);
printf_vector(result, "%.0f "); // Print '1 -2 -9'

destroy_vector(&vector1);
destroy_vector(&vector2);
destroy_vector(&result);
```

#### Scalar multiplication
```c
vector_t vector1 = string_to_vector("1,4,1");
vector_scalar_multiplication(vector1, 2.1); // Overwrite the vector
print_vector(vector1); // Print '2.1 8.4 2.1'

destroy_vector(&vector1);
```

#### Scalar sum
```c
vector_t vector1 = string_to_vector("4,7,2");
vector_add_scalar(vector1, 1.1);
print_vector(vector1); // Print '5.1 8.1 3.1'

destroy_vector(&vector1);
```

#### Absolute value
```c
vector_t vector1 = string_to_vector("-84.5,-67.1,24.0");
vector_abs(vector1);
print_vector(vector1); // Print '84.5 67.1 24.0'

destroy_vector(&vector1);
```

#### Vector normalitation and magnitude
```c
vector_t vector1 = string_to_vector("1,4,1");
vector_normalize(vector1); // Overwrite the vector
print_vector(vector1); // Print '0.24 0.94 0.24'
double magnitude = vector_magnitude(vector1);
printf("Mangnitude: %.2f\n", magnitude); // Print 1.00

destroy_vector(&vector1);
```

### Vector properties
You can use these useful functions to show vector properties
```c
vector_t vector1 = string_to_vector("5,3,2");
vector_t vector2 = string_to_vector("10,6,4");

int min_index = min_vector_component(vector1);
int max_index = max_vector_component(vector1);
printf("min_index: %d | max_index: %d\n", min_index, max_index); // Print '2 0'

int result1 = is_zero_vector(vector2); // Check if all components are equal to zero
int result2 = is_parallel_to(vector2, vector1); // Check if vector2 is parallel to vector1
int result3 = is_perpendicular_to(vector2, vector1); // Check if vector2 is perpendicular to vector1
printf("result1: %d | result2: %d | result3: %d\n", result1, result2, result3); // Print '0 1 0'

double angle = vector_angle(vector1, vector2); // Calculate the angle in radians between vector1 and vector2
printf("angle: %.2f\n", angle); // Printf '0.00' because the vectors are parallel
```

### Other stuff
If you want to access to vector dimension or single vector component:
```c
vector_t vector1 = string_to_vector("4,4,1,2");
printf("%u %.0f\n", vector1->dimension, vector1->component[3]); // Print '4 2'
```

If you want to duplicate an existing vector use `copy_vector`:
```c
vector_t vector1 = string_to_vector("2,4,5,1");
vector_t vector2 = copy_vector(vector1);
print_vector(vector2); // Print '2.00 4.00 5.00 1.00'
destroy_vector(&vector1);
destroy_vector(&vector2);
```

### Memory leaks
Pay attention to not change vector rvalue before destroying it.
```c
vector_t vector1 = create_vector(5);
vector1 = create_vector(2);
destroy_vector(&vector1); // Old vector1 is still in memory (Memory leaks)
```

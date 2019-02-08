#include <stdio.h>
#include <check.h>
#include "libvector.h"

START_TEST(create_vector_test)
{
	vector_t vector = NULL;
	vector = create_vector(4);
	ck_assert(vector != NULL);
	ck_assert_uint_eq(vector->dimension, 4);
	for(unsigned int i = 0; i < vector->dimension; i++)
		ck_assert(vector->components[i] ==  0.0);

	destroy_vector(&vector);
	ck_assert(vector == NULL);
}
END_TEST

START_TEST(string_to_vector_test)
{
	vector_t vector = string_to_vector("30.0,3.5,1.5");
	ck_assert(vector->components[0] == 30.0);
	ck_assert(vector->components[1] == 3.5);
	ck_assert(vector->components[2] == 1.5);
	destroy_vector(&vector);
}
END_TEST

START_TEST(copy_vector_test)
{
	vector_t vector1 = string_to_vector("3,3,3,3");
	vector_t vector2 = copy_vector(vector1);
	for(unsigned int i = 0; i < vector2->dimension; i++)
		ck_assert(vector2->components[i] == 3.0);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
}
END_TEST

START_TEST(fill_vector_test)
{
	vector_t vector = string_to_vector("30,30,30,30");
	for(unsigned int i = 0; i < vector->dimension; i++)
		ck_assert(vector->components[i] == 30.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(vector_push_test)
{
	vector_t vector = string_to_vector("1,1,1,1");
	vector_push(vector, 2.0, 1);
	ck_assert(vector->components[1] == 2.0);
	for(unsigned int i = 0; i < vector->dimension; i++)
		if(i != 1) ck_assert(vector->components[i] == 1.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(vector_pop_test)
{
	vector_t vector = string_to_vector("1,1,1,1");
	vector->components[1] = 2.0;
	vector_pop(vector, 1);
	for(unsigned int i = 0; i < vector->dimension; i++)
		ck_assert(vector->components[i] == 1.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(sum_vector_test)
{
	vector_t vector1 = string_to_vector("1,1,1");
	vector_t vector2 = string_to_vector("1,1,1");
	vector_t vector3 = sum_vector(vector1, vector2);
	for(unsigned int i = 0; i < vector3->dimension; i++)
		ck_assert(vector3->components[i] == 2.0);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
	destroy_vector(&vector3);
}
END_TEST

START_TEST(dot_procuct_test)
{
	vector_t vector1 = string_to_vector("1,1,1");
	vector_t vector2 = string_to_vector("2,2,2");
	ck_assert(dot_product(vector1, vector2) == 6.0);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
}
END_TEST

START_TEST(cross_product_test)
{
	vector_t vector1 = string_to_vector("1,1,1");
	vector_t vector2 = string_to_vector("2,2,2");
	vector_t vector3 = cross_product(vector1, vector2);
	for(unsigned int i = 0; i < vector3->dimension; i++)
		ck_assert(vector3->components[i] == 0.0);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
	destroy_vector(&vector3);
}
END_TEST

START_TEST(vector_scalar_multiplication_test)
{
	vector_t vector = string_to_vector("3,3,3");
	vector_scalar_multiplication(vector, 10.0);
	for(unsigned int i = 0; i < vector->dimension; i++)
		ck_assert(vector->components[i] == 30.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(vector_add_scalar_test)
{
	vector_t vector = string_to_vector("1,1,1");
	vector_add_scalar(vector, 1.0);
	for(unsigned int i = 0; i < vector->dimension; i++)
		ck_assert(vector->components[i] == 2.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(vector_magnitude_test)
{
	vector_t vector = create_vector(3);
	vector->components[2] = 1.0;
	ck_assert(vector_magnitude(vector) == 1.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(vector_normalize_test)
{
	vector_t vector = string_to_vector("2,2,2");
	vector_normalize(vector);
	ck_assert(vector_magnitude(vector) == 1.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(vector_angle_test)
{
	vector_t vector1 = string_to_vector("1,1,1");
	vector_t vector2 = string_to_vector("1,1,1");
	vector2->components[1] = -2.0;
	double angle = vector_angle(vector1, vector2);
	ck_assert(angle >= 1.56 && angle <= 1.58);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
}
END_TEST

START_TEST(max_vector_component_test)
{
	vector_t vector = string_to_vector("1,2,5,-3");
	int max_index = max_vector_component(vector);
	ck_assert(max_index == 2);
	destroy_vector(&vector);
}
END_TEST

START_TEST(min_vector_component_test)
{
	vector_t vector = string_to_vector("1,2,5,-3");
	int min_index = min_vector_component(vector);
	ck_assert(min_index == 3);
	destroy_vector(&vector);
}
END_TEST

START_TEST(is_zero_vector_test)
{
	vector_t vector = create_vector(4);
	for(unsigned int i = 0; i < vector->dimension; i++)
		ck_assert(vector->components[i] == 0.0);
	destroy_vector(&vector);
}
END_TEST

START_TEST(is_parallel_to_test)
{
	vector_t vector1 = string_to_vector("2,3,5");
	vector_t vector2 = string_to_vector("6,9,15");
	ck_assert(is_parallel_to(vector1, vector2) == 1);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
}
END_TEST

START_TEST(is_perpendicular_to_test)
{
	vector_t vector1 = string_to_vector("2,4,5");
	vector_t vector2 = string_to_vector("-7,1,2");
	ck_assert(is_perpendicular_to(vector1, vector2) == 1);
	destroy_vector(&vector1);
	destroy_vector(&vector2);
}
END_TEST

Suite *libvector_suite(void)
{
	Suite *suite = suite_create("libvector_suite");

	TCase *tc_vector_instance = tcase_create("vector_instance");
	tcase_add_test(tc_vector_instance, create_vector_test);
	tcase_add_test(tc_vector_instance, string_to_vector_test);
	tcase_add_test(tc_vector_instance, copy_vector_test);
	suite_add_tcase(suite, tc_vector_instance);

	TCase *tc_vector_initialization = tcase_create("vector_initialization");
	tcase_add_test(tc_vector_initialization, vector_push_test);
	tcase_add_test(tc_vector_initialization, vector_pop_test);
	tcase_add_test(tc_vector_initialization, fill_vector_test);
	tcase_add_test(tc_vector_initialization, vector_push_test);
	tcase_add_test(tc_vector_initialization, vector_pop_test);
	suite_add_tcase(suite, tc_vector_initialization);

	TCase *tc_vector_operations = tcase_create("vector_operations");
	tcase_add_test(tc_vector_operations, sum_vector_test);
	tcase_add_test(tc_vector_operations, dot_procuct_test);
	tcase_add_test(tc_vector_operations, cross_product_test);
	tcase_add_test(tc_vector_operations, vector_scalar_multiplication_test);
	tcase_add_test(tc_vector_operations, vector_add_scalar_test);
	suite_add_tcase(suite, tc_vector_operations);

	TCase *tc_vector_properties = tcase_create("vector_properties");
	tcase_add_test(tc_vector_properties, vector_magnitude_test);
	tcase_add_test(tc_vector_properties, vector_normalize_test);
	tcase_add_test(tc_vector_properties, vector_angle_test);
	tcase_add_test(tc_vector_properties, max_vector_component_test);
	tcase_add_test(tc_vector_properties, min_vector_component_test);
	tcase_add_test(tc_vector_properties, is_zero_vector_test);
	tcase_add_test(tc_vector_properties, is_parallel_to_test);
	tcase_add_test(tc_vector_properties, is_perpendicular_to_test);
	suite_add_tcase(suite, tc_vector_properties);

	return suite;
}

int main()
{
	Suite *suite = libvector_suite();
	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_NORMAL);
	int number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (number_failed == 0) ? 0 : 1;
}
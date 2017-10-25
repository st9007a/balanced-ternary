#include <check.h>
#include <stdlib.h>

#include "../ternary.h"

START_TEST(test_tint6_eq)
{
    tint6 *t;
    for (int i = -364; i <= 364; i++) {
        t = getTernaryInt(i);
        ck_assert_int_eq(toBinary(t), i);
    }
    free(t);
}
END_TEST

START_TEST(test_tint6_out_of_upper_bound)
{
    tint6 *up = getTernaryInt(365);
    ck_assert_msg(up == NULL, "NULL should be returned on input integer out of range.");
}
END_TEST

START_TEST(test_tint6_out_of_lower_bound)
{
    tint6 *low = getTernaryInt(-365);
    ck_assert_msg(low == NULL, "NULL should be returned on input integer out of range.");
}
END_TEST

START_TEST(test_tint6_sum)
{
    tint6 *a;
    tint6 *b;
    tint6 carry;

    for (int i = -364; i <= 364; i++) {
        a = getTernaryInt(i);
        for (int j = -364; j <= 364; j++) {
            b = getTernaryInt(j);
            int total = toBinary(sum(a, b, &carry)) + toBinary(&carry) * 729;
            ck_assert_int_eq(total, i + j);
        }
    }
}
END_TEST

Suite *ternarySuite()
{
    Suite *s;
    TCase *tCore;

    s = suite_create("Ternary");
    tCore = tcase_create("Core");

    tcase_add_test(tCore, test_tint6_eq);
    tcase_add_test(tCore, test_tint6_out_of_upper_bound);
    tcase_add_test(tCore, test_tint6_out_of_lower_bound);
    tcase_add_test(tCore, test_tint6_sum);

    suite_add_tcase(s, tCore);
    return s;

}

int main()
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = ternarySuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

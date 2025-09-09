#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_P4(char *root, char *perfect_4th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int perfect_4th_midi = note_to_midi(perfect_4th);

    int chord_root_position[] = {root_midi, perfect_4th_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s perfect 4th", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, perfect_4th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_perfect_4th(void) { test_P4("C3", "F3"); }
void test_Cs_perfect_4th(void) { test_P4("C#3", "F#3"); }
void test_D_perfect_4th(void) { test_P4("D3", "G3"); }
void test_Ds_perfect_4th(void) { test_P4("D#3", "G#3"); }
void test_E_perfect_4th(void) { test_P4("E3", "A3"); }
void test_F_perfect_4th(void) { test_P4("F3", "A#3"); }
void test_Fs_perfect_4th(void) { test_P4("F#3", "B3"); }
void test_G_perfect_4th(void) { test_P4("G3", "C4"); }
void test_Gs_perfect_4th(void) { test_P4("G#3", "C#4"); }
void test_A_perfect_4th(void) { test_P4("A3", "D4"); }
void test_As_perfect_4th(void) { test_P4("A#3", "D#4"); }
void test_B_perfect_4th(void) { test_P4("B3", "E4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite =
        CU_add_suite("Perfect Fourth Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C perfect 4th", test_C_perfect_4th);
    CU_add_test(pSuite, "C# perfect 4th", test_Cs_perfect_4th);
    CU_add_test(pSuite, "D perfect 4th", test_D_perfect_4th);
    CU_add_test(pSuite, "D# perfect 4th", test_Ds_perfect_4th);
    CU_add_test(pSuite, "E perfect 4th", test_E_perfect_4th);
    CU_add_test(pSuite, "F perfect 4th", test_F_perfect_4th);
    CU_add_test(pSuite, "F# perfect 4th", test_Fs_perfect_4th);
    CU_add_test(pSuite, "G perfect 4th", test_G_perfect_4th);
    CU_add_test(pSuite, "G# perfect 4th", test_Gs_perfect_4th);
    CU_add_test(pSuite, "A perfect 4th", test_A_perfect_4th);
    CU_add_test(pSuite, "A# perfect 4th", test_As_perfect_4th);
    CU_add_test(pSuite, "B perfect 4th", test_B_perfect_4th);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

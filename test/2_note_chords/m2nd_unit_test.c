#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_m2nd(char *root, char *minor_2nd) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int minor_2nd_midi = note_to_midi(minor_2nd);

    int chord_root_position[] = {root_midi, minor_2nd_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s minor 2nd", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, minor_2nd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_minor_2nd(void) { test_m2nd("C3", "C#3"); }
void test_Cs_minor_2nd(void) { test_m2nd("C#3", "D3"); }
void test_D_minor_2nd(void) { test_m2nd("D3", "D#3"); }
void test_Ds_minor_2nd(void) { test_m2nd("D#3", "E3"); }
void test_E_minor_2nd(void) { test_m2nd("E3", "F3"); }
void test_F_minor_2nd(void) { test_m2nd("F3", "F#3"); }
void test_Fs_minor_2nd(void) { test_m2nd("F#3", "G3"); }
void test_G_minor_2nd(void) { test_m2nd("G3", "G#3"); }
void test_Gs_minor_2nd(void) { test_m2nd("G#3", "A3"); }
void test_A_minor_2nd(void) { test_m2nd("A3", "A#3"); }
void test_As_minor_2nd(void) { test_m2nd("A#3", "B3"); }
void test_B_minor_2nd(void) { test_m2nd("B3", "C4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Minor 2nd Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C minor 2nd", test_C_minor_2nd);
    CU_add_test(pSuite, "C# minor 2nd", test_Cs_minor_2nd);
    CU_add_test(pSuite, "D minor 2nd", test_D_minor_2nd);
    CU_add_test(pSuite, "D# minor 2nd", test_Ds_minor_2nd);
    CU_add_test(pSuite, "E minor 2nd", test_E_minor_2nd);
    CU_add_test(pSuite, "F minor 2nd", test_F_minor_2nd);
    CU_add_test(pSuite, "F# minor 2nd", test_Fs_minor_2nd);
    CU_add_test(pSuite, "G minor 2nd", test_G_minor_2nd);
    CU_add_test(pSuite, "G# minor 2nd", test_Gs_minor_2nd);
    CU_add_test(pSuite, "A minor 2nd", test_A_minor_2nd);
    CU_add_test(pSuite, "A# minor 2nd", test_As_minor_2nd);
    CU_add_test(pSuite, "B minor 2nd", test_B_minor_2nd);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

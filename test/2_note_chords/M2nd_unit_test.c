#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_M2nd(char *root, char *major_2nd) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int major_2nd_midi = note_to_midi(major_2nd);

    int chord_root_position[] = {root_midi, major_2nd_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s major 2nd", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, major_2nd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_major_2nd(void) { test_M2nd("C3", "D3"); }
void test_Cs_major_2nd(void) { test_M2nd("C#3", "D#3"); }
void test_D_major_2nd(void) { test_M2nd("D3", "E3"); }
void test_Ds_major_2nd(void) { test_M2nd("D#3", "F3"); }
void test_E_major_2nd(void) { test_M2nd("E3", "F#3"); }
void test_F_major_2nd(void) { test_M2nd("F3", "G3"); }
void test_Fs_major_2nd(void) { test_M2nd("F#3", "G#3"); }
void test_G_major_2nd(void) { test_M2nd("G3", "A3"); }
void test_Gs_major_2nd(void) { test_M2nd("G#3", "A#3"); }
void test_A_major_2nd(void) { test_M2nd("A3", "B3"); }
void test_As_major_2nd(void) { test_M2nd("A#3", "C4"); }
void test_B_major_2nd(void) { test_M2nd("B3", "C#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Major 2nd Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C major 2nd", test_C_major_2nd);
    CU_add_test(pSuite, "C# major 2nd", test_Cs_major_2nd);
    CU_add_test(pSuite, "D major 2nd", test_D_major_2nd);
    CU_add_test(pSuite, "D# major 2nd", test_Ds_major_2nd);
    CU_add_test(pSuite, "E major 2nd", test_E_major_2nd);
    CU_add_test(pSuite, "F major 2nd", test_F_major_2nd);
    CU_add_test(pSuite, "F# major 2nd", test_Fs_major_2nd);
    CU_add_test(pSuite, "G major 2nd", test_G_major_2nd);
    CU_add_test(pSuite, "G# major 2nd", test_Gs_major_2nd);
    CU_add_test(pSuite, "A major 2nd", test_A_major_2nd);
    CU_add_test(pSuite, "A# major 2nd", test_As_major_2nd);
    CU_add_test(pSuite, "B major 2nd", test_B_major_2nd);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

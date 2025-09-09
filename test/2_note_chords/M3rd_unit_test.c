#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_M3rd(char *root, char *major_3rd) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int major_3rd_midi = note_to_midi(major_3rd);

    int chord_root_position[] = {root_midi, major_3rd_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s major 3rd", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, major_3rd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_major_3rd(void) { test_M3rd("C3", "E3"); }
void test_Cs_major_3rd(void) { test_M3rd("C#3", "F3"); }
void test_D_major_3rd(void) { test_M3rd("D3", "F#3"); }
void test_Ds_major_3rd(void) { test_M3rd("D#3", "G3"); }
void test_E_major_3rd(void) { test_M3rd("E3", "G#3"); }
void test_F_major_3rd(void) { test_M3rd("F3", "A3"); }
void test_Fs_major_3rd(void) { test_M3rd("F#3", "A#3"); }
void test_G_major_3rd(void) { test_M3rd("G3", "B3"); }
void test_Gs_major_3rd(void) { test_M3rd("G#3", "C4"); }
void test_A_major_3rd(void) { test_M3rd("A3", "C#4"); }
void test_As_major_3rd(void) { test_M3rd("A#3", "D4"); }
void test_B_major_3rd(void) { test_M3rd("B3", "D#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Major 3rd Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C major 3rd", test_C_major_3rd);
    CU_add_test(pSuite, "C# major 3rd", test_Cs_major_3rd);
    CU_add_test(pSuite, "D major 3rd", test_D_major_3rd);
    CU_add_test(pSuite, "D# major 3rd", test_Ds_major_3rd);
    CU_add_test(pSuite, "E major 3rd", test_E_major_3rd);
    CU_add_test(pSuite, "F major 3rd", test_F_major_3rd);
    CU_add_test(pSuite, "F# major 3rd", test_Fs_major_3rd);
    CU_add_test(pSuite, "G major 3rd", test_G_major_3rd);
    CU_add_test(pSuite, "G# major 3rd", test_Gs_major_3rd);
    CU_add_test(pSuite, "A major 3rd", test_A_major_3rd);
    CU_add_test(pSuite, "A# major 3rd", test_As_major_3rd);
    CU_add_test(pSuite, "B major 3rd", test_B_major_3rd);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

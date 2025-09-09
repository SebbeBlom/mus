#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_m3rd(char *root, char *minor_3rd) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int minor_3rd_midi = note_to_midi(minor_3rd);

    int chord_root_position[] = {root_midi, minor_3rd_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s minor 3rd", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, minor_3rd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_minor_3rd(void) { test_m3rd("C3", "D#3"); }
void test_Cs_minor_3rd(void) { test_m3rd("C#3", "E3"); }
void test_D_minor_3rd(void) { test_m3rd("D3", "F3"); }
void test_Ds_minor_3rd(void) { test_m3rd("D#3", "F#3"); }
void test_E_minor_3rd(void) { test_m3rd("E3", "G3"); }
void test_F_minor_3rd(void) { test_m3rd("F3", "G#3"); }
void test_Fs_minor_3rd(void) { test_m3rd("F#3", "A3"); }
void test_G_minor_3rd(void) { test_m3rd("G3", "A#3"); }
void test_Gs_minor_3rd(void) { test_m3rd("G#3", "B3"); }
void test_A_minor_3rd(void) { test_m3rd("A3", "C4"); }
void test_As_minor_3rd(void) { test_m3rd("A#3", "C#4"); }
void test_B_minor_3rd(void) { test_m3rd("B3", "D4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Minor 3rd Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C minor 3rd", test_C_minor_3rd);
    CU_add_test(pSuite, "C# minor 3rd", test_Cs_minor_3rd);
    CU_add_test(pSuite, "D minor 3rd", test_D_minor_3rd);
    CU_add_test(pSuite, "D# minor 3rd", test_Ds_minor_3rd);
    CU_add_test(pSuite, "E minor 3rd", test_E_minor_3rd);
    CU_add_test(pSuite, "F minor 3rd", test_F_minor_3rd);
    CU_add_test(pSuite, "F# minor 3rd", test_Fs_minor_3rd);
    CU_add_test(pSuite, "G minor 3rd", test_G_minor_3rd);
    CU_add_test(pSuite, "G# minor 3rd", test_Gs_minor_3rd);
    CU_add_test(pSuite, "A minor 3rd", test_A_minor_3rd);
    CU_add_test(pSuite, "A# minor 3rd", test_As_minor_3rd);
    CU_add_test(pSuite, "B minor 3rd", test_B_minor_3rd);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_M7th(char *root, char *major_7th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int major_7th_midi = note_to_midi(major_7th);

    int chord_root_position[] = {root_midi, major_7th_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s major 7th", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, major_7th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_major_7th(void) { test_M7th("C3", "B3"); }
void test_Cs_major_7th(void) { test_M7th("C#3", "C4"); }
void test_D_major_7th(void) { test_M7th("D3", "C#4"); }
void test_Ds_major_7th(void) { test_M7th("D#3", "D4"); }
void test_E_major_7th(void) { test_M7th("E3", "D#4"); }
void test_F_major_7th(void) { test_M7th("F3", "E4"); }
void test_Fs_major_7th(void) { test_M7th("F#3", "F4"); }
void test_G_major_7th(void) { test_M7th("G3", "F#4"); }
void test_Gs_major_7th(void) { test_M7th("G#3", "G4"); }
void test_A_major_7th(void) { test_M7th("A3", "G#4"); }
void test_As_major_7th(void) { test_M7th("A#3", "A4"); }
void test_B_major_7th(void) { test_M7th("B3", "A#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite =
        CU_add_suite("Major Seventh Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C major 7th", test_C_major_7th);
    CU_add_test(pSuite, "C# major 7th", test_Cs_major_7th);
    CU_add_test(pSuite, "D major 7th", test_D_major_7th);
    CU_add_test(pSuite, "D# major 7th", test_Ds_major_7th);
    CU_add_test(pSuite, "E major 7th", test_E_major_7th);
    CU_add_test(pSuite, "F major 7th", test_F_major_7th);
    CU_add_test(pSuite, "F# major 7th", test_Fs_major_7th);
    CU_add_test(pSuite, "G major 7th", test_G_major_7th);
    CU_add_test(pSuite, "G# major 7th", test_Gs_major_7th);
    CU_add_test(pSuite, "A major 7th", test_A_major_7th);
    CU_add_test(pSuite, "A# major 7th", test_As_major_7th);
    CU_add_test(pSuite, "B major 7th", test_B_major_7th);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

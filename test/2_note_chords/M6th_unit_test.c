#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_M6th(char *root, char *major_6th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int major_6th_midi = note_to_midi(major_6th);

    int chord_root_position[] = {root_midi, major_6th_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s major 6th", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, major_6th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_major_6th(void) { test_M6th("C3", "A3"); }
void test_Cs_major_6th(void) { test_M6th("C#3", "A#3"); }
void test_D_major_6th(void) { test_M6th("D3", "B3"); }
void test_Ds_major_6th(void) { test_M6th("D#3", "C4"); }
void test_E_major_6th(void) { test_M6th("E3", "C#4"); }
void test_F_major_6th(void) { test_M6th("F3", "D4"); }
void test_Fs_major_6th(void) { test_M6th("F#3", "D#4"); }
void test_G_major_6th(void) { test_M6th("G3", "E4"); }
void test_Gs_major_6th(void) { test_M6th("G#3", "F4"); }
void test_A_major_6th(void) { test_M6th("A3", "F#4"); }
void test_As_major_6th(void) { test_M6th("A#3", "G4"); }
void test_B_major_6th(void) { test_M6th("B3", "G#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Major Sixth Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C major 6th", test_C_major_6th);
    CU_add_test(pSuite, "C# major 6th", test_Cs_major_6th);
    CU_add_test(pSuite, "D major 6th", test_D_major_6th);
    CU_add_test(pSuite, "D# major 6th", test_Ds_major_6th);
    CU_add_test(pSuite, "E major 6th", test_E_major_6th);
    CU_add_test(pSuite, "F major 6th", test_F_major_6th);
    CU_add_test(pSuite, "F# major 6th", test_Fs_major_6th);
    CU_add_test(pSuite, "G major 6th", test_G_major_6th);
    CU_add_test(pSuite, "G# major 6th", test_Gs_major_6th);
    CU_add_test(pSuite, "A major 6th", test_A_major_6th);
    CU_add_test(pSuite, "A# major 6th", test_As_major_6th);
    CU_add_test(pSuite, "B major 6th", test_B_major_6th);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

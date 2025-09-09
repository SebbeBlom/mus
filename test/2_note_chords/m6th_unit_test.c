#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_m6th(char *root, char *minor_6th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int minor_6th_midi = note_to_midi(minor_6th);

    int chord_root_position[] = {root_midi, minor_6th_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s minor 6th", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, minor_6th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_minor_6th(void) { test_m6th("C3", "G#3"); }
void test_Cs_minor_6th(void) { test_m6th("C#3", "A3"); }
void test_D_minor_6th(void) { test_m6th("D3", "A#3"); }
void test_Ds_minor_6th(void) { test_m6th("D#3", "B3"); }
void test_E_minor_6th(void) { test_m6th("E3", "C4"); }
void test_F_minor_6th(void) { test_m6th("F3", "C#4"); }
void test_Fs_minor_6th(void) { test_m6th("F#3", "D4"); }
void test_G_minor_6th(void) { test_m6th("G3", "D#4"); }
void test_Gs_minor_6th(void) { test_m6th("G#3", "E4"); }
void test_A_minor_6th(void) { test_m6th("A3", "F4"); }
void test_As_minor_6th(void) { test_m6th("A#3", "F#4"); }
void test_B_minor_6th(void) { test_m6th("B3", "G4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Minor Sixth Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C minor 6th", test_C_minor_6th);
    CU_add_test(pSuite, "C# minor 6th", test_Cs_minor_6th);
    CU_add_test(pSuite, "D minor 6th", test_D_minor_6th);
    CU_add_test(pSuite, "D# minor 6th", test_Ds_minor_6th);
    CU_add_test(pSuite, "E minor 6th", test_E_minor_6th);
    CU_add_test(pSuite, "F minor 6th", test_F_minor_6th);
    CU_add_test(pSuite, "F# minor 6th", test_Fs_minor_6th);
    CU_add_test(pSuite, "G minor 6th", test_G_minor_6th);
    CU_add_test(pSuite, "G# minor 6th", test_Gs_minor_6th);
    CU_add_test(pSuite, "A minor 6th", test_A_minor_6th);
    CU_add_test(pSuite, "A# minor 6th", test_As_minor_6th);
    CU_add_test(pSuite, "B minor 6th", test_B_minor_6th);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

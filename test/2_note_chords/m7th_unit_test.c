#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_m7th(char *root, char *minor_7th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int minor_7th_midi = note_to_midi(minor_7th);

    int chord_root_position[] = {root_midi, minor_7th_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s minor 7th", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, minor_7th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_minor_7th(void) { test_m7th("C3", "A#3"); }
void test_Cs_minor_7th(void) { test_m7th("C#3", "B3"); }
void test_D_minor_7th(void) { test_m7th("D3", "C4"); }
void test_Ds_minor_7th(void) { test_m7th("D#3", "C#4"); }
void test_E_minor_7th(void) { test_m7th("E3", "D4"); }
void test_F_minor_7th(void) { test_m7th("F3", "D#4"); }
void test_Fs_minor_7th(void) { test_m7th("F#3", "E4"); }
void test_G_minor_7th(void) { test_m7th("G3", "F4"); }
void test_Gs_minor_7th(void) { test_m7th("G#3", "F#4"); }
void test_A_minor_7th(void) { test_m7th("A3", "G4"); }
void test_As_minor_7th(void) { test_m7th("A#3", "G#4"); }
void test_B_minor_7th(void) { test_m7th("B3", "A4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite =
        CU_add_suite("Minor Seventh Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C minor 7th", test_C_minor_7th);
    CU_add_test(pSuite, "C# minor 7th", test_Cs_minor_7th);
    CU_add_test(pSuite, "D minor 7th", test_D_minor_7th);
    CU_add_test(pSuite, "D# minor 7th", test_Ds_minor_7th);
    CU_add_test(pSuite, "E minor 7th", test_E_minor_7th);
    CU_add_test(pSuite, "F minor 7th", test_F_minor_7th);
    CU_add_test(pSuite, "F# minor 7th", test_Fs_minor_7th);
    CU_add_test(pSuite, "G minor 7th", test_G_minor_7th);
    CU_add_test(pSuite, "G# minor 7th", test_Gs_minor_7th);
    CU_add_test(pSuite, "A minor 7th", test_A_minor_7th);
    CU_add_test(pSuite, "A# minor 7th", test_As_minor_7th);
    CU_add_test(pSuite, "B minor 7th", test_B_minor_7th);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

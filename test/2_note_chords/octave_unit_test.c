#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_Octave(char *root, char *octave) {
    /*     HashMap *map = hash_map_create();
        populate_hash_map(map);

        int root_midi = note_to_midi(root);
        int octave_midi = note_to_midi(octave);

        int chord_root_position[] = {root_midi, octave_midi};
        chord_t *chord = chord_analyzer(chord_root_position,2, map);

        char expected[20];
        char extract_root[3];

        extract_note_name(root, extract_root);
        sprintf(expected, "%s octave", extract_root);

        if (strcmp(chord->to_string, expected) != 0) {
            puts("");
            puts("");
            printf("Test failed: %s + %s\n", root, octave);
            printf("Expected: '%s'\n", expected);
            printf("Got:      '%s'", chord->to_string);
            CU_FAIL("Chord analysis failed");
        }
            */
}

void test_C_octave(void) { test_Octave("C3", "C4"); }
void test_Cs_octave(void) { test_Octave("C#3", "C#4"); }
void test_D_octave(void) { test_Octave("D3", "D4"); }
void test_Ds_octave(void) { test_Octave("D#3", "D#4"); }
void test_E_octave(void) { test_Octave("E3", "E4"); }
void test_F_octave(void) { test_Octave("F3", "F4"); }
void test_Fs_octave(void) { test_Octave("F#3", "F#4"); }
void test_G_octave(void) { test_Octave("G3", "G4"); }
void test_Gs_octave(void) { test_Octave("G#3", "G#4"); }
void test_A_octave(void) { test_Octave("A3", "A4"); }
void test_As_octave(void) { test_Octave("A#3", "A#4"); }
void test_B_octave(void) { test_Octave("B3", "B4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Octave Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C octave", test_C_octave);
    CU_add_test(pSuite, "C# octave", test_Cs_octave);
    CU_add_test(pSuite, "D octave", test_D_octave);
    CU_add_test(pSuite, "D# octave", test_Ds_octave);
    CU_add_test(pSuite, "E octave", test_E_octave);
    CU_add_test(pSuite, "F octave", test_F_octave);
    CU_add_test(pSuite, "F# octave", test_Fs_octave);
    CU_add_test(pSuite, "G octave", test_G_octave);
    CU_add_test(pSuite, "G# octave", test_Gs_octave);
    CU_add_test(pSuite, "A octave", test_A_octave);
    CU_add_test(pSuite, "A# octave", test_As_octave);
    CU_add_test(pSuite, "B octave", test_B_octave);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

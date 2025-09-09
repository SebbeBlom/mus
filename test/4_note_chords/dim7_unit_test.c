#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

// Test function for a given major triad chord
void test_dim7_chord( char *root,  char *minor_3rd,
                      char *tritone,  char *diminished_7th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int minor_3rd_midi = note_to_midi(minor_3rd);
    int tritone_midi = note_to_midi(tritone);
    int diminished_7th_midi = note_to_midi(diminished_7th);

    int chord_root_position[] = {root_midi, minor_3rd_midi, tritone_midi,
                                 diminished_7th_midi};

    chord_t *chord1 = chord_analyzer(chord_root_position, 4, map);
    
    char expected[20];
    char extract_root[3];
    extract_note_name(root, extract_root);
    sprintf(expected, "%sdim7", extract_root);

    if (strcmp(chord1->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s + %s + %s\n", root, minor_3rd, tritone,
               diminished_7th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord1->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

// Wrapper functions for major triad chords
void test_C_dim7(void) { test_dim7_chord("C3", "D#3", "F#3", "A3"); }
void test_Cs_dim7(void) { test_dim7_chord("C#3", "E3", "G3", "A#3"); }
void test_D_dim7(void) { test_dim7_chord("D3", "F3", "G#3", "B3"); }
void test_Ds_dim7(void) { test_dim7_chord("D#3", "F#3", "A3", "C4"); }
void test_E_dim7(void) { test_dim7_chord("E3", "G3", "A#3", "C#4"); }
void test_F_dim7(void) { test_dim7_chord("F3", "G#3", "B3", "D4"); }
void test_Fs_dim7(void) { test_dim7_chord("F#3", "A3", "C4", "D#4"); }
void test_G_dim7(void) { test_dim7_chord("G3", "A#3", "C#4", "E4"); }
void test_Gs_dim7(void) { test_dim7_chord("G#3", "B3", "D4", "F4"); }
void test_A_dim7(void) { test_dim7_chord("A3", "C4", "D#4", "F#4"); }
void test_As_dim7(void) { test_dim7_chord("A#3", "C#4", "E4", "G4"); }
void test_B_dim7(void) { test_dim7_chord("B3", "D4", "F4", "G#4"); }

int main() {
    // Initialize the CUnit test registry
    CU_initialize_registry();

    // Add a test suite
    CU_pSuite pSuite = CU_add_suite("Major Chords Test Suite", 0, 0);

    // Add major triad tests
    CU_add_test(pSuite, "C dim7", test_C_dim7);
    CU_add_test(pSuite, "C# dim7", test_Cs_dim7);
    CU_add_test(pSuite, "D dim7", test_D_dim7);
    CU_add_test(pSuite, "D# dim7", test_Ds_dim7);
    CU_add_test(pSuite, "E dim7", test_E_dim7);
    CU_add_test(pSuite, "F dim7", test_F_dim7);
    CU_add_test(pSuite, "F# dim7", test_Fs_dim7);
    CU_add_test(pSuite, "G dim7", test_G_dim7);
    CU_add_test(pSuite, "G# dim7", test_Gs_dim7);
    CU_add_test(pSuite, "A dim7", test_A_dim7);
    CU_add_test(pSuite, "A# dim7", test_As_dim7);
    CU_add_test(pSuite, "B dim7", test_B_dim7);

    // Run all the tests
    CU_basic_run_tests();

    // Clean up
    CU_cleanup_registry();

    return 0;
}

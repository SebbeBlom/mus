#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

// Test function for a given aug_maj 7th chord
void test_aug_maj7_chord(char *root, char *major_3rd, char *augmented_5th,
                         char *minor_7th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int major_3rd_midi = note_to_midi(major_3rd);
    int augmented_5th_midi = note_to_midi(augmented_5th);
    int minor_7th_midi = note_to_midi(minor_7th);

    int chord_root_position[] = {root_midi, major_3rd_midi, augmented_5th_midi,
                                 minor_7th_midi};
    int chord_1st_inversion[] = {major_3rd_midi, augmented_5th_midi,
                                 minor_7th_midi, root_midi};
    int chord_2nd_inversion[] = {augmented_5th_midi, minor_7th_midi, root_midi,
                                 major_3rd_midi};
    int chord_3rd_inversion[] = {minor_7th_midi, root_midi, major_3rd_midi,
                                 augmented_5th_midi};

    chord_t *chord1 = chord_analyzer(chord_root_position, 4, map);
    chord_t *chord2 = chord_analyzer(chord_1st_inversion, 4, map);
    chord_t *chord3 = chord_analyzer(chord_2nd_inversion, 4, map);
    chord_t *chord4 = chord_analyzer(chord_3rd_inversion, 4, map);

    char expected[20];
    char extract_root[3];
    extract_note_name(root, extract_root);
    sprintf(expected, "%saug7", extract_root);

    if (strcmp(chord1->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s + %s + %s\n", root, major_3rd,
               augmented_5th, minor_7th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord1->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord2->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s + %s\n", major_3rd, augmented_5th,
               minor_7th, root);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord2->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord3->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s + %s\n", augmented_5th, minor_7th,
               root, major_3rd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord3->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord4->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s + %s\n", minor_7th, root, major_3rd,
               augmented_5th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord4->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_aug_maj7(void) { test_aug_maj7_chord("C3", "E3", "G#3", "B3"); }
void test_Cs_aug_maj7(void) { test_aug_maj7_chord("C#3", "F3", "A3", "C4"); }
void test_D_aug_maj7(void) { test_aug_maj7_chord("D3", "F#3", "A#3", "C#4"); }
void test_Ds_aug_maj7(void) { test_aug_maj7_chord("D#3", "G3", "B3", "D4"); }
void test_E_aug_maj7(void) { test_aug_maj7_chord("E3", "G#3", "C4", "D#4"); }
void test_F_aug_maj7(void) { test_aug_maj7_chord("F3", "A3", "C#4", "E4"); }
void test_Fs_aug_maj7(void) { test_aug_maj7_chord("F#3", "A#3", "D4", "F4"); }
void test_G_aug_maj7(void) { test_aug_maj7_chord("G3", "B3", "D#4", "F#4"); }
void test_Gs_aug_maj7(void) { test_aug_maj7_chord("G#3", "C4", "E4", "G4"); }
void test_A_aug_maj7(void) { test_aug_maj7_chord("A3", "C#4", "F4", "G#4"); }
void test_As_aug_maj7(void) { test_aug_maj7_chord("A#3", "D4", "F#4", "A4"); }
void test_B_aug_maj7(void) { test_aug_maj7_chord("B3", "D#4", "G4", "A#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("aug7 Chords Test Suite", 0, 0);

    CU_add_test(pSuite, "C aug7", test_C_aug_maj7);
    CU_add_test(pSuite, "C# aug7", test_Cs_aug_maj7);
    CU_add_test(pSuite, "D aug7", test_D_aug_maj7);
    CU_add_test(pSuite, "D# aug7", test_Ds_aug_maj7);
    CU_add_test(pSuite, "E aug7", test_E_aug_maj7);
    CU_add_test(pSuite, "F aug7", test_F_aug_maj7);
    CU_add_test(pSuite, "F# aug7", test_Fs_aug_maj7);
    CU_add_test(pSuite, "G aug7", test_G_aug_maj7);
    CU_add_test(pSuite, "G# aug7", test_Gs_aug_maj7);
    CU_add_test(pSuite, "A aug7", test_A_aug_maj7);
    CU_add_test(pSuite, "A# aug7", test_As_aug_maj7);
    CU_add_test(pSuite, "B aug7", test_B_aug_maj7);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

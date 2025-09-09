#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_minor_triad_chord(char *root, char *minor_3rd, char *perfect_5th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int minor_3rd_midi = note_to_midi(minor_3rd);
    int perfect_5th_midi = note_to_midi(perfect_5th);

    int chord_root_position[] = {root_midi, minor_3rd_midi, perfect_5th_midi};
    int chord_1st_inversion[] = {minor_3rd_midi, perfect_5th_midi, root_midi};
    int chord_2nd_inversion[] = {perfect_5th_midi, root_midi, minor_3rd_midi};

    chord_t *chord1 = chord_analyzer(chord_root_position, 3, map);
    chord_t *chord2 = chord_analyzer(chord_1st_inversion, 3, map);
    chord_t *chord3 = chord_analyzer(chord_2nd_inversion, 3, map);

    char expected[20];
    char extract_root[3];
    extract_note_name(root, extract_root);
    sprintf(expected, "%sm", extract_root);

    if (strcmp(chord1->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s + %s\n", root, minor_3rd, perfect_5th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord1->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord2->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s\n", minor_3rd, perfect_5th, root);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord2->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord3->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s\n", perfect_5th, root, minor_3rd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord3->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_minor(void) { test_minor_triad_chord("C3", "D#3", "G3"); }
void test_Cs_minor(void) { test_minor_triad_chord("C#3", "E3", "G#3"); }
void test_D_minor(void) { test_minor_triad_chord("D3", "F3", "A3"); }
void test_Ds_minor(void) { test_minor_triad_chord("D#3", "F#3", "A#3"); }
void test_E_minor(void) { test_minor_triad_chord("E3", "G3", "B3"); }
void test_F_minor(void) { test_minor_triad_chord("F3", "G#3", "C4"); }
void test_Fs_minor(void) { test_minor_triad_chord("F#3", "A3", "C#4"); }
void test_G_minor(void) { test_minor_triad_chord("G3", "A#3", "D4"); }
void test_Gs_minor(void) { test_minor_triad_chord("G#3", "B3", "D#4"); }
void test_A_minor(void) { test_minor_triad_chord("A3", "C4", "E4"); }
void test_As_minor(void) { test_minor_triad_chord("A#3", "C#4", "F4"); }
void test_B_minor(void) { test_minor_triad_chord("B3", "D4", "F#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Minor Chords Test Suite", 0, 0);

    CU_add_test(pSuite, "Test C minor", test_C_minor);
    CU_add_test(pSuite, "Test C# minor", test_Cs_minor);
    CU_add_test(pSuite, "Test D minor", test_D_minor);
    CU_add_test(pSuite, "Test D# minor", test_Ds_minor);
    CU_add_test(pSuite, "Test E minor", test_E_minor);
    CU_add_test(pSuite, "Test F minor", test_F_minor);
    CU_add_test(pSuite, "Test F# minor", test_Fs_minor);
    CU_add_test(pSuite, "Test G minor", test_G_minor);
    CU_add_test(pSuite, "Test G# minor", test_Gs_minor);
    CU_add_test(pSuite, "Test A minor", test_A_minor);
    CU_add_test(pSuite, "Test A# minor", test_As_minor);
    CU_add_test(pSuite, "Test B minor", test_B_minor);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_sus4_chord(char *root, char *perfect_4th, char *perfect_5th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int perfect_4th_midi = note_to_midi(perfect_4th);
    int perfect_5th_midi = note_to_midi(perfect_5th);

    int chord_root_position[] = {root_midi, perfect_4th_midi, perfect_5th_midi};

    chord_t *chord = chord_analyzer(chord_root_position, 3, map);

    char expected[20];
    char extract_root[3];
    extract_note_name(root, extract_root);
    sprintf(expected, "%ssus4", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s + %s\n", root, perfect_4th, perfect_5th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_sus4(void) { test_sus4_chord("C3", "F3", "G3"); }
void test_Cs_sus4(void) { test_sus4_chord("C#3", "F#3", "G#3"); }
void test_D_sus4(void) { test_sus4_chord("D3", "G3", "A3"); }
void test_Ds_sus4(void) { test_sus4_chord("D#3", "G#3", "A#3"); }
void test_E_sus4(void) { test_sus4_chord("E3", "A3", "B3"); }
void test_F_sus4(void) { test_sus4_chord("F3", "A#3", "C4"); }
void test_Fs_sus4(void) { test_sus4_chord("F#3", "B3", "C#4"); }
void test_G_sus4(void) { test_sus4_chord("G3", "C4", "D4"); }
void test_Gs_sus4(void) { test_sus4_chord("G#3", "C#4", "D#4"); }
void test_A_sus4(void) { test_sus4_chord("A3", "D4", "E4"); }
void test_As_sus4(void) { test_sus4_chord("A#3", "D#4", "F4"); }
void test_B_sus4(void) { test_sus4_chord("B3", "E4", "F#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("sus4 Chords Test Suite", 0, 0);

    CU_add_test(pSuite, "C sus4", test_C_sus4);
    CU_add_test(pSuite, "C# sus4", test_Cs_sus4);
    CU_add_test(pSuite, "D sus4", test_D_sus4);
    CU_add_test(pSuite, "D# sus4", test_Ds_sus4);
    CU_add_test(pSuite, "E sus4", test_E_sus4);
    CU_add_test(pSuite, "F sus4", test_F_sus4);
    CU_add_test(pSuite, "F# sus4", test_Fs_sus4);
    CU_add_test(pSuite, "G sus4", test_G_sus4);
    CU_add_test(pSuite, "G# sus4", test_Gs_sus4);
    CU_add_test(pSuite, "A sus4", test_A_sus4);
    CU_add_test(pSuite, "A# sus4", test_As_sus4);
    CU_add_test(pSuite, "B sus4", test_B_sus4);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

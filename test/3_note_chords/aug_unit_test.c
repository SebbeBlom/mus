#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_aug_chord(char *root, char *major_3rd, char *augmented_5th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int major_3rd_midi = note_to_midi(major_3rd);
    int augmented_5th_midi = note_to_midi(augmented_5th);

    int chord_root_position[] = {root_midi, major_3rd_midi, augmented_5th_midi};

    chord_t *chord = chord_analyzer(chord_root_position, 3, map);

    char expected[20];
    char extract_root[3];
    extract_note_name(root, extract_root);
    sprintf(expected, "%saug", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s + %s\n", root, major_3rd, augmented_5th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_Caug(void) { test_aug_chord("C3", "E3", "G#3"); }
void test_Csaug(void) { test_aug_chord("C#3", "F3", "A3"); }
void test_Daug(void) { test_aug_chord("D3", "F#3", "A#3"); }
void test_Dsaug(void) { test_aug_chord("D#3", "G3", "B3"); }
void test_Eaug(void) { test_aug_chord("E3", "G#3", "C4"); }
void test_Faug(void) { test_aug_chord("F3", "A3", "C#4"); }
void test_Fsaug(void) { test_aug_chord("F#3", "A#3", "D4"); }
void test_Gaug(void) { test_aug_chord("G3", "B3", "D#4"); }
void test_Gsaug(void) { test_aug_chord("G#3", "C4", "E4"); }
void test_Aaug(void) { test_aug_chord("A3", "C#4", "F4"); }
void test_Asaug(void) { test_aug_chord("A#3", "D4", "F#4"); }
void test_Baug(void) { test_aug_chord("B3", "D#4", "G4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("aug Chords Test Suite", 0, 0);

    CU_add_test(pSuite, "C aug", test_Caug);
    CU_add_test(pSuite, "C# aug", test_Csaug);
    CU_add_test(pSuite, "D aug", test_Daug);
    CU_add_test(pSuite, "D# aug", test_Dsaug);
    CU_add_test(pSuite, "E aug", test_Eaug);
    CU_add_test(pSuite, "F aug", test_Faug);
    CU_add_test(pSuite, "F# aug", test_Fsaug);
    CU_add_test(pSuite, "G aug", test_Gaug);
    CU_add_test(pSuite, "G# aug", test_Gsaug);
    CU_add_test(pSuite, "A aug", test_Aaug);
    CU_add_test(pSuite, "A# aug", test_Asaug);
    CU_add_test(pSuite, "B aug", test_Baug);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

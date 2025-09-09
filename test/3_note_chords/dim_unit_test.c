#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_dim_triad_chord(char *root, char *minor_3rd, char *tritone) {
    HashMap *map = hash_map_create();
    populate_hash_map(map); 

    int root_midi = note_to_midi(root);
    int minor_3rd_midi = note_to_midi(minor_3rd);
    int tritone_midi = note_to_midi(tritone);

    int chord_root_position[] = {root_midi, minor_3rd_midi, tritone_midi};
    int chord_1st_inversion[] = {minor_3rd_midi, tritone_midi, root_midi};
    int chord_2nd_inversion[] = {tritone_midi, root_midi, minor_3rd_midi};

    chord_t *chord1 = chord_analyzer(chord_root_position, 3, map);
    chord_t *chord2 = chord_analyzer(chord_1st_inversion, 3, map);
    chord_t *chord3 = chord_analyzer(chord_2nd_inversion, 3, map);

    char expected[20];
    char extract_root[3];
    extract_note_name(root, extract_root);
    sprintf(expected, "%sdim", extract_root);

    if (strcmp(chord1->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s + %s\n", root, minor_3rd, tritone);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord1->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord2->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s\n", minor_3rd, tritone, root);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord2->to_string);
        CU_FAIL("Chord analysis failed");
    }

    if (strcmp(chord3->to_string, expected) != 0) {
        puts("");
        printf("Test failed: %s + %s + %s\n", tritone, root, minor_3rd);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord3->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_dim(void) { test_dim_triad_chord("C3", "D#3", "F#3"); }
void test_Cs_dim(void) { test_dim_triad_chord("C#3", "E3", "G3"); }
void test_D_dim(void) { test_dim_triad_chord("D3", "F3", "G#3"); }
void test_Ds_dim(void) { test_dim_triad_chord("D#3", "F#3", "A3"); }
void test_E_dim(void) { test_dim_triad_chord("E3", "G3", "A#3"); }
void test_F_dim(void) { test_dim_triad_chord("F3", "G#3", "B3"); }
void test_Fs_dim(void) { test_dim_triad_chord("F#3", "A3", "C4"); }
void test_G_dim(void) { test_dim_triad_chord("G3", "A#3", "C#4"); }
void test_Gs_dim(void) { test_dim_triad_chord("G#3", "B3", "D4"); }
void test_A_dim(void) { test_dim_triad_chord("A3", "C4", "D#4"); }
void test_As_dim(void) { test_dim_triad_chord("A#3", "C#4", "E4"); }
void test_B_dim(void) { test_dim_triad_chord("B3", "D4", "F4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Major Chords Test Suite", 0, 0);

    CU_add_test(pSuite, "C dim", test_C_dim);
    CU_add_test(pSuite, "C# dim", test_Cs_dim);
    CU_add_test(pSuite, "D dim", test_D_dim);
    CU_add_test(pSuite, "D# dim", test_Ds_dim);
    CU_add_test(pSuite, "E dim", test_E_dim);
    CU_add_test(pSuite, "F dim", test_F_dim);
    CU_add_test(pSuite, "F# dim", test_Fs_dim);
    CU_add_test(pSuite, "G dim", test_G_dim);
    CU_add_test(pSuite, "G# dim", test_Gs_dim);
    CU_add_test(pSuite, "A dim", test_A_dim);
    CU_add_test(pSuite, "A# dim", test_As_dim);
    CU_add_test(pSuite, "B dim", test_B_dim);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_P5(char *root, char *perfect_5th) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int perfect_5th_midi = note_to_midi(perfect_5th);

    int chord_root_position[] = {root_midi, perfect_5th_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s perfect 5th", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, perfect_5th);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_perfect_5th(void) { test_P5("C3", "G3"); }
void test_Cs_perfect_5th(void) { test_P5("C#3", "G#3"); }
void test_D_perfect_5th(void) { test_P5("D3", "A3"); }
void test_Ds_perfect_5th(void) { test_P5("D#3", "A#3"); }
void test_E_perfect_5th(void) { test_P5("E3", "B3"); }
void test_F_perfect_5th(void) { test_P5("F3", "C4"); }
void test_Fs_perfect_5th(void) { test_P5("F#3", "C#4"); }
void test_G_perfect_5th(void) { test_P5("G3", "D4"); }
void test_Gs_perfect_5th(void) { test_P5("G#3", "D#4"); }
void test_A_perfect_5th(void) { test_P5("A3", "E4"); }
void test_As_perfect_5th(void) { test_P5("A#3", "F4"); }
void test_B_perfect_5th(void) { test_P5("B3", "F#4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite =
        CU_add_suite("Perfect Fifth Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C 5", test_C_perfect_5th);
    CU_add_test(pSuite, "C# 5", test_Cs_perfect_5th);
    CU_add_test(pSuite, "D 5", test_D_perfect_5th);
    CU_add_test(pSuite, "D# 5", test_Ds_perfect_5th);
    CU_add_test(pSuite, "E 5", test_E_perfect_5th);
    CU_add_test(pSuite, "F 5", test_F_perfect_5th);
    CU_add_test(pSuite, "F# 5", test_Fs_perfect_5th);
    CU_add_test(pSuite, "G 5", test_G_perfect_5th);
    CU_add_test(pSuite, "G# 5", test_Gs_perfect_5th);
    CU_add_test(pSuite, "A 5", test_A_perfect_5th);
    CU_add_test(pSuite, "A# 5", test_As_perfect_5th);
    CU_add_test(pSuite, "B 5", test_B_perfect_5th);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

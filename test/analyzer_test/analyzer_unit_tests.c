#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_note_to_midi() {
    char *notes[] = {
        "C8",  "B7",  "A#7", "A7",  "G#7", "G7",  "F#7", "F7",  "E7",  "D#7",
        "D7",  "C#7", "C7",  "B6",  "A#6", "A6",  "G#6", "G6",  "F#6", "F6",
        "E6",  "D#6", "D6",  "C#6", "C6",  "B5",  "A#5", "A5",  "G#5", "G5",
        "F#5", "F5",  "E5",  "D#5", "D5",  "C#5", "C5",  "B4",  "A#4", "A4",
        "G#4", "G4",  "F#4", "F4",  "E4",  "D#4", "D4",  "C#4", "C4",  "B3",
        "A#3", "A3",  "G#3", "G3",  "F#3", "F3",  "E3",  "D#3", "D3",  "C#3",
        "C3",  "B2",  "A#2", "A2",  "G#2", "G2",  "F#2", "F2",  "E2",  "D#2",
        "D2",  "C#2", "C2",  "B1",  "A#1", "A1",  "G#1", "G1",  "F#1", "F1",
        "E1",  "D#1", "D1",  "C#1", "C1",  "B0",  "A#0", "A0",
    };

    int midi = 108;
    for (int i = 0; i < 88; i++) {
        if (midi != note_to_midi(notes[i])) {
            puts("");
            puts("");
            printf("Test failed: note_to_midi(%s)\n", notes[i]);
            printf("Expected: '%d'\n", midi);
            printf("Got:      '%d'", note_to_midi(notes[i]));
            CU_FAIL("Note to MIDI failed");
        }
        midi--;
    }
}

void test_midi_to_note() {
    char *notes[] = {
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#",
        "A", "A#", "B", "C"};

    int midi = 21;
    for (int i = 0; i < 88; i++) {
        if (strcmp(midi_to_note(midi), notes[i]) != 0) {
            puts("");
            puts("");
            printf("Test failed: midi_to_note(%d)\n", midi);
            printf("Expected: '%s'\n", notes[i]);
            printf("Got:      '%s'", midi_to_note(midi));
            CU_FAIL("MIDI to note failed");
        }
        midi++;
    }
}

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Helper functions", 0, 0);

    CU_add_test(pSuite, "note to midi", test_note_to_midi);
    CU_add_test(pSuite, "midi to note", test_midi_to_note);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

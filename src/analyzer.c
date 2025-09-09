#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chord_map.h"

int *remove_duplicate_notes(int *arr, int length) {
    int *result = (int *)malloc(length * sizeof(int));

    int unique_count = 0;

    for (int i = 0; i < length; ++i) {
        bool already_added = false;
        for (int j = 0; j < unique_count; j++) {
            if (arr[i] % 12 == result[j]) {
                already_added = true;
                break;
            }
        }

        if (!already_added) {
            result[unique_count++] = arr[i] % 12;
        }
    }

    result = (int *)realloc(result, unique_count * sizeof(int));

    return result;
}

int compare(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}

int *sort_midi(int *arr, int length) {
    int *result = (int *)malloc(length * sizeof(int));

    for (int i = 0; i < length; ++i) {
        result[i] = arr[i];
    }

    qsort(result, length, sizeof(int), compare);

    return result;
}

int *normalize_midi(int *sorted_arr, int length) {
    int *result = (int *)malloc(length * sizeof(int));
    int lowest_note = sorted_arr[0];

    for (int i = 0; i < length; ++i) {
        result[i] = sorted_arr[i] - lowest_note;
    }

    return result;
}

int *calculate_distances(int *arr, int length) {
    if (length < 2) {
        return NULL;
    }
    int *result = (int *)malloc((length - 1) * sizeof(int));

    for (int i = 0; i < length - 1; ++i) {
        result[i] = (arr[i + 1] - arr[i] + 12) % 12;
    }

    return result;
}

char *midi_to_note(int midi_value) {
    if (midi_value < 21 || midi_value > 108) {
        return NULL;
    }

    char *notes[] = {"C",  "C#", "D",  "D#", "E",  "F",
                     "F#", "G",  "G#", "A",  "A#", "B"};

    return notes[(midi_value - 12) % 12];
}

chord_t *chord_analyzer(int midi_notes[], int note_count, HashMap *map) {
    if (note_count < 1) {
        return NULL;
    }

    if (note_count == 1) {
        char *root_note = midi_to_note(midi_notes[0]);
        int octave = (midi_notes[0] / 12) - 1;
        chord_t *chord = chord_create(0, "", NULL, 0);
        char to_string[4];
        sprintf(to_string, "%s%d", root_note, octave);
        chord->to_string = strdup(to_string);
        return chord;
    }

    int *sorted_midi_notes = sort_midi(midi_notes, note_count);

    int *unique_midi_notes =
        remove_duplicate_notes(sorted_midi_notes, note_count);

    int *normalized_midi_notes = normalize_midi(unique_midi_notes, note_count);

    int *relations_array =
        calculate_distances(normalized_midi_notes, note_count);

    int relations_array_length = note_count - 1;

    chord_t *chord =
        hash_map_lookup(map, relations_array, relations_array_length);
    if (!chord) {
        return NULL;
    }

    int root_note_midi = sorted_midi_notes[chord->root_index];
    char *root_note = midi_to_note(root_note_midi);
    char to_string[30];
    sprintf(to_string, "%s%s", root_note, chord->quality);
    chord->to_string = strdup(to_string);
    chord->midi_notes = midi_notes;
    return chord;
}

#ifndef ANALYZER_H
#define ANALYZER_H

#include "chord_map.h"

chord_t *chord_analyzer(int midi_notes[], int note_count, HashMap *map);

char *midi_to_note(int midi_value);

#endif
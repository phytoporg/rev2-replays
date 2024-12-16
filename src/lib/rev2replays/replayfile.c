#include "replayfile.h"

#include <stdlib.h>
#include <stdio.h>

const char* replayfile_character_to_str(enum replayfile_character character) {
    switch (character) {
    case SOL:
        return "SOL";
    case KY:
        return "KY";
    case MAY:
        return "MAY";
    case MILLIA:
        return "MILLIA";
    case ZATO:
        return "ZATO";
    case POTEMKIN:
        return "POTEMKIN";
    case CHIPP:
        return "CHIPP";
    case FAUST:
        return "FAUST";
    case AXL:
        return "AXL";
    case VENOM:
        return "VENOM";
    case SLAYER:
        return "SLAYER";
    case INO:
        return "INO";
    case BEDMAN:
        return "BEDMAN";
    case RAMLETHAL:
        return "RAMLETHAL";
    case SIN:
        return "SIN";
    case ELPHELT:
        return "ELPHELT";
    case LEO:
        return "LEO";
    case JOHNNY:
        return "JOHNNY";
    case JACKO:
        return "JACKO";
    case JAM:
        return "JAM";
    case KUM:
        return "KUM";
    case RAVEN:
        return "RAVEN";
    case DIZZY:
        return "DIZZY";
    case BAIKEN:
        return "BAIKEN";
    case ANSWER:
        return "ANSWER";
    default:
        return "INVALID";
    };
}

struct replayfile_context* replayfile_create(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL)
    {
        return NULL;
    }

    // Replay files are fixed-length and should be REPLAYFILE_LEN.
    struct replayfile_context* context = (struct replayfile_context*)malloc(REPLAYFILE_LEN);
    if (context == NULL)
    {
        return NULL;
    }

    const size_t filesize = fread(context, 1, REPLAYFILE_LEN, file);
    // TODO: warn if filesize < REPLAYFILE_LEN, but don't fail
    // TODO: check magic against REPL

    fclose(file);
    return context;
}

void replayfile_destroy(struct replayfile_context* context) {
    free(context);
}

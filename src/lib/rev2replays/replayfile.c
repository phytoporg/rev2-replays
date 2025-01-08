#include "replayfile.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static uint32_t CRCTABLE[0x100] = { 0 };

void _replayfile_populate_crctable() 
{
    static bool initialized = false;
    if (initialized)
    {
        return;
    }

    const uint32_t generator = 0xEDB88320;
    const uint32_t count = sizeof(CRCTABLE) / sizeof(CRCTABLE[0]);
    for (uint32_t index = 0; index < count; ++index)
    {
        uint32_t entry = index;
        for (uint32_t bit = 0; bit < 8; ++bit)
        {
            if (entry & 1)
            {
                entry = (entry >> 1) ^ generator;
            }
            else
            {
                entry >>= 1;
            }
        }

        CRCTABLE[index] = entry;
    }
}

const char* replayfile_character_to_str(enum replayfile_character character) 
{
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

struct replayfile_context* replayfile_create(const char* path) 
{
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

void replayfile_destroy(struct replayfile_context* context) 
{
    free(context);
}

uint32_t replayfile_compute_crc32(struct replayfile_context* context)
{
    if (!context)
    {
        return 0;
    }

    _replayfile_populate_crctable();

    // TODO: header struct should only contain the first 0x10 bytes
    // Skip the header
    const uint8_t* buffer = (uint8_t*)(context) + 0x10;
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t index = 0; index < context->header.filesize; ++index)
    {
        const int q = (buffer[index] ^ crc) & 0xFF;
        crc = crc >> 8 ^ CRCTABLE[q];
    }

    return ~crc;
}

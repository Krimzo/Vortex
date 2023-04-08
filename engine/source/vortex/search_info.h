#pragma once

#include "klib.h"


struct search_info
{
    int depth = 0;
    uint64_t calls = 0;
    float time = 0.0f;
    float eval = 0.0f;

    search_info();
    ~search_info();
};

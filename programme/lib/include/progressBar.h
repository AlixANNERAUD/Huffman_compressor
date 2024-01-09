#pragma once

#include "common.h"

typedef struct {
    FileSize percentage, maximum;
    unsigned int nextShow;
    const char* message;
} ProgressBar;

ProgressBar progress_bar_create(FileSize maximum, const char* message);

void progress_bar_update(ProgressBar *progress_bar, FileSize current);
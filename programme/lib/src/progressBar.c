#include "progressBar.h"

#include <stdio.h>

ProgressBar progress_bar_create(FileSize maximum, const char *message)
{
    ProgressBar progressBar;
    progressBar.maximum = maximum;
    // - Calcul de l'intervalle de progression pour éviter d'afficher trop de fois la barre de progression
    progressBar.percentage = maximum / 100;
    progressBar.nextShow = progressBar.percentage;
    progressBar.message = message;
    return progressBar;
}

void progress_bar_update(ProgressBar *progressBar, FileSize current)
{
    if (current >= progressBar->nextShow)
    {
        printf("%s: %u%%\n", progressBar->message, (unsigned int)(current / progressBar->percentage));
        progressBar->nextShow += progressBar->percentage;
    }
}

#include "progressBar.h"

#include <stdio.h>

ProgressBar progress_bar_create(FileSize maximum, const char *message)
{
    assert(maximum >= 100);
    ProgressBar progressBar;
    progressBar.maximum = maximum;
    // - Calcul de l'intervalle de progression pour éviter d'afficher trop de fois la barre de progression
    progressBar.percentage = maximum / 100;
    progressBar.nextShow = 0;
    progressBar.message = message;
    return progressBar;
}

void progress_bar_update(ProgressBar *progressBar, FileSize current)
{
    if (current >= progressBar->nextShow)
    {
        printf("%s: [", progressBar->message);
        for (unsigned i = 0; i < 20; i++)
            printf(i < current / (progressBar->percentage * 5) ? "#" : " ");
        printf("] - %lu%%\r", current / progressBar->percentage);

        progressBar->nextShow += progressBar->percentage;
    
        fflush(stdout); // Force l'affichage
    }
}

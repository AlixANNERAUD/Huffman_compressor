#pragma once

#include "common.h"

/// @brief Structure représentant une barre de progression.
typedef struct {
    /// @brief Pourcentage de progression de la barre.
    FileSize percentage;
    /// @brief Maximum de la barre.
    FileSize maximum;
    /// @brief Prochaine valeur à partir de laquelle la barre sera actualisée (pour éviter de l'afficher trop souvent).
    unsigned int nextShow;
    /// @brief Message à afficher avant la barre.
    const char* message;
} ProgressBar;

/// @brief Fonction créant une barre de progression.
/// @param maximum Valeur maximale de la barre.
/// @param message Message à afficher avant la barre.
/// @return La barre de progression.
ProgressBar progress_bar_create(FileSize maximum, const char* message);

/// @brief Fonction mettant à jour la barre de progression.
/// @param progress_bar Barre de progression à mettre à jour.
/// @param current Valeur courante de la progression.
void progress_bar_update(ProgressBar *progress_bar, FileSize current);
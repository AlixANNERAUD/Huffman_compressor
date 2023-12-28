#pragma once

#include "bit.h"

/// @brief Type Byte qui est un unsigned char (valeur variant de 0 à 255)
typedef unsigned char Byte;

/// @brief Crée un Byte à partir d'un naturel
/// @param natural Le naturel à convertir en Byte
/// @return Le résultat de la conversion de type Byte
Byte byte_create(unsigned int natural);

/// @brief Convertit un Byte en naturel 
/// @param byte Le Byte à convertir en naturel
/// @return Le résultat de la conversion qui est un naturel
unsigned int byte_to_natural(Byte byte);

/// @brief Définir le Bit d'un Byte à la position donnée
/// @param byte Le Byte à modifier
/// @param position La position du Byte où la modification aura lieu
/// @param bit Le Bit à mettre à la position désirée
void byte_set_bit(Byte* byte, unsigned int position, Bit bit);

/// @brief Obtenir le Bit d'un Byte à la position donnée
/// @param byte Le Byte à enquêter
/// @param position La position du Byte où l'enquête aura lieu
/// @return Le Bit d'un Byte à la position donnée
Bit byte_get_bit(Byte byte, unsigned int position);

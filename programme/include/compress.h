#pragma once

#include "common.h"
#include "compress.h"
#include "statistics.h"
#include "huffmanTree.h"
#include "codingTable.h"
#include "binaryCode.h"
#include <stdio.h>

bool compress(FILE *in, FILE *out);


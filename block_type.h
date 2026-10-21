#pragma once
#include <raylib.h>

typedef enum {
	GRASS         = 0,
	DIRT          = 1,
	STONE         = 2,
	GOLD_ORE      = 3,
	IRON_ORE      = 4,
	COAL_ORE      = 5,
	DIAMOND_ORE   = 6,
	NETHERITE_ORE = 7,
	BEDROCK       = 8,
} Block_Type;

const int BLOCK_TYPE_DURABILITY[] = {
	10, // GRASS
	10, // DIRT
	20, // STONE
	30, // GOLD_ORE
	30, // IRON_ORE
	35, // COAL_ORE
	40, // DIAMOND_ORE
	50, // NETHERITE_ORE
	-1, // BEDROCK
};

const int BLOCK_TYPE_WEIGHT[] = {
	0,  // GRASS
	0,  // DIRT
	60, // STONE
	20, // GOLD_ORE
	20, // IRON_ORE
	30, // COAL_ORE
	5, // DIAMOND_ORE
	1, // NETHERITE_ORE
	0, // BEDROCK
};

const Color BLOCK_TYPE_COLORS[9] = {
	GREEN,  // GRASS
	BROWN,  // DIRT
	GRAY, // STONE
	GOLD, // GOLD_ORE
	PINK, // IRON_ORE
	BLACK, // COAL_ORE
	SKYBLUE, // DIAMOND_ORE
	WHITE, // NETHERITE_ORE
	RAYWHITE, // BEDROCK
};



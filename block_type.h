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
};

static char* BLOCK_TYPE_IMGS[] = {
	"./assets/grass.png",  // GRASS
	"./assets/dirt.png",  // DIRT
	"./assets/stone.png", // STONE
	"./assets/gold_ore.png", // GOLD_ORE
	"./assets/iron_ore.png", // IRON_ORE
	"./assets/coal_ore.png", // COAL_ORE
	"./assets/diamond_ore.png", // DIAMOND_ORE
	"./assets/ancient_debris.png", // NETHERITE_ORE
};



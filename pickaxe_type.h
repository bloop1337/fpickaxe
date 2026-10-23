#pragma once

typedef enum {	
	WOODEN_PICKAXE  = 0, 
	STONE_PICKAXE   = 1,
	IRON_PICKAXE    = 2,
	DIAMOND_PICKAXE = 3,
} Pickaxe_Type;

static const int PICKAXE_DURABILITY[] = {
	20,
	30,
	50,
	100,
};

static const char* PICKAXE_IMGS[] = {
	"./assets/wooden_pickaxe.png",
	"./assets/stone_pickaxe.png",
	"./assets/iron_pickaxe.png",
	"./assets/diamond_pickaxe.png",
};

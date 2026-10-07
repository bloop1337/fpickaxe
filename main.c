#include <raylib.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 0.3


#define BLOCK_SIZE 100
#define BLOCK_COLS (WIDTH / BLOCK_SIZE) // 8

const int BLOCK_TYPE_DURABILITY[9] = {
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


const int BLOCK_TYPE_CHANCE[9] = {
	0,  // GRASS
	0,  // DIRT
	60, // STONE
	10, // GOLD_ORE
	10, // IRON_ORE
	14, // COAL_ORE
	5, // DIAMOND_ORE
	1, // NETHERITE_ORE
	-1, // BEDROCK
};


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
} BlockType;

typedef struct {
	Rectangle hitbox;
	Vector2 vel;
} Pickaxe;

typedef struct {
	Rectangle hitbox;
	int durability;	
	BlockType type;
	Color color;
} Block;


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

typedef struct {
	Block* blocks;

	int width;
	int height;
} Level;

void init_pickaxe(Pickaxe* pick) {
	*pick = (Pickaxe){
		.hitbox = (Rectangle){ .x = (int)(WIDTH / 2) - 50, .y = 100, .width = 100, .height = 100 },
		.vel = (Vector2){ .x = 0, .y = 0},
	};
}

void init_level(Level* level) {
	int height = 20;
	int len = BLOCK_COLS*height;

	Block* blocks = malloc(sizeof(Block) * len);

	// GRASS GENERATION
	for (int grass = 0; grass < BLOCK_COLS; ++grass) {
		blocks[grass] = (Block){
			.hitbox = (Rectangle){.x = grass*BLOCK_SIZE, .y = 300, .width = BLOCK_SIZE, .height = BLOCK_SIZE },
			.durability = BLOCK_TYPE_DURABILITY[GRASS],
			.type = GRASS,
			.color = GREEN,
		};
	}

	// DIRT GENERATION
	// 				8					// 24
	int dirt_rows = 3;
	int dirt_blocks = BLOCK_COLS*(dirt_rows+1);

	int dirt_row_counter = 0;
	int dirt_col_counter = 1;
	for (int dirt = BLOCK_COLS; dirt < dirt_blocks; dirt++) {
		blocks[dirt] = (Block){		
			.hitbox = (Rectangle){ .x = BLOCK_SIZE*dirt_row_counter, .y = 300 + (BLOCK_SIZE*dirt_col_counter), .width = BLOCK_SIZE, .height = BLOCK_SIZE },
			.durability = BLOCK_TYPE_DURABILITY[DIRT],
			.type = DIRT,
			.color = BROWN,
		};
		dirt_row_counter++;	
		if (dirt_row_counter == BLOCK_COLS) {
			dirt_row_counter = 0;
			dirt_col_counter++;
		}
	}
	// EVERYTHING ELSE GENERATION
	
	int row_counter = 0;
	int col_counter = dirt_col_counter;
//		 24			              160
	
	BlockType type = STONE;
	for (int i = dirt_blocks; i < len; ++i) {
		blocks[i] = (Block){		
			.hitbox = (Rectangle){ .x = BLOCK_SIZE*row_counter, .y = 300 + (BLOCK_SIZE*col_counter), .width = BLOCK_SIZE, .height = BLOCK_SIZE },
			.durability = BLOCK_TYPE_DURABILITY[type],
			.type = type,
			.color = BLOCK_TYPE_COLORS[STONE],
		};


		row_counter++;	
		if (row_counter == BLOCK_COLS) {
			row_counter = 0;
			col_counter++;
		}
	}

	*level = (Level){
		.blocks = blocks,
		.width = BLOCK_COLS,
		.height = height,
	};
}

void draw_pickaxe(Pickaxe* pick, bool hitbox) {

	if (hitbox)
		DrawRectangleLinesEx(pick->hitbox, 5, RED);
}

void draw_block(Block* block, bool hitbox) {
	
	DrawRectangleRec(block->hitbox, block->color);
	if (hitbox)
		DrawRectangleLinesEx(block->hitbox, 5, RED);
}

void draw_level(Level* level, bool hitbox) {
	for (int i = 0; i < level->width*level->height; ++i) {
		draw_block(&level->blocks[i], hitbox);
	}
}

void update_pickaxe(Pickaxe* pick, Level* level) {
	pick->vel.y += GRAVITY;
	
	
	bool is_collide = false;
	for (int i = 0; i < level->width*level->height; ++i) {
		if (CheckCollisionRecs(pick->hitbox, level->blocks[i].hitbox)) {
			is_collide = true;
			break;
		}
	}
	
	if (!is_collide) {
		pick->hitbox.y += pick->vel.y;
		pick->hitbox.x += pick->vel.x;
	} 	
}


int main(void) {
	InitWindow(WIDTH, HEIGHT, "Falling pickaxe");
	SetTargetFPS(60);
	
	Level level = {0};
	init_level(&level);

	Pickaxe pickaxe = {0};
	init_pickaxe(&pickaxe);

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLUE);
			update_pickaxe(&pickaxe, &level);
			draw_pickaxe(&pickaxe, true);
			draw_level(&level, false);
		EndDrawing();
	}


	CloseWindow();
	return 0;
}

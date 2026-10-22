#include <stdlib.h>
#include "block_type.h"

#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 0.3
#define FORCE GRAVITY * 100

#define BLOCK_SIZE 100
#define BLOCK_COLS (WIDTH / BLOCK_SIZE)

typedef struct {
	Rectangle hitbox;
	Vector2 vel;
} Pickaxe;

typedef struct {
	Rectangle hitbox;
	int durability;	
	Block_Type type;
	Texture2D texture;
} Block;

typedef struct {
	Block* blocks;

	int width;
	int height;
} Level;

static void init_pickaxe(Pickaxe* pick) {
	*pick = (Pickaxe){
		.hitbox = (Rectangle){ .x = (int)(WIDTH / 2) - 50, .y = 100, .width = 100, .height = 100 },
		.vel = (Vector2){ .x = 0, .y = 0},
	};
}

static Block_Type random_block_type() {
	int sum = 0; for (size_t i = 0; i < sizeof(BLOCK_TYPE_WEIGHT) / sizeof(int); ++i) sum+=BLOCK_TYPE_WEIGHT[i];

	int att = arc4random() % sum;
	for (size_t i = 0; i < sizeof(BLOCK_TYPE_WEIGHT) / sizeof(int); ++i) {
		if (att < BLOCK_TYPE_WEIGHT[i])
			return (Block_Type)i;
		att -= BLOCK_TYPE_WEIGHT[i];
	}
	
	return (Block_Type)0;
}


void render_block_durability(Block* block) {
	if (block->durability <= 0)
		return;
	
	DrawRectangle(block->hitbox.x, block->hitbox.y, BLOCK_SIZE, BLOCK_SIZE/4, BLACK);
}

static void init_level(Level* level, const int leveln) {
	const int height = 20 + leveln;
	const int len = BLOCK_COLS*height;

	Block* blocks = malloc(sizeof(Block) * len);
	

	Image img_grass = LoadImage(BLOCK_TYPE_IMGS[GRASS]);
	ImageResizeNN(&img_grass, BLOCK_SIZE, BLOCK_SIZE);
	Texture texture_grass = LoadTextureFromImage(img_grass);
	// GRASS GENERATION
	
	for (int grass = 0; grass < BLOCK_COLS; ++grass) {
		blocks[grass] = (Block){
			.hitbox = (Rectangle){.x = grass*BLOCK_SIZE, .y = 300, .width = BLOCK_SIZE, .height = BLOCK_SIZE },
			.durability = BLOCK_TYPE_DURABILITY[GRASS],
			.type = GRASS,
			.texture = texture_grass,
		};
	}

	int dirt_rows = 3;
	int dirt_blocks = BLOCK_COLS*(dirt_rows+1);

	int dirt_row_counter = 0;
	int dirt_col_counter = 1;

	Image img_dirt = LoadImage(BLOCK_TYPE_IMGS[DIRT]);
	ImageResizeNN(&img_dirt, BLOCK_SIZE, BLOCK_SIZE);
	Texture texture_dirt = LoadTextureFromImage(img_dirt);
	
	// DIRT GENERATION
	for (int dirt = BLOCK_COLS; dirt < dirt_blocks; dirt++) {
		blocks[dirt] = (Block){		
			.hitbox = (Rectangle){ .x = BLOCK_SIZE*dirt_row_counter, .y = 300 + (BLOCK_SIZE*dirt_col_counter), .width = BLOCK_SIZE, .height = BLOCK_SIZE },
			.durability = BLOCK_TYPE_DURABILITY[DIRT],
			.type = DIRT,
			.texture = texture_dirt,
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
	
	for (int i = dirt_blocks; i < len; ++i) {
		Block_Type type = random_block_type();
		Image img = LoadImage(BLOCK_TYPE_IMGS[type]);
		ImageResizeNN(&img, BLOCK_SIZE, BLOCK_SIZE);
		Texture2D block_texture = LoadTextureFromImage(img);
		blocks[i] = (Block){		
			.hitbox = (Rectangle){ .x = BLOCK_SIZE*row_counter, .y = 300 + (BLOCK_SIZE*col_counter), .width = BLOCK_SIZE, .height = BLOCK_SIZE },
			.durability = BLOCK_TYPE_DURABILITY[type],
			.type = type,
			.texture = block_texture, 
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

static void destroy_level(Level *level) {
	if (level->blocks != NULL) {
		free(level->blocks);
		level->blocks = NULL;
	}
	level->width  = 0;
	level->height = 0;
}

static void draw_pickaxe(Pickaxe* pick, bool hitbox) {
	if (hitbox)
		DrawRectangleLinesEx(pick->hitbox, 5, RED);
}

static void draw_block(Block* block, bool hitbox) {
	DrawTexture(block->texture, block->hitbox.x, block->hitbox.y, WHITE);
	if (hitbox)
		DrawRectangleLinesEx(block->hitbox, 5, RED);
}

static void draw_level(Level* level, bool hitbox) {
	for (int i = 0; i < level->width*level->height; ++i) {
		draw_block(&level->blocks[i], hitbox);
	}
}

static void update_pickaxe(Pickaxe* pick, Level* level, Camera2D *camera) {
	pick->vel.y += GRAVITY;
		
	bool is_collide = false;
	for (int i = 0; i < level->width*level->height; ++i) {
		if (CheckCollisionRecs(pick->hitbox, level->blocks[i].hitbox)) {
			is_collide = true;
			render_block_durability(&level->blocks[i]);

			//level->blocks[i] = (Block){0};
			break;
		}
	}
	
	if (is_collide) {
		pick->vel.y = -GRAVITY * FORCE;
		pick->vel.x = GetRandomValue(-2, 2);
	}

	pick->hitbox.y += pick->vel.y;
	pick->hitbox.x += pick->vel.x;

	camera->target.y = pick->hitbox.y + pick->hitbox.height / 2;	
	camera->target.x = WIDTH / 2;
}


int main(void) {
	InitWindow(WIDTH, HEIGHT, "Falling pickaxe");
	SetTargetFPS(60);
	
	Level level = {0};
	init_level(&level, 1);
	
	Pickaxe pickaxe = {0};
	init_pickaxe(&pickaxe);

	Camera2D camera = (Camera2D) {
		.offset  = (Vector2) { .x = GetRenderWidth() / 2.0f, .y = GetRenderHeight() / 2.0f},
    	.target  = (Vector2) { .x = pickaxe.hitbox.x, .y = pickaxe.hitbox.y },
    	.rotation = 0,
    	.zoom     = 1.0f, 
	};

	while (!WindowShouldClose()) {
		BeginDrawing();

			ClearBackground(BLUE);

				BeginMode2D(camera);
					draw_level(&level, false);
					draw_pickaxe(&pickaxe, true);
				EndMode2D();

			update_pickaxe(&pickaxe, &level, &camera);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

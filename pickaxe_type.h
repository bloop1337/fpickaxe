// Copyright (C) 2026 bloop
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-2.0

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

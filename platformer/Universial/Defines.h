#pragma once
enum class Direction
{
	Left,
	Right,
	None
};

enum class SceneId
{
	None = -1,
	Title,
	Menu,
	Char1,
	Char2,
	Game1,
	Game2,
	Count
};

enum class ResourceTypes
{
	Texture,
	Font,
	Sound,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

#define SCREEN_WIDTH 1280;
#define SCREEN_HEIGHT 720;
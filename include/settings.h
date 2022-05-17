#pragma once

#include <raylib.h>


//	Constant list of the mine storm




//----------------------------------DISPLAY----------------------------------//

//	Window dimension:

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 800

#define UI_PADDING 40
//	FPS

#define DEFAULT_FPS 60

//-----------------------------------ENUM-----------------------------------//

enum DisplayType
{
	D_MAIN_MENU,
	D_IN_GAME,
	D_PAUSE,
	D_GAME_OVER,
	D_INTER_ROUND,

	D_COUNT
};

//
enum TextureList
{
	T_BACKGROUND,
	T_FOREGROUND,
	T_SPRITE,

	T_COUNT
};

enum SoundList
{
	S_MUSIC,
	S_AMBIENT,
	S_SHOOT,
	S_PROPULSION,
	S_TELEPORTATION,
	S_EXPLOSION,
	S_SPAWN,
	S_MINELAYER,

	S_COUNT
};

enum ColliderType
{
	C_CIRCLE,
	C_POLYGON,
	C_MULTIPOLYGONE
};

enum EffectType
{
	FX_EXPLOSION,
	FX_TELEPORTATION,
	FX_PROPULSION,
	FX_BACKGROUND,

	FX_COUNT
};
//----------------------------------INPUTS----------------------------------//


#define PAUSE_INPUT KEY_SPACE
#define DEBUG_INPUT KEY_C
#define LEAVE_INPUT KEY_Q



#define MAX_PLAYER	2
struct PlayersInput
{
	int forward[MAX_PLAYER] = { KEY_R , KEY_I };
	int turn_left[MAX_PLAYER] = { KEY_G , KEY_L };
	int turn_right[MAX_PLAYER] = { KEY_D , KEY_J };
	int shoot[MAX_PLAYER] = { KEY_F , KEY_K };
	int teleport1[MAX_PLAYER] = { KEY_E , KEY_U };
	int teleport2[MAX_PLAYER] = { KEY_T , KEY_O };
};

//----------------------------------PLAYER----------------------------------//



#define PLAYER_DIPLACEMENT_SPEED	10.f
#define PLAYER_ROTATION_SPEED		200.f
#define PLAYER_DRAG					.02f
#define DRIFT						0.1f
#define PLAYER_WIDTH				96
#define PLAYER_HEIGHT				96

#define PLAYER_ONE_X				280
#define PLAYER_ONE_Y				400

#define PLAYER_TWO_X				360
#define PLAYER_TWO_Y				400



#define PLAYER_CADENCE				.1f



//----------------------------------BULLET----------------------------------//

enum BulletType
{
	B_PLAYER_BULLET,
	B_FIREBALL
};
	
#define PLAYER_BULLET_SPEED		750.f
#define PLAYER_BULLET_AGE		5.f		//	Max Age
#define PLAYER_BULLET_SIZE		75.f


#define FIREBALL_SPEED			75.f
#define FIREBALL_AGE			50.f	//	Max Age
#define FIREBALL_SIZE			128.f
#define FIREBALL_SCORE			110

#define BULLET_AGING			10.f	//	Aging speed

//----------------------------------ENEMIES----------------------------------//

enum MineType
{
	M_FLOATING,
	M_FIREBALL,
	M_MAGNETIC,
	M_MAGNETIC_FIREBALL,

	M_COUNT
};

enum MineSize
{
	SI_BIG,
	SI_MEDIUM,
	SI_SMALL,

	SI_COUNT
};

//Dimensions
#define SIZE_BIG		192
#define SIZE_MEDIUM		128
#define SIZE_SMALL		64

//Speeds
#define GREAT_SPEED		75.f
#define MEDIUM_SPEED	50.f
#define SLOW_SPEED		25.f

//Scores
#define BIG_FLOATING_MINE_SCORE			100
#define MEDIUM_FLOATING_MINE_SCORE		135
#define SMALL_FLOATING_MINE_SCORE		200

#define BIG_FIREBALL_MINE_SCORE			325
#define MEDIUM_FIREBALL_MINE_SCORE		360
#define SMALL_FIREBALL_MINE_SCORE		425

#define BIG_MAGNETIC_MINE_SCORE			500
#define MEDIUM_MAGNETIC_MINE_SCORE		535
#define SMALL_MAGNETIC_MINE_SCORE		600

#define BIG_MAGNETIC_FIREBALL_MINE_SCORE		750
#define MEDIUM_MAGNETIC_FIREBALL_MINE_SCORE		585
#define SMALL_MAGNETIC_FIREBALL_MINE_SCORE		850

#define MINELAYER_SCORE		1000
#define MINELAYER_SPEED	200.f

//Spawns
#define SPAWN_ACCEPTANCE_RADIUS 5.f
#define SPAWNER_SPEED	100.f
#define SPAWN_POINT_SPEED	100.f

#define SPAWN_SIZE	32
#define MIN_SPAWN	14
#define WAVE_TIMER_LIMIT	5.f


//--------------------------------PARTICLES--------------------------------//
#define PARTICLE_AGING 5.f


//----------------------------------ROUND----------------------------------//

#define START_ROUND 1

static int round_data[10][4]
{
	//		  ROUND
	//  |0-10|-20|-30|
		{ 0, 0, 0, 0 },	// 0
		{ 1, 0, 0, 1 },	// 1 
		{ 2, 0, 0, 2 },	// 2
		{ 3, 0, 0, 3 },	// 3
		{ 1, 1, 1, 1 },	// 4
		{ 2, 1, 1, 2 },	// 5
		{ 3, 1, 1, 3 },	// 6
		{ 2, 2, 2, 1 },	// 7
		{ 3, 2, 2, 2 },	// 8
		{ 3, 3, 3, 3 }	// 9
};

//Color of the stars in the background
//It depends on the round number
static Color RoundColor[10]
{
	DARKBLUE,
	BLUE,
	GREEN,
	WHITE,
	YELLOW,
	GOLD,
	ORANGE,
	RED,
	PINK,
	PURPLE,
};
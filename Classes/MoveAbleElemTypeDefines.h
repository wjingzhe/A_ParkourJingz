#pragma once

#define EMPTY 0
#define OBSTACLE__ID              (1)
#define COIN_TYPE_ID              (1<<1)
#define PLAYER_TYPE_ID            (1<<2)
#define MOVE_ABLE_ELEM_TYPE_ID     OBSTACLE__ID | COIN_TYPE_ID | PLAYER_TYPE_ID
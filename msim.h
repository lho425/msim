//This code is public domain.


extern const int flag_print_on_move ;
extern const int flag_print_on_turn ;

//msim_setOptions(flag_draw_on_move | flag_draw_on_turn);
//という感じで論理和を入れる
void msim_setOptions(int flags);

void msim_printMap();

//void setMyWallData();


/********** マウス視点の関数達 *************/
//マウスから見た向きを基準にした方向
enum msim_Direction { front, right, back, left };

//現在のマウスの座標で、マウスの向きを基準にして右とか正面とかに壁があるか見る関数
int msim_existsWallAt(enum msim_Direction d);

void msim_turnMouseTo(enum msim_Direction d);

int msim_moveMouseToFront();

/*******************************************/



/****** 神の視点の関数達(使いづらい、要望がなければ将来廃止される予定) *******/
enum msim_CompassDirection { north, east, south, west };

void msim_turnMouseToCompassDirection(enum msim_CompassDirection d);

int msim_existsWestWall(unsigned int x, unsigned int y);

int msim_existsSouthWall(unsigned int x, unsigned int y);

int msim_existsEastWall(unsigned int x, unsigned int y);

int msim_existsNorthWall(unsigned int x, unsigned int y);

int msim_existsWall(int x, int y, enum msim_CompassDirection d);

/*******************************************/



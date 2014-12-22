//This code is public domain.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msim.h"

//const unsigned int map_size = 16;
#define map_size 16
static char map_data[map_size][map_size];
//フォーマット
//0,...,西壁,南壁

static struct {
  unsigned int x;
  unsigned int y;
  int isCrashed;
  enum msim_CompassDirection mouse_direction;
} mouse_zahyo = {0,0,0,north};//dirty!!! 座標という名前なのに方角とかの情報も入っている

static int _flags = 0;

const int flag_no_option = 0;
const int flag_print_on_move = 1<<0;
const int flag_print_on_turn = 1<<1;

void msim_setOptions(int flags){
  _flags = flags;
}

//座標が迷路の中にあるかチェックする関数
int isInMap(unsigned int x, unsigned int y){
  return (0 <= x) && (x < map_size) && (0 <= y) && (y < map_size);
    
}

enum msim_CompassDirection msim_addCompassDirectionAndDirection(enum msim_CompassDirection cd, enum msim_Direction d){
  return (cd + d) % 4;
}

/***** 壁設定系関数 *****/

void msim_setWestWall(unsigned int x, unsigned int y,int existsWall){
  if( ! isInMap(x,y) ){
    return;
  }
  
  if(existsWall){
    map_data[x][y] |= 2;
  }else{
    map_data[x][y] &= ~2;
  }
}

void msim_setSouthWall(unsigned int x, unsigned int y,int existsWall){
  if( ! isInMap(x,y) ){
    return;
  }

  if(existsWall){
    map_data[x][y] |= 1;
  }else{
    map_data[x][y] &= ~1;
  }
}
void msim_setNorthWall(unsigned int x, unsigned int y,int existsWall){
    msim_setSouthWall(x, y+1, existsWall);
}

void msim_setEastWall(unsigned int x, unsigned int y,int existsWall){
    msim_setWestWall(x+1, y, existsWall);
}



  

/***** 壁存在判定系関数 *****/

int msim_existsWestWall(unsigned int x, unsigned int y){
  if( ! isInMap(x,y) ){
    return 1;//!!!あやしい (16,0)とかの壁が
  }

  return map_data[x][y] & 2; //0b00000010
}

int msim_existsSouthWall(unsigned int x, unsigned int y){
  if( ! isInMap(x,y) ){
    return 1;
  }
  return map_data[x][y] & 1;//0b00000001
}


int msim_existsEastWall(unsigned int x, unsigned int y){
  return msim_existsWestWall(x+1, y);
}

int msim_existsNorthWall(unsigned int x, unsigned int y){
  return msim_existsSouthWall(x, y+1);
}

int msim_existsWall(int x, int y, enum msim_CompassDirection d){
  switch(d){
  case north:
    return msim_existsNorthWall(x,y);
  case west:
    return msim_existsWestWall(x,y);
  case east:
    return msim_existsEastWall(x,y);
  case south:
    return msim_existsSouthWall(x,y);
  default:
    return 1;
    //abort();
  }
}
  
//現在のマウスの座標で、マウスの向きを基準にして右とか正面とかに壁があるか見る関数
int msim_existsWallAt(enum msim_Direction d){

  return msim_existsWall(mouse_zahyo.x, mouse_zahyo.y, msim_addCompassDirectionAndDirection(mouse_zahyo.mouse_direction, d));
}





/***** 移動系関数 *****/

void msim_turnMouseToCompassDirection(enum msim_CompassDirection d) {
if ( ! mouse_zahyo.isCrashed){
    mouse_zahyo.mouse_direction = d;
  }
  
  if(_flags & flag_print_on_turn){
    msim_printMap();
  }
}

void msim_turnMouseTo(enum msim_Direction d) {
  msim_turnMouseToCompassDirection( msim_addCompassDirectionAndDirection(mouse_zahyo.mouse_direction, d) );

}


int msim_moveMouseToFront(){

  int isOK;
  if (mouse_zahyo.isCrashed){
    isOK = 0;
  }else if(msim_existsWall(mouse_zahyo.x, mouse_zahyo.y, mouse_zahyo.mouse_direction)){
    mouse_zahyo.isCrashed = 1;
    isOK = 0;

  }else{
    switch(mouse_zahyo.mouse_direction){
    case north:
      mouse_zahyo.y++;
      break;
    case west:
      mouse_zahyo.x--;
      break;
    case east:
      mouse_zahyo.x++;
      break;
    case south:
      mouse_zahyo.y--;
      break;
    default:
      break;
      //abort();
    }


    isOK = 1;
  }

  if(_flags & flag_print_on_move){
    msim_printMap();
  }
      
  return isOK;
}





/****** 描画系関数 ******/

void msim_printWestWall(){
  printf("|");
}
void msim_printWestWallEmpty(){
  printf(" ");  
}

void msim_printEmptyBox(){
  printf("   ");
}

void msim_printHasira(){
  printf("+");
}

void msim_printSouthWall(){
  printf("---");
}
void msim_printSouthWallEmpty(){
    printf("   ");
}

void msim_printNewLine(){
  printf("\n");
}

void msim_printMouse() {
  if (mouse_zahyo.isCrashed) {
    printf("\e[31m");
    switch (mouse_zahyo.mouse_direction) {
    case north:
      printf("AXA");
      break;
    case west:
      printf("<X<");
      break;
    case east:
      printf(">X>");
      break;
    case south:
      printf("VXV");
      break;
    default:
      break;
      //abort();
    }
    printf("\e[m");
  }else{
    switch (mouse_zahyo.mouse_direction) {
    case north:
      printf(" A ");
      break;
    case west:
      printf("<< ");
      break;
    case east:
      printf(" >>");
      break;
    case south:
      printf(" V ");
      break;
    default:
      break;
      //abort();
    }

  }
}

void msim_printMap(){
  int x,y;
  for(y=0;y<map_size;y++){//一番上の壁描画
    msim_printHasira();
    msim_printSouthWall();

  }
  msim_printHasira();
  msim_printNewLine();
  

  for(y=map_size-1;y>=0;y--){
    //y行目の西壁描画
    for(x=0;x<map_size;x++){

      if(msim_existsWestWall(x,y)){
	msim_printWestWall();
      }
      else{
	msim_printWestWallEmpty();
      }
      
      if(mouse_zahyo.x == x && mouse_zahyo.y == y){
        msim_printMouse();
      }
      else{
	msim_printEmptyBox();
      }
    }
    msim_printWestWall();//最東端の壁を描画
    msim_printNewLine();
    
    //y行目の南壁描画
    for(x=0;x<map_size;x++){
      msim_printHasira();
      if(msim_existsSouthWall(x,y)){
	msim_printSouthWall();
      }else{
	msim_printSouthWallEmpty();
      }
    }
    msim_printHasira();
    msim_printNewLine();
  }
  
  //printf("\n");
}




#if 0 //C言語で実装されたマップデータの変換器は実装がわかりにくいのでもはや保守しない

#define MSIM_STATUS int
// #define MSIM_FAILED 1以外のすべての数
#define MSIM_SUCCESSED 1

//return int isSuccessed
MSIM_STATUS msim_loadMapDataFromFile(char filename[]){
  int x = 0;
  int y = map_size - 1;
  const int max_char_num_in_line = 4*16+1+10;//"+---" * 16 + "+" + 改行＆null文字＆予備
  char map_line[max_char_num_in_line];
  FILE *map_file;
  if ( (map_file = fopen(filename, "r") )== NULL ){
    printf("fopen err\n");
    return -1;
  }

  /*** ここまで前処理 ***/
  
  //途中でEOFだったり、迷路データが不正だったときの対応はまだ考えてない
  fgets(map_line, max_char_num_in_line, map_file);
  while (y >= 0){
    for(;;){ //西
      fgets(map_line, 1+1, map_file);//"|\0"
      if ( strcmp(map_line, "|") == 0){
	msim_setWestWall(x, y, 1);
      }else{
	msim_setWestWall(x, y, 0);
      }
      x++;
      if( x == map_size ){
	x=0;
	fgets(map_line, max_char_num_in_line, map_file);//一行読み捨て
	break;
      }
      fgets(map_line, 3+1, map_file);//"   " or " M "
    }//西END
    for(;;){//南
      fgets(map_line, 1+1, map_file);//"+"
      fgets(map_line, 3+1, map_file);//"---"
      if ( strcmp(map_line, "---") == 0){
	msim_setSouthWall(x, y, 1);
      }else{
	msim_setSouthWall(x, y, 0);
      }
      x++;
      if( x == map_size ){
	x=0;
	y--;
	fgets(map_line, max_char_num_in_line, map_file);//一行読み捨て
	break;
      }
    }//南END
  }
  

  /*** ここから後処理 ***/
  if (fclose(map_file) != 0){//if error
    fprintf(stderr, "fatal error!: fclose() failed!");
    exit(1);
  }

  return MSIM_SUCCESSED;
}


#endif //0 msim_loadMapDataFromFile()

//This code is public domain.
#include "../msim.h"

void setMyWallData();//this func genarated by map2Ccode.sh

void doMyAlgolizm();//impliment this func by your self

int main(){

  setMyWallData();//this func genarated by map2Ccode.sh
  
  msim_setOptions(flag_print_on_move|flag_print_on_turn);

  msim_printMap();

  doMyAlgolizm();//impliment this func by your self
  
  return 0;
}

#include <stdio.h>

void msim_debug_logExsitsWallAroundMouse(){
  printf("front:%d right:%d back:%d left:%d\n", msim_existsWallAt(front)>0, msim_existsWallAt(right)>0, msim_existsWallAt(back)>0, msim_existsWallAt(left)>0);
}

void doMyAlgolizm(){
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();


  msim_moveMouseToFront();
  msim_moveMouseToFront();
  msim_moveMouseToFront();
  msim_turnMouseTo(right);
  msim_moveMouseToFront();
  
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();
  msim_turnMouseTo(right);
  msim_debug_logExsitsWallAroundMouse();


  msim_moveMouseToFront();
  msim_moveMouseToFront();
  msim_moveMouseToFront();

  msim_turnMouseTo(back);
  msim_moveMouseToFront();
}

#!/bin/bash 

#This code is public domain.

[ $# != 2 ] && echo Please read readme.txt && exit 1

map_size=16
y=$((map_size -1))
x=0

exec >"$2"

echo 'void msim_setWestWall(unsigned int x, unsigned int y,int isExists);'

echo 'void msim_setSouthWall(unsigned int x, unsigned int y,int isExists);'

echo 'void setMyWallData(){'
echo
{
    read
    while [ $y -ge 0 ] ;do
	while : ;do #西
	    read -n 1 char #|
	    [ x$char = x'|' ] && echo 'msim_setWestWall(' $x ',' $y ', 1 );'  || echo 'msim_setWestWall(' $x ',' $y ', 0 );' 
	    : $((x++))
	    [ $x = $map_size ] && x=0 && read && break
    	    read -n 3 #'   '
	done
	while : ;do #南
	    read -n 1 #+
	    read -n 3 char #---
	    [ x$char = x'---' ] && echo 'msim_setSouthWall(' $x ',' $y ', 1 );' || echo 'msim_setSouthWall(' $x ',' $y ', 0 );'
	    : $((x++))
	    [ $x = $map_size ] && x=0 && : $((y--)) && read && break
	done
    done
    
} <"$1"

echo
echo '}'

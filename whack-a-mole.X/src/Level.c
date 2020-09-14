#include "Level.h"

//ƒQ[ƒ€“ïˆÕ“xÝ’èŠÖ”
void SetLevel(uint8_t i_level){
    if(i_level>0 && i_level<4){
        Level = i_level;        
    }
}
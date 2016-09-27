#include "globals.h"
#include "rogue.h"

#define U_K  'k'
#define D_K  'j'
#define L_K  'h'
#define R_K  'l'
#define UL_K 'y'
#define UR_K 'u'
#define DL_K 'b'
#define DR_K 'n'
#define Q_K  'q'

/*
  Given raw user input, turn it into a command
 */
command parse_input(int input) {
    switch(input) {
    case U_K:
        return MOVE_U;
    case D_K:
        return MOVE_D;
    case L_K:
        return MOVE_L;
    case R_K:
        return MOVE_R;
    case UL_K:
        return MOVE_UL;
    case UR_K:
        return MOVE_UR;
    case DL_K:
        return MOVE_DL;
    case DR_K:
        return MOVE_DR;
    case Q_K:
        return QUIT;
    case '.':
    default:
        return STAY;
    }
}

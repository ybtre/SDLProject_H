
//draw debug rects
//#define draw_rects

#define SCREEN_WIDTH            320
#define SCREEN_HEIGHT           180
#define SCREEN_SCALE            4                   // x4 equals 1280x720

#define FPS                     60

#define PI                      3.14159265358979323846


#define CELL_SIZE               1
#define GRID_X                  300
#define GRID_Y                  200

#define ENTITIES_MAX            256


#define MAX_NAME_LENGTH         32
#define MAX_LINE_LENGTH         1024

#define MAX_KEYBOARD_KEYS       350
#define MAX_MOUSE_BUTTONS       6

#define MAX_SND_CHANNELS        16

enum
{
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};


#undef MIN 
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#undef MAX 
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#undef AVG
#define AVG(A, B) (((A) + (B)) / 2.)
#define STRNCPY(DEST, SRC, N) strncpy(DEST, SRC, N); DEST[N - 1] = '\0'


#define NOT     !
#define NOTEQ   !=
#define AND     &&
#define OR      ||
#define MOD     %
#define elif    else if
#define true    1
#define false   0

#define ifnull( _ ) if( ( _ ) == NULL)


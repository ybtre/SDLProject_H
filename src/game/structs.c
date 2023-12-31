
typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct Texture
{
    char            active;

    char            name[MAX_NAME_LENGTH];
    SDL_Texture*    texture;
} Texture;

typedef struct
{
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
    int wheel;
} Mouse;

#define TEXTURE_CACHE_MAX   16
typedef struct
{
	SDL_Renderer*   renderer;
	SDL_Window*     window;
    Delegate        delegate;

    Mouse           mouse;

    int             keyboard[MAX_KEYBOARD_KEYS];

    float           dt;

    TTF_Font        *font;

    SDL_Texture     *spritesheet;

    Texture         texture_cache[TEXTURE_CACHE_MAX];
} Game;
Game game;

typedef enum Game_State
{
    MAIN_MENU,
    PLAYING,
    GAME_OVER,
} Game_State;
Game_State game_state;

typedef enum Layers
{
    BG_0,
    BG_1,
    BG_2,
    GAMEPLAY,
    FG,
    UI,

    NUM_LAYERS,
} Layers;

enum Flags 
{
    GAME_PAUSED         = 1 << 0,
};

// |= flag      : set flag
// &= !()flag   : unset flag
// ^= flag      : flip flag
typedef struct Game_Flags
{
    uint64_t flags;

} Game_Flags;
Game_Flags game_flags;

SDL_Rect mouse_rect  =
{
    0, 0, 1, 1
};

typedef struct
{
    char            active;

    SDL_Rect        src;
    SDL_Rect        dest;

    SDL_Texture     *tex;
} Sprite;

typedef enum Entity_Type
{
    CELL,
    UI_BUTTON,

} Entity_Type;

typedef enum
{
    CELL_DEAD       = 0,
    CELL_ALIVE      = 1,
} Cell_State;

typedef struct
{
    char                active;
    int                 idx;
    int                 idy;
    SDL_Rect            rect;

    Cell_State          state;
    Cell_State          state_next_step;

    int                 steps_since_dead;

    int                 r;
    int                 g;
    int                 b;
} Cell;

typedef struct
{
    char                active;
    SDL_Rect            rect;

    Cell                cells[GRID_X][GRID_Y]; 
} Grid;
Grid grid;

typedef enum
{
    BUTTON_ACTIVE,
    BUTTON_INACTIVE,
    BUTTON_HOVERED,
    BUTTON_PRESSED,
} Button_State;

typedef struct
{
    SDL_Rect            rect;
    Button_State        state;
} Button;

typedef enum
{
    TURN_DEFAULT,
    TURN_PAUSED,
    
} Turn_State;

typedef struct
{
    //Entity 0 is always player
    Turn_State      turn_state;

    Grid            *grid;

    char            is_stepping;
    float           step_rate;
    float           step_timer;

    //int             entity_count;
    //Entity          entities_pool[ENTITIES_MAX];
}Stage;
Stage stage;


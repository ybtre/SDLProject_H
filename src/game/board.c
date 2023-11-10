

Button button_play = {};
Button button_stop = {};

void init_board()
{
    grid.active          = true;

    grid.rect.x          = 10;
    grid.rect.y          = 10;
    grid.rect.w          = GRID_X * CELL_SIZE; 
    grid.rect.h          = GRID_Y * CELL_SIZE;

    Cell* c = NULL;
    int margin = 2;
    int x, y;
    for(x = 0; x < GRID_X; x++) {
        for(y = 0; y < GRID_Y; y++)
        {
            c                   = &grid.cells[x][y];

            c->active            = true; 
            c->idx               = x;
            c->idy               = y;

            c->rect.w            = CELL_SIZE;
            c->rect.h            = c->rect.w;
            c->rect.x            = grid.rect.x + (x * (c->rect.w + margin));
            c->rect.y            = grid.rect.y + (y * (c->rect.h + margin));
            
            c->state             = CELL_DEAD;
        }
    }

    button_play.rect.x = 1000;
    button_play.rect.y = 100;
    button_play.rect.w = 100;
    button_play.rect.h = 50;

    button_play.state = BUTTON_ACTIVE;

    button_stop.rect.x = 1000;
    button_stop.rect.y = 175;
    button_stop.rect.w = 100;
    button_stop.rect.h = 50;

    button_stop.state = BUTTON_ACTIVE;
}

void update_board(void)
{
    int x, y;
    char hover, pressed;

    mouse_rect.x = game.mouse.x;
    mouse_rect.y = game.mouse.y;

    Cell* c = NULL;
    for(x = 0; x < GRID_X; x++) {
        for(y = 0; y < GRID_Y; y++)
        {
            c       = &grid.cells[x][y];

            hover   = false;
            pressed = false;

            if(SDL_HasIntersection(&mouse_rect, &c->rect))
            {
                hover       = true;

                if(game.mouse.button[SDL_BUTTON_LEFT])
                {
                    pressed     = true;
                    game.mouse.button[SDL_BUTTON_LEFT] = 0;
                }
            }
            else
            {
                hover       = false;
                pressed     = false;
            }

            if(pressed == true)
            {
                if(c->state == CELL_DEAD)
                {
                    c->state        = CELL_ALIVE;
                }
                elif(c->state == CELL_ALIVE)
                {
                    c->state        = CELL_DEAD;
                }
            }
        }
    }
}

void draw_board(void)
{
    Cell* c = NULL;
    int x, y;
    for(x = 0; x < GRID_X; x++) {
        for(y = 0; y < GRID_Y; y++)
        {
            c        = &grid.cells[x][y];

            SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);

            if(c->state == CELL_ALIVE)
            {
                SDL_SetRenderDrawColor(game.renderer, 190, 215, 134, 255);
            }
            elif(c->state == CELL_DEAD)
            {
                SDL_SetRenderDrawColor(game.renderer, 89, 102, 102, 255);
            }

            SDL_RenderFillRect(game.renderer, &c->rect);
        }
    }


    SDL_SetRenderDrawColor(game.renderer, 89, 102, 102, 255);
    SDL_RenderFillRect(game.renderer, &button_play.rect);

    SDL_SetRenderDrawColor(game.renderer, 89, 102, 102, 255);
    SDL_RenderFillRect(game.renderer, &button_stop.rect);
}

void reset_board(void)
{
}

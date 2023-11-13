

Vec2i left      = { -1, 0 };
Vec2i right     = { +1, 0 };
Vec2i top       = { 0, -1 };
Vec2i bot       = { 0, +1 };
Vec2i top_left  = { -1, -1 };
Vec2i top_right = { +1, -1 };
Vec2i bot_left  = { -1, +1 };
Vec2i bot_right = { +1, +1 };

void init_board()
{
    grid.active          = true;

    grid.rect.x          = 250;
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
}

void interact_board(void)
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
                    c->state_next_step = CELL_ALIVE;
                }
                elif(c->state == CELL_ALIVE)
                {
                    c->state        = CELL_DEAD;
                    c->state_next_step = CELL_DEAD;
                }
            }
        }
    }
}

void step_board(void)
{
    int x, y, neigh;
    Cell* c = NULL;
    for(x = 0; x < GRID_X; x++) {
        for(y = 0; y < GRID_Y; y++)
        {
            c           = &grid.cells[x][y];
            neigh       = 0;
            c->state    = c->state_next_step;

            if(grid.cells[x + left.x][y + left.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + right.x][y + right.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + top.x][y + top.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + bot.x][y + bot.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + top_left.x][y + top_left.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + top_right.x][y + top_right.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + bot_left.x][y + bot_left.y].state == CELL_ALIVE)
            {
                neigh++;
            }
            if(grid.cells[x + bot_right.x][y + bot_right.y].state == CELL_ALIVE)
            {
                neigh++;
            }

            if(neigh == 2)
            {
                if(c->state == CELL_ALIVE)
                {
                    c->state_next_step = CELL_ALIVE;
                }
                else
                {
                    c->state_next_step = CELL_DEAD;
                }
            }
            elif(neigh == 3)
            {
                //c->state = CELL_ALIVE;
                c->state_next_step = CELL_ALIVE;

            }
            else
            {
                //c->state = CELL_DEAD;
                c->state_next_step = CELL_DEAD;
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
}

void reset_board(void)
{
}



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
           
            if((x > 50 AND x < 100)
                    AND 
                (y > 50 AND y < 100))
            {
                //int s                = rand() % 2;
                c->state             = CELL_ALIVE;
            }
            else 
            {
                c->state = CELL_DEAD;
            }

            c->steps_since_dead  = 0;
            
            if(c->state == CELL_ALIVE)
            {
                c->r = 190;
                c->g = 215;
                c->b = 134;
            }
            else
            {
                c->r = 89;
                c->g = 102;
                c->b = 102;
            }
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

    //create next gen
    for(x = 0; x < GRID_X; x++) {
        for(y = 0; y < GRID_Y; y++)
        {
            c           = &grid.cells[x][y];
            neigh       = 0;

            for(int u = x - 1; u <= x + 1; ++u) {
                for(int w = y - 1; w <= y + 1; ++w)
                {
                    if(u == x AND w == y)
                        continue;

                    if(grid.cells[u][w].state == CELL_ALIVE)
                        ++neigh;
                }
            }
            
            c->state_next_step = c->state;

            if(neigh == 2
                    OR neigh == 1
                    OR neigh == 4
                    OR neigh == 5)
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
                c->state_next_step = CELL_ALIVE;
            }
            else
            {
                c->state_next_step = CELL_DEAD;
            }
        }
    }

    //update next gen
    for(x = 0; x < GRID_X; x++) {
        for(y = 0; y < GRID_Y; y++)
        {
            c           = &grid.cells[x][y];
            c->state    = c->state_next_step;

            if(c->state == CELL_DEAD)
            {
                c->steps_since_dead++;
                c->r *= .95f;
                c->g *= .95f;
                c->b *= .95f;
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
                c->r = 190;
                c->g = 215;
                c->b = 132;
                SDL_SetRenderDrawColor(game.renderer, c->r, c->g, c->b, 255);
            }
            elif(c->state == CELL_DEAD)
            {

                /*
                c->r *= .99f;
                c->g *= .99f;
                c->b *= .99f;
                */

                if(c->r < 89)
                    c->r = 89;

                if(c->g < 102)
                    c->g = 102;

                if(c->b < 102)
                    c->b = 102;

                SDL_SetRenderDrawColor(game.renderer, c->r, c->g, c->b, 255);
            }

            SDL_RenderFillRect(game.renderer, &c->rect);
        }
    }
}

void reset_board(void)
{
}




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
            
            c->state             = CELL_ALIVE;
        }
    }
}

void update_board(void)
{
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

             SDL_RenderFillRect(game.renderer, &c->rect);
        }
    }
}

void reset_board(void)
{
}

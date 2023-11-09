

void update(void);
void render(void);

SDL_Texture *cursor_texture;

void reset_game(void);

void init_stage(void)
{
    game.delegate.logic = update;
    game.delegate.draw = render;

    memset(&stage, 0, sizeof(Stage));

    cursor_texture = load_texture("assets/cursor.png");
    //game.spritesheet = load_texture("assets/spritesheet.png"); 

    game_state = PLAYING;

    stage.turn_state = TURN_DEFAULT;

    init_board();
}

void update(void)
{
    switch(game_state)
    {
        case MAIN_MENU:
             {
                 //TODO: update_main_menu();
                 if(game.keyboard[SDL_SCANCODE_SPACE])
                 {
                     game_state = PLAYING;
                 }
             }
             break;
        
        case PLAYING:
            {
                update_board();
            }
            break;

        case GAME_OVER:
            {
                //TODO:
                //update_game_over();
                if(game.keyboard[SDL_SCANCODE_SPACE])
                {
                    game_state = PLAYING;
                }
            }
            break;

    }
    if(game.keyboard[SDL_SCANCODE_ESCAPE])
    {
        exit(1);
    }
}

void render(void)
{
    switch(game_state)
    {
        case MAIN_MENU:
            {
                //TODO:
                //draw_main_menu();
            }
            break;
        
        case PLAYING:
            {
                draw_board();
            }
            break;

        case GAME_OVER:
            {
                //TODO:
                //draw_game_over();
            }
            break;
    }

    blit(cursor_texture, game.mouse.x, game.mouse.y, 1.f, 1);
}


void reset_game(void)
{
}


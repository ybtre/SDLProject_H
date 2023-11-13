

Button button_play = {};
Button button_step = {};
Button button_random_board = {};

void update(void);
void render(void);

SDL_Texture *cursor_texture;

void reset_game(void);

void init_stage(void)
{
    game.delegate.logic = update;
    game.delegate.draw = render;

    memset(&stage, 0, sizeof(Stage));

    cursor_texture          = load_texture("assets/cursor.png");
    //game.spritesheet = load_texture("assets/spritesheet.png"); 

    game_state              = PLAYING;

    stage.turn_state        = TURN_DEFAULT;

    init_board();

    stage.is_stepping       = false;
    stage.step_rate         = .01f;
    stage.step_timer        = 0.f;

    button_play.rect.x = 1000;
    button_play.rect.y = 100;
    button_play.rect.w = 100;
    button_play.rect.h = 50;

    button_play.state = BUTTON_ACTIVE;

    button_step.rect.x = 1000;
    button_step.rect.y = 175;
    button_step.rect.w = 100;
    button_step.rect.h = 50;

    button_step.state = BUTTON_ACTIVE;

    button_random_board.rect.x = 1000;
    button_random_board.rect.y = 250;
    button_random_board.rect.w = 100;
    button_random_board.rect.h = 50;

    button_random_board.state = BUTTON_ACTIVE;
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
                mouse_rect.x = game.mouse.x;
                mouse_rect.y = game.mouse.y;

                //SDL_Log("DT: %f", (game.dt / 1000.f));

                if(stage.is_stepping)
                {
                    stage.step_timer    += (game.dt / 1000.f);
                    //SDL_Log("step timer: %f", stage.step_timer);

                    if(stage.step_timer > stage.step_rate)
                    {
                        step_board();
                        stage.step_timer = 0;
                    }
                }
                elif(!stage.is_stepping)
                {
                    interact_board();
                    stage.step_timer    = 0;
                }

                if(SDL_HasIntersection(&mouse_rect, &button_play.rect))
                {
                    if(game.mouse.button[SDL_BUTTON_LEFT])
                    {
                        if(stage.is_stepping)
                        {
                            stage.is_stepping       = false;
                        }
                        else
                        {
                            stage.is_stepping       = true;
                        }
                        game.mouse.button[SDL_BUTTON_LEFT] = 0;

                    }
                }

                if(SDL_HasIntersection(&mouse_rect, &button_step.rect))
                {
                    if(game.mouse.button[SDL_BUTTON_LEFT])
                    {
                        step_board();
                        stage.step_timer = 0;

                        game.mouse.button[SDL_BUTTON_LEFT] = 0;
                    }
                }

                if(SDL_HasIntersection(&mouse_rect, &button_random_board.rect))
                {
                    if(game.mouse.button[SDL_BUTTON_LEFT])
                    {
                        init_board();

                        game.mouse.button[SDL_BUTTON_LEFT] = 0;
                    }
                }
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

                if(stage.is_stepping)
                {
                    SDL_SetRenderDrawColor(game.renderer, 89, 102, 102, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(game.renderer, 190, 215, 134, 255);
                }
                SDL_RenderFillRect(game.renderer, &button_play.rect);

                SDL_SetRenderDrawColor(game.renderer, 89, 102, 102, 255);
                SDL_RenderFillRect(game.renderer, &button_step.rect);

                SDL_SetRenderDrawColor(game.renderer, 89, 102, 102, 255);
                SDL_RenderFillRect(game.renderer, &button_random_board.rect);
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


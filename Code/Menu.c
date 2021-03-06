#include "Utils.h"

static SDL_Sprite* mBackgroundMenu = NULL;
static SDL_Sprite* mButtons[4];
static SDL_Sprite* mLogoEsig;
static SDL_Sprite* mEsig;

int MENU_create(SDL_Renderer* renderer)
{
    int i;

    mBackgroundMenu = SDL_CreateSprite("Assets/fond.bmp",renderer);
    if (mBackgroundMenu == NULL)
    {
        error("BackgroundMenu");
        return 0;
    }

    for (i = 0; i < 4; i++)
    {
        mButtons[i] = SDL_CreateSpriteTransparency("Assets/buttons.bmp",renderer,255,0,255);
        if (mButtons[i] == NULL)
        {
            error("ButtonMenu");
            return 0;
        }
        mButtons[i]->pos.x = SCREEN_WIDTH / 2 - 110;
        mButtons[i]->pos.y = 210 + 90 * i;
        mButtons[i]->rect.x = 0;
        mButtons[i]->rect.y = 80 * i;
        mButtons[i]->rect.w = 220;
        mButtons[i]->rect.h = 80;
    }

    mLogoEsig = SDL_CreateSprite("Assets/logo-esigelec.bmp",renderer);
    mLogoEsig->pos.x = 800 - 100;
    mLogoEsig->pos.y = 608 - 100;

    mEsig = SDL_CreateSprite("Assets/esigelec.bmp",renderer);
    mEsig->pos.x = 0;
    mEsig->pos.y = 608 - 50;

    return 1;
}

void MENU_destroy()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        SDL_DestroySprite(mButtons[i]);
    }
    SDL_DestroySprite(mBackgroundMenu);
    SDL_DestroySprite(mLogoEsig);
    SDL_DestroySprite(mEsig);
}

void MENU_handleEvent(SDL_Event event, SDL_Context* context)
{
    SDL_Point p = SDL_GetMousePosition();
    SDL_Rect r;
    int i;
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
    {
        for (i = 0; i < 4; i++)
        {
            r = SDL_GetSpriteRect(mButtons[i]);
            if (SDL_PointInRect(&p,&r))
            {
                switch (i)
                {
                    case 0: STATES_switch(STATE_GAME,context); break;
                    case 1: STATES_switch(STATE_ALGO_1,context); break;
                    case 2: STATES_switch(STATE_ALGO_2,context); break;
                    case 3: STATES_switch(-1,context); break;
                    default: break;
                }
            }
        }
    }
}

void MENU_update()
{
    SDL_Point p = SDL_GetMousePosition();
    SDL_Rect r;
    int i;
    for (i = 0; i < 4; i++)
    {
        r = SDL_GetSpriteRect(mButtons[i]);
        if (SDL_PointInRect(&p,&r))
        {
            mButtons[i]->rect.x = 220;
        }
        else
        {
            mButtons[i]->rect.x = 0;
        }
    }
}

void MENU_render(SDL_Renderer* renderer)
{
    int i;
    SDL_RenderSprite(renderer,mBackgroundMenu);
    for (i = 0; i < 4; i++)
    {
        SDL_RenderSprite(renderer,mButtons[i]);
    }
    SDL_RenderSprite(renderer,mLogoEsig);
    SDL_RenderSprite(renderer,mEsig);
}

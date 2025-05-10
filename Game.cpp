
#include "Game.h"


Game::Game(SDL_Renderer *des, Gun &gun, MainObject &player) : gun_(gun), player_(player)
{

    p_play = {544, 400};
    p_replay = {544, 272};
    p_quit = {544, 388};
    P_YouLose = {544, 100};
    P_YouLose = {580,200};
    p_pause_button = {SCREEN_WIDTH-WIDTH_BUTTON_SETTING, 0};
    p_music_button = {544, 300};

    frame = IMG_LoadTexture(des, "images//Buff_window.png");
    info = IMG_LoadTexture(des, "images//Info_table.png");

    Sound_button[0] = IMG_LoadTexture(des,"images//music_off.png");
    Sound_button[1] = IMG_LoadTexture(des,"images//music_off_hover.png");
    Sound_button[2] = IMG_LoadTexture(des,"images//music_on.png");
    Sound_button[3] = IMG_LoadTexture(des,"images//music_on_hover.png");

    for(int i=0;i<MAIN_BUFFS;i++)
    {
        Main_buffs_texture[i] = nullptr;
    }

    for(int i=0;i<TOTAL_BUFFS;i++)
    {
        NoteTB[i] = nullptr;
    }

    NotePos[0] = {140, 230};
    NotePos[1] = {140, 258};
    NotePos[2] = {140, 286};
    NotePos[3] = {140, 314};
    NotePos[4] = {140, 342};

    NoteText[0] = 2;
    NoteText[1] = 3;
    NoteText[2] = 5;
    NoteText[3] = 20;
    NoteText[4] = 100;

    Buffs["dame"] = "images//Dame.png";
    Buffs["total_bullets"] = "images//total_bullets.png";
    Buffs["speed"] = "images//Speed.png";
    Buffs["bullet_speed"] = "images//Bullet_speed.png";
    Buffs["max_health"] = "images//health.png";
    Buffs["healing"] = "images//healing.png";

    p_frame = {512, 235};
    p_info = {131, 209};
    Points["first"] = {564, 329};
    Points["second"] = {624, 329};
    Points["third"] = {684, 329};

    Press["first"] = false;
    Press["second"] = false;
    Press["third"] = false;
}


Game::~Game()
{

}

bool Game::CheckButton(SDL_Point &point, int wid, int hei)
{
    int left = point.x;
    int right = point.x + wid;
    int top = point.y;
    int bottom = point.y + hei;

    if(left <= mouse_x && right >= mouse_x && top <= mouse_y && bottom >= mouse_y)
        return true;
    return false;
}

void Game::HandleMouseHover(SDL_Event event, AudioManager &audio)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                setting_pressed[0] = true;
            }
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                if(menu)
                {
                    if(CheckButton(p_play, WIDTH_BUTTON, HEIGH_BUTTON))
                    {
                        pressed[0] = true;
                    }
                }
                else if(!menu)
                {
                    if(CheckButton(p_replay, WIDTH_BUTTON, HEIGH_BUTTON))
                    {
                        pressed[1] = true;
                        isResume = true;
                    }
                    else if(CheckButton(p_quit, WIDTH_BUTTON, HEIGH_BUTTON))
                    {
                        pressed[2] = true;
                    }
                }

                if(!paused)
                {
                    if(CheckButton(p_pause_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        setting_pressed[0] = true;
                    }
                }
                else if(paused)
                {
                    if(CheckButton(p_resume_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        setting_pressed[1] = true;
                    }
                    else if(CheckButton(p_quit_button_setting, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        setting_pressed[2] = true;
                    }
                    else if(CheckButton(p_music_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                    {
                        music = !music;
                    }
                }
                if(buff)
                {
                    if(CheckButton(Points["first"], WIDTH_BUFF, HEIGHT_BUFF))
                    {
                        Press["first"] = true;
                        selected_buff = Main_buffs_name[0];
                    }
                    else if(CheckButton(Points["second"], WIDTH_BUFF, HEIGHT_BUFF))
                    {
                        Press["second"] = true;
                        selected_buff = Main_buffs_name[1];
                    }
                    else if(CheckButton(Points["third"], WIDTH_BUFF, HEIGHT_BUFF))
                    {
                        Press["third"] = true;
                        selected_buff = Main_buffs_name[2];
                    }
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            for(int i=0;i<3;i++)
            {
                pressed[i] = false;
            }
            for(int i=0;i<4;i++)
            {
                setting_pressed[i] = false;
            }
            Press["first"] = false;
            Press["second"] = false;
            Press["third"] = false;
            break;
        }
        case SDL_MOUSEMOTION:
        {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            if(menu)
            {
                if(CheckButton(p_play, WIDTH_BUTTON, HEIGH_BUTTON))
                {
                    play_button_frame++;
                    if(play_button_frame == 3)
                    {
                        play_button_frame = 2;
                    }
                }
                else
                {
                    play_button_frame = 0;
                }
            }
            else if(!menu)
            {
                if(CheckButton(p_replay, WIDTH_BUTTON, HEIGH_BUTTON))
                {
                    isResume = true;
                    replay_button_frame++;
                    if(replay_button_frame == 3)
                        replay_button_frame = 2;
                }
                else if(CheckButton(p_quit, WIDTH_BUTTON, HEIGH_BUTTON))
                {
                    quit_button_frame++;
                    if(quit_button_frame == 3)
                        quit_button_frame = 2;
                }
                else
                {
                    replay_button_frame = 0;
                    quit_button_frame = 0;
                }
            }

            if(!paused)
            {
                if(CheckButton(p_pause_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    paused_frame++;
                    if(paused_frame == 2)
                        paused_frame = 1;
                }
                else
                {
                    paused_frame = 0;
                }
            }
            else if(paused)
            {

                if(CheckButton(p_resume_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    resume_frame++;
                    if(resume_frame == 2)
                        resume_frame = 1;
                }
                else if(CheckButton(p_quit_button_setting, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    quit_frame++;
                    if(quit_frame == 2)
                        quit_frame = 1;
                }
                else if(CheckButton(p_music_button, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING))
                {
                    isHovermusic = true;
                }
                else
                {
                    resume_frame = 0;
                    quit_frame = 0;
                    isHovermusic = false;
                }
            }
            if(buff)
            {
                if (CheckButton(Points["first"], WIDTH_BUFF, HEIGHT_BUFF))
                {
                    hover_buff = Main_buffs_name[0];
                    first_buff_frame++;
                    if (first_buff_frame == 2)
                        first_buff_frame = 1;
                }
                else if (CheckButton(Points["second"], WIDTH_BUFF, HEIGHT_BUFF)) // Thêm else
                {
                    hover_buff = Main_buffs_name[1];
                    second_buff_frame++;
                    if (second_buff_frame == 2)
                        second_buff_frame = 1;
                }
                else if (CheckButton(Points["third"], WIDTH_BUFF, HEIGHT_BUFF)) // Thêm else
                {
                    hover_buff = Main_buffs_name[2];
                    third_buff_frame++;
                    if (third_buff_frame == 2)
                        third_buff_frame = 1;
                }
                else
                {
                    hover_buff.clear();
                    first_buff_frame = 0;
                    second_buff_frame = 0;
                    third_buff_frame = 0;
                }
            }
            break;
        }
    }
    if(pressed[0])
    {
        menu = false;
    }
    if(setting_pressed[0])
    {
        paused = true;
    }
    if(Press["first"] || Press["second"] || Press["third"])
    {
        audio.PlaySound("buff");
        SDL_Delay(100);
        ApplyBuff(player_, gun_, audio);
        buff = false;
        paused = false;
        buff_active = false;
    }
    audio.ToggleMute(music);
}

void Game::RenderStartMenu(SDL_Renderer *des)
{
    Setclip_and_Render(des, p_play, play_button, play_button_frame,3, "images//Play_button.png", WIDTH_BUTTON, HEIGH_BUTTON);
    Logo = IMG_LoadTexture(des, "images//Logo.png");
    SDL_RenderCopy(des,Logo,NULL,&r_logo);
}

void Game::Setclip_and_Render(SDL_Renderer *des, SDL_Point &point, SDL_Texture *&texture, int &frame, int NUMBER_OF_FRAMES, const char* name, int wid, int hei)
{
    SDL_Rect button_clips[NUMBER_OF_FRAMES];
    for(int i=0;i<NUMBER_OF_FRAMES;i++)
    {
        button_clips[i].x = wid*i;
        button_clips[i].y = 0;
        button_clips[i].w = wid;
        button_clips[i].h = hei;
    }
    if(texture == NULL)
    {
        texture = IMG_LoadTexture(des, name);
        if (texture == NULL) {
            std::cerr << "Failed to load texture: " << name << "\n";
            return;
        }
    }
    SDL_Rect button_rect = {point.x, point.y, wid, hei};
    SDL_Rect *current_frame = &button_clips[frame];
    SDL_RenderCopy(des, texture, current_frame, &button_rect);
}

void Game::FreeButton(SDL_Texture*& texture)
{
    if(texture!=nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

SDL_Texture* Game::Render_Text(SDL_Renderer *des, TTF_Font *font, const char *text, SDL_Point point, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(des, textSurface);

    SDL_Rect textRect = {point.x, point.y, textSurface->w, textSurface->h };
    SDL_RenderCopy(des, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);

    return textTexture;
}

void Game::Replay(SDL_Renderer*des, TTF_Font* font, bool &game_event, bool &is_quit, MainObject &player, std::vector<SmallEnemy*> &Spawner
                  , std::vector<Exp*> &exp_list, std::vector<Nuke*> &nuke_list, Lich &lich)
{
    SDL_Texture* Youlose = Render_Text(des, font, "YOU LOSE", P_YouLose, textColor);
    Setclip_and_Render(des, p_replay, Replay_button, replay_button_frame,3, "images//Replay_button.png", WIDTH_BUTTON, HEIGH_BUTTON);
    Setclip_and_Render(des, p_quit, Quit_button, quit_button_frame,3, "images//Quit_button.png", WIDTH_BUTTON, HEIGH_BUTTON);
    game_event = false;
    for(auto *smallenemy : Spawner)
    {
        if(smallenemy != nullptr) delete smallenemy;
    }

    for(auto *exp : exp_list)
    {
        if(exp != nullptr) delete exp;
    }

    for(auto *nuke : nuke_list)
    {
        if(nuke != nullptr)
            delete nuke;
    }

    Spawner.clear();
    exp_list.clear();
    nuke_list.clear();

    if(pressed[1] == true)
    {
        FreeButton(Replay_button);
        FreeButton(Quit_button);
        SDL_DestroyTexture(Youlose);
        Youlose = NULL;
        player.Reset_status();
        game_event = true;
        menu = true;
        lich.Reset();
    }
    if(pressed[2] == true)
    {
        is_quit = true;

    }
}

void Game::RenderPaused(SDL_Renderer *des)
{
    Setclip_and_Render(des, p_pause_button, Pause_button, paused_frame,2, "images//Paused_button.png", 32, 32);
}

void Game::RenderPausedList(SDL_Renderer *des, bool &is_quit, bool &game_event)
{

    SDL_SetRenderDrawBlendMode(des, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(des, 0, 0, 0, 100);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(des, &overlay);

    p_resume_button.x = SCREEN_WIDTH/2 - 64;
    p_resume_button.y = SCREEN_HEIGHT/2 -64;
    p_quit_button_setting.x = SCREEN_WIDTH/2 - 64;
    p_quit_button_setting.y = SCREEN_HEIGHT/2 ;

    Setclip_and_Render(des, p_resume_button, Resume_button, resume_frame,2, "images//Resume_button.png", 32, 32);
    Setclip_and_Render(des, p_quit_button_setting, Quit_button_setting, quit_frame,2, "images//quit_button_setting.png", 32, 32);
    if(setting_pressed[1] == true)
    {
        FreeButton(Resume_button);
        FreeButton(Quit_button_setting);
        FreeButton(Pause_button);
        paused = false;
        setting_pressed[1] = false;
    }
    else if(setting_pressed[2] == true)
    {
        FreeButton(Resume_button);
        FreeButton(Quit_button_setting);
        FreeButton(Pause_button);
        is_quit = true;
        setting_pressed[2] = false;
    }

    SDL_Texture *target = nullptr;
    if(!music)
    {
        target = isHovermusic ? Sound_button[1] : Sound_button[0];
    }
    else
    {
        target = isHovermusic ? Sound_button[3] : Sound_button[2];
    }
//    audio.ToggleMute(music);
    if(target != NULL)
    {
        SDL_Rect RenderQuad = {p_music_button.x, p_music_button.y, WIDTH_BUTTON_SETTING, HEIGH_BUTTON_SETTING};
        SDL_RenderCopy(des, target, NULL, &RenderQuad);
    }
}

void Game::ApplyBuff(MainObject &player, Gun &gun, AudioManager &audio)
{
    if(player.G_EXP >= player.MAX_EXP)
    {
        paused = true;
        audio.PlaySound("levelUp");
        buff = true;
        buff_active = true;
        RandomPick();
        player.LEVEL++;
        player.G_EXP = 0;
        player.MAX_EXP = player.MAX_EXP * pow(1.5f, player.LEVEL - 1);
    }
    if(buff_active && !selected_buff.empty())
    {
        if(selected_buff == Buffs["dame"])
        {
            gun.IncreaseDame();
            NoteText[0] = gun.GetDame();
        }
        else if(selected_buff == Buffs["total_bullets"])
        {
            gun.IncreaseTotalBullets();
            NoteText[1] = gun.GetTotalBullets();
        }
        else if(selected_buff == Buffs["speed"])
        {
            player.IncreaseSpeed();
            NoteText[2] = player.GetSpeed();
        }
        else if(selected_buff == Buffs["bullet_speed"])
        {
            gun.IncreaseBulletSpeed();
            NoteText[3] = gun.GetBulletSpeed();
        }
        else if(selected_buff == Buffs["max_health"])
        {
            player.IncreaseMaxHealth();
            NoteText[4] = player.GetMaxHp();
        }
        else if(selected_buff == Buffs["healing"])
        {
            player.Healing();
        }
        for(int i=0;i<MAIN_BUFFS;i++)
        {
            FreeButton(Main_buffs_texture[i]);
        }
        selected_buff.clear();
        hover_buff.clear();
        buff_active = false;
    }
}

void Game::RandomPick()
{
    std::vector<char*> availableBuffs = {
        "dame", "total_bullets", "speed", "bullet_speed", "max_health", "healing"
    };
    std::srand(std::time(0));
    std::random_shuffle(availableBuffs.begin(), availableBuffs.end());
    for(int i = 0; i < MAIN_BUFFS; i++) {
        if (i < availableBuffs.size())
        {
            Main_buffs_name[i] = Buffs[availableBuffs[i]];
        }
    }
}

void Game::RenderBuff(SDL_Renderer *des)
{
    SDL_SetRenderDrawBlendMode(des, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(des, 0, 0, 0, 100);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(des, &overlay);

    SDL_Rect renderquad = {p_frame.x, p_frame.y, 255, 170};
    SDL_RenderCopy(des, frame, NULL, &renderquad);

    for (int i = 0; i < MAIN_BUFFS; i++) {
        if (Main_buffs_texture[i] == nullptr) {
            Main_buffs_texture[i] = IMG_LoadTexture(des, Main_buffs_name[i]);
        }
    }

    // Render 3 buff
    Setclip_and_Render(des, Points["first"], Main_buffs_texture[0], first_buff_frame, 2, "", WIDTH_BUFF, HEIGHT_BUFF);
    Setclip_and_Render(des, Points["second"], Main_buffs_texture[1], second_buff_frame, 2, "", WIDTH_BUFF, HEIGHT_BUFF);
    Setclip_and_Render(des, Points["third"], Main_buffs_texture[2], third_buff_frame, 2, "", WIDTH_BUFF, HEIGHT_BUFF);
}

void Game::RenderNoteTB(SDL_Renderer *des, TTF_Font *game_font)
{
    SDL_Rect renderquad2 = {p_info.x, p_info.y, 237, 223};
    SDL_RenderCopy(des, info, NULL, &renderquad2);
    std::string name[5] = {"DAMAGE: ", "BULLET/BURST: ", "MOVE SPEED: ", "BULLET SPEED: ", "HP: "};
    for(int i=0;i<TOTAL_BUFFS;i++)
    {
        std::string text = name[i] + std::to_string(NoteText[i]);
        NoteTB[i] = Render_Text(des, game_font, text.c_str(), NotePos[i], gameColor);
    }
}

void Game::RenderPreview(SDL_Renderer *des, TTF_Font *game_font, MainObject& player, Gun &gun)
{
    std::string text = "";
    SDL_Point position = {0, 0};
    SDL_Texture *preview = nullptr;

    if(!hover_buff.empty())
    {
        if(hover_buff == "images//Dame.png")
        {
            int newDame = gun.GetDame() + 1;
            text = "-> " + std::to_string(newDame);
            position = {NotePos[0].x + 100, NotePos[0].y};
        }
        else if(hover_buff == "images//total_bullets.png")
        {
            int newBullets = gun.GetTotalBullets() + 1;
            text = "-> " + std::to_string(newBullets);
            position = {NotePos[1].x + 167, NotePos[1].y};
        }
        else if(hover_buff == "images//Speed.png")
        {
            int newSpeed = player.GetSpeed() * 1.2;
            text = "-> " + std::to_string(newSpeed);
            position = {NotePos[2].x + 140, NotePos[2].y};
        }
        else if(hover_buff == "images//Bullet_speed.png")
        {
            int newBulletSpeed = gun.GetBulletSpeed() * 1.1;
            text = "-> " + std::to_string(newBulletSpeed);
            position = {NotePos[3].x + 170, NotePos[3].y};
        }
        else if(hover_buff == "images//health.png")
        {
            int newHP = player.GetMaxHp() * 1.1;
            text = "-> " + std::to_string(newHP);
            position = {NotePos[4].x + 70, NotePos[4].y};
        }
        if (!text.empty()) {
            preview = Render_Text(des, game_font, text.c_str(), position, textColor);
        }
    }
    if (preview) {
        SDL_DestroyTexture(preview);
    }
}



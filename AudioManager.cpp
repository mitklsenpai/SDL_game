
#include "AudioManager.h"

AudioManager::AudioManager()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(16);

    soundEffects["gun"] = Mix_LoadWAV("sfx/sfx_gun_sound_effect.wav");
    soundEffects["hit"] = Mix_LoadWAV("sfx/sfx_damage_hit.wav");
    soundEffects["levelUp"] = Mix_LoadWAV("sfx/level_up.wav");
    soundEffects["buff"] = Mix_LoadWAV("sfx/choose_buff.wav");
    soundEffects["youLose"] = Mix_LoadWAV("sfx/you_lose.wav");
    bgMusic = Mix_LoadMUS("sfx/8_bit_dungeon.mp3");

    Mix_VolumeMusic(MIX_MAX_VOLUME * 0.3);
    Mix_Volume(-1, MIX_MAX_VOLUME * 0.4);

}

AudioManager::~AudioManager()
{
    for(auto& sfx : soundEffects) {
        Mix_FreeChunk(sfx.second);
    }
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
}

void AudioManager::PlaySound(const std::string& name)
{
    if(soundEffects.find(name) != soundEffects.end())
    {
        Mix_PlayChannel(-1, soundEffects[name], 0);
    }
}

void AudioManager::PlayMusic()
{
    Mix_PlayMusic(bgMusic, -1);
}

void AudioManager::ToggleMute(bool &isMusic)
{
    if (!isMusic) {
        Mix_Volume(-1, 0);
        Mix_VolumeMusic(0);
    } else {
        Mix_Volume(-1, soundVolume);
        Mix_VolumeMusic(musicVolume);
    }
}

void AudioManager::MuteMusic()
{
    Mix_VolumeMusic(0);
}


#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_

#include "commonFunc.h"

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    void PlaySound(const std::string& name);
    void PlayMusic();
    void ToggleMute(bool &isMuted);
    void MuteMusic();

private:
    int soundVolume = MIX_MAX_VOLUME * 0.4;
    int musicVolume = MIX_MAX_VOLUME * 0.3;

    std::map<std::string, Mix_Chunk*> soundEffects;
    Mix_Music* bgMusic;

};

#endif // AUDIO_MANAGER_H_

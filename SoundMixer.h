#ifndef _SoundMixer_
#define _SoundMixer_

#include "SDL2/SDL_mixer.h"

#include <map>
#include <string>
#include <iostream>

enum soundType
{
  SOUND_MUSIC = 0,
  SOUND_SFX = 1
};

class SoundMixer {

private:
  static SoundMixer* s_pInstance;

  //maps holding a string reference to an audio file. Split into music and soundSFX maps
  std::map<std::string, Mix_Chunk*> m_sfxs;
  std::map<std::string, Mix_Music*> m_music;
  
public:

  SoundMixer(); //constructor
  ~SoundMixer(); //destr

  //singleton instance
  static SoundMixer* Instance();

  //the file name is found within the assets/Audio folder, and has a string id associated with it so it can be
  //referred to via a name. The sound is given a type (music/soundSFX) which will determine which audio channel
  //the sound is played on
  bool load(std::string fileName, std::string id, soundType type);

  //plays the audio file mapped to the given string id for int loop times
  void playMusic (std::string id, int loop);
  void pauseMusic();
  void resumeMusic();

  //plays the audio file mapped to the given string id for int loop times
  void playSound (std::string id, int loop, int channel = -1);

  //stops playing the sound effect on given the given channel, fading out over msToFadeOut
  void stopPlaying(int channel, int msToFadeOut);
};

typedef SoundMixer TheSoundMixer;

#endif

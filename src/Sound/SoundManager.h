#pragma once
#include <irrKlang.h>

using namespace irrklang;

class SoundManager 
{
public:
	SoundManager();

	void playRotateSound();
	void playSuccessSound();
	void playErrorSound();

	void muteMusic();
	void muteEffects();

	void incMusicVol();
	void decMusicVol();
	void incEffectsVol();
	void decEffectsVol();

protected:

	void startMusic();
	ISoundEngine* engine;
	ISoundSource* music;
	ISoundSource* error;
	ISoundSource* success;
	ISoundSource* rotate;

	ISound* musicVolumeControl;

	bool musicMute;
	bool effectsMute;

	float musicVol;
	float effectsVol;
};

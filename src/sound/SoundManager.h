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

protected:

	void startMusic();
	ISoundEngine* engine;
	ISoundSource* music;
	ISoundSource* error;
	ISoundSource* success;
	ISoundSource* rotate;

	ISound* musicVolumeControl;

	bool mute;
};

/*
 * Sounds retrieved from https://freesound.org/
 * Some of the sounds are non-attribution creative commons.
 * The other sounds are under creative-commons attribution:
 * 
 * "frankum_techno_loop.mp3" is made by the user Frankum
 * "success.wav" is made by the user xtrgamr
 * "neutral_click.wav"
 * 
*/


#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
	engine = createIrrKlangDevice();
	music = engine->addSoundSourceFromFile("res/sounds/frankum_techno_loop.mp3");
	error = engine->addSoundSourceFromFile("res/sounds/error.wav");
	success = engine->addSoundSourceFromFile("res/sounds/success.wav");
	rotate = engine->addSoundSourceFromFile("res/sounds/neutral_click.wav");

	startMusic();
	mute = false;

}

void SoundManager::startMusic() {
	music->setDefaultVolume(0.5f);
	musicVolumeControl = engine->play2D(music, true, false, true);
}

void SoundManager::muteMusic() {

	if (mute == false) {
		mute = true;
		musicVolumeControl->setVolume(0.0f);
	}
	else {
		mute = false;
		musicVolumeControl->setVolume(0.5f);
	}
}

void SoundManager::playRotateSound() {
	rotate->setDefaultVolume(0.5f);
	engine->play2D(rotate);
}

void SoundManager::playSuccessSound() {
	success->setDefaultVolume(0.6f);
	engine->play2D(success);
}

void SoundManager::playErrorSound() {
	error->setDefaultVolume(0.75f);
	engine->play2D(error);
}
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

	musicVol = 0.5f;
	effectsVol = 0.6f;

	music->setDefaultVolume(musicVol);
	rotate->setDefaultVolume(effectsVol);
	success->setDefaultVolume(effectsVol);
	error->setDefaultVolume(effectsVol);

	startMusic();
	musicMute = false;
	effectsMute = false;

}

void SoundManager::startMusic() {
	musicVolumeControl = engine->play2D(music, true, false, true);
}

void SoundManager::muteMusic() {

	if (musicMute == false) {
		musicMute = true;
		musicVolumeControl->setVolume(0.0f);
	}
	else {
		musicMute = false;
		musicVolumeControl->setVolume(musicVol);
	}
}

void SoundManager::incMusicVol() {
	if (musicVol < 1.0f) {
		musicVol += 0.05f;
		musicVolumeControl->setVolume(musicVol);
	}
}

void SoundManager::decMusicVol() {
	if (musicVol > 0.0f) {
		musicVol -= 0.05f;
		musicVolumeControl->setVolume(musicVol);
	}
}

void SoundManager::muteEffects() {
	if (effectsMute == false) {
		effectsMute = true;
	}
	else {
		effectsMute = false;
	}
}

void SoundManager::incEffectsVol() {
	if (effectsVol < 1.0f) {
		effectsVol += 0.05f;
	}
}

void SoundManager::decEffectsVol() {
	if (effectsVol > 0.0f) {
		effectsVol -= 0.05f;
	}
}

void SoundManager::playRotateSound() {
	if (effectsMute == false) {
		rotate->setDefaultVolume(effectsVol);
		engine->play2D(rotate);
	}
}

void SoundManager::playSuccessSound() {
	if (effectsMute == false) {
		success->setDefaultVolume(effectsVol);
		engine->play2D(success);
	}
}

void SoundManager::playErrorSound() {
	if (effectsMute == false) {
		error->setDefaultVolume(effectsVol);
		engine->play2D(error);
	}
}
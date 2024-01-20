#ifndef RISPIRIT_AUDIOHANDLER_H
#define RISPIRIT_AUDIOHANDLER_H

#include <SFML/Audio.hpp>
#include <iostream>

class AudioHandler{
public:
    AudioHandler(){};

    void playmusic(std::string path){   //function, give path to sound file then play the fil with sf::music. (used for songs/music)

        if(!music.openFromFile(path)){
            std::cout << "something went wrong finding path or loading file for music" << std::endl;
        }
        else{
            music.setLoop(true);
            music.play();
        }
    }

    bool IfMusicPlaying(){ //checks if music is playing
        return music.getStatus() == sf::Music::Playing;
    }

    void stopMusic(){ // stops the music
        music.stop();
    }

    void playSound(std::string path){ //function, give path to sound file then play the fil with sf::sound. (used for sound effects)
        if(!buffer.loadFromFile(path)){
            std::cout << "something went wrong finding path or loading file for music" << std::endl;
        }
        else{
            sound.setBuffer(buffer);
            sound.setLoop(false);
            sound.play();
        }

    }

    bool IfSoundPlaying(){ //check is sound is playing
        return sound.getStatus() == sf::Sound::Playing;
    }

    void MusicVolume(float volume){ // sets the music volume
        music.setVolume(volume);
    }

    void soundvolume(float volume){ //sets soundvolume
        sound.setVolume(volume);
    }

    void mastervolume(float volume){ // sets volume for sound and music
        float vol = 10 - volume;

        music.setVolume(music.getVolume()/vol);
        sound.setVolume(sound.getVolume()/vol);
    }

private:
    sf::SoundBuffer buffer;
    sf::Music music;
    sf::Sound sound;
};

#endif //RISPIRIT_AUDIOHANDLER_H

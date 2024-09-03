#include "gui/GuiSound.h"
#include "gui/sounds/SoundHandler.hpp"
#include <stdio.h>
#include <string.h>
#include <string>

GuiSound::GuiSound(const char *filepath) {
    voice = -1;
    Load(filepath);
}

GuiSound::GuiSound(const uint8_t *snd, int32_t length) {
    voice = -1;
    Load(snd, length);
}

GuiSound::~GuiSound() {
    if (voice >= 0) {
        SoundHandler::instance()->RemoveDecoder(voice);
    }
}


bool GuiSound::Load(const char *filepath) {
    if (voice >= 0) {
        SoundHandler::instance()->RemoveDecoder(voice);
        voice = -1;
    }

    //! find next free decoder
    for (int32_t i = 0; i < MAX_DECODERS; i++) {
        SoundDecoder *decoder = SoundHandler::instance()->getDecoder(i);
        if (decoder == NULL) {
            SoundHandler::instance()->AddDecoder(i, filepath);
            decoder = SoundHandler::instance()->getDecoder(i);
            if (decoder) {
                voice = i;
                SoundHandler::instance()->ThreadSignal();
            }
            break;
        }
    }

    if (voice < 0) {
        return false;
    }

    return true;
}

bool GuiSound::Load(const uint8_t *snd, int32_t len) {
    if (voice >= 0) {
        SoundHandler::instance()->RemoveDecoder(voice);
        voice = -1;
    }

    if (!snd) {
        return false;
    }

    //! find next free decoder
    for (int32_t i = 0; i < MAX_DECODERS; i++) {
        SoundDecoder *decoder = SoundHandler::instance()->getDecoder(i);
        if (decoder == NULL) {
            SoundHandler::instance()->AddDecoder(i, snd, len);
            decoder = SoundHandler::instance()->getDecoder(i);
            if (decoder) {
                voice = i;
                SoundHandler::instance()->ThreadSignal();
            }
            break;
        }
    }

    if (voice < 0) {
        return false;
    }

    return true;
}

void GuiSound::Play() {
    Stop();

    Voice *v = SoundHandler::instance()->getVoice(voice);
    if (v) {
        v->setState(Voice::STATE_START);
    }
}

void GuiSound::Stop() {
    Voice *v = SoundHandler::instance()->getVoice(voice);
    if (v) {
        if ((v->getState() != Voice::STATE_STOP) && (v->getState() != Voice::STATE_STOPPED)) {
            v->setState(Voice::STATE_STOP);
        }

        while (v->getState() != Voice::STATE_STOPPED)
            OSSleepTicks(OSMicrosecondsToTicks(1000));
    }

    SoundDecoder *decoder = SoundHandler::instance()->getDecoder(voice);
    if (decoder) {
        decoder->Lock();
        decoder->Rewind();
        decoder->ClearBuffer();
        SoundHandler::instance()->ThreadSignal();
        decoder->Unlock();
    }
}

void GuiSound::Pause() {
    if (!IsPlaying()) {
        return;
    }

    Voice *v = SoundHandler::instance()->getVoice(voice);
    if (v) {
        v->setState(Voice::STATE_STOP);
    }
}

void GuiSound::Resume() {
    if (IsPlaying()) {
        return;
    }

    Voice *v = SoundHandler::instance()->getVoice(voice);
    if (v) {
        v->setState(Voice::STATE_START);
    }
}

bool GuiSound::IsPlaying() {
    Voice *v = SoundHandler::instance()->getVoice(voice);
    if (v) {
        return v->getState() == Voice::STATE_PLAYING;
    }
    return false;
}

void GuiSound::SetVolume(uint32_t vol) {
    if (vol > 100) {
        vol = 100;
    }

    uint32_t volumeConv = ((0x8000 * vol) / 100) << 16;

    Voice *v = SoundHandler::instance()->getVoice(voice);
    if (v) {
        v->setVolume(volumeConv);
    }
}

void GuiSound::SetLoop(bool l) {
    SoundDecoder *decoder = SoundHandler::instance()->getDecoder(voice);
    if (decoder) {
        decoder->SetLoop(l);
    }
}

void GuiSound::Rewind() {
    Stop();
}

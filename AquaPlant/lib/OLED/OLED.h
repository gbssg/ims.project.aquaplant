#pragma once

void oledSetup();
void emojiSad2();
void emojiHappy2();
void emojiMeh2();
void sadEmojiAnimation();
void wateringFrame();
void mehEmojiAnimation();
void happyEmojiAnimation();
void playAnimation(uint8_t **array, int maxFrameCount);
enum EmojiType
{
    SAD,
    MEH,
    HAPPY
};

void playEmoji(EmojiType type);
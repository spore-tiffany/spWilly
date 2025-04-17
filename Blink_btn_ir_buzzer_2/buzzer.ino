#include "buzzer.h"
void buzsetup()
{
  pinMode(buzrPin,OUTPUT);
}

void playSong(int x) {
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  //for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
  for (int thisNote = 0; thisNote < x ; thisNote = thisNote + 2) {
    int b = digitalRead(btnPin);
    if(b == false)
    {
      Serial.println("press");
      digitalWrite(ledPin, LOW); 
      break;
    }



    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration*0.5);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}
/*
void playSong2()
{
   for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}
*/
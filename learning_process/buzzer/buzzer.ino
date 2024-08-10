
// buzzer vars
const int buzzer_pin = 9;

void setup(){
    // buzzer pinmode
    pinMode(buzzer_pin, OUTPUT);
}

void loop(){
    beeping();
}


void beeping(){
    tone(buzzer_pin, 400, 150);
    delay(500);
    noTone(buzzer_pin);
    delay(500);    
}

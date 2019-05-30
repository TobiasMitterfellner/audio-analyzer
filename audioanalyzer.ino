int audiopin = A0;
int audio = 0;
String audioString = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(5);
  audio = analogRead(audiopin);
  audioString = "";
  int i = 0;
  while (i < audio/16){
    audioString.concat("|");
    i++;
    }
  Serial.println(audioString);
}

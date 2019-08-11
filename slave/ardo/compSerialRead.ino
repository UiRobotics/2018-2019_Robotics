void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    input = input.substring(1);
    Serial.println(input);
    int data[6] = {0,0,0,0,0,0};
    for (int i = 0; i < 6; i++) {
      data[i] = input.substring(i*3,(i*3)+3).toInt();
    }
  }
}

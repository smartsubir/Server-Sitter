//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.


const int LM_35 = A0;
int input_val = 0;
float celsius = 0;
float farenheit = 0;

void setup() {
  Serial.begin(9600);
}
 

void loop() {

  input_val = analogRead(LM_35);

  celsius = (input_val * 500) / 1023;

  farenheit = ((9 * celsius) / 5) + 32;

  Serial.println("Temp Reading: ");
  Serial.print("\t\tCelsius: ");
  Serial.println(celsius);
  Serial.print("\t\tFarenheit: ");
  Serial.println(farenheit);
  delay(1000);
  }
  

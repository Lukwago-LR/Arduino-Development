/*
  System and Design 3B MOSQUITO TRAP PROJECT
  GROUP A
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Variables for controls and lights
int maxExpected = 1022;
int pinBlue = 9;
int pinGreen = 10;
int buzzer = 7;

//Variables for sensors and LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int sensorA = 11;
int sensorB = 13;
int count_value = 0;





//Methods

//smoothening out analog potentiometer values
int avg(unsigned char pin ) {
  int numReads = 20;
  int sum = 0;
  for (int i = 0; i < numReads; i++) {
    sum += analogRead(pin);
  }

  return sum / numReads;
}



//Analog write - sending different voltage values to the LEDS
void writeToPins(int pinVal, int voltValue) {
  analogWrite(pinVal, voltValue);
}

//Digital write - switching off and on the LEDS
void offPins(int pinVal) {
  digitalWrite(pinVal, LOW);
}

void onPins(int pinVal) {
  digitalWrite(pinVal, HIGH);
}

//displayPatterns method
void displayPatterns(int bluePin , int greenPin) {
  onPins(bluePin);
  delay(50);
  offPins(greenPin);
  delay(50);

  onPins(bluePin);
  delay(50);
  onPins(greenPin);
  delay(50);

  offPins(bluePin);
  delay(50);
  offPins(greenPin);
  delay(50);

  onPins(bluePin);
  offPins(greenPin);
  delay(50);
}

//determining what to display on the LCD for the user
void configLCDDisplay(String displayTitle, String displayPrompt, String displayInfo) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(displayTitle);
  lcd.setCursor(0, 1);
  lcd.print(displayPrompt);
  lcd.print(displayInfo);
  delay(200);
}

//updating functionality as user requires
void updatingFunctionality(int displayPot, int buzzP, int lightP) {

  //switching the device off
  if (displayPot < 101) {
    count_value = 0;
    offPins(buzzer);
    noTone(buzzer);
    offPins(pinBlue);
    offPins(pinGreen);
    offPins(11);
    offPins(20);
    offPins(21);


  } else {
    //analyse the value from potentiometer and send different voltages to the LEDS respectively
    if (lightP < 200) {
      writeToPins(pinBlue, 0);
      writeToPins(pinGreen, 255);
    } else if (lightP > 250 && lightP < 500) {
      writeToPins(pinBlue, 255);
      writeToPins(pinGreen, 0);
    } else if (lightP > 550 && lightP < 800) {
      writeToPins(pinBlue, 255);
      writeToPins(pinGreen, 255);
    } else if (lightP > 850) {
      displayPatterns(pinBlue , pinGreen);
    }

    if (buzzP < 200) {
      //digitalWrite(buzzer, HIGH);
      tone(buzzer, 20);
    } else if (buzzP > 250 && buzzP < 500) {
      //digitalWrite(buzzer, HIGH);
      tone(buzzer, 10);
    } else if (buzzP > 550 && buzzP < 800) {
      //digitalWrite(buzzer, HIGH);
      tone(buzzer, 30);
    }

    //Updating the sensor counter
    int temp1 = digitalRead(sensorA);
    int temp2 = digitalRead(sensorB);

    if (temp1 == 0 || temp2 == 0)
    {
      count_value++;
    }  

  }
}

//OverAll Display Functionality
void displaying(int displayPot, int buzzP, int lightP) {

  switch (displayPot) {

    case 0 ... 100: {
        configLCDDisplay("Off Mode", "State: ", "None");
      }
      break;
    //controlling the lights
    case 101 ... 400:
      {
        if (lightP < 200) {
          configLCDDisplay("Light Mode", "Level: ", "1");
        } else if (lightP > 250 && lightP < 500) {
          configLCDDisplay("Light Mode", "Level: ", "2");
        } else if (lightP > 550 && lightP < 800) {
          configLCDDisplay("Light Mode", "Level: ", "3");
        } else if (lightP > 850) {
          configLCDDisplay("Light Mode", "State: ", "Patterns");
        } else {
          configLCDDisplay("Buffering", "State: ", "Tuning");
        }
      }
      break;

    case 450 ... 700: {
        if (buzzP < 200) {
          configLCDDisplay("Sound Mode", "Level: ", "1");
        } else if (buzzP > 250 && buzzP < 500) {
          configLCDDisplay("Sound Mode", "Level: ", "2");
        } else if (buzzP > 550 && buzzP < 800) {
          configLCDDisplay("Sound Mode", "Level: ", "3");
        } else {
          configLCDDisplay("Buffering", "State: ", "Tuning");
        }
      }
      break;
    //displaying sensor information
    case 750 ... 1200: {
        //then call configLCDDisplay
        lcd.setCursor(0, 0);
        lcd.print("Mosquitoes No");
        lcd.setCursor(0, 1);
        lcd.print("Count: ");
        lcd.print(count_value);
      }
      break;
    default: {

      }
      break;

  }

}



// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(9600);
  // initialize digital pins as an output.
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);

  //At the start, all the parameters are at their minimum
  writeToPins(pinBlue, 5);
  writeToPins(pinGreen, 5);
  tone(buzzer, 5);

  //initialise the LCD properties
  lcd.init();
  lcd.backlight();
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
}





// the loop function runs over and over again forever
void loop() {
  //read the potetiometer value (between 0 and 1023)
  int potentiometerVal = avg(A0);

  //read buzzer potentiometer
  int potBuzz = avg(A4);
  Serial.println(potBuzz);

  //The second potentiometer for chosing the parameter being displayed
  int pot2 = avg(A2);

  updatingFunctionality(pot2, potBuzz, potentiometerVal);
  displaying(pot2, potBuzz, potentiometerVal);
}

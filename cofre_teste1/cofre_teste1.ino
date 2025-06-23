#include <Keypad.h>
#include <Servo.h>

#define piezoPino 2 
#define servoPino 11

Servo servo_Motor;
const char* password = "123"; 
String inputPassword = "";   

bool alarmeAtivado = false;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {8, 7, 6, 1};
byte colPins[COLS] = {5, 4, 3, 0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(piezoPino, OUTPUT);

  servo_Motor.attach(servoPino);
  setLocked(true);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == '*') {
      inputPassword = "";
      setLocked(true);
      pararAlarme();
    }
    else if (key == 'D') {
      // Quando aperta D, verifica a senha
      if (inputPassword == password) {
        setLocked(false); 
        pararAlarme();
      } else {
        setLocked(true); 
        ativarAlarme();
      }
      inputPassword = ""; 
    }
    else if (key == '0') {
      
      pararAlarme();
    }
    else {
      inputPassword += key; 
    }
  }
  
  delay(100);
}

void setLocked(bool locked) {
  if (locked) {
    servo_Motor.write(82);
  } else {
    servo_Motor.write(180);
  }
}

void ativarAlarme() {
  tone(piezoPino, 1000); 
  alarmeAtivado = true;
}

void pararAlarme() {
  noTone(piezoPino);
  alarmeAtivado = false;
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


 
// No Tinkercad, ajuste para 0x20 ou 0x27 conforme o endereço do seu LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
const int BTN_PEDRA = 2;
const int BTN_PAPEL = 3;
const int BTN_TESOURA = 4;
 
// 0 = Pedra, 1 = Papel, 2 = Tesoura
const char* nomes[3] = {"Pedra", "Papel", "Tesoura"};
 
int placarJogador = 0;
int placarCPU = 0;
 
void mostrarTelaInicial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JOKENPO! Escolha");
  lcd.setCursor(0, 1);
  lcd.print("1:Ped 2:Pap 3:Tes");
}
 
void jogarRodada(int escolhaJogador) {
  int escolhaCPU = random(0, 3);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vc:");
  lcd.print(nomes[escolhaJogador]);
  lcd.print(" CPU:");
  lcd.print(nomes[escolhaCPU]);
 
  lcd.setCursor(0, 1);
  if (escolhaJogador == escolhaCPU) {
    lcd.print("Empate! ");
  } else if (
    (escolhaJogador == 0 && escolhaCPU == 2) ||
    (escolhaJogador == 1 && escolhaCPU == 0) ||
    (escolhaJogador == 2 && escolhaCPU == 1)
  ) {
    placarJogador++;
    lcd.print("Vc venceu! ");
  } else {
    placarCPU++;
    lcd.print("CPU venceu!");
  }
 
  lcd.setCursor(11, 1);
  lcd.print(placarJogador);
  lcd.print("x");
  lcd.print(placarCPU);
 
  delay(2500);
  mostrarTelaInicial();
}
 
void setup() {
  pinMode(BTN_PEDRA, INPUT_PULLUP);
  pinMode(BTN_PAPEL, INPUT_PULLUP);
  pinMode(BTN_TESOURA, INPUT_PULLUP);
  Serial.begin(9600);
 
  randomSeed(analogRead(A0));
 
  lcd.init();
  lcd.backlight();
  mostrarTelaInicial();
}
 
void loop() {
  if (digitalRead(BTN_PEDRA) == LOW) {
    delay(200);
    jogarRodada(0);
  } else if (digitalRead(BTN_PAPEL) == LOW) {
    delay(200);
    jogarRodada(1);
  } else if (digitalRead(BTN_TESOURA) == LOW) {
    delay(200);
    jogarRodada(2);
  }
}
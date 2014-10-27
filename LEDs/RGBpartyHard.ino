#define R_PIN 10                    //пин с красным светодиодом 10
#define G_PIN 9                     //пин с зеленым светодиодом 9
#define B_PIN 3                     //пин с синим светодиодом 3

void setup(){
  randomSeed (0);                   //инициализация рандома
}

void loop(){
  analogWrite(R_PIN,random(0,255)); //рандомная якрость на красном светодиоде
  analogWrite(G_PIN,random(0,255)); //рандомная яркость на зеленом светодиоде
  analogWrite(B_PIN,random(0,255)); //рандомная яркость на синем светодиоде
  if (millis()%1000==0){            //если с начала работы программы прошло целое количество секунд
    digitalWrite (R_PIN,HIGH);      //выключаем красный светодиод
    digitalWrite (G_PIN,HIGH);      //выключаем зеленый светодиод
    digitalWrite (B_PIN,HIGH);      //выключаем синий светодиод
    delay(500);                     //ждем полсекунды
  }
}

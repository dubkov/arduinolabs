void setup(){
  for (int i=2; i<10; i++){   //цикл i от 2 до 9
    pinMode(i, OUTPUT);       //назначаем i-й пин на вывод
  }
}

void loop(){
  for (int i=2; i<10; i++){   //цикл i от 2 до 9
    digitalWrite(i, HIGH);    //зажигаем i-й светодиод
    delay(200);               //ждем 200 миллисекунд
  } 
  for (int i=2; i<10; i++){   //цикл i от 2 до 9
    digitalWrite(i, LOW);     //гасим i-й светодиод
    delay(200);               //ждем 200 миллисекунд
  } 
}

//http://wiki.amperka.ru/Схемы-подключения:подключение-текстового-экрана
//http://files.amperka.ru/datasheets/MT-16S2H.pdf

#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);  // RS-пин, Enable-пин, 4 пина данных
char *p = new char[2];                    // Для преобразования байта в символ

void setup() 
{
    lcd.begin(16, 2); // Иниц
    p[1] = 0;         // Нуль-терминатор после первого символа
}
 
unsigned char i=0,k=0,m=0;
void loop() 
{
    i++;              // Индекс крайне левого отрисованного символа
    for(m=0; m<4; m++)  // Малый сдвиг
    {
        lcd.clear();    // Очистить экран
        for(k=0; k<19; k+=4)  // Большой сдвиг
        {
            lcd.setCursor(k-m, 0);  
            lcd.print(i + k/4);   // Вывести код символа
            lcd.setCursor(k-m, 1);
            *p = i+k/4;           // Залить код символа в байт в массиве
            lcd.print(p);         // Вывести массив (из 1 символа и терминатора)
        }
        delay(200); 
    }
}

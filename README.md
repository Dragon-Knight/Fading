Требуется переработать текст. От помощи не откажусь :)

# Fading
Библиотека реализует простой интерфейс плавного и линейного изменения значения переменных.
Позволяет работать до 255 числами одновременно, причём каждое число может иметь индивидуальные настройки, а именно:
* Минимальное значение, за которое число уйти не может.
* Максимальное значение, за которое число уйти не может.
* Размер одного шага изменения числа.
* Интервал обновления числа в мс.

Библиотека работает с типом `int32_t`, что означает что пределы результирующего числа равны от –2.147.483.648 до 2.147.483.647.

Класс является шаблонным, поэтому при создании экземпляра класса не забудьте указать параметр шаблона, который отвечает за кол-во чисел, с которыми работаем.


### Конструктор
Для удобства, класс имеет два конструктора.

```c
Fading(callback_t callback);
```
Конструктор класса без указания настроек. При создании заполняет все настройки всех чисел нулями.
Параметры: Колбек.


```c
Fading(callback_t callback, int32_t min, int32_t max, uint32_t step, uint32_t interval);
```
Конструктор класса с указанием настроек для всех чисел.
Параметры: Колбек, Минимальное значение числа, Максимальное значение числа, Шаг изменения числа, Интервал обновления числа.


### Колбек
При любом изменение числа вызывается колбек, в котором Вы должны определять нужные Вам действия.
```c
void onFading(uint8_t index, int32_t value, bool complete)
```
Параметры: Индекс числа, Текущее значение, Флаг окончания изменения числа.


### Методы класса
```c
bool SetParam(uint8_t index, int32_t min, int32_t max, uint32_t step, uint32_t interval)
```
Метод устанавливает настройки для конкретного числа.
Параметры: Индекс числа, Минимальное значение числа, Максимальное значение числа, Шаг изменения числа, Интервал обновления числа.


```c
bool SetTo(uint8_t index, int32_t value)
```
Метод устанавливает значение числа.
Параметры: Индекс числа, Значение числа.


```c
bool SetToMin(uint8_t index)
```
Метод устанавливает минимальное значение числа.
Параметры: Индекс числа.


```c
bool SetToMin(uint8_t index)
```
Метод устанавливает максимальное значение числа.
Параметры: Индекс числа.


```c
int32_t Get(uint8_t index, bool force = false)
```
Метод получает текущее значение числа. По умолчанию этот метод вернёт ноль, в случае если в данный момент идёт процесс изменения числа. Это поведение можно изменить с помощью второго параметра, которое вернёт текущее значение числа любом случае.
Параметры: Индекс числа, Флаг принудительного возврата значения.


```c
bool FadeTo(uint8_t index, int32_t value)
```
Метод запускает плавное изменение значение числа.
Параметры: Индекс числа, Значение числа.


```c
bool FadeToMin(uint8_t index)
```
Метод запускает плавное изменение значение числа до минимального значения.
Параметры: Индекс числа.


```c
bool FadeToMin(uint8_t index)
```
Метод запускает плавное изменение значение числа до максимального значения.
Параметры: Индекс числа.


```c
void Processing(uint32_t currentTime = millis())
```
Метод обновления класса. В случае, если в Вашей `loop` функции есть определение текущего времени, то целесообразнее передать это время в качестве параметра.
Параметры: Текущая метра времени.


### Заключение

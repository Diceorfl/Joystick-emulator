# Joystick-emulator  
## Joystick control emulator program/Эмулятор управления джойстиком  

### Для чего это нужно?  
    Приложение помогает подобрать лучшие настройки управления для оборудования, которое управляется при помощи джойстика (например: подъемный кран).  

### Как это работает?
 #### Управление:  
      1.Вся эмуляция джойстика происходит за счет кручения колесика мышки.   
      2.Если крутим вперед, то увеличиваем значение выбранных параметров(угол поворота, скорость, ускорение)  
      3.Если крутим назад, то уменьшаем.  
      4.Если нажимаем на колесико, то значения угла поворота, скорости, ускорения обнуляются.  
      5.Ctrl + колесико мышки вверх/вниз - приблизить/отдалить.
      6.Зажать ЛКМ и двигать мышкой - поворот камеры вокруг объекта.   
      7.Можно загружать несколько моделей одновременно.

 #### Что делать?
      1.После того, как запустили приложение, нажимаем File->Add file(s).    
      2.Добавляем нужную нам STL модель для эмуляции.  
      3.Появляется окно настроек:  
         time - частота шага.  
         coefficient for angle - шаг изменения угла при скроллировании.  
         coefficient for speed - шаг изменения скорости при скроллировании.  
         coefficient for acceleration - шаг изменения ускорения при скроллировании.  
         Select axis of rotation - ось вращения.  
         Set mode - выбор настройки, которую изменяем (угол поворота, скорость, ускорение). Можно выбирать несколько. 
      4.Жмём Ok. 
![](https://github.com/Diceorfl/Joystick-emulator/blob/master/Set%20Time.PNG?raw=true)

 #### Требования для сборки проекта:
      Комплект: Qt5.14.2 MSVC2017 32 или 64 bit.  

![](https://github.com/Diceorfl/Joystick-emulator/blob/master/ex.PNG?raw=true)  
![](https://github.com/Diceorfl/Joystick-emulator/blob/master/ex2.PNG?raw=true)  
![](https://github.com/Diceorfl/Joystick-emulator/blob/master/ex3.PNG?raw=true)

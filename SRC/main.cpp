/*
 * Программа эмулятор управления джойстиком
 * Автор: Канониров Александр
 * Создана: 11.09.2019
 */
#include "simulation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simulation w;
    w.show();

    return a.exec();
}

#include "shortestpath.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShortestPath w;
    w.show();

    return a.exec();
}

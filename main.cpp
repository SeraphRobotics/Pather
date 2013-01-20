
#include <QCoreApplication>
#include "slicer/xygrid.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XYGrid<int> grid;
    grid.setDim(1,1);
    grid(1,1)=1;
    grid.setStepSize(1.0);



    return a.exec();
}

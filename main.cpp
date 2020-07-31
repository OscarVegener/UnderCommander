#include "undercommander.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    UnderCommander w;
    w.show();
    int ret;
    try{
        ret = a.exec();
    }
    catch (const std::bad_alloc &){
        return EXIT_FAILURE;
    }
    return ret;
}

#include <QtGui/QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GoToCellDialog *dialog = new GoToCellDialog;
    GoToCellDialog w;
    w.show();

    return a.exec();
}

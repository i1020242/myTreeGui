#include <QApplication>
#include "tree.h"

int main(int argv, char** argc)
{
    QApplication app(argv, argc);
    cBST *window = new cBST;
    window->setWindowTitle("Binary Tree");
    window->show();

    return app.exec();
}

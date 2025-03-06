#include "frm_login.h"
#include "SqlOperation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.addLibraryPath(a.applicationDirPath() + "/plugins");

    SqlOperation::InitDatabase();

    Frm_Login log;
    log.show();

    SqlOperation::ClearDatabase();
    return a.exec();
}

#ifndef WINDOWSEXPLORERPROPERTIES_H
#define WINDOWSEXPLORERPROPERTIES_H

#include <QString>
#include <qt_windows.h>

class WindowsExplorerProperties
{
public:
    WindowsExplorerProperties(QString &path);
    ~WindowsExplorerProperties();
    void exec();
private:
    SHELLEXECUTEINFO info = {0};
    wchar_t *file;
};

#endif // WINDOWSEXPLORERPROPERTIES_H

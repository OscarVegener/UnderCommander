#include "windowsexplorerproperties.h"

WindowsExplorerProperties::WindowsExplorerProperties(QString &path)
{
    if(!path.isEmpty()){
        info.cbSize = sizeof info;
        file = new wchar_t[path.length() + 1];
        file[path.length()] = '\0';
        path.toWCharArray(file);
        info.lpFile = file;
        info.nShow = SW_SHOW;
        info.fMask = SEE_MASK_INVOKEIDLIST;
        info.lpVerb = L"properties";
    }
}

WindowsExplorerProperties::~WindowsExplorerProperties()
{
    delete file;
}

void WindowsExplorerProperties::exec()
{
    ShellExecuteEx(&info);
}

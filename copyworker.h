#ifndef COPYWORKER_H
#define COPYWORKER_H

#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <filesystem>
#include <QDebug>

using namespace std;

using namespace std::filesystem;

class CopyWorker : public QObject
{
    Q_OBJECT
public:
    explicit CopyWorker(const QString &src, const QString &dst, const copy_options &op, QObject *parent = nullptr);
private:
    QString source;
    QString destination;
    copy_options options;
public slots:
    void start_copying();
    void start_moving();
signals:
    void copying_finished();
};

#endif // COPYWORKER_H

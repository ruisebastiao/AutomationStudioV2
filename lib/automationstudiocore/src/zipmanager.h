#ifndef ZIPMANAGER_H
#define ZIPMANAGER_H

#include <QObject>

#include <sys/stat.h>

#ifdef unix
# include <unistd.h>
# include <utime.h>
#else
# include <direct.h>
# include <io.h>
#endif

#include "unzip.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

#ifdef WIN32
#define USEWIN32IOAPI
#include "iowin32.h"
#endif

class ZipManager : public QObject
{
    Q_OBJECT
    int makedir(const char *newdir);
    int mymkdir(const char *dirname);
    int do_extract_currentfile(unzFile uf, const int *popt_extract_without_path, int *popt_overwrite, const char *password);
    void change_file_date(const char *filename, uLong dosdate, tm_unz tmu_date);
    int do_extract(unzFile uf, int opt_extract_without_path, int opt_overwrite, const char *password);
    int do_extract_onefile(unzFile uf, const char *filename, int opt_extract_without_path, int opt_overwrite, const char *password);
public:
    explicit ZipManager(QObject *parent = nullptr);
    void Unzip(QString zipfile);
signals:

public slots:
};

#endif // ZIPMANAGER_H

#ifndef WRAPPER_QFILE_H
#define WRAPPER_QFILE_H

#include <QtCore/QObject>
#include <QtCore/QFile>
#include "wrapper_QIODevice.h"

class WRAPPER_DLL_EXPORT wrapper_QFile : public wrapper_QFileDevice {

  Q_OBJECT

public:

  Q_INVOKABLE wrapper_QFile() :
    wrapper_QFileDevice(new QFile()) { }
  Q_INVOKABLE wrapper_QFile(const QString &path) :
    wrapper_QFileDevice(new QFile(path)) { }
#ifdef Q_CLANG_QDOC
  Q_INVOKABLE wrapper_QFile(const std::filesystem::path &name) :
    wrapper_QFileDevice(new QFile(name)) { }
#endif

#ifndef QT_NO_QOBJECT
  Q_INVOKABLE explicit wrapper_QFile(QObject *parent) :
    wrapper_QFileDevice(new QFile(parent)) { }
  Q_INVOKABLE wrapper_QFile(const QString &name, QObject *parent) :
    wrapper_QFileDevice(new QFile(name, parent)) { }

#ifdef Q_CLANG_QDOC
  Q_INVOKABLE wrapper_QFile(const std::filesystem::path &path, QObject *parent) :
    wrapper_QFileDevice(new QFile(path, parent)) { }
#endif // Q_CLANG_QDOC
#endif // !QT_NO_QOBJECT

#if 0

    QString fileName() const override;
#if QT_CONFIG(cxx17_filesystem) || defined(Q_CLANG_QDOC)
    std::filesystem::path filesystemFileName() const
    { return QtPrivate::toFilesystemPath(fileName()); }
#endif
    void setFileName(const QString &name);
#ifdef Q_CLANG_QDOC
    void setFileName(const std::filesystem::path &name);
#elif QT_CONFIG(cxx17_filesystem)
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    void setFileName(const T &name)
    {
        setFileName(QtPrivate::fromFilesystemPath(name));
    }
#endif // QT_CONFIG(cxx17_filesystem)

#if defined(Q_OS_DARWIN)
    // Mac always expects filenames in UTF-8... and decomposed...
    static inline QByteArray encodeName(const QString &fileName)
    {
        return fileName.normalized(QString::NormalizationForm_D).toUtf8();
    }
    static QString decodeName(const QByteArray &localFileName)
    {
        // note: duplicated in qglobal.cpp (qEnvironmentVariable)
        return QString::fromUtf8(localFileName).normalized(QString::NormalizationForm_C);
    }
    static inline QString decodeName(const char *localFileName)
    {
        return QString::fromUtf8(localFileName).normalized(QString::NormalizationForm_C);
    }
#else
    static inline QByteArray encodeName(const QString &fileName)
    {
        return fileName.toLocal8Bit();
    }
    static QString decodeName(const QByteArray &localFileName)
    {
        return QString::fromLocal8Bit(localFileName);
    }
    static inline QString decodeName(const char *localFileName)
    {
        return QString::fromLocal8Bit(localFileName);
    }
#endif

    bool exists() const;
    static bool exists(const QString &fileName);
#ifdef Q_CLANG_QDOC
    static bool exists(const std::filesystem::path &fileName);
#elif QT_CONFIG(cxx17_filesystem)
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    static bool exists(const T &fileName)
    {
        return exists(QtPrivate::fromFilesystemPath(fileName));
    }
#endif // QT_CONFIG(cxx17_filesystem)

    QString symLinkTarget() const;
    static QString symLinkTarget(const QString &fileName);
#ifdef Q_CLANG_QDOC
    std::filesystem::path filesystemSymLinkTarget() const;
    static std::filesystem::path filesystemSymLinkTarget(const std::filesystem::path &fileName);
#elif QT_CONFIG(cxx17_filesystem)
    std::filesystem::path filesystemSymLinkTarget() const
    {
        return QtPrivate::toFilesystemPath(symLinkTarget());
    }
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    static std::filesystem::path filesystemSymLinkTarget(const T &fileName)
    {
        return QtPrivate::toFilesystemPath(symLinkTarget(QtPrivate::fromFilesystemPath(fileName)));
    }
#endif // QT_CONFIG(cxx17_filesystem)

    bool remove();
    static bool remove(const QString &fileName);
#ifdef Q_CLANG_QDOC
    static bool remove(const std::filesystem::path &fileName);
#elif QT_CONFIG(cxx17_filesystem)
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    static bool remove(const T &fileName)
    {
        return remove(QtPrivate::fromFilesystemPath(fileName));
    }
#endif // QT_CONFIG(cxx17_filesystem)

    bool moveToTrash();
    static bool moveToTrash(const QString &fileName, QString *pathInTrash = nullptr);
#ifdef Q_CLANG_QDOC
    static bool moveToTrash(const std::filesystem::path &fileName, QString *pathInTrash = nullptr);
#elif QT_CONFIG(cxx17_filesystem)
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    static bool moveToTrash(const T &fileName, QString *pathInTrash = nullptr)
    {
        return moveToTrash(QtPrivate::fromFilesystemPath(fileName), pathInTrash);
    }
#endif // QT_CONFIG(cxx17_filesystem)

    bool rename(const QString &newName);
    static bool rename(const QString &oldName, const QString &newName);
#ifdef Q_CLANG_QDOC
    bool rename(const std::filesystem::path &newName);
    static bool rename(const std::filesystem::path &oldName,
                       const std::filesystem::path &newName);
#elif QT_CONFIG(cxx17_filesystem)
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    bool rename(const T &newName)
    {
        return rename(QtPrivate::fromFilesystemPath(newName));
    }
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    static bool rename(const T &oldName, const T &newName)
    {
        return rename(QtPrivate::fromFilesystemPath(oldName),
                      QtPrivate::fromFilesystemPath(newName));
    }
#endif // QT_CONFIG(cxx17_filesystem)

    bool link(const QString &newName);
    static bool link(const QString &fileName, const QString &newName);
#ifdef Q_CLANG_QDOC
    bool link(const std::filesystem::path &newName);
    static bool link(const std::filesystem::path &fileName,
                     const std::filesystem::path &newName);
#elif QT_CONFIG(cxx17_filesystem)
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    bool link(const T &newName)
    {
        return link(QtPrivate::fromFilesystemPath(newName));
    }
    template<typename T, QtPrivate::ForceFilesystemPath<T> = 0>
    static bool link(const T &fileName, const T &newName)
    {
        return link(QtPrivate::fromFilesystemPath(fileName),
                    QtPrivate::fromFilesystemPath(newName));
    }
#endif // QT_CONFIG(cxx17_filesystem)

    bool copy(const QString &newName);
    static bool copy(const QString &fileName, const QString &newName);
#ifdef Q_CLANG_QDOC
    bool copy(const std::filesystem::path &newName);
    static bool copy(const std::filesystem::path &fileName,
                     const std::filesystem::path &newName);
#endif // QT_CONFIG(cxx17_filesystem)

#endif

  // bool open(OpenMode flags) override;
  Q_INVOKABLE bool open(wrapper_QIODeviceBase::OpenMode flags) {
    return get_selfptr()->open((QIODeviceBase::OpenMode)(int)flags);
  }
  //  bool open(OpenMode flags, Permissions permissions);
  Q_INVOKABLE bool open(wrapper_QIODeviceBase::OpenMode flags, wrapper_QFileDevice::Permissions permissions) {
    return get_selfptr()->open((QIODeviceBase::OpenMode)(int)flags, (QFileDevice::Permissions)(int)permissions);
  }
  // bool open(FILE *f, OpenMode ioFlags, FileHandleFlags handleFlags=DontCloseHandle);
  Q_INVOKABLE bool open(FILE *f, wrapper_QIODeviceBase::OpenMode mode, wrapper_QFileDevice::FileHandleFlags handleFlags = wrapper_QFileDevice::DontCloseHandle) {
    return get_selfptr()->open(f, (QIODeviceBase::OpenMode)(int)mode, (QFileDevice::FileHandleFlags)(int)handleFlags);
  }
  // bool open(int fd, OpenMode ioFlags, FileHandleFlags handleFlags=DontCloseHandle);
  Q_INVOKABLE bool open(int fd, wrapper_QIODeviceBase::OpenMode mode, wrapper_QFileDevice::FileHandleFlags handleFlags = wrapper_QFileDevice::DontCloseHandle) {
    return get_selfptr()->open(fd, static_cast<QIODeviceBase::OpenMode>(static_cast<int>(mode)), static_cast<QFileDevice::FileHandleFlags>(static_cast<int>(handleFlags)));
  }

  // qint64 size() const override;
  Q_INVOKABLE qint64 size() const {
    return get_selfptr()->size();
  }


#if 0

    bool resize(qint64 sz) override;
    static bool resize(const QString &filename, qint64 sz);

    Permissions permissions() const override;
    static Permissions permissions(const QString &filename);
    bool setPermissions(Permissions permissionSpec) override;
    static bool setPermissions(const QString &filename, Permissions permissionSpec);
#ifdef Q_CLANG_QDOC
    static Permissions permissions(const std::filesystem::path &filename);
    static bool setPermissions(const std::filesystem::path &filename, Permissions permissionSpec);
#endif // Q_CLANG_QDOC

#endif

public:

  // Конструктор из объекта
  explicit wrapper_QFile(QFile* self) :
    wrapper_QFileDevice(static_cast<QFileDevice*>(self)) {
    qDebug() << "wrapper_QFile::constructor(self=" << reinterpret_cast<unsigned long long>(self) << ")";
  }

  // Деструктор
  virtual ~wrapper_QFile() {
    delete static_cast<QFile*>(wrapper_QFileDevice::get_selfptr());
  }

  // Получение константного указателя на объект
  const QFile* get_selfptr() const {
    return static_cast<const QFile*>(wrapper_QFileDevice::get_selfptr());
  }

  // Получение указателя на объект
  QFile* get_selfptr() {
    return static_cast<QFile*>(wrapper_QFileDevice::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QFile);

#endif // WRAPPER_QFILE_H

#ifndef WRAPPER_QIODEVICE_H
#define WRAPPER_QIODEVICE_H

#include <QtCore/QObject>
#include <QtCore/QIODevice>
#include <QtCore/QFileDevice>
#include "wrapper_common.h"
#include "wrapper_QObject.h"

class WRAPPER_DLL_EXPORT wrapper_QIODeviceBase : public wrapper_common {

  Q_OBJECT

public:

  enum OpenModeFlag {
    NotOpen = 0x0000,
    ReadOnly = 0x0001,
    WriteOnly = 0x0002,
    ReadWrite = ReadOnly | WriteOnly,
    Append = 0x0004,
    Truncate = 0x0008,
    Text = 0x0010,
    Unbuffered = 0x0020,
    NewOnly = 0x0040,
    ExistingOnly = 0x0080
  };

  Q_ENUM(OpenModeFlag)
  Q_DECLARE_FLAGS(OpenMode, OpenModeFlag)
  Q_FLAGS(OpenMode)

public:

  // Конструктор из объекта
  explicit wrapper_QIODeviceBase(QIODeviceBase* self) :
    wrapper_common(self) {
    qDebug() << "wrapper_QIODeviceBase::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор (объект QIODeviceBase не удаляется)
  virtual ~wrapper_QIODeviceBase() {
  }

  // Получение константного указателя на объект
  const QIODeviceBase* get_selfptr() const {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QIODeviceBase::get_selfptr - got nullptr";
    }
    return static_cast<const QIODeviceBase*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QIODeviceBase* get_selfptr() {
    if (wrapper_common::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QIODeviceBase::get_selfptr - got nullptr";
    }
    return static_cast<QIODeviceBase*>(wrapper_common::get_selfptr());
  }
};

class wrapper_QIODevice
#ifndef QT_NO_QOBJECT
    : // virtual public wrapper_QObject,
#else
    :
#endif
      public wrapper_QIODeviceBase {

  Q_OBJECT

#if 0
    QIODevice();
#ifndef QT_NO_QOBJECT
    explicit QIODevice(QObject *parent);
#endif
    virtual ~QIODevice();

    QIODeviceBase::OpenMode openMode() const;

    void setTextModeEnabled(bool enabled);
    bool isTextModeEnabled() const;

    bool isOpen() const;
    bool isReadable() const;
    bool isWritable() const;
    virtual bool isSequential() const;

    int readChannelCount() const;
    int writeChannelCount() const;
    int currentReadChannel() const;
    void setCurrentReadChannel(int channel);
    int currentWriteChannel() const;
    void setCurrentWriteChannel(int channel);

    virtual bool open(QIODeviceBase::OpenMode mode);
    virtual void close();

    // ### Qt 7 - QTBUG-76492: pos() and seek() should not be virtual, and
    // ### seek() should call a virtual seekData() function.
    virtual qint64 pos() const;
    virtual qint64 size() const;
    virtual bool seek(qint64 pos);
    virtual bool atEnd() const;
    virtual bool reset();

    virtual qint64 bytesAvailable() const;
    virtual qint64 bytesToWrite() const;

    qint64 read(char *data, qint64 maxlen);
    QByteArray read(qint64 maxlen);
    QByteArray readAll();
    qint64 readLine(char *data, qint64 maxlen);
    QByteArray readLine(qint64 maxlen = 0);
    virtual bool canReadLine() const;

    void startTransaction();
    void commitTransaction();
    void rollbackTransaction();
    bool isTransactionStarted() const;

    qint64 write(const char *data, qint64 len);
    qint64 write(const char *data);
    qint64 write(const QByteArray &data);

    qint64 peek(char *data, qint64 maxlen);
    QByteArray peek(qint64 maxlen);
    qint64 skip(qint64 maxSize);

    virtual bool waitForReadyRead(int msecs);
    virtual bool waitForBytesWritten(int msecs);

    void ungetChar(char c);
    bool putChar(char c);
    bool getChar(char *c);

    QString errorString() const;

#ifndef QT_NO_QOBJECT
Q_SIGNALS:
    void readyRead();
    void channelReadyRead(int channel);
    void bytesWritten(qint64 bytes);
    void channelBytesWritten(int channel, qint64 bytes);
    void aboutToClose();
    void readChannelFinished();
#endif

#endif

public:

  // Конструктор из объекта
  explicit wrapper_QIODevice(QIODevice* self) :
    wrapper_QIODeviceBase(self) {
    qDebug() << "wrapper_QIODevice::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QIODevice() {
    delete static_cast<QIODevice*>(wrapper_QIODeviceBase::get_selfptr());
  }

  // Получение константного указателя на объект
  const QIODevice* get_selfptr() const {
    if (wrapper_QIODeviceBase::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QIODevice::get_selfptr - got nullptr";
    }
    return static_cast<const QIODevice*>(wrapper_QIODeviceBase::get_selfptr());
  }

  // Получение указателя на объект
  QIODevice* get_selfptr() {
    if (wrapper_QIODeviceBase::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QIODevice::get_selfptr - got nullptr";
    }
    return static_cast<QIODevice*>(wrapper_QIODeviceBase::get_selfptr());
  }


};

class wrapper_QFileDevice : public wrapper_QIODevice {

  Q_OBJECT

public:

    enum FileError {
        NoError = 0,
        ReadError = 1,
        WriteError = 2,
        FatalError = 3,
        ResourceError = 4,
        OpenError = 5,
        AbortError = 6,
        TimeOutError = 7,
        UnspecifiedError = 8,
        RemoveError = 9,
        RenameError = 10,
        PositionError = 11,
        ResizeError = 12,
        PermissionsError = 13,
        CopyError = 14
    };

    enum FileTime {
        FileAccessTime,
        FileBirthTime,
        FileMetadataChangeTime,
        FileModificationTime
    };

    enum Permission {
        ReadOwner = 0x4000, WriteOwner = 0x2000, ExeOwner = 0x1000,
        ReadUser  = 0x0400, WriteUser  = 0x0200, ExeUser  = 0x0100,
        ReadGroup = 0x0040, WriteGroup = 0x0020, ExeGroup = 0x0010,
        ReadOther = 0x0004, WriteOther = 0x0002, ExeOther = 0x0001
    };
    Q_DECLARE_FLAGS(Permissions, Permission)

    enum FileHandleFlag {
        AutoCloseHandle = 0x0001,
        DontCloseHandle = 0
    };
    Q_DECLARE_FLAGS(FileHandleFlags, FileHandleFlag)

#if 0
    ~QFileDevice();

    FileError error() const;
    void unsetError();

    void close() override;

    bool isSequential() const override;

    int handle() const;
    virtual QString fileName() const;

    qint64 pos() const override;
    bool seek(qint64 offset) override;
    bool atEnd() const override;
    bool flush();

    qint64 size() const override;

    virtual bool resize(qint64 sz);
    virtual Permissions permissions() const;
    virtual bool setPermissions(Permissions permissionSpec);

    enum MemoryMapFlag {
        NoOptions = 0,
        MapPrivateOption = 0x0001
    };
    Q_DECLARE_FLAGS(MemoryMapFlags, MemoryMapFlag)

    uchar *map(qint64 offset, qint64 size, MemoryMapFlags flags = NoOptions);
    bool unmap(uchar *address);

    QDateTime fileTime(QFileDevice::FileTime time) const;
    bool setFileTime(const QDateTime &newDate, QFileDevice::FileTime fileTime);
#endif

public:

  // Конструктор из объекта
  explicit wrapper_QFileDevice(QFileDevice* self) :
    wrapper_QIODevice(self) {
    qDebug() << "wrapper_QFileDevice::constructor(self=" << (unsigned long long)self << ")";
  }

  // Деструктор
  virtual ~wrapper_QFileDevice() {
    qDebug() << "wrapper_QFileDevice::destructor";
    //!!! не должен удаляться! delete static_cast<QFileDevice*>(wrapper_QIODevice::get_selfptr());
  }

  // Получение константного указателя на объект
  const QFileDevice* get_selfptr() const {
    if (wrapper_QIODevice::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QFileDevice::get_selfptr - got nullptr";
    }
    return static_cast<const QFileDevice*>(wrapper_QIODevice::get_selfptr());
  }

  // Получение указателя на объект
  QFileDevice* get_selfptr() {
    if (wrapper_QIODevice::get_selfptr() == nullptr) {
      qCritical() << "wrapper_QFileDevice::get_selfptr - got nullptr";
    }
    return static_cast<QFileDevice*>(wrapper_QIODevice::get_selfptr());
  }
};

Q_DECLARE_METATYPE(wrapper_QIODeviceBase);
Q_DECLARE_METATYPE(wrapper_QIODevice);
Q_DECLARE_METATYPE(wrapper_QFileDevice);

#endif // WRAPPER_QIODEVICE_H

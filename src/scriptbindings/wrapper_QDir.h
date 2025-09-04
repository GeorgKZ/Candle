#ifndef WRAPPER_QDIR_H
#define WRAPPER_QDIR_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include "wrapper_common.h"

class WRAPPER_DLL_EXPORT wrapper_QDir : public wrapper_common {

  Q_OBJECT

  // Из файла qdir.h
public:

  enum Filter { Dirs        = 0x001,
                Files       = 0x002,
                Drives      = 0x004,
                NoSymLinks  = 0x008,
                AllEntries  = Dirs | Files | Drives,
                TypeMask    = 0x00f,

                Readable    = 0x010,
                Writable    = 0x020,
                Executable  = 0x040,
                PermissionMask    = 0x070,

                Modified    = 0x080,
                Hidden      = 0x100,
                System      = 0x200,

                AccessMask  = 0x3F0,

                AllDirs       = 0x400,
                CaseSensitive = 0x800,
                NoDot         = 0x2000,
                NoDotDot      = 0x4000,
                NoDotAndDotDot = NoDot | NoDotDot,

                NoFilter = -1
  };

  Q_ENUM(Filter)
  Q_DECLARE_FLAGS(Filters, Filter)
  Q_FLAGS(Filters)

  enum SortFlag { Name        = 0x00,
                  Time        = 0x01,
                  Size        = 0x02,
                  Unsorted    = 0x03,
                  SortByMask  = 0x03,

                  DirsFirst   = 0x04,
                  Reversed    = 0x08,
                  IgnoreCase  = 0x10,
                  DirsLast    = 0x20,
                  LocaleAware = 0x40,
                  Type        = 0x80,
                  NoSort = -1
  };

  Q_ENUM(SortFlag)
  Q_DECLARE_FLAGS(SortFlags, SortFlag)
  Q_FLAGS(SortFlags)

//  Q_INVOKABLE wrapper_QDir(const wrapper_QDir &obj) :
//    wrapper_common(new QDir(*obj.get_selfptr()))  { }

  Q_INVOKABLE wrapper_QDir(const QString &path = QString()) :
    wrapper_common(new QDir(path)) { }

  Q_INVOKABLE wrapper_QDir(const QString &path, const QString &nameFilter, SortFlags sort = SortFlags(Name | IgnoreCase), Filters filter = AllEntries) :
    wrapper_common(new QDir(path, nameFilter, (QDir::SortFlags)(int)sort, (QDir::Filters)(int)filter)) { }

#ifdef Q_CLANG_QDOC
  Q_INVOKABLE wrapper_QDir(const std::filesystem::path &path) :
    wrapper_common(new QDir(path)) { }

  Q_INVOKABLE wrapper_QDir(const std::filesystem::path &path, const QString &nameFilter, SortFlags sort = SortFlags(Name | IgnoreCase), Filters filter = AllEntries) :
    wrapper_common(new QDir(path, nameFilter, (QDir::SortFlags)(int)sort, (QDir::Filters)(int)filter)) { }
#endif

//!!! Оператор присваивания не требуется!
//  Q_INVOKABLE QJSValue operator=(const QJSValue &other) {
//    qDebug() << "wrapper_QDir::operator=";
//    get_selfptr()->operator=(*jsvalueToPointer(QDir, other));
//    return PointerToJsvalue(QDir, get_selfptr());
//  }

  Q_INVOKABLE void swap(wrapper_QDir &other) { get_selfptr()->swap(*other.get_selfptr()); }

  Q_INVOKABLE void setPath(const QString &path) { get_selfptr()->setPath(path); }
  Q_INVOKABLE QString path() const { return get_selfptr()->path(); }
  Q_INVOKABLE QString absolutePath() const { return get_selfptr()->absolutePath(); }
  Q_INVOKABLE QString canonicalPath() const { return get_selfptr()->canonicalPath(); }
#if QT_CONFIG(cxx17_filesystem) || defined(Q_CLANG_QDOC)
  Q_INVOKABLE std::filesystem::path filesystemPath() const { return get_selfptr()->filesystemPath(); }
  Q_INVOKABLE std::filesystem::path filesystemAbsolutePath() const { return get_selfptr()->filesystemAbsolutePath(); }
  Q_INVOKABLE std::filesystem::path filesystemCanonicalPath() const { return get_selfptr()->filesystemCanonicalPath(); }
#endif

  Q_INVOKABLE static void setSearchPaths(const QString &prefix, const QStringList &searchPaths) { QDir::setSearchPaths(prefix, searchPaths); }
  Q_INVOKABLE static void addSearchPath(const QString &prefix, const QString &path) { QDir::addSearchPath(prefix, path); }
#ifdef Q_CLANG_QDOC
  Q_INVOKABLE static void addSearchPath(const QString &prefix, const std::filesystem::path &path) { QDir::AddSearchPath(prefix, path); }
#endif
  Q_INVOKABLE static QStringList searchPaths(const QString &prefix) { return QDir::searchPaths(prefix); }

  Q_INVOKABLE QString dirName() const { return get_selfptr()->dirName(); }
  Q_INVOKABLE QString filePath(const QString &fileName) const { return get_selfptr()->filePath(fileName); }
  Q_INVOKABLE QString absoluteFilePath(const QString &fileName) const { return get_selfptr()->absoluteFilePath(fileName); }
  Q_INVOKABLE QString relativeFilePath(const QString &fileName) const { return get_selfptr()->relativeFilePath(fileName); }

  Q_INVOKABLE static QString toNativeSeparators(const QString &pathName) { return QDir::toNativeSeparators(pathName); }
  Q_INVOKABLE static QString fromNativeSeparators(const QString &pathName) { return QDir::fromNativeSeparators(pathName); }

  Q_INVOKABLE bool cd(const QString &dirName) { return get_selfptr()->cd(dirName); }
  Q_INVOKABLE bool cdUp() { return get_selfptr()->cdUp(); }

//  Q_INVOKABLE QStringList nameFilters() const;
//  Q_INVOKABLE void setNameFilters(const QStringList &nameFilters);

//  Q_INVOKABLE Filters filter() const;
//  Q_INVOKABLE void setFilter(Filters filter);
//  Q_INVOKABLE SortFlags sorting() const;
//  Q_INVOKABLE void setSorting(SortFlags sort);

//  Q_INVOKABLE uint count() const;
//  Q_INVOKABLE  bool isEmpty(Filters filters = Filters(Filter::AllEntries | Filter::NoDotAndDotDot)) const;

//  Q_INVOKABLE QString operator[](int i) const;

//  Q_INVOKABLE  static QStringList nameFiltersFromString(const QString &nameFilter);

//  Q_INVOKABLE  QStringList entryList1(Filters filters = Filter::NoFilter, SortFlags sort = SortFlag::NoSort) const;

//  Q_INVOKABLE  QStringList entryList2(const QStringList &nameFilters, Filters filters = Filter::NoFilter, SortFlags sort = SortFlag::NoSort) const;

//  QFileInfoList entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
//  QFileInfoList entryInfoList(const QStringList &nameFilters, Filters filters = NoFilter, SortFlags sort = NoSort) const;

//  Q_INVOKABLE bool mkdir(const QString &dirName) const;
//  Q_INVOKABLE bool rmdir(const QString &dirName) const;
//  Q_INVOKABLE bool mkpath(const QString &dirPath) const;
//  Q_INVOKABLE bool rmpath(const QString &dirPath) const;

//  Q_INVOKABLE bool removeRecursively();

//  Q_INVOKABLE bool isReadable() const;
//  Q_INVOKABLE bool exists() const;
//  Q_INVOKABLE bool isRoot() const;

//  Q_INVOKABLE static bool isRelativePath(const QString &path);
//  Q_INVOKABLE static bool isAbsolutePath(const QString &path);
//  Q_INVOKABLE bool isRelative() const;
//  Q_INVOKABLE bool isAbsolute() const;
//  Q_INVOKABLE bool makeAbsolute();

//  Q_INVOKABLE bool operator==(const wrapper_QDir &dir) const;
//  Q_INVOKABLE bool operator!=(const wrapper_QDir &dir) const;

  Q_INVOKABLE bool remove(const QString &fileName) { return get_selfptr()->remove(fileName); }
  Q_INVOKABLE bool rename(const QString &oldName, const QString &newName) { return get_selfptr()->rename(oldName, newName); }
  Q_INVOKABLE bool exists(const QString &name) const { return get_selfptr()->exists(name); }
//!!! new unknown type
  Q_INVOKABLE static QFileInfoList drives() { return QDir::drives(); }

  Q_INVOKABLE static QChar listSeparator() { return QDir::listSeparator(); }

  Q_INVOKABLE static QChar separator() { return QDir::separator(); }

    Q_INVOKABLE static bool setCurrent(const QString &path)
    {
        return QDir::setCurrent(path);
    }

    Q_INVOKABLE QJSValue current()
    {
//      return wrapperFactory("QDir", new QDir(QDir::current()));
        return PointerToJsvalue(QDir, new QDir(QDir::current()));
    }

    Q_INVOKABLE static QString currentPath()  { return QDir::currentPath(); }

    Q_INVOKABLE QJSValue home()
    {
//      return wrapperFactory("QDir", new QDir(QDir::home()));
        return PointerToJsvalue(QDir, new QDir(QDir::home()));
    }

    Q_INVOKABLE static QString homePath()     { return QDir::homePath(); }

    Q_INVOKABLE QJSValue root()
    {
//      return wrapperFactory("QDir", new QDir(QDir::root()));
        return PointerToJsvalue(QDir, new QDir(QDir::root()));
    }

    Q_INVOKABLE static QString rootPath()     { return QDir::rootPath(); }

    Q_INVOKABLE QJSValue temp()
    {
//      return wrapperFactory("QDir", new QDir(QDir::temp()));
        return PointerToJsvalue(QDir, new QDir(QDir::temp()));
    }

    Q_INVOKABLE static QString tempPath()     { return QDir::tempPath(); }

#ifndef QT_NO_REGEXP
    Q_INVOKABLE static bool match(const QStringList &filters, const QString &fileName) { return QDir::match(filters, fileName); }
    Q_INVOKABLE static bool match(const QString &filter, const QString &fileName) { return QDir::match(filter, fileName); }
#endif

    Q_INVOKABLE static QString cleanPath(const QString &path) { return QDir::cleanPath(path);}
    Q_INVOKABLE void refresh() const { get_selfptr()->refresh(); }

public:

  // Конструктор из объекта
  explicit wrapper_QDir(void *self) : wrapper_common(self) {
    qDebug() << "wrapper_QDir::constructor(self=" << get_selfvalue() << ")";
  }

  // Получение константного указателя на объект
  const QDir* get_selfptr() const {
    return static_cast<const QDir*>(wrapper_common::get_selfptr());
  }

  // Получение указателя на объект
  QDir* get_selfptr() {
    return static_cast<QDir*>(wrapper_common::get_selfptr());
  }

  // Деструктор
  virtual ~wrapper_QDir() override {
    qDebug() << "wrapper_QDir::destructor(self=" << get_selfvalue() << ")";
  }
};

Q_DECLARE_METATYPE(wrapper_QDir)

#endif // WRAPPER_QDIR_H

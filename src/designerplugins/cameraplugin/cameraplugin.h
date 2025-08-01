#ifndef CAMERAPLUGIN_H
#define CAMERAPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class CameraPlugin: public QObject, QDesignerCustomWidgetInterface
{

#if !defined(__DOXYGEN__)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)
#endif

public:

    /**
     * \brief Конструктор
     * \param [in] parent Родительский объект
     */
    explicit CameraPlugin(QObject *parent = nullptr);

    bool isContainer() const override;
    bool isInitialized() const override;
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override;
    QString includeFile() const override;
    QString name() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QWidget *createWidget(QWidget *parent) override;
    void initialize(QDesignerFormEditorInterface *core) override;

private:

    bool m_initialized;
};

#endif // CAMERAPLUGIN_H

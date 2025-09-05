#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class CustomWidgetsPlugin: public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
#if !defined(__DOXYGEN__)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
#endif

public:
    CustomWidgetsPlugin(QObject *parent = nullptr);

    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};

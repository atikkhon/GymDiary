#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <diarymodel.h>
#include <repsmodel.h>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QQuickStyle::setStyle("Fusion");
    QGuiApplication app(argc, argv);

    qmlRegisterType<DiaryModel>("DiaryModel", 0, 1, "DiaryModel");

    qmlRegisterType<RepsModel>("RepsModel", 0, 1, "RepsModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

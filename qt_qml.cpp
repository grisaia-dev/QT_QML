#include <stdlib.h>
#include <cstdint>
#include <QtWidgets/qapplication.h>
#include <QtQml/qqmlapplicationengine.h>
#include <QtCharts/qchart.h>
#include <QtChartsQml/qtchartsqmlexports.h>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru_RU");
	QApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.addImportPath(":/imports");
	const QUrl url(QStringLiteral("qrc:/imports/Qtqml/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, 
		[url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl) { QCoreApplication::exit(EXIT_FAILURE); }
		}, Qt::QueuedConnection);
	engine.load(url);

	int16_t rc = app.exec();
	return rc;
}

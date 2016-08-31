#include "hatsu.h"
//#include "splash.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#pragma comment(lib,"Shell32.lib")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSplashScreen s;
	s.setPixmap(QPixmap(":/Hatsu/Resources/splash.png"));
	/*splash screen from: http://adh5.diverse.jp/ */
	s.show();
	s.showMessage(QString::fromLocal8Bit("\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n载入主界面...   ")
		, Qt::AlignVCenter |Qt::AlignRight, Qt::white);
	Hatsu w;
	s.finish(&w);
	w.show();
	return a.exec();
}

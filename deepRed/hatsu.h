#ifndef HATSU_H
#define HATSU_H

#include <QtWidgets/QMainWindow>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QList>
#include <QMessageBox>
#include <QCloseEvent>
#include "ui_hatsu.h"
#include "encoderinfo.h"
#include "..\scripteditor\syntaxhighlighter.h"

class Hatsu : public QMainWindow
{
	Q_OBJECT

public:
	Hatsu(QWidget *parent = 0);
	void QmsgCritical(QString a, QString b);
	void QstartEncoder(QString x264encoderParams,
		QString muxParams);
	~Hatsu();

signals:
	void msgCritical(QString a, QString b) const;
	void startEncoder(QString x264encoderParams,
		QString muxParams) const;

public slots:
	int toCompress();
	int SelectVideoFile();
	int SelectAudioFile();
	void msgCriticalSlot(const QString & a, const QString & b) const;
	void startEncoderSlot(const QString & x264encoderParams,
		const QString & muxParams);

protected:
	void Hatsu::dragEnterEvent(QDragEnterEvent *mevent);
	void Hatsu::dropEvent(QDropEvent *mevent);

private:
	Ui::HatsuClass ui;
	SyntaxHighlighter* highlighter;
	encoderinfo* e;
	const QString about = QString::fromLocal8Bit(
R"(历时3天，原生支持vs脚本的视频压制GUI《彩》终于完工。
此为 “深红” 版本。
alpha 0.01
使用了以下开源项目：
vapoursynth，x264
ffmpeg，Qt
mawen's mvsfunc
参考了以下开源项目:
vseditor
背景图来自：http://adh5.diverse.jp/
由MikaPikazo(
http://mikapikazo.tumblr.com/
http://www.pixiv.net/member_illust.php?id=1039353
)所绘。
x264为我编译的版本，支持vapoursynth：
https://github.com/MoePus/vapoursynth-source-filter-for-x264
ffmpeg由esterTion（http://estertion.win）编译。
特别感谢以上全员。

song_5007
www.moepus.com
2016.8.30
)"
	);
};

#endif // HATSU_H

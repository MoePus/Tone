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
R"(��ʱ3�죬ԭ��֧��vs�ű�����Ƶѹ��GUI���ʡ������깤��
��Ϊ ����족 �汾��
alpha 0.01
ʹ�������¿�Դ��Ŀ��
vapoursynth��x264
ffmpeg��Qt
mawen's mvsfunc
�ο������¿�Դ��Ŀ:
vseditor
����ͼ���ԣ�http://adh5.diverse.jp/
��MikaPikazo(
http://mikapikazo.tumblr.com/
http://www.pixiv.net/member_illust.php?id=1039353
)���档
x264Ϊ�ұ���İ汾��֧��vapoursynth��
https://github.com/MoePus/vapoursynth-source-filter-for-x264
ffmpeg��esterTion��http://estertion.win�����롣
�ر��л����ȫԱ��

song_5007
www.moepus.com
2016.8.30
)"
	);
};

#endif // HATSU_H

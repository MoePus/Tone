#pragma once
#include "ui_encoderinfo.h"
#include <QWidget>
#include <QProcess>
#include <QCloseEvent>

class encoderinfo:public QWidget
{
	Q_OBJECT
public:
	encoderinfo(QString x264encoderParams,
		QString _muxParams,
		QWidget *parent = 0);
	~encoderinfo();

public slots:
	int printEncoderInfo();
	int muxIt(int exitCode, QProcess::ExitStatus exitStatus);

private:
	Ui::EncoderForm ui;
	QProcess x264Encoder;
	QString muxParams;

protected:
	void closeEvent(QCloseEvent *event);
};
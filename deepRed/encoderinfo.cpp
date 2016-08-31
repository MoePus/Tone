#include "encoderinfo.h"
#include <QProcess>
#include <QDebug>
#include <QScrollBar>

encoderinfo::~encoderinfo()
{
}

int encoderinfo::muxIt(int exitCode, QProcess::ExitStatus exitStatus)
{
	if (!exitCode && ui.infoBox->toPlainText().indexOf("[error]") == -1)
	{
		this->setWindowTitle("Muxing...");
		QProcess ff;
		ff.setProcessChannelMode(QProcess::MergedChannels);
		ff.start(muxParams);
		ff.waitForFinished();
		QString info = ff.readAll();
		ui.infoBox->insertPlainText(info);
		this->setWindowTitle("Finished.");
	}
	else
	{
		this->setWindowTitle("failed.");
	}

	return 1;
}

void encoderinfo::closeEvent(QCloseEvent * event)
{
	x264Encoder.kill();
	event->accept();
}

encoderinfo::encoderinfo(QString x264encoderParams,
	QString _muxParams, QWidget *parent):
	QWidget(parent), x264Encoder(this),
	muxParams(_muxParams)
{
	ui.setupUi(this);
	
	x264Encoder.setProcessChannelMode(QProcess::MergedChannels);
	connect(&x264Encoder, &QProcess::readyRead,
		this, &encoderinfo::printEncoderInfo);

	connect(&x264Encoder, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
		this, &encoderinfo::muxIt);
	x264Encoder.start(x264encoderParams);
}

int encoderinfo::printEncoderInfo()
{
	QRegExp rx("\\[(.{1,8}%)\\] ");
	QString textGet = x264Encoder.readAll();
	if (textGet.indexOf(rx, 0) != -1)
	{
		this->setWindowTitle(rx.cap(1));
		ui.infoBox->insertPlainText(textGet);
		QScrollBar *v = ui.infoBox->verticalScrollBar();
		v->setValue(v->maximum());
	}
	else
	{
		ui.infoBox->insertPlainText(textGet);
	}
	return 1;
}
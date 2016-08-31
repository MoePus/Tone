#include "hatsu.h"
#include <qcommandlinkbutton.h>
#include <QDir>
#include <iostream>
#include <thread>
#include <Tlogic.h>
#include <QFileDialog>

Hatsu::Hatsu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.ScriptEditor->document()->setPlainText(
		R"(import vapoursynth as vs
core = vs.get_core()

clip = getVideoSource()
clip.set_output())");
	highlighter = new SyntaxHighlighter(ui.ScriptEditor->document());

	connect(ui.commandCompress, &QCommandLinkButton::released,this,&Hatsu::toCompress);

	QStringList encoders;
	QDir dir(R"(supportFilles\x264\)");

	for(QFileInfo mfi: dir.entryInfoList())
	{
		if (mfi.isFile() && mfi.fileName().endsWith(".exe"))
		{
			encoders << mfi.fileName();
		}
	}
	ui.x264Selector->addItems(encoders);

	connect(ui.videoSelector, &QPushButton::clicked, this, &Hatsu::SelectVideoFile);
	connect(ui.audioSelector, &QPushButton::clicked, this, &Hatsu::SelectAudioFile);

	connect(this, &Hatsu::msgCritical, this, &Hatsu::msgCriticalSlot);
	connect(this, &Hatsu::startEncoder, this, &Hatsu::startEncoderSlot);

	ui.About->setPlainText(about);
}

Hatsu::~Hatsu()
{

}

void Hatsu::dragEnterEvent(QDragEnterEvent *mevent)
{
	mevent->acceptProposedAction();
}

void Hatsu::dropEvent(QDropEvent *mevent)
{
	const QMimeData* mimeData = mevent->mimeData();
	if (mimeData->hasUrls())
	{
		QStringList pathList;
		QList<QUrl> urlList = mimeData->urls();

		// extract the local paths of the files
		for (int i = 0; i < urlList.size() && i < 4; ++i)
		{
			pathList.append(urlList.at(i).toLocalFile());
		}

		for (auto v : pathList)
		{
			if (v.endsWith(".wav") || v.endsWith(".aac") 
				|| v.endsWith(".mp3") || v.endsWith(".ape")
				|| v.endsWith(".flac"))
			{
				ui.audioFile->setText(v);
			}else if (v.endsWith(".264") || v.endsWith(".yuv") 
				|| v.endsWith(".avi") || v.endsWith(".mp4")
				|| v.endsWith(".flv") || v.endsWith(".mov"))
			{
				ui.videoFile->setText(v);
			}
		}
	}
}

int Hatsu::toCompress()
{
	auto CO = new compressOptions;
	CO->audioFile	= ui.audioFile->text();
	CO->videoFile	= ui.videoFile->text();
	CO->script		= ui.ScriptEditor->toPlainText();
	CO->CRF			= static_cast<float>(ui.crfBox->value());
	CO->encoder		= ui.x264Selector->itemText(ui.x264Selector->currentIndex());
	CO->careColor	= ui.IsCareColor->isChecked();
	CO->careMontion = ui.IsCareMontion->isChecked();
	CO->careTime	= ui.IsCareTime->isChecked();
	CO->preprocess	= preProcessType::None;

	if (ui.preProcess_Gaussian->isChecked())
	{
		CO->preprocess = preProcessType::Gaussian;
	}
	else if (ui.preProcess_Bilateral->isChecked())
	{
		CO->preprocess = preProcessType::Bilateral;
	}
	else if (ui.preProcess_SurfaceBlur->isChecked())
	{
		CO->preprocess = preProcessType::SurfaceBlur;
	}
	else if (ui.preProcess_BM3D->isChecked())
	{
		CO->preprocess = preProcessType::BM3D;
	}


	if (CO->audioFile.length() == 0)
	{
		CO->audioFile = CO->videoFile;
	}
	std::thread th(CompressLogic, CO,this);
	th.detach();
	return 1;
}

int Hatsu::SelectVideoFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		NULL,
		tr("ALL(*.*)"));
	ui.videoFile->setText(fileName);
	return 1;
}

int Hatsu::SelectAudioFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		NULL,
		tr("ALL(*.*)"));
	ui.audioFile->setText(fileName);
	return 1;
}

void Hatsu::msgCriticalSlot(const QString & a, const QString & b) const
{
	QMessageBox::critical(NULL, a, b);
}

void Hatsu::QmsgCritical(QString a, QString b)
{
	emit msgCritical(a, b);
}

void Hatsu::QstartEncoder(QString x264encoderParams,
	QString muxParams)
{
	emit startEncoder(x264encoderParams, muxParams);
}

void Hatsu::startEncoderSlot(const QString & x264encoderParams,
	const QString & muxParams)
{
	e = new encoderinfo(x264encoderParams, muxParams);
	e->show();
}
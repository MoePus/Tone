#include "Tlogic.h"
#include "hatsu.h"
#include "const.h"
#include <QProcess>
#include <memory>
QString generateVideoSource(QString filename, preProcessType preprocessFuncIndex)
{
	const QString defaultSourceFunc = R"(clip = core.ffms2.Source(r"%1"))";
	const QString aviSourceFunc = R"(clip = core.avisource.AVISource(r"%1"))";
	QString  SourceFunc;
	if (filename.endsWith(".avi"))
		SourceFunc = aviSourceFunc.arg(filename);
	else
		SourceFunc = defaultSourceFunc.arg(filename);
	const QString Gaussian = "clip = core.bilateral.Gaussian(clip,0.55)";
	const QString Bilateral = "clip = core.bilateral.Bilateral(clip,sigmaS = 3,sigmaR = 0.028,planes = [0])";
	const QString SurfaceBlur = "clip = core.surfaceblur.surfaceblur(clip)";
	const QString BM3D = "import mvsfunc as mvf\n    clip = mvf.BM3D(clip)";
	QString preprocessFunc;
	switch (preprocessFuncIndex)
	{
	case preProcessType::Gaussian:
	{
		preprocessFunc = Gaussian;
		break;
	}
	case preProcessType::Bilateral:
	{
		preprocessFunc = Bilateral;
		break;
	}
	case preProcessType::SurfaceBlur:
	{
		preprocessFunc = SurfaceBlur;
		break;
	}
	case preProcessType::BM3D:
	{
		preprocessFunc = BM3D;
		break;
	}
	default:
	{
		preprocessFunc = "";
		break;
	}
	}
	QString getVideoSource =
		QString(R"(def getVideoSource():
    import vapoursynth as vs
    core = vs.get_core()
    %1
    %2
    return clip)").arg(SourceFunc).arg(preprocessFunc);
	return getVideoSource;
}

void saveVpyScript(QString script,Hatsu* handle)
{
	QDir *Dtemp = new QDir;
	if (!Dtemp->exists("vpy"))
		Dtemp->mkdir("vpy");
	delete Dtemp;

	QFile scriptFile(R"(vpy/w.vpy)");
	//方式：Append为追加，WriteOnly，ReadOnly  
	if (!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		handle->QmsgCritical("WARN", QString::fromLocal8Bit("无法创建文件"));
		return;
	}
	QTextStream wScript(&scriptFile);
	wScript.setCodec("UTF-8");
	wScript << script;
	wScript.flush();
	scriptFile.close();
}

auto generateEncoderParams(compressOptions* CO)
{
	const QString careTime = "--preset 8 -b 4 -I 120";
	const QString NOTcareTime = "--preset 9 -r 16 -b 6 -I 400";
	const QString careColor = "--aq-mode 3 --aq-strength 0.85";
	const QString NOTcareColor = "";
	const QString careMontion = "--qcomp 0.65";
	const QString NOTcareMontion = "--qcomp 0.5";

	QString outFile = CO->videoFile.left(CO->videoFile.lastIndexOf("."))+"_DR.mp4";

	QString params = QString(R"( -o "%1" %2 %3 %4 --crf %5 vpy/w.vpy)").arg(outFile)
		.arg(CO->careColor ? careColor : NOTcareColor)
		.arg(CO->careTime ? careTime : NOTcareTime)
		.arg(CO->careMontion ? careMontion : NOTcareMontion)
		.arg(CO->CRF);
	return std::make_pair(params, outFile);
}

bool NeedCompressAudio(compressOptions* CO)
{	
	QProcess ff;
	ff.setProcessChannelMode(QProcess::MergedChannels);
	ff.start(ffmpegPath,QStringList()<<"-i"<<CO->audioFile);
	ff.waitForFinished();
	QString audiofileinfo = ff.readAll();
	QRegExp rx("Audio: aac.+([0-9]{1,3}) kb/s");
	bool compressAudio = 1;
	if (audiofileinfo.indexOf(rx, 0) != -1)
	{
		int bitrate = atoi(rx.cap(1).toStdString().c_str());
		if (bitrate <= 192 && bitrate > 1) compressAudio = 0;
		qDebug() << "AAC Audio: " << bitrate << "kb/s";
	}
	return compressAudio;
}

void CompressLogic(compressOptions* CO, Hatsu* handle)
{
	if (CO->videoFile.length() == 0 || CO->audioFile.length() == 0)
	{
		qDebug() << "Err NO file";
		handle->QmsgCritical("Err", QString::fromLocal8Bit("未指定文件"));
		return;
	}

	bool compressAudio = NeedCompressAudio(CO);
	QString preFunc = generateVideoSource(CO->videoFile, CO->preprocess);
	QString script = QString("%1\n%2").arg(preFunc).arg(CO->script);

	saveVpyScript(script,handle);
	auto encoderParams = generateEncoderParams(CO);

	QString encoder = x264Dir + CO->encoder;

	QString muxParams = R"( -i "%1" -i "%2" -map 0:v -map 1:a -c:v copy -c:a )";
	muxParams = muxParams.arg(encoderParams.second).arg(CO->audioFile);
	if (compressAudio)
		muxParams += "aac -b:a 190k ";
	else
		muxParams += "copy ";
	muxParams += QString("\"%1.mp4\"").
		arg(encoderParams.second.left(
			encoderParams.second.length() - 6)
		+"_MUX.mp4");

	handle->QstartEncoder(encoder + encoderParams.first, ffmpegPath + muxParams);
	delete CO;
	return;
}

#pragma once
#include <iostream>
#include <stdexcept>
#include <QDebug>
#include <stdio.h>
#include <string>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include "hatsu.h"
#include <QDir>

enum preProcessType
{
	None,
	Gaussian,
	Bilateral,
	SurfaceBlur,
	BM3D
};

struct compressOptions
{
	QString videoFile;
	QString audioFile;
	QString script;
	QString	encoder;
	float   CRF;
	preProcessType	preprocess;
	bool	careTime;
	bool	careColor;
	bool	careMontion;
};

void CompressLogic(compressOptions* CO, Hatsu* handle);

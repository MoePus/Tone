/********************************************************************************
** Form generated from reading UI file 'hatsu.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HATSU_H
#define UI_HATSU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HatsuClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *Settings;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *postprocess;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDoubleSpinBox *crfBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *x264Selector;
    QSpacerItem *horizontalSpacer;
    QCheckBox *IsCareColor;
    QCheckBox *IsCareMontion;
    QCheckBox *IsCareTime;
    QGroupBox *preprocess;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QRadioButton *preProcess_None;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *preProcess_Gaussian;
    QRadioButton *preProcess_Bilateral;
    QRadioButton *preProcess_SurfaceBlur;
    QRadioButton *preProcess_BM3D;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *videoFile;
    QPushButton *videoSelector;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *audioFile;
    QPushButton *audioSelector;
    QWidget *Scripting;
    QPlainTextEdit *ScriptEditor;
    QWidget *tab;
    QTextEdit *About;
    QCommandLinkButton *commandCompress;

    void setupUi(QMainWindow *HatsuClass)
    {
        if (HatsuClass->objectName().isEmpty())
            HatsuClass->setObjectName(QStringLiteral("HatsuClass"));
        HatsuClass->resize(480, 456);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HatsuClass->sizePolicy().hasHeightForWidth());
        HatsuClass->setSizePolicy(sizePolicy);
        HatsuClass->setMinimumSize(QSize(480, 456));
        HatsuClass->setMaximumSize(QSize(480, 456));
        HatsuClass->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Hatsu/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QStringLiteral(":/Hatsu/Resources/icon32.ico"), QSize(), QIcon::Disabled, QIcon::Off);
        HatsuClass->setWindowIcon(icon);
        centralWidget = new QWidget(HatsuClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 461, 371));
        Settings = new QWidget();
        Settings->setObjectName(QStringLiteral("Settings"));
        layoutWidget = new QWidget(Settings);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 110, 411, 201));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        postprocess = new QGroupBox(layoutWidget);
        postprocess->setObjectName(QStringLiteral("postprocess"));
        postprocess->setMinimumSize(QSize(200, 0));
        layoutWidget1 = new QWidget(postprocess);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 21, 171, 161));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_4->addWidget(label);

        crfBox = new QDoubleSpinBox(layoutWidget1);
        crfBox->setObjectName(QStringLiteral("crfBox"));
        crfBox->setMinimum(1);
        crfBox->setMaximum(37);
        crfBox->setSingleStep(0.5);
        crfBox->setValue(26.4);

        horizontalLayout_4->addWidget(crfBox);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_5->addWidget(label_2);

        x264Selector = new QComboBox(layoutWidget1);
        x264Selector->setObjectName(QStringLiteral("x264Selector"));

        horizontalLayout_5->addWidget(x264Selector);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer);

        IsCareColor = new QCheckBox(layoutWidget1);
        IsCareColor->setObjectName(QStringLiteral("IsCareColor"));

        verticalLayout_3->addWidget(IsCareColor);

        IsCareMontion = new QCheckBox(layoutWidget1);
        IsCareMontion->setObjectName(QStringLiteral("IsCareMontion"));

        verticalLayout_3->addWidget(IsCareMontion);

        IsCareTime = new QCheckBox(layoutWidget1);
        IsCareTime->setObjectName(QStringLiteral("IsCareTime"));

        verticalLayout_3->addWidget(IsCareTime);


        horizontalLayout_6->addWidget(postprocess);

        preprocess = new QGroupBox(layoutWidget);
        preprocess->setObjectName(QStringLiteral("preprocess"));
        layoutWidget2 = new QWidget(preprocess);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 20, 141, 161));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        preProcess_None = new QRadioButton(layoutWidget2);
        preProcess_None->setObjectName(QStringLiteral("preProcess_None"));

        verticalLayout->addWidget(preProcess_None);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        preProcess_Gaussian = new QRadioButton(layoutWidget2);
        preProcess_Gaussian->setObjectName(QStringLiteral("preProcess_Gaussian"));

        verticalLayout->addWidget(preProcess_Gaussian);

        preProcess_Bilateral = new QRadioButton(layoutWidget2);
        preProcess_Bilateral->setObjectName(QStringLiteral("preProcess_Bilateral"));

        verticalLayout->addWidget(preProcess_Bilateral);

        preProcess_SurfaceBlur = new QRadioButton(layoutWidget2);
        preProcess_SurfaceBlur->setObjectName(QStringLiteral("preProcess_SurfaceBlur"));

        verticalLayout->addWidget(preProcess_SurfaceBlur);

        preProcess_BM3D = new QRadioButton(layoutWidget2);
        preProcess_BM3D->setObjectName(QStringLiteral("preProcess_BM3D"));

        verticalLayout->addWidget(preProcess_BM3D);


        horizontalLayout_6->addWidget(preprocess);

        layoutWidget3 = new QWidget(Settings);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 10, 431, 84));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        videoFile = new QLineEdit(layoutWidget3);
        videoFile->setObjectName(QStringLiteral("videoFile"));
        videoFile->setAcceptDrops(false);

        horizontalLayout_2->addWidget(videoFile);

        videoSelector = new QPushButton(layoutWidget3);
        videoSelector->setObjectName(QStringLiteral("videoSelector"));

        horizontalLayout_2->addWidget(videoSelector);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        audioFile = new QLineEdit(layoutWidget3);
        audioFile->setObjectName(QStringLiteral("audioFile"));
        audioFile->setAcceptDrops(false);

        horizontalLayout_3->addWidget(audioFile);

        audioSelector = new QPushButton(layoutWidget3);
        audioSelector->setObjectName(QStringLiteral("audioSelector"));

        horizontalLayout_3->addWidget(audioSelector);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tabWidget->addTab(Settings, QString());
        Scripting = new QWidget();
        Scripting->setObjectName(QStringLiteral("Scripting"));
        ScriptEditor = new QPlainTextEdit(Scripting);
        ScriptEditor->setObjectName(QStringLiteral("ScriptEditor"));
        ScriptEditor->setGeometry(QRect(10, 10, 431, 321));
        tabWidget->addTab(Scripting, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        About = new QTextEdit(tab);
        About->setObjectName(QStringLiteral("About"));
        About->setGeometry(QRect(10, 10, 431, 321));
        About->setReadOnly(true);
        tabWidget->addTab(tab, QString());
        commandCompress = new QCommandLinkButton(centralWidget);
        commandCompress->setObjectName(QStringLiteral("commandCompress"));
        commandCompress->setGeometry(QRect(400, 400, 71, 41));
        commandCompress->setAutoFillBackground(false);
        HatsuClass->setCentralWidget(centralWidget);
        QWidget::setTabOrder(videoFile, audioFile);
        QWidget::setTabOrder(audioFile, videoSelector);
        QWidget::setTabOrder(videoSelector, audioSelector);
        QWidget::setTabOrder(audioSelector, crfBox);
        QWidget::setTabOrder(crfBox, commandCompress);
        QWidget::setTabOrder(commandCompress, IsCareColor);
        QWidget::setTabOrder(IsCareColor, IsCareMontion);
        QWidget::setTabOrder(IsCareMontion, IsCareTime);
        QWidget::setTabOrder(IsCareTime, x264Selector);
        QWidget::setTabOrder(x264Selector, preProcess_None);
        QWidget::setTabOrder(preProcess_None, preProcess_Gaussian);
        QWidget::setTabOrder(preProcess_Gaussian, preProcess_Bilateral);
        QWidget::setTabOrder(preProcess_Bilateral, preProcess_SurfaceBlur);
        QWidget::setTabOrder(preProcess_SurfaceBlur, preProcess_BM3D);
        QWidget::setTabOrder(preProcess_BM3D, tabWidget);
        QWidget::setTabOrder(tabWidget, ScriptEditor);

        retranslateUi(HatsuClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(HatsuClass);
    } // setupUi

    void retranslateUi(QMainWindow *HatsuClass)
    {
        HatsuClass->setWindowTitle(QApplication::translate("HatsuClass", "\345\275\251-\346\267\261\347\272\242", 0));
        postprocess->setTitle(QApplication::translate("HatsuClass", "\345\216\213\345\210\266\345\217\202\346\225\260", 0));
        label->setText(QApplication::translate("HatsuClass", "CRF", 0));
        label_2->setText(QApplication::translate("HatsuClass", "Encoder", 0));
        IsCareColor->setText(QApplication::translate("HatsuClass", "\345\234\250\344\271\216\350\211\262\345\275\251", 0));
        IsCareMontion->setText(QApplication::translate("HatsuClass", "\345\234\250\344\271\216\345\212\250\346\200\201", 0));
        IsCareTime->setText(QApplication::translate("HatsuClass", "\345\234\250\344\271\216\346\227\266\351\227\264", 0));
        preprocess->setTitle(QApplication::translate("HatsuClass", "\350\247\206\351\242\221\345\211\215\345\244\204\347\220\206", 0));
        preProcess_None->setText(QApplication::translate("HatsuClass", "\346\227\240", 0));
        preProcess_Gaussian->setText(QApplication::translate("HatsuClass", "\351\253\230\346\226\257\346\250\241\347\263\212", 0));
        preProcess_Bilateral->setText(QApplication::translate("HatsuClass", "\345\217\214\350\276\271\346\250\241\347\263\212", 0));
        preProcess_SurfaceBlur->setText(QApplication::translate("HatsuClass", "\350\241\250\351\235\242\346\250\241\347\263\212", 0));
        preProcess_BM3D->setText(QApplication::translate("HatsuClass", "BM3D", 0));
        videoSelector->setText(QApplication::translate("HatsuClass", "\350\247\206\351\242\221", 0));
        audioSelector->setText(QApplication::translate("HatsuClass", "\351\237\263\351\242\221", 0));
        tabWidget->setTabText(tabWidget->indexOf(Settings), QApplication::translate("HatsuClass", "\350\256\276\345\256\232", 0));
        tabWidget->setTabText(tabWidget->indexOf(Scripting), QApplication::translate("HatsuClass", "\350\204\232\346\234\254", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("HatsuClass", "\345\205\263\344\272\216", 0));
        commandCompress->setText(QApplication::translate("HatsuClass", "\345\216\213\345\210\266", 0));
    } // retranslateUi

};

namespace Ui {
    class HatsuClass: public Ui_HatsuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HATSU_H

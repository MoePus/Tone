/********************************************************************************
** Form generated from reading UI file 'encoderinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENCODERINFO_H
#define UI_ENCODERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EncoderForm
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *infoBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *OKexit;

    void setupUi(QWidget *EncoderForm)
    {
        if (EncoderForm->objectName().isEmpty())
            EncoderForm->setObjectName(QStringLiteral("EncoderForm"));
        EncoderForm->resize(522, 246);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EncoderForm->sizePolicy().hasHeightForWidth());
        EncoderForm->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(EncoderForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 501, 223));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        infoBox = new QTextEdit(layoutWidget);
        infoBox->setObjectName(QStringLiteral("infoBox"));
        infoBox->setAcceptDrops(false);
        infoBox->setUndoRedoEnabled(false);
        infoBox->setReadOnly(true);
        infoBox->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(infoBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(408, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        OKexit = new QPushButton(layoutWidget);
        OKexit->setObjectName(QStringLiteral("OKexit"));
        OKexit->setMaximumSize(QSize(80, 16777215));
        OKexit->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(OKexit);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(EncoderForm);
        QObject::connect(OKexit, SIGNAL(clicked()), EncoderForm, SLOT(close()));

        QMetaObject::connectSlotsByName(EncoderForm);
    } // setupUi

    void retranslateUi(QWidget *EncoderForm)
    {
        EncoderForm->setWindowTitle(QApplication::translate("EncoderForm", "0%", 0));
        infoBox->setPlaceholderText(QString());
        OKexit->setText(QApplication::translate("EncoderForm", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class EncoderForm: public Ui_EncoderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENCODERINFO_H

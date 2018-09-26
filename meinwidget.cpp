#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include "meinwidget.h"

meinWidget::meinWidget(QWidget* parent) :QWidget(parent)
{
    StartButton->setFont(QFont("Bakskerville", 18, QFont::Bold));
    connect(StartButton, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton* sichernButton = new QPushButton(tr("Sichern"));
    sichernButton->setFont(QFont("Baskerville", 18, QFont::Bold));
    connect(sichernButton, SIGNAL(clicked()), this, SLOT(sichern()));

    QPushButton* ladenButton = new QPushButton(tr("Laden"));
    ladenButton->setFont(QFont("Baskerville", 18, QFont::Bold));
    connect(ladenButton, SIGNAL(clicked()), this, SLOT(laden()));

    QPushButton* quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Baskerville", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    meinZeichenFeld = new zeichenFeld;

    meinZeichenFeld->setFocusPolicy(Qt::StrongFocus);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(StartButton, 0, 0);
    gridLayout->addWidget(quit, 2, 0);
    gridLayout->addWidget(sichernButton, 3, 0);
    gridLayout->addWidget(ladenButton, 4, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 5, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
    connect(formen, SIGNAL(timeout()), this, SLOT(objekte()));
}

 void meinWidget::start(){

        if(zähler % 2){
            meinZeichenFeld->start();
            StartButton->setText("Stopp");
            formen->start(400);
        }
        else{
            meinZeichenFeld->stop();
            StartButton->setText("Start");
            formen ->stop();
        }
        zähler++;
    }

void meinWidget::objekte(void) {
     meinZeichenFeld->placeObject();
 }

//aus Beispiel Mehr Mäuse
void meinWidget::sichern(void)
{

    QFileDialog dialog(this);
    QString fileName;
    QFile file;
    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,tr("Speichern als"), ".", tr("Savegame-File (*.sav)"));
    if (fileName.isNull() == false) {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Dateifehler"),
                tr("Folgende Datei kann nicht verwendet werden: ") + fileName, QMessageBox::Ok);
        }
      meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

//aus Beispiel Mehr Mäuse
void meinWidget::laden(void) {

    QFileDialog dialog(this);
    QString fileName;
    QFile file;
    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
        tr("Speichern als"), ".", tr("Savegame-File (*.sav)"));
    if (fileName.isNull() == false) {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Dateifehler"),
                tr("Folgende Datei kann nicht geöffnet werden: ") + fileName, QMessageBox::Ok);
        }
        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}




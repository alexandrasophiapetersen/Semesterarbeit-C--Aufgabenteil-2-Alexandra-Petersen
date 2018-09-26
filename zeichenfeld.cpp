#include <QtGui>
#include "zeichenfeld.h"
#include <stdlib.h>
#include <QMessageBox>
#include <QWidget>
#include <QPainter>
#include <math.h>

//Die meisten Methoden setzen sich aus den Beispielen der Vorlesungen sowie des Praktikums zusammen.
//Ergänzt wurden diese durch Internet Recherche in Foren und der QT Documentation.
// Beispiel --> Farben --> http://doc.qt.io/qt-5/qcolor.html#fromRgb
zeichenFeld::zeichenFeld(QWidget *parent):QWidget(parent){

    setPalette(QPalette(QColor(250, 250, 250)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    setFixedSize(500,500);
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    increment=0;
    punkte=0;
    x = 225;

}

zeichenFeld::~zeichenFeld() {
    for (vector<struct myDrawingObject*>::iterator pos = objects.begin(); pos != objects.end(); pos++)
            delete *pos;
}

void zeichenFeld::paintEvent(QPaintEvent * ){
    QPainter punktemalen, lebenmalen, avatarmalen, painter;



    //Punkte steigend Stufe 1.5


        punktemalen.begin(this);
        punktemalen.setFont(QFont("Baskerville", 20, QFont::Bold));
        punktemalen.drawText(20, 30, "Punkte: " + QString::number(punkte));
        if (increment)
            punkte++;
        punktemalen.end();

   //Leben Stufe 1.6

        lebenmalen.begin(this);
        lebenmalen.setBrush(Qt::SolidPattern);
        lebenmalen.setBrush(QColor(255, 0, 0, 127));
        lebenmalen.drawEllipse(410,25,25,25);

        lebenmalen.setBrush(Qt::SolidPattern);
        lebenmalen.setBrush(QColor(255, 0, 0, 127));
        lebenmalen.drawEllipse(440,25,25,25);

        lebenmalen.setBrush(Qt::SolidPattern);
        lebenmalen.setBrush(QColor(255, 0, 0, 127));
        lebenmalen.drawEllipse(470,25,25,25);
        lebenmalen.end();


   //Avatar Stufe 1.2

        avatarmalen.begin(this);
        avatarmalen.setBrush(Qt::BDiagPattern);
        avatarmalen.fillRect(x, 480, 70, 60, QColor(0, 0, 255, 127));
        avatarmalen.drawRect(x, 480, 70, 60);
        avatarmalen.end();



//Objekte von oben nach unten -> die struct Methode entstammt größtenteils der vorletzten Sitzung des Programmierpraktikums,
//in welchem wir die letzte  C++ Hausaufgabe des Sommersemesters 2017 bearbeitet hatten
// und Beispiel 2 von Zeichnen und Bewegen
//Stufe 1.7

    vector<struct myDrawingObject*>::iterator pos;
    int z, y;

      painter.begin(this);
      for (pos = objects.begin(); pos != objects.end(); pos++)

      switch ((*pos)->type) {
      case square:
      z = (*pos)->x - 30;
      y = (*pos)->y - 30;
      painter.setBrush(QColor(236, 247, 111)); //Unterscheidung in Farbe Stufe 2
      painter.drawRect(z, y, 40, 40); //Unterscheidung in Form und Gräße Stufe 2
      break;

      case circle:
      z = (*pos)->x - 30;
      y = (*pos)->y - 30;
      painter.setBrush(QColor(132, 237, 151));
      painter.drawEllipse(z, y, 50, 50);
      break;
      }
      painter.end();

      for (vector<struct myDrawingObject*>::iterator pos = objects.begin(); pos != objects.end(); pos++) {

      if (increment) {
      if ((*pos)->type == square) {
           (*pos)->y++;
                    }
      if ((*pos)->type == circle) {
          (*pos)->y = (*pos)->y + 2; //Geschwindigkeitserhöhung Stufe 2
      }
      if ((*pos)->y > 550) {
           objects.erase(pos);
           break;
         }
   }
  }
}

void zeichenFeld::placeObject()
{
    struct myDrawingObject* object;

    object = new myDrawingObject;
    object->x = rand() % 480; // Zufälligkeit Stufe 2
    object->y = -50;

    int random = rand() % 11;
    switch (random) {
    case 0: case 1: case 2: case 3:
        object->type = square;
        break;
    case 4: case 5: case 6: case 7:
        object->type = circle;
        break;
    }

    objects.push_back(object);

    update();
}

//deserialize und serialize orientiert sich an Beispiel 5 von Mehr Mäuse
// (http://hki.uni-koeln.de/mehr-maeuse/)
//leider kommt beim Speichern immer die Fehlermeldung "Folgender Objekttyp ist unbekannt: p "
//trotz Versuch der Lösung des Problems mit p, habe ich den Fehler nicht behoben bekommen.


//Stufe 1.3
void zeichenFeld::serialize(QFile& file)


    {
    vector<struct myDrawingObject*>::iterator pos;
    QTextStream out(&file);
    out << "MeinSpielstand" << endl;
    out << "p: " << x << " " << punkte << endl;

    for (pos = objects.begin(); pos != objects.end(); pos++) {
    out << "x " << (*pos)->type << " " <<(*pos)->x << " " << (*pos)->y << endl;
    }
  }

//Stufe 1.4
void zeichenFeld::deserialize(QFile& file)
{
    struct myDrawingObject* object;
    char c;
    QString test;
    QTextStream in(&file);
    in >> test;
    if (test != "MeinSpielstand") {
    QMessageBox::warning(this, tr("Formatfehler"),
    tr("Das ist kein Spielstand!"), QMessageBox::Ok);
   return;
    }


     in >> c; // Leerstellen werden vom '>>' Operator 'konmsumiert';
     // Zeilenenden nicht.

    while (in.status() == QTextStream::Ok) {
    in >> c;
    if (in.status() == QTextStream::ReadPastEnd)
    break;

    if
       (c != 'p'){
         QMessageBox::warning(this, tr("Objektfehler"),
         tr("Folgender Objekttyp ist unbekannt: ") + c, QMessageBox::Ok);
         return;
      }

    if (c != 'x'){
      QMessageBox::warning(this, tr("Objektfehler"),
      tr("Folgender Objekttyp ist unbekannt: ") + c, QMessageBox::Ok);
      return;
   }


    if (c == 'p') {
        in >> x >> punkte;
        in >> c;
    }

    if (c == 'x') {
        object = new struct myDrawingObject;
        int type;
        in >> type >> object->x >> object->y;
        object->type = (drawType)type;
        objects.push_back(object);
        in >> c;
    }


    }

update();
}


void zeichenFeld::keyPressEvent(QKeyEvent* event)
{
    if (increment) {
        if (event->key() == Qt::Key_Left) {
            if (x > -25)
                x -= 25;
        }
        if (event->key() == Qt::Key_Right) {
            if (x < 475)
                x += 25;
        }
    }
}



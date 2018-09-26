#include <QWidget>
#include <QTimer>
#include "zeichenfeld.h"
#include <QPushButton>

class meinWidget : public QWidget{
    Q_OBJECT
public:
    meinWidget(QWidget *parent = 0);

    QPushButton *StartButton=new QPushButton(tr("Start"));


private:

   zeichenFeld *meinZeichenFeld;
   int zähler=1;
   QTimer* formen = new QTimer(this);

private slots:
    void start();
    void laden();
    void sichern();
    void objekte();
};


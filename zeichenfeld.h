#include <vector>
using namespace std;
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QColor>
#include <vector>


class zeichenFeld : public QWidget {
public:
    zeichenFeld(QWidget* parent = 0);

   ~zeichenFeld(); // alle in diesem Header "kommentierten" (//) Daten und Funktionen
                    // orientieren sich an Beispiel 2 von Zeichnen und Bewegen (http://hki.uni-koeln.de/zeichnen-und-bewegen/)

    enum drawType{ //
      square, circle //
    }; //

    void placeObject(); //


    void start(){
           timer->start(20);
           increment=1;
       }

       void stop() {
           timer->stop();
           increment=0;
       }


    void serialize(QFile& file);
    void deserialize(QFile& file);



private:
    QTimer* timer;
    int increment;
    int punkte;
    int x;
    vector<struct myDrawingObject* >objects; //

protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
};

struct myDrawingObject { //
    zeichenFeld::drawType type;
    int x;
    int y;
};

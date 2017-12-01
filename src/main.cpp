#include "widget.h"
#include <QApplication>

#include "neural/neuraltests.h"
#include "osu/osutests.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand (static_cast <unsigned> (time(0)));

    /*
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
    */

    OsuTests::testOsuFile("/home/fuguet/osu/Songs/21321 Hatsune Miku - Nisoku Hokou/Hatsune Miku - Nisoku Hokou (banvi) [Garven's Easy].osu");

    return 0;
}

#include <QApplication>

#include <ella/ws.h>

#include "artistlist.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    ella::ws::Username = "";
    ella::ws::Password = "";

    ArtistList artists;
    artists.getSimilar("Nirvana");
    artists.resize(300, 400);
    artists.show();

    return app.exec();
}

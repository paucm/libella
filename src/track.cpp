#include <QNetworkReply>
#include <QLatin1String>

#include "xmlquery.h"
#include <ella/ws.h>
#include <ella/track.h>

using namespace ella;

Track::Track(const QByteArray &id, const QString &title, 
             const QByteArray &artistId, const QString &artistName)
{
    m_id = id;
    m_title = title;
    m_artistId = artistId;
    m_artistName = artistName;
}
            
Track::Track(const QByteArray &id)
{
    m_id = id;
}

QNetworkReply *Track::search(const SearchParams &params, int limit)
{
    QString path = "/collections/bmat/tracks/search";
    QString query;
    
    SearchParams::const_iterator iter = params.constBegin();
    for(; iter < params.constEnd(); ++iter) {
        if(!query.isEmpty()) {
            query += " AND ";
        }
        query += QLatin1String(searchParamToString(iter->first));
        query += ":";
        query += iter->second.toString();
    }
    //query = query.replace(" ", "%20");

    QMap<QString, QString> p;
    p["q"] = query;
    p["fetch_metadata"] = "track,artist,bmat_artist_id";
    if (limit > 0) p["limit"] =  QString::number(limit);

    return ella::ws::get(path, p);
}
 
QList<Track> Track::list(QNetworkReply *reply)
{
    QList<Track> tracks;
    XmlQuery xml = ella::ws::parse(reply);
    Q_FOREACH(XmlQuery q, xml.children("track")) {
        QString id = q.attribute("id");
        if (!id.isEmpty()) {
             XmlQuery ch = q.children("metadata")[0];
             QString title = ch["track"].text();
             QString artist = ch["artist"].text();
             QString artistId = ch["bmat_artist_id"].text();
             Track track(id.toLocal8Bit(), 
                         title, 
                         artistId.toLocal8Bit(), 
                         artist);
             tracks += track;
        }
    }
    return tracks;
}

QByteArray Track::searchParamToString(SearchParam param)
{
    switch(param) {
        case Title:
            return "title";
        case Artist:
            return "artist";
        case ArtistId:
            return "artist_id";
        case Genre:
            return "genre";
        case Speed:
            return "speed";
        case Mood:
            return "mood";
        default:
            return "";
    }
}


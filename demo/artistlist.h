#include <QListWidget>
#include <QNetworkReply>

#include <ella/artist.h>

class ArtistList : public QListWidget
{
    Q_OBJECT

    public:
        ArtistList()
        {
            connect(this, SIGNAL(itemActivated( QListWidgetItem* )), SLOT(onItemActivated( QListWidgetItem*)));
        }
        
        ~ArtistList()
        {
        }

        void getSimilar(const QString &artist)
        {
            m_artist = artist;
            clear();
            //First search for artist bmatid
            setWindowTitle( "Searching " + m_artist + "..." );
            QNetworkReply *reply = ella::Artist(m_artist).search();
            connect( reply, SIGNAL(finished()), this, SLOT(onSearch()));
        }


    private slots:
        void onSearch()
        {
            QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
            QList<ella::Artist> artists = ella::Artist::list(reply);
            similar(artists[0]);
        }

        void similar(ella::Artist &artist)
        {
            setWindowTitle( "Loading " + m_artist + "..." );
            QNetworkReply *reply = artist.getSimilar();
            connect( reply, SIGNAL(finished()), this, SLOT(onGotSimilar()));
        }

        void onGotSimilar()
        {
            setWindowTitle(m_artist);
            QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
            QList<ella::Artist> artists = ella::Artist::getSimilar(reply).values();

            QListIterator<ella::Artist> i(artists);
            i.toBack();
            while (i.hasPrevious()) {
                ella::Artist a = i.previous();
                addItem(a.name());
            }
        }

        void onItemActivated(QListWidgetItem *item)
        {
            getSimilar(item->text());
        }

    private:
        QString m_artist;
};


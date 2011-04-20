#ifndef ELLA_H
#define ELLA_H

#include <QByteArray>
#include <QMetaType>

namespace ella {

    class Ella {

        public:

            enum SimilarityType {
                Default,
                CollaborativeFiltering,
                Playlist
            };
            static QByteArray similarityTypeToString(SimilarityType type);

            enum Mood {
                Blue,
                Happy,
                Furious,
                Acoustic,
                Party,
                Relax
            };
            static QByteArray moodToString(Mood mood);
    };
};

Q_DECLARE_METATYPE(ella::Ella::Mood)

#endif //ELLA_H

#ifndef ELLA_H
#define ELLA_H

#include <QByteArray>
#include <QMetaType>

namespace ella {

    class Util {

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

Q_DECLARE_METATYPE(ella::Util::Mood)

#endif //ELLA_H

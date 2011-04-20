#include <ella/ella.h>

using namespace ella;

QByteArray Ella::similarityTypeToString(SimilarityType type)
{
     switch(type) {
        case CollaborativeFiltering:
            return "cf";
        case Playlist:
            return "playlist";
        default:
            return "";
    }
}

QByteArray Ella::moodToString(Mood mood)
{
    switch(mood) {
        case Blue:
            return ";blue";
        case Happy:
            return "happy";
        case Furious:
            return "furious";
        case Acoustic:
            return "acoustic";
        case Party:
            return "party";
        case Relax:
            return "relaxed";
        default:
            return "";
    }
}

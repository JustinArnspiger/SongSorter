#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QString>

#define UNRANKED -1

class Song : public QObject
{
    Q_OBJECT

    public:
        Song(int aTrackNumber, QString aAlbumName, QString aArtistName, QString aFilePath, QString aSongName);
        ~Song();

        QString getAlbumName() const;
        QString getArtistName() const;
        QString getFilePath() const;
        int getRank() const;
        QString getSongName() const;
        int getTrackNumber() const;
        void setAlbumName(QString aAlbumName);
        void setArtistName(QString aArtistName);
        void setFilePath(QString aFilePath);
        void setRank(int aRank);
        void setSongName(QString aSongName);
        void setTrackNumber(int aTrackNumber);

        bool operator <(const Song &aOtherSong) const;
        bool operator >(const Song &aOtherSong) const;
        bool operator <=(const Song &aOtherSong) const;
        bool operator >=(const Song &aOtherSong) const;

    private:
        int mRank; //!< The ranking of the song in the sorting.
        int mTrackNumber; //!< The track number of the song in its album.
        QString mAlbumName; //!< The name of the album containing the song.
        QString mArtistName; //!< The name of the artist who wrote the song.
        QString mFilePath; //!< The file path of the song.
        QString mSongName; //!< The name of the song.

};
#endif // SONG_H

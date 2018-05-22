#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QString>

#define UNRANKED -1

class Song : public QObject
{
    Q_OBJECT

    public:
        Song();
        Song(QString aFilePath, QString aArtistName, QString aAlbumName, QString aSongName);
        ~Song();

        QString getAlbumName() const;
        QString getArtistName() const;
        QString getFilePath() const;
        int getRank() const;
        QString getSongName() const;
        void setAlbumName(QString aAlbumName);
        void setArtistName(QString aArtistName);
        void setFilePath(QString aFilePath);
        void setRank(int aRank);
        void setSongName(QString aSongName);

        bool operator <(const Song &aOtherSong) const;
        bool operator >(const Song &aOtherSong) const;
        bool operator <=(const Song &aOtherSong) const;
        bool operator >=(const Song &aOtherSong) const;


        static Song* createSongFromFilePath(QString aFilePath);

    private:
        int mRank;
        QString mAlbumName;
        QString mArtistName;
        QString mFilePath;
        QString mSongName;

};
#endif // SONG_H

#include "song.h"

//-----------------------------------------------
// Constructors & Destructor
//-----------------------------------------------
Song::Song(QString aFilePath = "", QString aArtistName = "", QString aAlbumName = "", QString aSongName = "") :
    mRank(UNRANKED), mFilePath(aFilePath), mArtistName(aArtistName), mAlbumName(aAlbumName), mSongName(aSongName)
{}

Song::~Song()
{}

//-----------------------------------------------
// Getters and Setters
//-----------------------------------------------
QString Song::getAlbumName() const
{
    return mAlbumName;
}

QString Song::getArtistName() const
{
    return mArtistName;
}

QString Song::getFilePath() const
{
    return mFilePath;
}

int Song::getRank() const
{
    return mRank;
}

QString Song::getSongName() const
{
    return mSongName;
}

void Song::setAlbumName(QString aAlbumName)
{
    mAlbumName = aAlbumName;
}

void Song::setArtistName(QString aArtistName)
{
    mArtistName = aArtistName;
}

void Song::setFilePath(QString aFilePath)
{
    mFilePath = aFilePath;
}

void Song::setRank(int aRank)
{
    mRank = aRank;
}

void Song::setSongName(QString aSongName)
{
    mSongName = aSongName;
}

//-----------------------------------------------
// Overloaded Operators
//-----------------------------------------------
bool Song::operator <(const Song &aOtherSong) const
{
    return mRank < aOtherSong.mRank;
}

bool Song::operator >(const Song &aOtherSong) const
{
    return mRank > aOtherSong.mRank;
}

bool Song::operator <=(const Song &aOtherSong) const
{
    return mRank <= aOtherSong.mRank;
}

bool Song::operator >=(const Song &aOtherSong) const
{
    return mRank >= aOtherSong.mRank;
}

//-----------------------------------------------
// Static Functions
//-----------------------------------------------
Song* Song::createSongFromFilePath(QString aFilePath)
{
    // Initialize default values for the metadata.
    QString album = "Unknown Album";
    QString artist = "Unknown Artist";

    // Use the last part of the file path as the song name.
    QStringList substrings = aFilePath.split('/');
    QString songName = substrings.at( substrings.count() - 1 );
    songName.remove(QRegExp("^([0-9]+)(\\s*)?(-*)(\\s*)?"));
    songName.remove(QRegExp(".mp3|.flac"));

    // See if we can make an attempt to get the artist and album from the
    // file path as well.
    if( substrings.count() >= 3 )
    {
        album = substrings.at( substrings.count() - 2 );
        artist = substrings.at( substrings.count() - 3 );
    }

    return new Song(aFilePath, artist, album, songName);
}

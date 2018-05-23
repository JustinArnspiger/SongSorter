#include "song.h"

/*!
  \class Song
  \ingroup songHandling
  \inmodule SongSorter
  \brief Represents a Song.

  This class is a container that represents a Song according to its metadata (artist, album, etc.) as well
  as its overall rank and file path.
*/

//-----------------------------------------------
// Constructors & Destructor
//-----------------------------------------------
/*!
 * \fn Song::Song(QString aFilePath, QString aArtistName, QString aAlbumName, QString aSongName)
 * \brief Default constructor for a song
 * \a aFilePath The file path to the song. Defaults to an empty string.
 * \a aArtistName The name of the artist who made the song. Defaults to an empty string.
 * \a aAlbumName The name of the album which the song belongs to. Defaults to an empty string.
 * \a aSongName The name of the song. Defaults to an empty string.
*/
Song::Song(QString aFilePath = "", QString aArtistName = "", QString aAlbumName = "", QString aSongName = "") :
    mRank(UNRANKED), mFilePath(aFilePath), mArtistName(aArtistName), mAlbumName(aAlbumName), mSongName(aSongName)
{}

/*!
 * \fn Song::~Song()
 * \brief The destructor for a song.
 */
Song::~Song()
{}

//-----------------------------------------------
// Getters and Setters
//-----------------------------------------------
/*!
 * \fn QString Song::getAlbumName() const
 * \brief Gets the name of the album that the song belongs to.
 * Returns a string representing the name of the album that the song belongs to.
 */
QString Song::getAlbumName() const
{
    return mAlbumName;
}

/*!
 * \fn QString Song::getArtistName() const
 * \brief Gets the name of the artist that wrote the song.
 * Returns a string representing the name of the artist that wrote the song.
 */
QString Song::getArtistName() const
{
    return mArtistName;
}

/*!
 * \fn QString Song::getFilePath() const
 * \brief Gets the path to the song file.
 * Returns a string representing the file path of the song.
 */
QString Song::getFilePath() const
{
    return mFilePath;
}

/*!
 * \fn int Song::getRank() const
 * \brief Gets the ranking of the song.
 * Returns an integer representing the ranking of the song in the sorting.
 */
int Song::getRank() const
{
    return mRank;
}

/*!
 * \fn QString Song::getSongName() const
 * \brief Gets the name of the song.
 * Returns a string representing the name of song.
 */
QString Song::getSongName() const
{
    return mSongName;
}

/*!
 * \fn void Song::setAlbumName(QString aAlbumName)
 * \brief Sets the name of the album that the song belongs to.
 * \a aAlbumName The new name of the album that the song belongs to.
 */
void Song::setAlbumName(QString aAlbumName)
{
    mAlbumName = aAlbumName;
}

/*!
 * \fn void Song::setArtistName(QString aArtistName)
 * \brief Sets the name of the artist that wrote the song.
 * \a aArtistName The new name of the artist that wrote the song.
 */
void Song::setArtistName(QString aArtistName)
{
    mArtistName = aArtistName;
}

/*!
 * \fn void Song::setFilePath(QString aFilePath)
 * \brief Sets the path to the song file.
 * \a aFilePath The new file path to the song.
 */
void Song::setFilePath(QString aFilePath)
{
    mFilePath = aFilePath;
}

/*!
 * \fn void Song::setRank(int aRank)
 * \brief Sets the ranking of the song in the sorting.
 * \a aRank The new ranking of the song.
 */
void Song::setRank(int aRank)
{
    mRank = aRank;
}

/*!
 * \fn void Song::setSongName(QString aSongName)
 * \brief Sets the name of the song.
 * \a aSongName The new name of the song.
 */
void Song::setSongName(QString aSongName)
{
    mSongName = aSongName;
}

//-----------------------------------------------
// Overloaded Operators
//-----------------------------------------------
/*!
 * \fn bool Song::operator <(const Song &aOtherSong) const
 * \brief Overloaded operator that compares this song to another song.
 * \a aOtherSong The song to compare to this one.
 *
 * Returns \c true if this song has a lesser rank than aOtherSong.
 */
bool Song::operator <(const Song &aOtherSong) const
{
    return mRank < aOtherSong.mRank;
}

/*!
 * \fn bool Song::operator >(const Song &aOtherSong) const
 * \brief Overloaded operator that compares this song to another song.
 * \a aOtherSong The song to compare to this one.
 *
 * Returns \c true if this song has a greater rank than aOtherSong.
 */
bool Song::operator >(const Song &aOtherSong) const
{
    return mRank > aOtherSong.mRank;
}

/*!
 * \fn bool Song::operator <=(const Song &aOtherSong) const
 * \brief Overloaded operator that compares this song to another song.
 * \a aOtherSong The song to compare to this one.
 *
 * Returns \c true if this song has a lesser than or equal rank to aOtherSong.
 */
bool Song::operator <=(const Song &aOtherSong) const
{
    return mRank <= aOtherSong.mRank;
}

/*!
 * \fn bool Song::operator >=(const Song &aOtherSong) const
 * \brief Overloaded operator that compares this song to another song.
 * \a aOtherSong The song to compare to this one.
 *
 * Returns \c true if this song has a greater than or equal rank to aOtherSong.
 */
bool Song::operator >=(const Song &aOtherSong) const
{
    return mRank >= aOtherSong.mRank;
}

//-----------------------------------------------
// Static Functions
//-----------------------------------------------
/*!
 * \fn Song* Song::createSongFromFilePath(QString aFilePath)
 * \brief Returns a new Song whose metadata is retrieved from the file path.
 * \a aFilePath The given file path to the song.
 *
 * This function is for when a song's metadata is unable to be retrieved through the
 * standard method of using QMediaPlayer. In order to try to approximate the metadata,
 * this function will use parts of the file path with the assumption that if the file is
 * something like example_song.mp3, then the song's name is Example Song.
 *
 * The function also tries to obtain the artist and album by assuming (if applicable) that
 * the file path is formatted as .../artistName/albumName/song.<file_extension>.
 *
 * \note This function will allocate a new song, so the song that is created must be deleted later.
 */
Song* Song::createSongFromFilePath(QString aFilePath)
{
    // Initialize default values for the metadata.
    QString album = "Unknown Album";
    QString artist = "Unknown Artist";

    // Use the last part of the file path as the song name.
    QStringList substrings = aFilePath.split('/');
    QString songName = substrings.at( substrings.count() - 1 );
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

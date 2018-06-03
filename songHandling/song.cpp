#include "song.h"

/**
  @class Song
  @ingroup songHandling
  @brief Represents a Song.

  This class is a container that represents a Song according to its metadata (artist, album, etc.) as well
  as its overall rank and file path.
*/

//-----------------------------------------------
// Constructors and Destructor
//-----------------------------------------------

/**
 * @brief Constructor for a song
 * @param aTrackNumber The track number of the song. Defaults to 1.
 * @param aAlbumName The name of the album which the song belongs to. Defaults to an empty string.
 * @param aArtistName The name of the artist who made the song. Defaults to an empty string.
 * @param aFilePath The file path to the song. Defaults to an empty string.
 * @param aSongName The name of the song. Defaults to an empty string.
 */
Song::Song(int aTrackNumber = 1, QString aAlbumName = "", QString aArtistName = "", QString aFilePath = "", QString aSongName = "") :
    mRank(UNRANKED),
    mTrackNumber(aTrackNumber),
    mAlbumName(aAlbumName),
    mArtistName(aArtistName),
    mFilePath(aFilePath),
    mSongName(aSongName)
{}

/**
 * @brief The destructor for a song.
 */
Song::~Song()
{}

//-----------------------------------------------
// Public Functions
//-----------------------------------------------

/**
 * @brief Gets the name of the album that the song belongs to.
 * @return A QString representing the name of the album that the song belongs to.
 */
QString Song::getAlbumName() const
{
    return mAlbumName;
}

/**
 * @brief Gets the name of the artist that wrote the song.
 * @return A QString representing the name of the artist that wrote the song.
 */
QString Song::getArtistName() const
{
    return mArtistName;
}

/**
 * @brief Gets the path to the song file.
 * @return A QString representing the file path of the song.
 */
QString Song::getFilePath() const
{
    return mFilePath;
}

/**
 * @brief Gets the ranking of the song.
 * @return An integer representing the ranking of the song in the sorting.
 */
int Song::getRank() const
{
    return mRank;
}

/**
 * @brief Gets the name of the song.
 * @return A QString representing the name of song.
 */
QString Song::getSongName() const
{
    return mSongName;
}

/**
 * @brief Gets the track number of the song.
 * @return An integer representing the track number of the song.
 */
int Song::getTrackNumber() const
{
    return mTrackNumber;
}

/**
 * @brief Sets the name of the album that the song belongs to.
 * @param aAlbumName The new name of the album that the song belongs to.
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

/**
 * @brief Sets the track number of the song.
 * @param aTrackNumber The new track number of the song.
 */
void Song::setTrackNumber(int aTrackNumber)
{
    mTrackNumber = aTrackNumber;
}

//-----------------------------------------------
// Overloaded Operators
//-----------------------------------------------

/**
 * @brief Less than operator for a Song.
 * @param aOtherSong The song to compare to this one.
 * @return True if this Song's rank is less than aOtherSong's rank.
 */
bool Song::operator <(const Song &aOtherSong) const
{
    return mRank < aOtherSong.mRank;
}

/**
 * @brief Greater than operator for a Song.
 * @param aOtherSong The song to compare to this one.
 * @return True if this Song's rank is greater than aOtherSong's rank.
 */
bool Song::operator >(const Song &aOtherSong) const
{
    return mRank > aOtherSong.mRank;
}

/**
 * @brief Less than or equal operator for a Song.
 * @param aOtherSong The song to compare to this one.
 * @return True if this Song's rank is less than or equal to aOtherSong's rank.
 */
bool Song::operator <=(const Song &aOtherSong) const
{
    return mRank <= aOtherSong.mRank;
}

/**
 * @brief Greater than or equal operator for a Song.
 * @param aOtherSong The song to compare to this one.
 * @return True if this Song's rank is greater than or equal to aOtherSong's rank.
 */
bool Song::operator >=(const Song &aOtherSong) const
{
    return mRank >= aOtherSong.mRank;
}

#include "startupwindow.h"
#include "ui_startupwindow.h"

/*!
  \class StartupWindow
  \brief Contains the UI handling for the startup window.
  \ingroup UI
  \inmodule SongSorter

  This class handles the various UI events that can occur on the startup window.
  The UI events are mostly just related to choosing a folder of songs to sort.
*/

//-----------------------------------------------
// Constructors and Destructor
//-----------------------------------------------
/*!
    \fn StartupWindow::StartupWindow(QWidget *parent)
    \a parent The parent of the window.
    \brief Constructor for the welcome window.

    This function creates the welcome window and initializes the media player that will be used for
    retrieving metadata from songs.
*/
StartupWindow::StartupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartupWindow)
{
    ui->setupUi(this);

    // Set up the media player (used for retrieving metadata from the songs.)
    mMetadataRetrievalMediaPlayer = new QMediaPlayer();
    mMetadataRetrievalMediaPlayer->setVolume(0);

    // Connect signals to slots.
    connect(mMetadataRetrievalMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged));
}

/*!
 * \fn StartupWindow::~StartupWindow()
 * \brief Destructor for the startup window.
 */
StartupWindow::~StartupWindow()
{
    delete ui;
}

//-----------------------------------------------
// Slots
//-----------------------------------------------
/*! \fn void StartupWindow::on_addFolderButton_released()
 * Handles when the Add Folder button is pressed and released.
 *
 * When the Add Folder button is pressed and released, a dialog will show to allow
 * the user to pick a folder of songs that will be added to the list of songs
 * to sort.
*/
void StartupWindow::on_addFolderButton_released()
{
    // Show the open folder dialog and get the chosen directory.
    QFileDialog openFolderDialog( this );
    openFolderDialog.setFileMode( QFileDialog::DirectoryOnly );
    mCurrentPath = openFolderDialog.getExistingDirectory();
}

/*! \fn void StartupWindow::on_mMetadataRetrievalMediaPlayer_mediaStatusChanged(QMediaPlayer::MediaStatus aStatus)
    Handles when the media status of StartupWindow::mMetadataRetrievalMediaPlayer changes.

    This function will create a Song using the metadata that is retrieved.
*/
void StartupWindow::on_mMetadataRetrievalMediaPlayer_mediaStatusChanged(QMediaPlayer::MediaStatus aStatus)
{

}



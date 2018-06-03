#include "startupwindow.h"
#include "ui_startupwindow.h"

/**
  @class StartupWindow
  @brief Contains the UI handling for the startup window.
  @ingroup UI

  The startup window is pretty much the main window of the program. It allows
  for users to import songs, edit imported songs, and begin sorting once songs are
  imported.
*/

//-----------------------------------------------
// Static Variable Initialization
//-----------------------------------------------

const QString StartupWindow::mNumSongsLabel = QString("Number of songs that will be sorted: ");
QStringList StartupWindow::msSupportedFileExtensions = QStringList() << "*.mp3" << "*.flac";


//-----------------------------------------------
// Constructors and Destructor
//-----------------------------------------------

/**
 * @brief Constructor for the StartupWindow.
 * @param parent The parent of the window.
 *
 * The constructor sets up the UI for the StartupWindow and connects signals to its
 * slots.
*/
StartupWindow::StartupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartupWindow)
{
    // Set up the UI and other windows.
    ui->setupUi(this);
    mComparisonWindow = new ComparisonWindow(this);
    mSongListViewerWindow = new SongListViewerWindow(this);
    mComparisonWindow->hide();
    mSongListViewerWindow->hide();
    ui->viewSongListButton->setEnabled(false);
    ui->beginSortingButton->setEnabled(false);

    // Connect slots.
    connect(mSongListViewerWindow, SIGNAL(importedSongsConfirmed()), this, SLOT(on_importedSongsConfirmed()));
    connect(mSongListViewerWindow, SIGNAL(songListEdited()), this, SLOT(on_songListEdited()));
    connect(mSongListViewerWindow, SIGNAL(importCancelled()), this, SLOT(on_SongListViewerWindowCancelled()));
}

/**
 * @brief Destructor for the startup window.
 */
StartupWindow::~StartupWindow()
{
    delete ui;

    // Delete the songs in the main list.
    Song* songToDelete = nullptr;
    QMutableListIterator<Song*> iter(mSongs);
    while(iter.hasNext())
    {
        songToDelete = iter.next();
        iter.remove();
        delete songToDelete;
        songToDelete = nullptr;
    }

    // Delete the songs in the imported song list.
    iter = QMutableListIterator<Song*>(mSongsFromSelectedFolder);
    while(iter.hasNext())
    {
        songToDelete = iter.next();
        iter.remove();
        delete songToDelete;
        songToDelete = nullptr;
    }

}

//-----------------------------------------------
// Slots
//-----------------------------------------------

/**
 * @brief Handles when the Add Folder button is pressed and released.
 *
 * When the Add Folder button is pressed and released, a dialog will show to allow
 * the user to pick a folder of songs that will be added to the list of songs
 * to sort.
*/
void StartupWindow::on_addFolderButton_released()
{
    // Show the open folder dialog and get the chosen directory.
    QFileDialog openFolderDialog;
    openFolderDialog.setFileMode(QFileDialog::DirectoryOnly);
    QString openedDirectory = openFolderDialog.getExistingDirectory();

    if(openedDirectory != "")
    {
        // If the chosen directory contains songs to import, then get their metadata and create a container for them.
        QDirIterator iter(openedDirectory, msSupportedFileExtensions, QDir::Filter::NoFilter, QDirIterator::FollowSymlinks|QDirIterator::Subdirectories);
        if(iter.hasNext())
        {
            // Declare variables.
            TagLib::FileRef file;
            int currentPathLength = 0;
            int trackNumber = 1;
            QString currentPath, artist, album, songName;
            Song* newSong = nullptr;
            wchar_t* filePathForTaglib = nullptr;

            // Get the metadata of all of the songs in the chosen directory.
            while(iter.hasNext())
            {
                // Convert the QString containing the current path so that we can use it with taglib.
                currentPath = iter.next();
                currentPathLength = currentPath.length();
                filePathForTaglib = new wchar_t[currentPathLength + 1];
                currentPath.toWCharArray(filePathForTaglib);
                filePathForTaglib[currentPathLength] = L'\0';

                // Use Taglib to get the metadata of the song.
                file = TagLib::FileRef(TagLib::FileName(filePathForTaglib));
                if(!file.isNull() && file.tag() != nullptr)
                {
                    artist = QString(file.tag()->artist().toCString(true));
                    album = QString(file.tag()->album().toCString(true));
                    songName = QString(file.tag()->title().toCString(true));
                    trackNumber = (int)file.tag()->track();
                    newSong = new Song(trackNumber, album, artist, currentPath, songName);

                    // Add the new song to the list of imported songs.
                    mSongsFromSelectedFolder.append(newSong);
                }

                // Clear allocated memory.
                delete [] filePathForTaglib;
                filePathForTaglib = nullptr;
            }
        }
    }

    // If we found songs in the selected folder, then let the user confirm which ones they want to import.
    if(mSongsFromSelectedFolder.count() > 0)
    {
        showSongListViewerWindow(SongListViewerWindow::SONG_LIST_MODE::CONFIRM_IMPORTED_SONGS);
    }
}

/**
 * @brief Handles the Begin Sorting! button being clicked and released.
 *
 * This function will close the StartupWindow and open the ComparisonWindow
 * to begin sorting the songs.
 */
void StartupWindow::on_beginSortingButton_released()
{
    mComparisonWindow->show();
    hide();
}

/**
 * @brief Slot that handles songs being imported.
 *
 * This slot will be called when the SongListViewerWindow is accepted and its
 * @link SongListViewerWindow::SONG_LIST_MODE mode@endlink is set to CONFIRM_IMPORTED_SONGS.
 *
 */
void StartupWindow::on_importedSongsConfirmed()
{
    // Re-enable the "Add a Folder" button.
    ui->addFolderButton->setEnabled(true);

    // Append the imported songs to the main list.
    mSongs.append(mSongsFromSelectedFolder);
    mSongsFromSelectedFolder.clear();

    // Update the ui.
    show();
    updateUi();
}

/*!
 * @brief A slot that handles when the song list is edited in the SongListViewerWindow.
 *
 * This function checks if there are still songs in the @link StartupWindow::mSongs main song list@endlink
 * and updates the UI accordingly.
 */
void StartupWindow::on_songListEdited()
{
    show();
    ui->addFolderButton->setEnabled(true);
    updateUi();
}

/*!
 * @brief Slot that handles the SongListViewerWindow being cancelled or exited.
 *
 * This function just resets the import process and updates the ui.
 */
void StartupWindow::on_SongListViewerWindowCancelled()
{
    ui->addFolderButton->setEnabled(true);
    mSongsFromSelectedFolder.clear();
    show();
    updateUi();
}

/*!
 * @brief Handles the View Songs button being clicked and released.
 *
 * This function will show the SongListViewerWindow and populate it with
 * @link StartupWindow::mSongsFromSelectedFolder the current imported songs@endlink.
 */
void StartupWindow::on_viewSongListButton_released()
{
    showSongListViewerWindow(SongListViewerWindow::SONG_LIST_MODE::EDIT_MAIN_SONG_LIST);
}

//-----------------------------------------------
// Private Functions
//-----------------------------------------------

/**
 * @brief Shows the SongListViewerWindow.
 * @param aSongListMode The @link SongListViewerWindow::SONG_LIST_MODE mode@endlink in which to run the song list viewer.
 */
void StartupWindow::showSongListViewerWindow(SongListViewerWindow::SONG_LIST_MODE aSongListMode)
{
    // Update the ui since we're showing the dialog.
    ui->addFolderButton->setEnabled(false);

    // Setup the window and show it.
    if(aSongListMode == SongListViewerWindow::SONG_LIST_MODE::CONFIRM_IMPORTED_SONGS)
    {
        mSongListViewerWindow->setupSongListViewerWindow(aSongListMode, &mSongsFromSelectedFolder);
    }
    else
    {
        mSongListViewerWindow->setupSongListViewerWindow(aSongListMode, &mSongs);
    }
    mSongListViewerWindow->show();
    hide();
}

/**
 * @brief Updates the the ui based on the state of the main song list.
 */
void StartupWindow::updateUi()
{
    bool enableViewAndSortButtons = !mSongs.empty();
    ui->beginSortingButton->setEnabled(enableViewAndSortButtons);
    ui->viewSongListButton->setEnabled(enableViewAndSortButtons);
    if(mSongs.count() > 0)
    {
        ui->numSongsLabel->show();
        ui->numSongsLabel->setText(StartupWindow::mNumSongsLabel + QString("%1").arg(mSongs.count()));
    }
    else
    {
        ui->numSongsLabel->hide();
    }
}

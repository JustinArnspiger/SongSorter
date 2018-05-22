#include "welcomewindow.h"
#include "ui_welcomewindow.h"

/*!
    \fn WelcomeWindow::WelcomeWindow
    Constructor for the welcome window.
*/
WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);

    // Set up the media player (used for retrieving metadata from the songs.)
    mMetadataRetrievalMediaPlayer = new QMediaPlayer();
    mMetadataRetrievalMediaPlayer->setVolume(0);

    // Connect signals to slots.
    connect(mMetadataRetrievalMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged));
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

/*! \fn void WelcomeWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus aStatus)
    Handles when the media status of WelcomeWindow::mMetadataRetrievalMediaPlayer changes.

    This function will create a Song using the metadata that is retrieved.
*/
void WelcomeWindow::on_mMetadataRetrievalMediaPlayer_mediaStatusChanged(QMediaPlayer::MediaStatus aStatus)
{

}

/*! \fn void WelcomeWindow::on_addFolderButton_released()
 * Handles when the Add Folder button is pressed and released.
 *
 * When the Add Folder button is pressed and released, a dialog will show to allow
 * the user to pick a folder of songs that will be added to the list of songs
 * to sort.
*/
void WelcomeWindow::on_addFolderButton_released()
{
    // Show the open folder dialog and get the chosen directory.
    QFileDialog openFolderDialog( this );
    openFolderDialog.setFileMode( QFileDialog::DirectoryOnly );
    mCurrentPath = openFolderDialog.getExistingDirectory();
}

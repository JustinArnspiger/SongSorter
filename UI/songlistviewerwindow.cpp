#include "SongListViewerWindow.h"
#include "ui_SongListViewerWindow.h"

/**
  @class SongListViewerWindow
  @brief Allows the user to choose which songs to import from a folder.
  @ingroup UI

  This class implements event handling for a window that displays lists of @link Song songs@endlink.
  The window has different @link SongListViewerWindow::SONG_LIST_MODE modes@endlink that it can
  be run in, and these modes dictate the actions that are available for the user in the window.
*/

//-----------------------------------------------
// Static Variable Initialization
//-----------------------------------------------
const QString SongListViewerWindow::msConfirmImportedSongsLabel = QString("Number of songs to import from folder: ");
const QString SongListViewerWindow::msEditMainSongListLabel = QString("Number of songs that will be sorted: ");

//-----------------------------------------------
// Constructors and Destructor
//-----------------------------------------------

/**
 * @param parent The parent widget.
 * @brief Constructor for the SongListViewerWindow.
 */
SongListViewerWindow::SongListViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SongListViewerWindow)
{
    ui->setupUi(this);
}

/**
 * @brief Destructor for the SongListViewerWindow
 */
SongListViewerWindow::~SongListViewerWindow()
{
    delete ui;
}

//-----------------------------------------------
// Public Functions
//-----------------------------------------------

/**
 * @brief Sets up the SongListViewerWindow.
 * @param aSongListMode The new @link SongListViewerWindow::SONG_LIST_MODE mode@endlink of the SongListViewerWindow.
 * @param aSongList The Song list to display in the SongListViewerWindow.
 */
void SongListViewerWindow::setupSongListViewerWindow(SONG_LIST_MODE aSongListMode, QList<Song*>* aSongList)
{
    mSongListMode = aSongListMode;
    mUnsavedChanges = (aSongListMode == SONG_LIST_MODE::CONFIRM_IMPORTED_SONGS);
    mEditsOccurred = false;
    mChangesAccepted = false;
    mSongList = aSongList;
    mNumSongsAfterSave = mSongList->count();
    updateNumberOfSongsLabel();
    fillTableWidget();
}

//-----------------------------------------------
// Slots
//-----------------------------------------------

/**
 * @brief Overrides the closeEvent from the QMainWindow parent class.
 * @param event The close event.
 *
 * This function will show a dialog asking the user to confirm that they want to discard
 * unsaved changes if applicable.
 */
void SongListViewerWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if(mUnsavedChanges)
    {
        if(confirmCancel())
        {
            mSongList = nullptr;
            emit importCancelled();
            event->accept();
        }
    }
    else
    {
        if(mSongListMode == SONG_LIST_MODE::EDIT_MAIN_SONG_LIST)
        {
            emit songListEdited();
        }
        event->accept();
    }

}
/**
 * @brief Handles changes being saved.
 *
 * This function will @link SongListViewerWindow::updateSongListFromTable update the list of songs@endlink
 * and then emit the proper signal.
 */
void SongListViewerWindow::on_buttonBox_accepted()
{
    // Update the song list using the table if it's possible that it was edited.
    if(mSongListMode != SHOW_RESULTS)
    {
        updateSongListFromTable();
    }

    // Emit the proper signal.
    switch(mSongListMode)
    {
        case CONFIRM_IMPORTED_SONGS:
            emit importedSongsConfirmed();
            break;
        case EDIT_MAIN_SONG_LIST:
            emit songListEdited();
            break;
        case SHOW_RESULTS:
            emit resultsWindowClosed();
            break;
        default:
            Q_ASSERT_X(false, "SongListViewerWindow::on_buttonBox_accepted", "Reached default case when it shouldn't have!");
            break;
    }

    // Clear dialog contents. The song list is shared, so we don't need to delete it.
    mSongList = nullptr;
    ui->songListTableWidget->clear();
    mSongEdits.clear();
    mUnsavedChanges = false;
    close();
}

/*!
 * @brief Handles the cancel button being clicked.
 * This function will just close the SongListViewerWindow.
 * @sa SongListViewerWindow::closeEvent.
 */
void SongListViewerWindow::on_buttonBox_rejected()
{
    close();
}

/*!
 * @brief Handles when the user edits an entry in the table.
 * @param row The row of the entry that changed. This corresponds to the song that changed.
 * @param column The column of the entry that changed. This corresponds to the field that changed.
 *
 * \note Updating songs only occurs when the dialog is confirmed. See SongListViewerWindow::updateSongListFromTable.
 */
void SongListViewerWindow::on_songListTableWidget_cellChanged(int row, int column)
{
    // Mark that edits have occurred and that there are unsaved changes.
    mEditsOccurred = true;
    mUnsavedChanges = true;

    // See if this song has already been edited. If not, then add it to the map.
    if(!mSongEdits.contains(row))
    {
        mSongEdits.insert(row, song_edit());
    }
    // Mark that we should update the song if the dialog is confirmed.
    switch(column)
    {
        case CHECKBOX_OR_RANK_COLUMN:
        {
            // Note: Results can't be edited, so this case only matters for when the column has checkboxes.
            // A checked checkbox means keep the song. If it's unchecked, then it means that the song should be removed from the list.
            QCheckBox* checkBox = (QCheckBox*)ui->songListTableWidget->cellWidget(row, CHECKBOX_OR_RANK_COLUMN)->layout()->itemAt(0)->widget();
            mSongEdits[row].remove_song = (!checkBox->isChecked());
            mSongEdits[row].remove_song ? mNumSongsAfterSave-- : mNumSongsAfterSave++;
            updateNumberOfSongsLabel();
            break;
        }
        case ARTIST_COLUMN:
            mSongEdits[row].artist_edited = true;
            break;
        case ALBUM_COLUMN:
            mSongEdits[row].album_edited = true;
            break;
        case TRACK_NUMBER_COLUMN:
            mSongEdits[row].track_number_edited = true;
            break;
        case SONG_NAME_COLUMN:
            mSongEdits[row].song_name_edited = true;
            break;
        default:
            Q_ASSERT_X(false, "SongListViewerWindow::on_songListTableWidget_cellChanged", "Reached default case when we shouldn't have!");
            break;
    }

}

//-----------------------------------------------
// Private Functions
//-----------------------------------------------

/**
 * @brief Shows a message box asking the user to confirm that they want to exit with unsaved changes.
 * @return True if the user confirms they want to discard their unsaved changes. False otherwise.
 */
bool SongListViewerWindow::confirmCancel()
{
    // Declare Variables.
    bool confirmed = false;
    QMessageBox confirmCancelBox;

    // Set up the message box.
    confirmCancelBox.setText("Exit the song list viewer?\nYour changes will not be saved");
    confirmCancelBox.setStandardButtons(QMessageBox::Cancel);
    QPushButton* exitButton = confirmCancelBox.addButton("Exit", QMessageBox::YesRole);

    // Display the message box and mark the result.
    confirmCancelBox.exec();
    confirmed = ((QPushButton*)confirmCancelBox.clickedButton() == exitButton);
    if(exitButton != nullptr)
    {
        delete exitButton;
        exitButton = nullptr;
    }

    return confirmed;
}

/**
 * @brief Fills the table in the window with the contents of the Song list.
 *
 * The table is formatted as follows:
 * @n If the window is in @link SongListViewerWindow::SONG_LIST_MODE SHOW_RESULTS mode@endlink:
 * @n Rank   Artist   Album   Track Number  Song Name
 * @n @n Otherwise, the table is:
 * @n Keep?   Artist   Album   Track Number  Song Name
 * @n where the Keep column contains a checkbox.
 *
 */
void SongListViewerWindow::fillTableWidget()
{
    // Block signals from the table temporarily so that we don't invoke the on_songListTableWidget_cellChanged slot.
    QSignalBlocker signalBlocker(ui->songListTableWidget);

    // Declare variables
    int numSongs = mSongList->count();
    QStringList headerLabels;
    QTableWidgetItem* artistItem = nullptr;
    QTableWidgetItem* albumItem = nullptr;
    QSpinBox* trackNumberItem = nullptr;
    QTableWidgetItem* songNameItem = nullptr;

    // Set the attributes of the table.
    ui->songListTableWidget->setRowCount(numSongs);
    ui->songListTableWidget->setColumnCount(5);
    ui->songListTableWidget->setColumnWidth(CHECKBOX_OR_RANK_COLUMN, 60);
    ui->songListTableWidget->setColumnWidth(ARTIST_COLUMN, 390);
    ui->songListTableWidget->setColumnWidth(ALBUM_COLUMN, 390);
    ui->songListTableWidget->setColumnWidth(TRACK_NUMBER_COLUMN, 60);
    ui->songListTableWidget->setColumnWidth(SONG_NAME_COLUMN, 390);
    ui->songListTableWidget->verticalHeader()->setVisible(false);

    // If we're confirming imported songs or allowing the user to edit the song list,
    // then we want a checkbox to allow for the user to decide whether or not to include the song
    // in the sorting. If we're showing the results, then we want to put the song ranking instead
    // of the checkbox.
    if(mSongListMode == SHOW_RESULTS)
    {
        headerLabels << "Rank";
    }
    else
    {
        headerLabels << "Keep?";
    }
    headerLabels << "Artist" << "Album" << "Track" << "Song Name";
    ui->songListTableWidget->setHorizontalHeaderLabels(headerLabels);

    // Add all of the songs to the table.
    for(int i = 0; i < numSongs; i++)
    {
        // If we're showing the results of the sort, then we want to put the rank of the song
        // in the first column. Otherwise, we want to put a checkbox.
        if(mSongListMode == SHOW_RESULTS)
        {
            QTableWidgetItem* rankEntry = new QTableWidgetItem();
            rankEntry->setText(QString("%1").arg((*mSongList)[i]->getRank()));
            rankEntry->setFlags(rankEntry->flags() ^ Qt::ItemIsEditable);
            ui->songListTableWidget->setItem(i, CHECKBOX_OR_RANK_COLUMN, rankEntry);


        }
        else
        {
            // Create a widget to contain the check box. We need this so the check box can
            // be centered in the cell.
            QWidget* checkBoxWidget = new QWidget(ui->songListTableWidget);
            QHBoxLayout* checkBoxWidgetLayout = new QHBoxLayout(checkBoxWidget);
            QCheckBox* checkBox = new QCheckBox(checkBoxWidget);
            checkBox->setChecked(true);
            checkBoxWidgetLayout->setAlignment(Qt::AlignHCenter);
            checkBoxWidgetLayout->setContentsMargins(0, 0, 0, 0);
            checkBoxWidgetLayout->addWidget(checkBox);
            checkBoxWidget->setLayout(checkBoxWidgetLayout);
            ui->songListTableWidget->setCellWidget(i, CHECKBOX_OR_RANK_COLUMN, checkBoxWidget);
            connect(checkBox, &QCheckBox::toggled, [=](){ this->on_songListTableWidget_cellChanged(i, CHECKBOX_OR_RANK_COLUMN);});
        }

        // Create the entries for the artist name, album name, and song name.
        artistItem = new QTableWidgetItem((*mSongList)[i]->getArtistName());
        artistItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        albumItem = new QTableWidgetItem((*mSongList)[i]->getAlbumName());
        albumItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        songNameItem = new QTableWidgetItem((*mSongList)[i]->getSongName());
        songNameItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        // Set up the track number entry. These entries require connecting to their valueChanged signal.
        trackNumberItem = new QSpinBox(ui->songListTableWidget);
        trackNumberItem->setAlignment(Qt::AlignHCenter);
        trackNumberItem->setValue((*mSongList)[i]->getTrackNumber());
        connect(trackNumberItem, qOverload<int>(&QSpinBox::valueChanged), [=](int){ this->on_songListTableWidget_cellChanged(i,TRACK_NUMBER_COLUMN); });

        // Insert the items.
        ui->songListTableWidget->setItem(i, ARTIST_COLUMN, artistItem);
        ui->songListTableWidget->setItem(i, ALBUM_COLUMN, albumItem);
        ui->songListTableWidget->setCellWidget(i, TRACK_NUMBER_COLUMN, trackNumberItem);
        ui->songListTableWidget->setItem(i, SONG_NAME_COLUMN, songNameItem);
    }

    // We can unblock signals now that the table is filled.
    signalBlocker.unblock();
}

/**
 * @brief Updates the label at the bottom of the SongListViewerWindow.
 */
void SongListViewerWindow::updateNumberOfSongsLabel()
{
    switch(mSongListMode)
    {
        case CONFIRM_IMPORTED_SONGS:
            ui->numSongsInTableLabel->show();
            ui->numSongsInTableLabel->setText(SongListViewerWindow::msConfirmImportedSongsLabel + QString("%1").arg(mNumSongsAfterSave));
            break;
        case EDIT_MAIN_SONG_LIST:
            ui->numSongsInTableLabel->show();
            ui->numSongsInTableLabel->setText(SongListViewerWindow::msEditMainSongListLabel + QString("%1").arg(mNumSongsAfterSave));
            break;
        case SHOW_RESULTS:
            ui->numSongsInTableLabel->hide();
            break;
        default:
            Q_ASSERT_X(false, "SongListViewerWindow::updateNumberOfSongsLabel", "Reached a default case when we shouldn't have!");
            break;
    }
}

/**
 * @brief Updates the songs with edits made in the dialog's table.
 *
 * When the user edits an entry in the Song list, a @link SongListViewerWindow::song_edit struct@endlink
 * is used to keep track of what changed. This function goes through all of the marked edits and updates
 * the @link Song songs@endlink in the list. This function is only called right before the window is closed
 * if the user clicked the Ok button and either edits occurred or songs were imported. We only edit the Song
 * list in this function because if the edits were applied to the Song at the time when the user makes them,
 * these edits would be kept even if the window was cancelled.
 */
void SongListViewerWindow::updateSongListFromTable()
{
    // See if we need to update any metadata.
    if(mEditsOccurred)
    {
        // The keys in the map correspond to a song's placement in the song list.
        // Get them in descending order so that we can modify the song list
        // without worrying about indices changing.
        QList<int> songListIndices = mSongEdits.keys();
        std::sort(songListIndices.begin(), songListIndices.end(), std::greater<int>());
        QMutableListIterator<int> iter(songListIndices);

        // Declare variables.
        int index = 0;
        QSpinBox* trackNumberSpinBox = nullptr;


        // Handle all of the song edits.
        while(iter.hasNext())
        {
            index = iter.next();

            // See if we need to remove the song. Other edits for the song don't matter if we're
            // removing it anyway.
            if(mSongEdits[index].remove_song)
            {
                Song* songToRemove = mSongList->takeAt(index);
                Q_ASSERT_X(songToRemove != nullptr, "SongListViewerWindow::updateSongListFromTable", "Somehow we're trying to delete a null song!");
                delete songToRemove;
            }
            else
            {
                // Update the metadata of the song as needed.
                if(mSongEdits[index].artist_edited)
                {
                    (*mSongList)[index]->setArtistName(ui->songListTableWidget->item(index, ARTIST_COLUMN)->text());
                }
                if(mSongEdits[index].album_edited)
                {
                    (*mSongList)[index]->setAlbumName(ui->songListTableWidget->item(index, ALBUM_COLUMN)->text());
                }
                if(mSongEdits[index].track_number_edited)
                {
                    trackNumberSpinBox = (QSpinBox*)ui->songListTableWidget->cellWidget(index, TRACK_NUMBER_COLUMN);
                    (*mSongList)[index]->setTrackNumber(trackNumberSpinBox->value());
                }
                if(mSongEdits[index].song_name_edited)
                {
                    (*mSongList)[index]->setSongName(ui->songListTableWidget->item(index, SONG_NAME_COLUMN)->text());
                }
            }
        }
    }
}

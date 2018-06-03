#ifndef SONGLISTVIEWERWINDOW_H
#define SONGLISTVIEWERWINDOW_H

#include <QMainWindow>

#include <QCheckBox>
#include <QCloseEvent>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QHBoxLayout>
#include <QMap>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include "songHandling/song.h"

#define CHECKBOX_OR_RANK_COLUMN 0
#define ARTIST_COLUMN 1
#define ALBUM_COLUMN 2
#define TRACK_NUMBER_COLUMN 3
#define SONG_NAME_COLUMN 4

namespace Ui {
    class SongListViewerWindow;
}

class SongListViewerWindow : public QMainWindow
{
        Q_OBJECT

    public:
        /**
         * @brief The different modes of the SongListViewerWindow.
         */
        typedef enum SONG_LIST_MODE
        {
            CONFIRM_IMPORTED_SONGS, //!< Confirming songs imported from a folder.
            EDIT_MAIN_SONG_LIST, //!< Editing the main list of songs before sorting.
            SHOW_RESULTS //!< Showing the results of the sort.
        } SONG_LIST_MODE;

        explicit SongListViewerWindow(QWidget *parent = 0);
        ~SongListViewerWindow();

        void setupSongListViewerWindow(SONG_LIST_MODE aSongListMode, QList<Song*>* aSongList);

    signals:
        void importCancelled(); //!< Emitted when the window exits with unsaved changes.
        void importedSongsConfirmed(); //!< Emitted when songs imported from a folder have been confirmed for inclusion in the sort.
        void songListEdited(); //!< Emitted when the main Song list has been edited.
        void resultsWindowClosed(); //!< Emitted when the window exits when it is displaying the results of the sort.

    private slots:
        void closeEvent(QCloseEvent *event);
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_songListTableWidget_cellChanged(int row, int column);

    private:
        /**
         * @brief Keeps tracks of edits that occur to a song in the table.
         */
        typedef struct song_edit
        {
            bool remove_song = false; //!< True if the Song should not be imported.
            bool artist_edited = false; //!< True if the artist of the Song was edited.
            bool album_edited = false; //!< True if the name of the album containing the Song was edited.
            bool track_number_edited = false; //!< True if the track number of the Song was edited.
            bool song_name_edited = false; //!< True if the name of the Song was edited.
        } song_edit;

        bool confirmCancel();
        void fillTableWidget();
        void updateNumberOfSongsLabel();
        void updateSongListFromTable();

        Ui::SongListViewerWindow *ui; //!< The ui of the window.

        bool mChangesAccepted = false; //!< Whether or not the user has clicked ok to exit the window and save their changes.
        bool mEditsOccurred = false; //!< Whether or not edits have occurred.
        bool mUnsavedChanges = false; //!< Whether or not there are unsaved changes.
        int mNumSongsAfterSave = 0; //!< The number of songs that will be in the saved song list should the user save.
        QList<Song*>* mSongList = nullptr; //!< The list of \link Song songs\endlink that are displayed in the viewer.
        QMap<int, song_edit> mSongEdits; //!< A map that connects the edits that have occurred to the index of the Song in the song list.
        SONG_LIST_MODE mSongListMode = CONFIRM_IMPORTED_SONGS; //!< The \link SONG_LIST_MODE mode\endlink that the song list viewer is in.

        static const QString msEditMainSongListLabel; //!< The label at the bottom of the window when it is being used to edit the main song list.
        static const QString msConfirmImportedSongsLabel; //!< The label at the bottom of the window when it is being used to confirm imported songs.
};

#endif // SONGLISTVIEWERWINDOW_H

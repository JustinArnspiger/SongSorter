#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QString>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "songHandling/song.h"
#include "UI/songlistviewerwindow.h"
#include <UI/comparisonwindow.h>

namespace Ui {
    class StartupWindow;
}

class StartupWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit StartupWindow(QWidget *parent = 0);
        ~StartupWindow();

    private slots:
        void on_addFolderButton_released();
        void on_beginSortingButton_released();
        void on_importedSongsConfirmed();
        void on_SongListViewerWindowCancelled();
        void on_songListEdited();
        void on_viewSongListButton_released();

    private:
        void parseNextSong();
        void showSongListViewerWindow(SongListViewerWindow::SONG_LIST_MODE aSongListMode);
        void updateUi();

        Ui::StartupWindow *ui;

        ComparisonWindow* mComparisonWindow = nullptr; //!< The window for comparing pairs of songs.
        SongListViewerWindow* mSongListViewerWindow = nullptr; //!< The window for viewing lists of songs.
        QList<Song*> mSongs; //!< The main song list.
        QList<Song*> mSongsFromSelectedFolder; //!< A temporary list of songs from an imported folder.

        const static QString mNumSongsLabel; //!< A label for the number of songs in the main song list.
        static QStringList msSupportedFileExtensions; //!< The file extensions that are searched for in a selected folder.
};

#endif // STARTUPWINDOW_H

#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QString>
#include <QVector>
#include "songHandling/song.h"

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
        void on_mMetadataRetrievalMediaPlayer_mediaStatusChanged(QMediaPlayer::MediaStatus aStatus);
        void on_addFolderButton_released();

    private:
        Ui::StartupWindow *ui;
        QMediaPlayer* mMetadataRetrievalMediaPlayer = nullptr;
        QString mCurrentPath;
};

#endif // STARTUPWINDOW_H

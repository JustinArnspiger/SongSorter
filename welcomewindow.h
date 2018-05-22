#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QString>
#include <QVector>
#include "song.h"

namespace Ui {
    class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit WelcomeWindow(QWidget *parent = 0);
        ~WelcomeWindow();

    private slots:
        void on_mMetadataRetrievalMediaPlayer_mediaStatusChanged(QMediaPlayer::MediaStatus aStatus);
        void on_addFolderButton_released();

    private:
        Ui::WelcomeWindow *ui;
        QMediaPlayer* mMetadataRetrievalMediaPlayer = nullptr;
        QString mCurrentPath;
};

#endif // WELCOMEWINDOW_H

#ifndef SORTINGWINDOW_H
#define SORTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
    class SortingWindow;
}

class SortingWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit SortingWindow(QWidget *parent = 0);
        ~SortingWindow();

    private:
        Ui::SortingWindow *ui;
};

#endif // SORTINGWINDOW_H

#ifndef SORTINGWINDOW_H
#define SORTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ComparisonWindow;
}

class ComparisonWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit ComparisonWindow(QWidget *parent = 0);
        ~ComparisonWindow();

    private:
        Ui::ComparisonWindow *ui; //!< The ui for the ComparisonWindow.
};

#endif // SORTINGWINDOW_H

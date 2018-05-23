#include "comparisonwindow.h"
#include "ui_comparisonwindow.h"

/*!
  \class ComparisonWindow
  \brief Contains the UI handling for the comparison window.
  \ingroup UI
  \inmodule SongSorter

  This class handles the various UI events that can occur on the comparison window.
*/

//-----------------------------------------------
// Constructors and Destructor
//-----------------------------------------------
/*!
 * \fn ComparisonWindow::ComparisonWindow(QWidget *parent)
 * \brief The constructor for the comparison window.
 * \a parent The parent widget of the comparison window.
 */
ComparisonWindow::ComparisonWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComparisonWindow)
{
    ui->setupUi(this);
}

/*!
 * \fn ComparisonWindow::~ComparisonWindow()
 * \brief The destructor for the comparison window.
 */
ComparisonWindow::~ComparisonWindow()
{
    delete ui;
}

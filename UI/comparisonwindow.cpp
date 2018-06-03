#include "comparisonwindow.h"
#include "ui_comparisonwindow.h"

/**
  @class ComparisonWindow
  @brief Contains the UI handling for the comparison window.
  @ingroup UI

  This class handles the various UI events that can occur on the comparison window.
*/

//-----------------------------------------------
// Constructors and Destructor
//-----------------------------------------------

/**
 * @brief The constructor for the ComparisonWindow.
 * @param parent The parent widget of the ComparisonWindow.
 */
ComparisonWindow::ComparisonWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComparisonWindow)
{
    ui->setupUi(this);
}

/**
 * @brief The destructor for the comparison window.
 */
ComparisonWindow::~ComparisonWindow()
{
    delete ui;
}

#include <QMainWindow>
#include "ui_pill_app.h"
#include "AddPillDialog.h"

class pill_app : public QMainWindow
{
    Q_OBJECT

public:
    pill_app(QWidget* parent = nullptr);
    ~pill_app();

private slots:
    void add_pill_button_clicked();
    void remove_pill_button_clicked();
    void calendar_button_clicked();
    void remaining_quantity_button_clicked();

private:
    Ui::pill_appClass ui;
};


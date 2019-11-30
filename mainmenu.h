#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:

    static QTimer *timer;

    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:

    void on_pushButton_clicked();

    void on_horizontalSlider_6_valueChanged(int value);

    void on_horizontalSlider_7_valueChanged(int value);

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H

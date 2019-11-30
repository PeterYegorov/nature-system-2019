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

    void on_horizontalSlider_8_valueChanged(int value);

    void on_horizontalSlider_9_valueChanged(int value);

    void on_horizontalSlider_10_valueChanged(int value);

    void on_horizontalSlider_11_valueChanged(int value);

    void on_horizontalSlider_12_valueChanged(int value);

    void on_horizontalSlider_13_valueChanged(int value);

    void on_horizontalSlider_14_valueChanged(int value);

    void on_horizontalSlider_15_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_horizontalSlider_16_valueChanged(int value);

    void on_horizontalSlider_17_valueChanged(int value);

    void on_horizontalSlider_18_valueChanged(int value);

    void on_horizontalSlider_19_valueChanged(int value);

    void on_horizontalSlider_20_valueChanged(int value);

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H

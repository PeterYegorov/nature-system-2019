#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "initialparameters.h"
#include "environment.h"


MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);



    ui->horizontalSlider_6->setValue(InitialParameters::herbsCount);
    ui->horizontalSlider_7->setValue(InitialParameters::herbsSpeed);



    ui->label_6->setText(QString::number(ui->horizontalSlider_6->value()));
    ui->label_7->setText(QString::number(ui->horizontalSlider_7->value()));

}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::on_pushButton_clicked()
{

    InitialParameters::herbsCount = ui->horizontalSlider_6->value();
    InitialParameters::herbsSpeed = ui->horizontalSlider_7->value();



    //-----------------------------------------Food Spawn---------------------------------------

    size_t regFoodsCount = InitialParameters::regFoodsCount;
    for (size_t i = 0; i < regFoodsCount; ++i)
    {
        Environment::foods.push_back(Food(rand() % width(),rand() % height()));
    }

    //----------------------------------------Herbivores spawn---------------------------------
    //size_t herbsCount = rand() % 50 + 5;
    size_t herbsCount = InitialParameters::herbsCount;
    for (size_t i = 0; i < herbsCount; ++i)
    {
        Environment::herbs.push_back(Herbivores(rand() % width(),rand() % height(), false));
    }
    //----------------------------------------Predators spawn---------------------------------
    size_t predsCount = InitialParameters::predsCount;
    for (size_t i = 0; i < predsCount; ++i)
    {
        Environment::preds.push_back(Predators(rand() % width(),rand() % height(), false));
    }
    //----------------------------------------Omnivorous spawn--------------------------------
    size_t omsCount = InitialParameters::omsCount;
    for (size_t i = 0; i < omsCount; ++i)
    {
        Environment::oms.push_back(Omnivorous(rand() % width(),rand() % height(), false));
    }


    timer->start(InitialParameters::simulationSpeed);

    hide();
}

void MainMenu::on_horizontalSlider_6_valueChanged(int value)
{
    ui->label_6->setText(QString::number(ui->horizontalSlider_6->value()));
}

void MainMenu::on_horizontalSlider_7_valueChanged(int value)
{
    ui->label_7->setText(QString::number(ui->horizontalSlider_7->value()));
}

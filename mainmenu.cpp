#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "initialparameters.h"
#include "environment.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->horizontalSlider_5->setValue(InitialParameters::regFoodsCount);
    ui->horizontalSlider_6->setValue(InitialParameters::herbsCount);
    ui->horizontalSlider_7->setValue(InitialParameters::herbsSpeed);
    ui->horizontalSlider_8->setValue(InitialParameters::herbsHp);
    ui->horizontalSlider_9->setValue(InitialParameters::minHerbsLifetime);
    ui->horizontalSlider_10->setValue(InitialParameters::herbsRepSatiety);
    ui->horizontalSlider_11->setValue(InitialParameters::predsCount);
    ui->horizontalSlider_12->setValue(InitialParameters::predsSpeed);
    ui->horizontalSlider_13->setValue(InitialParameters::predsHp);
    ui->horizontalSlider_14->setValue(InitialParameters::minPredsLifetime);
    ui->horizontalSlider_15->setValue(InitialParameters::predsRepSatiety);
    ui->horizontalSlider_16->setValue(InitialParameters::simulationSpeed);
    ui->horizontalSlider_17->setValue(InitialParameters::omsCount);
    ui->horizontalSlider_18->setValue(InitialParameters::omsSpeed);
    ui->horizontalSlider_19->setValue(InitialParameters::minOmsLifetime);
    ui->horizontalSlider_20->setValue(InitialParameters::omsRepSatiety);

    ui->label_31->setText(QString::number(ui->horizontalSlider_5->value()));
    ui->label_6->setText(QString::number(ui->horizontalSlider_6->value()));
    ui->label_7->setText(QString::number(ui->horizontalSlider_7->value()));
    ui->label_8->setText(QString::number(ui->horizontalSlider_8->value()));
    ui->label_9->setText(QString::number(ui->horizontalSlider_9->value()));
    ui->label_10->setText(QString::number(ui->horizontalSlider_10->value()));
    ui->label_12->setText(QString::number(ui->horizontalSlider_11->value()));
    ui->label_14->setText(QString::number(ui->horizontalSlider_12->value()));
    ui->label_16->setText(QString::number(ui->horizontalSlider_13->value()));
    ui->label_18->setText(QString::number(ui->horizontalSlider_14->value()));
    ui->label_19->setText(QString::number(ui->horizontalSlider_15->value()));
    ui->label_33->setText(QString::number(ui->horizontalSlider_16->value()));
    ui->label_22->setText(QString::number(ui->horizontalSlider_17->value()));
    ui->label_24->setText(QString::number(ui->horizontalSlider_18->value()));
    ui->label_26->setText(QString::number(ui->horizontalSlider_19->value()));
    ui->label_28->setText(QString::number(ui->horizontalSlider_20->value()));
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{
    InitialParameters::regFoodsCount = ui->horizontalSlider_5->value();
    InitialParameters::herbsCount = ui->horizontalSlider_6->value();
    InitialParameters::herbsSpeed = ui->horizontalSlider_7->value();
    InitialParameters::herbsHp = ui->horizontalSlider_8->value();
    InitialParameters::minHerbsLifetime = ui->horizontalSlider_9->value();
    InitialParameters::minHerbsLifetime = ui->horizontalSlider_10->value();
    InitialParameters::predsCount = ui->horizontalSlider_11->value();
    InitialParameters::predsSpeed = ui->horizontalSlider_12->value();
    InitialParameters::predsHp = ui->horizontalSlider_13->value();
    InitialParameters::minPredsLifetime = ui->horizontalSlider_14->value();
    InitialParameters::predsRepSatiety = ui->horizontalSlider_15->value();
    InitialParameters::simulationSpeed = ui->horizontalSlider_16->value();
    InitialParameters::omsCount = ui->horizontalSlider_17->value();
    InitialParameters::omsSpeed = ui->horizontalSlider_18->value();
    InitialParameters::minOmsLifetime = ui->horizontalSlider_19->value();
    InitialParameters::omsRepSatiety = ui->horizontalSlider_20->value();

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

void MainMenu::on_horizontalSlider_8_valueChanged(int value)
{
    ui->label_8->setText(QString::number(ui->horizontalSlider_8->value()));
}

void MainMenu::on_horizontalSlider_9_valueChanged(int value)
{
    ui->label_9->setText(QString::number(ui->horizontalSlider_9->value()));
}

void MainMenu::on_horizontalSlider_10_valueChanged(int value)
{
    ui->label_10->setText(QString::number(ui->horizontalSlider_10->value()));
}

void MainMenu::on_horizontalSlider_11_valueChanged(int value)
{
    ui->label_12->setText(QString::number(ui->horizontalSlider_11->value()));
}

void MainMenu::on_horizontalSlider_12_valueChanged(int value)
{
    ui->label_14->setText(QString::number(ui->horizontalSlider_12->value()));
}

void MainMenu::on_horizontalSlider_13_valueChanged(int value)
{
    ui->label_16->setText(QString::number(ui->horizontalSlider_13->value()));
}

void MainMenu::on_horizontalSlider_14_valueChanged(int value)
{
    ui->label_18->setText(QString::number(ui->horizontalSlider_14->value()));
}

void MainMenu::on_horizontalSlider_15_valueChanged(int value)
{
    ui->label_19->setText(QString::number(ui->horizontalSlider_15->value()));
}

void MainMenu::on_horizontalSlider_5_valueChanged(int value)
{
     ui->label_31->setText(QString::number(ui->horizontalSlider_5->value()));
}

void MainMenu::on_horizontalSlider_16_valueChanged(int value)
{
    ui->label_33->setText(QString::number(ui->horizontalSlider_16->value()));
}

void MainMenu::on_horizontalSlider_17_valueChanged(int value)
{
     ui->label_22->setText(QString::number(ui->horizontalSlider_17->value()));
}

void MainMenu::on_horizontalSlider_18_valueChanged(int value)
{
    ui->label_24->setText(QString::number(ui->horizontalSlider_18->value()));
}

void MainMenu::on_horizontalSlider_19_valueChanged(int value)
{
    ui->label_26->setText(QString::number(ui->horizontalSlider_19->value()));
}

void MainMenu::on_horizontalSlider_20_valueChanged(int value)
{
     ui->label_28->setText(QString::number(ui->horizontalSlider_20->value()));
}

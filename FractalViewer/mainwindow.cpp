#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FractalCreator.h"
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if (ui->spinBoxWidth->value() > 1280 || ui->spinBoxHeight->value() > 720) {
        QMessageBox Msgbox;
        Msgbox.setText("Resolution must be within 1280x720.");
        Msgbox.exec();
        return;
    }

    /*if (ui->pushButtonStart->text()=="Start") {
        ui->pushButtonStart->setText("Stop");
    }   */

    FractalCreator frac1(ui->spinBoxMaxIt->value(), ui->spinBoxWidth->value(), ui->spinBoxHeight->value(), ui->spinBoxRed->value(), ui->spinBoxGreen->value(),
                         ui->spinBoxBlue->value(), ui->doubleSpinBoxRedM->value(), ui->doubleSpinBoxGreenM->value(), ui->doubleSpinBoxBlueM->value());


    Zoom zoom(ui->spinBoxZoomX->value(), ui->spinBoxZoomY->value(), ui->doubleSpinBoxScale->value());
    frac1.addZoom(zoom);
    frac1.drawFractal();
    ui->labelImage->setPixmap(QPixmap::fromImage(frac1.getImage()));

    if (ui->spinBoxWidth->value() > 800) {
        this->resize(ui->spinBoxWidth->value() + 18, this->height());

    }
    if (ui->spinBoxHeight->value() > 600) {
        this->resize(this->width(), ui->spinBoxHeight->value() + 192);

    }

    if (ui->spinBoxWidth->value() <= 800) {
        this->resize(818, this->height());

    }

    if (ui->spinBoxHeight->value() <= 600) {
        this->resize(this->width(), 792);
    }

    /*if (ui->pushButtonStart->text()=="Stop") {
        ui->pushButtonStart->setText("Start");
    }*/

}

/*void MainWindow::on_pushButtonDive_clicked()
{
    qDebug() << "inicio Dive";

    if (ui->pushButtonDive->text() == "Dive") {
        ui->pushButtonReset->setEnabled(false);
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonSave->setEnabled(false);
        ui->pushButtonDive->setText("Stop");
        qDebug() << "botoes desativados";
    }
    else {
        ui->pushButtonReset->setEnabled(true);
        ui->pushButtonStart->setEnabled(true);
        ui->pushButtonSave->setEnabled(true);
        ui->pushButtonDive->setText("Dive");
        qDebug() << "botoes ativados";
        return;
    }

    using namespace std::this_thread;
    using namespace std::chrono;

    int timeToWait = 3000/ui->doubleSpinBoxSpeed->value();

    FractalCreator frac1(ui->spinBoxMaxIt->value(), 800, 600, ui->spinBoxRed->value(), ui->spinBoxGreen->value(),
                         ui->spinBoxBlue->value(), ui->doubleSpinBoxRedM->value(), ui->doubleSpinBoxGreenM->value(), ui->doubleSpinBoxBlueM->value());

    qDebug() << "inicio loop while";


    steady_clock::time_point tBeginning;

    while (true) {
       tBeginning = steady_clock::now();

       ui->spinBoxZoomX->setEnabled(false);
       ui->spinBoxZoomY->setEnabled(false);
       ui->doubleSpinBoxScale->setEnabled(false);

       Zoom zoom(ui->spinBoxZoomX->value(), ui->spinBoxZoomY->value(), ui->doubleSpinBoxScale->value());
       frac1.addZoom(zoom);
       qDebug() << "a desenhar...";

       frac1.drawFractal();
       ui->labelImage->setPixmap(QPixmap::fromImage(frac1.getImage()));

       if(ui->pushButtonDive->text() == "Dive") {
           qDebug() << "fim Dive";
           break;
       }

       sleep_until(tBeginning + milliseconds(timeToWait));
    }

     ui->spinBoxZoomX->setEnabled(true);
     ui->spinBoxZoomY->setEnabled(true);
     ui->doubleSpinBoxScale->setEnabled(true);
}*/

void MainWindow::on_pushButtonReset_clicked()
{
    ui->labelImage->clear();
    ui->spinBoxMaxIt->clear();
    ui->spinBoxRed->clear();
    ui->spinBoxGreen->clear();
    ui->spinBoxBlue->clear();
    ui->doubleSpinBoxRedM->setValue(0.0);
    ui->doubleSpinBoxGreenM->setValue(0.0);
    ui->doubleSpinBoxBlueM->setValue(0.0);
    ui->spinBoxZoomX->setValue(400);
    ui->spinBoxZoomY->setValue(300);
    ui->doubleSpinBoxScale->setValue(1.0);
    ui->spinBoxMaxIt->clear();
    //ui->doubleSpinBoxSpeed->clear();
}

void MainWindow::on_pushButtonSave_clicked()
{
    //QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"), QString(), tr("Images (*.bmp)"));

    QFile file(fileName);

    if(!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, "Warning", "Cannor save file : " + file.errorString());
        return;
    }
    FractalCreator frac1(ui->spinBoxMaxIt->value(), ui->spinBoxWidth->value(), ui->spinBoxHeight->value(), ui->spinBoxRed->value(), ui->spinBoxGreen->value(),
                         ui->spinBoxBlue->value(), ui->doubleSpinBoxRedM->value(), ui->doubleSpinBoxGreenM->value(), ui->doubleSpinBoxBlueM->value());
    frac1.drawFractal();

    currentFile = fileName;
    setWindowTitle(fileName);
    QPixmap::fromImage(frac1.getImage()).save(fileName);
    file.close();
}

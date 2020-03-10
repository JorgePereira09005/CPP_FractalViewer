#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPixmap image;
    QString currentFile = "";
};
#endif // MAINWINDOW_H

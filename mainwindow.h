#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getScriptFileName() const;

public slots:
    void on_saveButton_clicked();
    void on_navigateButton_clicked();
    void on_runButton_clicked();

protected:
private:
    Ui::MainWindow *ui;
    QSettings *m_settings;
    QString m_lastPath;
    QString m_lastFileName;
};
#endif // MAINWINDOW_H

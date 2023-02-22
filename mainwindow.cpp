#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QClipboard>
#include <QMouseEvent>
#include <QPlainTextEdit>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include <QCoreApplication>
#include <QProcess>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*Style sheet file */
    QFile filestyle(":/style/stylesheet.css");

    if (filestyle.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->setStyleSheet(filestyle.readAll());
        filestyle.close();
    }

    // Initialize last path and file name from settings
    QSettings settings;
    m_lastPath = settings.value("lastPath", QDir::currentPath()).toString();
    m_lastFileName = settings.value("lastFileName", "script").toString();

    // Update UI with last path and file name
    ui->scriptPathEdit->setText(m_lastPath);
    ui->scriptNameEdit->setText(m_lastFileName);

    // Load the content of the last saved script file
    QFile scriptFile(getScriptFileName());
    if (scriptFile.exists() && scriptFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->scriptBodyEdit->setPlainText(scriptFile.readAll());
        scriptFile.close();
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_saveButton_clicked()
{
    QString fileName = getScriptFileName();

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->scriptBodyEdit->toPlainText();
    file.close();

    // Update last path and file name
    m_lastPath = QFileInfo(fileName).path();
    m_lastFileName = QFileInfo(fileName).baseName();
    QSettings settings;
    settings.setValue("lastPath", m_lastPath);
    settings.setValue("lastFileName", m_lastFileName);
}

void MainWindow::on_navigateButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Script"), m_lastPath,
                                                    tr("Batch Files (*.bat)"));
    if (fileName.isEmpty())
        return;

    QFileInfo fileInfo(fileName);
    ui->scriptPathEdit->setText(fileInfo.path());
    ui->scriptNameEdit->setText(fileInfo.baseName());
}

void MainWindow::on_runButton_clicked()
{
    QProcess::startDetached("cmd /c start " + getScriptFileName());
}

QString MainWindow::getScriptFileName() const
{
    return ui->scriptPathEdit->text() + QDir::separator() + ui->scriptNameEdit->text() + ".bat";
}

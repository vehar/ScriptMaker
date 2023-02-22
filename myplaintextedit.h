#ifndef MYPLAINTEXTEDIT_H
#define MYPLAINTEXTEDIT_H


#include "qguiapplication.h"
#include <QPlainTextEdit>
#include <QClipboard>
#include <QMimeData>
#include <QMouseEvent>

class MyPlainTextEdit : public QPlainTextEdit {
public:
    MyPlainTextEdit(QWidget *parent = nullptr) : QPlainTextEdit(parent) {}
protected:
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            const QMimeData *mimeData = clipboard->mimeData();
            if (mimeData->hasText()) {
                insertPlainText(mimeData->text());
            }
        }
        else {
            QPlainTextEdit::mousePressEvent(event);
        }
    }
};

#endif // MYPLAINTEXTEDIT_H

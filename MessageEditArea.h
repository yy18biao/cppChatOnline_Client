#pragma once

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>

class MessageEditArea : public QWidget
{
	Q_OBJECT

private:
	QPushButton* imageBt;
	QPushButton* fileBt;
	QPushButton* speechBt;
	QPushButton* historyBt;
	QPlainTextEdit* edit;
	QPushButton* sendBt;

public:
	explicit MessageEditArea(QWidget* parent = nullptr);

signals:
};

#include "MainWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWidget::getInstance()->show();
	return a.exec();
}

// TODO 聊天会话更多按钮点击事件 SessionTailMoreArea
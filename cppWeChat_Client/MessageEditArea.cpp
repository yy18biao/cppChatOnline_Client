#include "MessageEditArea.h"

MessageEditArea::MessageEditArea(QWidget* parent)
	: QWidget{ parent }
{
	///// 设置尺寸
	// 高度固定 宽度可变
	this->setMinimumHeight(200);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	///// 将整体部件为垂直布局
	QVBoxLayout* layout = new QVBoxLayout();
	// 设置布局里面的元素距离四个边界的间距
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	this->setLayout(layout);

	///// 头部按钮设置为水平布局
	QHBoxLayout* titleLayout = new QHBoxLayout();
	// 设置元素之间的间隔为0
	titleLayout->setSpacing(10);
	// 设置布局里面的元素距离四个边界的间距除了顶部外都为0
	titleLayout->setContentsMargins(10, 0, 0, 0);
	// 创建四个按钮
	imageBt = new QPushButton();
	fileBt = new QPushButton();
	speechBt = new QPushButton();
	historyBt = new QPushButton();
	// 设置添加按钮尺寸
	imageBt->setFixedSize(30, 30);
	fileBt->setFixedSize(30, 30);
	speechBt->setFixedSize(30, 30);
	historyBt->setFixedSize(30, 30);
	// 设置添加按钮图片尺寸和图片
	imageBt->setIconSize(QSize(30, 30));
	imageBt->setIcon(QIcon(":/image/image.png"));
	fileBt->setIconSize(QSize(30, 30));
	fileBt->setIcon(QIcon(":/image/file.png"));
	speechBt->setIconSize(QSize(30, 30));
	speechBt->setIcon(QIcon(":/image/speech.png"));
	historyBt->setIconSize(QSize(30, 30));
	historyBt->setIcon(QIcon(":/image/history.png"));
	// 设置样式
	imageBt->setStyleSheet("QPushButton { border: none; background-color: rgb(245, 245, 245); } QPushButton:pressed { background-color: #2e2e2e; }");
	fileBt->setStyleSheet("QPushButton { border: none; background-color: rgb(245, 245, 245); } QPushButton:pressed { background-color: #2e2e2e; }");
	speechBt->setStyleSheet("QPushButton { border: none; background-color: rgb(245, 245, 245); } QPushButton:pressed { background-color: #2e2e2e; }");
	historyBt->setStyleSheet("QPushButton { border: none; background-color: rgb(245, 245, 245); } QPushButton:pressed { background-color: #2e2e2e; }");

	titleLayout->addWidget(imageBt);
	titleLayout->addWidget(fileBt);
	titleLayout->addWidget(speechBt);
	titleLayout->addWidget(historyBt);
	titleLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	layout->addLayout(titleLayout, Qt::AlignTop);

	///// 中间输入框
	edit = new QPlainTextEdit();
	edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	edit->setStyleSheet("QPlainTextEdit { border: none; background-color: transparent; font-size: 14px; padding: 10px; }");
	edit->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(45, 45, 45); }");
	layout->addWidget(edit);

	///// 发送按钮
	sendBt = new QPushButton();
	sendBt->setText("发送");
	sendBt->setFixedSize(120, 40);
	QString style = "QPushButton { font-size: 16px; color: rgb(7, 193, 96); border: none; background-color: rgb(233, 233, 233); border-radius: 10px; } ";
	style += "QPushButton:hover { background-color: rgb(210, 210, 210); }";
	style += "QPushButton:pressed { background-color: rgb(190, 190, 190); }";
	sendBt->setStyleSheet(style);
	layout->addWidget(sendBt, 0, Qt::AlignRight | Qt::AlignVCenter);
}

#pragma once

#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QLabel>
#include "../data.h"
#include "../Dialog/SessionTailMoreArea.h"

////////// 右侧消息展示区 //////////
class MessageShowArea : public QScrollArea // 继承滚动
{
	Q_OBJECT

private:
	QWidget* mainWidget; // 存放内容的整体组件

public:
	MessageShowArea();

	// 清空所有消息
	void clear();

	// 尾插一条新消息
	void addMessage(bool isLeft, const model::Message& message);

	// 头插一条新消息
	void addFrontMessage(bool isLeft, const model::Message& message);
};


////////// 一条消息的部件 //////////
class MessageItem : public QWidget {
	Q_OBJECT

private:
	bool isLeft;

public:
	// isLeft表示消息的位置（分为左右）
	MessageItem(bool isLeft);

	// 使用工厂模式生成事例
	static MessageItem* makeMessageItem(bool isLeft,
		const model::Message& message);

	// 使用工厂模式生成四种不同类型的消息正文部件
	static QWidget* makeTextMessage(const QString& text, bool isLeft);
	static QWidget* makeImageMessage();
	static QWidget* makeFileMessage();
	static QWidget* makeSpeechMessage();
};

////////// 正文为文本消息的部件 //////////
class MessageTextLabel : public QWidget {
private:
	QLabel* label;
	bool isLeft;

public:
	MessageTextLabel(const QString& text, bool isLeft);

	// 文字区域的绘制
	void paintEvent(QPaintEvent* event);
};

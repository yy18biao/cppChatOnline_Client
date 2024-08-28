#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "../data.h"
#include "../Dialog/FriendInfoArea.h"

///// 好友或聊天会话的列表 //////

// 单个部件的类型枚举
enum ItemType {
	SESSIONITEMTYPE,
	FRIENDITEMTYPE,
	FRIENDAPPLYITEMTYPE
};

// 整个区域主类
class SessionFriendArea : public QScrollArea // 继承滚动组件
{
	Q_OBJECT

private:
	QWidget* mainWidget; // 存放内容的整体组件

public:
	explicit SessionFriendArea(QWidget* parent = nullptr);

	// 清空内容
	void clear();

	// 添加单个部件
	void addItem(ItemType type,
		const QString& id,
		const QIcon& photo,
		const QString& nickname,
		const QString& text);

	// 选中指定的会话
	void clickItem(int index);

signals:
};

// 单个好友或聊天会话或好友申请父类
class SessionFriendItem : public QWidget {
	Q_OBJECT

private:
	QWidget* _owner; // 单个类对应的区域主类
	bool _selected = false; // 当前类是否为选中状态
	QPushButton* _photoBt; // 头像部件
	QLabel* _nicknameLb; // 头像部件
	QLabel* _text; // 下方文本部件

public:
	// 构造函数
	// owner为该单个类对应的区域主类
	SessionFriendItem(QWidget* owner, const QIcon& photo, const QString& nickname, const QString& lastMessage);

	// 部件的get方法
	QPushButton* getPhotoBt() { return _photoBt; }
	QLabel* getNicknameLb() { return _nicknameLb; }
	QLabel* getText() { return _text; }

	// 鼠标点击事件
	void mousePressEvent(QMouseEvent* event) override;

	// 鼠标进入事件
	void enterEvent(QEnterEvent* event) override;

	// 鼠标移出事件
	void leaveEvent(QEvent* event) override;

	// 选中某个部件点击时触发的效果逻辑；
	void select();

	// 实际上的点击触发业务逻辑
	virtual void active();

	// 为了能够修改QWidget子类的样式
	// 需要重写该函数
	void paintEvent(QPaintEvent* event) override;
};

// 单个聊天会话类（继承至单个好友或聊天会话父类）
class SessionItem : public SessionFriendItem {
	Q_OBJECT

public:
	SessionItem(QWidget* owner,
		const QString& sessionId,
		const QIcon& photo,
		const QString& nickname,
		const QString& lastMessage);

	// 重写实际上的点击触发业务逻辑
	void active() override;

private:
	QString _sessionId; // 当前会话的id
};

// 单个好友框类（继承至单个好友或聊天会话父类）
class FriendItem : public SessionFriendItem {
	Q_OBJECT

public:
	FriendItem(QWidget* owner,
		const QString& sessionId,
		const QIcon& photo,
		const QString& nickname,
		const QString& desc);

	// 重写实际上的点击触发业务逻辑
	void active() override;

private:
	QString _userId; // 当前好友的id
};

// 单个好友申请框类（继承至单个好友或聊天会话父类）
class FriendApplyItem : public SessionFriendItem {
	Q_OBJECT

public:
	FriendApplyItem(QWidget* owner,
		const QString& sessionId,
		const QIcon& photo,
		const QString& nickname);

	// 重写实际上的点击触发业务逻辑
	void active() override;

private:
	QString _userId; // 当前申请人的id
};

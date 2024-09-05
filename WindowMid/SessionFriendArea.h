#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include "SessionItem.h"
#include "FriendItem.h"
#include "FriendApplyItem.h"


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

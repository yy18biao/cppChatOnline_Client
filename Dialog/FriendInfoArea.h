#pragma once

#include <QDialog>
#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>
#include "../data.h"

/// <summary>
/// 点击好友列表某个好友弹出的好友信息详情界面
/// </summary>
class FriendInfoArea : public QDialog
{
	Q_OBJECT

private:
	/*const model::UserInfo& userInfo;*/

	QGridLayout* layout;

	QPushButton* photo; // 头像

	QLabel* usernameTag; // 显示“账号”
	QLabel* usernameLabel; // 显示具体账号

	QLabel* nicknameTag; // 显示“昵称”
	QLabel* nicknameLabel; // 显示具体昵称

	QLabel* phoneTag; // 显示“电话”
	QLabel* phoneLabel; // 显示具体电话

	QLabel* descTag; // 显示“签名”
	QLabel* descLabel; // 显示具体签名

	QPushButton* chatBt; // 发送消息按钮
	QPushButton* cancelBt; // 删除好友按钮

public:
	explicit FriendInfoArea(QWidget* parent);

	// 初始化各按钮的信号槽
	void initSingalSlot();
};

#pragma once

#include <QtWidgets/QWidget>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>

#include "WindowMid/SessionFriendArea.h"
#include "WindowRight/MessageEditArea.h"
#include "WindowRight/MessageShowArea.h"
#include "Dialog/UserInfoArea.h"
#include "ui_MainWidget.h"

class MainWidget : public QWidget
{
	Q_OBJECT

		//////// 将mainWidget类设计为单例模式 ////////
private:
	static MainWidget* instance;
	MainWidget(QWidget* parent = nullptr);

public:
	static MainWidget* getInstance();

public:
	~MainWidget();

private:
    Ui::MainWidget* ui;

	QWidget* windowLeft; // 窗口左侧
	QWidget* windowMid; // 窗口中间侧
	QWidget* windowRight; // 窗口右侧

	//////// 左侧部件 /////////
	QPushButton* userPhoto; // 用户头像
	QPushButton* sessionTab; // 会话标签页按钮
	QPushButton* friendTab; // 好友列表标签页按钮
	QPushButton* applyTab; // 好友申请标签页按钮
	enum TabCur {
		SESSION_TAB,
		FRIEND_TAB,
		APPLY_TAB
	}; // 当前标签页的类型
	TabCur tabCur = SESSION_TAB; // 当前标签页记录

	//////// 中间侧部件 ////////
	QLineEdit* searchEdit; // 搜索框
	QPushButton* addButton; // 添加按钮

	//////// 右侧部件 ////////
	MessageShowArea* messageShowArea; // 消息显示区
	MessageEditArea* messageEditArea; // 消息编辑区

	//////// 相关函数声明 //////
	void initUi(); // 初始化界面
	void initMainWindow(); // 初始化整体界面布局
	void initMainWindowLeft(); // 初始化主窗口左侧
	void initMainWindowMid(); // 初始化主窗口中间侧
	void initMainWindowRight(); // 初始化主窗口右侧
	void initSignalSlot(); // 初始化信号槽
	void switchTabToSession(); // 会话标签点击槽函数
	void switchTabToFriend(); // 好友列表标签点击槽函数
	void switchTabToApply(); // 好友申请列表标签点击槽函数
	void getSessionList(); // 获取会话列表
	void getFriendList(); // 获取好友列表
	void getApplyList(); // 获取好友申请列表
};

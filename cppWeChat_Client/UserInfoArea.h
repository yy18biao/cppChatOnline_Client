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
#include "data.h"


/// <summary>
/// 点击左侧头像出现的个人信息详情页
/// </summary>
class UserInfoArea : public QDialog
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
	QLineEdit* nicknameEdit; // 编辑昵称
	QPushButton* nicknameModifyBtn; // 修改昵称
	QPushButton* nicknameSubmitBtn;	// 提交修改

	QLabel* phoneTag; // 显示“电话”
	QLabel* phoneLabel; // 显示具体电话
	QLineEdit* phoneEdit; // 编辑电话
	QPushButton* phoneModifyBtn; // 修改电话
	QPushButton* phoneSubmitBtn; // 提交修改

	QLabel* descTag; // 显示“签名”
	QLabel* descLabel; // 显示具体签名
	QLineEdit* descEdit; // 编辑签名
	QPushButton* descModifyBtn; // 修改签名
	QPushButton* descSubmitBtn; // 提交修改

	QLabel* codeTag; // 显示 "验证码"
	QLineEdit* codeEdit; // 输入验证码
	QPushButton* getCodeBtn; // 获取验证码按钮

	// 要修改的新的手机号码
	QString newPhone;

	// 获取验证码倒计时的时间
	int leftTime = 60;

public:
	explicit UserInfoArea(QWidget* parent);

	// 初始化各按钮的信号槽
	void initSingalSlot();
};

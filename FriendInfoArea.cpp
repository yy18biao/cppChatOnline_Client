#include "FriendInfoArea.h"

FriendInfoArea::FriendInfoArea(QWidget* parent)
	: QDialog(parent)
{
	///// 设置整个窗口的属性
	this->setFixedSize(500, 250);
	this->setWindowTitle("好友信息");
	this->setWindowIcon(QIcon(":/image/logo.png"));
	// 窗口被关闭时自动销毁这个对话框对象.
	this->setAttribute(Qt::WA_DeleteOnClose);
	// 把窗口移动到鼠标当前的位置
	this->move(QCursor::pos());

	///// 创建整体为网格布局管理器
	layout = new QGridLayout();
	layout->setSpacing(5);
	layout->setContentsMargins(20, 20, 20, 0);
	layout->setAlignment(Qt::AlignTop);
	this->setLayout(layout);

	///// 公共样式
	QString labelStyle = "QLabel { font-size: 14px; font-weight: 800; }";
	QString chatBtStyle = "QPushButton { background-color: rgb(0, 153, 255); color: black; } QPushButton:pressed { background-color: rgb(210, 210, 210); }";
	QString cancelBtStyle = "QPushButton { background-color: rgb(249, 47, 96); color: black; } QPushButton:pressed { background-color: rgb(210, 210, 210); }";

	///// 创建头像
	photo = new QPushButton();
	// 设置头像部件尺寸
	photo->setFixedSize(50, 50);
	// 设置头像部件图片尺寸和图片
	photo->setIconSize(QSize(50, 50));
	photo->setIcon(QIcon(":/image/photo.jpg"));
	layout->addWidget(photo, 1, 0, 3, 1);

	///// 创建账号部分
	usernameTag = new QLabel();
	usernameTag->setText("账号：");
	usernameLabel = new QLabel();
	usernameLabel->setText("1436145529");
	// 样式
	usernameTag->setStyleSheet(labelStyle);
	usernameTag->setFixedSize(50, 30);
	usernameTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	usernameLabel->setStyleSheet(labelStyle);
	usernameLabel->setFixedHeight(30);
	usernameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	// 添加到整体布局
	layout->addWidget(usernameTag, 0, 1, Qt::AlignCenter);
	layout->addWidget(usernameLabel, 0, 2, Qt::AlignLeft);

	///// 昵称部分
	nicknameTag = new QLabel();
	nicknameTag->setFixedSize(50, 30);
	nicknameTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	nicknameTag->setText("昵称");
	nicknameTag->setStyleSheet(labelStyle);

	nicknameLabel = new QLabel();
	nicknameLabel->setFixedHeight(30);
	nicknameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	nicknameLabel->setStyleSheet(labelStyle);
	nicknameLabel->setText("zhangsan");

	layout->addWidget(nicknameTag, 1, 1);
	layout->addWidget(nicknameLabel, 1, 2);

	///// 个性签名
	descTag = new QLabel();
	descTag->setFixedSize(50, 30);
	descTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	descTag->setText("签名");
	descTag->setStyleSheet(labelStyle);

	descLabel = new QLabel();
	descLabel->setFixedHeight(30);
	descLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	descLabel->setStyleSheet(labelStyle);
	descLabel->setText("我有一头小毛驴");

	layout->addWidget(descTag, 2, 1);
	layout->addWidget(descLabel, 2, 2);

	///// 手机部分
	phoneTag = new QLabel();
	phoneTag->setFixedSize(50, 30);
	phoneTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	phoneTag->setText("电话");
	phoneTag->setStyleSheet(labelStyle);

	phoneLabel = new QLabel();
	phoneLabel->setFixedHeight(30);
	phoneLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	phoneLabel->setStyleSheet(labelStyle);
	phoneLabel->setText("19898126695");

	layout->addWidget(phoneTag, 3, 1);
	layout->addWidget(phoneLabel, 3, 2);

	///// 下方按钮部分
	chatBt = new QPushButton();
	chatBt->setText("发送消息");
	chatBt->setStyleSheet(chatBtStyle);
	chatBt->setFixedSize(60, 30);

	cancelBt = new QPushButton();
	cancelBt->setText("删除好友");
	cancelBt->setStyleSheet(cancelBtStyle);
	cancelBt->setFixedSize(60, 30);

	layout->addWidget(chatBt, 4, 1);
	layout->addWidget(cancelBt, 4, 2);
}
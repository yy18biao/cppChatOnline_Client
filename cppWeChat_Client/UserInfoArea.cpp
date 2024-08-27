#include "UserInfoArea.h"

UserInfoArea::UserInfoArea(QWidget* parent)
	: QDialog(parent)
{
	///// 设置整个窗口的属性
	this->setFixedSize(500, 250);
	this->setWindowTitle("个人信息");
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
	QString btnStyle = "QPushButton { border: none; background-color: transparent; }";
	btnStyle += "QPushButton:pressed { background-color: rgb(210, 210, 210); }";
	QString editStyle = "QLineEdit { border: none; border-radius:5px; padding-left:2px; }";

	///// 创建头像
	photo = new QPushButton();
	// 设置头像部件尺寸
	photo->setFixedSize(50, 50);
	// 设置头像部件图片尺寸和图片
	photo->setIconSize(QSize(50, 50));
	photo->setIcon(QIcon(":/image/photo.jpg"));
	// 设置头像部件的底色以及去掉边框
	photo->setStyleSheet(btnStyle);
	// 添加头像部件到布局中 设置水平方向居中垂直方向靠顶部
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

	nicknameModifyBtn = new QPushButton();
	nicknameModifyBtn->setFixedSize(25, 25);
	nicknameModifyBtn->setIconSize(QSize(20, 20));
	nicknameModifyBtn->setIcon(QIcon(":/image/modify.png"));
	nicknameModifyBtn->setStyleSheet(btnStyle);

	nicknameEdit = new QLineEdit();
	nicknameEdit->setFixedHeight(30);
	nicknameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	nicknameEdit->setStyleSheet(editStyle);
	nicknameEdit->hide();

	nicknameSubmitBtn = new QPushButton();
	nicknameSubmitBtn->setFixedSize(25, 25);
	nicknameSubmitBtn->setIconSize(QSize(20, 20));
	nicknameSubmitBtn->setIcon(QIcon(":/image/ok.png"));
	nicknameSubmitBtn->setStyleSheet(btnStyle);
	nicknameSubmitBtn->hide();

	layout->addWidget(nicknameTag, 1, 1);
	layout->addWidget(nicknameLabel, 1, 2);
	layout->addWidget(nicknameModifyBtn, 1, 3);

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

	descModifyBtn = new QPushButton();
	descModifyBtn->setFixedSize(25, 25);
	descModifyBtn->setIconSize(QSize(20, 20));
	descModifyBtn->setIcon(QIcon(":/image/modify.png"));
	descModifyBtn->setStyleSheet(btnStyle);

	descEdit = new QLineEdit();
	descEdit->setFixedHeight(30);
	descEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	descEdit->setStyleSheet(editStyle);
	descEdit->hide();

	descSubmitBtn = new QPushButton();
	descSubmitBtn->setFixedSize(25, 25);
	descSubmitBtn->setIconSize(QSize(20, 20));
	descSubmitBtn->setIcon(QIcon(":/image/submit.png"));
	descSubmitBtn->setStyleSheet(btnStyle);
	descSubmitBtn->hide();

	layout->addWidget(descTag, 2, 1);
	layout->addWidget(descLabel, 2, 2);
	layout->addWidget(descModifyBtn, 2, 3);

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

	phoneModifyBtn = new QPushButton();
	phoneModifyBtn->setFixedSize(25, 25);
	phoneModifyBtn->setIconSize(QSize(20, 20));
	phoneModifyBtn->setIcon(QIcon(":/image/modify.png"));
	phoneModifyBtn->setStyleSheet(btnStyle);

	phoneEdit = new QLineEdit();
	phoneEdit->setFixedHeight(30);
	phoneEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	phoneEdit->setStyleSheet(editStyle);
	phoneEdit->hide();

	phoneSubmitBtn = new QPushButton();
	phoneSubmitBtn->setFixedSize(25, 25);
	phoneSubmitBtn->setIconSize(QSize(20, 20));
	phoneSubmitBtn->setIcon(QIcon(":/image/submit.png"));
	phoneSubmitBtn->setStyleSheet(btnStyle);
	phoneSubmitBtn->hide();

	layout->addWidget(phoneTag, 3, 1);
	layout->addWidget(phoneLabel, 3, 2);
	layout->addWidget(phoneModifyBtn, 3, 3);

	///// 验证码部分
	codeTag = new QLabel();
	codeTag->setFixedSize(50, 30);
	codeTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	codeTag->setText("验证码");
	codeTag->setStyleSheet(labelStyle);
	codeTag->hide();

	codeEdit = new QLineEdit();
	codeEdit->setFixedHeight(30);
	codeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	codeEdit->setStyleSheet(editStyle);
	codeEdit->hide();

	getCodeBtn = new QPushButton();
	getCodeBtn->setText("获取验证码");
	getCodeBtn->setStyleSheet("QPushButton { border: none; background-color: transparent; } QPushButton:pressed { background-color: rgb(231, 231, 231); }");
	getCodeBtn->setFixedSize(70, 30);
	getCodeBtn->hide();


	///// 初始化信号槽
	initSingalSlot();
}

void UserInfoArea::initSingalSlot()
{
	///// 修改昵称按钮
	connect(nicknameModifyBtn, &QPushButton::clicked, this, [=]() {
		// 隐藏显示的账号和修改按钮
		nicknameLabel->hide();
		nicknameModifyBtn->hide();
		layout->removeWidget(nicknameLabel);
		layout->removeWidget(nicknameModifyBtn);
		// 显示输入框和确认按钮
		nicknameEdit->show();
		nicknameSubmitBtn->show();
		layout->addWidget(nicknameEdit, 1, 2);
		layout->addWidget(nicknameSubmitBtn, 1, 3);
		// 设置新的昵称
		nicknameEdit->setText(nicknameLabel->text());
		});

	///// 确认修改昵称按钮
	connect(nicknameSubmitBtn, &QPushButton::clicked, this, [=]() {
		const QString& nickname = nicknameEdit->text();
		if (nickname.isEmpty())
			return;

		// 隐藏输入框和确认按钮
		layout->removeWidget(nicknameEdit);
		nicknameEdit->hide();
		layout->removeWidget(nicknameSubmitBtn);
		nicknameSubmitBtn->hide();

		// 显示账号和修改按钮
		layout->addWidget(nicknameLabel, 1, 2);
		nicknameLabel->show();
		nicknameLabel->setText(nicknameEdit->text());
		layout->addWidget(nicknameModifyBtn, 1, 3);
		nicknameModifyBtn->show();
		});

	///// 个性签名修改按钮
	connect(descModifyBtn, &QPushButton::clicked, this, [=]() {
		descLabel->hide();
		descModifyBtn->hide();
		layout->removeWidget(descLabel);
		layout->removeWidget(descModifyBtn);

		descEdit->show();
		descSubmitBtn->show();
		layout->addWidget(descEdit, 2, 2);
		layout->addWidget(descSubmitBtn, 2, 3);

		descEdit->setText(descLabel->text());
		});

	///// 电话号码修改按钮
	connect(phoneModifyBtn, &QPushButton::clicked, this, [=]() {
		phoneLabel->hide();
		phoneModifyBtn->hide();
		layout->removeWidget(phoneLabel);
		layout->removeWidget(phoneModifyBtn);

		phoneEdit->show();
		phoneSubmitBtn->show();
		layout->addWidget(phoneEdit, 3, 2);
		layout->addWidget(phoneSubmitBtn, 3, 3);

		// 显示出验证码部分
		codeTag->show();
		codeEdit->show();
		getCodeBtn->show();
		layout->addWidget(codeTag, 4, 1);
		layout->addWidget(codeEdit, 4, 2);
		layout->addWidget(getCodeBtn, 4, 3);

		phoneEdit->setText(phoneLabel->text());
		});
}

#include "MainWidget.h"

//////// 单例模式创建实例实现 ////////
MainWidget* MainWidget::instance = nullptr;
MainWidget* MainWidget::getInstance()
{
	if (instance == nullptr) {
		// 不传参数 以桌面作为父窗口
		instance = new MainWidget();
	}
	return instance;
}

MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MainWidgetClass)
{
	ui->setupUi(this);

	// 设置窗口标题
	this->setWindowTitle("WeChat");
	this->setWindowIcon(QIcon(":/image/logo.png"));

	// 初始化界面
	initUi();

	// 初始化信号槽
	initSignalSlot();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::initUi()
{
	initMainWindow();
	initMainWindowLeft();
	initMainWindowMid();
	initMainWindowRight();
}

void MainWidget::initMainWindow()
{
	///// 设置为水平布局
	QHBoxLayout* layout = new QHBoxLayout();
	// 设置布局的间隔为0
	layout->setSpacing(0);
	// 设置布局里面的元素距离四个边界的间距为0
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);

	///// 为三侧窗口创建实例
	windowLeft = new QWidget();
	windowMid = new QWidget();
	windowRight = new QWidget();

	///// 设置三侧窗口的名称
	windowLeft->setObjectName("windowLeft");
	windowMid->setObjectName("windowMid");
	windowRight->setObjectName("windowRight");

	///// 设置三侧窗口的宽度
	windowLeft->setFixedWidth(60);
	windowMid->setFixedWidth(200);
	// 右侧聊天框不需要设置固定宽度 可以让其进行缩放所以只需要设置最小宽度
	windowRight->setMinimumWidth(650);

	///// 设置三侧窗口的颜色
	windowLeft->setStyleSheet("QWidget { background-color: #2e2e2e; }");
	windowMid->setStyleSheet("QWidget { background-color: #e9e7e6; }");
	windowRight->setStyleSheet("QWidget { background-color: #f5f5f5; }");

	///// 将三侧窗口添加进主窗口
	layout->addWidget(windowLeft);
	layout->addWidget(windowMid);
	layout->addWidget(windowRight);

	// 设置主窗口的最小高度
	this->setMinimumHeight(651);
}

void MainWidget::initMainWindowLeft()
{
	///// 设置垂直布局
	QVBoxLayout* layout = new QVBoxLayout();
	// 设置元素之间的间隔为20
	layout->setSpacing(30);
	// 设置布局里面的元素距离四个边界的间距除了顶部外都为0
	layout->setContentsMargins(0, 40, 0, 0);
	windowLeft->setLayout(layout);

	///// 头像部件
	userPhoto = new QPushButton();
	// 设置头像部件尺寸
	userPhoto->setFixedSize(40, 40);
	// 设置头像部件图片尺寸和图片
	userPhoto->setIconSize(QSize(40, 40));
	userPhoto->setIcon(QIcon(":/image/photo.jpg"));
	// 设置头像部件的底色以及去掉边框
	userPhoto->setStyleSheet("QWidget { background-color: #2e2e2e; border: none}");
	// 添加头像部件到布局中 设置水平方向居中垂直方向靠顶部
	layout->addWidget(userPhoto, 1, Qt::AlignTop | Qt::AlignHCenter);

	///// 会话标签
	sessionTab = new QPushButton();
	// 设置会话标签尺寸
	sessionTab->setFixedSize(30, 30);
	// 设置会话标签图片尺寸和图片
	sessionTab->setIconSize(QSize(30, 30));
	sessionTab->setIcon(QIcon(":/image/sessionTab2.png"));
	// 设置会话标签的底色以及去掉边框
	sessionTab->setStyleSheet("QWidget { background-color: #2e2e2e; border: none}");
	// 添加会话标签到布局中 设置水平方向居中垂直方向靠顶部
	layout->addWidget(sessionTab, 1, Qt::AlignTop | Qt::AlignHCenter);


	///// 好友列表标签
	friendTab = new QPushButton();
	// 设置会话标签尺寸
	friendTab->setFixedSize(30, 30);
	// 设置会话标签图片尺寸和图片
	friendTab->setIconSize(QSize(30, 30));
	friendTab->setIcon(QIcon(":/image/friendTab1.png"));
	// 设置会话标签的底色以及去掉边框
	friendTab->setStyleSheet("QWidget { background-color: #2e2e2e; border: none}");
	// 添加会话标签到布局中 设置水平方向居中垂直方向靠顶部
	layout->addWidget(friendTab, 1, Qt::AlignTop | Qt::AlignHCenter);

	///// 好友申请列表标签
	applyTab = new QPushButton();
	// 设置会话标签尺寸
	applyTab->setFixedSize(30, 30);
	// 设置会话标签图片尺寸和图片
	applyTab->setIconSize(QSize(30, 30));
	applyTab->setIcon(QIcon(":/image/applyTab1.png"));
	// 设置会话标签的底色以及去掉边框
	applyTab->setStyleSheet("QWidget { background-color: #2e2e2e; border: none}");
	// 添加会话标签到布局中 设置水平方向居中垂直方向靠顶部
	layout->addWidget(applyTab, 1, Qt::AlignTop | Qt::AlignHCenter);

	///// 下方添加空隙, 将部件全部挤上去
	layout->addStretch(20);
}

void MainWidget::initMainWindowMid()
{
	// 去除默认边框
	windowMid->setStyleSheet("QWidget { border: none; }");

	///// 设置网格布局
	QGridLayout* layout = new QGridLayout();
	// 设置元素之间的垂直间隔为10 水平间隔为0
	layout->setVerticalSpacing(10);
	layout->setHorizontalSpacing(0);
	// 设置布局里面的元素距离四个边界的间距除了顶部外都为0
	layout->setContentsMargins(0, 10, 0, 0);
	windowMid->setLayout(layout);

	///// 搜索框部件
	searchEdit = new QLineEdit();
	searchEdit->setFixedHeight(30);
	searchEdit->setPlaceholderText("搜索");
	searchEdit->setStyleSheet("QLineEdit { border-radius: 5px; background-color: #e2e2e2; }");

	///// 添加按钮部件
	addButton = new QPushButton();
	// 设置添加按钮尺寸
	addButton->setFixedSize(30, 30);
	// 设置添加按钮图片尺寸和图片
	addButton->setIconSize(QSize(30, 30));
	addButton->setIcon(QIcon(":/image/addButton.png"));
	// 设置样式
	QString style = "QPushButton { border: none; background-color: #e9e7e6; } QPushButton:pressed { background-color: #2e2e2e; }";
	addButton->setStyleSheet(style);

	///// 会话好友列表
	SessionFriendArea* sessionFriendArea = new SessionFriendArea();

	///// 添加部件到布局中
	// 通过添加空白 widget 来控制搜索框和搜索按钮之间的边距
	QWidget* spacer1 = new QWidget();
	spacer1->setFixedWidth(10);
	QWidget* spacer2 = new QWidget();
	spacer2->setFixedWidth(10);
	QWidget* spacer3 = new QWidget();
	spacer3->setFixedWidth(10);

	layout->addWidget(spacer1, 0, 0);
	layout->addWidget(searchEdit, 0, 1);
	layout->addWidget(spacer2, 0, 2);
	layout->addWidget(addButton, 0, 3);
	layout->addWidget(spacer3, 0, 4);
	// 整个列表区域放在2行 0列 行方向跨一行 列方向跨五列
	layout->addWidget(sessionFriendArea, 1, 0, 1, 5);
}

void MainWidget::initMainWindowRight()
{
	///// 设置垂直布局
	QVBoxLayout* layout = new QVBoxLayout();
	// 设置元素之间的间隔为20
	layout->setSpacing(0);
	// 设置布局里面的元素距离四个边界的间距除了顶部外都为0
	layout->setContentsMargins(0, 0, 0, 0);
	// 修改对齐方式靠上
	layout->setAlignment(Qt::AlignTop);
	windowRight->setLayout(layout);

	///// 创建上方标题栏
	QWidget* title = new QWidget();
	title->setFixedHeight(51);
	// 尺寸策略设为水平不固定垂直固定
	title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	// 设置整体的样式
	title->setObjectName("title");
	title->setStyleSheet("#title { border-bottom: 1px solid rgb(231, 231, 231); }");
	// 创建水平布局
	QHBoxLayout* titleLayout = new QHBoxLayout();
	// 设置元素之间的间隔为0
	titleLayout->setSpacing(0);
	// 设置布局里面的元素距离四个边界的间距除了顶部外都为0
	titleLayout->setContentsMargins(20, 0, 0, 10);
	// 创建好友名字的label
	QLabel* nicknameLb = new QLabel();
	nicknameLb->setStyleSheet("QLabel { font-size: 22px; }");
	nicknameLb->setText("zhangsan");
	// 创建 ... 更多选项按钮
	QPushButton* extraBt = new QPushButton();
	extraBt->setFixedSize(30, 30);
	extraBt->setIconSize(QSize(30, 30));
	extraBt->setIcon(QIcon(":/image/more.png"));
	extraBt->setStyleSheet("QPushButton { border: none;  }");
	// 添加部件到布局
	titleLayout->addWidget(nicknameLb);
	titleLayout->addWidget(extraBt);
	// 添加布局到标题栏
	title->setLayout(titleLayout);
	// 添加标题栏到整体布局
	layout->addWidget(title);

	///// 消息显示区
	messageShowArea = new MessageShowArea();
	layout->addWidget(messageShowArea);

	///// 编辑区
	messageEditArea = new MessageEditArea();
	// 固定高度，位于下方
	layout->addWidget(messageEditArea, 0, Qt::AlignBottom);
}

void MainWidget::initSignalSlot()
{
	///// 处理标签按钮的点击操作
	connect(sessionTab, &QPushButton::clicked, this, &MainWidget::switchTabToSession);
	connect(friendTab, &QPushButton::clicked, this, &MainWidget::switchTabToFriend);
	connect(applyTab, &QPushButton::clicked, this, &MainWidget::switchTabToApply);

	///// 左侧头像点击操作
	connect(userPhoto, &QPushButton::clicked, this, [=]() {
		UserInfoArea* userInfoArea = new UserInfoArea(this);
		userInfoArea->exec();
		});
}

void MainWidget::switchTabToSession()
{
	if (tabCur == SESSION_TAB) {
		return;
	}
	// 改变上一个的标签按钮的图标的颜色
	if (tabCur == FRIEND_TAB) {
		friendTab->setIcon(QIcon(":/image/friendTab1.png"));
	}
	else if (tabCur == APPLY_TAB) {
		applyTab->setIcon(QIcon(":/image/applyTab1.png"));
	}
	// 改变当前标签页的记录
	tabCur = SESSION_TAB;
	// 改变标签图标的颜色
	sessionTab->setIcon(QIcon(":/image/sessionTab2.png"));

}

void MainWidget::switchTabToFriend()
{
	if (tabCur == FRIEND_TAB) {
		return;
	}
	// 改变上一个的标签按钮的图标的颜色
	if (tabCur == SESSION_TAB) {
		sessionTab->setIcon(QIcon(":/image/sessionTab1.png"));
	}
	else if (tabCur == APPLY_TAB) {
		applyTab->setIcon(QIcon(":/image/applyTab1.png"));
	}
	// 改变当前标签页的记录
	tabCur = FRIEND_TAB;
	// 改变标签图标的颜色
	friendTab->setIcon(QIcon(":/image/friendTab2.png"));
}

void MainWidget::switchTabToApply()
{
	if (tabCur == APPLY_TAB) {
		return;
	}
	// 改变上一个的标签按钮的图标的颜色
	if (tabCur == SESSION_TAB) {
		sessionTab->setIcon(QIcon(":/image/sessionTab1.png"));
	}
	else if (tabCur == FRIEND_TAB) {
		friendTab->setIcon(QIcon(":/image/friendTab1.png"));
	}
	// 改变当前标签页的记录
	tabCur = APPLY_TAB;
	// 改变标签图标的颜色
	applyTab->setIcon(QIcon(":/image/applyTab2.png"));
}

void MainWidget::getSessionList()
{

}

void MainWidget::getFriendList()
{

}

void MainWidget::getApplyList()
{

}

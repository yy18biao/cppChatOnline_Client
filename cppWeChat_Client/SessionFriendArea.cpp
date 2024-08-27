#include "SessionFriendArea.h"

////////// 整个区域主类 //////////
SessionFriendArea::SessionFriendArea(QWidget* parent)
	: QScrollArea{ parent }
{
	///// 设置部件属性
	// 开启滚动效果
	this->setWidgetResizable(true);
	// 滚动条样式
	this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(184, 182, 180); }");
	this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
	// 设置内部的主要部件
	mainWidget = new QWidget();
	mainWidget->setFixedWidth(250);
	this->setWidget(mainWidget);

	///// 设置存放内容组件的属性
	// 设置垂直布局
	QVBoxLayout* layout = new QVBoxLayout();
	// 设置元素之间的间隔为0
	layout->setSpacing(0);
	// 设置布局里面的元素距离四个边界的间距都为0
	layout->setContentsMargins(0, 0, 0, 0);
	// 设置所有元素靠顶部对齐
	layout->setAlignment(Qt::AlignTop);
	// 添加布局到组件
	mainWidget->setLayout(layout);

	// 添加测试效果
	this->addItem(FRIENDITEMTYPE, "1",
		QIcon(":/image/photo.jpg"), "zhangsan", "woyou");
	this->addItem(FRIENDITEMTYPE, "2",
		QIcon(":/image/logo.png"), "lisi", "hi");
}

void SessionFriendArea::clear()
{
	// 获取到整体的布局元素
	QLayout* layout = mainWidget->layout();

	// 遍历布局元素里的所有元素，依次移除
	for (int i = layout->count() - 1; i >= 0; --i) {
		QLayoutItem* item = layout->takeAt(i);
		// 移除之后释放对象
		if (item && item->widget())
			delete item->widget();
	}
}

void SessionFriendArea::addItem(ItemType type,
	const QString& id,
	const QIcon& photo,
	const QString& nickname,
	const QString& text)
{
	// 创建新的部件
	SessionFriendItem* item = nullptr;
	if (type == SESSIONITEMTYPE)
		item = new SessionItem(this, id, photo, nickname, text);
	else if (type == FRIENDITEMTYPE)
		item = new FriendItem(this, id, photo, nickname, text);
	else if (type == FRIENDAPPLYITEMTYPE)
		item = new FriendApplyItem(this, id, photo, nickname);
	else {
		LOG() << "需要添加的部件属性不合理";
		return;
	}

	// 将部件添加到整体区域中
	mainWidget->layout()->addWidget(item);
}

void SessionFriendArea::clickItem(int index)
{
	// 判断下标合理性
	if (index < 0 || index >= mainWidget->layout()->count()) {
		LOG() << "点击元素下标超出范围 index=" << index;
		return;
	}

	// 判断元素的合理性
	QLayoutItem* layoutItem = mainWidget->layout()->itemAt(index);
	if (layoutItem == nullptr || layoutItem->widget() == nullptr) {
		LOG() << "元素不存在";
		return;
	}

	SessionFriendItem* item = dynamic_cast<SessionFriendItem*>(layoutItem);
	item->select();
}


////////// 单个好友或聊天会话或好友申请部件的父类 //////////
SessionFriendItem::SessionFriendItem(QWidget* owner,
	const QIcon& photo,
	const QString& nickname,
	const QString& lastMessage)
	: _owner(owner)
{
	///// 设置整体的样式
	this->setFixedHeight(70);
	this->setStyleSheet("QWidget { background-color: rgb(229, 228, 228);}");

	///// 将整体设置为网格布局
	QGridLayout* layout = new QGridLayout();
	// 设置布局里面的元素距离四个边界的间距除了左侧外都为0
	layout->setContentsMargins(10, 0, 0, 0);
	// 设置布局里面的元素相互之间水平间距为10，垂直间距为0
	layout->setHorizontalSpacing(10);
	layout->setVerticalSpacing(0);
	this->setLayout(layout);

	///// 头像部分
	_photoBt = new QPushButton();
	// 设置尺寸
	_photoBt->setFixedSize(50, 50);
	// 设置图片尺寸、图片、样式
	_photoBt->setIconSize(QSize(50, 50));
	_photoBt->setIcon(photo);
	_photoBt->setStyleSheet("QPushButton { border: none; }");
	// 尺寸策略设为固定
	_photoBt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	///// 用户昵称部分
	_nicknameLb = new QLabel();
	// 设置尺寸、文字、样式
	_nicknameLb->setText(nickname);
	_nicknameLb->setStyleSheet("QLabel { font-size: 18px; font-weight: 600; }");
	_nicknameLb->setFixedHeight(35);
	// 尺寸策略设为水平不固定垂直固定
	_nicknameLb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	///// 下方文本
	_text = new QLabel();
	// 设置尺寸、文字、样式
	_text->setText(lastMessage);
	_text->setFixedHeight(35);
	// 尺寸策略设为水平不固定垂直固定
	_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	///// 将设置后的部件添加到布局中
	layout->addWidget(_photoBt, 0, 0, 2, 2); // 0行0列占2行2列
	layout->addWidget(_nicknameLb, 0, 2, 1, 8); // 0行2列占1行1列
	layout->addWidget(_text, 1, 2, 1, 8); // 1行2列占1行1列
}

void SessionFriendItem::mousePressEvent(QMouseEvent* event)
{
	(void)event;
	select();
}

void SessionFriendItem::enterEvent(QEnterEvent* event)
{
	(void)event;
	// 修改当前选中的
	if (!this->_selected)
		this->setStyleSheet("QWidget { background-color: rgb(197, 196, 197);}");
}

void SessionFriendItem::leaveEvent(QEvent* event)
{
	(void)event;
	// 修改当前选中的
	if (!this->_selected)
		this->setStyleSheet("QWidget { background-color: rgb(229, 228, 228);}");
}

void SessionFriendItem::select()
{
	///// 修改选中的背景色并将其他的背景色还原
	// 获取到当前整个区域里的其他单个会话元素
	// 判断它们的_selected是否为true
	// 如果是则改为false并还原背景色
	const QObjectList items = this->parentWidget()->children();
	for (QObject* item : items) {
		// 首先判断是否为widget元素
		if (!item->isWidgetType()) {
			continue;
		}
		// 判断成功将其强转为SessionFriendItem类型
		SessionFriendItem* ii = dynamic_cast<SessionFriendItem*>(item);
		if (ii->_selected) {
			ii->_selected = false;
			ii->setStyleSheet("QWidget { background-color: rgb(229, 228, 228);}");
		}
	}
	// 修改当前选中的
	this->setStyleSheet("QWidget { background-color: rgb(197, 196, 197);}");
	this->_selected = true;

	// 实现业务逻辑
	this->active();
}

void SessionFriendItem::active()
{

}


void SessionFriendItem::paintEvent(QPaintEvent* event)
{
	(void)event;
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


////////// 单个聊天会话类（继承至单个好友或聊天会话父类）//////////
SessionItem::SessionItem(QWidget* owner, const QString& sessionId, const QIcon& photo, const QString& nickname, const QString& lastMessage)
	: SessionFriendItem(owner, photo, nickname, lastMessage),
	_sessionId(sessionId)
{

}

void SessionItem::active()
{
	// TODO 聊天会话点击之后的业务处理逻辑实现
}


////////// 单个好友框类（继承至单个好友或聊天会话父类）//////////
FriendItem::FriendItem(QWidget* owner, const QString& userId, const QIcon& photo, const QString& nickname, const QString& desc)
	: SessionFriendItem(owner, photo, nickname, desc),
	_userId(userId)
{

}

void FriendItem::active()
{
	// TODO 好友框点击之后的业务处理逻辑实现
	FriendInfoArea* friendInfo = new FriendInfoArea(this);
	friendInfo->exec();
}

////////// 单个好友申请框类（继承至单个好友或聊天会话父类）//////////
FriendApplyItem::FriendApplyItem(QWidget* owner,
	const QString& userId,
	const QIcon& photo,
	const QString& nickname)
	: SessionFriendItem(owner, photo, nickname, ""),
	_userId(userId)
{
	///// 移除父类构造中的下方文本改为两个按钮

	// 移除
	QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
	QLabel* text = getText();
	layout->removeWidget(text);
	delete text;

	// 创建按钮
	QPushButton* aBt = new QPushButton();
	QPushButton* rBt = new QPushButton();
	aBt->setText("同意");
	rBt->setText("拒绝");
	aBt->setStyleSheet("QPushButton { background-color: rgb(0, 153, 255); }");
	rBt->setStyleSheet("QPushButton { background-color: rgb(0, 153, 255); }");

	layout->addWidget(aBt, 1, 2, 1, 1);
	layout->addWidget(rBt, 1, 3, 1, 1);
}

void FriendApplyItem::active()
{
	// TODO 好友申请框点击之后的业务处理逻辑实现
}

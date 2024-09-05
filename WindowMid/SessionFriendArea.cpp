#include "SessionFriendArea.h"

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

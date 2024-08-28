#include "MessageShowArea.h"

////////// 右侧消息展示区 //////////
MessageShowArea::MessageShowArea() {
	///// 设置部件属性
	this->setMinimumHeight(400);
	// 尺寸策略
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	// 开启滚动效果
	this->setWidgetResizable(true);
	// 滚动条样式
	this->verticalScrollBar()->setStyleSheet(
		"QScrollBar:vertical { width: 2px; background-color: rgb(184, 182, 180); }");
	this->horizontalScrollBar()->setStyleSheet(
		"QScrollBar:horizontal { height: 0px; }");
	this->setStyleSheet("QScrollArea { border: none; }");
	// 设置内部的主要部件
	mainWidget = new QWidget();
	this->setWidget(mainWidget);

	///// 设置垂直布局
	QVBoxLayout* layout = new QVBoxLayout();
	// 设置布局里面的元素距离四个边界的间距除了左侧外都为0
	layout->setContentsMargins(0, 0, 0, 0);
	mainWidget->setLayout(layout);

	// test
	for (int i = 0; i < 30; ++i) {
		model::UserInfo user;
		user._userPhoto = QIcon(":/image/photo.jpg");
		user._nickname = "zhangsan" + QString::number(i);

		model::Message message = model::Message::makeMessage(model::TEXT,
			QString::number(i),
			user,
			QString("测试消息").toUtf8(),
			"");
		if (i % 2 == 0)
			this->addMessage(true, message);
		else
			this->addMessage(false, message);
	}
}

void MessageShowArea::clear()
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

void MessageShowArea::addMessage(bool isLeft, const model::Message& message)
{
	// 构造一条消息部件并添加到布局
	mainWidget->layout()->addWidget(MessageItem::makeMessageItem(isLeft, message));
}

void MessageShowArea::addFrontMessage(bool isLeft, const model::Message& message)
{
	// 构造一条消息部件并添加到布局
	MessageItem* item = MessageItem::makeMessageItem(isLeft, message);
	QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(mainWidget->layout());
	layout->insertWidget(0, item);
}

////////// 一条消息的部件 //////////
MessageItem::MessageItem(bool isLeft)
{

}

MessageItem* MessageItem::makeMessageItem(bool isLeft, const model::Message& message)
{
	///// 创建一个消息部件
	MessageItem* item = new MessageItem(isLeft);
	item->setMinimumHeight(30);

	///// 将整体部件为网格布局
	QGridLayout* layout = new QGridLayout();
	// 设置布局里面的元素距离四个边界的间距除了左侧外都为0
	layout->setContentsMargins(10, 0, 10, 0);
	layout->setSpacing(5);
	// 添加布局到部件
	item->setLayout(layout);

	///// 头像部分
	QPushButton* photoBt = new QPushButton();
	// 设置尺寸
	photoBt->setFixedSize(30, 30);
	// 设置图片尺寸、图片、样式
	photoBt->setIconSize(QSize(30, 30));
	// 头像设置为发送该条消息的用户的头像
	photoBt->setIcon(message._sendUserInfo._userPhoto);
	photoBt->setStyleSheet("QPushButton { border: none; }");
	// 尺寸策略设为固定
	photoBt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	// 根据消息的左右侧情况分别放在布局的左侧和右侧
	if (isLeft)
		layout->addWidget(photoBt, 0, 0, 2, 1, Qt::AlignTop | Qt::AlignLeft);
	else
		layout->addWidget(photoBt, 0, 1, 2, 1, Qt::AlignTop | Qt::AlignRight);

	///// 用户昵称部分
	QLabel* nicknameLb = new QLabel();
	// 设置尺寸、文字、样式
	nicknameLb->setText(message._sendUserInfo._nickname + " | " + message._messageTime);
	nicknameLb->setAlignment(Qt::AlignTop);
	nicknameLb->setStyleSheet("QLabel { font-size: 12px; color: rgb(197, 197, 197); }");
	// 根据消息的左右侧情况分别放在头像的左侧和右侧
	if (isLeft)
		layout->addWidget(nicknameLb, 0, 1, Qt::AlignLeft);
	else
		layout->addWidget(nicknameLb, 0, 0, Qt::AlignRight);


	///// 消息部分
	QWidget* content = nullptr;
	// 根据消息类型创建不同的类型
	switch (message._messageType)
	{
	case model::TEXT:
		content = makeTextMessage(message._messageContent, isLeft);
		break;
	case model::IMAGE:
		content = makeImageMessage();
		break;
	case model::FILE:
		content = makeFileMessage();
		break;
	case model::SPEECH:
		content = makeSpeechMessage();
		break;
	default:
		break;
	}

	// 根据消息的左右侧情况分别放在头像的左侧和右侧
	if (isLeft)
		layout->addWidget(content, 1, 1);
	else
		layout->addWidget(content, 1, 0);

	return item;
}

QWidget* MessageItem::makeTextMessage(const QString& text, bool isLeft)
{
	return new MessageTextLabel(text, isLeft);
}

QWidget* MessageItem::makeImageMessage()
{
	return nullptr;
}

QWidget* MessageItem::makeFileMessage()
{
	return nullptr;
}

QWidget* MessageItem::makeSpeechMessage()
{
	return nullptr;
}


////////// 正文为文本消息的部件 //////////
MessageTextLabel::MessageTextLabel(const QString& text, bool isLeft)
	: isLeft(isLeft)
{
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QFont font;
	font.setFamily("微软雅黑");
	font.setPixelSize(16);

	this->label = new QLabel(this);
	this->label->setText(text);
	this->label->setFont(font);
	this->label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	// 设置文本自动换行
	this->label->setWordWrap(true);
	this->label->setStyleSheet(
		"QLabel { padding: 0 10px; line-height: 1.2; background-color: transparent; }");
}

// 文字区域的绘制
void MessageTextLabel::paintEvent(QPaintEvent* event)
{
	(void)event;

	// 获取到父元素的宽度
	QObject* object = this->parent();
	if (!object->isWidgetType()) {
		return;
	}
	QWidget* parent = dynamic_cast<QWidget*>(object);
	int width = parent->width() * 0.6;

	// 计算当前文本, 一行放置时需要的宽度
	QFontMetrics metrics(this->label->font());
	int totalWidth = metrics.horizontalAdvance(this->label->text());

	// 计算此处的行数是多少
	int rows = (totalWidth / (width - 40)) + 1;
	if (rows == 1) {
		// 如果此时得到的行数就只有一行
		width = totalWidth + 40;
	}

	// 根据行数计算得到高度(20 表示上下各有 10px 的边距)
	int height = rows * (this->label->font().pixelSize() * 1.2) + 20;

	// 绘制圆角矩形和箭头
	QPainter painter(this);
	QPainterPath path;
	// 设置 "抗锯齿"
	painter.setRenderHint(QPainter::Antialiasing);
	if (isLeft) {
		painter.setPen(QPen(QColor(255, 255, 255)));
		painter.setBrush(QColor(255, 255, 255));

		// 绘制圆角矩形
		painter.drawRoundedRect(10, 0, width, height, 10, 10);
		// 绘制箭头
		path.moveTo(10, 15);
		path.lineTo(0, 20);
		path.lineTo(10, 25);
		path.closeSubpath();   // 绘制的线形成闭合的多边形
		painter.drawPath(path);  // 最终的绘制操作

		this->label->setGeometry(10, 0, width, height);
	}
	else {
		painter.setPen(QPen(QColor(137, 217, 97)));
		painter.setBrush(QColor(137, 217, 97));

		// 圆角矩形左侧边的横坐标位置
		int leftPos = this->width() - width - 10;
		// 圆角矩形右侧边的横坐标位置
		int rightPos = this->width() - 10;
		// 绘制圆角矩形
		painter.drawRoundedRect(leftPos, 0, width, height, 10, 10);
		// 绘制箭头
		path.moveTo(rightPos, 15);
		path.lineTo(rightPos + 10, 20);
		path.lineTo(rightPos, 25);
		path.closeSubpath();
		painter.drawPath(path);

		this->label->setGeometry(leftPos, 0, width, height);
	}

	// 6. 重新设置父元素的高度, 确保父元素足够高, 能够容纳下上述绘制的消息显示的区域
	//    注意高度要涵盖之前名字和时间的 label 的高度, 以及留点冗余空间.
	parent->setFixedHeight(height + 20);
}
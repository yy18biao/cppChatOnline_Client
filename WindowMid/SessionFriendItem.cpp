#include "SessionFriendItem.h"

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


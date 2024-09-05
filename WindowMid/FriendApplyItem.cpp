#include "FriendApplyItem.h"

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


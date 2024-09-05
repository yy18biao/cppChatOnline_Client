#ifndef SESSIONFRIENDITEM_H
#define SESSIONFRIENDITEM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "../data.h"
#include "../Dialog/FriendInfoArea.h"

// 单个好友或聊天会话或好友申请父类
class SessionFriendItem : public QWidget {
    Q_OBJECT

private:
    QWidget* _owner; // 单个类对应的区域主类
    bool _selected = false; // 当前类是否为选中状态
    QPushButton* _photoBt; // 头像部件
    QLabel* _nicknameLb; // 头像部件
    QLabel* _text; // 下方文本部件

public:
    // 构造函数
    // owner为该单个类对应的区域主类
    SessionFriendItem(QWidget* owner, const QIcon& photo, const QString& nickname, const QString& lastMessage);

    // 部件的get方法
    QPushButton* getPhotoBt() { return _photoBt; }
    QLabel* getNicknameLb() { return _nicknameLb; }
    QLabel* getText() { return _text; }

    // 鼠标点击事件
    void mousePressEvent(QMouseEvent* event) override;

    // 鼠标进入事件
    void enterEvent(QEnterEvent* event) override;

    // 鼠标移出事件
    void leaveEvent(QEvent* event) override;

    // 选中某个部件点击时触发的效果逻辑；
    void select();

    // 实际上的点击触发业务逻辑
    virtual void active();

    // 为了能够修改QWidget子类的样式
    // 需要重写该函数
    void paintEvent(QPaintEvent* event) override;
};

#endif // SESSIONFRIENDITEM_H

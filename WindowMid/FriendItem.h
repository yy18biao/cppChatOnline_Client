#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include "SessionFriendItem.h"

// 单个好友框类（继承至单个好友或聊天会话父类）
class FriendItem : public SessionFriendItem {
    Q_OBJECT

public:
    FriendItem(QWidget* owner,
               const QString& sessionId,
               const QIcon& photo,
               const QString& nickname,
               const QString& desc);

    // 重写实际上的点击触发业务逻辑
    void active() override;

private:
    QString _userId; // 当前好友的id
};

#endif // FRIENDITEM_H

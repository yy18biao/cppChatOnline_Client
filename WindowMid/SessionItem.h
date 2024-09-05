#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include "SessionFriendItem.h"

// 单个聊天会话类（继承至单个好友或聊天会话父类）
class SessionItem : public SessionFriendItem {
    Q_OBJECT

public:
    SessionItem(QWidget* owner,
                const QString& sessionId,
                const QIcon& photo,
                const QString& nickname,
                const QString& lastMessage);

    // 重写实际上的点击触发业务逻辑
    void active() override;

private:
    QString _sessionId; // 当前会话的id
};


#endif // SESSIONITEM_H

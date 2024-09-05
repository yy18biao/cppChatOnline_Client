#ifndef FRIENDAPPLYITEM_H
#define FRIENDAPPLYITEM_H

#include "SessionFriendItem.h"

// 单个好友申请框类（继承至单个好友或聊天会话父类）
class FriendApplyItem : public SessionFriendItem {
    Q_OBJECT

public:
    FriendApplyItem(QWidget* owner,
                    const QString& sessionId,
                    const QIcon& photo,
                    const QString& nickname);

    // 重写实际上的点击触发业务逻辑
    void active() override;

private:
    QString _userId; // 当前申请人的id
};

#endif // FRIENDAPPLYITEM_H

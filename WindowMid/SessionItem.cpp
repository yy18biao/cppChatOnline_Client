#include "SessionItem.h"

SessionItem::SessionItem(QWidget* owner, const QString& sessionId, const QIcon& photo, const QString& nickname, const QString& lastMessage)
    : SessionFriendItem(owner, photo, nickname, lastMessage),
    _sessionId(sessionId)
{

}

void SessionItem::active()
{
    // TODO 聊天会话点击之后的业务处理逻辑实现
}

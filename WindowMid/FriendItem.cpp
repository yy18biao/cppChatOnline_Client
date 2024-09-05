#include "FriendItem.h"

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

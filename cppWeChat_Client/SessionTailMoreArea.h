#pragma once

#include <QDialog>

/// <summary>
/// 点击右侧聊天会话标题栏上的更多按钮弹出的
/// 当前聊天会话详细信息界面
/// </summary>
class SessionTailMoreArea : public QDialog
{
	Q_OBJECT

private:


public:
	SessionTailMoreArea(QWidget* parent);
};

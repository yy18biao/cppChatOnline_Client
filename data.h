#pragma once

#include <QString>
#include <QIcon>
#include <QUuid>
#include <Qtime>
#include <QFile>
#include <QDebug>
#include <QFileInfo>

// 辅助打印日志的宏定义
static inline QString getFileName(const QString& path) {
	QFileInfo fileInfo(path);
	return fileInfo.fileName();
}

#define TAG QString("[%1:%2]").arg(getFileName(__FILE__), QString::number(__LINE__))
// 使用 .noquote() 设置 qDebug 针对字符串不输出 ""
#define LOG() qDebug().noquote() << TAG

namespace model {
	//////// 工具函数 ////////

	// 使用uuid生成消息id
	static QString makeMessageId() {
		return "M" + QUuid::createUuid().toString().sliced(25, 12);
	}

	// 获取当前秒级时间戳
	static inline int64_t getSecTime() {
		return QDateTime::currentSecsSinceEpoch();
	}

	// 将时间戳转成 2000-01-01 13:00 格式
	static inline QString formatTime(int64_t timestamp) {
		QDateTime dateTime = QDateTime::fromSecsSinceEpoch(static_cast<time_t>(timestamp));
		return dateTime.toString("yyyy-MM-dd HH:mm");
	}

	// 将 QByteArray 的数据转成 QIcon 类型
	static inline QIcon byteArrayToIcon(const QByteArray& byteArray) {
		QPixmap pixmap;
		pixmap.loadFromData(byteArray);
		QIcon icon(pixmap);
		return icon;
	}

	// 从文件中读取二进制数据
	static inline QByteArray loadFileToByteArray(const QString& path) {
		QFile file(path);
		if (!file.open(QFile::ReadOnly)) {
			qDebug() << "文件打开失败";
			return QByteArray();
		}

		QByteArray content = file.readAll();
		file.close();
		return content;
	}

	// 将二进制数据写入文件
	static inline void writeByteArrayToFile(const QString& filename,
		const QByteArray& content) {
		QFile file(filename);
		bool ok = file.open(QFile::WriteOnly);
		if (!ok) {
			qDebug() << "文件写入失败";
			return;
		}

		file.write(content);
		file.flush(); // 刷新
		file.close();
		return;
	}

	//////// 用户信息 ////////
	class UserInfo {
	public:
		QString _userId; // 用户id
		QString _username; // 用户账号
		QString _nickname; // 用户昵称
		QString _phone; // 用户手机号码
		QString _desc; // 个性签名
		QIcon _userPhoto; // 用户头像
	};

	//////// 聊天消息的类型 ////////
	enum MessageType {
		TEXT, // 文本
		IMAGE, // 图片
		FILE, // 文件
		SPEECH // 语音
	};

	//////// 聊天消息 ///////
	class Message {
	public:
		QString _messageId; // 消息id
		QString _chatSessionId; // 该消息属于的会话id
		QString _messageTime; // 消息时间 2000-01-01 13:00
		MessageType _messageType; // 消息类型
		UserInfo _sendUserInfo; // 消息的发送用户
		QByteArray _messageContent; // 正文内容 由于消息类型不同则使用二进制数组
		/*
			如果为文件/图片/语音消息则需要有文件的标识信息
			防止文件过大导致低效，需要再向服务器请求
		*/
		QString _fileId = "";
		QString _fileName = "";

	public:
		//////// 采用工厂模式实现构造 ////////

		// 生成对象总函数
		static Message makeMessage(MessageType messageType,
			const QString& chatSessionId,
			const UserInfo& sendUserInfo,
			const QByteArray& messageContent,
			const QString& extraInfo) {
			// 根据类型调用相对应的函数实现构造
			if (messageType == TEXT) {
				return makeTextMessage(chatSessionId, sendUserInfo, messageContent);
			}
			else if (messageType == SPEECH) {
				return makeSpeechMessage(chatSessionId, sendUserInfo, messageContent);
			}
			else if (messageType == IMAGE) {
				return makeImageMessage(chatSessionId, sendUserInfo, messageContent);
			}
			else if (messageType == FILE) {
				return makeFileMessage(chatSessionId, sendUserInfo, messageContent, extraInfo);
			}

			return Message();
		}

		// 生成一个文本消息
		static Message makeTextMessage(const QString& chatSessionId,
			const UserInfo& sendUserInfo,
			const QByteArray& messageContent) {
			Message message;
			message._messageId = makeMessageId();
			message._chatSessionId = chatSessionId;
			message._sendUserInfo = sendUserInfo;
			message._messageTime = formatTime(getSecTime());
			message._messageType = TEXT;
			message._messageContent = messageContent;
			return message;
		}

		// 生成一个语音消息
		static Message makeSpeechMessage(const QString& chatSessionId,
			const UserInfo& sendUserInfo,
			const QByteArray& messageContent) {
			Message message;
			message._messageId = makeMessageId();
			message._chatSessionId = chatSessionId;
			message._sendUserInfo = sendUserInfo;
			message._messageTime = formatTime(getSecTime());
			message._messageType = SPEECH;
			message._messageContent = messageContent;
			return message;
		}

		// 生成一个图片消息
		static Message makeImageMessage(const QString& chatSessionId,
			const UserInfo& sendUserInfo,
			const QByteArray& messageContent) {
			Message message;
			message._messageId = makeMessageId();
			message._chatSessionId = chatSessionId;
			message._sendUserInfo = sendUserInfo;
			message._messageTime = formatTime(getSecTime());
			message._messageType = IMAGE;
			message._messageContent = messageContent;
			return message;
		}

		// 生成一个文件消息
		static Message makeFileMessage(const QString& chatSessionId,
			const UserInfo& sendUserInfo,
			const QByteArray& messageContent
			, const QString& fileName) {
			Message message;
			message._messageId = makeMessageId();
			message._chatSessionId = chatSessionId;
			message._sendUserInfo = sendUserInfo;
			message._messageTime = formatTime(getSecTime());
			message._messageType = FILE;
			message._messageContent = messageContent;
			message._fileName = fileName;
			return message;
		}

	};

	//////// 聊天会话 ////////
	class ChatSession {
	public:
		QString _chatSessionId; // 会话id
		QString _chatSessionName; // 会话名
		Message _lastMessage; // 会话中的最新消息
		QIcon _sessionPhoto; // 会话的头像
		QString _userId; // 当前会话中的用户
	};

}
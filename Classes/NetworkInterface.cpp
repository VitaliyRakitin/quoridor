#include "NetworkInterface.h"

NetworkMessage::MessageType NetworkMessage::get_type() {
	return type;
}

GameRequestMessage::GameRequestMessage(std::string &from, std::string &to): NetworkMessage(MessageType::MESSAGE_GAME_REQUEST) {
	m_dictionary.put("from", from.c_str());
	m_dictionary.put("to", to.c_str());
}

GameRequestMessage::DictType& GameRequestMessage::getDictionary() {
	return m_dictionary;
}

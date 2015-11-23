#include "NetworkInterface.h"

NetworkMessage::MessageType NetworkMessage::get_type() {
	return type;
}

GameRequestMessage::GameRequestMessage(std::string &in_from, std::string &in_to): NetworkMessage(MessageType::MESSAGE_GAME_REQUEST) {
	from = in_from;
	to = in_to;
	m_dictionary.put("from", from.c_str());
	m_dictionary.put("to", to.c_str());
}

GameRequestMessage::DictType& GameRequestMessage::getDictionary() {
	return m_dictionary;
}

GameRequestMessage::GameRequestMessage(DictType &in_dict): NetworkMessage(MessageType::MESSAGE_GAME_REQUEST) {
	m_dictionary = in_dict;
	to = std::string(m_dictionary.getValue("to")->ANSIRepresentation().cstr());
	from = std::string(m_dictionary.getValue("from")->ANSIRepresentation().cstr());
}

std::string &GameRequestMessage::get_to() {
	return to;
}

std::string &GameRequestMessage::get_from() {
	return from;
}

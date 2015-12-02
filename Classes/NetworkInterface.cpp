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

GameRequestAnswerMessage::GameRequestAnswerMessage(bool in_answer, std::string &in_opponent):
		NetworkMessage(NetworkMessage::MESSAGE_GAME_REQUEST_ANSWER),
		opponent(in_opponent),
		answer(in_answer)
{
	data.put("answer", answer);
	data.put("to", opponent.c_str());
}

GameRequestAnswerMessage::HashType& GameRequestAnswerMessage::getData() {
	return data;
}

GameRequestAnswerMessage::GameRequestAnswerMessage(HashType &in_data):
		NetworkMessage(NetworkMessage::MESSAGE_GAME_REQUEST_ANSWER),
		data(in_data)
{
	answer = ExitGames::Common::ValueObject<bool>(data.getValue("answer")).getDataCopy();
	//this is insane... Needs a FIX
	opponent = std::string(ExitGames::Common::ValueObject<ExitGames::Common::JString>(data.getValue("to")).getDataCopy().ANSIRepresentation().cstr());
}

bool GameRequestAnswerMessage::getAnswer() {
	return answer;
}

std::string& GameRequestAnswerMessage::getOpponent() {
	return opponent;
}

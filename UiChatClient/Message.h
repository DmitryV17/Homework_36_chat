#ifndef MESSAGE_H
#define MESSAGE_H
#pragma once
#include "string"


#endif // MESSAGE_H
//using namespace std;


class Message
{
private:
    const std::string _from; /// От кого отправлено сообщение
    const std::string _to; /// Кому отпралено сообщение
    const std::string _text;/// Текст сообщения

public:
    Message(const std::string& from, const std::string& to, const std::string& text)
        : _from(from), _to(to), _text(text) {}

    const std::string& getFrom() const { return this->_from; }
    const std::string& getTo() const { return this->_to; }
    const std::string& getText() const { return this->_text; }
};

/*
 * DelimitedMessagesStreamParser.hpp
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */
#include <memory>
#include <vector>
#include <list>
#include "helpers.hpp"
#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

template <typename MessageType>
class DelimitedMessagesStreamParser
{
 public:
  typedef std::shared_ptr<const MessageType> PointerToConstValue;

  std::list<PointerToConstValue> parse(const std::string& data){
      std::list<PointerToConstValue> parsedMassages;
      m_buffer.insert(m_buffer.end(),data.begin(), data.end());
      size_t bytesConsumed = 0;
      while (!m_buffer.empty())
      {
        std::shared_ptr<MessageType> parsedMassage = parseDelimited<MessageType>(data, m_buffer.size(), &bytesConsumed);
        if(parsedMassage){
          parsedMassages.push_back(parsedMassage);
          m_buffer.erase(m_buffer.begin(), m_buffer.begin() + bytesConsumed);
        }
        else
          break;
      }
      
    return parsedMassages;
  };

 private:
  std::vector<char> m_buffer;
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */

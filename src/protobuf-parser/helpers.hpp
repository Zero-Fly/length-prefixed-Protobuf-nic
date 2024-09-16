/*
 * helpers.h
 *
 *  Created on: 2 Feb 2023
 *      Author: sia
 */

#include <memory>
#include <vector>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#ifndef SRC_PROTOBUF_PARSER_HELPERS_H_
#define SRC_PROTOBUF_PARSER_HELPERS_H_

#if GOOGLE_PROTOBUF_VERSION >= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif
typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;

template <typename Message> PointerToConstData serializeDelimited(const Message& msg) { 
    
    return nullptr; 
    }

/*!
 * \brief Расшифровывает сообщение, предваренное длиной из массива байтов.
 *
 * \tparam Message Тип сообщения, для работы с которым предназначена данная
 * функция.
 *
 * \param data Указатель на буфер данных.
 * \param size Размер буфера данных.
 * \param bytesConsumed Количество байт, которое потребовалось для расшифровки
 * сообщения в случае успеха.
 *
 * \return Умный указатель на сообщение. Если удалось расшифровать сообщение, то
 * он не пустой.
 */
template <typename Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0)
{
    google::protobuf::io::ArrayInputStream arrayInputStream(data, size);
    google::protobuf::io::CodedInputStream codedInputStream(&arrayInputStream);
    
    uint32_t messageSize;
    if (!codedInputStream.ReadVarint32(&messageSize)) {
        return nullptr;
    }
    
    auto limit = codedInputStream.PushLimit(messageSize);
    Message message;
    if(!message.ParseFromCodedStream(&codedInputStream)){
        return nullptr;
    }

    codedInputStream.PopLimit(limit);
    *bytesConsumed = codedInputStream.CurrentPosition();
    
    return std::make_shared<Message>(message);
}






#endif /* SRC_PROTOBUF_PARSER_HELPERS_H_ */

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Buffer Buffer;

/// \brief Создаёт буфер в динамической памяти.
///
/// \param[in] capacity Размер буфера
///
/// \return Дескриптор буфера (NULL в случае неудачи)
///
Buffer* Buffer_Create(size_t capacity);

/// \brief Удаляет буфер из динамической памяти.
///
/// \param[in] buffer Дескриптор буфера
///
void Buffer_Destroy(Buffer* buffer);

/// \brief Пытается добавить элемент в буфер.
///        Если это сделать не удаётся,
///        вставляет элемент на место последнего добавленного
///        и возвращает старый элемент.
///
/// \param[in] buffer  Дескриптор буфера
/// \param[in] element Вставляемый элемент
///
/// \return Последний добавленный ранее элемент в случае, если буфер полон,
///         NULL в противном случае
///
void* Buffer_Add(Buffer* buffer, void* element);

/// \brief Пытается удалить элемент из буфера.
///
/// \param[in] buffer Дескриптор буфера
///
/// \return Удалённый элемент (NULL в случае, если буфер пустой)
///
void* Buffer_Poll(Buffer* buffer);

/// \brief Проверяет, является ли буфер пустым.
///
/// \param[in] buffer Дескриптор буфера
///
/// \return true, если буфер пустой, false в противном случае
///
bool Buffer_IsEmpty(const Buffer* buffer);

/// \brief Возвращает количество элементов в буфере.
///
/// \param[in] buffer Дескриптор буфера
///
/// \return Количество элементов в буфере
///
bool Buffer_Size(const Buffer* buffer);

#endif

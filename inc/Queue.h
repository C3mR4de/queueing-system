#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Queue Queue;

/// \brief Создаёт очередь с приоритетом в динамической памяти.
///
/// \param[in] capacity Размер очереди с приоритетом
///
/// \return Дескриптор очереди с приоритетом (NULL в случае неудачи)
///
Queue* Queue_Create(size_t capacity);

/// \brief Удаляет очередь с приоритетом из динамической памяти.
///
/// \param[in] buffer Дескриптор очереди с приоритетом
///
void Queue_Destroy(Queue* queue);

/// \brief Пытается добавить элемент в очередь с приоритетом.
///
/// \param[in] buffer  Дескриптор очереди с приоритетом
/// \param[in] element Добавляемый элемент
///
/// \return true, если удалось добавить элемент, false в противном случае
///
bool Queue_Enqueue(Queue* queue, void* element);

/// \brief Пытается удалить элемент из очереди с приоритетом.
///
/// \param[in] buffer  Дескриптор очереди с приоритетом
/// \param[in] element Добавляемый элемент
///
/// \return Удалённый элемент (NULL в случае, если очередь пустая)
///
void* Queue_Dequeue(Queue* queue);

/// \brief Проверяет, является ли очередь с приоритетом пустой.
///
/// \param[in] buffer Дескриптор очереди с приоритетом
///
/// \return true, если очередь с приоритетом пустая, false в противном случае
///
bool Queue_IsEmpty(const Queue* queue);

/// \brief Возвращает количество элементов в очереди с приоритетом.
///
/// \param[in] buffer Дескриптор очереди с приоритетом
///
/// \return Количество элементов в очереди с приоритетом
///
size_t Queue_Size(const Queue* queue);

#endif

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>
#include "CommonTypedefs.h"

typedef struct PriorityQueue PriorityQueue;

/// \brief Создаёт очередь с приоритетом в динамической памяти.
///
/// \param[in] capacity   Размер очереди с приоритетом
/// \param[in] comparator Функция-компаратор, определяющая более приоритетный элемент
///
/// \return Дескриптор очереди с приоритетом (NULL в случае неудачи)
///
PriorityQueue* PriorityQueue_Create(size_t capacity, Comparator comparator);

/// \brief Удаляет очередь с приоритетом из динамической памяти.
///
/// \param[in] buffer Дескриптор очереди с приоритетом
///
void PriorityQueue_Destroy(PriorityQueue* queue);

/// \brief Пытается добавить элемент в очередь с приоритетом.
///
/// \param[in] buffer  Дескриптор очереди с приоритетом
/// \param[in] element Добавляемый элемент
///
/// \return true, если удалось добавить элемент, false в противном случае
///
bool PriorityQueue_Enqueue(PriorityQueue* queue, void* element);

/// \brief Пытается удалить элемент из очереди с приоритетом.
///
/// \param[in] buffer  Дескриптор очереди с приоритетом
/// \param[in] element Добавляемый элемент
///
/// \return Удалённый элемент (NULL в случае, если очередь пустая)
///
void* PriorityQueue_Dequeue(PriorityQueue* queue);

/// \brief Проверяет, является ли очередь с приоритетом пустой.
///
/// \param[in] buffer Дескриптор очереди с приоритетом
///
/// \return true, если очередь с приоритетом пустая, false в противном случае
///
bool PriorityQueue_IsEmpty(const PriorityQueue* queue);

/// \brief Возвращает количество элементов в очереди с приоритетом.
///
/// \param[in] buffer Дескриптор очереди с приоритетом
///
/// \return Количество элементов в очереди с приоритетом
///
size_t PriorityQueue_Size(const PriorityQueue* queue);

#endif

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Vector Vector;

/// \brief Создаёт вектор в динамической памяти.
///
/// \param[in] size Размер вектора
///
/// \return Дескриптор вектора (NULL в случае неудачи)
///
Vector* Vector_Create(size_t size);

/// \brief Удаляет вектор из динамической памяти.
///
/// \param[in] vector Дескриптор вектора
///
void Vector_Destroy(Vector* const vector);

/// \brief Возвращает элемент из вектора.
///
/// \param[in] vector Дескриптор вектора
/// \param[in] index  Индекс элемента
///
/// \return Возвращаемый элемент
///
void* Vector_Get(const Vector* vector, size_t index);

/// \brief Задаёт элемент в векторе.
///
/// \param[in] vector  Дескриптор вектора
/// \param[in] element Добавляемый элемент
///
/// \return true, если удалось добавить элемент, false в противном случае
///
bool Vector_Set(Vector* vector, size_t index, void* element);

/// \brief Возвращает количество элементов в векторе.
///
/// \param[in] vector Дескриптор вектора
///
/// \return Количество элементов в векторе
///
size_t Vector_Size(const Vector* vector);

#endif

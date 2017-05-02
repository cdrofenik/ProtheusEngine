#ifndef ALIGNED_ARRAY_H
#define ALIGNED_ARRAY_H

//system directory
#include <malloc.h>

namespace collections {
	
	template<typename T>
	class AlignedArray
	{
		//TODO: add allocator for alignment

	protected:
		int m_size;
		int m_capacity;
		T* m_data;

	protected:
		int getAllocationSize(const int& size) const
		{
			return (size ? size * 2 : 1);
		}

		void copy(const int& start, const int& end, T* destination) const
		{
			int i;
			for (i = start; i < end; ++i)
			{
				destination[i] = T(m_data[i]);
			}

		}

		void destroy(const int& first, const int& last)
		{
			for (int i = first; i < last; i++)
			{
				m_data[i].~T();
			}
		}

		void* allocate(const int& size)
		{
			if (size)
				return malloc(size);
			return 0;
		}

		void deallocate()
		{
			m_data = 0;
		}

		void init()
		{
			m_size = 0;
			m_capacity = 0;
			m_data = 0;
		}

	public:
		AlignedArray()
		{
			init();
		}

		AlignedArray(const int& size)
		{
			init();
			reserve(size);
		}

		//TODO: Copy constructor

		~AlignedArray()
		{
			clear();
		}

		int size() const
		{
			return m_size;
		}

		int capacity() const
		{
			return m_capacity;
		}

		const T operator[](int index) const
		{
			//Assert if index >= 0
			//Asert if index < size
			return m_data[index];

		}

		T& operator[](const int& index)
		{
			//Assert if index >= 0
			//Asert if index < size
			return m_data[index];
		}

		const T at(const int& index) const
		{
			//Assert if index >= 0
			//Asert if index < size
			m_data[index];
		}

		T& at(const int& index)
		{
			//Assert if index >= 0
			//Asert if index < size
			return m_data[index];
		}

		void reserve(const int& newSize)
		{
			if (capacity() < newSize)
			{
				int memorySize = newSize * sizeof(T);
				T* source = (T*)allocate(memorySize);
				copy(0, size(), source);
				destroy(0, size());
				deallocate();

				m_data = source;
				m_capacity = newSize;
			}
		}

		void push_back(const T& value)
		{
			const int sz = size();
			if (sz == capacity())
			{
				reserve(getAllocationSize(size()));
			}

			m_data[m_size] = T(value);
			m_size++;
		}

		void pop_back()
		{
			//Assert if size >= 0
			m_size--;
			m_data[m_size].~T();
		}

		void swap(const int& index0, const int& index1)
		{
			T tmp = m_data[index0];
			m_data[index0] = m_data[index1];
			m_data[index1] = tmp;
		}

		void removeAt(const int& index)
		{
			if (index < size())
			{
				swap(index, size() - 1);
				pop_back();
			}
		}

		void clear()
		{
			destroy(0, size());
			deallocate();
			init();
		}

		void bubbleSort(bool(*compareFunc)(T, T))
		{
			int sz = size();
			for (int i = 0; i < sz; i++)
			{
				for (int j = 0; j < sz; j++)
				{
					if (compareFunc(m_data[i], m_data[j]))
						swap(i, j);
				}
			}
		}
	};
}

#endif
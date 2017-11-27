#ifndef _CLIST_H
#define _CLIST_H

#ifndef INLINE
#include "../ExternalDefines.h"
#ifdef __LINUX__
#define INLINE inline
#else
#define INLINE __forceinline
#endif
#endif

// BASED ON ID SOFTWARE LIST CONTAINER

template<class T>
class List
{
private:
	T*						containerList;
	// Tyle miejsc alokuje na tablicy, jesli ilosc aktualnych elementow sie zblizy do tej liczby
	unsigned int			granularity; 
	//
	unsigned int			num;
	unsigned int			size;
public:
	// Constructors
							List(unsigned int _granularity = 16);
							~List();

	List<T> &				operator=( const List<T> &other );

	void					DeleteContentsAndClear(void); // Only for pointers
	int						PushBack( const T & obj );
	int						Insert( const T & obj, int index = 0 );
	INLINE void				PopBack(void){num = num - 1;};
	void					Clear(void);
	void					Resize(unsigned int newSize);
	bool					Remove(T const & obj);
	void					RemoveIndex(unsigned int index);
	// Returns the index of the object in list
	// Returns -1 if not found
	int						FindIndex( T const & obj );

	// Returns the amount of elements in the list
	INLINE unsigned int		Num( void ) const { return num ;};
	INLINE T&				operator[]( int index ) { return containerList[index]; };
	INLINE T&				GetElementByIndex( int index ) { return containerList[index]; };
	// Returns last element from the list
	INLINE T&				Back()
	{
		if(num > 0)
			return containerList[num-1];
	}
};

template< class T >
INLINE List<T>::List(unsigned int _granularity) {
	containerList		= 0;
	granularity			= _granularity;
	Clear();
};

template< class T >
INLINE List<T>::~List() {
	Clear();
};

// Works only for pointers
template< class T >
INLINE void List<T>::DeleteContentsAndClear( void ) {
	for(unsigned int i = 0; i < num; ++i ){
		delete containerList[i];
		containerList[i] = 0;
	}

	Clear();
};

template< class T >
INLINE void List<T>::Clear( void ) {
	if ( containerList ) delete[] containerList;

	containerList	= 0;
	num				= 0;
	size			= 0;
};

template< class T >
INLINE void List<T>::Resize(unsigned int newSize) {
	T*					temp;
	unsigned int		i;

	if(newSize == size) return;

	if(newSize <= 0){
		Clear();
		return;
	}

	temp	= containerList;
	size	= newSize;
	if(size < num) num = size;

	containerList = new T[size];
	for( i = 0; i < num; ++i )
		containerList[ i ] = temp[ i ];

	if(temp) delete[] temp;
};

template< class T >
INLINE bool List<T>::Remove(T const & obj) {
	int foundIndex = FindIndex(obj);
	if(foundIndex >= 0){
		RemoveIndex((unsigned int)foundIndex);
		return true;
	}
	return false;
};

template< class T >
INLINE void List<T>::RemoveIndex(unsigned int index) {
	if ( ( index < 0 ) || ( index >= num ) ) {
		return;
	}

	num--;
	for(unsigned int i = index; i < num; ++i )
		containerList[i] = containerList[i+1];
};

template< class T >
INLINE int List<T>::FindIndex(T const & obj) {
	for(unsigned int i = 0; i < num; ++i ){
		if(containerList[i] == obj) return i;
	}

	// Object not found
	return -1;
};


template< class T >
INLINE int List<T>::PushBack( T const & obj ) {
	if ( !containerList ) {
		Resize( granularity );
	}

	if ( num == size ) {
		int newsize;

		/*if ( granularity == 0 ) {
			granularity = 16;
		}*/
		newsize = size + granularity;
		Resize( newsize - newsize % granularity );
	}

	containerList[ num ] = obj;
	num++;

	return num - 1;
};

template< class T >
INLINE int List<T>::Insert(T const & obj, int index) 
{
	if ( !containerList ) {
		Resize( granularity );
	}

	if ( num == size ) {
		int newsize;

		/*if ( granularity == 0 ) {	
			granularity = 16;
		}*/
		newsize = size + granularity;
		Resize( newsize - newsize % granularity );
	}

	if ( index < 0 ) {
		index = 0;
	}
	else if ( index > num ) {
		index = num;
	}
	for ( int i = num; i > index; --i ) {
		containerList[i] = containerList[i-1];
	}

	num++;
	containerList[index] = obj;
	return index;
}

template< class T >
INLINE List<T> &List<T>::operator=( const List<T> &other ) {
	Clear();

	num			= other.num;
	size		= other.size;
	granularity	= other.granularity;

	if ( size ) {
		containerList = new T[ size ];
		for(unsigned int i = 0; i < num; ++i ) {
			containerList[ i ] = other.containerList[ i ];
		}
	}

	return *this;
}

#endif
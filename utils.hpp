#include <cstddef> // std::ptrdiff_t

// important about typedefs : https://stackoverflow.com/questions/34975536/are-public-in-class-typedefs-necessary-in-c1y?rq=1

namespace ft {

	template < class Iter >
		struct iterator_traits {

			using difference_type	Iter::difference_type;
			using value_type		Iter::value_type;
			// important about typedefs : https://stackoverflow.com/questions/34975536/are-public-in-class-typedefs-necessary-in-c1y?rq=1
			using pointer			Iter::pointer;
			using reference			Iter::reference;
			using iterator_category	Iter::iterator_category;
		};

	template < class T >
		struct iterator_traits< T* > {

			using difference_type	std::ptrdiff_t;
			using value_type		T;
			using pointer			T*;
			using reference			T&;
			using iterator_category	ft::random_access_iterator_tag;
		};

	template < class T >
		struct iterator_traits< const T* > {

			using difference_type	std::ptrdiff_t;
			using value_type		T;
			using pointer			const T*;
			using reference			const T&;
			using iterator_category	ft::random_access_iterator_tag;
		};

	// Illl have to work on the random acces iterator before even creating this XD.
}


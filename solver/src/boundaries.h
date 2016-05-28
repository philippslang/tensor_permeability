#ifndef BOUNDARIES_H
#define BOUNDARIES_H


#include <utility>
#include <vector>

namespace csmp {
	template<size_t> class Node;

	namespace tperm {


		/// A minimal Boundary class for this application
		class Boundary
		{
		public:
			Boundary();
			
			/// Number of nodes
			size_t size() const { return nodes_.size(); }

			/// This is a direct no-check accessor
			Node<3>* operator[](size_t i) const { return nodes_[i]; }	

			template <typename InputIterator>
			void assign(InputIterator first, InputIterator last) {
				nodes_.assign(first, last);
			}

		private:
			std::vector<csmp::Node<3>*> nodes_;
		};


		/// A collection of opposing Boundary pairs
		class Boundaries
		{
		public:
			typedef std::pair<Boundary, Boundary> OpposingBoundaries;

			Boundaries();
			explicit Boundaries(size_t);

			/// Number of OpposingBoundaries
			size_t size() const { return boundaries_.size(); }

			/// This is a check-bounds accessor
			OpposingBoundaries& operator[](size_t i) { return boundaries_.at(i); }
			const OpposingBoundaries& operator[](size_t i) const { return boundaries_.at(i); }

		private:
			std::vector<OpposingBoundaries> boundaries_;
		};


		/** \class Boundary

		At its most abstract implementation, a Boundary for the pressure solution problem is a collcection
		of nodes. It thus can either be an external or internal boundary of the Model.
		*/

	} // !tperm
} // !csmp


#endif
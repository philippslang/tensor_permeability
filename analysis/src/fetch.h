/** @file */
#ifndef FETCH_H
#define FETCH_H


namespace csmp {
	template<size_t> class Model;

	namespace tperm {
		class FlowResults;

		/// Returns sorted Boundaries of the Model
		FlowResults fetch(const char*, const csmp::Model<3>&);

		
	} // !tperm
} // !csmp

#endif // !FETCH_H
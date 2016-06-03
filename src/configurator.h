#ifndef TP_CONFIG_H
#define TP_CONFIG_H


namespace csmp {
	// forwards
	template<size_t> class Model;


	namespace tperm {

		/// ABC for model configuration, changes the state of a csmp::Model
		class Configurator 
		{
		public:
			typedef csmp::Model<3> Model;

			Configurator();
			virtual ~Configurator();

			virtual bool configure(Model&) const = 0;
		};

		/** \class Configurator

		Configurators should check correctness of settings in ctor and throw.
		*/
	} // !tperm
} // !csmp

#endif // !TP_CONFIG_H
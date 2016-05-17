#ifndef TP_CONFIG_H
#define TP_CONFIG_H


namespace csmp {
	// forwards
	template<size_t> class Model;


	namespace tperm {

		/// ABC for model configuration. Changes the state of a csmp::Model.
		class Configurator 
		{
		public:
			typedef csmp::Model<3> Model;

			Configurator(Model&);
			virtual ~Configurator();

			virtual bool configure() const = 0;

		protected:
			Model& model() const {return model_;}

		private:
			Model& model_;
		};

	} // !tperm
} // !csmp

#endif // !TP_CONFIG_H
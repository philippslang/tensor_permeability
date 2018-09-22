#ifndef TP_NULLCONFIG_H
#define TP_NULLCONFIG_H

#include "configurator.h"

namespace csmp {

namespace tperm {

    /// Dummy model configurator
    class NullConfigurator : public Configurator {
    public:
        NullConfigurator();
        virtual ~NullConfigurator();

        virtual bool configure(Model&) const override;
    };

    /** \class NullConfigurator

		Default Configurator if, for example, no settings are provided.
		*/

} // !tperm
} // !csmp

#endif // !TP_NULLCONFIG_H
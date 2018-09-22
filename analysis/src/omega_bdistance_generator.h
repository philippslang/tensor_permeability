#ifndef TP_OMEGA_BD_GENERATOR_H
#define TP_OMEGA_BD_GENERATOR_H

#include "omega_generator.h"

namespace csmp {

namespace tperm {

    /// ABC for omega generators
    class OmegaBDistanceGenerator : public OmegaGenerator {
    public:
        /// All elements
        OmegaBDistanceGenerator();
        /// Minimum distance
        explicit OmegaBDistanceGenerator(double);
        virtual ~OmegaBDistanceGenerator();

        virtual OmegaPtrColl generate(const csmp::Model<3>&) const override;

    private:
        /// Assumes box shape
        double sampling_box_total_volume(const csmp::Model<3>&) const;

        const double dist_;
    };

    /** \class OmegaBDistanceGenerator

		Generates a single Omega using a boundary minumum distance critertion.
		*/

} // !tperm
} // !csmp

#endif // !TP_OMEGA_BD_GENERATOR_H
#ifndef TP_OMEGA_CP_GENERATOR_H
#define TP_OMEGA_CP_GENERATOR_H

#include "omega_generator.h"

#include "Point.h"

#include <array>
#include <vector>

namespace csmp {

namespace tperm {

    /// ABC for omega generators
    class OmegaCornerPointsGenerator : public OmegaGenerator {
    public:
        OmegaCornerPointsGenerator() = delete;
        /// Minimum distance
        explicit OmegaCornerPointsGenerator(const std::vector<std::array<csmp::Point<3>, 2>>&);
        virtual ~OmegaCornerPointsGenerator();

        virtual OmegaPtrColl generate(const csmp::Model<3>&) const override;

    private:
        // False if strictly greated or strictly less than bounds
        bool within_bounds(const csmp::Point<3>& pt, const std::array<csmp::Point<3>, 2>& minmax) const
        {
            for (size_t xyz(0); xyz < 3; ++xyz)
                if (pt[xyz] < minmax[0][xyz] || pt[xyz] > minmax[1][xyz])
                    return false; // not within min-max bounds
            return true;
        }

        const std::vector<std::array<csmp::Point<3>, 2>> cpts_;
    };

    /** \class OmegaBDistanceGenerator

		Generates arbtrary number of Omegas using a bounding box corner point criterion.
		*/

} // !tperm
} // !csmp

#endif // !TP_OMEGA_CP_GENERATOR_H
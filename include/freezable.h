#ifndef MODEL_FREEZABLE_H
#define MODEL_FREEZABLE_H

#include "randomdist.h"

namespace model
{
    class Freezable
    {
    public:

        /// @brief constructor
        /// with default values for range

        inline Freezable() :
                         m_floatdist(0.0, 1.0) {;}

        /// @brief extract random number within the distribution range
        /// and compare with the given one
        ///
        /// Its purpose is to check whether or not a cell of the mesh
        /// has to freeze
        /// @param[in] _probability value to be compared
        /// @param[out] true if _probability > extracted number

        inline bool isFreezable(const PROBABILITY _probability)
        {
            return _probability > m_floatdist.get_distr();
        }

        /// @brief destructor
        inline ~Freezable() {;}

    private:
        common::FloatDistribution m_floatdist;
    };
}

#endif //MODEL_FREEZABLE_H

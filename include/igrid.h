#ifndef MODEL_IGRID_H
#define MODEL_IGRID_H

#include <cstdarg>
#include <vector>
#include <memory>

namespace model
{
    template <typename T, std::size_t N>
    class IGrid
    {
        public:
            virtual void set(const std::array<std::size_t, N>& coordinates, T element) = 0;

            virtual T get(const std::array<std::size_t, N>& coordinates) const = 0;
    };
}

#endif // MODEL_IGRID_H

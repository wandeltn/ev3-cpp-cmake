#ifndef __MOVEMENT_PARSER_HPP__
#define __MOVEMENT_PARSER_HPP__

#include <vector>

#include <math/Vector2.hpp>
#include <math/Line.hpp>
#include <utility/RobotMovement/RobotMovement.hpp>
#include <engines/location/LocationEngine.hpp>

namespace finder::engines::movement
{
    class MovementParser {
        public:
            MovementParser();
            ~MovementParser();

            void parse(std::vector<math::Vector2> path);
            void parse(math::Vector2 destination);

        private:
            robot::RobotMovement _robotMovement;
    };
} // namespace finder::engines::movement

#endif // __MOVEMENT_PARSER_HPP__
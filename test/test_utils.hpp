#ifndef __testutils__
#define __testutils__

#include <glm/glm.hpp>

namespace test_utils
{
    inline bool is_scaling_matrix(const glm::mat4 &matrix)
    {

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i != j && matrix[i][j] != 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
} // namespace test_utils

#endif
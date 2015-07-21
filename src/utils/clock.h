#ifndef LOGGER_CLOCK_H
#define LOGGER_CLOCK_H

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright © 2015
 * Quality and Usability Lab
 * Berlin Institute of Technology
 * http://www.qu.tu-berlin.de
 *
 * For more detailed information, please read the license.txt in the root directory.
 */

#include <string>

namespace SSR
{

    /**
     * Computes the current time and returns it formatted as follows:
     *
     * YYYY-MM-DD HH:mm:SS
     *
     * @return the current time.
     *
     * @author Florian Willich
     * @since 2015-06-30
     */
    std::string compute_current_time();

}


#endif //LOGGER_CLOCK_H

#ifndef LOGGER_CLOCK_H
#define LOGGER_CLOCK_H

#include <string>

namespace SSR {

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

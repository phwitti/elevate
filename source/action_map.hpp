#ifndef __PW_ACTION_MAP_HPP__
#define __PW_ACTION_MAP_HPP__

#include <functional>
#include <map>
#include <vector>

namespace pw
{
    template<typename T>
    class action_map : public std::map<T, std::function<void(void)>>
    {

    public:
        
        bool execute(const T &_key) const;
        bool execute_first(const std::vector<T> &_keys) const;
        bool execute_all(const std::vector<T> &_keys) const;

    };
}

//

#include "action_map.tlh"

//

#endif

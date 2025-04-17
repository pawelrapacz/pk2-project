#pragma once

#include <type_traits>

namespace graph_traits
{
    template<typename Tp>
    using is_not_void = std::negation<std::is_void<Tp>>;

    template<typename Tp>
    inline constexpr bool is_not_void_v = is_not_void<Tp>::value;

    template<typename CondTp, typename Tp = void>
    using enable_if_not_void = std::enable_if<is_not_void_v<CondTp>, Tp>;

    template<typename CondTp, typename Tp = void>
    using enable_if_not_void_t = typename enable_if_not_void<CondTp, Tp>::type;
    
} // namespace graph_traits
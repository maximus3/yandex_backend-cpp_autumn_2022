#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

namespace url_shortener {

void AppendRedirectToLong(userver::components::ComponentList& component_list);

}  // namespace url_shortener

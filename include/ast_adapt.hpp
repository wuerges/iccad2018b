#pragma once

#include <ast.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(ast::Point, x, y);
BOOST_FUSION_ADAPT_STRUCT(ast::Rectangle, p1, p2);
BOOST_FUSION_ADAPT_STRUCT(ast::RoutedShape, layer, rect);


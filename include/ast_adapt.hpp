#pragma once

#include <ast.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(ast::Point, x, y);
BOOST_FUSION_ADAPT_STRUCT(ast::Layer, name, points);
BOOST_FUSION_ADAPT_STRUCT(ast::Path, size, layers);
BOOST_FUSION_ADAPT_STRUCT(ast::Bit, width, path);
BOOST_FUSION_ADAPT_STRUCT(ast::Bus, name, bits);


#pragma once

#include <ast.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(ast::Point, x, y);
BOOST_FUSION_ADAPT_STRUCT(ast::Rectangle, p1, p2);
BOOST_FUSION_ADAPT_STRUCT(ast::RoutedShape, layer, rect);
BOOST_FUSION_ADAPT_STRUCT(ast::Bit, name, shapes);
BOOST_FUSION_ADAPT_STRUCT(ast::Width, constraints);
BOOST_FUSION_ADAPT_STRUCT(ast::Bus, name, width, bits);
BOOST_FUSION_ADAPT_STRUCT(ast::Layer, name, horizontal, spacing);
BOOST_FUSION_ADAPT_STRUCT(ast::Track, line, width);
BOOST_FUSION_ADAPT_STRUCT(ast::Parameters, runtime, alpha, beta, gamma, delta, epsilon);


#pragma once

#include <ast.hpp>

#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>

#include <vector>

using std::vector;

struct Draw {
    Cairo::RefPtr<Cairo::Context> cairo;

    Draw(Cairo::RefPtr<Cairo::Context> cr):cairo(cr) {}

    void routedShape(const ast::RoutedShape& rs) {
        cairo->rectangle(rs.rect.p1.x, rs.rect.p1.y, (rs.rect.p2.x-rs.rect.p1.x), (rs.rect.p2.y-rs.rect.p1.y));
        cairo->fill();
    }

    void track(const ast::Track& tk) {
        vector<double> dashes = {
            10.0,  /* ink */
            10.0  /* skip */
        };
        cairo->set_line_width(1);
        cairo->set_dash(dashes, 0);
        if (tk.line.rect.p1.x==tk.line.rect.p2.x) {
            cairo->set_source_rgb(0, 255, 255);
            cairo->move_to(tk.line.rect.p1.x,tk.line.rect.p1.y);
            cairo->line_to(tk.line.rect.p2.x,tk.line.rect.p2.y);
            cairo->stroke();
            cairo->set_source_rgba(255, 0, 0, 0.3);
            cairo->rectangle(tk.line.rect.p1.x-tk.width/2,tk.line.rect.p1.y,tk.width,tk.line.rect.p2.y-tk.line.rect.p1.y);
        }
        else {
            cairo->set_source_rgb(255, 105, 180);
            cairo->move_to(tk.line.rect.p1.x,tk.line.rect.p1.y);
            cairo->line_to(tk.line.rect.p2.x,tk.line.rect.p2.y);
            cairo->stroke();
            cairo->move_to(0,0);
            cairo->set_source_rgba(255, 0, 0, 0.3);
            cairo->rectangle(tk.line.rect.p1.x,tk.line.rect.p1.y-tk.width/2,tk.line.rect.p2.x-tk.line.rect.p1.x,tk.width);
        }
        cairo->fill();
    }
};
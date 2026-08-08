#!/usr/bin/env python3
"""Render MEMU_PERF_TRACE CSV as an SVG using only the standard library."""

import argparse
import csv


WIDTH, HEIGHT = 1000, 700
LEFT, RIGHT = 80, 30
PLOT_WIDTH = WIDTH - LEFT - RIGHT
COLORS = ("#2563eb", "#16a34a", "#dc2626", "#9333ea")


def panel(rows, fields, top, height, title):
    max_cycle = max(int(row["cycle"]) for row in rows)
    max_value = max(1, *(int(row[field]) for row in rows for _, field in fields))
    bottom = top + height
    parts = [
        f'<text x="{LEFT}" y="{top - 12}" font-size="16">{title}</text>',
        f'<line x1="{LEFT}" y1="{top}" x2="{LEFT}" y2="{bottom}" stroke="black"/>',
        f'<line x1="{LEFT}" y1="{bottom}" x2="{WIDTH-RIGHT}" y2="{bottom}" stroke="black"/>',
        f'<text x="8" y="{top + 12}" font-size="12">{max_value}</text>',
        f'<text x="45" y="{bottom}" font-size="12">0</text>',
    ]
    for index, (label, field) in enumerate(fields):
        points = []
        for row in rows:
            x = LEFT + int(row["cycle"]) * PLOT_WIDTH / max_cycle
            y = bottom - int(row[field]) * height / max_value
            points.append(f"{x:.2f},{y:.2f}")
        color = COLORS[index]
        parts.append(
            f'<polyline fill="none" stroke="{color}" stroke-width="1.5" '
            f'points="{" ".join(points)}"/>'
        )
        legend_x = LEFT + index * 190
        parts.append(
            f'<line x1="{legend_x}" y1="{bottom+25}" x2="{legend_x+25}" '
            f'y2="{bottom+25}" stroke="{color}" stroke-width="3"/>'
            f'<text x="{legend_x+30}" y="{bottom+29}" font-size="12">{label}</text>'
        )
    return parts


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("trace", help="CSV produced through MEMU_PERF_TRACE")
    parser.add_argument("-o", "--output", default="perf-trace.svg")
    args = parser.parse_args()

    with open(args.trace, newline="", encoding="utf-8") as source:
        rows = list(csv.DictReader(source))
    if not rows:
        raise SystemExit("empty performance trace")

    svg = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{HEIGHT}" '
        f'viewBox="0 0 {WIDTH} {HEIGHT}">',
        '<rect width="100%" height="100%" fill="white"/>',
    ]
    svg += panel(rows, (
        ("instructions", "inst_accept"),
        ("IFU response", "ifu_resp"),
        ("EXU finish", "exu_finish"),
        ("LSU response", "lsu_resp"),
    ), 55, 230, "Cumulative performance events")
    svg += panel(rows, (
        ("IFU wait", "ifu_wait_resp_cycles"),
        ("backend blocked", "ifu_backend_cycles"),
        ("request stalled", "ifu_req_stall_cycles"),
        ("LSU wait", "lsu_wait_resp_cycles"),
    ), 390, 230, "Cumulative stall cycles")
    svg += [
        f'<text x="{WIDTH/2}" y="{HEIGHT-12}" text-anchor="middle" font-size="13">cycle</text>',
        '</svg>',
    ]
    with open(args.output, "w", encoding="utf-8") as output:
        output.write("\n".join(svg))


if __name__ == "__main__":
    main()

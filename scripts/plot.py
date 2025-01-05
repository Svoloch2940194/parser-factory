#!/usr/bin/env python3

import sys
import json
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from collections import defaultdict

def main():
    try:
        input_data = sys.stdin.read()
        data = json.loads(input_data)

        points = data.get("points", [])
        if not points:
            raise ValueError("There are no points to display.")

        data_dict = defaultdict(lambda: defaultdict(list))
        for point in points:
            file = point["file"]
            group = point["group"]
            x = point["x"]
            y = point["y"]
            data_dict[file][group].append((x, y))

        plt.figure(figsize=(10, 8))
        color_map = plt.get_cmap('tab20')
        color_idx = 0
        legend_handles = []

        for file, groups in data_dict.items():
            for group, coords in groups.items():
                xs, ys = zip(*coords)
                color = color_map(color_idx % 20)
                plt.scatter(xs, ys, color=color, label=f"{file} - Group {group}")
                legend_handles.append(mpatches.Patch(color=color, label=f"{file} - Group {group}"))
                color_idx += 1

        plt.legend(handles=legend_handles, bbox_to_anchor=(1.05, 1), loc='upper left')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.title('Точки из файлов')
        plt.tight_layout()
        plt.savefig('output.png')
        print("The graph was successfully saved to output.png")
    except Exception as e:
        print(f"Error in Python script: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()

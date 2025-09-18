from queue import PriorityQueue

# Heuristic: Manhattan Distance
def heuristic(pos1, pos2):
    return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1])

def a_star_search(grid, start, goal):
    rows, cols = len(grid), len(grid[0])

    frontier = PriorityQueue()
    frontier.put((0, start))

    came_from = {}
    g_score = {start: 0}

    while not frontier.empty():
        _, current = frontier.get()

        if current == goal:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            path.reverse()
            return path

        r, c = current
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            neighbor = (r + dr, c + dc)

            if (
                0 <= neighbor[0] < rows and
                0 <= neighbor[1] < cols and
                grid[neighbor[0]][neighbor[1]] == 0
            ):
                new_g = g_score[current] + 1

                if neighbor not in g_score or new_g < g_score[neighbor]:
                    g_score[neighbor] = new_g
                    f_score = new_g + heuristic(neighbor, goal)
                    frontier.put((f_score, neighbor))
                    came_from[neighbor] = current

    return None  # No valid path found

# Sample Grid: 0 = walkable, 1 = blocked
grid = [
    [0, 1, 0, 0],
    [0, 1, 0, 1],
    [0, 0, 0, 0],
    [1, 1, 0, 0]
]

start = (0, 2)
end = (3, 3)

path = a_star_search(grid, start, end)
print("A* Path:", path)

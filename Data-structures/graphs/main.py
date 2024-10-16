from collections import defaultdict, deque

class Solution:
    def findBuildOrder(self, projects, dependencies):
        # Build the adjacency list and in-degree count
        adj_list = defaultdict(list)
        in_degree = {project: 0 for project in projects}
        
        # Fill the adjacency list and in-degree map
        for dep in dependencies:
            first, second = dep
            adj_list[first].append(second)  # first -> second
            in_degree[second] += 1  # Increment in-degree of second
        
        # Queue to maintain projects with zero in-degree (no dependencies)
        zero_in_degree_queue = deque([project for project in projects if in_degree[project] == 0])
        
        # List to store the build order
        build_order = []
        
        # Process nodes with zero in-degrees
        while zero_in_degree_queue:
            current = zero_in_degree_queue.popleft()
            build_order.append(current)
            
            # For every project dependent on the current one
            for neighbor in adj_list[current]:
                in_degree[neighbor] -= 1  # Reduce the in-degree since one dependency is resolved
                
                # If the neighbor's in-degree drops to 0, add it to the queue
                if in_degree[neighbor] == 0:
                    zero_in_degree_queue.append(neighbor)
        
        # If the build order contains all the projects, return the build order
        if len(build_order) == len(projects):
            return build_order
        else:
            return "Error: No valid build order exists (cycle detected)."

# Example usage:
projects = ['a', 'b', 'c', 'd', 'e', 'f']
dependencies = [('a', 'd'), ('f', 'b'), ('b', 'd'), ('f', 'a'), ('d', 'c')]

solution = Solution()
build_order = solution.findBuildOrder(projects, dependencies)
print(build_order)  # Output should be ['f', 'e', 'a', 'b', 'd', 'c']

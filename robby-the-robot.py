import numpy as np  
import matplotlib.pyplot as plt  

# Environment parameters
GRID_SIZE = 10 
ACTIONS = ['Move-North', 'Move-South', 'Move-East', 'Move-West', 'Pick-Up-Can']
ACTION_COUNT = len(ACTIONS)  # Number of possible actions
STATE_COUNT = (3**5)  # number of possible states

# Q-Learning parameters
EPISODES = 5000 
STEPS_PER_EPISODE = 200 
ALPHA = 0.2 
GAMMA = 0.9 
INITIAL_EPSILON = 0.1 

#state encoding
def encode_state(sensors):
    mapping = {'Empty': 0, 'Can': 1, 'Wall': 2}  
    encoded = 0
    # Iterate over each sensor
    for i in range(5):  
        value = mapping[sensors[i]]  
        power = 3 ** i  
        encoded += value * power  
    return encoded


# Initialize the Q-table with zeros
Q_table = np.zeros((STATE_COUNT, ACTION_COUNT))

def get_sensors(grid, position):
    x, y = position
    sensor_values = [] 

    # Current position's sensor value
    current = grid[x, y]
    sensor_values.append(current)

    # North sensor value
    if x == 0:  # Check if Robby is at the top edge of the grid
        north = 'Wall'
    else:
        north = grid[x-1, y]
    sensor_values.append(north)

    # South sensor value
    if x == GRID_SIZE - 1:  # Check if Robby is at the bottom edge of the grid
        south = 'Wall'
    else:
        south = grid[x+1, y]
    sensor_values.append(south)

    # East sensor value
    if y == GRID_SIZE - 1:  # Check if Robby is at the right edge of the grid
        east = 'Wall'
    else:
        east = grid[x, y+1]
    sensor_values.append(east)

    # West sensor value
    if y == 0:  # Check if Robby is at the left edge of the grid
        west = 'Wall'
    else:
        west = grid[x, y-1]
    sensor_values.append(west)

    return sensor_values  

# initialize the grid with cans randomly placed
def initialize_grid():
    grid = np.empty((GRID_SIZE, GRID_SIZE), dtype=object) 

    # Loop through each cell in the grid
    for x in range(GRID_SIZE):
        for y in range(GRID_SIZE):
            if x == 0 or y == 0 or x == GRID_SIZE - 1 or y == GRID_SIZE - 1:
                grid[x, y] = 'Wall'  # Set the boundary cells to 'Wall'
            else:
                # Randomly assign 'Empty' or 'Can' to internal cells
                grid[x, y] = np.random.choice(['Empty', 'Can'], p=[0.5, 0.5])  

    return grid 


#perform an action and update Robby's position and the grid
def perform_action(grid, position, action):
    x, y = position
    if action == 'Move-North' and x > 1:
        position = (x-1, y)  # Move north unless Robby is at the top row
    elif action == 'Move-South' and x < GRID_SIZE-2:
        position = (x+1, y)  # Move south unless Robby is at the bottom row
    elif action == 'Move-East' and y < GRID_SIZE-2:
        position = (y+1, y)  # Move east unless Robby is at the rightmost column
    elif action == 'Move-West' and y > 1:
        position = (x, y-1)  # Move west unless Robby is at the leftmost column
    elif action == 'Pick-Up-Can' and grid[x, y] == 'Can':
        grid[x, y] = 'Empty'  # Remove the can from the grid and give a reward
        return 10, position  # Reward for picking up a can
    return -1, position  # Default penalty for an unsuccessful action

# Epsilon-greedy algorithm to decide exploring or exploiting
def epsilon_greedy(Q_values, epsilon):
    if np.random.random() < epsilon:
        return np.random.randint(0, ACTION_COUNT)  # Choose a random action (explore)
    else:
        return np.argmax(Q_values)  # Choose the best known action (exploit)

# Main function to train the agent
def train_agent():
    rewards_per_episode = []  
    epsilon = INITIAL_EPSILON  

    for episode in range(EPISODES):
        grid = initialize_grid()  
        position = (np.random.randint(1, GRID_SIZE-1), np.random.randint(1, GRID_SIZE-1)) 
        total_reward = 0

        for _ in range(STEPS_PER_EPISODE):
            sensors = get_sensors(grid, position) 
            state = encode_state(sensors) 
            action_index = epsilon_greedy(Q_table[state], epsilon)  # Decide action
            reward, new_position = perform_action(grid, position, ACTIONS[action_index])  # Perform action and get reward
            new_sensors = get_sensors(grid, new_position)  # Read sensors for the new position
            new_state = encode_state(new_sensors)  # Get the new state
            best_future_q = np.max(Q_table[new_state])  # Get the best future Q value for updating
            Q_table[state, action_index] += ALPHA * (reward + GAMMA * best_future_q - Q_table[state, action_index])  # Update Q-table
            position = new_position  # Update position
            total_reward += reward  # Accumulate reward
        rewards_per_episode.append(total_reward)  # Append the total reward of this episode
        if episode % 50 == 0 and epsilon > 0:
            epsilon *= 0.99  # Reduce epsilon gradually to decrease exploration over time

    return rewards_per_episode

# Plots of reqwards 
def plot_rewards(rewards, title='Training Rewards'):
    plt.figure(figsize=(10, 5))
    plt.plot(rewards)
    plt.xlabel('Episodes') 
    plt.ylabel('Total Reward') 
    plt.title(title)  
    plt.show()

# Train the agent and plot the results
rewards = train_agent()
plot_rewards(rewards)

def test_agent(Q_table, episodes=1000, steps_per_episode=200, epsilon=0.1):
    rewards_per_episode = []
    
    for episode in range(episodes):
        grid = initialize_grid()  # Randomly place cans
        position = (np.random.randint(1, GRID_SIZE-1), np.random.randint(1, GRID_SIZE-1))
        total_reward = 0
        
        for step in range(steps_per_episode):
            sensors = get_sensors(grid, position)
            state = encode_state(sensors)
            action_index = epsilon_greedy(Q_table[state], epsilon)  # Fixed epsilon during testing
            reward, new_position = perform_action(grid, position, ACTIONS[action_index])
            position = new_position
            total_reward += reward
        
        rewards_per_episode.append(total_reward)
    
    return rewards_per_episode

# Run the test episodes
test_rewards = test_agent(Q_table)

# Calculate the average and standard deviation
test_average = np.mean(test_rewards)
test_std_dev = np.std(test_rewards)

print(f"Test-Average: {test_average}")
print(f"Test-Standard Deviation: {test_std_dev}")

# plot results
plt.figure(figsize=(10, 5))
plt.plot(test_rewards)
plt.xlabel('Episode')
plt.ylabel('Total Reward')
plt.title('Test Rewards per Episode')
plt.show()


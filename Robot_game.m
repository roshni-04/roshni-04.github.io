% Define the grid for the robot's movement
x_range = [0 5];
y_range = [0 5];
step_size = 1;
[x, y] = ndgrid(x_range(1):step_size:x_range(2), y_range(1):step_size:y_range(2));

% Define the can position
can_position = [2, 2];

% Genetic Algorithm
population_size = 100;
num_generations = 50;
mutation_rate = 0.1;

% Initialize the population with random solutions
pop = randi([1, 4], population_size, 100); % Assuming a solution of length 100

% Initialize a figure for visualization
figure;
hold on;
axis([x_range, y_range]);
plot(can_position(1), can_position(2), 'ro', 'MarkerSize', 10); % Plot the can

robot_handle = plot(1, 1, 'bo', 'MarkerSize', 10); % Plot the robot, starting at [1, 1]
drawnow;

for generation = 1:num_generations
    % ... (rest of your code for genetic algorithm)

    % Simulate the robot's movement with the best solution
    robot_position = [1, 1];
    for i = 1:length(best_solution)
        movement_command = '';
        if best_solution(i) == 1
            movement_command = 'E';
        elseif best_solution(i) == 2
            movement_command = 'S';
        elseif best_solution(i) == 3
            movement_command = 'W';
        elseif best_solution(i) == 4
            movement_command = 'N';
        end

        % Update the robot's position
        robot_position = update_robot_position(robot_position, movement_command);

        % Update the robot's position on the plot
        set(robot_handle, 'XData', robot_position(1), 'YData', robot_position(2));
        drawnow;

        distance_threshold = 0.5;
        distance = calculate_distance(robot_position, can_position);

        if distance <= distance_threshold
            disp('The robot has reached the can.');
            break;
        end
    end
end

% Helper function to evaluate fitness
function fitness = evalfitness(solution)
    x = 1; % Starting x-coordinate
    y = 1; % Starting y-coordinate
    can_position = [5, 5]; % Coordinates of the can
    fitness = 0;

    for i = 1:length(solution)
        if solution(i) == 1 % Move right
            x = x + 1;
        elseif solution(i) == 2 % Move down
            y = y + 1;
        elseif solution(i) == 3 % Move left
            x = x - 1;
        elseif solution(i) == 4 % Move up
            y = y - 1;
        end

        % If the robot hits a wall, can, or a hole, break and set a negative fitness
        if x < 0 || x > 5 || y < 0 || y > 5 || is_can_reached([x, y], can_position) || solution(i) == 5
            fitness = -100000;
            break;
        end

        % The fitness increases as the robot gets closer to the can
        fitness = fitness + calculate_distance([x, y], can_position);
    end
end

% Helper function to check if the can is reached
function reached = is_can_reached(robot_position, can_position)
    reached = norm(robot_position - can_position) < 0.5; % Adjust the threshold as needed
end

% Helper function to calculate the Euclidean distance between two points
function distance = calculate_distance(point1, point2)
    distance = norm(point1 - point2);
end

% Helper function for tournament selection
function parent = tournament_selection(pop, fitness)
    tournament_size = 5; % Adjust the tournament size as needed

    % Randomly select individuals for the tournament
    tournament_indices = randperm(length(pop), tournament_size);
    tournament_fitness = fitness(tournament_indices);

    % Find the individual with the highest fitness in the tournament
    [~, max_index] = max(tournament_fitness);
    selected_individual = pop(tournament_indices(max_index), :);

    parent = selected_individual;
end

% Helper function for one-point crossover
function child = one_point_crossover(parent1, parent2)
    n = length(parent1);

    % Choose a random crossover point (between 1 and n-1)
    crossover_point = randi([1, n-1]);

    % Create the child solution by taking part of parent1 and part of parent2
    child = [parent1(1:crossover_point), parent2(crossover_point+1:end)];
end

% Helper function to update robot's position
function robot_position = update_robot_position(robot_position, movement_command)
    step_size = 1; % Assuming a step size of 1 unit

    switch movement_command
        case 'N' % Move north
            robot_position(2) = robot_position(2) + step_size;
        case 'S' % Move south
            robot_position(2) = robot_position(2) - step_size;
        case 'E' % Move east
            robot_position(1) = robot_position(1) + step_size;
        case 'W' % Move west
            robot_position(1) = robot_position(1) - step_size;
        otherwise
            error('Invalid movement command');
    end
end

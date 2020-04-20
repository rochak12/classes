def reward_function(params):
    import math
    from statistics import mean

    '''
    Example of penalize steering, which helps mitigate zig-zag behaviors
    '''

    # Read input parameters
    distance_from_center = params['distance_from_center']
    track_width = params['track_width']
    all_wheels_on_track = params['all_wheels_on_track']
    progress = params['progress']
    waypoints = params['waypoints']
    steering = abs(params['steering_angle'])

    # Max min reward
    reward_MIN = 1e-3
    reward_MAX = 1e3

    ABS_STEERING_THRESHOLD = .85

    # Calculate 3 markers that are at varying distances away from the center line
    # marker_1 = 0.1 * track_width
    marker_2 = 0.25 * track_width
    marker_3 = 0.5 * track_width

    # Give higher reward if the agent is closer to center line and vice versa
    if not all_wheels_on_track:  # Fail them if off Track
        reward = reward_MIN
        return reward
    else:
        reward = reward_MAX * progress

    if progress == 1:
        reward = reward_MAX
        return reward

    if distance_from_center > marker_2:
        reward *= 1 - (distance_from_center / marker_3)

    # Steering penality threshold, change the number based on your action space setting
    ABS_STEERING_THRESHOLD = 15

    # Penalize reward if the agent is steering too much
    if steering > ABS_STEERING_THRESHOLD:
        reward *= 0.8

    # make sure reward value returned is within the prescribed value range.
    reward = max(reward, REWARD_MIN)
    reward = min(reward, REWARD_MAX)

    return float(reward)    